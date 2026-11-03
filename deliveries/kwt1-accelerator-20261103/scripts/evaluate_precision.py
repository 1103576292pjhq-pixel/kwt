#!/usr/bin/env python3
"""Measure the current frozen FFN1 model on read-only real validation data."""
import argparse
from collections import Counter
import csv
import hashlib
import json
import math
from numbers import Integral
import os
from pathlib import Path
import subprocess
import sys
import time

os.environ['OPENBLAS_NUM_THREADS'] = '1'
os.environ['MKL_NUM_THREADS'] = '1'
sys.dont_write_bytecode = True
PROJECT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT))
import numpy as np
from model.fixed_numeric import encode_finite, decode_fixed, ffn1_int16, load_contract

SOURCE_COMMIT = '237e4097afd4f6851e0b82f0a8d65c2dfe8eae30'


def sha256(path):
    digest = hashlib.sha256()
    with Path(path).open('rb') as stream:
        for chunk in iter(lambda: stream.read(1024*1024), b''):
            digest.update(chunk)
    return digest.hexdigest()


def write_json(path, value):
    Path(path).write_text(json.dumps(value, ensure_ascii=False, indent=2, allow_nan=False)+'\n', encoding='utf-8')


class LayerMetrics:
    """Combine weighted output errors before applying the guide's RMS ratio."""
    def __init__(self, layer):
        self.layer = layer
        self.sse = self.energy = self.absolute_error = self.max_error = 0.
        self.count = self.tasks = 0
        self.worst = {'sample': None, 'nrmse': 0.}

    def add(self, reference, actual, sample, multiplicity=1):
        if (isinstance(multiplicity, (bool, np.bool_)) or not isinstance(multiplicity, Integral)
                or multiplicity <= 0):
            raise ValueError('Sample multiplicity must be a positive integer')
        reference, actual = np.asarray(reference, dtype=np.float64), np.asarray(actual, dtype=np.float64)
        if reference.shape != actual.shape or not reference.size:
            raise ValueError('Nonempty matching reference/output shapes required')
        if not np.isfinite(reference).all() or not np.isfinite(actual).all():
            raise ValueError('Non-finite reference/output')
        error = actual-reference
        sse = float(np.sum(error*error, dtype=np.float64))
        energy = float(np.sum(reference*reference, dtype=np.float64))
        if not math.isfinite(sse) or not math.isfinite(energy):
            raise ValueError('Non-finite squared energy')
        task_nrmse = math.sqrt(sse/reference.size)/max(math.sqrt(energy/reference.size), 1e-8)
        if task_nrmse >= self.worst['nrmse']:
            self.worst = {'sample': sample, 'nrmse': task_nrmse}
        self.sse += multiplicity*sse
        self.energy += multiplicity*energy
        self.absolute_error += multiplicity*float(np.sum(np.abs(error), dtype=np.float64))
        self.max_error = max(self.max_error, float(np.max(np.abs(error))))
        self.count += multiplicity*reference.size
        self.tasks += multiplicity

    def result(self):
        if not self.count:
            raise ValueError('No measurements')
        rmse, reference_rms = math.sqrt(self.sse/self.count), math.sqrt(self.energy/self.count)
        nrmse = rmse/max(reference_rms, 1e-8)
        return dict(layer=self.layer, tasks=self.tasks, values=self.count,
                    squared_error=self.sse, reference_energy=self.energy,
                    rmse=rmse, reference_rms=reference_rms, nrmse=nrmse, nrmse_percent=100*nrmse,
                    mae=self.absolute_error/self.count, max_abs_error=self.max_error,
                    worst_task=self.worst, within_3_percent=nrmse <= .03)


def source_identity(workspace):
    repo = workspace/'keyword-transformer'
    commit = subprocess.check_output(['git','-C',str(repo),'rev-parse','HEAD'], text=True).strip()
    status = subprocess.check_output(['git','-C',str(repo),'status','--porcelain'], text=True)
    if commit != SOURCE_COMMIT or status:
        raise ValueError('Specified upstream model source must be pinned and clean')
    model = repo/'models_data_v2_12_labels/kwt1'
    checkpoint = {p.name:sha256(p) for p in sorted(model.glob('best_weights.*'))}
    if set(checkpoint) != {'best_weights.index','best_weights.data-00000-of-00001'}:
        raise ValueError('Unexpected checkpoint files')
    return dict(source_commit=commit, source_clean=True, checkpoint_sha256=checkpoint,
                model_flags_sha256=sha256(model/'flags.json'),
                model_labels_sha256=sha256(model/'labels.txt'))


def checked_audio(workspace, samples):
    root = (workspace/'datasets/data2').resolve()
    val_list = root/'validation_list.txt'
    validation = set(val_list.read_text().splitlines())
    checked = 0
    for sample in samples:
        if sample['split'] != 'validation':
            raise ValueError('Refusing non-validation sample')
        if sample['path'] is None:
            if sample['label'] != '_silence_':
                raise ValueError('Only generated silence can omit a WAV file')
            continue
        relative = sample['path']
        path = (root/relative).resolve()
        if root not in path.parents or relative not in validation:
            raise ValueError('WAV not inside original validation partition: '+relative)
        if sha256(path) != sample['sha256']:
            raise ValueError('Changed raw WAV: '+relative)
        checked += 1
    return dict(raw_wavs_verified=checked, validation_list_sha256=sha256(val_list))


class Evaluation:
    def __init__(self):
        self.metrics = [LayerMetrics(i+1) for i in range(12)]
        self.stats = [dict(x_clips=0, w_clips=0, bias_clips=0, output_saturations=0,
                           raw_overflows=0, last_flags=0, source_affine_max_nrmse=0.) for _ in range(12)]
        self.hashes = [hashlib.sha256() for _ in range(12)]
        self.flag_hashes = [hashlib.sha256() for _ in range(12)]

    def parameters(self, weights, biases):
        self.float_w = [np.asfortranarray(w, dtype=np.float64) for w in weights]
        self.float_b = [np.asarray(b, dtype=np.float64) for b in biases]
        self.qw = [encode_finite(np.asfortranarray(w), 'w') for w in weights]
        self.qb = [encode_finite(b, 'bias') for b in biases]

    def task(self, layer, sample, x, reference):
        multiplicity = sample.get('multiplicity', 1)
        if x.shape != (99,64) or reference.shape != (99,256):
            raise ValueError('Wrong production task dimensions')
        encoded = encode_finite(x, 'x')
        y, flags = ffn1_int16(encoded.values, self.qw[layer].values, self.qb[layer].values)
        decoded = decode_fixed(y, 'y')
        self.metrics[layer].add(reference, decoded, sample['path'] or '_silence_', multiplicity)
        stat = self.stats[layer]
        for key, amount in [('x_clips',encoded.endpoint_clipped_count),
                            ('w_clips',self.qw[layer].endpoint_clipped_count),
                            ('bias_clips',self.qb[layer].endpoint_clipped_count),
                            ('output_saturations',int(np.count_nonzero(flags & 2))),
                            ('raw_overflows',int(np.count_nonzero(flags & 1))),
                            ('last_flags',int(np.count_nonzero(flags & 4)))]:
            stat[key] += multiplicity*amount
        exact = np.asarray(x, dtype=np.float64) @ self.float_w[layer] + self.float_b[layer]
        reference64 = np.asarray(reference, dtype=np.float64)
        cross = float(np.sqrt(np.mean((exact-reference64)**2)) /
                      max(float(np.sqrt(np.mean(reference64**2))), 1e-8))
        if not math.isfinite(cross) or cross >= 1e-6:
            raise ValueError('Floating reference is not the expected affine calculation')
        stat['source_affine_max_nrmse'] = max(stat['source_affine_max_nrmse'], cross)
        self.hashes[layer].update(np.ascontiguousarray(y, dtype='<i2').tobytes())
        self.flag_hashes[layer].update(np.ascontiguousarray(flags).tobytes())

    def results(self):
        layers = []
        for i, metrics in enumerate(self.metrics):
            result = metrics.result()
            result.update(self.stats[i])
            result['unique_task_y_stream_sha256'] = self.hashes[i].hexdigest()
            result['unique_task_flags_stream_sha256'] = self.flag_hashes[i].hexdigest()
            layers.append(result)
        return layers


def cached_run(workspace, cache, out, evaluator, identity):
    manifest_path = cache/'manifest.json'
    manifest_hash = sha256(manifest_path)
    manifest = json.loads(manifest_path.read_text())
    if manifest['status'] != 'passed' or manifest['split'] != 'validation':
        raise ValueError('Completed validation cache required')
    if manifest['source_commit'] != SOURCE_COMMIT or manifest['checkpoint_sha256'] != identity['checkpoint_sha256']:
        raise ValueError('Cache source/checkpoint identity mismatch')
    samples = manifest['samples']
    if len(samples) != manifest['sample_count']:
        raise ValueError('Sample list length mismatch')
    audit = checked_audio(workspace, samples)
    files = {}
    for record in manifest['files']:
        path = (cache/record['path']).resolve()
        if cache.resolve() not in path.parents or sha256(path) != record['sha256']:
            raise ValueError('Cache file changed: '+record['path'])
        value = np.load(str(path), mmap_mode='r', allow_pickle=False)
        if list(value.shape) != record['shape'] or value.dtype != np.dtype('<f4') or not np.isfinite(value).all():
            raise ValueError('Invalid float cache array: '+record['path'])
        files[record['path']] = dict(sha256=record['sha256'], shape=list(value.shape))
    expected = {'audio.npy','logits.npy'} | {
        'layer_%02d/%s.npy'%(layer,name) for layer in range(12) for name in ('X','W','b','Y_reference')}
    if set(files) != expected:
        raise ValueError('Cache must include exactly the 12 complete FFN layers plus audio/logits')
    evaluator.parameters([np.load(str(cache/('layer_%02d/W.npy'%i)),allow_pickle=False) for i in range(12)],
                         [np.load(str(cache/('layer_%02d/b.npy'%i)),allow_pickle=False) for i in range(12)])
    for layer in range(12):
        x = np.load(str(cache/('layer_%02d/X.npy'%layer)), mmap_mode='r',allow_pickle=False)
        y = np.load(str(cache/('layer_%02d/Y_reference.npy'%layer)), mmap_mode='r',allow_pickle=False)
        if x.shape != (len(samples),99,64) or y.shape != (len(samples),99,256):
            raise ValueError('Cache sample dimension mismatch')
        for position, sample in enumerate(samples):
            evaluator.task(layer, sample, x[position], y[position])
        print('CACHE layer=%d/12 samples=%d nrmse=%.8f%%'%(layer+1,len(samples),evaluator.metrics[layer].result()['nrmse_percent']),flush=True)
    if sha256(manifest_path) != manifest_hash:
        raise ValueError('Source manifest changed during run')
    write_json(out/'samples.json', samples)
    write_json(out/'cache-audit.json', dict(path=str(cache),manifest_sha256=manifest_hash,files=files,**audit))
    return samples, sum(s.get('multiplicity',1) for s in samples), audit


def full_run(workspace, out, evaluator):
    # Reuse only the personal float extraction runner, never old fixed-point code.
    extraction = workspace/'kwt1-accelerator-2026/scripts/model'
    sys.path.insert(0, str(extraction))
    from kwt_reference import KWTReference
    from validation_references import validation_samples, load_validation_audio
    source_files = ['kwt_reference.py','validation_references.py','smoke_check.py',
                    'export_ffn_sample.py','analyze_training_ranges.py']
    before = {name:sha256(extraction/name) for name in source_files}
    with KWTReference() as reference:
        samples, original_count = validation_samples(reference, per_label=None)
        if sum(s['multiplicity'] for s in samples) != original_count:
            raise ValueError('Original validation index multiplicity mismatch')
        audit = checked_audio(workspace,samples)
        write_json(out/'samples.json',dict(split='validation',original_count=original_count,samples=samples))
        evaluator.parameters(reference.weights, reference.biases)
        for position, sample in enumerate(samples):
            tasks, _ = reference.run(load_validation_audio(reference, sample))
            for layer, (x,y) in enumerate(tasks):
                evaluator.task(layer,sample,x,y)
            if position == 0 or (position+1)%100 == 0 or position+1 == len(samples):
                print('FULL unique=%d/%d original=%d'%(position+1,len(samples),original_count),flush=True)
                write_json(out/'progress.json',dict(unique_finished=position+1,unique_total=len(samples)))
        audit['matched_checkpoint_tensors'] = reference.matched_parameters
    if before != {name:sha256(extraction/name) for name in source_files}:
        raise ValueError('Float extraction source changed during run')
    audit['extraction_sources_sha256'] = before
    return samples, original_count, audit


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--mode',choices=('cache','full'),required=True)
    parser.add_argument('--workspace',type=Path,default=PROJECT.parent)
    parser.add_argument('--cache',type=Path)
    parser.add_argument('--output',type=Path,required=True)
    args = parser.parse_args()
    out = args.output.resolve()
    out.mkdir(parents=True,exist_ok=False)
    start = time.monotonic()
    try:
        contract = load_contract(PROJECT/'model/numeric-contract.json')
        model_hash = sha256(PROJECT/'model/fixed_numeric.py')
        contract_hash = sha256(PROJECT/'model/numeric-contract.json')
        script_hash = sha256(Path(__file__))
        workspace = args.workspace.resolve()
        identity = source_identity(workspace)
        write_json(out/'state.json',dict(status='running',mode=args.mode))
        evaluator = Evaluation()
        if args.mode == 'cache':
            cache = args.cache or workspace/'generated/validation/20261018_val_p20_v1'
            samples, count, audit = cached_run(workspace,cache,out,evaluator,identity)
        else:
            samples, count, audit = full_run(workspace,out,evaluator)
        layers = evaluator.results()
        worst = max(layers,key=lambda layer:layer['nrmse'])
        if model_hash != sha256(PROJECT/'model/fixed_numeric.py') or contract_hash != sha256(PROJECT/'model/numeric-contract.json'):
            raise ValueError('Frozen numeric model changed during evaluation')
        if identity != source_identity(workspace):
            raise ValueError('Upstream/checkpoint changed during evaluation')
        report = dict(status='COMPLETED_LOCAL_VALIDATION_SOFTWARE_EVALUATION',mode=args.mode,
                      spec_id=contract['spec_id'],samples=count,unique_computations=len(samples),
                      layer_tasks=count*12,output_values=count*12*99*256,
                      class_counts=dict(Counter(s['label'] for s in samples)),
                      weighted_class_counts={label:sum(s.get('multiplicity',1) for s in samples if s['label']==label)
                                             for label in sorted(set(s['label'] for s in samples))},
                      worst_layer=worst['layer'],worst_layer_nrmse=worst['nrmse'],
                      worst_layer_nrmse_percent=worst['nrmse_percent'],
                      all_layers_within_3_percent=worst['nrmse']<=.03,
                      worst_task_nrmse=max(layer['worst_task']['nrmse'] for layer in layers),
                      layers=layers,source=identity,audit=audit,elapsed_seconds=time.monotonic()-start,
                      runtime=dict(python=sys.version,numpy=np.__version__,tensorflow=sys.modules['tensorflow'].__version__ if 'tensorflow' in sys.modules else None),
                      numeric_model_sha256=model_hash,numeric_contract_sha256=contract_hash,evaluator_sha256=script_hash,
                      command=sys.argv,
                      limitations=['Local development validation split, not the organizer unpublished 600-sample set.',
                                   'Software numerical model evaluation; no new real-data RTL/SoC run.',
                                   'Float extraction uses TensorFlow2.4.0 in place of required2.4.0rc1; equivalence unproven.',
                                   'Frozen scales unchanged; no training, fine-tuning, or test-split calibration.'])
        for name in ('x_clips','w_clips','bias_clips','output_saturations','raw_overflows'):
            report[name] = sum(layer[name] for layer in layers)
        write_json(out/'report.json',report)
        with (out/'layers.csv').open('w',encoding='utf-8-sig',newline='') as stream:
            names=['layer','tasks','values','nrmse_percent','rmse','mae','max_abs_error',
                   'x_clips','w_clips','bias_clips','output_saturations','raw_overflows']
            writer=csv.DictWriter(stream,fieldnames=names,extrasaction='ignore')
            writer.writeheader();writer.writerows(layers)
        rows=['# 当前FFN1数值方案：真实验证数据精度\n',
              '样本数：%d；唯一计算输入：%d；12层合计%d项输出。'%(count,len(samples),report['output_values']),
              '最差第%d层：NRMSE %.8f%%；本科门槛3%%；本地验证结果：%s。'%(worst['layer'],worst['nrmse_percent'],'满足' if worst['nrmse']<=.03 else '不满足'),
              '\n| 层 | NRMSE (%) | 最大绝对误差 | 输出饱和数 |\n| --- | ---: | ---: | ---: |']
        rows += ['| %d | %.8f | %.9g | %d |'%(layer['layer'],layer['nrmse_percent'],layer['max_abs_error'],layer['output_saturations']) for layer in layers]
        rows += ['\n指标按每层汇总全部样本的误差RMS / max(浮点参考RMS,1e-8)，再取12层最大值。',
                 '\n当前整数模型重新运算，不读取或继承旧候选数值报告。原始数据、权重、RTL和数值尺度均未修改。',
                 '\n此结果是软件数值模型的本地验证集结果，不是官方600条验收或新的真实数据RTL通过。',
                 '浮点提取依赖TensorFlow2.4.0，与原2.4.0rc1的运行时等价性未证明。']
        (out/'README.md').write_text('\n\n'.join(rows)+'\n',encoding='utf-8')
        write_json(out/'state.json',dict(status='complete',within_3_percent=report['all_layers_within_3_percent']))
        print('PRECISION_DONE samples=%d layers=12 worst_layer=%d nrmse=%.8f%% outputs=%d saturations=%d'%
              (count,worst['layer'],worst['nrmse_percent'],report['output_values'],report['output_saturations']),flush=True)
        print('REPORT',out/'report.json',flush=True)
    except Exception as error:
        write_json(out/'state.json',dict(status='failed',error=str(error)))
        raise


if __name__ == '__main__':
    main()

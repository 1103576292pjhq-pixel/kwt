"""Export official full KWT-1 encoder stages into a new immutable namespace.

Uses frozen preprocessed audio, restores every parameter against the actual
checkpoint, and compares same-object replay against the complete original
model in the same TF session. No baseline file or upstream source is changed.
"""
import argparse
import json
import os
from pathlib import Path
import platform
import sys
import time
import wave

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
os.environ.setdefault('CUDA_VISIBLE_DEVICES','-1')
os.environ.setdefault('TF_CPP_MIN_LOG_LEVEL','2')
os.environ.setdefault('TF_DETERMINISTIC_OPS','1')
sys.dont_write_bytecode=True
import numpy as np
from model.run_baseline import official_flags, restore_and_verify, verify_sources
from numeric.encoder.contracts import STAGES, layout, sha, write_array, json_write, metrics


def layer_parameters(block):
    return [block.att.query_dense.kernel,block.att.key_dense.kernel,
            block.att.value_dense.kernel,block.att.combine_heads.kernel,
            block.att.combine_heads.bias,block.layernorm1.gamma,block.layernorm1.beta,
            block.ffn.layers[0].kernel,block.ffn.layers[0].bias,
            block.ffn.layers[2].kernel,block.ffn.layers[2].bias,
            block.layernorm2.gamma,block.layernorm2.beta]


def prepare_dataset(manifest_path,flags):
    """Use the exact official offline audio path for a provenance-checked set."""
    import tensorflow as tf
    from kws_streaming.data import input_data
    manifest_path=manifest_path.resolve()
    document=json.loads(manifest_path.read_text(encoding='utf-8'))
    samples=[]
    for item in document['samples']:
        path=(manifest_path.parent/item['relative_path']).resolve()
        if manifest_path.parent not in path.parents:raise ValueError('dataset path escapes root')
        if sha(path)!=item['sha256']:raise ValueError('dataset hash mismatch: '+str(path))
        with wave.open(str(path),'rb') as wav:
            if (wav.getframerate(),wav.getnchannels(),wav.getsampwidth())!=(16000,1,2):
                raise ValueError('dataset audio must be 16k mono PCM16')
        with tf.Graph().as_default(),tf.compat.v1.Session() as session:
            processor=object.__new__(input_data.AudioProcessor)
            processor.prepare_processing_graph(flags)
            audio=processor.get_features_for_wav(str(path),flags,session)[0]
        samples.append({'sample_id':item['sample_id'],'partition':item['partition'],
                        'ground_truth_label':item.get('ground_truth_label',item['word']),
                        'audio':audio.reshape(1,-1),
                        'source_audio':{'path':str(path.relative_to(ROOT)),'sha256':sha(path)}})
    if len({s['sample_id'] for s in samples})!=len(samples):raise ValueError('duplicate sample id')
    return samples,{'manifest':str(manifest_path.relative_to(ROOT)),'sha256':sha(manifest_path),
                    'metadata':{k:v for k,v in document.items() if k!='samples'}}


def observed_model(tf,builder,flags):
    from kws_streaming.models.transformer_utils import TransformerBlock
    original_block=TransformerBlock.call
    observations={}
    def block_call(self,inputs,training):
        block=self
        x=inputs
        # Observe actual object calls rather than constructing equivalent
        # arithmetic. Grappler can fuse a manually reconstructed GELU/Dense
        # graph differently, causing small same-session differences. Every
        # wrapper below returns the original tensor unchanged.
        captured={}
        original_dense=tf.keras.layers.Dense.call
        original_norm=tf.keras.layers.LayerNormalization.call
        original_attention=block.att.attention
        names={id(block.att.query_dense):'q',id(block.att.key_dense):'k',
               id(block.att.value_dense):'v',id(block.att.combine_heads):'attn',
               id(block.ffn.layers[0]):'ffn1',id(block.ffn.layers[2]):'ffn2'}
        def dense_call(layer,values):
            result=original_dense(layer,values)
            name=names.get(id(layer))
            if name:
                captured[name]=result
                if name=='attn':captured['context']=values
                if name=='ffn2':captured['gelu']=values
            return result
        def norm_call(layer,values):
            result=original_norm(layer,values)
            if layer is block.layernorm1:captured.update(r1=values,n1=result)
            if layer is block.layernorm2:captured.update(r2=values,y=result)
            return result
        def attention_call(query,key,value):
            result,prob=original_attention(query,key,value)
            if prob.op.type!='Softmax':
                raise ValueError('actual softmax op cannot be observed: '+prob.op.type)
            captured['scores']=prob.op.inputs[0][:,0]
            captured['prob']=prob[:,0]
            return result,prob
        tf.keras.layers.Dense.call=dense_call
        tf.keras.layers.LayerNormalization.call=norm_call
        block.att.attention=attention_call
        try:
            result=original_block(block,x,training)
        finally:
            tf.keras.layers.Dense.call=original_dense
            tf.keras.layers.LayerNormalization.call=original_norm
            block.att.attention=original_attention
        if set(captured)!=set(STAGES):
            raise ValueError('missing observed official stages: '+str(set(STAGES)-set(captured)))
        observations[block]=(x,[captured[name] for name in STAGES])
        return result
    TransformerBlock.call=block_call
    try:
        model=builder.model(flags)
    finally:
        TransformerBlock.call=original_block
    tr=[layer for layer in model.layers if hasattr(layer,'enc_layers')][0]
    if len(observations)!=12:raise ValueError('must observe all 12 actual model blocks')
    before=[id(w) for w in model.weights]
    inputs=[observations[b][0] for b in tr.enc_layers]
    stages=[observations[b][1] for b in tr.enc_layers]
    initial=inputs[0];final=stages[-1][-1]
    # All stages belong to the actual complete original graph, with no neural
    # arithmetic reconstructed. Check its final output by replaying only the
    # original classification object on the observed final encoder tensor.
    head=[layer for layer in model.layers if isinstance(layer,tf.keras.Sequential)][0]
    logits=head(final[:,0])
    if before!=[id(w) for w in model.weights]:raise ValueError('replay created variables')
    return model,tr,initial,inputs,stages,final,logits,head


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,default=ROOT/'reports/encoder/export')
    parser.add_argument('--dataset-manifest',type=Path)
    args=parser.parse_args()
    output=args.output.resolve()
    allowed=(ROOT/'reports/encoder').resolve()
    if allowed not in output.parents:
        raise ValueError('output must be below reports/encoder')
    output.mkdir(parents=True,exist_ok=True)
    if (output/'manifest.json').exists():(output/'manifest.json').unlink()
    json_write(output/'status.json',{'status':'RUNNING','started_unix':time.time()})
    import tensorflow as tf
    import tensorflow_addons as tfa
    if tf.__version__!='2.4.0':
        raise ValueError('requires the pinned TF 2.4 compatibility runtime')
    vendor=ROOT/'vendor/keyword-transformer'
    source=verify_sources(vendor)
    flags,overrides,builder=official_flags(vendor)
    baseline_root=ROOT/'reports/model/baseline'
    old=json.loads((baseline_root/'manifest.json').read_text(encoding='utf-8'))
    from kws_streaming.data import input_data
    official_labels=(vendor/'models_data_v2_12_labels/kwt1/labels.txt').read_text(encoding='utf-8').splitlines()
    labels_from_flags=input_data.prepare_words_list(flags.wanted_words.split(','),flags.split_data)
    if old['labels']!=official_labels or official_labels!=labels_from_flags:
        raise ValueError('class mapping differs between official labels/flags and frozen baseline')
    if args.dataset_manifest:
        samples,dataset=prepare_dataset(args.dataset_manifest,flags)
    else:
        samples=old['samples']
        dataset={'manifest':str((baseline_root/'manifest.json').relative_to(ROOT)),
                 'sha256':sha(baseline_root/'manifest.json'),'scope':'Three prior frozen preprocessed inputs'}
    config=tf.compat.v1.ConfigProto(intra_op_parallelism_threads=1,inter_op_parallelism_threads=1,
                                  device_count={'GPU':0})
    tf.keras.backend.clear_session()
    with tf.Graph().as_default(),tf.compat.v1.Session(config=config) as session:
        tf.compat.v1.keras.backend.set_session(session)
        tf.compat.v1.keras.backend.set_learning_phase(0)
        tf.compat.v1.set_random_seed(1234)
        model,tr,initial,inputs,stages,final,replay_logits,head=observed_model(tf,builder,flags)
        checkpoint_dir=vendor/'models_data_v2_12_labels/kwt1'
        restored=restore_and_verify(tf,session,model,checkpoint_dir/'best_weights')
        if restored['variable_count']!=162:
            raise ValueError('expected all 162 parameters')
        key_by_name={v['variable']:v['checkpoint_key'] for v in restored['variables']}
        semantic=[]
        globals_=[('patch_kernel',tr.patch_proj.kernel),('patch_bias',tr.patch_proj.bias),
                  ('position_embedding',tr.pos_emb),('class_embedding',tr.class_emb),
                  ('classifier_kernel',head.layers[0].kernel),('classifier_bias',head.layers[0].bias)]
        semantic.extend(globals_)
        for i,block in enumerate(tr.enc_layers):
            semantic.extend(('layer_{:02d}/{}'.format(i,e['name']),v)
                            for e,v in zip(layout(),layer_parameters(block)))
        if len(semantic)!=162 or len({id(v) for _,v in semantic})!=162:
            raise ValueError('semantic mapping is not one-to-one')
        params=session.run([v for _,v in semantic])
        mapping={name:value for (name,_),value in zip(semantic,params)}
        manifest={'schema_version':1,'status':'PASS','shape':{'m':99,'d':64,'h':256,'layers':12},
                  'source':source,'design_sha256':sha(ROOT/'work/formal_seven_design.md'),
                  'checkpoint_sha256':{p.name:sha(p) for p in sorted(checkpoint_dir.glob('best_weights.*'))},
                  'original_baseline_manifest_sha256':sha(baseline_root/'manifest.json'),
                  'dataset':dataset,
                  'labels':official_labels,'label_to_index':{name:i for i,name in enumerate(official_labels)},
                  'label_mapping_verified_against_official_flags':True,
                  'label_flags':{'wanted_words':flags.wanted_words,'split_data':flags.split_data},
                  'weight_layout':layout(),'weight_words':49792,
                  'stages':list(STAGES),'parameters':[],'weights':[],'samples':[],
                  'runtime':{'python':platform.python_version(),'tensorflow':tf.__version__,
                             'tensorflow_addons':tfa.__version__,'numpy':np.__version__,
                             'cpu_threads':1,'gpu':False,'rc1_bit_identity_claim':False},
                  'scope':'Provenance-checked engineering subset, not official 600 samples; official precise-erf floating reference',
                  'export_method':'Observe original complete model Dense/LN/attention tensors, return all original tensors unchanged; verify every actual layer boundary and replay original classifier on actual final encoder output'}
        count=0
        for (name,var),value in zip(semantic,params):
            item=write_array(output,'parameters/'+name,value)
            item.update(name=name,variable=var.name,checkpoint_key=key_by_name[var.name])
            manifest['parameters'].append(item)
            count+=value.size
        if count!=607308:
            raise ValueError('incorrect scalar count')
        manifest['parameter_count']=count
        for i in range(12):
            arrays=[mapping['layer_{:02d}/{}'.format(i,e['name'])].reshape(-1) for e in layout()]
            packed=np.concatenate(arrays)
            if packed.size!=49792:
                raise ValueError('incorrect layer pack length')
            item=write_array(output,'weights/layer_{:02d}'.format(i),packed)
            item['layer_index']=i
            manifest['weights'].append(item)
        manifest['classifier']={name:next(p for p in manifest['parameters'] if p['name']==name)
                                for name in ('classifier_kernel','classifier_bias')}
        fetches=[model.outputs[0],initial,final,replay_logits,inputs,stages]
        for sample in samples:
            sid=sample['sample_id']
            if 'audio' in sample:
                audio=sample['audio'];source_audio=sample['source_audio']
            else:
                audio_path=baseline_root/sample['audio_array']['path']
                if sha(audio_path)!=sample['audio_array']['sha256']:
                    raise ValueError('frozen audio changed')
                audio=np.load(str(audio_path),allow_pickle=False).reshape(1,-1)
                source_audio={'path':str(audio_path.relative_to(ROOT)),'sha256':sha(audio_path)}
            logits,h0,last,replayed,in_values,stage_values=session.run(
                fetches,feed_dict={model.inputs[0]:audio})
            if not np.array_equal(logits.view(np.uint32),replayed.view(np.uint32)):
                raise ValueError('same-graph complete replay logits differ')
            item={'sample_id':sid,'partition':sample['partition'],'ground_truth_label':sample['ground_truth_label'],
                  'source_audio':source_audio,
                  'same_graph_logits_bit_equal':True,'layers':[],
                  'input':write_array(output,'cases/'+sid+'/input',h0[0]),
                  'final':write_array(output,'cases/'+sid+'/final',last[0]),
                  'logits':write_array(output,'cases/'+sid+'/logits',logits[0])}
            predicted=int(np.argmax(logits))
            item['predicted_index']=predicted;item['predicted_label']=old['labels'][predicted]
            if 'logits_array' in sample:
                old_logits=np.load(str(baseline_root/sample['logits_array']['path']),allow_pickle=False)
                item['old_baseline_logits_comparison']=metrics(logits[0],old_logits)
            for i,(iv,sv) in enumerate(zip(in_values,stage_values)):
                next_value=in_values[i+1] if i<11 else last
                if not np.array_equal(sv[-1].view(np.uint32),next_value.view(np.uint32)):
                    raise ValueError('actual graph layer boundary mismatch at '+str(i))
                directory='cases/{}/layer_{:02d}/'.format(sid,i)
                layer={'layer_index':i,'input':write_array(output,directory+'input',iv[0]),
                       'same_graph_y_bit_equal':True,'actual_graph_next_input_bit_equal':True,'stages':{}}
                for name,value in zip(STAGES,sv):
                    layer['stages'][name]=write_array(output,directory+name,value[0])
                if 'logits_array' in sample:
                    old_x=baseline_root/'cases'/sid/'layer_{:02d}'.format(i+1)/'X.npy'
                    layer['old_ffn1_input_comparison']=metrics(sv[8][0],np.load(str(old_x),allow_pickle=False))
                item['layers'].append(layer)
            manifest['samples'].append(item)
            print('Official export {}: {} complete layers; same-session replay exact; prediction={}'.format(sid,12,item['predicted_label']),flush=True)
        after=session.run([v for _,v in semantic])
        if any(not np.array_equal(a.view(np.uint32),b.view(np.uint32)) for a,b in zip(params,after)):
            raise ValueError('model parameters changed during inference')
    json_write(output/'restore-verification.json',restored)
    manifest['restore_verification_sha256']=sha(output/'restore-verification.json')
    manifest['source_hashes']={p:sha(ROOT/p) for p in ('model/encoder_export.py','numeric/encoder/contracts.py')}
    json_write(output/'manifest.json',manifest)
    json_write(output/'status.json',{'status':'PASS','sample_count':len(samples),'layers':12*len(samples),
                                   'parameters':162,'scalar_parameters':607308,
                                   'manifest_sha256':sha(output/'manifest.json'),'finished_unix':time.time()})

if __name__=='__main__':
    main()

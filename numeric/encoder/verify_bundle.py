"""Read back every binary/NPY/hex word and validate source and chain bindings."""
import argparse
import json
from pathlib import Path
import sys
import numpy as np

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from numeric.encoder.contracts import STAGES,layout,sha,json_write


def arrays_in(value):
    if isinstance(value,dict):
        if 'bits_sha256' in value:yield value
        for child in value.values():yield from arrays_in(child)
    elif isinstance(value,list):
        for child in value:yield from arrays_in(child)


def read_array(root,meta):
    for key,hashkey in [('npy','npy_sha256'),('hex','hex_sha256'),('bin','bits_sha256')]:
        path=(root/meta[key]).resolve()
        if root not in path.parents:raise ValueError('array path escapes output')
        if sha(path)!=meta[hashkey]:raise ValueError('array SHA mismatch '+str(path))
    array=np.load(str(root/meta['npy']),allow_pickle=False)
    if array.dtype!=np.dtype('float32') or list(array.shape)!=meta['shape'] or array.size!=meta['words']:
        raise ValueError('array shape/dtype/length mismatch')
    if not np.isfinite(array).all():raise ValueError('nonfinite array')
    raw=(root/meta['bin']).read_bytes()
    if raw!=np.ascontiguousarray(array,dtype='<f4').tobytes():raise ValueError('binary disagrees with NPY')
    lines=(root/meta['hex']).read_text(encoding='ascii').splitlines()
    if any(len(line)!=8 for line in lines):raise ValueError('hex word width')
    hexwords=np.array([int(v,16) for v in lines],dtype='<u4')
    if not np.array_equal(hexwords,array.reshape(-1).view('<u4')):raise ValueError('hex disagrees with NPY')
    return array


def verify(directory):
    directory=directory.resolve()
    manifest=json.loads((directory/'manifest.json').read_text(encoding='utf-8'))
    status=json.loads((directory/'status.json').read_text(encoding='utf-8'))
    if manifest['status']!='PASS' or status['status']!='PASS':raise ValueError('bundle not PASS')
    if status['manifest_sha256']!=sha(directory/'manifest.json'):raise ValueError('status binding stale')
    if manifest['stages']!=list(STAGES) or manifest['weight_layout']!=layout():raise ValueError('format mismatch')
    for relative,expected in manifest['source_hashes'].items():
        if sha(ROOT/relative)!=expected:raise ValueError('source binding stale '+relative)
    if not manifest['label_mapping_verified_against_official_flags']:raise ValueError('unchecked labels')
    if manifest['label_to_index']!={name:i for i,name in enumerate(manifest['labels'])}:raise ValueError('wrong label index')
    checked={};words=0
    for meta in arrays_in(manifest):
        if meta['bin'] not in checked:
            checked[meta['bin']]=read_array(directory,meta);words+=meta['words']
    if 'parameters' in manifest:
        if len(manifest['parameters'])!=162 or manifest['parameter_count']!=607308:raise ValueError('incomplete parameters')
        params={p['name']:checked[p['bin']] for p in manifest['parameters']}
        for index,weight in enumerate(manifest['weights']):
            pack=checked[weight['bin']]
            if pack.size!=49792:raise ValueError('pack length')
            for e in layout():
                got=pack[e['offset_words']:e['offset_words']+e['words']]
                want=params['layer_{:02d}/{}'.format(index,e['name'])].reshape(-1)
                if not np.array_equal(got.view(np.uint32),want.view(np.uint32)):raise ValueError('wrong packed order')
    for sample in manifest['samples']:
        if len(sample['layers'])!=12:raise ValueError('incomplete encoder chain')
        prior=checked[sample['input']['bin']]
        for index,layer in enumerate(sample['layers']):
            if index!=layer['layer_index'] or set(layer['stages'])!=set(STAGES):raise ValueError('layer/stage order')
            current=checked[layer['input']['bin']]
            if not np.array_equal(prior.view(np.uint32),current.view(np.uint32)):raise ValueError('broken actual layer boundary')
            prior=checked[layer['stages']['y']['bin']]
        if not np.array_equal(prior.view(np.uint32),checked[sample['final']['bin']].view(np.uint32)):
            raise ValueError('final differs from last layer')
    return {'status':'PASS','manifest_sha256':sha(directory/'manifest.json'),'arrays':len(checked),
            'words':words,'samples':len(manifest['samples']),'complete_layers':12*len(manifest['samples']),
            'all_hex_binary_npy_words_equal':True,'source_bindings_current':True,
            'layer_boundaries_bit_equal':True}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory',type=Path)
    parser.add_argument('--compare',type=Path)
    args=parser.parse_args()
    result=verify(args.directory)
    if args.compare:
        current=json.loads((args.directory/'manifest.json').read_text(encoding='utf-8'))
        previous=json.loads((args.compare/'manifest.json').read_text(encoding='utf-8'))
        old_arrays={x['bin']:x['bits_sha256'] for x in arrays_in(previous)}
        new_arrays={x['bin']:x['bits_sha256'] for x in arrays_in(current)}
        if old_arrays!=new_arrays:raise ValueError('independent repeat raw arrays differ')
        for relative,expected in old_arrays.items():
            if sha(args.compare/relative)!=expected:raise ValueError('prior repeat data changed')
        for field in ('source_hashes','design_sha256','labels','weight_layout'):
            if previous[field]!=current[field]:raise ValueError('repeat source/format differs: '+field)
        result['repeat']={'status':'PASS','prior_manifest_sha256':sha(args.compare/'manifest.json'),
                          'compared_arrays':len(new_arrays),'raw_bits_equal':True}
    json_write(args.directory/'readback-verification.json',result)
    print(json.dumps(result,sort_keys=True))

if __name__=='__main__':main()

"""Build explicit simulation lists selecting the isolated accelerator candidate."""
import json
from pathlib import Path
import shlex
from real_tools import sha


def prepare_overlay(root,bundle,base,extra,out):
    root=Path(root).resolve();bundle=Path(bundle).resolve();out=Path(out).resolve()
    original=(root/'accelerator/rtl').resolve()
    candidate=(bundle/'rtl').resolve()
    baseline=json.loads((bundle/'baseline-rtl-sha256.json').read_text(encoding='utf-8'))
    source_map={}
    candidate_hashes={}
    changes=[]
    for relative,want in baseline.items():
        suffix=Path(relative).suffix
        if suffix not in {'.v','.vh'}:continue
        old=root/'accelerator'/relative
        new=bundle/relative
        if not old.is_file() or sha(old)!=want:raise ValueError('Accelerator source differs from known baseline: '+str(old))
        removed={'rtl/kwt_accelerator.v','rtl/interface/kwt_icb.v','rtl/interface/kwt_icb_regs.v',
                 'rtl/interface/kwt_command_fifo.v','rtl/interface/kwt_result_access.v'}
        if relative in removed:
            source_map[old.resolve()]=None
            changes.append(relative)
        else:
            if not new.is_file():raise ValueError('Missing candidate source: '+str(new))
            candidate_hashes[relative]=sha(new)
            if sha(new)!=want:raise ValueError('Unexpected arithmetic/storage/control change: '+relative)
            if suffix=='.v':source_map[old.resolve()]=new.resolve()
    dma_sources=sorted((candidate/'dma').glob('*.v'))
    if len(dma_sources)!=6:raise ValueError('Expected six DMA modules')
    for path in dma_sources:
        relative=path.relative_to(bundle).as_posix()
        candidate_hashes[relative]=sha(path)
        changes.append(relative)
    used=[];tb_count=0;nested_hashes={}
    def redirect(path):
        resolved=path.resolve()
        if resolved in {(root/'rtl/e203/soc/kwt_shared_soc_top.v').resolve(),
                        (root/'rtl/e203/soc/kwt_soc_top.v').resolve()}:
            return None
        if resolved in source_map:
            used.append(resolved)
            return source_map[resolved]
        if resolved.is_relative_to(original):raise ValueError('Unlisted accelerator input: '+str(resolved))
        return resolved
    def include_path(token,cwd):
        path=(cwd/token).resolve()
        if path.is_relative_to(original):return candidate/path.relative_to(original)
        return path
    def expand(path,cwd,stack):
        nonlocal tb_count
        path=path.resolve()
        if path in stack:raise ValueError('Recursive filelist: '+str(path))
        nested_hashes[str(path)]=sha(path)
        result=[]
        for raw in path.read_text(encoding='utf-8').splitlines():
            line=raw.strip()
            if not line or line.startswith('//'):continue
            tokens=shlex.split(line,comments=True)
            i=0
            while i<len(tokens):
                token=tokens[i]
                if token.startswith('//'):break
                if '$' in token:raise ValueError('Expand environment variable explicitly in filelist: '+token)
                if token in {'-f','-F'}:
                    i+=1
                    if i==len(tokens):raise ValueError('Filelist option lacks path')
                    child=(cwd/tokens[i]).resolve()
                    result+=expand(child,child.parent if token=='-F' else cwd,stack+[path])
                elif token.startswith('+incdir+'):
                    result.append('+incdir+'+'+'.join(str(include_path(value,cwd)) for value in token[8:].split('+')))
                elif token.startswith('+'):
                    result.append(token)
                elif token in {'-v','-y'}:
                    i+=1
                    if i==len(tokens):raise ValueError('Library option lacks path')
                    resolved=(cwd/tokens[i]).resolve()
                    if resolved.is_relative_to(original):raise ValueError('Implicit accelerator library selection unsupported')
                    result.append(token+' '+str(resolved))
                elif token.startswith('-'):
                    raise ValueError('Unsupported filelist option: '+token)
                else:
                    resolved=(cwd/token).resolve()
                    if resolved==(root/'tb/tb_top.v').resolve():
                        tb_count+=1;result.append(str(out/'tb_real.v'))
                    else:
                        replacement=redirect(resolved)
                        if replacement is not None:result.append(str(replacement))
                i+=1
        return result
    base_lines=expand(Path(base),root,[])
    extra_lines=expand(Path(extra),root,[])
    if tb_count!=1:raise ValueError('Expected one original testbench')
    if len(used)!=len(source_map) or set(used)!=set(source_map):
        raise ValueError('Must select each of the 15 candidate RTL files exactly once')
    base_lines.extend(str(path) for path in dma_sources)
    return dict(base_lines=base_lines,extra_lines=extra_lines,candidate_rtl_sha256=candidate_hashes,
                changed_files=changes,original_filelist_sha256=nested_hashes,
                mapping={str(old):(str(new) if new is not None else None) for old,new in source_map.items()})

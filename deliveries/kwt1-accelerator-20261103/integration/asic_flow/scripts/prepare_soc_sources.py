#!/usr/bin/env python3
"""Build a reviewable ASIC source candidate from existing promoted DMA lists.

Read-only toward existing files. Creates a new uniquely named output directory.
Does not run synthesis, change RTL, choose PVT, or claim SRAM mapping is complete.
Python 3.6+; standard library only.
"""
import argparse
import datetime
import hashlib
import json
from pathlib import Path
import re
import shlex
import tempfile


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def build(root):
    root = Path(root).resolve()
    top = root / 'rtl/e203/soc/kwt_dma_soc_top.v'
    lists = [root / x for x in (
        'accelerator/platform/base-soc.f',
        'accelerator/platform/base-shared.f', 'accelerator/rtl/dma.f')]
    for p in lists + [top]:
        if not p.is_file():
            raise ValueError('Required file missing: ' + str(p))
    sources, incdirs, excluded, issues, directives = [], [], [], [], []
    list_hashes = {}

    def label(p):
        try:
            return p.relative_to(root).as_posix()
        except ValueError:
            return str(p)

    def note(reason, value):
        excluded.append({'reason': reason, 'path': str(value)})

    def source(p):
        p = p.resolve()
        rel = label(p)
        # Known simulation and obsolete top-level inputs only.
        if (rel.startswith(('tb/', 'verification/', 'accelerator/platform/'))
                or p.name.startswith('tb_')
                or p.name in {'kwt_real_soc_top.v', 'real_loader.v', 'timing_probe.v',
                              'profile_probe.v', 'suite_metrics.v', 'kwt_shared_soc_top.v',
                              'kwt_soc_top.v', 'e203_soc_top.v'}):
            note('simulation input or replaced SoC top', rel)
            return
        if root not in p.parents:
            # Do not silently synthesize commercial functional models.
            note('external source requires library/wrapper classification', str(p))
            issues.append('Review external input: ' + str(p))
            return
        if p.suffix.lower() not in {'.v', '.sv'}:
            note('not a Verilog compilation unit', rel)
            if p.suffix.lower() not in {'.vh', '.svh'}:
                issues.append('Unclassified source: ' + rel)
            return
        if not p.is_file():
            issues.append('Missing source: ' + rel)
            return
        if p not in sources:
            sources.append(p)

    def expand(path, cwd, stack):
        path = path.resolve()
        if path in stack:
            raise ValueError('Recursive filelist: ' + str(path))
        if not path.is_file():
            raise ValueError('Missing filelist: ' + str(path))
        list_hashes[label(path)] = sha(path)
        for number, raw in enumerate(path.read_text(errors='replace').splitlines(), 1):
            if not raw.strip() or raw.lstrip().startswith(('//', '#')):
                continue
            tokens = shlex.split(raw, comments=True)
            i = 0
            while i < len(tokens):
                token = tokens[i]
                if token.startswith('//'):
                    break
                if '$' in token:
                    raise ValueError('Unexpanded variable at %s:%d' % (path, number))
                if token in ('-f', '-F'):
                    i += 1
                    child = (cwd / tokens[i]).resolve()
                    expand(child, child.parent if token == '-F' else cwd, stack + [path])
                elif token.startswith('+incdir+'):
                    for name in token[8:].split('+'):
                        p = (cwd / name).resolve()
                        if p not in incdirs:
                            incdirs.append(p)
                elif token.startswith('+define+'):
                    directives.append(token)
                elif token.startswith(('+', '-')):
                    raise ValueError('Unsupported option %s at %s:%d; no list generated' % (token, path, number))
                else:
                    source(cwd / token)
                i += 1

    for p in lists:
        expand(p, root, [])
    source(top)
    # These include paths are explicit in the existing suite compile command.
    for rel in ['accelerator/rtl/include', 'rtl/e203/core', 'rtl/e203/perips',
                'rtl/e203/perips/apb_i2c']:
        p = root / rel
        if p not in incdirs:
            incdirs.append(p)
    for p in incdirs:
        if not p.is_dir():
            issues.append('Missing include directory: ' + label(p))
    modules, include_hashes, memory_review, conditionals = {}, {}, [], {}
    for p in sources:
        text = p.read_text(errors='replace')
        # Lexical inventory only, not a Verilog preprocessor or elaborator.
        clean = re.sub(r'/\*.*?\*/|//[^\n]*', '', text, flags=re.S)
        for name in re.findall(r'\bmodule\s+(?:automatic\s+)?([A-Za-z_$][\w$]*)', clean):
            modules.setdefault(name, []).append(label(p))
        flags = sorted(set(re.findall(r'`(?:ifdef|ifndef|elsif)\s+(\w+)', clean)))
        if flags:
            conditionals[label(p)] = flags
        if ('mem_wrap' in p.parts or 'sram' in p.name.lower()
                or 'tcm_ram' in p.name.lower() or 'storage_array' in p.name.lower()):
            memory_review.append({'path': label(p), 'sha256': sha(p), 'conditional_macros': flags,
                                 'memory_tokens': sorted(set(re.findall(r'\b(?:RAMSP\w*|sram_wrap\w*|sirv_sim_ram\w*)\b', clean)))})
    duplicates = {k: v for k, v in modules.items() if len(v) > 1}
    if duplicates:
        issues.append('Duplicate module declarations require preprocessing/elaboration review')
    if modules.get('kwt_dma_soc_top') != [label(top)]:
        issues.append('Production top declaration missing or ambiguous')
    # Recursively inspect literal includes without evaluating conditionals.
    visited = set()

    def includes(p):
        if p in visited:
            return
        visited.add(p)
        clean = re.sub(r'/\*.*?\*/|//[^\n]*', '', p.read_text(errors='replace'), flags=re.S)
        for name in re.findall(r'`include\s+"([^"]+)"', clean):
            candidates = [root / name, p.parent / name] + [d / name for d in incdirs]
            found = next((q.resolve() for q in candidates if q.is_file()), None)
            if found is None:
                issues.append('Unresolved literal include (may be conditional): %s in %s' % (name, label(p)))
            else:
                include_hashes[label(found)] = sha(found)
                includes(found)
    for p in sources:
        includes(p)
    out = Path(tempfile.mkdtemp(prefix='soc-sources-' + datetime.datetime.now().strftime('%Y%m%d-%H%M%S') + '-', dir=str(root)))
    lines = ['// CANDIDATE ONLY: ASIC elaboration and SRAM binding NOT verified.',
             '// Read from kwt-soc; top = kwt_dma_soc_top. No simulation defines copied.']
    lines += ['+incdir+' + label(p) for p in incdirs]
    lines += [label(p) for p in sources]
    (out / 'sources.f').write_text('\n'.join(lines) + '\n')
    report = {'status': 'CANDIDATE_REQUIRES_ASIC_ELABORATION_AND_SRAM_BINDING',
              'server_root': str(root), 'top': 'kwt_dma_soc_top',
              'source_count': len(sources), 'include_directory_count': len(incdirs),
              'input_lists_sha256': list_hashes, 'sources_sha256': {label(p): sha(p) for p in sources},
              'headers_sha256': include_hashes, 'excluded': excluded,
              'simulation_defines_not_applied': sorted(set(directives + ['+define+FPGA+ARM_UD_MODEL'])),
              'issues': sorted(set(issues)), 'duplicate_modules_lexical': duplicates,
              'conditional_macros_lexical': conditionals, 'memory_review': memory_review,
              'limitations': ['Not a hierarchy elaborator; conditional inactive modules may be included.',
                              'No synthesis, library mapping, STA or functional simulation run.',
                              'Do not suppress unresolved references or claim SRAM power is zero.']}
    (out / 'source-audit.json').write_text(json.dumps(report, indent=2) + '\n')
    (out / 'README.txt').write_text(
        'Top: kwt_dma_soc_top\nRun source reading from: ' + str(root) + '\n'
        'sources.f is a candidate, NOT a synthesis pass. Use your tool to parse +incdir+ and file paths.\n'
        'Do not pass this VCS-style list directly as a Tcl source script.\n'
        'Review source-audit.json exclusions, issues, conditionals and memory wrappers.\n'
        'Supply ASIC defines/parameters, standard-cell/SRAM libraries and SDC separately.\n'
        'E203 ITCM/DTCM wrappers require explicit macro binding review.\n'
        'Production RTL and prior reports were not changed.\n')
    print('OUTPUT=' + str(out))
    print('TOP=kwt_dma_soc_top SOURCES=%d INCDIRS=%d' % (len(sources), len(incdirs)))
    print('EXCLUDED=%d ISSUES=%d DUPLICATE_MODULES=%d' % (len(excluded), len(report['issues']), len(duplicates)))
    print('STATUS=' + report['status'])
    for item in report['issues'][:6]:
        print('REVIEW=' + item)
    print('MEMORY_FILES=%d; details in source-audit.json' % len(memory_review))
    return out, report


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', default='.', help='Existing promoted kwt-soc directory')
    args = parser.parse_args()
    try:
        build(args.root)
    except (ValueError, OSError, IndexError) as exc:
        parser.exit(1, 'STOP: %s\n' % exc)

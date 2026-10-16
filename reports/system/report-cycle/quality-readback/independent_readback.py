"""Round 2 independent, read-only evidence audit; only writes its owned directory."""
from pathlib import Path
import csv
import hashlib
import json
import math
import re
import struct
import sys
import xml.etree.ElementTree as ET
from datetime import datetime, timezone

import numpy as np

ROOT = Path(__file__).resolve().parents[4]
OUT = Path(__file__).resolve().parent
hash_cache = {}
checks = {}
bound_count = 0


def require(condition, message):
    if not condition:
        raise AssertionError(message)


def read_json(path):
    return json.loads((ROOT / path).read_text(encoding="utf-8-sig"))


def sha(path):
    p = ROOT / path
    key = str(p)
    if key not in hash_cache:
        hash_cache[key] = hashlib.file_digest(p.open("rb"), "sha256").hexdigest()
    return hash_cache[key]


def bound(mapping):
    global bound_count
    for path, expected in mapping.items():
        require(sha(path) == expected, "hash mismatch: " + path)
        bound_count += 1
    return len(mapping)


def words(path):
    lines = (ROOT / path).read_text(encoding="ascii").splitlines()
    require(all(re.fullmatch(r"[0-9a-fA-F]{8}", v) for v in lines), "word format: " + str(path))
    values = np.array([int(v, 16) for v in lines], dtype="<u4")
    require(np.isfinite(values.view("<f4")).all(), "nonfinite: " + str(path))
    return values


def same_words(actual, expected, label):
    require(actual.shape == expected.shape and np.array_equal(actual, expected), label)
    return int(actual.size)


accept = read_json("reports/system/root-formal-acceptance.json")
require(accept["status"] == "ACCEPTED_LOCAL_DRAFT", "hardware acceptance")
checks["root_evidence_bindings"] = bound(accept["evidence_sha256"])
checks["root_review_input_bindings"] = bound(accept["review_inputs_sha256"])
freeze = read_json("work/encoder_source_freeze.json")
checks["production_source_bindings"] = bound(freeze["source_sha256"])
require(checks["production_source_bindings"] == 192, "freeze count")
checks["freeze_sha256"] = sha("work/encoder_source_freeze.json")
snapshot = read_json("reports/system/formal-baseline/runner-state.json")
require(snapshot["exit_code"] == 0 and snapshot["ended_at"], "stable runner exit")
checks["stable_hardware_runner"] = {k: snapshot[k] for k in ["run_id", "round", "exit_code", "ended_at"]}

# Recheck every reference array independently: bytes, NPY, hex and chain.
references = {}
for bundle in ["reference", "reference-test12"]:
    base = Path("reports/encoder") / bundle
    manifest = read_json(base / "manifest.json")
    bound(manifest["source_hashes"])
    seen = {}

    def walk(obj):
        if isinstance(obj, dict):
            if "bits_sha256" in obj and "bin" in obj:
                yield obj
            for value in obj.values():
                yield from walk(value)
        elif isinstance(obj, list):
            for value in obj:
                yield from walk(value)

    array_words = 0
    for meta in walk(manifest):
        if meta["bin"] in seen:
            continue
        for filekey, digestkey in [("bin", "bits_sha256"), ("npy", "npy_sha256"), ("hex", "hex_sha256")]:
            require(sha(base / meta[filekey]) == meta[digestkey], "reference array hash")
        raw = (ROOT / base / meta["bin"]).read_bytes()
        npy = np.load(ROOT / base / meta["npy"], allow_pickle=False)
        require(npy.dtype == np.dtype("float32") and list(npy.shape) == meta["shape"], "reference shape/dtype")
        require(npy.size == meta["words"] and np.isfinite(npy).all(), "reference finite/count")
        require(raw == np.ascontiguousarray(npy, dtype="<f4").tobytes(), "NPY/binary mismatch")
        w = words(base / meta["hex"])
        same_words(w, np.frombuffer(raw, dtype="<u4"), "hex/binary mismatch")
        seen[meta["bin"]] = w
        array_words += w.size
    for sample in manifest["samples"]:
        previous = seen[sample["input"]["bin"]]
        for layer in sample["layers"]:
            same_words(previous, seen[layer["input"]["bin"]], "broken layer chain")
            previous = seen[layer["stages"]["y"]["bin"]]
        same_words(previous, seen[sample["final"]["bin"]], "final chain")
    references[bundle] = manifest
    checks[bundle] = {"arrays": len(seen), "words": int(array_words),
                      "samples": len(manifest["samples"]), "layers": len(manifest["samples"]) * 12,
                      "max_final_nrmse": max(s["final_comparison"]["nrmse"] for s in manifest["samples"]),
                      "same_prediction_count": sum(s["same_prediction_as_official"] for s in manifest["samples"])}

cases = list(csv.DictReader((ROOT / "reports/encoder/verification/rtl-case-results.csv").open(encoding="utf-8")))
layers = list(csv.DictReader((ROOT / "reports/encoder/verification/rtl-layer-results.csv").open(encoding="utf-8")))
require(len(cases) == 15 and len(layers) == 180, "CSV coverage")
rtl_words = 0
rtl_bindings = 0
for row in cases:
    layer_rows = [l for l in layers if (l["reference"], l["case"]) == (row["reference"], row["case"])]
    require(len(layer_rows) == 12 and [int(l["layer"]) for l in layer_rows] == list(range(12)), "CSV layer order")
    status_path = Path(layer_rows[0]["status_record"])
    out = status_path.parent
    status = read_json(status_path)
    require(status["status"] == "PASS" and status["exit_code"] == 0, "RTL exit")
    require(sha(status_path) == row["status_sha256"], "CSV status binding")
    for key in ["source_sha256", "input_sha256", "compiled_source_sha256"]:
        rtl_bindings += bound(status[key])
    for key, rel in [("output_sha256", "output.hex"), ("log_sha256", "simulation.log"),
                     ("binary_sha256", "obj/Vtb_encoder"), ("compile_log_sha256", "compile.log"), ("build_key_sha256", "build.json")]:
        require(sha(out / rel) == status[key], "RTL artifact " + key)
    actual = words(out / "output.hex")
    refbase = Path("reports/encoder") / row["reference"] / "cases" / row["case"]
    expected = np.concatenate([words(refbase / f"layer_{l:02d}/y.hex") for l in range(12)])
    rtl_words += same_words(actual, expected, "RTL all output mismatch")
    log = (ROOT / out / "simulation.log").read_text(encoding="utf-8")
    records = re.findall(r"ENCODER_LAYER_PASS layer=(\d+) words=(\d+) cycles=(\d+) flags=(\w+)", log)
    require(len(records) == 12, "raw RTL log layers")
    for record, layer_row in zip(records, layer_rows):
        require(record == (layer_row["layer"], layer_row["words"], layer_row["compute_cycles"], layer_row["flags_hex"]), "raw log versus CSV")
    require(sum(int(l["compute_cycles"]) for l in layer_rows) == int(row["compute_cycles"]), "CSV layer cycle sum")
checks["rtl"] = {"unique_inputs": len(cases), "layers": len(layers), "output_words": rtl_words,
                  "source_input_compile_bindings": rtl_bindings,
                  "compute_cycles_total": sum(int(c["compute_cycles"]) for c in cases),
                  "compute_cycles_min": min(int(c["compute_cycles"]) for c in cases),
                  "compute_cycles_max": max(int(c["compute_cycles"]) for c in cases)}

# The independent repeat must be a distinct actual process, with identical outputs.
first = read_json("reports/encoder/rtl/full/original-0/status.json")
repeat = read_json("reports/encoder/rtl/repeat/status.json")
require(first["pid"] != repeat["pid"] and first["started_unix"] != repeat["started_unix"], "repeat process")
require(repeat["status"] == "PASS" and repeat["exit_code"] == 0, "repeat status")
for key in ["source_sha256", "input_sha256", "compiled_source_sha256"]:
    bound(repeat[key])
checks["repeat_words"] = same_words(words("reports/encoder/rtl/full/original-0/output.hex"),
                                    words("reports/encoder/rtl/repeat/output.hex"), "repeat output")

# Trace: all layer/stage/address identities, not only a text digest.
stage_names = references["reference"]["stages"]
sample = references["reference"]["samples"][0]
stage_arrays = {(l, s): words(Path("reports/encoder/reference") / sample["layers"][l]["stages"][name]["hex"])
                for l in range(12) for s, name in enumerate(stage_names)}
stage_seen = {key: bytearray(len(a)) for key, a in stage_arrays.items()}
trace_path = "reports/encoder/rtl/full/original-0/trace.txt"
trace_count = 0
with (ROOT / trace_path).open(encoding="ascii") as stream:
    for line in stream:
        l, s, a, v = line.split()
        key = (int(l), int(s)); address = int(a)
        require(key in stage_arrays and 0 <= address < len(stage_arrays[key]), "trace identity")
        require(not stage_seen[key][address] and int(v, 16) == int(stage_arrays[key][address]), "trace value/duplicate")
        stage_seen[key][address] = 1
        trace_count += 1
require(all(all(x) for x in stage_seen.values()), "missing trace")
require(sha(trace_path) == first["trace_sha256"], "trace hash")
checks["trace_words"] = trace_count

attention_base = Path("reports/encoder/rtl/attention-full")
attention_status = read_json(attention_base/"status.json")
require(attention_status["attention"] is True and attention_status["status"]=="PASS" and attention_status["exit_code"]==0,"attention actual run")
for key in ["source_sha256","compiled_source_sha256","input_sha256"]:
    bound(attention_status[key])
for key,rel in [("output_sha256","output.hex"),("trace_sha256","trace.txt"),("log_sha256","simulation.log"),("binary_sha256","obj/Vtb_encoder")]:
    require(sha(attention_base/rel)==attention_status[key],"attention artifact")
attention_words=same_words(words(attention_base/"output.hex"),stage_arrays[(0,6)],"attention public output")
attention_seen={s:bytearray(len(stage_arrays[(0,s)])) for s in range(7)}
attention_trace_words=0
with (ROOT/attention_base/"trace.txt").open(encoding="ascii") as stream:
    for line in stream:
        l,s,a,v=line.split();s=int(s);a=int(a)
        require(int(l)==0 and s in attention_seen and 0<=a<len(attention_seen[s]),"attention trace identity")
        require(not attention_seen[s][a] and int(v,16)==int(stage_arrays[(0,s)][a]),"attention trace compare")
        attention_seen[s][a]=1;attention_trace_words+=1
require(all(all(v) for v in attention_seen.values()),"attention trace completeness")
checks["attention"]={"public_words":attention_words,"trace_words":attention_trace_words,"output_sha256":sha(attention_base/"output.hex")}

perf = read_json("reports/encoder/verification/performance.json")
require(perf["source_sha256"] == sha("scripts/encoder_report.py"), "performance generator binding")
cpu = {}
for policy, name in [(1, "pingpong"), (2, "reload")]:
    base = Path("reports/encoder/system") / name
    status = read_json(base / "status.json")
    require(status["status"] == "PASS" and status["exit_code"] == 0, "CPU exit")
    maps = {k: bound(status[k]) for k in ["source_sha256", "input_sha256", "compiled_source_sha256"]}
    for key, rel in [("firmware_sha256", "firmware.elf"), ("binary_sha256", "obj/Vtb_e203_encoder"),
                     ("compile_log_sha256", "compile.log"), ("build_key_sha256", "build.json"),
                     ("output_sha256", "cpu-output.hex"), ("log_sha256", "simulation.log"), ("neural_sha256", "neural-output.hex")]:
        require(sha(base / rel) == status[key], "CPU artifact " + key)
    require(perf["policies"][name]["status_sha256"] == sha(base / "status.json"), "perf status")
    require(perf["policies"][name]["log_sha256"] == sha(base / "simulation.log"), "perf log")
    expected = np.concatenate([words(Path("reports/encoder/reference") / sample["layers"][l]["stages"]["y"]["hex"]) for l in range(12)])
    neural_count = same_words(words(base / "neural-output.hex"), expected, "CPU neural")
    cpu_count = same_words(words(base / "cpu-output.hex"), expected[-6336:] if policy == 1 else expected, "CPU writeback")
    same_words(words(base / "expected.hex"), expected, "actual consumed expected")
    same_words(words(base / "input.hex"), words("reports/encoder/reference/cases/eight_750e3e75_nohash_0/input.hex"), "actual input")
    # Rebuild objcopy-equivalent image from allocatable non-NOBITS ELF sections.
    elf = (ROOT / base / "firmware.elf").read_bytes()
    require(elf[:6] == b"\x7fELF\x01\x01", "ELF32 little endian")
    shoff = struct.unpack_from("<I", elf, 32)[0]
    shsize, shcount = struct.unpack_from("<HH", elf, 46)
    sections = []
    for i in range(shcount):
        _, kind, flags, addr, off, size, _, _, _, _ = struct.unpack_from("<10I", elf, shoff + i * shsize)
        if flags & 2 and kind != 8 and size:
            sections.append((addr, elf[off:off + size]))
    origin = min(a for a, _ in sections)
    rebuilt = bytearray(max(a + len(b) for a, b in sections) - origin)
    for addr, data in sections:
        rebuilt[addr-origin:addr-origin+len(data)] = data
    payload = (ROOT / base / "firmware.bin").read_bytes()
    require(rebuilt == payload and bytes.fromhex((ROOT / base / "firmware.hex").read_text()) == payload, "ELF/bin/hex")
    require(len(payload) == 1512 and status["command"][-2:] == ["+BYTES=1512", f"+POLICY={policy}"], "firmware command")
    commands = [json.loads(x) for x in (ROOT / base / "commands.jsonl").read_text(encoding="utf-8").splitlines()]
    matching = [c for c in commands if c["command"] == status["command"] and status["started_unix"] <= c["time"] <= status["completed_unix"]]
    require(len(matching) == 1, "actual command timestamp binding")
    require(any(f"-DENCODER_POLICY={policy}" in c["command"] and status["started_unix"] <= c["time"] <= status["completed_unix"] for c in commands), "firmware policy compilation")
    log = (ROOT / base / "simulation.log").read_text(encoding="utf-8")
    summary_line = next(l for l in log.splitlines() if l.startswith("E203_ENCODER_PASS "))
    require(summary_line == status["summary"], "summary log identity")
    values = {k: int(v) for k, v in re.findall(r"(\w+)=(\d+)", summary_line)}
    inclusive = values["final_write_cycle"] - values["begin_cycle"] + 1
    require(inclusive == values["end_to_end_cycles"], "inclusive cycles")
    loads = [tuple(map(int, x)) for x in re.findall(r"HOST_LAYER_LOAD layer=(\d+) words=(\d+) begin=(\d+) end=(\d+) cycles=(\d+)", log)]
    starts = dict((int(l), int(c)) for l, c in re.findall(r"CPU_ENCODER_START layer=(\d+) cycle=(\d+)", log))
    require(len(loads) == len(starts) == 12 and [l[0] for l in loads] == list(range(12)), "load/start coverage")
    decoded_layers = []
    for l, count, begin, end, duration in loads:
        require(count == end-begin == duration == 49792, "host load duration")
        decoded_layers.append({"layer": l, "host_load_cycles": duration,
                               "parameter_ready_to_start_cycles": starts[l]-end,
                               "start_to_next_request_or_final_write_cycles":
                                   (loads[l+1][2] if l < 11 else values["final_write_cycle"]+1) - starts[l]})
    initial = loads[0][2] - values["begin_cycle"]
    segments = [initial] + [sum(l[k] for l in decoded_layers) for k in ["host_load_cycles", "parameter_ready_to_start_cycles", "start_to_next_request_or_final_write_cycles"]]
    require(sum(segments) == inclusive and decoded_layers == perf["policies"][name]["layers"], "four segment/per-layer recompute")
    shared = values["shared_reads"] + values["shared_writes"]
    model_shared = shared + values["host_words"] + 12 + 12
    cpu[name] = {"policy": policy, "source_bindings": maps, "neural_words": neural_count,
                 "cpu_writeback_words": cpu_count, "firmware_bytes": len(payload), "elf_bin_hex_equal": True,
                 "summary": values, "four_segments": segments, "cpu_shared_transactions": shared,
                 "model_shared_transactions": model_shared, "layers": decoded_layers,
                 "time_at_assumed_150mhz_seconds": inclusive / 150e6,
                 "throughput_at_assumed_150mhz": 150e6 / inclusive}
checks["cpu"] = cpu
metric_values = {
    "cpu_shared_reads": [cpu[x]["summary"]["shared_reads"] for x in cpu],
    "cpu_shared_writes": [cpu[x]["summary"]["shared_writes"] for x in cpu],
    "cpu_shared_transactions": [cpu[x]["cpu_shared_transactions"] for x in cpu],
    "cpu_shared_word_bytes": [cpu[x]["cpu_shared_transactions"]*4 for x in cpu],
    "host_parameter_writes": [cpu[x]["summary"]["host_words"] for x in cpu],
    "host_ready_writes": [12,12], "host_request_reads": [12,12],
    "model_shared_transactions": [cpu[x]["model_shared_transactions"] for x in cpu],
    "model_shared_word_bytes": [cpu[x]["model_shared_transactions"]*4 for x in cpu],
    "end_to_end_cycles": [cpu[x]["summary"]["end_to_end_cycles"] for x in cpu]}
for key, (ping, reload) in metric_values.items():
    row = perf["comparison"][key]
    require([ping, reload, reload-ping] == [row["pingpong"], row["reload"], row["saved"]], "performance value " + key)
    require(math.isclose((reload-ping)/reload, row["saved_fraction_of_reload"], abs_tol=1e-14), "performance fraction")
checks["performance_comparisons_recomputed"] = len(metric_values)
checks["layer_savings"] = [r["start_to_next_request_or_final_write_cycles"]-p["start_to_next_request_or_final_write_cycles"] for p,r in zip(cpu["pingpong"]["layers"],cpu["reload"]["layers"])]

# Recompute C-versus-official errors from actual frozen binary tensors.
all_input_hashes = []
for bundle, exported in [("reference", "export"), ("reference-test12", "export-test12")]:
    export_base = Path("reports/encoder")/exported
    export = read_json(export_base/"manifest.json")
    reference = references[bundle]
    require(sha(export_base/"manifest.json") == reference["export_manifest_sha256"], "official export binding")
    official_by_id = {s["sample_id"]:s for s in export["samples"]}
    recomputed = []
    for sample in reference["samples"]:
        all_input_hashes.append(sample["input"]["bits_sha256"])
        official = official_by_id[sample["sample_id"]]
        a_meta, b_meta = sample["final"], official["final"]
        require(sha(export_base/b_meta["bin"]) == b_meta["bits_sha256"], "official final binding")
        a = np.frombuffer((ROOT/"reports/encoder"/bundle/a_meta["bin"]).read_bytes(),dtype="<f4").astype(np.float64)
        b = np.frombuffer((ROOT/export_base/b_meta["bin"]).read_bytes(),dtype="<f4").astype(np.float64)
        rmse = float(np.sqrt(np.mean((a-b)**2)))
        nrmse = rmse/max(float(np.sqrt(np.mean(b*b))),1e-8)
        require(math.isclose(nrmse,sample["final_comparison"]["nrmse"],rel_tol=1e-12), "recomputed final NRMSE")
        recomputed.append(nrmse)
    checks[bundle]["max_final_nrmse_recomputed_from_binary"] = max(recomputed)
require(len(set(all_input_hashes)) == len(all_input_hashes) == 15, "distinct actual encoder inputs")
checks["actual_distinct_input_hashes"] = len(set(all_input_hashes))

# Integer reports: all full-matrix Y/flags, actual counts and aggregate errors.
prototype = read_json("reports/prototype/ffn1/full/status.json")
vectors = read_json("reports/prototype/vectors/manifest.json")
bound(prototype["fingerprints"])
v_by_id = {v["case_id"]:v for v in vectors["cases"]}
integer_words = 0
integer_macs = 0
cycles = {k:0 for k in ["load","compute","row_wait","readback"]}
layer_energies = {}
case_errors = []
for case in prototype["cases"]:
    vector = v_by_id[case["case_id"]]
    actual_path = Path(case["file"])
    require(sha(actual_path) == case["file_sha256"], "integer output binding")
    actual = [int(line,16) for line in (ROOT/actual_path).read_text(encoding="ascii").splitlines()]
    arrays = {}
    for name,meta in vector["arrays"].items():
        p=Path("reports/prototype/vectors")/meta["path"]
        require(sha(p) == meta["sha256"], "integer array hash")
        arrays[name]=np.load(ROOT/p,allow_pickle=False)
    y = arrays["Yq"].reshape(-1)
    overflow = arrays["overflow"].reshape(-1)
    saturated = arrays["output_saturated"].reshape(-1)
    expected = [(int(v)&0xffffffff)|(int(o)<<32)|(int(s)<<33) for v,o,s in zip(y,overflow,saturated)]
    require(actual == expected and len(actual) == case["outputs"] == 25344, "integer Y/flag mismatch")
    require(case["macs"] == 64*len(actual), "integer MAC count")
    integer_words += len(actual); integer_macs += case["macs"]
    for k in cycles:cycles[k]+=case["cycles"][k]
    source = vector["source_arrays"]["Y"]
    p = Path("reports/model/baseline")/source["path"]
    require(sha(p)==source["sha256"],"integer official Y binding")
    official = np.load(ROOT/p,allow_pickle=False).astype(np.float64).reshape(-1)
    decoded = y.astype(np.float64)*vector["config"]["output_scale"]
    sse=float(np.sum((decoded-official)**2)); energy=float(np.sum(official**2))
    nrmse=math.sqrt(sse/len(y))/max(math.sqrt(energy/len(y)),1e-8)
    require(math.isclose(nrmse,vector["metrics"]["nrmse"],rel_tol=1e-12),"integer NRMSE")
    case_errors.append(nrmse)
    l=case["layer"]
    old=layer_energies.get(l,(0.0,0.0,0))
    layer_energies[l]=(old[0]+sse,old[1]+energy,old[2]+len(y))
max_layer=max(math.sqrt(s/n)/max(math.sqrt(e/n),1e-8) for s,e,n in layer_energies.values())
require(math.isclose(max(case_errors),vectors["summary"]["max_case_nrmse"],rel_tol=1e-12),"max integer case NRMSE")
require(math.isclose(max_layer,vectors["summary"]["max_layer_nrmse"],rel_tol=1e-12),"max integer layer NRMSE")
checks["integer_ffn1"]={"cases":len(prototype["cases"]),"words_and_flags":integer_words,"actual_macs":integer_macs,
                         "cycle_categories":cycles,"max_case_nrmse_recomputed":max(case_errors),"max_layer_nrmse_recomputed":max_layer}
checks["xml_counts"]={}
for name,path in [("numeric","reports/prototype/integration-numeric.xml"),("gate","reports/prototype/integration-gate.xml"),("dot64","reports/prototype/dot64/results.xml")]:
    tree=ET.parse(ROOT/path)
    tests=list(tree.iter("testcase"))
    failures=sum(len(t.findall("failure"))+len(t.findall("error")) for t in tests)
    skips=sum(len(t.findall("skipped")) for t in tests)
    require(failures==0 and skips==0,"XML failure/skip")
    checks["xml_counts"][name]={"tests":len(tests),"failures":failures,"skipped":skips}
ffn_cpu=read_json("reports/system/e203-ffn1/result.json")
bound(ffn_cpu["input_sha256"])
for rel,digest in ffn_cpu["artifacts"].items():
    require(sha(Path("reports/system/e203-ffn1")/rel)==digest,"FFN1 CPU artifact")
for mode in ["full","repeat"]:
    metrics=ffn_cpu["results"][mode]["metrics"]
    require(metrics["outputs"]==metrics["flags"]==25344 and metrics["cycles"]==8595787,"FFN1 CPU coverage")
checks["integer_cpu"]={"full":ffn_cpu["results"]["full"]["metrics"],"repeat":ffn_cpu["results"]["repeat"]["metrics"],"artifact_bindings":len(ffn_cpu["artifacts"])}
case0=vectors["cases"][0]
y0=np.load(ROOT/"reports/prototype/vectors"/case0["arrays"]["Yq"]["path"],allow_pickle=False).reshape(-1)
o0=np.load(ROOT/"reports/prototype/vectors"/case0["arrays"]["overflow"]["path"],allow_pickle=False).reshape(-1)
s0=np.load(ROOT/"reports/prototype/vectors"/case0["arrays"]["output_saturated"]["path"],allow_pickle=False).reshape(-1)
for mode in ["full-verilator","repeat-verilator"]:
    for name,want in [("cpu-output.txt",[(int(v)&0xffffffff) for v in y0]),("cpu-flags.txt",[(4|int(o)|(int(s)<<1)) for o,s in zip(o0,s0)])]:
        records=[line.split() for line in (ROOT/"reports/system/e203-ffn1"/mode/name).read_text(encoding="ascii").splitlines()]
        require([int(i) for i,_ in records]==list(range(25344)),"integer CPU index order")
        require([int(v,16) for _,v in records]==want,"integer CPU word/flags")
checks["integer_cpu"]["independent_word_and_flags_comparisons"]=2*25344

# Hand-derived examples checked independently with standard arithmetic.
dot=sum(x*w for x,w in zip([1,-2,3],[2,4,-1]))+1
probability0=1/(1+2*math.exp(-0.125))
ln_inv=1/math.sqrt(0.75+1e-6)
require(dot==-8 and round(-5/2)==-2,"integer teaching examples")
require(abs(probability0-0.361664)<1e-6,"attention teaching example")
require(abs(-0.5*ln_inv-(-0.57734988))<1e-8,"LN teaching example")
checks["didactic_arithmetic"]={"dot":dot,"rne_negative_half":round(-5/2),"attention_probability0":probability0,
                               "ln_inverse_std":ln_inv,"ln_first_component":-0.5*ln_inv,
                               "weight_address_2_7":16576+2*256+7,
                               "int_ffn_ram_bytes":(6336*16+16384*16+256*48+256*34)//8,
                               "encoder_bulk_bytes":(49792+4*6336)*4,
                               "row_scratch_bytes":(4*64+2*99+256)*4}

# Generic network connectivity, independent of the status text.
for label, directory, top in [("encoder_generic", "reports/encoder/synthesis", "encoder_icb"),
                               ("soc_generic", "reports/encoder/synthesis/soc", "e203_encoder_soc")]:
    base = Path(directory)
    status = read_json(base / "status.json")
    bound(status["source_sha256"])
    require(sha(base / "design.json") == status["design_sha256"], "generic design")
    design = read_json(base / "design.json")
    modules = design["modules"]
    pending = [top]; reached = set()
    while pending:
        current = pending.pop()
        if current in reached:
            continue
        reached.add(current)
        pending.extend(c["type"] for c in modules[current].get("cells",{}).values() if c["type"] in modules)
    checks[label] = {"definitions":len(modules), "reachable":len(reached), "design_sha256":sha(base / "design.json")}
    if label == "soc_generic":
        cells = modules[top]["cells"]
        require(all(name in cells and cells[name]["type"] in modules for name in ["cpu","ram","encoder","ffn1"]), "SoC connections")
        checks[label]["connections"] = {n:cells[n]["type"] for n in ["cpu","ram","encoder","ffn1"]}

# Document bytes and links; semantic judgments are separately recorded by reviewer.
documents = {}
local_links = 0
output_examples = 0
for p in sorted((ROOT / "docs/encoder/reports").glob("*.md")):
    text = p.read_text(encoding="utf-8")
    require("\ufffd" not in text, "UTF8 replacement in report")
    documents[str(p.relative_to(ROOT)).replace("\\", "/")] = sha(p)
    for target in re.findall(r"(?<!!)\[[^\]]*\]\(([^)]+)\)", text):
        if "://" in target or target.startswith("#"):
            continue
        from urllib.parse import unquote
        require((p.parent/unquote(target.split("#")[0])).exists(), "missing local link " + target)
        local_links += 1
    for target in re.findall(r"--output\s+([^\s`]+)", text):
        resolved = (ROOT/target).resolve()
        require((ROOT/"reports/encoder").resolve() in resolved.parents, "runner output guard " + target)
        output_examples += 1
checks["documents"] = documents
checks["local_links_checked"] = local_links
checks["encoder_output_examples_guard_checked"] = output_examples
checks["all_hash_bindings_checked"] = bound_count
checks["unique_files_hashed"] = len(hash_cache)
inputs_manifest={str(Path(path).relative_to(ROOT)).replace("\\","/"):digest for path,digest in hash_cache.items()}
(OUT/"evidence-inputs.json").write_text(json.dumps(inputs_manifest,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
checks["evidence_inputs_manifest_sha256"]=sha(OUT/"evidence-inputs.json")
checks["completed_utc"] = datetime.now(timezone.utc).isoformat()
checks["status"] = "PASS"
checks["no_hardware_commands_run"] = True
(OUT/"evidence.json").write_text(json.dumps(checks,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps({k:v for k,v in checks.items() if k not in ["cpu", "documents"]},ensure_ascii=False,indent=2))

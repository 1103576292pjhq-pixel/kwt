"""Evidence-backed D0 self-review; this does not grant parent acceptance."""
from datetime import datetime, timezone
import json
from pathlib import Path
import sys
import uuid

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from dv.revd.d0_run import identity, read, sha, write


def main():
    result = read(ROOT / "work/revd/d0_result.json")
    out = ROOT / "reports/revd/d0/self_review" / (
        datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ") + "_" + uuid.uuid4().hex[:8])
    out.mkdir(parents=True, exist_ok=False)
    run = ROOT / result["run_dir"]
    vectors = result["retained_vectors"]
    scalar_path = ROOT / vectors["scalar_vectors"]
    scalars = [json.loads(line) for line in scalar_path.read_text(encoding="utf-8").splitlines()]
    inputs = read(ROOT / result["validated_inputs"])
    compare = read(run / "compare_v0/compare_v0.json")
    negative = read(run / "artifact_negatives/result.json")
    unit_log = (run / "input_unit_tests.stderr.log").read_text(encoding="utf-8")
    final_identity = identity()
    rounds = [
        {"name": "SPEC_NUMERIC_INPUTS", "checks": {
            "pinned_blob": compare["git_blob"] == final_identity["golden_git_blob"],
            "actual_full_compare_count": compare["vectors"] == 768 and compare["full_matrix_outputs"] == 25344,
            "scalar_inputs_retained": len(scalars) == 768 and {x["shift"] for x in scalars} == set(range(48)),
            "all_matrix_results_retained": set(vectors["full_matrix"]) == {"X", "W", "b", "raw48", "Y", "overflow", "saturated"},
            "full_api_validation": inputs["verification_api"] == "numeric.artifacts.verify_vectors" and inputs["verification_result"]["case_count"] == 36 and inputs["verification_result"]["array_count"] == 288,
            "all_W_bias_repacked": inputs["weights_checked"] == 36 * 16384 and inputs["biases_checked"] == 36 * 256,
            "same_layer_parameter_identities": len(inputs["layer_identities"]) == 12 and all(len(x["cases"]) == 3 for x in inputs["layer_identities"].values()),
            "priority_source_pages": result["contracts"]["priority_physical_pages"] == [4, 8, 11, 12, 13, 14],
        }},
        {"name": "QUALITY_PROVENANCE_ACCEPTANCE", "checks": {
            "all_actual_commands_zero": bool(result["commands"]) and all(x["exit_code"] == 0 for x in result["commands"]),
            "unit_tests_real_green": "Ran 7 tests" in unit_log and "OK" in unit_log and "FAILED" not in unit_log,
            "six_software_input_negatives_detected": len(negative["cases"]) == 6 and all(x["detected"] for x in negative["cases"]),
            "artifact_hashes_current": all(sha(ROOT / name) == expected for name, expected in result["artifacts_sha256"].items()),
            "execution_source_hashes_current": all(sha(ROOT / name) == expected for name, expected in result["execution_sources"].items()),
            "old_source_identity_checked_at_exit": final_identity["protected_count"] == 192 and final_identity["tracked_inventory_count"] == 12313 and final_identity["snapshot_file_count"] == 58,
            "no_official_acceptance_claim": result["contracts"]["official_contest_acceptance"] is False,
            "scope_limitations_explicit": all(x.get("status") == "NOT_RUN" for x in result["contracts"]["source_test_mapping"] if x["id"] in {"TASK3_SOC", "OFFICIAL_NUMERICAL", "OFFICIAL_PERFORMANCE", "STA150", "AREA", "POWER_ENERGY"}),
        }},
    ]
    passed = all(all(round_["checks"].values()) for round_ in rounds)
    review = {"status": "PASS" if passed else "FAIL", "scope": "D0_SELF_REVIEW_ONLY",
              "run_manifest": str((run / "run_manifest.json").relative_to(ROOT).as_posix()),
              "run_manifest_sha256": sha(run / "run_manifest.json"), "rounds": rounds,
              "parent_accepted": False, "official_contest_acceptance": False,
              "known_scope_side_effect": "Two Python bytecode extras outside allowlist; rejected restoration recorded separately, parent controls restoration. Original bytes unchanged."}
    write(out / "review.json", review)
    print(json.dumps({"status": review["status"], "path": (out / "review.json").relative_to(ROOT).as_posix(),
                      "rounds": rounds}))
    return 0 if passed else 1


if __name__ == "__main__":
    raise SystemExit(main())

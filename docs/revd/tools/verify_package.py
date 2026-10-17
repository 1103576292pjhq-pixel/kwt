"""Verify manifest-listed package files (not authenticity and not RTL acceptance)."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import sys


def verify(root: Path) -> dict:
    manifest = json.loads((root / "MANIFEST.json").read_text(encoding="utf-8"))
    errors = []
    for name, meta in manifest["files"].items():
        relative = Path(name)
        if relative.is_absolute() or ".." in relative.parts:
            errors.append(f"unsafe manifest path: {name}"); continue
        path = root / relative
        if path.is_symlink() or root.resolve() not in path.resolve().parents:
            errors.append(f"symlink/escape: {name}"); continue
        try:
            body = path.read_bytes()
            if len(body) != meta["bytes"] or hashlib.sha256(body).hexdigest() != meta["sha256"]:
                errors.append(f"changed: {name}")
        except OSError:
            errors.append(f"missing: {name}")
    return dict(status="PACKAGE_INTEGRITY_PASS" if not errors else "PACKAGE_INTEGRITY_FAIL",
                checked_files=len(manifest["files"]), errors=errors,
                scope="Only listed bytes; manifest is unsigned. Extra run outputs are not verified.")


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    args = p.parse_args()
    try:
        report = verify(args.root)
        print(json.dumps(report, ensure_ascii=False, indent=2))
        return 0 if not report["errors"] else 1
    except (OSError, ValueError, KeyError, TypeError) as exc:
        print(f"FAIL: {exc}", file=sys.stderr); return 1

if __name__ == "__main__":
    raise SystemExit(main())

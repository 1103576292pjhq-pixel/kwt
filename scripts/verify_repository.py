#!/usr/bin/env python3
"""Read-only integrity check for the copied repository, not a simulation gate."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import re
import sys
from pathlib import Path, PurePosixPath
from urllib.parse import unquote, urlsplit


def sha256(path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def local_path(root, name):
    path = PurePosixPath(name)
    if path.is_absolute() or ".." in path.parts or "\\" in name:
        raise ValueError("unsafe manifest path: " + name)
    return root.joinpath(*path.parts)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    args = parser.parse_args()
    root = args.root.resolve()
    manifest = json.loads((root / "config/repository-delivery.json").read_text(encoding="utf-8"))
    errors = []
    def check_file(item):
        name, expected = item
        try:
            path = local_path(root, name)
            if path.is_symlink() or sha256(path) != expected:
                return "file hash/type mismatch: " + name
        except (OSError, ValueError) as error:
            return name + ": " + str(error)
        return None

    # The tree includes many small files on Windows-mounted WSL drives.
    # Bounded I/O parallelism avoids serial filesystem round trips.
    with ThreadPoolExecutor(max_workers=8) as pool:
        errors.extend(error for error in pool.map(check_file, manifest["files_sha256"].items()) if error)
    for name, expected in manifest["symlinks"].items():
        try:
            path = local_path(root, name)
            if not path.is_symlink() or str(path.readlink()) != expected or not path.exists():
                errors.append("symlink mismatch/dangling: " + name)
        except (OSError, ValueError) as error:
            errors.append(name + ": " + str(error))

    frozen = json.loads((root / manifest["accepted_manifest"]).read_text(encoding="utf-8"))
    for name, expected in frozen["files_sha256"].items():
        if manifest["files_sha256"].get(name) != expected:
            errors.append("accepted evidence binding differs: " + name)

    production = json.loads((root / "work/encoder_source_freeze.json").read_text(encoding="utf-8"))["source_sha256"]
    for name, expected in production.items():
        if manifest["files_sha256"].get(name) != expected:
            errors.append("production source binding differs: " + name)

    link_count = 0
    for name in manifest["reading_documents"]:
        document = local_path(root, name)
        text = document.read_text(encoding="utf-8")
        for match in re.finditer(r"\[[^\]]*\]\(([^)]+)\)", text):
            raw = match.group(1).strip()
            target = raw[1:raw.index(">")] if raw.startswith("<") and ">" in raw else raw.split(' "', 1)[0]
            parsed = urlsplit(target)
            if parsed.scheme or parsed.netloc or not parsed.path:
                continue
            link_count += 1
            path = document.parent / unquote(parsed.path)
            if not path.exists():
                errors.append("broken link: " + name + " -> " + target)
    result = {
        "status": "FAIL" if errors else "PASS",
        "scope": "copied file bytes, symlinks, frozen evidence bindings, reading links; no new hardware run",
        "regular_files": len(manifest["files_sha256"]),
        "symlinks": len(manifest["symlinks"]),
        "accepted_evidence_files": len(frozen["files_sha256"]),
        "frozen_production_files": len(production),
        "reading_documents": len(manifest["reading_documents"]),
        "local_links": link_count,
        "errors": errors,
    }
    if any(error.startswith("symlink ") for error in errors):
        result["hint"] = "On a fresh checkout, run python3 scripts/prepare_repository.py inside WSL/Linux first."
    print(json.dumps(result, ensure_ascii=False, indent=2))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())

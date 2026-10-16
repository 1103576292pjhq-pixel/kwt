#!/usr/bin/env python3
"""Restore pinned upstream symlinks after checkout; run in WSL/Linux."""
import argparse
import json
import os
from pathlib import Path, PurePosixPath
import sys


def safe_path(root, relative):
    name = PurePosixPath(relative)
    if name.is_absolute() or ".." in name.parts or "\\" in relative:
        raise ValueError("unsafe source path: " + relative)
    return root.joinpath(*name.parts)


def prepare(root, check=False):
    delivery = json.loads((root / "config/repository-delivery.json").read_text(encoding="utf-8"))
    upstream = json.loads((root / "config/e203-source-manifest.json").read_text(encoding="utf-8-sig"))
    links = {
        repo["root"] + "/" + item["path"]: item["target"]
        for repo in upstream["repositories"]
        for item in repo["files"]
        if item["type"] == "symlink"
    }
    if links != delivery["symlinks"]:
        raise ValueError("upstream and delivery symlink metadata differ")

    missing = []
    for name, target in links.items():
        path = safe_path(root, name)
        if Path(target).is_absolute() or "\\" in target:
            raise ValueError("unsafe link target: " + name)
        resolved = (path.parent / target).resolve()
        if not resolved.is_relative_to(root):
            raise ValueError("link target escapes repository: " + name)
        if not resolved.is_file():
            raise ValueError("missing upstream link target: " + name)
        if path.is_symlink():
            if str(path.readlink()) != target:
                raise ValueError("existing link differs: " + name)
        elif path.exists():
            raise ValueError("refusing to replace existing non-link file: " + name)
        else:
            missing.append((path, target))

    if check and missing:
        raise ValueError("missing symlinks; first run: python3 scripts/prepare_repository.py")
    for path, target in missing:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.symlink_to(target)
    return {"status": "PASS", "symlinks": len(links), "created": len(missing), "check_only": check}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="validate without creating links")
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    args = parser.parse_args()
    if os.name != "posix":
        parser.error("Run this preparation command inside WSL/Linux, not Windows Python.")
    try:
        result = prepare(args.root.resolve(), args.check)
    except (OSError, ValueError, KeyError) as error:
        print(json.dumps({"status": "FAIL", "error": str(error)}, ensure_ascii=False), file=sys.stderr)
        return 1
    print(json.dumps(result, ensure_ascii=False))
    return 0


if __name__ == "__main__":
    sys.exit(main())

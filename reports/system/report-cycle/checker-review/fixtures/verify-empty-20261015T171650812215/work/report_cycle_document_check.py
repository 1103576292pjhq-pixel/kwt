"""Mechanical report checks; separate from independent technical review."""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import tempfile
from datetime import datetime, timezone
from pathlib import Path
from urllib.parse import unquote, urlsplit

ROOT = Path(__file__).resolve().parents[1]
NAMES = [
    "README.md", "00_赛题要求与验收对应表.md", "01_乘累加与数值处理模块.md",
    "02_前馈线性加速器.md", "03_前馈线性加速器SoC集成与综合.md", "04_单头注意力模块.md",
    "05_单层编码器.md", "06_十二层编码器与参数调度.md", "07_编码器加速器综合与性能分析.md",
    "08_总体验收报告.md", "09_复现与学习指南.md",
]


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def document_set_errors(base, names):
    actual = {p.name for p in base.iterdir()}
    files = {p.name for p in base.iterdir() if p.is_file()}
    expected = set(names)
    return (["missing document file " + name for name in sorted(expected - files)] +
            ["unexpected report entry " + name for name in sorted(actual - expected)])


def anchors(text):
    found, counts = set(), {}
    for heading in re.findall(r"^#{1,6}\s+(.+?)\s*#*\s*$", text, re.M):
        slug = re.sub(r"[^\w\- ]", "", heading.strip().lower()).replace(" ", "-")
        count = counts.get(slug, 0)
        counts[slug] = count + 1
        found.add(slug + ("-" + str(count) if count else ""))
    found.update(re.findall(r'\bid=[\"\']([^\"\']+)[\"\']', text))
    return found


def scan(path, check_links=True):
    text = path.read_bytes().decode("utf-8", errors="strict")
    errors, links = [], []
    if "\ufffd" in text or re.search(r"\b(?:TODO|TBD|PLACEHOLDER)\b|待补正文|占位图", text, re.I):
        errors.append("unresolved placeholder or replacement character")
    if not text.startswith("# "):
        errors.append("missing document title")
    active_fence = None
    prose_lines = []
    for line in text.splitlines():
        fence = re.match(r"^\s{0,3}(`{3,}|~{3,})(.*)$", line)
        if active_fence:
            if fence and fence[1][0] == active_fence[0] and len(fence[1]) >= active_fence[1] and not fence[2].strip():
                active_fence = None
            continue
        if fence:
            active_fence = (fence[1][0], len(fence[1]))
        else:
            prose_lines.append(line)
    if active_fence:
        errors.append("unbalanced fenced code block")
    # Both real encoder runners reject output directories outside reports/encoder.
    # Check the documented invocation, without running or importing a simulator.
    for invocation in re.finditer(r"\bbash\s+scripts/(?:run_encoder|run_e203_encoder)\.sh\b[^\n]*", text):
        output = re.search(r"--output\s+([^\s]+)", invocation.group())
        if output and not output[1].strip("\"'").startswith("reports/encoder/"):
            errors.append("encoder command output must be within reports/encoder: " + output[1])
    prose = "\n".join(prose_lines)
    math_prose = re.sub(r"(`+)(?:(?!\1).)*?\1", "", prose)
    delimiters = re.findall(r"(?<!\\)\$\$|(?<!\\)\$", math_prose)
    if (delimiters.count("$$") % 2 or delimiters.count("$") % 2 or
            prose.count(r"\[") != prose.count(r"\]") or prose.count(r"\(") != prose.count(r"\)")):
        errors.append("unbalanced math delimiter")
    for match in re.finditer(r"\[[^\]]+\]\((<[^>]+>|[^)]+)\)", prose):
        target = match.group(1).strip().strip("<>")
        # Optional markdown title follows a quoted string after the URL.
        target = re.split(r'\s+"', target, maxsplit=1)[0]
        if target.startswith(("https://", "http://", "mailto:", "codex:")):
            continue
        parsed = urlsplit(target)
        raw_path = unquote(parsed.path)
        resolved = (path.parent / raw_path).resolve() if raw_path else path.resolve()
        links.append(str(resolved))
        if check_links and not resolved.exists():
            errors.append("missing linked path: " + target)
        elif check_links and parsed.fragment and resolved.suffix.lower() == ".md":
            if unquote(parsed.fragment) not in anchors(resolved.read_text(encoding="utf-8")):
                errors.append("missing linked heading: " + target)
    return {"errors": errors, "local_links": links, "characters": len(text), "lines": len(text.splitlines()), "sha256": digest(path)}


def verify_manifest(base, mapping):
    for name, expected in mapping.items():
        path = base / name
        if not path.is_file() or digest(path) != expected:
            raise ValueError("missing/changed manifest member " + name)


def self_test():
    with tempfile.TemporaryDirectory() as td:
        base = Path(td)
        p = base / "ok.md"
        p.write_text("# 文档\n\n[自身](ok.md)\n\n$$x=1$$\n", encoding="utf-8")
        assert scan(p)["errors"] == []
        verify_manifest(base, {"ok.md": digest(p)})
        assert document_set_errors(base, ["ok.md"]) == []
        assert document_set_errors(base, ["ok.md", "missing.md"])
        assert document_set_errors(base, [])
        (base / "directory.md").mkdir()
        assert document_set_errors(base, ["ok.md", "directory.md"])
        p.write_text("# 文档\n[本节](#文档)\n$x=1$\n`$exp`与``$mem_v2``是代码\n", encoding="utf-8")
        assert scan(p)["errors"] == []
        bad = [
            ("missing-link.md", "# 标题\n[失效](gone.md)\n"),
            ("bad-fence.md", "# 标题\n```python\nx=1\n"),
            ("bad-tilde-fence.md", "# 标题\n~~~bash\nx=1\n"),
            ("bad-math.md", "# 标题\n$$x=1\n"),
            ("bad-inline-math.md", "# 标题\n$x=1\n"),
            ("bad-anchor.md", "# 标题\n[不存在](ok.md#missing)\n"),
            ("bad-encoder-output.md", "# 标题\n```bash\nbash scripts/run_encoder.sh --mode small --output reports/reproduction/demo\n```\n"),
            ("placeholder.md", "# 标题\nTODO\n"),
        ]
        for name, content in bad:
            q = base / name
            q.write_text(content, encoding="utf-8")
            assert scan(q)["errors"], name
        p.write_bytes(b"# x\n\xff")
        try:
            scan(p)
        except UnicodeDecodeError:
            pass
        else:
            raise AssertionError("invalid UTF8 accepted")
        try:
            verify_manifest(base, {"gone.md": "0" * 64})
        except ValueError:
            pass
        else:
            raise AssertionError("missing manifest member accepted")
        p.write_text("# Changed\n", encoding="utf-8")
        try:
            verify_manifest(base, {"ok.md": "0" * 64})
        except ValueError:
            pass
        else:
            raise AssertionError("stale hash accepted")
    return {"status": "PASS", "positive_fixtures": 2, "negative_fixtures_rejected": 14,
            "checker_sha256": digest(Path(__file__)), "checked_utc": datetime.now(timezone.utc).isoformat()}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        result = self_test()
        out = ROOT / "reports/system/report-cycle"
        out.mkdir(parents=True, exist_ok=True)
        (out / "document-self-test.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
        print(json.dumps(result))
        return
    base = ROOT / "docs/encoder/reports"
    results, errors = {}, document_set_errors(base, NAMES)
    for name in NAMES:
        p = base / name
        if not p.is_file():
            continue
        try:
            results[name] = scan(p)
        except (UnicodeError, OSError) as exc:
            errors.append(name + ": " + str(exc))
            continue
        errors.extend(name + ": " + err for err in results[name]["errors"])
        if re.match(r"0[1-7]_", name) and results[name]["characters"] < 3500:
            errors.append(name + ": technical report is only a short outline")
    out = ROOT / "reports/system/report-cycle"
    out.mkdir(parents=True, exist_ok=True)
    result = {
        "status": "PASS" if not errors else "INCOMPLETE",
        "checked_utc": datetime.now(timezone.utc).isoformat(),
        "scope": "Mechanical UTF8/file/link/delimiter/placeholder checks only; independent content and evidence reviews required",
        "checker_sha256": digest(Path(__file__)), "expected_documents": 11,
        "documents_checked": len(results), "local_links_checked": sum(len(v["local_links"]) for v in results.values()),
        "errors": errors, "documents": results,
    }
    (out / "document-check.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(result["status"], "documents=", len(results), "errors=", len(errors))
    for err in errors:
        print(err)
    if errors:
        raise SystemExit(1)


if __name__ == "__main__":
    main()

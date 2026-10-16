#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
PROJECT_KEY="$(python3 -c 'import hashlib,sys; print(hashlib.sha256(sys.argv[1].encode()).hexdigest()[:12])' "$ROOT")"
NATIVE_ROOT="$HOME/.local/share/kwt1-envs/$PROJECT_KEY"
NATIVE_ENV="$NATIVE_ROOT/model"
export UV_PYTHON_INSTALL_DIR="$ROOT/tools/python"
export UV_PYTHON_BIN_DIR="$ROOT/tools/python-bin"
export UV_CACHE_DIR="$NATIVE_ROOT/uv-cache-native"
export UV_HTTP_TIMEOUT=180
export UV_LINK_MODE=copy
UV="$ROOT/tools/uv-package/uv-0.13.0.data/scripts/uv"
if [[ ! -x "$UV" ]]; then
  python3 -m venv --copies "$ROOT/.venv-bootstrap"
  "$ROOT/.venv-bootstrap/bin/python" -m pip install 'uv==0.13.0'
  UV="$ROOT/.venv-bootstrap/bin/uv"
fi
mkdir -p "$ROOT/reports/model"
mkdir -p "$NATIVE_ROOT"
if [[ ! -f "$UV_CACHE_DIR/.workspace-cache-seeded" && -d "$ROOT/tools/uv-cache" ]]; then
  mkdir -p "$UV_CACHE_DIR"
  if [[ -d "$ROOT/tools/uv-cache/simple-v26" ]]; then
    cp -a "$ROOT/tools/uv-cache/simple-v26" "$UV_CACHE_DIR/"
  fi
  touch "$UV_CACHE_DIR/.workspace-cache-seeded"
fi
"$UV" python install 3.8.20
if [[ ! -x "$NATIVE_ENV/bin/python" ]]; then
  "$UV" venv --python 3.8.20 "$NATIVE_ENV"
fi
if [[ -e "$ROOT/.venv-model" || -L "$ROOT/.venv-model" ]]; then
  [[ "$(readlink -f "$ROOT/.venv-model")" == "$NATIVE_ENV" ]] || { echo 'ERROR: .venv-model exists at a different location; preserve it before changing environments.'; exit 2; }
else
  ln -s "$NATIVE_ENV" "$ROOT/.venv-model"
fi
python3 -c 'import json,sys; from pathlib import Path; Path(sys.argv[1]).write_text(json.dumps({"venv":sys.argv[2],"cache":sys.argv[3],"workspace_entry":".venv-model","reason":"WSL-native dependency installation; workspace keeps source/data/reports"},indent=2)+"\n",encoding="utf-8")' "$ROOT/config/model-environment-location.json" "$NATIVE_ENV" "$UV_CACHE_DIR"
"$NATIVE_ENV/bin/python" -c 'import sys; assert sys.version_info[:3] == (3, 8, 20), sys.version'
TF_WHEEL="$ROOT/tools/wheels/tensorflow-2.4.0-cp38-cp38-manylinux2010_x86_64.whl"
if [[ -f "$TF_WHEEL" ]]; then
  python3 -c 'import hashlib,sys; p=sys.argv[1]; h=hashlib.file_digest(open(p,"rb"),"sha256").hexdigest(); assert h=="dcd8f2e501a791c937fa19b31ea963470fc20d30cb763c3cc4740dc3c44aefe9", "TensorFlow wheel SHA-256 mismatch"' "$TF_WHEEL"
  "$UV" pip install --python "$NATIVE_ENV/bin/python" --no-deps "$TF_WHEEL"
fi
if [[ -s "$ROOT/config/requirements-model.lock.txt" ]]; then
  "$UV" pip sync --python "$NATIVE_ENV/bin/python" "$ROOT/config/requirements-model.lock.txt"
else
  "$UV" pip install --python "$NATIVE_ENV/bin/python" -r "$ROOT/config/requirements-model.txt"
fi
"$UV" pip check --python "$NATIVE_ENV/bin/python"
"$NATIVE_ENV/bin/python" -c 'import sys,tensorflow as tf,numpy as np,tensorflow_addons as tfa; print("MODEL_ENV_READY",sys.version.split()[0],"tensorflow",tf.__version__,"numpy",np.__version__,"addons",tfa.__version__)'
if [[ ! -s "$ROOT/config/requirements-model.lock.txt" ]]; then
  "$NATIVE_ENV/bin/python" -c 'from importlib.metadata import distributions; from pathlib import Path; import sys; packages={d.metadata["Name"]:d.version for d in distributions()}; assert packages.get("tensorflow")=="2.4.0",packages.get("tensorflow"); Path(sys.argv[1]).write_text("".join(name+"=="+packages[name]+"\n" for name in sorted(packages,key=str.lower)),encoding="utf-8")' "$ROOT/config/requirements-model.lock.txt"
fi

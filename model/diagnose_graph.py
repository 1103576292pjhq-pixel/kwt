"""Read-only official graph diagnostic; no inference/export or random baseline."""
from pathlib import Path
import sys

WORKSPACE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(WORKSPACE))
from model.run_baseline import official_flags

flags, _, builder = official_flags(WORKSPACE / "vendor/keyword-transformer")
import tensorflow as tf

with tf.Graph().as_default() as graph:
    model = builder.model(flags)
    transformer = next(layer for layer in model.layers if hasattr(layer, "enc_layers"))
    block = transformer.enc_layers[0]
    dense = block.ffn.layers[0]
    print("DENSE_KERNEL", dense.kernel.name)
    print("LN1_GAMMA", block.layernorm1.gamma.name)
    for op in graph.get_operations():
        if block.name + "/" in op.name and (dense.name + "/" in op.name or block.layernorm1.name + "/" in op.name):
            print(op.name, op.type, "IN", [tensor.name for tensor in op.inputs],
                  "OUT", [(tensor.name, str(tensor.shape)) for tensor in op.outputs])

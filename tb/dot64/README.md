# 点积模块测试平台

2026-10-23：按用户要求移除旧版三个测试平台：乘法器、结果转换、完整单乘法器点积核心TB。对应旧RTL也已移除，Git提交 `480bda3` 保留历史版本。

V07的四个计算模块与自检TB现已加入。接口、打包顺序、合法输入约定及测试来源见[V07计算接口说明](../../docs/shared/dot64-v07-interface.md)。

在Worktree根目录执行：

```bash
bash scripts/rtl/run_v07_tests.sh
```

脚本先使用Python标准库生成独立整数向量，再以Verilog-2005编译RTL并运行两个SystemVerilog TB。生成数据和仿真产物只放在out目录。

- `tb_v07_units.sv`：400个lane乘积、251个转换输入、12拍连续转换及背压/标签/中止。
- `tb_v07_compute.sv`：39个不同矩阵小块和6次恢复重算，共45块、1904次有效输出，比较内部累加选读结果及输出data/flags/tag。

2026-10-23上述测试通过。不是完整矩阵/存储/平台测试，不证明面积和150MHz时序通过。

以下验证依据继续保留：

- `tests/fixtures/dot64-v0.1/`：原有30个点积用例。
- `tests/fixtures/result-convert-v0.1/`：180个转换用例。
- `tests/fixtures/dot64-integration-v0.1/`：33个点积用例及来源。
- `scripts/model/fixed_point.py`：软件整数参考。

上述路径相对仓库根目录。旧版历史验证范围见[历史核心说明](../../docs/shared/dot64-core-v0.1.md)，不能作为新框架的通过结论。`out/`中可能保留旧仿真产物，不应当作新实现运行结果。

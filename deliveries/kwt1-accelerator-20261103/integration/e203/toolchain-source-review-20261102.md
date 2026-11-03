# E203 配套交叉编译器来源核对

日期：2026-11-02。用户要求直接核对指定 GitHub 仓库。通过 GitHub 插件读取完整仓库树和官方文档，没有安装或下载编译器，也没有修改服务器。

仓库：https://github.com/riscv-mcu/e203_hbirdv2

本次 master 对应提交：9f3e34f337f5d0a1236a285871ffa2032491617a。

## 直接证据

1. 递归 Git 树返回 truncated=false，共 1147 项。没有 riscv-tools/prebuilt_tools 路径，没有 riscv-nuclei-elf-gcc 可执行文件；prebuilt 路径匹配项为 FPGA 的预生成 mcs 镜像。
2. 官方 doc/source/quick_start/simulation.rst 第 47～79 行明确要求 Install RISC-V GNU toolchain，从 https://nucleisys.com/download.php 下载。在工程内创建 riscv-tools/prebuilt_tools/prefix/bin，随后将另行解压的工具链 bin/* 软链接到此目录。文档中的 rv_linux_bare 旧版本名只是样例，不能据此硬性要求使用同一旧版本。
3. riscv-tools/riscv-tests/isa/Makefile 第 35～39 行：RISCV_PREFIX ?= ${PWD}/../../prebuilt_tools/prefix/bin/riscv-nuclei-elf-；RISCV_GCC ?= $(RISCV_PREFIX)gcc；RISCV_OBJCOPY 使用 $(RISCV_PREFIX)objcopy -O verilog。用户服务器截图中的这些行与本次上游读取一致。
4. 官方 sdk.rst 分别说明 Windows/Linux 工具单独下载和解压；GNU 工具链与 HBird SDK 分开准备。

来源：
- https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/doc/source/quick_start/simulation.rst#L47
- https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/riscv-tools/riscv-tests/isa/Makefile#L35
- https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/doc/source/quick_start/sdk.rst#L99

## 结论与边界

E203 确有配套工具链及安装说明，但克隆/解压 RTL 仓库不会自动安装 GCC。源码相似不足以证明服务器另行安装了某软件。服务器可读范围未找到常见工具链；/eda/other 无权限，不能据此断言整台服务器完全没有安装。

下一步准确核对服务器工程内 riscv-tools/prebuilt_tools/prefix/bin/riscv-nuclei-elf-gcc。如缺失，可向平台管理员确认另装工具链的路径，或按官方文档准备独立工具链；不再将 build-e203-rvtests.sh 误当成 GCC 安装器。

## 赛题指南复核与服务器结果补充

用户随后截图确认，上述指定 gcc 路径返回 No such file or directory。该结果只证明工程指定位置缺失，不证明整台服务器未部署工具链。

直接读取本地 D:/嵌赛芯片设计赛道/2026赛题指南.pdf，《02 芯片硬件框架》正文第 3 页（PDF 第 4 页）明确写明：“芯来科技 E203 开源 RISC-V 处理器及配套软件开发环境，总线和外设采用组委会发布的平台工程。”指南要求驱动与 SoC 仿真，但没有指定编译器安装路径，也没有明确要求参赛队必须额外下载某一 GCC 包。因此不能用公开仓库需要单独安装的说明，推断赛方未提供配套编译环境；前面直接倾向补装工具链过早。

用户服务器公共目录截图包含 2025_Lab、Document、SMIC40_2025、SOC_RTL_2025、SRAM_Lib_2025。下一步针对配套资料和归档名称（nuclei、toolchain、rv_linux、gcc、sdk）核查，不仅按 riscv 名称匹配；若安装处无权限，向平台支持确认可用工具链路径和环境脚本。

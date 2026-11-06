# CPU固件导航

这是分类导航目录，实际文件仍在原位置，以保持脚本相对路径和已有清单有效。不要把本目录作为编译或运行工作目录。

12任务环境的实际目录：[dma_suite](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/)。

| 文件 | 用途 |
|---|---|
| [real_io.c](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/real_io.c) | 主程序入口 |
| [shared_task.c](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/shared_task.c) | 输出预填充、共享结果及守卫检查 |
| [task_test.c](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/task_test.c) | DMA寄存器配置、启动与轮询 |
| [kwt_mmio.h](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/kwt_mmio.h) | MMIO接口 |
| [start.S](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/start.S) | 启动汇编 |
| [link.ld](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/link.ld) | 链接布局 |
| [build.py](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/build.py) | 固件构建 |

[加速器独立测试固件](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_accelerator/firmware/)是另一配套环境，不应与整套SoC结果混用。

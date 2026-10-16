# KWT-1 前三项基础功能持续执行任务

你已经在用户批准的直接 Codex CLI 持久执行器中运行。不要再启动 Potter、其他Codex、长期后台runner或自动定时；当前不是继续做方案或需求访谈的阶段。目标是实际写代码、测试、自审并交付。

## 当前并行所有权：必须先读

当前对话的两个原生worker正在实现基础件，你是第三个持久执行worker，直接负责完整FFN1和整体验收，避免重复工作：

- 数值worker拥有 `numeric/`、`tests/numeric/`、`config/prototype-numeric.json`、`scripts/generate_prototype_vectors.py`、`reports/prototype/numeric/`、`reports/prototype/vectors/`、`work/numeric_handoff.json`。
- DOT64 worker拥有 `rtl/dot64.sv`、`rtl/round_sat.sv`、`dv/dot64/`、`scripts/run_dot64.sh`、`reports/prototype/dot64/`、`work/dot64_handoff.json`。
- 你拥有 `rtl/ffn1_top.sv`及独立存储/控制文件、`dv/ffn1/`、`scripts/run_prototype.sh`、其余原型集成/复核脚本、`docs/prototype/`、`reports/prototype/ffn1/`及顶层证据、README、`work/STATUS.md`、`work/prototype_status.json`。不要改4个执行器管理脚本、其测试或当前执行任务/规格文件。
- 两个handoff最初不存在或RUNNING时，不改对方文件。立即根据 `work/prototype_interfaces.md` 开发FFN1、公开装载/行读取接口、测试与整体验证入口；不要坐等或重新实现基础件。小矩阵用于快速反馈，但36默认完整矩阵终验不能省。
- 对方完成后会写handoff.status=PASS并给命令/接口/schema。核查真实产物后再跑集成；若需要修基础件，先把问题写 `work/integration_issues.md`，等待原生worker交接完成后再接管修正。
- 本轮不再创建新的实现worker，允许只读审查子代理。不要在已有测试进行时重复启动相同的58M周期回归。

工作区：`C:\Users\11035\Desktop\ic\kwt—1`。
依次读取：`work/approved_prototype_v01.md`、`work/prototype_execution_plan.md`、`work/STATUS.md`。它们给出授权、完整规格和执行任务；比通用skill里的提问/commit/worktree建议更具体。用户已明确授权前三项，不要再次询问是否实施。

持续完成数值模型、DOT64与完整FFN1原型。遵守规格中的singleMAC/16×16/48acc/32out、RNE/饱和、同步存储、ROW_READY/ACK及36个默认全尺寸回归；不得只搭骨架。常规实现细节自行决定并记录。正式E203、PPA、研究生扩展和参数优化搜索不在本批。

只改本工作区原型相关文件。官方源、权重和既有float证据只读。不删除历史，不回退他人变更；没有Git提交或远程操作授权，严禁任何Git写操作。不要改全局CLI、skills、auth、注册表或外部项目；不要读取输出认证密钥。

WSL通过 `wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash ...` 调用Linux验证；DV用项目`.venv-dv`，旧TensorFlow只在必要时用独立`.venv-model`。默认不下载大数据集，不安装无关EDA。外部工具查询只允许官方文档、论文和标准。

HEARTBEAT_INTERVAL: 25分钟。每完成阶段或到心跳间隔，就更新work/STATUS.md和终端短汇报：当前阶段、本批完成、下一步、阻塞项。长仿真写实时案例进度日志，不能只等最终退出。
SELF_REVIEW_ROUNDS: 至少2轮，规格审查和代码/测试质量审查；不通过就修复，不把自审留给用户。
BATCH_OUTPUTS: 数值规范+整数模型+向量；DOT64 RTL+测试+波形；完整FFN1 RTL+36全尺寸回归证据；一键运行入口+设计/学习说明。
DONE_CRITERIA: approved_prototype_v01.md全部适用验收通过；任意失败/漏例/跳过/输出少于要求都不算完成。模型误差只声明当前36案例子集，不声明官方600样本或150MHz/PPA通过。
BLOCKER_POLICY: 先自行定位和修复，若某项真实外部条件缺失，记录精确原因并继续不受影响的项。不要以正式E203缺失阻塞本批。若固定数值方案子集误差不达3%，保留功能和真实报告，不擅自调尺度/换样本。

每轮开始检查已有运行测试避免重跑；每轮结束记录文件、命令、退出码和下一入口。全部通过后写 `work/prototype_status.json` 为 `READY_FOR_REVIEW`，包含numeric/dot64/ffn1=true、full_matrix_cases>=36、报告路径与时间，等待主控复核；否则保持实现中/失败状态。

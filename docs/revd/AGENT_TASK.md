# 交给开发代理的执行指令：KWT RevD

先阅读PLAN和docs/REVIEW_AUDIT，再执行。不要把外部评估未经核对的断言当作项目现状。

## 范围与不可破坏的基线

KWT固定3d9d0fc77457b8869cbf525d826dafb114f2a8e1；E203参考9f3e34f337f5d0a1236a285871ffa2032491617a。

当前任务是本科FFN1独立核，不改CPU/旧ICB/驱动/vendor，不重写FP32 encoder，不安装工艺库，不开发NICE/DMA，不做综合。保留旧模型、源码和报告；未来本科top选择整数核，不例化无用FP32硬件。不得push远程。

已核事实：官方提取为TensorFlow，不是PyTorch；当前加速器验证为ICB，不得声称已有NICE；已有内部交换/外部重载CPU对照；3%与2个百分点是门槛，不是满分。

## 本轮路线

D0固定契约和复现；D1基础micro；D2全缓存矩阵；D3CTX4；D4单W/Y；D5分别双W/双Y；D6可选XP2；D7同条件比较。

4×4为主，2×4对照；K64、N16..256且16倍数，M1..99，N_TILE16。数值保持signed16乘、signed48累加、signed49加bias、sat48、RNE、sat32和原flags。所有shift0..47、极值、最后乘积及连续任务/复位都要测试。

CTX4每k读取保持四行X，按四个列组更新四上下文。向量/acc/快照/输出都带标签和owner；反馈延迟与返回信用要按真实时序验证。

V2外层按16列W块，内层处理全部99行，每W/b每任务只装一次。大bank为16位单端口同步读，不清零RAM。W在最后bias使用结束前不释放；Y在最后结果握手前不覆盖。

新增XP2不是默认替换X4。两个16×4096候选存储体按m%2放X，四行分两拍读，CTX4四组计算期间预取下一k；保留两组向量寄存器。比较1/2拍RAM延迟，不能只凭容量足够说带宽足够，不能把22vs28个宏写成确定面积节省。

## 公开逻辑接口

使用一个有序事件流BEGIN/LOAD_X/TILE_OPEN/LOAD_W/LOAD_B/TILE_COMMIT/START，正常数据不逐元素应答。入口接受与实际RAM写入分开，COMMIT/START不可越过未完成写。

V2只在START前预载tile0；不得让一个等EMPTY槽的未来OPEN阻塞队列中后续START。输入供给和输出接收必须并发。未取得slot是合法背压，非法顺序是错误；不要用全局大超时掩盖死锁。

结果带task_id、y_index、data、flags、last。25344个唯一有效输出被真正接受后才core_done，未来system_done另等共享写响应。故障不假成功，valid背压保持至握手或reset。

TB可以从公开端口装载输入并接结果。禁止直写DUT私有RAM、内部强制状态、答案回灌或CPU软件代算必做运算。旧数值模型为golden，新软件模型只辅助。

## 验收、日志与停止条件

先运行短例；一个全尺寸通过再跑旧36例和独立新进程复跑。每阶段实际命令、工具、源/diff、输入/权重/输出摘要与退出码全部保留；失败先修，不堆更多功能。

本包软件自检不是RTL通过。缺工具/缺产物/跳过/非零退出/输出不足/不匹配均失败。不得删除断言、放宽阈值、改旧SHA或旧PASS。宏面积/功耗未知为null，不为0。

本轮结束提供：V1/V2的真实独立核数据、七组+XP2可选对照、模块来源和剩余事项。不要声称150MHz、正式精度、E203新版本或PPA已通过。

完整编码器复用/INT8/LUT/PWL只在后续另行批准阶段执行；必须先建立跨K分段宽部分和和新的尺度契约，不能直接把dot64最终sat32输出拼加。

## 本地工作树启动（先确认分支和目录未存在）

```bash
git status --short
git rev-parse HEAD
git worktree add -b opt/ffn1-core-revd ../kwt-core-revd 3d9d0fc77457b8869cbf525d826dafb114f2a8e1
cd ../kwt-core-revd
python3 scripts/prepare_repository.py
python3 scripts/verify_repository.py
```

新代码放rtl/revd、dv/revd、config/revd；新输出放reports/revd/<config>/<run_id>，拒绝覆盖。工作树不自动复制未跟踪虚拟环境，先确认工具路径。

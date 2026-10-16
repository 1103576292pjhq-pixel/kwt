"""Write the independent human review and machine-readable acceptance snapshot."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

ROOT = Path(__file__).resolve().parents[4]
OWN = Path(__file__).resolve().parent
REVIEW = OWN.parent / "review-quality-all.md"
RECORD = OWN.parent / "review-quality-all.json"


def digest(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


e = json.loads((OWN / "evidence.json").read_text(encoding="utf-8"))
assert e["status"] == "PASS"
docs = e["documents"]
assert len(docs) == 11
for rel, expected in docs.items():
    assert digest(ROOT / rel) == expected, rel

assessments = [
    ("README.md", "PASS", "逐段实读导航、1—3本科/4—7扩展、两数值路径、学习顺序与状态语义；读者能选主线且不会把本地证据当比赛通过。"),
    ("00_赛题要求与验收对应表.md", "PASS", "逐条比对指南全文；补齐三处遗漏后回读。覆盖平台、宏、模型/数据、七项、评分准入/分式和交付来源；页码和待验边界明确，自检有答案。"),
    ("01_乘累加与数值处理模块.md", "PASS", "完整阅读量化尺度、48/49位、后置bias、RNE/sat、64次握手、复位/背压与证据；−8和溢出后右移例子可复核，6道自检均给明确答案。"),
    ("02_前馈线性加速器.md", "PASS", "完整阅读X/W_pack布局、同步PRIME/FEED、69拍、行生命周期、十二组FFN1参数与覆盖；全部Y/flags及MAC计数独立核对，7道自检可校对。"),
    ("03_前馈线性加速器SoC集成与综合.md", "PASS", "完整阅读系统图/地址、fresh LO/HI、同步读/响应、生产驱动/错误、真实CPU边界和generic；整数CPU输出/flags回读，8道自检含恢复和失败信号。Yosys cell名修后以代码显示。"),
    ("04_单头注意力模块.md", "PASS", "完整阅读QKV无bias、Wo有bias、QKᵀ/8、稳定Softmax、PV、转置地址、行缓存和公开op6；6336公开Y与51282 trace逐项核实，手算概率可重算且6题有答案。"),
    ("05_单层编码器.md", "PASS", "完整阅读两残差/两LN、总体方差/eps1e−6、gamma/beta预取、64→256→64、tanh GELU与erf分离；14阶段/180层覆盖有准确分界，LN例子及8道自检可学可校对。"),
    ("06_十二层编码器与参数调度.md", "PASS", "完整阅读13段参数、49792word、共享/内部容量、真实固件供参、WAIT_DONE、SWAP/RELOAD和分类；三要素/同输入/真实CPU写回分列清楚，5题均附答案。"),
    ("07_编码器加速器综合与性能分析.md", "PASS", "完整阅读generic拓扑/宏映射缺口、面积/功耗不同范围、inclusive/四段/逐层、CPU与host分母及条件吞吐；10项统计独立重算，7题解释边界，未虚构PPA。"),
    ("08_总体验收报告.md", "PASS", "完整阅读七项、34阶段/根控接受、唯一输入/重复/被动与CPU、近似误差/分类和正式待验；接受身份与稳定快照回验，结尾比例自检给因果及分母。"),
    ("09_复现与学习指南.md", "PASS", "完整阅读WSL/环境、只读入口、小例→代码→完整CPU、允许输出路径和副作用；逐项对照真实argparse/guard/调用链，6道检查均附答案。"),
]
closed = [
    {"id":"Q3-01", "severity":"P3", "state":"CLOSED", "original_location":"docs/encoder/reports/00_赛题要求与验收对应表.md:精度、性能与最终交付", "issue":"缺印刷12页效率/创新评分准入、无合格零分及三项相对计分", "closure":"作者新增准入行、六项组别权重、T/Tmax、Emin/E、Amin/A及精度扣分；审查者对照物理13/印刷12页图像及全文独立回读。"},
    {"id":"Q3-02", "severity":"P3", "state":"CLOSED", "original_location":"docs/encoder/reports/00_赛题要求与验收对应表.md:初赛/决赛交付", "issue":"缺印刷14页来源/贡献、禁止预存答案/适配脚本代算、冻结及统一更正", "closure":"作者新增来源/贡献与冻结评测行；审查者逐项对照物理15/印刷14页图像和实际TB/固件的数据流回读。"},
    {"id":"Q3-03", "severity":"P3", "state":"CLOSED", "original_location":"docs/encoder/reports/00_赛题要求与验收对应表.md:平台、模型和数据的共同约束", "issue":"缺印刷5页batch1、固定长度及不要求因果mask的明确约束", "closure":"作者新增固定99token/batch1/无变长与因果mask要求行；审查者对照物理6/印刷5页及04/05/06独立回读。"},
    {"id":"D3-01", "severity":"P3", "state":"CLOSED", "reported_by":"root", "original_location":"docs/encoder/reports/03_前馈线性加速器SoC集成与综合.md:211,212,216,220", "issue":"Yosys $mul/$mem_v2 未包代码标记，可能触发数学解析", "closure":"root只补代码反引号；本审查者再次逐行读取四处，当前均为代码标识，内容/数值未改，绑定最终03摘要。"},
]
commands = [
    {"command":"D:/Program Files/Python312/python.exe -B reports/system/report-cycle/quality-readback/independent_readback.py", "exit_code":0,"result":"PASS", "scope":"Read-only source/artifact/word/statistics verification; only writes owned quality-readback files"},
    {"command":"wsl.exe -d Ubuntu-24.04 --cd /mnt/c/Users/11035/Desktop/ic/kwt—1 --exec /usr/bin/env PYTHONDONTWRITEBYTECODE=1 .venv-dv/bin/python dv/encoder/freeze_sources.py --verify", "exit_code":0,"result":"ENCODER_SOURCE_FREEZE_CURRENT files=192", "scope":"The documented WSL read-only verifier, no compile/simulation"},
    {"command":"Native Windows Python dv/encoder/freeze_sources.py --verify (diagnostic, outside documented WSL platform)","exit_code":1,"result":"production or dependency changed after freeze","interpretation":"Native Path.relative_to renders backslash keys while frozen WSL keys use slash; custom byte hashes and actual documented WSL verifier both pass. No production drift inferred."},
]
evidence_paths = [
    "reports/system/root-formal-acceptance.json", "reports/system/formal-baseline/runner-state.json", "work/encoder_source_freeze.json",
    "reports/encoder/verification/performance.json", "reports/encoder/system/pingpong/status.json", "reports/encoder/system/reload/status.json",
    "reports/encoder/reference/manifest.json", "reports/encoder/reference-test12/manifest.json", "reports/encoder/rtl/full/original-0/status.json",
    "reports/encoder/rtl/repeat/status.json", "reports/encoder/rtl/attention-full/status.json",
    "reports/prototype/ffn1/full/status.json", "reports/prototype/vectors/manifest.json", "reports/system/e203-ffn1/result.json",
    "work/report_cycle_sources/2026赛题指南.pdf", "work/report_cycle_sources/guide-text.txt",
    "reports/system/report-cycle/quality-readback/independent_readback.py", "reports/system/report-cycle/quality-readback/evidence.json",
    "reports/system/report-cycle/quality-readback/evidence-inputs.json", "reports/system/report-cycle/quality-readback/pdf-readback.json",
    "reports/system/report-cycle/quality-readback/independent-readback.stdout.json",
    "reports/system/report-cycle/quality-readback/finalize_review.py",
    "reports/system/report-cycle/quality-readback/guide-physical-06.png",
    "reports/system/report-cycle/quality-readback/guide-physical-13.png",
    "reports/system/report-cycle/quality-readback/guide-physical-15.png",
]
evidence_hashes = {p:digest(ROOT/p) for p in evidence_paths}
per_file_rows = "\n".join(f"| {name} | {status} | {reason} |" for name,status,reason in assessments)
hash_rows = "\n".join(f"| {Path(rel).name} | `{value}` |" for rel,value in docs.items())
finding_rows = "\n".join(f"| {x['id']} / {x['severity']} | {x['issue']} | {x['closure']} | CLOSED |" for x in closed)
body = f"""# 第二轮独立审查：数字、来源绑定、复现与可学性

**结论：PASS。** 全部11份Markdown已经逐篇完整阅读；开放P1=0、P2=0、P3=0。本轮独立发现3项需求矩阵P3，作者修复后由本审查者回读关闭；root另发现的Yosys标识显示P3也已独立回读关闭。本结论仅代表当前报告快照第二轮审查通过，不代表报告执行主线已真实结束或整套报告已由总控接受，更不代表正式比赛通过。

审查者：`cycle_quality_review`，第二轮、非作者。本轮遵守只读生产/阅读文件/状态边界，只写本审查文件、同名JSON及`quality-readback/`。未启动仿真、综合、搜索、持久runner或Git操作。第一轮工件保持原状，未用其PASS替代本轮阅读和证据核实。

## 发现、修复和独立关闭

| 编号 | 初始问题 | 再次回读证据 | 状态 |
|---|---|---|---|
{finding_rows}

00最终SHA为`{docs['docs/encoder/reports/00_赛题要求与验收对应表.md']}`；03最终SHA为`{docs['docs/encoder/reports/03_前馈线性加速器SoC集成与综合.md']}`。00和03的修改只影响文档，192项生产冻结保持不变。第一轮历史快照不改写，本轮绑定当前11份文件。

## 逐篇实读与学习性判定

| 文件 | 判定 | 实读范围与学习性评估 |
|---|---|---|
{per_file_rows}

报告01—05分别给出完整例子、公式/地址/时序说明、输入输出与失败信号；06—07将调度、性能拆成可复核量；08—09提供结果辨识与动手路径。各篇自检均有直接答案或判定口径。用独立算术重算−8、负半值RNE、attention概率0.3616644631、LN倒标准差1.1546997686、地址17095、48064/300544/2840B容量，均符合正文。教学十进制近似与实际FP32 hex明确区分。

## 本轮实际证据回读

独立脚本为[quality-readback/independent_readback.py](quality-readback/independent_readback.py)，本次实际退出0，结果[quality-readback/evidence.json](quality-readback/evidence.json)。本轮没有调用生产门禁来重跑长任务，也没有把`--help`当功能验证。

- **接受与冻结**：独立回验根接受17项evidence、59项review输入、192项生产源，全部摘要匹配。旧硬件runner使用稳定`formal-baseline/runner-state.json`，真实exit0、结束于`2026-10-15T16:44:40.0858073Z`；不以新动态runner状态否定旧接受。冻结清单SHA=`{e['freeze_sha256']}`。
- **来源到消费物**：本次{e['all_hash_bindings_checked']}条映射哈希核验、{e['unique_files_hashed']}个唯一文件摘要回读，失配0。每个完整RTL案例及两CPU的生产来源、编译来源、输入、binary、build/compile记录和日志均按各自状态字段实核；完整输入manifest见[evidence-inputs.json](quality-readback/evidence-inputs.json)。事后消费物回读不冒充运行前staging快照。
- **独立参考**：原3输入597数组、5,676,572word；test12的2244数组、20,909,216word。共2841数组、26,585,788word的NPY/bin/hex原始位、有限值、格式及层间链全部一致。实际15份输入binary摘要互不相同。独立读取官方导出binary重算最大最终NRMSE为0.0004071640493761876/0.000513838042935309，和正文相符。silence双方预测unknown；12/12为与官方预测一致，不能称全部标签正确，也不可据test调数值配置。
- **完整RTL**：直接读取15案例/180层CSV和各次原simulation.log，对12条逐层words/cycles/flags重新比对；所有公开Y共1,140,480word逐位一致且有限，计算周期总和3,817,428,084，单例范围254,468,303—254,507,214。额外独立repeat76,032word与首例一致，PID/起始时间不同；不算第16个唯一输入。首例完整trace逐项核对(layer,stage,address,value)、重复/缺项，共1,603,800word零差。
- **独立attention**：公开op6实际PASS/exit0、输出6336word、七阶段trace51,282word均逐项一致；输出SHA为`{e['attention']['output_sha256']}`。trace完整不代表硬件常驻完整score矩阵。
- **真实双CPU**：两策略各12层，各76,032 neural word；policy1 CPU写6336，policy2写76,032，共152,064 neural与82,368 CPU word逐项零差且有限。每策略178自身来源+172编译来源+30输入绑定实核；两份不同ELF分别重建allocatable sections形成bin，与1512B bin/hex一致。实际命令在各status起止时间内唯一匹配，编译宏与`+POLICY`一致、`+BYTES=1512`一致，两模拟器binary摘要同为`f3757e5e36e51fd8c67140ed2992f6b2074fae48a8699113880a6435ea071bf9`。
- **整数证据**：直接读36案例的actual.hex及冻结Yq/overflow/saturated，912,384个完整结果/标志一致，真实MAC记录合计58,392,576；四类周期重加为load1,654,343、compute62,954,496、row_wait39,257、readback1,821,204。由原浮点Y与解码Y重算最大单例NRMSE0.0010805182139773971、最大三输入按层合并NRMSE0.0009342248801263425。整数CPU两次各25,344个Y和flags含顺序逐项核对；总cycles均8,595,787。XML实际numeric67/gate39/DOT648项，无失败/跳过；读取的是既有XML，本轮没有新执行这些测试。
- **generic**：从实际design.json重新遍历，encoder50个定义/可达50，SoC279个定义/可达278，cpu/ram/encoder/ffn1连接全部可解析。两design摘要实核，不将cell数或存储字节换算mm²。仍无指定库映射、SDC/STA或功耗结果。

证据结果SHA=`{evidence_hashes['reports/system/report-cycle/quality-readback/evidence.json']}`；完整输入摘要清单SHA=`{e['evidence_inputs_manifest_sha256']}`；独立脚本SHA=`{evidence_hashes['reports/system/report-cycle/quality-readback/independent_readback.py']}`。

## 从原日志重算性能与边界

两CPU的summary必须与各simulation.log的实际`E203_ENCODER_PASS`行完全相同；端点及HOST_LAYER_LOAD/CPU_ENCODER_START均从原日志重新解析。performance的生成源码SHA与当前`encoder_report.py`一致，10项comparison的原值、差值和分母比例重算全部一致。

| 指标 | pingpong | reload | 差值 / 解释 |
|---|---:|---:|---|
| begin/final_write | 4543 / 284358022 | 4543 / 290631971 | 首末拍inclusive |
| E2E=final−begin+1 | 284353480 | 290627429 | 6273949，减少2.1587601079% |
| 四段和 | 285547+597504+28685484+254784945 | 285547+597504+28685484+261058894 | 均等于E2E |
| CPU shared R+W | 653640+6394=660034 | 723336+76090=799426 | 139392，减少17.4365106964% |
| host参数写/ready写/请求读 | 597504 / 12 / 12 | 597504 / 12 / 12 | 两策略相同 |
| CPU+host逻辑总事务 | 1257562 | 1396954 | 139392，减少9.9782813178% |
| IFU握手 / 命令背压 | 16716244 / 0 | 20271323 / 0 | 不是退休指令/全部等待 |

每层host49792、ready→START2390457；前11层START后区段各省570359，末层差0。统计截止实际末输出写拍；CPU响应等待仍在E2E中，`bus_waits`只统计`cmd_valid&&!cmd_ready`。初始host输入fixture在窗外；逻辑host访问不是同一ICB物理端口的观测，逻辑合计不是宏访问或能耗。

150MHz仅条件换算：pingpong为1.8956898667s、0.5275124468任务/s；reload为1.9375161933s、0.5161247186任务/s。当前无STA签核，不能将条件换算称正式吞吐或将周期减少改名吞吐增加。两个同输入CPU运行也不是正式12类别整机性能任务。

## 复现安全和指南核对

逐项实读`run_encoder.py`、`run_system.py`、`verify_bundle.py`、冻结器及shell包装器的真实参数/guard/调用分支。15条encoder输出示例全在允许的`reports/encoder/`子树；新目录避免覆盖已接受案例，固定目录命令说明了写入和串行要求。`verify_bundle.py` CLI确会写readback-verification.json，04/05没有再称只读；freeze `--verify`不写冻结文件。

实际执行文档的WSL冻结只读命令，退出0，打印`ENCODER_SOURCE_FREEZE_CURRENT files=192`。原生Windows诊断直跑因Path键分隔符差异拒绝，报告本来就限定WSL；实际WSL通过和独立字节摘要均证明没有源漂移，不把不支持平台的拒绝当成本工程功能失败。

11文件UTF-8回读无替代字符，本轮313个本地Markdown链接存在。报告03的`$mul`/`$mem_v2`已放代码标记，公式/代码作用域没有混用。图示以Mermaid/文字箭头表达现有数据流，未用装饰图填充机制。

工程PDF实际15物理页，SHA=`b73a5414b4dcdb2cca337778a133be88705e207bec080687731d63b413ea927c`；逐页文本已实读，页码采用印刷=物理−1。另独立渲染并实际查看物理6/13/15页，对照batch边界、评分准入/分式、来源及禁止预存条款，记录见[pdf-readback.json](quality-readback/pdf-readback.json)。本科1—3与扩展4—7的边界、全部神经计算RTL/CPU搬运、PostNorm/两残差/两LN、QKV无bias/Wo有bias/eps1e−6、tanh/erf误差分离均与来源和代码一致。

## 正式待验与审查范围

组委会平台、指定标准单元及16bit×128/1024/4096 SP/DP SRAM宏、合法SDC和工艺映射、150MHz/关键路径裕量、新增面积≤2.25mm²、综合前后功能、同窗口活动映射/整SoC功耗与单任务能耗、600样本和正式12任务继续为外部待验。赛题无P&R验收。本轮不伪造这些结果，也不把不同层级通过合并成全部正式要求通过。

## 当前文档摘要

| 文件 | SHA-256 |
|---|---|
{hash_rows}

本审查允许总控进入剩余报告批次收口；最终manifest/检查结果、报告执行主线真实退出和根控接受仍由总控分别确认。
"""
REVIEW.write_text(body, encoding="utf-8")
record = {
    "status":"PASS", "round":2, "reviewer":"cycle_quality_review", "reviewer_role":"independent second-round reviewer, not an author",
    "document_count":11, "documents":docs, "review_file":str(REVIEW.relative_to(ROOT)).replace("\\","/"),
    "review_sha256":digest(REVIEW), "open_findings":{"P1":0,"P2":0,"P3":0}, "closed_findings":closed,
    "per_document_assessment":[{"path":"docs/encoder/reports/"+n,"status":s,"read_in_full":True,"assessment":a} for n,s,a in assessments],
    "whole_project_acceptance":False, "formal_acceptance":False,
    "read_only_production_and_documents":True,"hardware_commands_run":0,"git_operations":False,
    "counts":{k:e[k] for k in ["root_evidence_bindings","root_review_input_bindings","production_source_bindings","all_hash_bindings_checked","unique_files_hashed","actual_distinct_input_hashes","rtl","repeat_words","trace_words","attention","reference","reference-test12","performance_comparisons_recomputed","integer_ffn1","integer_cpu","xml_counts","local_links_checked","encoder_output_examples_guard_checked"]},
    "cpu_readback":{"neural_words":152064,"cpu_writeback_words":82368,"policies":e["cpu"]},
    "evidence_sha256":evidence_hashes, "artifacts_sha256":evidence_hashes, "command_results":commands,
    "external_pending":["official platform","specified cells and 16bit SRAM macros","mapped netlist and valid SDC","150MHz timing","incremental area <=2.25mm2","post-synthesis functionality","activity mapping and SoC power/energy","official 600 samples","official 12 performance tasks"],
    "completed_utc":datetime.now(timezone.utc).isoformat(),
}
RECORD.write_text(json.dumps(record,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps({"status":record["status"],"round":2,"documents":11,"open_findings":record["open_findings"],"review_sha256":record["review_sha256"],"json_sha256":digest(RECORD)},ensure_ascii=False))

"""Independent root acceptance for the scoped repair, not contest qualification."""
from pathlib import Path
import hashlib
import json
import subprocess
import sys
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[2]
REPORTS = ROOT / 'reports/revd_repair_20261017'

def disk(p):
    value = str(p.resolve())
    return Path('\\\\?\\' + value) if sys.platform == 'win32' and not value.startswith('\\\\?\\') else p

def sha(p):
    h = hashlib.sha256()
    with disk(p).open('rb') as stream:
        for block in iter(lambda: stream.read(1048576), b''):
            h.update(block)
    return h.hexdigest()

def read(p):
    return json.loads(disk(p).read_text(encoding='utf-8'))

def bind(items, base=ROOT):
    for name, digest in items.items():
        assert sha(base / name) == digest, name

state = read(ROOT / 'work/revd_repair_20261017/package_state.json')
assert state['status'] == 'ROUNDTRIP_AND_W2_PASS'
assert sha(ROOT / state['roundtrip_report']) == state['roundtrip_report_sha256']
assert sha(ROOT / state['w2_report']) == state['w2_report_sha256']
proof = read(ROOT / state['roundtrip_report'])
detail = read(ROOT / proof['portable_result'])
package = ROOT / proof['extraction']
assert proof['status'] == detail['status'] == 'PASS'
assert detail['completed_phases'] == ['manifest', 'smoke', 'numeric', 'cpu-small']
assert detail['tools_unchanged'] is True
assert proof['source_unchanged'] is True
assert sha(ROOT / proof['archive']) == proof['archive_sha256']
assert sha(package / 'MANIFEST.json') == state['manifest_sha256']
bind(proof['source_sha256'])
for command in [*proof['commands'], state['w2_command']]:
    assert command['exit_code'] == 0 and command['pid'] > 0
    log = ROOT / command['log']
    assert sha(log) == command['log_sha256']
    assert read(log.with_suffix(log.suffix + '.command.json')) == command
cpu = next(p for p in detail['phase_results'] if p['phase'] == 'cpu-small')
assert cpu['command']['exit_code'] == 0 and cpu['gate']['outputs'] == 96
assert sha(package / cpu['evidence']) == cpu['evidence_sha256']
assert sha(package / cpu['binary_binding']) == cpu['binary_binding_sha256']
cpu_report = read(package / cpu['evidence'])
binding = read(package / cpu['binary_binding'])
assert binding['actual_executable_sha256'] == cpu_report['compiled_simulator_sha256'] == cpu['gate']['cpu_binary_sha256']
assert sha(package / binding['actual_executable']) == binding['actual_executable_sha256']
bind(cpu_report['source_sha256'], package)
probe = read(REPORTS / 'fresh-cpu-probe.json')
assert probe['status'] == 'PASS' and probe['immutable_bytes_unchanged']
assert len(probe['observations']) == 5 and all(p['matches_expected'] for p in probe['observations'])
bind(probe['source_sha256'])
green = read(REPORTS / 'cpu_identity/green_frozen.json')
assert green['tests'] == 22 and green['failures'] == green['errors'] == 0
cpu_summary = read(REPORTS / 'cpu_identity/summary.json')
bind(cpu_summary['changed_sources'])
strict = read(REPORTS / 'w2_packaging/strict_red_replay_20261017T114307Z/proof.json')
assert strict['status'] == 'PASS' and strict['checker_sha256_equal']
assert strict['red_checker_exit_code'] == 1
assert sha(ROOT / 'dv/revd_opt/package_readme_command_checks.py') == strict['checker_sha256']
w2 = read(ROOT / state['w2_report'])
assert w2['status'] == 'PASS' and w2['source_unchanged']
assert state['w2_independent_output_words'] == state['w2_independent_flag_words'] == 192
bind(w2['source_sha256'], package)
bind(w2['artifacts_sha256'], (ROOT / state['w2_report']).parent)
repeat = read(REPORTS / 'root-precision-repeat.json')
assert repeat['status'] == 'PASS' and repeat['identical_npy_files'] == 680
precision = read(REPORTS / 'precision/run_20261017_05/summary.json')
assert precision['status'] == 'PASS_LOCAL_ENGINEERING_PRECISION_RECHECK'
assert sha(ROOT / 'scripts/recheck_precision_20261017.py') == precision['evaluator_sha256']
bind(precision['frozen_source_sha256'])
assert precision['fixed_ffn1_15_inputs']['cases'] == 180
assert precision['fixed_ffn1_15_inputs']['worst_layer_nrmse'] < .03
assert precision['fp32_full_encoder']['classification']['all15_including_synthetic']['agreement_count'] == 15
baseline = read(REPORTS / 'baseline-integrity-python3.log')
assert baseline['status'] == 'PASS' and baseline['frozen_production_files'] == 192
for name in ('round2-cpu-workflow.json', 'round3-precision.json', 'round4-fresh-integration.json'):
    review = read(REPORTS / 'review' / name)
    assert str(review['status']).startswith(('APPROVE', 'PASS')), name
    assert not review.get('blocking_findings', []), name
archive_map = read(REPORTS / 'fresh-package-evidence/SOURCE_MAP.json')
for name, item in archive_map['members'].items():
    assert sha(REPORTS / 'fresh-package-evidence' / name) == item['sha256']
    assert sha(ROOT / item['original_repository_path']) == item['sha256']
changed = subprocess.check_output(['git', 'diff', '--name-only'], cwd=ROOT, text=True).splitlines()
allowed = {'scripts/package_revd_candidate.py', 'scripts/revd_offline_gate.py', 'scripts/revd_offline_reproduce.py',
           'scripts/revd_offline_soc_baseline.py', 'scripts/revd_offline_soc_bindings.py', 'scripts/revd_offline_soc_edges.py',
           'scripts/revd_offline_soc_layers.py', 'scripts/revd_offline_soc_run.py'}
assert set(changed) == allowed, changed
subprocess.run(['git', 'diff', '--check'], cwd=ROOT, check=True)

report_text = '''# KWT 本轮修复、精度复测与交付报告

## 本轮结论

本轮关闭CPU执行文件身份和W2打包命令两项交付缺陷，重新执行精度评估及解压包真实E203验证。本轮没有修改RTL、官方权重、量化尺度或数值模型，没有训练/调参/新性能搜索，没有提交或推送Git。此前六小时时限结束的PARTIAL历史原样保留，本轮接受仅覆盖明确列出的修复与复测。

详细机器证据见[root-acceptance.json](root-acceptance.json)、[独立CPU审查](review/round2-cpu-workflow.json)、[独立精度审查](review/round3-precision.json)和[独立整包审查](review/round4-fresh-integration.json)。正式赛题验收仍待完成。

## 1. 精度是否下降

| 对象 | 本轮实际结果 | 能说明什么 |
|---|---|---|
| INT16 FFN1，15输入×12层 | 180例、4,561,920值；最大逐层聚合NRMSE **0.089307087%**；最大单例 **0.108053%** | 本批算子误差低于3%；不是600样本或端到端INT16分类验收 |
| 原36例独立重算 | 最大层NRMSE **0.093422488%**；Y/raw48/flags与冻结向量全相等 | 原数值模型未回退；与新180例分开统计 |
| 全FP32编码器→同官方分类头 | 15个预测全部与当前官方模型一致；包含人工静音时双方均14/15标签正确 | 本批观察到的分类下降为0个百分点；预测一致不等于标签全正确 |
| 14条真实WAV | 官方和当前C模型均13/14正确；12类test子集均11/12 | 小样本覆盖，不估计总体准确率 |
| 饱和 | X/W/bias/raw48/output32均0 | 本批没有饱和；边界行为另由2170向量覆盖 |

根控独立重复了整个host评估，作者run04与根控run05的680个NPY逐位相同，逐层指标和分类统计相同。独立审查还从保存数组重新计算180例全部误差。见[精度说明](precision/README.md)、[根控重复核验](root-precision-repeat.json)。

本地只有2条真实validation，均为unknown；12类公开test只作检查，不调参数。人工全零静音与公开test中的非零噪声音频是不同输入，因此去重后仍有15个不同波形和encoder输入。正式600样本待验。

历史浮点微差单列：当前评估路径与旧缓存405个选定张量中351个等位；另54个来自两条validation，最大NRMSE约7.578e-7、最大绝对差约7.033e-6，分类均未改变。直接运行未改动的原encoder_export入口又得到与旧缓存81/81等位的结果。已定位为两种host调用路径的微小数值差异，具体内核/内存机制尚未完全隔离；不能将Grappler融合当成已证实的唯一原因。所有误差都使用同一次新图产生的X/Y配对。

## 2. 两个缺陷为何发生、如何解决

### CPU身份门

原offset0门检查了输出、固件、命令和日志，却只返回当前可执行文件SHA，没有将它与独立记录的预期执行文件身份比较。缺陷影响证据可信度，不意味着此前CPU计算已发现错误。

新runner在执行前记录编译产物摘要，成功执行后生成一次性外部binding；只读gate比较报告、执行文件、固件、命令sidecar、日志和创建者身份。缺binding不能补签；新报告不能自报旧helper而降级；非零层对也检查编译身份。三个包装器延迟到最终报告写完才绑定，避免早绑定失效。历史兼容必须显式current=False，且清楚标为历史复用。

22项回归与独立重复均通过。对刚刚实际生成的CPU结果另做1正+4负：正常结果接受，伪报旧creator、错编译摘要、缺binding和替换binary全部拒绝。见[修复说明](cpu_identity/REPORT.md)、[fresh探针](fresh-cpu-probe.json)。

### W2命令生成

打包器复制了full-W的`--sim/--tasks`，但W2内部已固定Verilator和两个任务，parser不接受这些选项。已修复生成源，命令为：

```bash
python3 -B scripts/revd_offline_soc_w2_run.py --stage small
```

最终同一checker已对HEAD旧打包源码重放失败，并对修复源码通过；正确small/full接受，错误sim/tasks/stage继续拒绝。随后从新ZIP解压目录实际执行上述W2命令，两个真实E203小任务的192个Y和192个flags完整写回，根控独立逐word与冻结整数模型比较通过。

此前未关闭这两项，是旧执行时限结束时还缺修复后的完整验证；本轮取得新授权后串行闭合，没有改写旧时限或旧结论。

## 3. 新包实际验收

| 检查 | 结果 |
|---|---|
| 基础交付完整性 | 12,312常规文件、4链接、192冻结源码、9,448既有证据、402阅读链接PASS |
| ZIP解压与manifest | 新manifest与实际源码/归档一致；全新目录、隔离解释器运行 |
| RTL smoke | L1/L2读取延迟各160个完整输出PASS |
| 数值边界 | 2,170向量、52公开core案例、48个shift PASS |
| 默认full-W真实E203 | 2个小冷任务、96个Y及flags，执行到最终共享写响应；严格身份门PASS |
| fresh身份负测 | 1正+4负全部符合预期，原始字节未改 |
| W2真实E203 | 2个小冷任务、192个Y及flags，独立原始输出比较PASS |
| host精度重复 | 180例/4,561,920值；680数组重复位真，独立NumPy审查PASS |

这些是本轮实际新执行的范围，没有重跑完整十二层硬件或官方十二性能任务。原始新运行证据以逐byte副本保存在[fresh-package-evidence](fresh-package-evidence/SOURCE_MAP.json)，保留原始路径和SHA映射；移动后的档案不冒充在新路径执行。

## 4. 当前架构与赛题参数

```text
主机离线预处理/提取输入与参数
        ↓
512KiB共享SRAM ↔ E203控制/搬运 ↔ ICB/MMIO
                                   ├─ INT16 FFN1：99×64 · 64×256+b
                                   └─ FP32编码器：注意力→残差/LN→FFN/GELU→残差/LN，逐层12次
```

RevD是整数FFN1的优化扩展：默认PM4×PN4为16个乘法器，CTX4为四组48位累加上下文，复用同一输入。PM2为8个乘法器；W1/W2分别为单/双权重tile槽。它们不代表完整十二层编码器。完整编码器仍是单头D64、FFN64→256→64、PostNorm，采用顺序共享FP32计算接口。

整数格式为16位X/W、48位累加和bias、最近偶数舍入、32位饱和输出；题目允许自主选择数值格式。共享SRAM实为524288B，每层FP32参数49792word=199168B。编码器内部大块RAM300544B及行暂存2840B与共享容量分开；当前SoC还保留整数FFN1，正式面积必须计入所有保留的新增硬件。当前内部RAM仍未映射指定16bit宏。

| 任务 | 当前状态 |
|---|---|
| 1 点积/转换 | 本地功能与边界证据齐备 |
| 2 FFN1 | 原36完整尺寸案例、12层切参齐备；本轮新增host精度覆盖与RevD短回归 |
| 3 FFN1 SoC/综合 | 真实公开E203联调齐备；generic结构通过；正式工艺综合交付待验 |
| 4 注意力 | 独立公开模式和完整输出本地证据齐备 |
| 5 单层编码器 | 完整PostNorm、两残差、两LN及FFN本地证据齐备 |
| 6 十二层/调度 | 既有15输入RTL和同输入双策略真实CPU本地证据；正式精度/性能待验 |
| 7 综合/性能 | generic结构、周期、访问量可报；正式时序/面积/功耗/能耗待验 |

本科必做为1—3，4—7选做。正式待验包括组委会平台、指定库/内部SRAM宏、有效SDC与映射网表、综合后功能、150MHz、≤2.25mm²、同窗口整SoC功耗/能耗、正式600样本及官方12性能任务。赛题不要求布局布线或流片。

## 5. 优化收益和下一步

本轮优化的是验证可靠性和工程可交付性，没有新增硬件性能收益声明。此前同输入完整十二层的内部交换vsCPU重载对照，端到端周期节省2.158760%、CPU共享事务节省17.436511%；计时初始预载在窗外，不能直接作为正式性能成绩。RevD各候选的既有对照也必须保持相同输入、格式和测量边界，不能拼接不同配置最优值。

下一阶段先确定提交配置并闭合本科第3项：正式平台接口与复位、内部宏组合、指定库映射/SDC、150MHz及面积、综合后功能、完整装载计时与整SoC功耗能耗。精度继续用训练划分标定/验证划分调试；测试集不调参，最终冻结后统一评测。没有这些证据前不估报正式分数。

## 6. 给队友的交付方式

最终ZIP放到`C:\\Users\\11035\\Desktop\\ic\\交付包`，不加入Git。完整工程包保留基础七功能目录与报告，根目录保留当前RevD源码/历史，`extensions/RevD`提供本轮实际解压验证的独立扩展入口。先读ZIP中的`00_交付说明.md`，按基础README安装工具，再从小案例开始；不要用旧PASS代替新运行。

同名SHA-256文件检查整个ZIP，包内DELIVERY_MANIFEST检查每个成员。没有打包虚拟环境或Git历史。历史命令保留原路径，所有新的复现结果应写到新目录。软件源码与报告可继续开发；本轮未自动提交或推送。
'''
report_path = REPORTS / 'REPORT.md'
report_path.write_text(report_text, encoding='utf-8')
evidence = [
    'reports/revd_repair_20261017/REPORT.md', 'reports/revd_repair_20261017/cpu_identity/summary.json',
    'reports/revd_repair_20261017/cpu_identity/green_frozen.json', 'reports/revd_repair_20261017/fresh-cpu-probe.json',
    'reports/revd_repair_20261017/root-precision-repeat.json', 'reports/revd_repair_20261017/precision/run_20261017_05/summary.json',
    'reports/revd_repair_20261017/precision/README.md', 'reports/revd_repair_20261017/precision/run_20261017_04/self_audit.json',
    'reports/revd_repair_20261017/fresh-package-evidence/SOURCE_MAP.json', 'work/revd_repair_20261017/package_state.json',
    'reports/revd_repair_20261017/review/round2-cpu-workflow.json', 'reports/revd_repair_20261017/review/round3-precision.json',
    'reports/revd_repair_20261017/review/round4-fresh-integration.json', state['roundtrip_report'], state['w2_report']]
result = {'status': 'ACCEPTED_LOCAL_REPAIR_AND_PRECISION', 'checked_utc': datetime.now(timezone.utc).isoformat(),
          'root_acceptance': True, 'official_contest_acceptance': False,
          'scope': 'Two delivery defects, current-source fresh extracted package/CPU/W2 checks, and host precision retest only.',
          'closed_findings': ['ROOT-CPU-GATE-IDENTITY-HARDENING-001', 'ROOT-PKG-W2-README-CLI-001'],
          'historical_original_batch_status': 'TIMEBOX_ENDED_PARTIAL', 'old_entire_batch_reaccepted': False,
          'rtl_weights_numeric_model_changed': False, 'git_committed_or_pushed': False,
          'fresh_default_cpu_outputs_and_flags_each': 96, 'fresh_w2_outputs_and_flags_each': 192,
          'cpu_regressions': 22, 'fresh_identity_checks': 5, 'numeric_vectors': 2170,
          'precision_cases': 180, 'precision_values': 4561920, 'repeat_identical_npy': 680,
          'archived_fresh_evidence_files': len(archive_map['members']),
          'verified_archive_sha256': proof['archive_sha256'], 'changed_tracked_files': changed,
          'evidence_sha256': {name: sha(ROOT / name) for name in evidence}, 'acceptor_sha256': sha(Path(__file__))}
(REPORTS / 'root-acceptance.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
(ROOT / 'work/revd_repair_20261017/STATUS.json').write_text(json.dumps({
    'status': 'ACCEPTED_LOCAL_REPAIR_DELIVERY_PACKAGING_PENDING', 'stage': 'external_teammate_zip_packaging',
    'scope': result['scope'], 'acceptance': 'reports/revd_repair_20261017/root-acceptance.json',
    'official_contest_acceptance': False, 'persistent_runner_started': False}, indent=2) + '\n', encoding='utf-8')
(ROOT / 'work/revd_current.json').write_text(json.dumps({
    'latest_scoped_repair': 'reports/revd_repair_20261017/root-acceptance.json',
    'report': 'reports/revd_repair_20261017/REPORT.md', 'prior_batch_snapshot': 'work/revd_offline_20261017/ROOT_FINAL.json',
    'prior_batch_rewritten': False, 'official_contest_acceptance': False}, indent=2) + '\n', encoding='utf-8')
print('ROOT_ACCEPTED_LOCAL_REPAIR_AND_PRECISION', flush=True)

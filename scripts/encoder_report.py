"""Render evidence-derived local-draft report; never promote missing checks."""
from pathlib import Path
import datetime as dt
import csv,hashlib,json,os,re
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'reports/encoder/verification/report.md'
def load(rel,default=None):
 path=ROOT/rel
 return json.loads(path.read_text(encoding='utf-8-sig')) if path.exists() else ({} if default is None else default)
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def link(rel,label=None):
 path=ROOT/rel
 return f'[{label or rel}]({Path(os.path.relpath(path,OUT.parent)).as_posix()})' if path.is_file() else f'{label or rel}（待生成）'

def cpu_timing(name,record,stats):
 folder=ROOT/'reports/encoder/system'/name;log=folder/'simulation.log'
 if sha(log)!=record['log_sha256']:raise ValueError('CPU timing log differs from accepted evidence')
 text=log.read_text(encoding='utf-8')
 loads=[tuple(map(int,x)) for x in re.findall(r'HOST_LAYER_LOAD layer=(\d+) words=(\d+) begin=(\d+) end=(\d+) cycles=(\d+)',text)]
 starts=[tuple(map(int,x)) for x in re.findall(r'CPU_ENCODER_START layer=(\d+) cycle=(\d+)',text)]
 if len(loads)!=12 or len(starts)!=12 or [x[0] for x in loads]!=list(range(12)) or [x[0] for x in starts]!=list(range(12)):raise ValueError('CPU timing requires twelve actual host loads and starts')
 rows=[]
 for i,load in enumerate(loads):
  layer,words,begin,end,elapsed=load;start=starts[i][1]
  next_boundary=loads[i+1][2] if i<11 else stats['final_write_cycle']+1
  if words!=49792 or elapsed!=49792 or end-begin!=elapsed or not begin<end<=start<next_boundary:raise ValueError('invalid CPU timing boundaries')
  rows.append({'layer':layer,'host_load_cycles':elapsed,'parameter_ready_to_start_cycles':start-end,
               'start_to_next_request_or_final_write_cycles':next_boundary-start})
 initial=loads[0][2]-stats['begin_cycle']
 total=initial+sum(sum(r[k] for k in ('host_load_cycles','parameter_ready_to_start_cycles','start_to_next_request_or_final_write_cycles')) for r in rows)
 if initial<0 or total!=stats['end_to_end_cycles']:raise ValueError('CPU disjoint timing components do not sum to measured endpoint')
 return {'status_sha256':sha(folder/'status.json'),'log_sha256':sha(log),'initial_mmio_to_first_host_request_cycles':initial,
         'host_load_cycles':sum(r['host_load_cycles'] for r in rows),
         'parameter_ready_to_start_cycles':sum(r['parameter_ready_to_start_cycles'] for r in rows),
         'start_to_next_request_or_final_write_cycles':sum(r['start_to_next_request_or_final_write_cycles'] for r in rows),
         'command_backpressure_cycles':stats['bus_waits'],'end_to_end_cycles':total,'layers':rows,
         'scope':'Disjoint observed boundaries. START-to-next-request includes neural compute, CPU/ICB response waiting, output readback and layer control; command backpressure is only cmd_valid&&!cmd_ready.'}

def rtl_cycles(full):
 rows=[];cases=[]
 for item in full:
  record=load(item['record']);log=ROOT/Path(item['record']).parent/'simulation.log'
  if sha(log)!=record['log_sha256']:raise ValueError('RTL cycle log differs from accepted evidence')
  measured=re.findall(r'ENCODER_LAYER_PASS layer=(\d+) words=(\d+) cycles=(\d+) flags=([0-9a-f]+)',log.read_text(encoding='utf-8'))
  if len(measured)!=12 or [int(r[0]) for r in measured]!=list(range(12)):raise ValueError('RTL layer timing coverage incomplete')
  total=0;flags=0
  for layer,words,cycles,bits in measured:
   rows.append({'reference':item['reference'],'case':item['case'],'layer':int(layer),'words':int(words),'compute_cycles':int(cycles),'flags_hex':bits,'status_record':item['record']})
   total+=int(cycles);flags|=int(bits,16)
  cases.append({'reference':item['reference'],'case':item['case'],'layers':12,'words':record['output_words'],'compute_cycles':total,'flags_hex':f'{flags:02x}','wall_seconds':record['wall_seconds'],'output_sha256':record['output_sha256'],'status_sha256':sha(ROOT/item['record'])})
 for name,data,fields in [('rtl-layer-results.csv',rows,['reference','case','layer','words','compute_cycles','flags_hex','status_record']),('rtl-case-results.csv',cases,['reference','case','layers','words','compute_cycles','flags_hex','wall_seconds','output_sha256','status_sha256'])]:
  with (OUT.parent/name).open('w',encoding='utf-8',newline='') as handle:
   writer=csv.DictWriter(handle,fieldnames=fields);writer.writeheader();writer.writerows(data)
 return {(r['reference'],r['case']):r for r in cases}
def main():
 gate=load('reports/encoder/verification/gate.json');state=load('work/encoder_status.json')
 tasks=gate.get('tasks',{f'task{i}':False for i in range(1,8)})
 titles=['乘累加与数值处理','前馈线性加速器','前馈SoC集成与generic综合','独立单头注意力','单层编码器','十二层与参数调度','编码器综合与性能分析']
 lines=['# 正式七项本地初稿验证报告','',
        '此报告只统计完成门已经核对的当前源码证据。正式比赛平台、工艺/SRAM库、门级时序和600样本验收单列外部待验。',
        '',f'生成时间：{dt.datetime.now(dt.timezone.utc).isoformat()}。当前状态：**{state.get("status","INCOMPLETE")}**；通过本地门 {sum(bool(x) for x in tasks.values())}/7。',
        '', '| 项 | 本地交付 | 当前完成门 |','|---|---|---|']
 for i,title in enumerate(titles,1):lines.append(f'| {i} | {title} | {"PASS" if tasks.get("task"+str(i)) else "未通过，见门禁缺口"} |')
 lines+=['',f'唯一完成状态：{link("work/encoder_status.json")}；逐项检查和缺口：{link("reports/encoder/verification/gate.json")}。旧源 PASS 不重新绑定到新源；修复后重新执行受影响验证。',
         '', '## 数据、数学与位真边界','',
         '输入是官方离线预处理后的完整99×64序列。RTL先生成全部K/V，逐query计算Q、score×0.125、稳定Softmax、context、Wo与偏置，再做两次残差/PostNorm和FFN。每层所有6336个输出必须验证，不能只验证CLS。生产CPU仅搬运、发命令、逐层加载参数和读回。',
         '', '独立C参考固定逐操作binary32舍入和左到右FMA顺序；RTL必须逐word零差。官方GELU为erf，初稿采用冻结的tanh近似；与官方模型的误差和分类变化单独报告，不混作位真门。',
         '', '| 参考批次 | 输入 | 完整层 | 层输出word | 最大最终NRMSE | 与官方预测相同 |','|---|---:|---:|---:|---:|---:|']
 for rel,label in [('reports/encoder/reference/manifest.json','原三输入'),('reports/encoder/reference-test12/manifest.json','公开test十二类工程子集')]:
  m=load(rel);s=m.get('summary',{})
  lines.append(f'| {label} | {s.get("full_cases","待验")} | {s.get("full_layers","待验")} | {s.get("full_output_words","待验")} | {s.get("max_final_nrmse","待验")} | {s.get("same_prediction_count","待验")} |')
 lines+=['', '原三输入为两个真实unknown音频及合成零静音；公开test十二类按类别抽取，不按预测正确性筛选。预测与官方相同不等于分类正确，十二类工程覆盖也不构成600样本Top1结论。',
         '',f'来源、162张量/607308参数、49792word逐层打包及全部bin/NPY/hex回读：{link("work/encoder_reference_handoff.json")}；模型语义：{link("reports/encoder/research/model-semantics.md")}。',
         '', '## 当前冻结源的RTL覆盖','',
         '| 参考批次 | 输入 | 完整层 | 输出word | 计算周期合计 | flags | 输出SHA-256 |','|---|---|---:|---:|---:|---|---|']
 full=gate.get('details',{}).get('full_cases',[])
 measured=rtl_cycles(full)
 if not full:lines.append('| 当前冻结源 | 尚无完成记录 | 0 | 0 | 待验 | 待验 | 待实际运行结束并过门 |')
 for item in full:
  r=load(item['record']);timing=measured[(item['reference'],item['case'])]
  lines.append(f'| {item["reference"]} | {item["case"]} | {r.get("layers",0)} | {r.get("output_words",0)} | {timing["compute_cycles"]} | {timing["flags_hex"]} | `{r.get("output_sha256","")}` |')
 lines+=['',f'实际逐层数据：{link("reports/encoder/verification/rtl-layer-results.csv")}；逐例汇总与输出摘要：{link("reports/encoder/verification/rtl-case-results.csv")}。计算周期只统计core busy区间；CPU端到端周期另含装载、等待、换层和写回，不能直接混用。']
 lines+=['', '完整案例的每层都通过公开READ_Y握手读出6336word，并独立再次比较输出文件。首个原始输入还核对全部14阶段；独立新进程repeat必须与基准输出哈希相同。阶段trace是旁路证据，实际功能读回仍由公开接口完成。',
         '', '小尺寸3×4×8保留0.125缩放，随机/全零两组在Icarus和Verilator交叉；非线性各2030向量含±0、次正规、截断边界、非法域、背压和内部复位中断。source绑定和当前通过范围只由完成门确认。',
         '', '## 真实E203、512KiB与参数流量','',
         '公开E203同时保留FFN1的0x11000000窗口和encoder的0x11010000窗口。共享SRAM基址0xa0000000，输入偏移0x1000、单层权重0x8000、输出0x40000。49792word权重占199168B；十二层encoder参数共2390016B，逐层提供，不能宣称全部常驻512KiB。',
         '', 'host仅在CPU请求层号后写公开共享RAM参数区，每word耗一个真实仿真周期；CPU再通过生产driver搬入MMIO。TB不写encoder内部RAM，不代发CPU总线，不执行神经算术。WAIT_DONE持有真实CPU读事务直到完成或fault，40M拍watchdog；普通STATUS保持即时可读。',
         '', '本地整机覆盖为同一输入的两种策略各一次完整12层任务；其余输入的硬件覆盖见RTL表。组委会目标平台的正式十二项整机性能评测单列待验。',
         '', '| 策略 | 实际输入 | 当前记录 | CPU写回word | 被动核对神经word | 实测统计 |','|---|---|---|---:|---:|---|']
 for label,name in [('内部pingpong','pingpong'),('外部readback/reload','reload')]:
  r=load(f'reports/encoder/system/{name}/status.json')
  valid='cpu_'+name in gate.get('details',{})
  lines.append(f'| {label} | {r.get("case","待验") if valid else "待完成记录"} | {"PASS" if valid else "待完成/待过门"} | {r.get("output_words","待验") if valid else "待验"} | {r.get("neural_words","待验") if valid else "待验"} | {link(f"reports/encoder/system/{name}/status.json","记录")} |')
  if valid:lines+=['',f'`{r["summary"]}`','']
 comparison=gate.get('details',{}).get('reuse_comparison')
 if comparison:lines+=['',f'同输入逐层及最终位真一致；外部重载减内部交换：CPU侧共享SRAM事务差={comparison["saved_shared_transactions"]}，端到端周期差={comparison["saved_cycles"]}。这些是当前实现算例，不外推工艺PPA。']
 else:lines+=['','正式复用比较已获三要素放行，但只有两种策略的完整真实CPU任务都完成、输出逐位相同后才报告收益。当前没有可发布的正式收益数值。']
 if comparison:
  timings={name:cpu_timing(name,*gate['details']['cpu_'+name]) for name in ('pingpong','reload')}
  metrics={};traffic={}
  for name in ('pingpong','reload'):
   stats=comparison[name];cpu=stats['shared_reads']+stats['shared_writes'];events=len(timings[name]['layers'])
   traffic[name]={'cpu_shared_reads':stats['shared_reads'],'cpu_shared_writes':stats['shared_writes'],
                 'cpu_shared_transactions':cpu,'cpu_shared_word_bytes':cpu*4,
                 'host_parameter_writes':stats['host_words'],'host_ready_writes':events,'host_request_reads':events,
                 'model_shared_transactions':cpu+stats['host_words']+2*events,
                 'model_shared_word_bytes':(cpu+stats['host_words']+2*events)*4,'end_to_end_cycles':stats['end_to_end_cycles']}
  for key,label in [('cpu_shared_reads','CPU侧共享SRAM读事务'),('cpu_shared_writes','CPU侧共享SRAM写事务'),('cpu_shared_transactions','CPU侧共享SRAM总事务'),('cpu_shared_word_bytes','CPU侧32位字事务折算字节'),('host_parameter_writes','Host参数写word'),('host_ready_writes','Host ready写word'),('host_request_reads','Host请求层号读word'),('model_shared_transactions','CPU与供参host逻辑共享SRAM事务合计'),('model_shared_word_bytes','CPU与供参host逻辑32位字节合计'),('end_to_end_cycles','端到端周期')]:
   values={name:traffic[name][key] for name in ('pingpong','reload')}
   base=values['reload'];delta=base-values['pingpong']
   metrics[key]={'label':label,**values,'saved':delta,'saved_fraction_of_reload':delta/base if base else None}
  performance=ROOT/'reports/encoder/verification/performance.json'
  performance.write_text(json.dumps({'source_sha256':sha(Path(__file__)),'policies':timings,'comparison':metrics},indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
  lines+=['','| 指标 | 内部pingpong | 外部reload基准 | 节省绝对值 | 相对reload节省比例 |','|---|---:|---:|---:|---:|']
  for metric in metrics.values():
   fraction=metric['saved_fraction_of_reload'];ratio=f'{fraction:.6%}' if fraction is not None else '基准为0，未定义'
   lines.append(f'| {metric["label"]} | {metric["pingpong"]} | {metric["reload"]} | {metric["saved"]} | {ratio} |')
  lines+=['','CPU侧按sysmem实际握手计数，包含控制/参数/激活访问。Host参数写由实际写循环计数；每个已完成HOST_LAYER_LOAD事件在冻结TB中包含一次请求层号读和一次ready写，控制访问由这些事件回收。Host访问不是CPU ICB握手。逻辑合计仅含同一计时边界内CPU与供参host，不含复位前fixture预置、encoder内部RAM或被动核验探针；不冒称物理SRAM端口或逐byte掩码测量。差值为reload减pingpong，比例分母采用对应reload口径。']
  lines+=['','| 真实周期分段 | 内部pingpong | 外部reload |','|---|---:|---:|']
  for key,label in [('initial_mmio_to_first_host_request_cycles','首个MMIO至首层host请求（含输入搬运）'),('host_load_cycles','十二层host参数供给'),('parameter_ready_to_start_cycles','参数就绪至START（CPU检查、参数搬运和总线）'),('start_to_next_request_or_final_write_cycles','START至下一次请求/最终写回（计算、CPU/ICB等待、读回和换层）'),('end_to_end_cycles','端到端合计'),('command_backpressure_cycles','另列：ICB命令端背压')]:
   lines.append(f'| {label} | {timings["pingpong"][key]} | {timings["reload"][key]} |')
  lines+=['',f'四段互不重叠，逐层时间戳及摘要绑定见 {link("reports/encoder/verification/performance.json")}。响应等待已包含在START后的区段，未冒充单独测量；bus_waits只统计命令端背压。仿真时钟激励不代表工艺时序达标。']
 lines+=['',f'放行与一致边界：{link("work/MASTER_RELEASE_encoder_reuse.md")}。计时从首个MMIO到最终完整输出写回，含输入搬运、按层host/CPU参数加载、CPU/ICB等待和调度；离线预处理与主机分类头排除。host加载起止、MMIO读写、共享SRAM读写、真实cycle均在日志记录。',
         '', '## 负测、源码与实际执行绑定','',
         '完成门拒绝陈旧源码、失败子进程、--help/no-op与旧PASS拼接、部分层/输出、错误数据、零周期和不同binary。实际执行必须携带本轮run_id、开始/结束时间；显式历史复用必须重新核对全部来源和产物。',
         '', '协议覆盖连续装载/缺载拒绝、忙时拒绝、地址/掩码/类型错误、响应背压、同步读、层号和换层次序。定向复位覆盖计算中、同步读等待和未消费响应；故障后完整重装可以恢复。溢出保留真实overflow/inexact，不丢当前异常，也不把终止故障伪装成额外IEEE invalid。',
         '', '错误ICB响应、错误attention scale、LN偏置和漏末token均由可编译变异验证；错误算法必须在真实仿真中因独立逐word比较失败。门禁单测另覆盖删日志/向量/design、替换输出/binary、假本轮身份。',
         '',f'当前短测：{link("reports/encoder/verification/checks/status.json")}；算术变异：{link("reports/encoder/verification/mutations/status.json")}；FP32冷启动修复：{link("reports/encoder/fp32/cold-revalidation.md")}。',
         '',f'冻结清单：{link("work/encoder_source_freeze.json")}。各实际case记录source/input/compiled-source/binary/build-key/结果/日志SHA，CPU另存ELF、map、反汇编、固件image及neural-output。所有需要引用的文件在首次运行后才进入完成门。',
         '', '## Generic结构与正式外部待验','',
         f'完整encoder结构及同步RAM：{link("reports/encoder/synthesis/status.json")}；完整E203/原FFN1/encoder/共享RAM层级：{link("reports/encoder/synthesis/soc/status.json")}。共享存储的数据进程不含复位，响应状态单独复位。generic综合检查不是工艺映射。',
         '', 'EXTERNAL_PENDING：组委会定制E203平台与接口确认、工艺和SRAM库、150MHz时序、物理面积、功耗/能量、综合后门级时序仿真、官方600样本与Top1下降≤2个百分点，以及目标平台正式十二项整机性能评测。未生成面积、频率或功耗达标数值。',
         '', '## 初学者入口与一键复现','',
         f'先读 {link("docs/encoder/README.md","入门说明")} 和 {link("docs/encoder/interface.md","接口契约")}，再追踪同步RAM、FP32请求响应、非线性微程序及core phase。',
         '', '在Ubuntu-24.04 WSL、工程根目录运行：','', '```bash',
         'bash scripts/run_formal_seven.sh --reuse-verified','```','',
         '该入口逐项核对可复用历史证据；缺失或过期时执行真实回归。当前源码的短测通过后才冻结，随后运行原3+公开12类各十二层、独立repeat和真实CPU两策略。统一命令最后必须退出0，不能从本说明推断当前已经通过。',
         '',f'统一命令与实际退出记录：{link("reports/encoder/verification/unified/commands.json")}；有限案例批次进度：{link("reports/encoder/verification/case-batch/progress.json")}。',
         '', '自测：为何不同时保存十二层权重？答案：encoder十二层权重约2.39MB，超过512KiB，必须逐层调度。自测：为何不能把旧报告改成新源码哈希？答案：新源码尚未产生那份运行输出，哈希替换会切断执行与产物的证据链，必须重验受影响路径。',
         '',f'独立审查与修复记录：{link("reports/encoder/verification/review.json")}。未通过项保持false；最终本地接受仍由总控独立复核，正式外部待验不升级为通过。','']
 freeze=load('work/encoder_source_freeze.json')
 lines+=['## 工具与执行边界','','| 工具 | 冻结时实际版本 |','|---|---|']
 for name,version in freeze.get('toolchain',{}).items():lines.append(f'| {name} | {version} |')
 lines+=['', 'CPU沿用共同启动环境的 `-Diverilog -DDISABLE_SV_ASSERTION=1`，上游条件SVA未启用。验证依据是实际CPU执行、测试台显式fatal、握手/完整输出核对、独立参考和负测；不据此声称运行了上游全部SVA或获得CPU形式化认证。两种策略使用相同Verilator/C++ O3选项和仿真时钟。',
         '',f'逐阶段误差、GELU近似误差和原模型对照：{link("reports/encoder/reference/VERIFICATION.md")}；十二类逐层指标：{link("reports/encoder/reference-test12/manifest.json")}。这些指标来自数值参考，硬件逐位验收另见前文。',
         '', '| 任务 | 实际命令和日志 | 来源与产物指纹 |','|---|---|---|']
 for name,directory in [('RTL原始首例','reports/encoder/rtl/full/original-0'),('独立重复','reports/encoder/rtl/repeat'),('CPU内部交换','reports/encoder/system/pingpong'),('CPU外部重载','reports/encoder/system/reload')]:
  lines.append(f'| {name} | {link(directory+"/commands.jsonl","命令")}；{link(directory+"/simulation.log","逐层日志")} | {link(directory+"/status.json","摘要与SHA-256")} |')
 lines+=['','固件文件以每个CPU目录内的 `firmware.elf`、`firmware.map`、`firmware.bin`、`firmware.hex` 和 `firmware-disassembly.log` 保存；ELF、实际binary、输入权重、输出及日志SHA均在对应status记录。所有生成兼容源、实际导入源与编译选项绑定到运行记录，HardFloat vendor保持只读。','']
 lines+=['日志中的instructions是IFU向执行级交付的有效握手计数，不作为退休指令计数。bus_waits仅是ICB命令端背压；完成读的响应等待包含在真实端到端周期及START后区段内。','']
 lines+=['测试台在复位前把初始输入预置到共享RAM，这次host预置不计仿真周期；计时包含CPU把6336word搬入encoder。每层host权重供给实际耗一word/周期并计入；离线预处理、初次文件读取和软件分类头排除。固件rdcycle区间从各层参数就绪之后开始，本表使用测试台端到端边界，不把两者混称同一延时。','']
 lines+=['CPU暂存的input/expected、十二层weights目标与内容，在最终门与冻结参考核对；bin/hex由已绑定ELF重新objcopy派生并逐byte比较，BYTES及命令记录也交叉核验。摘要在gate的verified_runtime_artifacts_sha256中。这些是验收时回读摘要；冻结runner没有为暂存副本单独保存运行前/后快照，未补造该类历史记录。canonical参考和生产来源的前后绑定仍按原运行记录验证。','']
 reference=load('reports/encoder/reference/manifest.json');numerics=reference.get('nonlinear_validation',{})
 lines+=['## 近似误差与工程子集分类','','| 数值检查 | 点数 | 误差 |','|---|---:|---|']
 for name,title,metric in [('exp','exp_neg与double exp','max_relative'),('gelu_vs_exact_erf','tanh GELU与精确erf','max_abs')]:
  r=numerics.get(name,{})
  lines.append(f'| {title} | {r.get("count","待验")} | {metric}={r.get(metric,"待验")} |')
 test12=load('reports/encoder/reference-test12/manifest.json');labels=test12.get('labels',[])
 lines+=['', '以下分类来自冻结数值参考与原模型。硬件案例通过完整位真门后，其encoder输出与该参考一致；未过门的硬件案例不因此获得分类验证。',
         '', '| 样本 | 真实标签 | 参考预测 | 官方预测 | 最终输出NRMSE |','|---|---|---|---|---:|']
 for r in test12.get('samples',[]):
  idx=r.get('official_predicted_index');official=labels[idx] if isinstance(idx,int) and idx<len(labels) else idx
  lines.append(f'| {r["sample_id"]} | {r.get("ground_truth_label")} | {r.get("predicted_label")} | {official} | {r.get("final_comparison",{}).get("nrmse")} |')
 lines+=['','当前公开工程子集silence的官方和参考预测均为unknown，其余11项与标签一致；该事实描述不构成正式准确率估计。','']
 OUT.parent.mkdir(parents=True,exist_ok=True);OUT.write_text('\n'.join(lines),encoding='utf-8')
 text=OUT.read_text(encoding='utf-8')
 if '\ufffd' in text or len(text)<200:raise ValueError('UTF8 report readback failed')
 for target in re.findall(r'\]\(([^)]+)\)',text):
  if not target.startswith(('http://','https://','#')) and not (OUT.parent/target).resolve().is_file():raise ValueError('report link missing: '+target)
 write=ROOT/'reports/encoder/verification/report-artifact.json'
 derived={p.name:sha(p) for p in [OUT.parent/'rtl-layer-results.csv',OUT.parent/'rtl-case-results.csv',OUT.parent/'performance.json'] if p.is_file()}
 write.write_text(json.dumps({'report_sha256':sha(OUT),'generator_sha256':sha(Path(__file__)),'gate_sha256':sha(ROOT/'reports/encoder/verification/gate.json') if (ROOT/'reports/encoder/verification/gate.json').exists() else None,'utf8_readback':True,'all_local_links_exist':True,'derived_sha256':derived},indent=2)+'\n',encoding='utf-8')
 print('ENCODER_REPORT_UTF8_READBACK_OK')
if __name__=='__main__':main()

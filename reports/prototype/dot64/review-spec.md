# DOT64 规格审查

审查日期：2026-10-15。结论：DOT64 在本次批准的单MAC整数功能规格内通过；可作为FFN1调度模块的计算子模块。此文件只核对DOT64规格与已有实际证据，质量审查由其他审查者独立完成，不代表完整FFN1或比赛系统验收。

本次只读取既有RTL、接口、报告、XML及哈希，新增本审查文件；没有修改RTL、runner、测试或既有证据，也没有重复运行测试。

## 规格与实现逐项核对

|检查项|实现与实际覆盖|结论|
|---|---|---|
|单MAC、固定长度64|`rtl/dot64.sv`只有一处`in_x * in_w`乘法表达式；COLLECT状态中每个已接受输入累加一次，计数0..63|通过|
|输入与乘积符号|X/W为signed16，乘积为signed32，再按乘积符号位扩展为48位；极值、正负和抵消用例比对|通过|
|点积累加范围|64项16×16乘积的最大总和为68,719,476,736，最小总和为-68,717,379,584，均适配signed48；点积期间不加入偏置|通过|
|偏置处理|任务启动捕获signed48偏置；64项累计完成后使用49位临时和相加，显式比较signed48上下界|通过|
|raw48溢出|超界先饱和为`2^47-1`或`-2^47`，`out_overflow=1`；正负溢出均有实际测试|通过|
|先点积、后偏置|点积结束才相加；新增极大偏置配正负抵消乘积的用例，避免提前偏置饱和损坏最终值|通过|
|输出数值归属|RNE与signed32饱和都在RTL内，未移动至测试平台；Python只计算独立期望值|通过|
|RNE规则|取raw48的49位绝对值，求商与余数；超过半值进位、等于半值且商奇数才进位，最后恢复符号|通过|
|负值与最小值|绝对值中间量49位，可容纳abs(-2^47)；正负3/5半值、正负1半值、最小signed48均有定向测试|通过|
|输出饱和|RNE后比较signed32上下界；`out_saturated`只指输出转换饱和，与raw48溢出独立|通过|
|shift范围|合法0..47；0不做舍入移位，47测试半值和最小负数；48/63明确拒绝并回错误结果|通过|
|复位|异步低有效复位清状态、累加和结果；输入中途及结果等待期间分别复位，然后重新运行完整任务|通过|
|可综合编码边界|无浮点、仿真答案查表、force、层次RAM写入；状态机、寄存器及整数组合逻辑通过严格Verilator lint|通过，尚未实际综合|

输出计算顺序固定为：64项乘积求和 → 加48位偏置（49位临时值）→ sat48并保存overflow → 右移RNE → sat32并保存saturated。若raw48已溢出，输出转换消费饱和后的raw48，overflow仍保留，不允许回绕。

## 冻结接口与周期

接口原文为`dv/dot64/README.md`，机器交接为`work/dot64_handoff.json`。

|接口|冻结约定|核验|
|---|---|---|
|`start_valid/start_ready`|仅IDLE可握手；启动沿捕获`start_bias[47:0]`、`start_shift[5:0]`|连续任务与配置捕获用例通过|
|`in_valid/in_ready`|仅COLLECT可握手；`in_x/in_w`各signed16；恰好64次|首尾项、停顿、额外第65项用例通过|
|启动沿操作数|启动沿不接收第一对数据；启动后ready才有效|驱动及状态实现一致|
|结果时延|第64对接受沿更新最终点积；其后下一上升沿进入OUTPUT并置out_valid|最终测试严格要求下一拍产生结果，不能宽松等多拍|
|`out_valid/out_ready`|握手消费结果；out_valid未消费期间，data/raw/全部标志保持|7周期随机任务反压及其他定向保持用例通过|
|结果位宽|`out_data` signed32、`out_raw` signed48；`out_overflow/out_saturated/out_error`各1位|全部52个结果事务按位期望比对|
|`busy`|COLLECT、FINALIZE、OUTPUT均为1；结果反压时仍为1|反压与复位用例检查|
|非法shift|启动后直接产生out_error=1，data/raw/overflow/saturated均0，不接收操作数|48/63拒绝、错误保持与后续合法任务通过|
|忙时新start或额外输入|ready为0，无握手，忽略；不污染当前任务|定向用例通过|
|消费与下一任务|消费结果沿回IDLE，随后start_ready为1，下一拍可接新start；不支持消费沿同时接start|连续任务实测通过|
|复位交互|复位优先于握手，中止任务；外部复位期间不把ready当作已完成事务；解除后重新start并送完整64项|状态与复位用例一致|

FFN1适配者必须按ready握手，不能把保持多个周期的valid误当作仅一次事务。结果等待期间应读取有效输出并由out_ready明确消费；错误结果同样需要消费才能返回空闲。

## TDD与结果事务核对

测试先于生产实现编写。协议兼容但结果恒零的错误DUT已真实运行：8个测试、8个失败、0通过、退出码1。首例674ns报告期望`(-8,-8,0,0,0)`、实际`(0,0,0,0,0)`，属于功能断言失败，不是环境导入或编译失败。

RED证据：`red.log`、`red-results.xml`、`red-fixture.sv`、`red-status.json`。最终GREEN证据：`run.log`、`results.xml`、`status.json`。

|测试组|完整比较结果数|主要边界|
|---|---:|---|
|手算与恰好64项|2|-8手算、仅第64项非零|
|RNE与shift边界|12|正负半值、0、47、最小signed48|
|乘积极值、bias49与饱和|14|正负raw溢出、int32边界、RNE跨饱和边界、偏置顺序|
|随机输入停顿与输出反压|12|seed20261015，正负16位全范围、48位偏置、shift0..47随机取值|
|连续任务与配置捕获|6|启动后外部bias/shift改变不能污染任务|
|非法shift及恢复|4|2个错误结果、2个后续合法结果|
|复位中止与恢复|1|另有1个输入中途任务和1个未消费结果被复位中止|
|未接受输入及start|1|空闲输入、忙时start、第65对|
|合计|52|8组全部通过、0失败、0跳过|

Python期望值使用任意精度整数、显式饱和边界和`divmod`，不调用生产数值模型；未以NumPy固定宽度自然溢出复制硬件行为。

## 实际命令、哈希与波形

已执行命令（从`/tmp`工作目录运行，证明不依赖调用目录）：

```powershell
wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash '/mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_dot64.sh'
```

最后一次GREEN退出码0，8/8通过、0跳过，总仿真时间46866.01ns；Icarus Verilog 12.0为实际仿真器，Verilator 5.020的`--lint-only --Wall`严格检查退出码0。

本审查再次只读核对：`status.json`登记的RTL、测试、runner、波形检查器、XML、FST及VCD哈希均与当前文件匹配；GREEN XML确有8个testcase、0个failure/error、0个skipped，RED XML有8个testcase、8个failure/error。

冻结RTL SHA256：`7abcca0b102c351a0c8979a8b2ed7c131e79f44f672aec2aa039862d8986bccc`。

波形文件为`build/dot64.fst`、`dot64.vcd`。`dv/dot64/inspect_wave.py`独立解析真实VCD：首事务恰好64个输入握手后，于669000ps首次产生`out_raw=-8`、`out_data=-8`，out_error/out_overflow/out_saturated均0。此结果同时保存在`status.json.waveform_check`。

runner每次开始立即使旧PASS失效，缺虚拟环境、lint/编译错误、测试失败/跳过/漏组、波形缺失或波形检查失败均使入口非零退出。最终状态与本次XML、波形及源码哈希绑定。

## 适用边界与剩余限制

- 无未解决的DOT64功能规格阻塞项，可供完整FFN1集成；仍需完整矩阵公开装载、存储时序和逐行读回验证。
- 此测试通过证明整数算术与协议符合本版规格，不证明量化后与官方浮点模型的NRMSE；误差评估属于数值模型及完整矩阵验证。
- 12个随机任务与定向边界不等于所有输入穷举；shift范围由RTL统一实现，但本回归没有穷举每个合法shift和全部数据组合。
- 既有cocotb/Icarus启动日志`Log message construction failed: (error code) -1`以及WSL localhost代理警告仍存在；保留原日志，功能与波形检查均通过。
- 未打开GUI、未运行综合/PPA，也未进行E203平台集成；不能据此宣称150MHz时序、面积或正式比赛验收通过。

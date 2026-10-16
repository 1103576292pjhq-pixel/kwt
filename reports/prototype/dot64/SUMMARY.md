# DOT64 首版验证结果

状态：PASS。8个cocotb测试全部通过，0失败、0跳过；Icarus Verilog 12.0为真实仿真器，Verilator 5.020只做严格`--lint-only --Wall`，退出码均0。接口固定在`dv/dot64/README.md`，可供完整FFN1复用。

## 测试先失败，再实现

先编写完整8组独立整数期望测试，再建立协议兼容、结果恒零的错误DUT：8组真实失败、0通过、退出码1。第一组在674ns得到期望-8、实际0的功能断言，证明不是因导入或编译错误而失败。证据：`red.log`、`red-results.xml`、`red-fixture.sv`、`red-status.json`。之后替换为生产RTL，运行全部测试通过。后续加入更严格的单拍完成时延、临界舍入饱和和先点积后偏置用例，再次全部通过。

## 实现与覆盖

一个16×16有符号乘法表达式，每个输入握手累计一个乘积，48位点积累加器接受恰好64项。第64项明确计入后，下一拍以49位求和加偏置，先sat48及报告overflow，再以对称绝对值算法进行正负RNE、sat32。非法shift立即产生独立error结果。所有输出由寄存器保持，消费者等待时不接受新start或操作数。异步低复位中止任务并清输出。

8组覆盖：

1. 手算-8、只有第64项非零、结果反压。
2. 正负半值最近偶数、shift0、shift47及最小signed48绝对值。
3. 输入16位极值、49位正负bias溢出、sat32精确边界和舍入跨边界、乘积抵消、避免偏置提前相加造成中间饱和。
4. 固定seed20261015的12组随机任务，输入停顿和输出等待。
5. 连续6任务、start后外部偏置/shift改变不能影响已捕获配置。
6. shift48/63拒绝并持稳错误，再接受合法任务。
7. 17项输入后异步复位、已出结果未消费时复位、重启完整点积。
8. 空闲乱送输入、忙时start、64项后多送输入均没有握手，不能污染结果。

独立Python参考使用任意精度整数、`divmod`及显式边界，未调用生产数值模型。累计比较52个完整结果事务，另有1个未消费结果经复位丢弃和1个输入中途复位事务。

## 执行与证据

在Windows任意目录执行：

```powershell
wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash '/mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_dot64.sh'
```

最后一次退出码0，总仿真时间46866.01ns；`results.xml`与`run.log`为本次8/8通过记录，`status.json`记录RTL、测试、XML和波形SHA256。入口立即使旧PASS失效，缺虚拟环境、编译/lint错误、失败/跳过/测试数不为8、缺波形或波形核验失败均非零退出。

`build/dot64.fst`和`dot64.vcd`包含真实仿真信号。独立VCD读取器核对首事务恰好64个输入握手后，在669000ps首次产生`out_raw=-8`及`out_data=-8`，错误/饱和/溢出均0；细节以本次`status.json.waveform_check`为准。

## 限制

现有cocotb/Icarus启动仍有非致命`Log message construction failed: (error code) -1`日志，与前期环境验收一致；测试及波形均真实通过。WSL还会打印既有localhost代理警告。未运行GUI、综合或PPA，不能据此宣称150MHz时序或面积达标。

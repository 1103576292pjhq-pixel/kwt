# DOT64 接口契约

模块 `rtl/dot64.sv`，单时钟、异步低有效复位。所有握手只在上升沿发生，信号在上升沿前稳定。

|端口|方向/位宽|约定|
|---|---|---|
|`clk`, `rst_n`|输入1|时钟、异步低有效复位|
|`start_valid`, `start_ready`|输入/输出1|两者为1时捕获新任务，仅空闲可接收|
|`start_bias`|输入signed48|捕获后不受外部变化影响|
|`start_shift`|输入6|0..47合法；48..63直接产生错误结果|
|`in_valid`, `in_ready`|输入/输出1|合法任务接收恰好64次握手|
|`in_x`, `in_w`|输入signed16|握手时捕获一对操作数|
|`out_valid`, `out_ready`|输出/输入1|结果保持直至握手|
|`out_data`|输出signed32|raw48经右移RNE、sat32|
|`out_raw`|输出signed48|64项乘积先累加，再加bias；49位检测后sat48|
|`out_overflow`|输出1|49位bias和超出signed48|
|`out_saturated`|输出1|RNE后超出signed32并饱和|
|`out_error`|输出1|非法shift时为1，raw/data/overflow/saturated均0|
|`busy`|输出1|包含收集、最终数值处理及等待结果消费|

任务启动沿不接收第一对操作数。第64对接收后下一拍产生结果。等待结果消费时所有结果及标志保持，`in_ready=0`、`start_ready=0`。消费结果后回空闲，下一拍可启动新任务。额外输入和忙时start都没有握手，因而忽略。复位立即清控制和输出，必须重新start并重新送64对。

单MAC每次输入握手进行一个16×16有符号乘法，64项总和的范围小于48位。偏置在点积完成后相加，禁止因提前加入偏置而产生中途溢出。raw48溢出后先饱和；随后执行规定的输出转换，溢出标志仍保留。

测试：`bash /absolute/workspace/scripts/run_dot64.sh`，不依赖当前目录。报告位于`reports/prototype/dot64/`。随机种子20261015；独立Python整数参考不依赖生产数值模块。

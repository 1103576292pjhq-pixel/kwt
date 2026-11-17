`ifndef KWT_ICB_CONFIG_VH
`define KWT_ICB_CONFIG_VH
`include "kwt_control_config.vh"

// 总线宽度来自用户指定E203的32位sysper接口；寄存器偏移为本工程自定义。
`define KWT_ICB_ADDR_WIDTH 32
`define KWT_ICB_DATA_WIDTH 32
`define KWT_ICB_MASK_WIDTH (`KWT_ICB_DATA_WIDTH / 8)
`define KWT_ICB_OFFSET_WIDTH 8
// SysPer窗口内的首版开发地址，不表示赛方独占分配了此基址。
`define KWT_ICB_DEFAULT_BASE 32'h1100_0000
`define KWT_ICB_STATUS       8'h00
`define KWT_ICB_TASK         8'h04
`define KWT_ICB_LAYER        8'h08
`define KWT_ICB_TILE         8'h0c
`define KWT_ICB_INDEX        8'h10
`define KWT_ICB_DATA         8'h14
`define KWT_ICB_COMMAND      8'h18
`define KWT_ICB_ERROR        8'h1c
`define KWT_ICB_RESULT_TASK  8'h20
`define KWT_ICB_RESULT_META  8'h24
`define KWT_ICB_RESULT_SEQ   8'h28
`define KWT_ICB_RESULT_CURSOR 8'h2c
`define KWT_ICB_RESULT_DATA  8'h30
`define KWT_ICB_ACK_TASK     8'h34
`define KWT_ICB_ACK_SEQ      8'h38
`define KWT_ICB_ACK_COUNT    8'h3c
`define KWT_ICB_ACK          8'h40
`define KWT_ICB_ABORT        8'h44
// 一项快照包含所有身份及一个32位标量，不包含运行时shift或PAIR半项。
`define KWT_ICB_COMMAND_WIDTH (`KWT_CMD_OP_WIDTH + `KWT_LAYER_ID_WIDTH + `KWT_TASK_ID_WIDTH + `KWT_CMD_TILE_WIDTH + `KWT_CMD_INDEX_WIDTH + `KWT_CMD_DATA_WIDTH)
`endif

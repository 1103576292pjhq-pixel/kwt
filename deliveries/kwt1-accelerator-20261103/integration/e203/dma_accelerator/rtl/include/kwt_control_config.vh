`ifndef KWT_CONTROL_CONFIG_VH
`define KWT_CONTROL_CONFIG_VH
`include "kwt_storage_config.vh"

// 固定99行、每组4行，共25组；行组号0..24，区别于全局row0=0,4,..96。
`define KWT_ROW_GROUP_COUNT ((`KWT_M + `KWT_PM - 1) / `KWT_PM)
`define KWT_ROW_GROUP_WIDTH 5
// 供数缓存固定两项；指针1位，占用数需表示0、1、2，故用2位。
`define KWT_FEED_DEPTH 2
`define KWT_FEED_COUNT_WIDTH 2

// -------- 本工程命令字段：按固定任务所需范围定义 --------
// task/layer是本工程的会话身份字段，不是赛方规定的总线格式。
`define KWT_CMD_OP_WIDTH     3
`define KWT_LAYER_ID_WIDTH   4
`define KWT_TASK_ID_WIDTH    32
`define KWT_CMD_TILE_WIDTH   4
`define KWT_CMD_INDEX_WIDTH  13
`define KWT_CMD_DATA_WIDTH   32
`define KWT_ERROR_CODE_WIDTH 8
`define KWT_CMD_BEGIN        3'd0
`define KWT_CMD_X            3'd1
`define KWT_CMD_OPEN         3'd2
`define KWT_CMD_W            3'd3
`define KWT_CMD_BIAS         3'd4
`define KWT_CMD_COMMIT       3'd5
`define KWT_CMD_START        3'd6

// -------- 装载进度：包含“已经装完”的计数值 --------
`define KWT_X_WORD_COUNT     (`KWT_M * `KWT_K)
`define KWT_X_LOAD_COUNT_WIDTH 13
`define KWT_W_WORDS_PER_TILE  (`KWT_K * `KWT_BLOCK_COLS)
`define KWT_W_LOAD_COUNT_WIDTH 11
`define KWT_BIAS_LOAD_COUNT_WIDTH 5
`define KWT_TILE_COUNT       (`KWT_N / `KWT_BLOCK_COLS)
`define KWT_TASK_BLOCK_COUNT (`KWT_ROW_GROUP_COUNT * `KWT_TILE_COUNT)
`define KWT_TILE_ID_WIDTH    4
`define KWT_TILE_COUNT_WIDTH 5
`define KWT_SLOT_STATE_WIDTH 2
`define KWT_SLOT_FREE        2'd0
`define KWT_SLOT_LOADING     2'd1
`define KWT_SLOT_READY       2'd2
`define KWT_SLOT_ACTIVE      2'd3

// 装载语义错误码；错误锁存，共同复位后恢复。
`define KWT_LOAD_ERR_X       8'h11
`define KWT_LOAD_ERR_OPEN    8'h12
`define KWT_LOAD_ERR_W       8'h13
`define KWT_LOAD_ERR_BIAS    8'h14
`define KWT_LOAD_ERR_COMMIT  8'h15
`define KWT_LOAD_ERR_START   8'h16
`define KWT_LOAD_ERR_ID      8'h17
`define KWT_LOAD_ERR_OP      8'h18
`define KWT_LOAD_ERR_SESSION 8'h19

// -------- 双结果块：内部payload与外部描述符/响应容器分开 --------
`define KWT_RESULT_BLOCK_COUNT 2
`define KWT_RESULT_STATE_WIDTH 2
`define KWT_RESULT_FREE       2'd0
`define KWT_RESULT_FILL       2'd1
`define KWT_RESULT_READY      2'd2
`define KWT_RESULT_PAYLOAD_WIDTH (`KWT_Y_WIDTH + `KWT_FLAGS_WIDTH)
`define KWT_RESULT_WORDS      (`KWT_PM * `KWT_BLOCK_COLS)
`define KWT_RESULT_COUNT_WIDTH (`KWT_RESULT_INDEX_WIDTH + 1)
`define KWT_RESULT_ROW_WIDTH  7
`define KWT_RESULT_COUNT_CONTAINER_WIDTH 7
`define KWT_RESULT_SEQUENCE_WIDTH 9
`define KWT_RESULT_RESPONSE_WIDTH 32
`define KWT_RESULT_ERR_ALLOC  8'h21
`define KWT_RESULT_ERR_FILL   8'h22
`define KWT_RESULT_ERR_PUBLISH 8'h23

// -------- 任务调度：12个状态；新增错误码不覆盖子模块原错误码 --------
`define KWT_TASK_STATE_WIDTH 4
`define KWT_TASK_ERR_FEED    8'h31
`define KWT_TASK_ERR_SESSION 8'h32
`endif

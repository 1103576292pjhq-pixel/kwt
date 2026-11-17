`ifndef KWT_STORAGE_CONFIG_VH
`define KWT_STORAGE_CONFIG_VH

`include "kwt_compute_config.vh"

// 本地操作数存储的公共常量，沿用固定FFN1结构。
// 这里只补充宏数量和物理端口宽度，不改变计算位宽及数值方案。
// 这些常量绑定当前拼接方案，不表示支持任意修改矩阵尺寸。

// -------- 逻辑bank、W槽及物理宏的数量 --------
`define KWT_X_BANK_COUNT           `KWT_PM
`define KWT_W_SLOT_COUNT           2
`define KWT_W_BANKS_PER_SLOT       `KWT_PN
`define KWT_W_BANK_COUNT           (`KWT_W_SLOT_COUNT * `KWT_W_BANKS_PER_SLOT)
// 一个逻辑bank由两颗宏沿深度方向拼接，字宽仍然是16位。
`define KWT_SRAMS_PER_BANK         2
`define KWT_X_SRAM_COUNT           (`KWT_X_BANK_COUNT * `KWT_SRAMS_PER_BANK)
`define KWT_W_SRAM_COUNT           (`KWT_W_SLOT_COUNT * `KWT_W_BANKS_PER_SLOT * `KWT_SRAMS_PER_BANK)

// -------- 官方SRAM的原生端口宽度 --------
// 两种宏均为16位字；WEN也有16位，每位独立控制一个数据位。
`define KWT_SRAM_DATA_WIDTH        `KWT_X_WIDTH
`define KWT_SRAM_1024_ADDR_WIDTH   10
`define KWT_SRAM_128_ADDR_WIDTH    7
`define KWT_SRAM_EMA_WIDTH         3
`define KWT_SRAM_EMAW_WIDTH        2

// -------- wrapper对上层提供的逻辑bank地址 --------
// 两颗宏沿深度方向拼接，逻辑地址比单颗宏地址多1位，用于选择part。
// X逻辑bank使用1600项；bank3最后64个位置还需由上层尾行mask屏蔽。
`define KWT_X_BANK_ADDR_WIDTH      (`KWT_SRAM_1024_ADDR_WIDTH + 1)
`define KWT_X_BANK_DEPTH           (((`KWT_M + `KWT_PM - 1) / `KWT_PM) * `KWT_K)
// W每bank保存4个列组各64项，256个位置全部有效。
`define KWT_W_BANK_ADDR_WIDTH      (`KWT_SRAM_128_ADDR_WIDTH + 1)
`define KWT_W_BANK_DEPTH           (`KWT_CTX * `KWT_K)

// -------- bias寄存器组织 --------
// 每个W槽绑定16个bias32；共2×16=32项，即128字节。
// 块内bias地址宽度直接复用计算核的公共定义。
`define KWT_BIAS_WORDS_PER_SLOT    `KWT_BLOCK_COLS
`define KWT_BIAS_WORD_COUNT        (`KWT_W_SLOT_COUNT * `KWT_BIAS_WORDS_PER_SLOT)

`endif // KWT_STORAGE_CONFIG_VH

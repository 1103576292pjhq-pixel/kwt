// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb.h for the primary calling header

#include "Vsoc_cpu_tb__pch.h"
#include "Vsoc_cpu_tb_apb_uart_sv__A20.h"

VL_ATTR_COLD void Vsoc_cpu_tb_apb_uart_sv__A20___ctor_var_reset(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_apb_uart_sv__A20___ctor_var_reset\n"); );
    // Body
    vlSelf->CLK = VL_RAND_RESET_I(1);
    vlSelf->RSTN = VL_RAND_RESET_I(1);
    vlSelf->PADDR = VL_RAND_RESET_I(32);
    vlSelf->PWDATA = VL_RAND_RESET_I(32);
    vlSelf->PWRITE = VL_RAND_RESET_I(1);
    vlSelf->PSEL = VL_RAND_RESET_I(1);
    vlSelf->PENABLE = VL_RAND_RESET_I(1);
    vlSelf->PRDATA = VL_RAND_RESET_I(32);
    vlSelf->__PVT__PREADY = VL_RAND_RESET_I(1);
    vlSelf->__PVT__PSLVERR = VL_RAND_RESET_I(1);
    vlSelf->rx_i = VL_RAND_RESET_I(1);
    vlSelf->tx_o = VL_RAND_RESET_I(1);
    vlSelf->event_o = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(80, vlSelf->__PVT__regs_q);
    VL_RAND_RESET_W(80, vlSelf->__PVT__regs_n);
    vlSelf->__PVT__trigger_level_n = VL_RAND_RESET_I(2);
    vlSelf->__PVT__trigger_level_q = VL_RAND_RESET_I(2);
    vlSelf->__PVT__parity_error = VL_RAND_RESET_I(1);
    vlSelf->__PVT__tx_ready = VL_RAND_RESET_I(1);
    vlSelf->__PVT__rx_valid = VL_RAND_RESET_I(1);
    vlSelf->__PVT__tx_fifo_clr_n = VL_RAND_RESET_I(1);
    vlSelf->__PVT__tx_fifo_clr_q = VL_RAND_RESET_I(1);
    vlSelf->__PVT__rx_fifo_clr_n = VL_RAND_RESET_I(1);
    vlSelf->__PVT__rx_fifo_clr_q = VL_RAND_RESET_I(1);
    vlSelf->__PVT__fifo_tx_valid = VL_RAND_RESET_I(1);
    vlSelf->__PVT__tx_valid = VL_RAND_RESET_I(1);
    vlSelf->__PVT__fifo_rx_valid = VL_RAND_RESET_I(1);
    vlSelf->__PVT__fifo_rx_ready = VL_RAND_RESET_I(1);
    vlSelf->__PVT__fifo_tx_data = VL_RAND_RESET_I(8);
    vlSelf->__PVT__fifo_rx_data = VL_RAND_RESET_I(9);
    vlSelf->__PVT__uart_rx_i__DOT__CS = VL_RAND_RESET_I(3);
    vlSelf->__PVT__uart_rx_i__DOT__NS = VL_RAND_RESET_I(3);
    vlSelf->__PVT__uart_rx_i__DOT__reg_data = VL_RAND_RESET_I(8);
    vlSelf->__PVT__uart_rx_i__DOT__reg_data_next = VL_RAND_RESET_I(8);
    vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync = VL_RAND_RESET_I(3);
    vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count = VL_RAND_RESET_I(3);
    vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count_next = VL_RAND_RESET_I(3);
    vlSelf->__PVT__uart_rx_i__DOT__parity_bit = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_rx_i__DOT__sampleData = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_rx_i__DOT__baud_cnt = VL_RAND_RESET_I(16);
    vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_rx_i__DOT__bit_done = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_rx_i__DOT__start_bit = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_rx_i__DOT__set_error = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_tx_i__DOT__CS = VL_RAND_RESET_I(3);
    vlSelf->__PVT__uart_tx_i__DOT__NS = VL_RAND_RESET_I(3);
    vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count = VL_RAND_RESET_I(3);
    vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count_next = VL_RAND_RESET_I(3);
    vlSelf->__PVT__uart_tx_i__DOT__baud_cnt = VL_RAND_RESET_I(16);
    vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_tx_i__DOT__bit_done = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_rx_fifo_i__DOT__pointer_in = VL_RAND_RESET_I(4);
    vlSelf->__PVT__uart_rx_fifo_i__DOT__pointer_out = VL_RAND_RESET_I(4);
    vlSelf->__PVT__uart_rx_fifo_i__DOT__elements = VL_RAND_RESET_I(5);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->__PVT__uart_rx_fifo_i__DOT__buffer[__Vi0] = VL_RAND_RESET_I(9);
    }
    vlSelf->__PVT__uart_rx_fifo_i__DOT__full = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_tx_fifo_i__DOT__pointer_in = VL_RAND_RESET_I(4);
    vlSelf->__PVT__uart_tx_fifo_i__DOT__pointer_out = VL_RAND_RESET_I(4);
    vlSelf->__PVT__uart_tx_fifo_i__DOT__elements = VL_RAND_RESET_I(5);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->__PVT__uart_tx_fifo_i__DOT__buffer[__Vi0] = VL_RAND_RESET_I(8);
    }
    vlSelf->__PVT__uart_tx_fifo_i__DOT__full = VL_RAND_RESET_I(1);
    vlSelf->__PVT__uart_interrupt_i__DOT__iir_n = VL_RAND_RESET_I(4);
    vlSelf->__PVT__uart_interrupt_i__DOT__iir_q = VL_RAND_RESET_I(4);
    vlSelf->__PVT__uart_interrupt_i__DOT__trigger_level_reached = VL_RAND_RESET_I(1);
}

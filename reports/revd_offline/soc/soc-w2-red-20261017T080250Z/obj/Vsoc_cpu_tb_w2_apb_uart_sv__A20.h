// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsoc_cpu_tb_w2.h for the primary calling header

#ifndef VERILATED_VSOC_CPU_TB_W2_APB_UART_SV__A20_H_
#define VERILATED_VSOC_CPU_TB_W2_APB_UART_SV__A20_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vsoc_cpu_tb_w2__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsoc_cpu_tb_w2_apb_uart_sv__A20 final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(CLK,0,0);
        VL_IN8(RSTN,0,0);
        VL_IN8(PWRITE,0,0);
        VL_IN8(PSEL,0,0);
        VL_IN8(PENABLE,0,0);
        VL_OUT8(__PVT__PREADY,0,0);
        VL_OUT8(__PVT__PSLVERR,0,0);
        VL_IN8(rx_i,0,0);
        VL_OUT8(tx_o,0,0);
        VL_OUT8(event_o,0,0);
        CData/*1:0*/ __PVT__trigger_level_n;
        CData/*1:0*/ __PVT__trigger_level_q;
        CData/*0:0*/ __PVT__parity_error;
        CData/*0:0*/ __PVT__tx_ready;
        CData/*0:0*/ __PVT__rx_valid;
        CData/*0:0*/ __PVT__tx_fifo_clr_n;
        CData/*0:0*/ __PVT__tx_fifo_clr_q;
        CData/*0:0*/ __PVT__rx_fifo_clr_n;
        CData/*0:0*/ __PVT__rx_fifo_clr_q;
        CData/*0:0*/ __PVT__fifo_tx_valid;
        CData/*0:0*/ __PVT__tx_valid;
        CData/*0:0*/ __PVT__fifo_rx_valid;
        CData/*0:0*/ __PVT__fifo_rx_ready;
        CData/*7:0*/ __PVT__fifo_tx_data;
        CData/*2:0*/ __PVT__uart_rx_i__DOT__CS;
        CData/*2:0*/ __PVT__uart_rx_i__DOT__NS;
        CData/*7:0*/ __PVT__uart_rx_i__DOT__reg_data;
        CData/*7:0*/ __PVT__uart_rx_i__DOT__reg_data_next;
        CData/*2:0*/ __PVT__uart_rx_i__DOT__reg_rx_sync;
        CData/*2:0*/ __PVT__uart_rx_i__DOT__reg_bit_count;
        CData/*2:0*/ __PVT__uart_rx_i__DOT__reg_bit_count_next;
        CData/*0:0*/ __PVT__uart_rx_i__DOT__parity_bit;
        CData/*0:0*/ __PVT__uart_rx_i__DOT__parity_bit_next;
        CData/*0:0*/ __PVT__uart_rx_i__DOT__sampleData;
        CData/*0:0*/ __PVT__uart_rx_i__DOT__baudgen_en;
        CData/*0:0*/ __PVT__uart_rx_i__DOT__bit_done;
        CData/*0:0*/ __PVT__uart_rx_i__DOT__start_bit;
        CData/*0:0*/ __PVT__uart_rx_i__DOT__set_error;
        CData/*2:0*/ __PVT__uart_tx_i__DOT__CS;
        CData/*2:0*/ __PVT__uart_tx_i__DOT__NS;
        CData/*2:0*/ __PVT__uart_tx_i__DOT__reg_bit_count;
        CData/*2:0*/ __PVT__uart_tx_i__DOT__reg_bit_count_next;
        CData/*0:0*/ __PVT__uart_tx_i__DOT__baudgen_en;
        CData/*0:0*/ __PVT__uart_tx_i__DOT__bit_done;
        CData/*3:0*/ __PVT__uart_rx_fifo_i__DOT__pointer_in;
        CData/*3:0*/ __PVT__uart_rx_fifo_i__DOT__pointer_out;
        CData/*4:0*/ __PVT__uart_rx_fifo_i__DOT__elements;
        CData/*0:0*/ __PVT__uart_rx_fifo_i__DOT__full;
        CData/*3:0*/ __PVT__uart_tx_fifo_i__DOT__pointer_in;
        CData/*3:0*/ __PVT__uart_tx_fifo_i__DOT__pointer_out;
        CData/*4:0*/ __PVT__uart_tx_fifo_i__DOT__elements;
        CData/*0:0*/ __PVT__uart_tx_fifo_i__DOT__full;
        CData/*3:0*/ __PVT__uart_interrupt_i__DOT__iir_n;
        CData/*3:0*/ __PVT__uart_interrupt_i__DOT__iir_q;
        CData/*0:0*/ __PVT__uart_interrupt_i__DOT__trigger_level_reached;
        SData/*8:0*/ __PVT__fifo_rx_data;
        SData/*15:0*/ __PVT__uart_rx_i__DOT__baud_cnt;
        SData/*15:0*/ __PVT__uart_tx_i__DOT__baud_cnt;
        VL_IN(PADDR,31,0);
        VL_IN(PWDATA,31,0);
        VL_OUT(PRDATA,31,0);
        VlWide<3>/*79:0*/ __PVT__regs_q;
        VlWide<3>/*79:0*/ __PVT__regs_n;
        VlUnpacked<SData/*8:0*/, 16> __PVT__uart_rx_fifo_i__DOT__buffer;
    };
    struct {
        VlUnpacked<CData/*7:0*/, 16> __PVT__uart_tx_fifo_i__DOT__buffer;
    };

    // INTERNAL VARIABLES
    Vsoc_cpu_tb_w2__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsoc_cpu_tb_w2_apb_uart_sv__A20(Vsoc_cpu_tb_w2__Syms* symsp, const char* v__name);
    ~Vsoc_cpu_tb_w2_apb_uart_sv__A20();
    VL_UNCOPYABLE(Vsoc_cpu_tb_w2_apb_uart_sv__A20);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

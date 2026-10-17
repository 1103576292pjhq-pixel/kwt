// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsoc_cpu_tb.h for the primary calling header

#ifndef VERILATED_VSOC_CPU_TB_APB_SPI_MASTER__A20_H_
#define VERILATED_VSOC_CPU_TB_APB_SPI_MASTER__A20_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vsoc_cpu_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsoc_cpu_tb_apb_spi_master__A20 final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(HCLK,0,0);
        VL_IN8(HRESETn,0,0);
        VL_IN8(PWRITE,0,0);
        VL_IN8(PSEL,0,0);
        VL_IN8(PENABLE,0,0);
        VL_OUT8(__PVT__PREADY,0,0);
        VL_OUT8(__PVT__PSLVERR,0,0);
        VL_OUT8(events_o,0,0);
        VL_OUT8(spi_clk,0,0);
        VL_OUT8(spi_csn0,0,0);
        VL_OUT8(__PVT__spi_csn1,0,0);
        VL_OUT8(__PVT__spi_csn2,0,0);
        VL_OUT8(__PVT__spi_csn3,0,0);
        VL_OUT8(spi_sdo0,0,0);
        VL_OUT8(spi_sdo1,0,0);
        VL_OUT8(spi_sdo2,0,0);
        VL_OUT8(spi_sdo3,0,0);
        VL_OUT8(spi_oe0,0,0);
        VL_OUT8(spi_oe1,0,0);
        VL_OUT8(spi_oe2,0,0);
        VL_OUT8(spi_oe3,0,0);
        VL_IN8(spi_sdi0,0,0);
        VL_IN8(spi_sdi1,0,0);
        VL_IN8(spi_sdi2,0,0);
        VL_IN8(spi_sdi3,0,0);
        CData/*7:0*/ __PVT__spi_clk_div;
        CData/*0:0*/ __PVT__spi_clk_div_valid;
        CData/*5:0*/ __PVT__spi_addr_len;
        CData/*5:0*/ __PVT__spi_cmd_len;
        CData/*0:0*/ __PVT__spi_swrst;
        CData/*0:0*/ __PVT__spi_rd;
        CData/*0:0*/ __PVT__spi_wr;
        CData/*0:0*/ __PVT__spi_qrd;
        CData/*0:0*/ __PVT__spi_qwr;
        CData/*0:0*/ __PVT__spi_data_tx_valid;
        CData/*0:0*/ __PVT__spi_data_rx_valid;
        CData/*0:0*/ __PVT__spi_data_rx_ready;
        CData/*6:0*/ __PVT__spi_ctrl_status;
        CData/*0:0*/ __PVT__spi_ctrl_data_tx_valid;
        CData/*0:0*/ __PVT__spi_ctrl_data_tx_ready;
        CData/*0:0*/ __PVT__spi_ctrl_data_rx_valid;
        CData/*4:0*/ __PVT__s_th_tx;
        CData/*4:0*/ __PVT__s_th_rx;
        CData/*0:0*/ __PVT__s_rise_int_tx;
        CData/*0:0*/ __PVT__s_rise_int_rx;
        CData/*0:0*/ __PVT__s_int_en;
        CData/*4:0*/ __PVT__u_txfifo__DOT__elements;
        CData/*0:0*/ __PVT__u_txfifo__DOT__full;
        CData/*3:0*/ __PVT__u_rxfifo__DOT__pointer_in;
        CData/*3:0*/ __PVT__u_rxfifo__DOT__pointer_out;
        CData/*4:0*/ __PVT__u_rxfifo__DOT__elements;
        CData/*0:0*/ __PVT__u_rxfifo__DOT__full;
        CData/*0:0*/ __PVT__u_spictrl__DOT__spi_rise;
        CData/*0:0*/ __PVT__u_spictrl__DOT__spi_clock_en;
        CData/*0:0*/ __PVT__u_spictrl__DOT__en_quad;
        CData/*0:0*/ __PVT__u_spictrl__DOT__en_quad_int;
        CData/*0:0*/ __PVT__u_spictrl__DOT__do_rx;
        CData/*4:0*/ __PVT__u_spictrl__DOT__state;
        CData/*4:0*/ __PVT__u_spictrl__DOT__state_next;
        CData/*7:0*/ __PVT__u_spictrl__DOT__u_clkgen__DOT__counter_trgt;
        CData/*7:0*/ __PVT__u_spictrl__DOT__u_clkgen__DOT__counter_trgt_next;
        CData/*7:0*/ __PVT__u_spictrl__DOT__u_clkgen__DOT__counter;
        CData/*7:0*/ __PVT__u_spictrl__DOT__u_clkgen__DOT__counter_next;
        CData/*0:0*/ __PVT__u_spictrl__DOT__u_clkgen__DOT__spi_clk_next;
    };
    struct {
        CData/*0:0*/ __PVT__u_spictrl__DOT__u_clkgen__DOT__running;
        CData/*0:0*/ __PVT__u_spictrl__DOT__u_txreg__DOT__tx_CS;
        CData/*0:0*/ __PVT__u_spictrl__DOT__u_txreg__DOT__tx_NS;
        CData/*1:0*/ __PVT__u_spictrl__DOT__u_rxreg__DOT__rx_CS;
        CData/*1:0*/ __PVT__u_spictrl__DOT__u_rxreg__DOT__rx_NS;
        SData/*15:0*/ __PVT__spi_data_len;
        SData/*15:0*/ __PVT__spi_dummy_rd;
        SData/*15:0*/ __PVT__spi_dummy_wr;
        SData/*15:0*/ __PVT__u_spictrl__DOT__u_txreg__DOT__counter;
        SData/*15:0*/ __PVT__u_spictrl__DOT__u_txreg__DOT__counter_trgt;
        SData/*15:0*/ __PVT__u_spictrl__DOT__u_txreg__DOT__counter_next;
        SData/*15:0*/ __PVT__u_spictrl__DOT__u_txreg__DOT__counter_trgt_next;
        SData/*15:0*/ __PVT__u_spictrl__DOT__u_rxreg__DOT__counter;
        SData/*15:0*/ __PVT__u_spictrl__DOT__u_rxreg__DOT__counter_trgt;
        SData/*15:0*/ __PVT__u_spictrl__DOT__u_rxreg__DOT__counter_next;
        SData/*15:0*/ __PVT__u_spictrl__DOT__u_rxreg__DOT__counter_trgt_next;
        VL_IN(PADDR,31,0);
        VL_IN(PWDATA,31,0);
        VL_OUT(PRDATA,31,0);
        IData/*31:0*/ __PVT__spi_addr;
        IData/*31:0*/ __PVT__spi_cmd;
        IData/*31:0*/ u_rxfifo__DOT____Vlvbound_h01eed7db__0;
        IData/*31:0*/ __PVT__u_spictrl__DOT__u_rxreg__DOT__data_int;
        IData/*31:0*/ __PVT__u_spictrl__DOT__u_rxreg__DOT__data_int_next;
        VlUnpacked<IData/*31:0*/, 10> __PVT__u_rxfifo__DOT__buffer;
    };

    // INTERNAL VARIABLES
    Vsoc_cpu_tb__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsoc_cpu_tb_apb_spi_master__A20(Vsoc_cpu_tb__Syms* symsp, const char* v__name);
    ~Vsoc_cpu_tb_apb_spi_master__A20();
    VL_UNCOPYABLE(Vsoc_cpu_tb_apb_spi_master__A20);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

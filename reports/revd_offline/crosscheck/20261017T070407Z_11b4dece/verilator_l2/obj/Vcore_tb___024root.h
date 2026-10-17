// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcore_tb.h for the primary calling header

#ifndef VERILATED_VCORE_TB___024ROOT_H_
#define VERILATED_VCORE_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vcore_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcore_tb___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ core_tb__DOT__clk;
        CData/*0:0*/ core_tb__DOT__rst_n;
        CData/*0:0*/ core_tb__DOT__in_valid;
        CData/*0:0*/ core_tb__DOT__out_ready;
        CData/*3:0*/ core_tb__DOT__in_op;
        CData/*3:0*/ core_tb__DOT__in_layer_id;
        CData/*7:0*/ core_tb__DOT__in_tile_id;
        CData/*5:0*/ core_tb__DOT__in_shift;
        CData/*0:0*/ core_tb__DOT__in_ready;
        CData/*0:0*/ core_tb__DOT__out_valid;
        CData/*0:0*/ core_tb__DOT__out_overflow;
        CData/*0:0*/ core_tb__DOT__out_saturated;
        CData/*0:0*/ core_tb__DOT__out_last;
        CData/*0:0*/ core_tb__DOT__core_done;
        CData/*0:0*/ core_tb__DOT__fault;
        CData/*7:0*/ core_tb__DOT__error_code;
        CData/*0:0*/ core_tb__DOT__blocked;
        CData/*3:0*/ core_tb__DOT__dut__DOT__state;
        CData/*0:0*/ core_tb__DOT__dut__DOT__q_valid;
        CData/*3:0*/ core_tb__DOT__dut__DOT__q_op;
        CData/*3:0*/ core_tb__DOT__dut__DOT__q_layer;
        CData/*7:0*/ core_tb__DOT__dut__DOT__q_tile;
        CData/*5:0*/ core_tb__DOT__dut__DOT__q_shift;
        CData/*5:0*/ core_tb__DOT__dut__DOT__shift;
        CData/*0:0*/ core_tb__DOT__dut__DOT__tile_open;
        CData/*3:0*/ core_tb__DOT__dut__DOT__product_mask;
        CData/*5:0*/ core_tb__DOT__dut__DOT__product_k;
        CData/*1:0*/ core_tb__DOT__dut__DOT__product_g;
        CData/*0:0*/ core_tb__DOT__dut__DOT__product_valid;
        CData/*1:0*/ core_tb__DOT__dut__DOT__tag_valid;
        CData/*3:0*/ core_tb__DOT__dut__DOT__row_mask;
        CData/*3:0*/ core_tb__DOT__dut__DOT__x_rd;
        CData/*3:0*/ core_tb__DOT__dut__DOT__x_wr;
        CData/*3:0*/ core_tb__DOT__dut__DOT__w_wr;
        CData/*0:0*/ core_tb__DOT__dut__DOT__retire_event;
        CData/*0:0*/ core_tb__DOT__dut__DOT__command_ok;
        CData/*0:0*/ core_tb__DOT__dut__DOT__returned;
        CData/*0:0*/ core_tb__DOT__dut__DOT__qe_ready;
        CData/*0:0*/ core_tb__DOT__dut__DOT__qe_valid;
        CData/*0:0*/ core_tb__DOT__dut__DOT__qe_overflow;
        CData/*0:0*/ core_tb__DOT__dut__DOT__qe_saturated;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__quant__in_valid;
        CData/*0:0*/ core_tb__DOT__dut__DOT__core_active;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__rd_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__wr_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__rd_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__wr_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__rd_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__wr_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__rd_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__wr_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__wr_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__1__KET____DOT__ram__wr_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__2__KET____DOT__ram__wr_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__3__KET____DOT__ram__wr_en;
        CData/*0:0*/ core_tb__DOT__dut__DOT__quant__DOT__overflow;
        CData/*0:0*/ core_tb__DOT__dut__DOT__quant__DOT__saturated;
        CData/*1:0*/ core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__valid_pipe;
        CData/*1:0*/ core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__valid_pipe;
        CData/*1:0*/ core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__valid_pipe;
        CData/*1:0*/ core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__valid_pipe;
        CData/*1:0*/ core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__valid_pipe;
        CData/*1:0*/ core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__valid_pipe;
    };
    struct {
        CData/*1:0*/ core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__valid_pipe;
        CData/*1:0*/ core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__valid_pipe;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__core_tb__DOT__clk__0;
        CData/*0:0*/ __Vtrigprevexpr_h78b21af8__0;
        CData/*0:0*/ __Vtrigprevexpr_h07439b72__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__core_tb__DOT__fault__0;
        CData/*0:0*/ __Vtrigprevexpr_h7be2f429__0;
        CData/*0:0*/ __Vtrigprevexpr_hf506ef54__0;
        CData/*0:0*/ __Vtrigprevexpr_hc537c130__0;
        CData/*0:0*/ __Vtrigprevexpr_hc537d19d__0;
        CData/*0:0*/ __Vtrigprevexpr_h4fe0a6ca__0;
        CData/*0:0*/ __Vtrigprevexpr_h88b84a6b__0;
        CData/*0:0*/ __Vtrigprevexpr_ha6663f55__0;
        CData/*0:0*/ __VactDidInit;
        CData/*0:0*/ __VactContinue;
        SData/*15:0*/ core_tb__DOT__in_index;
        SData/*15:0*/ core_tb__DOT__dut__DOT__q_index;
        SData/*10:0*/ core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr;
        SData/*11:0*/ core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr;
        SData/*15:0*/ core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0;
        SData/*15:0*/ core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0;
        SData/*15:0*/ core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0;
        SData/*15:0*/ core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0;
        IData/*31:0*/ core_tb__DOT__in_task_id;
        IData/*31:0*/ core_tb__DOT__out_y_index;
        IData/*31:0*/ core_tb__DOT__out_data;
        IData/*31:0*/ core_tb__DOT__of;
        IData/*31:0*/ core_tb__DOT__sf;
        IData/*31:0*/ core_tb__DOT__rc;
        IData/*31:0*/ core_tb__DOT__op;
        IData/*31:0*/ core_tb__DOT__task_no;
        IData/*31:0*/ core_tb__DOT__tile_no;
        IData/*31:0*/ core_tb__DOT__idx;
        IData/*31:0*/ core_tb__DOT__shift_no;
        IData/*31:0*/ core_tb__DOT__layer_no;
        IData/*31:0*/ core_tb__DOT__cycles;
        IData/*31:0*/ core_tb__DOT__accepted;
        IData/*31:0*/ core_tb__DOT__received;
        IData/*31:0*/ core_tb__DOT__dones;
        IData/*31:0*/ core_tb__DOT__cold_first;
        IData/*31:0*/ core_tb__DOT__cold_start;
        IData/*31:0*/ core_tb__DOT__cold_last;
        IData/*31:0*/ core_tb__DOT__stall;
        IData/*31:0*/ core_tb__DOT__last_stalled;
        IData/*31:0*/ core_tb__DOT__retracted;
        IData/*31:0*/ core_tb__DOT__gap;
        IData/*31:0*/ core_tb__DOT__last_done_received;
        IData/*31:0*/ core_tb__DOT__expect_fault;
        IData/*31:0*/ core_tb__DOT__sink_hold;
        IData/*31:0*/ core_tb__DOT__force_ready;
        IData/*31:0*/ core_tb__DOT__boundary_ready;
        IData/*31:0*/ core_tb__DOT__rng;
        VlWide<4>/*98:0*/ core_tb__DOT__held;
        VlWide<4>/*98:0*/ core_tb__DOT__payload;
        IData/*31:0*/ core_tb__DOT__dut__DOT__q_task;
        IData/*31:0*/ core_tb__DOT__dut__DOT__task_id;
        IData/*31:0*/ core_tb__DOT__dut__DOT__x_count;
        IData/*31:0*/ core_tb__DOT__dut__DOT__w_count;
        IData/*31:0*/ core_tb__DOT__dut__DOT__b_count;
        IData/*31:0*/ core_tb__DOT__dut__DOT__next_tile;
        IData/*31:0*/ core_tb__DOT__dut__DOT__committed;
        IData/*31:0*/ core_tb__DOT__dut__DOT__row0;
        IData/*31:0*/ core_tb__DOT__dut__DOT__tile;
    };
    struct {
        IData/*31:0*/ core_tb__DOT__dut__DOT__g;
        IData/*31:0*/ core_tb__DOT__dut__DOT__qrow;
        IData/*31:0*/ core_tb__DOT__dut__DOT__qcol;
        IData/*31:0*/ core_tb__DOT__dut__DOT__out_pos;
        IData/*31:0*/ core_tb__DOT__dut__DOT__product_task;
        IData/*31:0*/ core_tb__DOT__dut__DOT__product_row;
        IData/*31:0*/ core_tb__DOT__dut__DOT__product_tile;
        IData/*31:0*/ core_tb__DOT__dut__DOT__req_g;
        IData/*31:0*/ core_tb__DOT__dut__DOT__req_k;
        IData/*31:0*/ core_tb__DOT__dut__DOT__qe_data;
        IData/*31:0*/ core_tb__DOT__dut__DOT__effective_rows;
        IData/*31:0*/ core_tb__DOT__dut__DOT__quant__DOT__result;
        IData/*31:0*/ __VactIterCount;
        QData/*47:0*/ core_tb__DOT__in_data;
        QData/*47:0*/ core_tb__DOT__word_data;
        QData/*47:0*/ core_tb__DOT__dut__DOT__q_data;
        QData/*47:0*/ core_tb__DOT__dut__DOT__unused_qe_raw;
        QData/*63:0*/ core_tb__DOT__dut__DOT__load_cycles;
        QData/*63:0*/ core_tb__DOT__dut__DOT__compute_cycles;
        QData/*63:0*/ core_tb__DOT__dut__DOT__output_cycles;
        QData/*63:0*/ core_tb__DOT__dut__DOT__wait_cycles;
        QData/*63:0*/ core_tb__DOT__dut__DOT__core_cycles;
        QData/*63:0*/ core_tb__DOT__dut__DOT__frontend_cycles;
        QData/*63:0*/ core_tb__DOT__dut__DOT__issue_count;
        QData/*63:0*/ core_tb__DOT__dut__DOT__retire_count;
        QData/*63:0*/ core_tb__DOT__dut__DOT__effective_macs;
        QData/*63:0*/ core_tb__DOT__dut__DOT__virtual_macs;
        QData/*63:0*/ core_tb__DOT__dut__DOT__input_accepts;
        QData/*63:0*/ core_tb__DOT__dut__DOT__event_retires;
        QData/*47:0*/ core_tb__DOT__dut__DOT__quant__DOT__clipped;
        VlUnpacked<VlUnpacked<VlUnpacked<QData/*47:0*/, 4>, 4>, 4> core_tb__DOT__dut__DOT__acc;
        VlUnpacked<SData/*15:0*/, 4> core_tb__DOT__dut__DOT__x_hold;
        VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> core_tb__DOT__dut__DOT__product;
        VlUnpacked<CData/*5:0*/, 2> core_tb__DOT__dut__DOT__tag_k;
        VlUnpacked<CData/*1:0*/, 2> core_tb__DOT__dut__DOT__tag_g;
        VlUnpacked<CData/*3:0*/, 2> core_tb__DOT__dut__DOT__tag_mask;
        VlUnpacked<IData/*31:0*/, 2> core_tb__DOT__dut__DOT__tag_task;
        VlUnpacked<IData/*31:0*/, 2> core_tb__DOT__dut__DOT__tag_row;
        VlUnpacked<IData/*31:0*/, 2> core_tb__DOT__dut__DOT__tag_tile;
        VlUnpacked<QData/*47:0*/, 256> core_tb__DOT__dut__DOT__biases;
        VlUnpacked<IData/*31:0*/, 64> core_tb__DOT__dut__DOT__result_data;
        VlUnpacked<CData/*0:0*/, 64> core_tb__DOT__dut__DOT__result_overflow;
        VlUnpacked<CData/*0:0*/, 64> core_tb__DOT__dut__DOT__result_saturated;
        VlUnpacked<SData/*15:0*/, 4> core_tb__DOT__dut__DOT__x_data;
        VlUnpacked<SData/*15:0*/, 4> core_tb__DOT__dut__DOT__w_data;
        VlUnpacked<QData/*63:0*/, 4> core_tb__DOT__dut__DOT__x_reads;
        VlUnpacked<QData/*63:0*/, 4> core_tb__DOT__dut__DOT__x_writes;
        VlUnpacked<QData/*63:0*/, 4> core_tb__DOT__dut__DOT__w_reads;
        VlUnpacked<QData/*63:0*/, 4> core_tb__DOT__dut__DOT__w_writes;
        VlUnpacked<SData/*15:0*/, 1600> core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem;
        VlUnpacked<SData/*15:0*/, 2> core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe;
        VlUnpacked<SData/*15:0*/, 1600> core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem;
        VlUnpacked<SData/*15:0*/, 2> core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe;
        VlUnpacked<SData/*15:0*/, 1600> core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem;
        VlUnpacked<SData/*15:0*/, 2> core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe;
        VlUnpacked<SData/*15:0*/, 1600> core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem;
        VlUnpacked<SData/*15:0*/, 2> core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe;
        VlUnpacked<SData/*15:0*/, 4096> core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem;
        VlUnpacked<SData/*15:0*/, 2> core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe;
        VlUnpacked<SData/*15:0*/, 4096> core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem;
        VlUnpacked<SData/*15:0*/, 2> core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe;
        VlUnpacked<SData/*15:0*/, 4096> core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem;
        VlUnpacked<SData/*15:0*/, 2> core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe;
        VlUnpacked<SData/*15:0*/, 4096> core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem;
    };
    struct {
        VlUnpacked<SData/*15:0*/, 2> core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe;
    };
    std::string core_tb__DOT__cmd_path;
    std::string core_tb__DOT__out_path;
    std::string core_tb__DOT__stats_path;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h81e7d9aa__0;
    VlTriggerScheduler __VtrigSched_hec86538a__0;
    VlTriggerScheduler __VtrigSched_h5ef4d410__0;
    VlTriggerScheduler __VtrigSched_h81e7d9f7__0;
    VlTriggerScheduler __VtrigSched_he7308b1f__0;
    VlTriggerScheduler __VtrigSched_hebd52a47__0;
    VlTriggerScheduler __VtrigSched_h70b12766__0;
    VlTriggerScheduler __VtrigSched_h2100f542__0;
    VlTriggerScheduler __VtrigSched_h2100062b__0;
    VlTriggerScheduler __VtrigSched_hd7e7e0e8__0;
    VlTriggerScheduler __VtrigSched_hdc7f84fd__0;
    VlTriggerScheduler __VtrigSched_h02527763__0;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<13> __VactTriggered;
    VlTriggerVec<13> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vcore_tb__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcore_tb___024root(Vcore_tb__Syms* symsp, const char* v__name);
    ~Vcore_tb___024root();
    VL_UNCOPYABLE(Vcore_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

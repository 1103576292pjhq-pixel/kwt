// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsoc_cpu_tb_w2.h for the primary calling header

#ifndef VERILATED_VSOC_CPU_TB_W2_SIRV_GNRL_ICB2APB__D20_H_
#define VERILATED_VSOC_CPU_TB_W2_SIRV_GNRL_ICB2APB__D20_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vsoc_cpu_tb_w2__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20 final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst_n,0,0);
        VL_IN8(i_icb_cmd_valid,0,0);
        VL_OUT8(i_icb_cmd_ready,0,0);
        VL_IN8(i_icb_cmd_read,0,0);
        VL_IN8(i_icb_cmd_wmask,3,0);
        VL_IN8(__PVT__i_icb_cmd_size,1,0);
        VL_OUT8(i_icb_rsp_valid,0,0);
        VL_IN8(i_icb_rsp_ready,0,0);
        VL_OUT8(__PVT__i_icb_rsp_err,0,0);
        VL_OUT8(apb_pwrite,0,0);
        VL_OUT8(apb_pselx,0,0);
        VL_OUT8(apb_penable,0,0);
        CData/*0:0*/ __PVT__apb_enable_ena;
        CData/*0:0*/ __PVT__apb_enable_nxt;
        CData/*0:0*/ __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren;
        CData/*1:0*/ __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt;
        CData/*0:0*/ __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en;
        CData/*0:0*/ __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r;
        CData/*0:0*/ __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r;
        CData/*0:0*/ __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r;
        CData/*0:0*/ __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r;
        CData/*0:0*/ __PVT__apb_enable_dfflr__DOT__qout_r;
        CData/*0:0*/ __Vintraval_ha6cd8b07__0;
        CData/*0:0*/ __Vintraval_hd4ed3694__0;
        CData/*0:0*/ __Vintraval_h88ee962d__0;
        CData/*0:0*/ __Vintraval_h0832c4b9__0;
        CData/*0:0*/ __Vintraval_hd7c47701__0;
        CData/*0:0*/ __Vintraval_h482209e4__0;
        CData/*0:0*/ __Vintraval_hd81e4296__0;
        CData/*0:0*/ __Vintraval_ha1de5790__0;
        CData/*0:0*/ __Vintraval_hdd79b79c__0;
        CData/*0:0*/ __Vintraval_h6d3cacfa__0;
        CData/*0:0*/ __Vintraval_h092d83ea__0;
        CData/*0:0*/ __Vintraval_h8ea1e1fb__0;
        CData/*0:0*/ __Vintraval_h653572f2__0;
        CData/*0:0*/ __Vintraval_h8a6133fe__0;
        CData/*0:0*/ __Vintraval_ha1fea460__0;
        CData/*0:0*/ __Vintraval_h96af441e__0;
        CData/*0:0*/ __Vintraval_h674882be__0;
        CData/*0:0*/ __Vintraval_h8245f252__0;
        CData/*0:0*/ __Vintraval_h79b03c47__0;
        CData/*0:0*/ __Vintraval_h445ee19f__0;
        CData/*0:0*/ __Vintraval_h5179263c__0;
        CData/*0:0*/ __Vintraval_hcb76dca7__0;
        CData/*0:0*/ __Vintraval_hb0417ab0__0;
        CData/*0:0*/ __Vintraval_hd8803de5__0;
        CData/*0:0*/ __Vintraval_hddce3e18__0;
        CData/*0:0*/ __Vintraval_h73ffeba4__0;
        CData/*0:0*/ __Vintraval_h656f383d__0;
        CData/*0:0*/ __Vintraval_h0b17127e__0;
        CData/*0:0*/ __Vintraval_h606aec64__0;
        CData/*0:0*/ __Vintraval_h5c8dd048__0;
        CData/*0:0*/ __Vintraval_h93d49f79__0;
        CData/*0:0*/ __Vintraval_h3346e739__0;
        CData/*0:0*/ __Vintraval_h6dbc2bc6__0;
        CData/*0:0*/ __Vintraval_h5fa33592__0;
        CData/*0:0*/ __Vintraval_h99de5462__0;
        CData/*0:0*/ __Vintraval_ha59c9c13__0;
        CData/*0:0*/ __Vintraval_hb22abf93__0;
        CData/*0:0*/ __Vintraval_hf863475e__0;
        CData/*0:0*/ __Vintraval_hac9146e7__0;
        CData/*0:0*/ __Vintraval_h4f6ece45__0;
        CData/*0:0*/ __Vintraval_h31b5ad41__0;
    };
    struct {
        CData/*0:0*/ __Vintraval_h8917a33b__0;
        CData/*0:0*/ __Vintraval_h975d1662__0;
        CData/*0:0*/ __Vintraval_hbebbfbbc__0;
        CData/*0:0*/ __Vintraval_h72e14854__0;
        CData/*0:0*/ __Vintraval_hebd75c8f__0;
        CData/*0:0*/ __Vintraval_h54d3cbee__0;
        CData/*0:0*/ __Vintraval_h9e56266d__0;
        CData/*0:0*/ __Vintraval_h86d1dfae__0;
        CData/*0:0*/ __Vintraval_h9ecfb8ed__0;
        CData/*0:0*/ __Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1;
        CData/*0:0*/ __Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1;
        CData/*0:0*/ __Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1;
        CData/*0:0*/ __Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1;
        CData/*0:0*/ __Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0;
        CData/*0:0*/ __Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1;
        CData/*0:0*/ __Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0;
        VL_IN(i_icb_cmd_addr,31,0);
        VL_IN(i_icb_cmd_wdata,31,0);
        VL_OUT(i_icb_rsp_rdata,31,0);
        VL_OUT(apb_paddr,31,0);
        VL_OUT(apb_pwdata,31,0);
        VL_IN(apb_prdata,31,0);
        IData/*31:0*/ __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r;
        IData/*31:0*/ __Vintraval_h23251fa7__0;
        IData/*31:0*/ __Vintraval_h8deeadb1__0;
        IData/*31:0*/ __Vintraval_ha6901b08__0;
        IData/*31:0*/ __Vintraval_ha0e6430f__0;
        IData/*31:0*/ __Vintraval_h4f245ac9__0;
        IData/*31:0*/ __Vintraval_hb12e65c4__0;
        IData/*31:0*/ __Vintraval_hbf074e12__0;
        IData/*31:0*/ __Vintraval_h6eb70417__0;
        IData/*31:0*/ __Vintraval_he5a0ea95__0;
        IData/*31:0*/ __Vintraval_hbbb0f04d__0;
        IData/*31:0*/ __Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0;
        VlUnpacked<IData/*31:0*/, 1> __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r;
    };

    // INTERNAL VARIABLES
    Vsoc_cpu_tb_w2__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20(Vsoc_cpu_tb_w2__Syms* symsp, const char* v__name);
    ~Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20();
    VL_UNCOPYABLE(Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

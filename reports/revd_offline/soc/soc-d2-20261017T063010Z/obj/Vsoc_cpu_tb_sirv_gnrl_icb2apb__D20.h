// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsoc_cpu_tb.h for the primary calling header

#ifndef VERILATED_VSOC_CPU_TB_SIRV_GNRL_ICB2APB__D20_H_
#define VERILATED_VSOC_CPU_TB_SIRV_GNRL_ICB2APB__D20_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vsoc_cpu_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 final : public VerilatedModule {
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
        CData/*0:0*/ __Vintraval_hfac05d6d__0;
        CData/*0:0*/ __Vintraval_h6b69a5a8__0;
        CData/*0:0*/ __Vintraval_h457ea803__0;
        CData/*0:0*/ __Vintraval_hce99e9ab__0;
        CData/*0:0*/ __Vintraval_h96ff4e6f__0;
        CData/*0:0*/ __Vintraval_h2aee73aa__0;
        CData/*0:0*/ __Vintraval_h99a5e57a__0;
        CData/*0:0*/ __Vintraval_hfe7d94a5__0;
        CData/*0:0*/ __Vintraval_hb5ef0565__0;
        CData/*0:0*/ __Vintraval_h7355dad4__0;
        CData/*0:0*/ __Vintraval_h8c13ff0f__0;
        CData/*0:0*/ __Vintraval_h7e40cd22__0;
        CData/*0:0*/ __Vintraval_h4e109248__0;
        CData/*0:0*/ __Vintraval_h58a13d8e__0;
        CData/*0:0*/ __Vintraval_hf7966aed__0;
        CData/*0:0*/ __Vintraval_hf1f7a5c8__0;
        CData/*0:0*/ __Vintraval_ha8a6b439__0;
        CData/*0:0*/ __Vintraval_h1e9e37b7__0;
        CData/*0:0*/ __Vintraval_h3aae0692__0;
        CData/*0:0*/ __Vintraval_hcef68dcf__0;
        CData/*0:0*/ __Vintraval_h95555504__0;
        CData/*0:0*/ __Vintraval_h204a370e__0;
        CData/*0:0*/ __Vintraval_h20c5c9a5__0;
        CData/*0:0*/ __Vintraval_h95fc2197__0;
        CData/*0:0*/ __Vintraval_h9bb77f21__0;
        CData/*0:0*/ __Vintraval_h3c4830a3__0;
        CData/*0:0*/ __Vintraval_h7353a0bb__0;
        CData/*0:0*/ __Vintraval_h89a11f0d__0;
        CData/*0:0*/ __Vintraval_h4db353df__0;
        CData/*0:0*/ __Vintraval_hb9c4cca5__0;
        CData/*0:0*/ __Vintraval_hca66d8b7__0;
        CData/*0:0*/ __Vintraval_h7f10a5b4__0;
        CData/*0:0*/ __Vintraval_h2dd31de8__0;
        CData/*0:0*/ __Vintraval_hed1798b9__0;
        CData/*0:0*/ __Vintraval_h3d7a887c__0;
        CData/*0:0*/ __Vintraval_h75463d93__0;
        CData/*0:0*/ __Vintraval_h193dd012__0;
        CData/*0:0*/ __Vintraval_h620c849d__0;
        CData/*0:0*/ __Vintraval_ha8508ec1__0;
        CData/*0:0*/ __Vintraval_h4c3ccd07__0;
        CData/*0:0*/ __Vintraval_h806a49ab__0;
    };
    struct {
        CData/*0:0*/ __Vintraval_h47d73fa5__0;
        CData/*0:0*/ __Vintraval_heab36c15__0;
        CData/*0:0*/ __Vintraval_h72a5ef14__0;
        CData/*0:0*/ __Vintraval_hbc06ab8f__0;
        CData/*0:0*/ __Vintraval_h542ddfa3__0;
        CData/*0:0*/ __Vintraval_h7fcd2c10__0;
        CData/*0:0*/ __Vintraval_h3aff6d7c__0;
        CData/*0:0*/ __Vintraval_h62208fa6__0;
        CData/*0:0*/ __Vintraval_hf063e1bd__0;
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
        IData/*31:0*/ __Vintraval_h5e150db5__0;
        IData/*31:0*/ __Vintraval_h96d9306e__0;
        IData/*31:0*/ __Vintraval_h891e626d__0;
        IData/*31:0*/ __Vintraval_h2924218a__0;
        IData/*31:0*/ __Vintraval_h0cb511f8__0;
        IData/*31:0*/ __Vintraval_h4bc523a2__0;
        IData/*31:0*/ __Vintraval_hbb5538c0__0;
        IData/*31:0*/ __Vintraval_hf6d5b79c__0;
        IData/*31:0*/ __Vintraval_h26d1befe__0;
        IData/*31:0*/ __Vintraval_h5381d840__0;
        IData/*31:0*/ __Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0;
        VlUnpacked<IData/*31:0*/, 1> __PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r;
    };

    // INTERNAL VARIABLES
    Vsoc_cpu_tb__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20(Vsoc_cpu_tb__Syms* symsp, const char* v__name);
    ~Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20();
    VL_UNCOPYABLE(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

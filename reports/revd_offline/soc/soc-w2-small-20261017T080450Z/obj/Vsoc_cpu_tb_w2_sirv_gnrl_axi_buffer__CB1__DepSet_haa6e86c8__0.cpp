// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb_w2.h for the primary calling header

#include "Vsoc_cpu_tb_w2__pch.h"
#include "Vsoc_cpu_tb_w2__Syms.h"
#include "Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1.h"

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0____Vfork_30__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h307d92f1__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h307d92f1__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0____Vfork_30__1(vlSelf, vlSelf->__Vintraval_h307d92f1__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0____Vfork_30__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h307d92f1__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0____Vfork_30__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h307d92f1__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1____Vfork_29__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hd6cd111b__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hd6cd111b__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1____Vfork_29__1(vlSelf, vlSelf->__Vintraval_hd6cd111b__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1____Vfork_29__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hd6cd111b__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1____Vfork_29__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hd6cd111b__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2____Vfork_28__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h59d5a6ed__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h59d5a6ed__0 = vlSelf->o_axi_bresp_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2____Vfork_28__1(vlSelf, vlSelf->__Vintraval_h59d5a6ed__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2____Vfork_28__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h59d5a6ed__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2____Vfork_28__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h59d5a6ed__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3____Vfork_27__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h228ee6cb__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h228ee6cb__0 = vlSelf->o_axi_bresp_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3____Vfork_27__1(vlSelf, vlSelf->__Vintraval_h228ee6cb__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3____Vfork_27__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h228ee6cb__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3____Vfork_27__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h228ee6cb__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4____Vfork_26__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h9308fd8e__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h9308fd8e__0 = vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4____Vfork_26__1(vlSelf, vlSelf->__Vintraval_h9308fd8e__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4____Vfork_26__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h9308fd8e__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4____Vfork_26__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h9308fd8e__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5____Vfork_25__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h431afb99__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h431afb99__0 = vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5____Vfork_25__1(vlSelf, vlSelf->__Vintraval_h431afb99__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5____Vfork_25__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h431afb99__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5____Vfork_25__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h431afb99__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6____Vfork_24__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_hfcbb7fb2__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hfcbb7fb2__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6____Vfork_24__1(vlSelf, vlSelf->__Vintraval_hfcbb7fb2__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6____Vfork_24__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_hfcbb7fb2__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6____Vfork_24__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hfcbb7fb2__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7____Vfork_23__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h83214436__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h83214436__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7____Vfork_23__1(vlSelf, vlSelf->__Vintraval_h83214436__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7____Vfork_23__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h83214436__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7____Vfork_23__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h83214436__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8____Vfork_22__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h7ee68b84__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h7ee68b84__0 = vlSelf->o_axi_rdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8____Vfork_22__1(vlSelf, vlSelf->__Vintraval_h7ee68b84__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8____Vfork_22__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h7ee68b84__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8____Vfork_22__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h7ee68b84__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9____Vfork_21__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h954f55f6__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h954f55f6__0 = vlSelf->o_axi_rdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9____Vfork_21__1(vlSelf, vlSelf->__Vintraval_h954f55f6__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9____Vfork_21__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h954f55f6__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9____Vfork_21__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h954f55f6__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10____Vfork_20__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h306c97b1__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h306c97b1__0 = vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10____Vfork_20__1(vlSelf, vlSelf->__Vintraval_h306c97b1__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10____Vfork_20__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h306c97b1__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10____Vfork_20__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h306c97b1__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11____Vfork_19__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h42f58020__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h42f58020__0 = vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11____Vfork_19__1(vlSelf, vlSelf->__Vintraval_h42f58020__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11____Vfork_19__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h42f58020__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11____Vfork_19__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h42f58020__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12____Vfork_18__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h881cca64__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h881cca64__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12____Vfork_18__1(vlSelf, vlSelf->__Vintraval_h881cca64__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12____Vfork_18__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h881cca64__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12____Vfork_18__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h881cca64__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13____Vfork_17__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hdf458cf3__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hdf458cf3__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13____Vfork_17__1(vlSelf, vlSelf->__Vintraval_hdf458cf3__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13____Vfork_17__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hdf458cf3__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13____Vfork_17__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hdf458cf3__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14____Vfork_16__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h678ba7c9__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h678ba7c9__0 = vlSelf->o_axi_wdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14____Vfork_16__1(vlSelf, vlSelf->__Vintraval_h678ba7c9__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14____Vfork_16__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h678ba7c9__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14____Vfork_16__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h678ba7c9__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15____Vfork_15__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h028e2d31__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h028e2d31__0 = vlSelf->o_axi_wdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15____Vfork_15__1(vlSelf, vlSelf->__Vintraval_h028e2d31__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15____Vfork_15__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h028e2d31__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15____Vfork_15__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h028e2d31__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16____Vfork_14__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h99463b99__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h99463b99__0 = vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16____Vfork_14__1(vlSelf, vlSelf->__Vintraval_h99463b99__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16____Vfork_14__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h99463b99__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16____Vfork_14__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h99463b99__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17____Vfork_13__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h7cb2779f__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h7cb2779f__0 = vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17____Vfork_13__1(vlSelf, vlSelf->__Vintraval_h7cb2779f__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17____Vfork_13__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h7cb2779f__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17____Vfork_13__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h7cb2779f__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18____Vfork_12__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h0d93b5cc__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h0d93b5cc__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18____Vfork_12__1(vlSelf, vlSelf->__Vintraval_h0d93b5cc__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18____Vfork_12__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h0d93b5cc__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18____Vfork_12__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h0d93b5cc__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19____Vfork_11__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hb8fd0b54__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hb8fd0b54__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19____Vfork_11__1(vlSelf, vlSelf->__Vintraval_hb8fd0b54__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19____Vfork_11__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hb8fd0b54__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19____Vfork_11__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hb8fd0b54__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20____Vfork_10__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h5f342756__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h5f342756__0 = vlSelf->o_axi_aw_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20____Vfork_10__1(vlSelf, vlSelf->__Vintraval_h5f342756__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20____Vfork_10__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h5f342756__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20____Vfork_10__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h5f342756__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21____Vfork_9__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hef5b740f__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if ((1U & (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r))) {
                vlSelf->__Vintraval_hef5b740f__0 = vlSelf->o_axi_aw_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21____Vfork_9__1(vlSelf, vlSelf->__Vintraval_hef5b740f__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21____Vfork_9__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hef5b740f__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21____Vfork_9__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hef5b740f__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22____Vfork_8__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h5943586c__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h5943586c__0 = vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22____Vfork_8__1(vlSelf, vlSelf->__Vintraval_h5943586c__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22____Vfork_8__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h5943586c__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22____Vfork_8__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h5943586c__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23____Vfork_7__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h5401ebdc__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if ((1U & (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r))) {
                vlSelf->__Vintraval_h5401ebdc__0 = vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23____Vfork_7__1(vlSelf, vlSelf->__Vintraval_h5401ebdc__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23____Vfork_7__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h5401ebdc__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23____Vfork_7__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h5401ebdc__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24____Vfork_6__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h5ca35a7b__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h5ca35a7b__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24____Vfork_6__1(vlSelf, vlSelf->__Vintraval_h5ca35a7b__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24____Vfork_6__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h5ca35a7b__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24____Vfork_6__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h5ca35a7b__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25____Vfork_5__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h5fbb254b__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h5fbb254b__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25____Vfork_5__1(vlSelf, vlSelf->__Vintraval_h5fbb254b__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25____Vfork_5__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h5fbb254b__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25____Vfork_5__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h5fbb254b__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26____Vfork_4__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hf18773da__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_hf18773da__0 = vlSelf->o_axi_ar_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26____Vfork_4__1(vlSelf, vlSelf->__Vintraval_hf18773da__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26____Vfork_4__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hf18773da__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26____Vfork_4__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hf18773da__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27____Vfork_3__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h79607730__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h79607730__0 = vlSelf->o_axi_ar_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27____Vfork_3__1(vlSelf, vlSelf->__Vintraval_h79607730__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27____Vfork_3__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h79607730__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27____Vfork_3__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h79607730__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28____Vfork_2__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hb52700a2__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_hb52700a2__0 = vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28____Vfork_2__1(vlSelf, vlSelf->__Vintraval_hb52700a2__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28____Vfork_2__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hb52700a2__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28____Vfork_2__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hb52700a2__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29____Vfork_1__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hc5d83d18__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_hc5d83d18__0 = vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29____Vfork_1__1(vlSelf, vlSelf->__Vintraval_hc5d83d18__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29____Vfork_1__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hc5d83d18__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29____Vfork_1__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hc5d83d18__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30____Vfork_32__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, QData/*34:0*/ __Vintraval_h3da6055d__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_hfc4b73f9__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen) 
             & (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r))) {
            vlSelf->__Vintraval_h3da6055d__0 = 1ULL;
            Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30____Vfork_32__1(vlSelf, vlSelf->__Vintraval_h3da6055d__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30____Vfork_32__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, QData/*34:0*/ __Vintraval_h3da6055d__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30____Vfork_32__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__1__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h3da6055d__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__1__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31____Vfork_31__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, QData/*34:0*/ __Vintraval_h14bcd985__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_hfc4b73f9__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen) 
             & (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h14bcd985__0 = 1ULL;
            Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31____Vfork_31__1(vlSelf, vlSelf->__Vintraval_h14bcd985__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31____Vfork_31__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, QData/*34:0*/ __Vintraval_h14bcd985__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31____Vfork_31__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h14bcd985__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0\n"); );
    // Body
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((- (QData)((IData)((1U & (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r))))) 
           & vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__mux_rdat 
           | ((- (QData)((IData)((1U & ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                        >> 1U))))) 
              & vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [1U]));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read) 
              & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_rsp_ready)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read)) 
              & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_rsp_ready)));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_read) 
                          & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_valid)));
    vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0) 
                          & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                             & (~ ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                   >> 1U)))));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0) 
                          & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                             & (~ ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                   >> 1U)))));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_en 
        = (1U & ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                 ^ (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen)));
    vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0____Vfork_62__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h5ba058ae__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h5ba058ae__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0____Vfork_62__1(vlSelf, vlSelf->__Vintraval_h5ba058ae__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0____Vfork_62__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h5ba058ae__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__0____Vfork_62__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h5ba058ae__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1____Vfork_61__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hf27a6155__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hf27a6155__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1____Vfork_61__1(vlSelf, vlSelf->__Vintraval_hf27a6155__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1____Vfork_61__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hf27a6155__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__1____Vfork_61__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hf27a6155__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2____Vfork_60__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hfa39b38f__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_hfa39b38f__0 = vlSelf->o_axi_bresp_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2____Vfork_60__1(vlSelf, vlSelf->__Vintraval_hfa39b38f__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2____Vfork_60__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hfa39b38f__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__2____Vfork_60__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hfa39b38f__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3____Vfork_59__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h2034865d__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h2034865d__0 = vlSelf->o_axi_bresp_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3____Vfork_59__1(vlSelf, vlSelf->__Vintraval_h2034865d__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3____Vfork_59__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h2034865d__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__3____Vfork_59__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h2034865d__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4____Vfork_58__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h78b5787a__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h78b5787a__0 = vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4____Vfork_58__1(vlSelf, vlSelf->__Vintraval_h78b5787a__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4____Vfork_58__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h78b5787a__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__4____Vfork_58__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h78b5787a__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5____Vfork_57__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hb092f0dc__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_hb092f0dc__0 = vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5____Vfork_57__1(vlSelf, vlSelf->__Vintraval_hb092f0dc__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5____Vfork_57__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hb092f0dc__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__5____Vfork_57__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hb092f0dc__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6____Vfork_56__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h0b3a91e2__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h0b3a91e2__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6____Vfork_56__1(vlSelf, vlSelf->__Vintraval_h0b3a91e2__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6____Vfork_56__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h0b3a91e2__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__6____Vfork_56__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h0b3a91e2__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7____Vfork_55__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h69ee19c7__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h69ee19c7__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7____Vfork_55__1(vlSelf, vlSelf->__Vintraval_h69ee19c7__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7____Vfork_55__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h69ee19c7__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__7____Vfork_55__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h69ee19c7__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8____Vfork_54__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h8ea49584__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h8ea49584__0 = vlSelf->o_axi_rdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8____Vfork_54__1(vlSelf, vlSelf->__Vintraval_h8ea49584__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8____Vfork_54__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h8ea49584__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__8____Vfork_54__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h8ea49584__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9____Vfork_53__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hcb00fe90__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_hcb00fe90__0 = vlSelf->o_axi_rdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9____Vfork_53__1(vlSelf, vlSelf->__Vintraval_hcb00fe90__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9____Vfork_53__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hcb00fe90__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__9____Vfork_53__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hcb00fe90__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10____Vfork_52__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h15bf8d86__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h15bf8d86__0 = vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10____Vfork_52__1(vlSelf, vlSelf->__Vintraval_h15bf8d86__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10____Vfork_52__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h15bf8d86__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__10____Vfork_52__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h15bf8d86__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11____Vfork_51__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hc680cd79__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_hc680cd79__0 = vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11____Vfork_51__1(vlSelf, vlSelf->__Vintraval_hc680cd79__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11____Vfork_51__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hc680cd79__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__11____Vfork_51__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hc680cd79__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12____Vfork_50__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h0d9cd96a__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h0d9cd96a__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12____Vfork_50__1(vlSelf, vlSelf->__Vintraval_h0d9cd96a__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12____Vfork_50__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h0d9cd96a__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__12____Vfork_50__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h0d9cd96a__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13____Vfork_49__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_he3547b53__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_he3547b53__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13____Vfork_49__1(vlSelf, vlSelf->__Vintraval_he3547b53__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13____Vfork_49__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_he3547b53__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__13____Vfork_49__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_he3547b53__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14____Vfork_48__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hd6705da1__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_hd6705da1__0 = vlSelf->o_axi_wdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14____Vfork_48__1(vlSelf, vlSelf->__Vintraval_hd6705da1__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14____Vfork_48__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hd6705da1__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__14____Vfork_48__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hd6705da1__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15____Vfork_47__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_ha3c95d9d__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_ha3c95d9d__0 = vlSelf->o_axi_wdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15____Vfork_47__1(vlSelf, vlSelf->__Vintraval_ha3c95d9d__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15____Vfork_47__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_ha3c95d9d__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__15____Vfork_47__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_ha3c95d9d__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16____Vfork_46__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h31812e6e__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h31812e6e__0 = vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16____Vfork_46__1(vlSelf, vlSelf->__Vintraval_h31812e6e__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16____Vfork_46__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h31812e6e__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__16____Vfork_46__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h31812e6e__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17____Vfork_45__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h89a07553__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h89a07553__0 = vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17____Vfork_45__1(vlSelf, vlSelf->__Vintraval_h89a07553__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17____Vfork_45__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h89a07553__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__17____Vfork_45__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h89a07553__0;
    vlSelf->__Vdlyvset__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18____Vfork_44__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_hfcec6d61__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hfcec6d61__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18____Vfork_44__1(vlSelf, vlSelf->__Vintraval_hfcec6d61__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18____Vfork_44__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_hfcec6d61__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__18____Vfork_44__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hfcec6d61__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19____Vfork_43__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h58312404__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h58312404__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19____Vfork_43__1(vlSelf, vlSelf->__Vintraval_h58312404__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19____Vfork_43__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h58312404__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__19____Vfork_43__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h58312404__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20____Vfork_42__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h3150a8e3__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h3150a8e3__0 = vlSelf->o_axi_aw_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20____Vfork_42__1(vlSelf, vlSelf->__Vintraval_h3150a8e3__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20____Vfork_42__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h3150a8e3__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__20____Vfork_42__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h3150a8e3__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21____Vfork_41__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h07c2fce9__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if ((1U & (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r))) {
                vlSelf->__Vintraval_h07c2fce9__0 = vlSelf->o_axi_aw_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21____Vfork_41__1(vlSelf, vlSelf->__Vintraval_h07c2fce9__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21____Vfork_41__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h07c2fce9__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__21____Vfork_41__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h07c2fce9__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22____Vfork_40__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hf97825a0__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_hf97825a0__0 = vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22____Vfork_40__1(vlSelf, vlSelf->__Vintraval_hf97825a0__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22____Vfork_40__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_hf97825a0__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__22____Vfork_40__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hf97825a0__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23____Vfork_39__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h98008347__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if ((1U & (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r))) {
                vlSelf->__Vintraval_h98008347__0 = vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23____Vfork_39__1(vlSelf, vlSelf->__Vintraval_h98008347__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23____Vfork_39__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h98008347__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__23____Vfork_39__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h98008347__0;
    vlSelf->__Vdlyvset__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24____Vfork_38__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_he9c46da5__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_he9c46da5__0 = 
                    (3U & ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24____Vfork_38__1(vlSelf, vlSelf->__Vintraval_he9c46da5__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24____Vfork_38__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_he9c46da5__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__24____Vfork_38__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_he9c46da5__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25____Vfork_37__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h9efc934d__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h9efc934d__0 = 
                    (1U & (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25____Vfork_37__1(vlSelf, vlSelf->__Vintraval_h9efc934d__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25____Vfork_37__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h9efc934d__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__25____Vfork_37__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h9efc934d__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26____Vfork_36__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h74398655__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_h74398655__0 = vlSelf->o_axi_ar_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26____Vfork_36__1(vlSelf, vlSelf->__Vintraval_h74398655__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26____Vfork_36__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h74398655__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__26____Vfork_36__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h74398655__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27____Vfork_35__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h9f09f49f__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h9f09f49f__0 = vlSelf->o_axi_ar_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27____Vfork_35__1(vlSelf, vlSelf->__Vintraval_h9f09f49f__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27____Vfork_35__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h9f09f49f__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__27____Vfork_35__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h9f09f49f__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28____Vfork_34__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_ha528be86__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen) {
                vlSelf->__Vintraval_ha528be86__0 = vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28____Vfork_34__1(vlSelf, vlSelf->__Vintraval_ha528be86__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28____Vfork_34__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_ha528be86__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__28____Vfork_34__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_ha528be86__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29____Vfork_33__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h722267d4__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_ha8e86045__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h722267d4__0 = vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r;
                Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29____Vfork_33__1(vlSelf, vlSelf->__Vintraval_h722267d4__0);
            }
        } else {
            vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29____Vfork_33__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*0:0*/ __Vintraval_h722267d4__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__29____Vfork_33__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h722267d4__0;
    vlSelf->__Vdlyvset__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30____Vfork_66__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h252a42d4__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_hfc4b73f9__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen) 
             & (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r))) {
            vlSelf->__Vintraval_h252a42d4__0 = 0U;
            Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30____Vfork_66__1(vlSelf, vlSelf->__Vintraval_h252a42d4__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30____Vfork_66__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h252a42d4__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__30____Vfork_66__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__1__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h252a42d4__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__1__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31____Vfork_65__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h990ba8e3__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_hfc4b73f9__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen) 
             & (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h990ba8e3__0 = 0U;
            Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31____Vfork_65__1(vlSelf, vlSelf->__Vintraval_h990ba8e3__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31____Vfork_65__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, CData/*1:0*/ __Vintraval_h990ba8e3__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__31____Vfork_65__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h990ba8e3__0;
    vlSelf->__Vdlyvset__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__32____Vfork_64__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, QData/*34:0*/ __Vintraval_hc85c4862__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__32(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__32\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_hfc4b73f9__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen) 
             & (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r))) {
            vlSelf->__Vintraval_hc85c4862__0 = 1ULL;
            Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__32____Vfork_64__1(vlSelf, vlSelf->__Vintraval_hc85c4862__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__32____Vfork_64__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, QData/*34:0*/ __Vintraval_hc85c4862__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__32____Vfork_64__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__1__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_hc85c4862__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__1__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__33____Vfork_63__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, QData/*34:0*/ __Vintraval_h1f5da7b7__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__33(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__33\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_hfc4b73f9__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb_w2.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen) 
             & (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h1f5da7b7__0 = 1ULL;
            Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__33____Vfork_63__1(vlSelf, vlSelf->__Vintraval_h1f5da7b7__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__33____Vfork_63__1(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf, QData/*34:0*/ __Vintraval_h1f5da7b7__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___eval_initial__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__Vtiming__33____Vfork_63__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h1f5da7b7__0;
    vlSelf->__Vdlyvset__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0(Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0\n"); );
    // Body
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((- (IData)((1U & (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r)))) 
           & vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__mux_rdat) 
           | ((- (IData)((1U & ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                >> 1U)))) & vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [1U]));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((- (QData)((IData)((1U & (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r))))) 
           & vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = (vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__mux_rdat 
           | ((- (QData)((IData)((1U & ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                        >> 1U))))) 
              & vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [1U]));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read) 
              & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_rsp_ready)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read)) 
              & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_rsp_ready)));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_read) 
                          & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_valid)));
    vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0) 
                          & ((~ ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                 >> 3U)) & (~ ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                               >> 1U)))));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0) 
                          & ((~ ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                 >> 3U)) & (~ ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                               >> 1U)))));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_en 
        = (1U & ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                 ^ (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen)));
    vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
}

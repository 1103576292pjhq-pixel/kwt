// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb.h for the primary calling header

#include "Vsoc_cpu_tb__pch.h"
#include "Vsoc_cpu_tb__Syms.h"
#include "Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20.h"

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__0____Vfork_5__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h96ff4e6f__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_h96ff4e6f__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__0____Vfork_5__1(vlSelf, vlSelf->__Vintraval_h96ff4e6f__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__0____Vfork_5__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h96ff4e6f__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__0____Vfork_5__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_h96ff4e6f__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__1____Vfork_4__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hce99e9ab__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hce99e9ab__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__1____Vfork_4__1(vlSelf, vlSelf->__Vintraval_hce99e9ab__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__1____Vfork_4__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hce99e9ab__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__1____Vfork_4__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hce99e9ab__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__2____Vfork_3__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h457ea803__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h457ea803__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__2____Vfork_3__1(vlSelf, vlSelf->__Vintraval_h457ea803__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__2____Vfork_3__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h457ea803__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__2____Vfork_3__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h457ea803__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__3____Vfork_2__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h6b69a5a8__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_h6b69a5a8__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__3____Vfork_2__1(vlSelf, vlSelf->__Vintraval_h6b69a5a8__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__3____Vfork_2__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h6b69a5a8__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__3____Vfork_2__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h6b69a5a8__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__4____Vfork_1__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hfac05d6d__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_hfac05d6d__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__4____Vfork_1__1(vlSelf, vlSelf->__Vintraval_hfac05d6d__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__4____Vfork_1__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hfac05d6d__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__4____Vfork_1__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hfac05d6d__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__5____Vfork_6__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h5e150db5__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h5e150db5__0 = vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_prdata;
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__5____Vfork_6__1(vlSelf, vlSelf->__Vintraval_h5e150db5__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__5____Vfork_6__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h5e150db5__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__Vtiming__5____Vfork_6__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h5e150db5__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__0____Vfork_11__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7355dad4__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_h7355dad4__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__0____Vfork_11__1(vlSelf, vlSelf->__Vintraval_h7355dad4__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__0____Vfork_11__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7355dad4__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__0____Vfork_11__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_h7355dad4__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__1____Vfork_10__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hb5ef0565__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hb5ef0565__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__1____Vfork_10__1(vlSelf, vlSelf->__Vintraval_hb5ef0565__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__1____Vfork_10__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hb5ef0565__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__1____Vfork_10__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hb5ef0565__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__2____Vfork_9__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hfe7d94a5__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hfe7d94a5__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__2____Vfork_9__1(vlSelf, vlSelf->__Vintraval_hfe7d94a5__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__2____Vfork_9__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hfe7d94a5__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__2____Vfork_9__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hfe7d94a5__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__3____Vfork_8__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h99a5e57a__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_h99a5e57a__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__3____Vfork_8__1(vlSelf, vlSelf->__Vintraval_h99a5e57a__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__3____Vfork_8__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h99a5e57a__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__3____Vfork_8__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h99a5e57a__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__4____Vfork_7__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h2aee73aa__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h2aee73aa__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__4____Vfork_7__1(vlSelf, vlSelf->__Vintraval_h2aee73aa__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__4____Vfork_7__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h2aee73aa__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__4____Vfork_7__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h2aee73aa__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__5____Vfork_12__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h96d9306e__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h96d9306e__0 = vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_prdata;
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__5____Vfork_12__1(vlSelf, vlSelf->__Vintraval_h96d9306e__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__5____Vfork_12__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h96d9306e__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__Vtiming__5____Vfork_12__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h96d9306e__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__0\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__0____Vfork_17__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hf7966aed__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_hf7966aed__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__0____Vfork_17__1(vlSelf, vlSelf->__Vintraval_hf7966aed__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__0____Vfork_17__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hf7966aed__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__0____Vfork_17__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_hf7966aed__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__1____Vfork_16__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h58a13d8e__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h58a13d8e__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__1____Vfork_16__1(vlSelf, vlSelf->__Vintraval_h58a13d8e__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__1____Vfork_16__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h58a13d8e__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__1____Vfork_16__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h58a13d8e__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__2____Vfork_15__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h4e109248__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h4e109248__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__2____Vfork_15__1(vlSelf, vlSelf->__Vintraval_h4e109248__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__2____Vfork_15__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h4e109248__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__2____Vfork_15__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h4e109248__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__3____Vfork_14__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7e40cd22__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_h7e40cd22__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__3____Vfork_14__1(vlSelf, vlSelf->__Vintraval_h7e40cd22__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__3____Vfork_14__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7e40cd22__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__3____Vfork_14__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h7e40cd22__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__4____Vfork_13__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h8c13ff0f__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h8c13ff0f__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__4____Vfork_13__1(vlSelf, vlSelf->__Vintraval_h8c13ff0f__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__4____Vfork_13__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h8c13ff0f__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__4____Vfork_13__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h8c13ff0f__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__5____Vfork_18__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h891e626d__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h891e626d__0 = vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0.PRDATA;
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__5____Vfork_18__1(vlSelf, vlSelf->__Vintraval_h891e626d__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__5____Vfork_18__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h891e626d__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__Vtiming__5____Vfork_18__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h891e626d__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__0\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__0____Vfork_23__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hcef68dcf__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_hcef68dcf__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__0____Vfork_23__1(vlSelf, vlSelf->__Vintraval_hcef68dcf__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__0____Vfork_23__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hcef68dcf__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__0____Vfork_23__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_hcef68dcf__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__1____Vfork_22__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h3aae0692__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h3aae0692__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__1____Vfork_22__1(vlSelf, vlSelf->__Vintraval_h3aae0692__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__1____Vfork_22__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h3aae0692__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__1____Vfork_22__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h3aae0692__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__2____Vfork_21__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h1e9e37b7__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h1e9e37b7__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__2____Vfork_21__1(vlSelf, vlSelf->__Vintraval_h1e9e37b7__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__2____Vfork_21__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h1e9e37b7__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__2____Vfork_21__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h1e9e37b7__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__3____Vfork_20__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_ha8a6b439__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_ha8a6b439__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__3____Vfork_20__1(vlSelf, vlSelf->__Vintraval_ha8a6b439__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__3____Vfork_20__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_ha8a6b439__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__3____Vfork_20__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_ha8a6b439__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__4____Vfork_19__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hf1f7a5c8__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_hf1f7a5c8__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__4____Vfork_19__1(vlSelf, vlSelf->__Vintraval_hf1f7a5c8__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__4____Vfork_19__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hf1f7a5c8__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__4____Vfork_19__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hf1f7a5c8__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__5____Vfork_24__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h2924218a__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h2924218a__0 = vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1.PRDATA;
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__5____Vfork_24__1(vlSelf, vlSelf->__Vintraval_h2924218a__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__5____Vfork_24__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h2924218a__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__Vtiming__5____Vfork_24__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h2924218a__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__0\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__0____Vfork_29__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h9bb77f21__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_h9bb77f21__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__0____Vfork_29__1(vlSelf, vlSelf->__Vintraval_h9bb77f21__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__0____Vfork_29__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h9bb77f21__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__0____Vfork_29__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_h9bb77f21__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__1____Vfork_28__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h95fc2197__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h95fc2197__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__1____Vfork_28__1(vlSelf, vlSelf->__Vintraval_h95fc2197__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__1____Vfork_28__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h95fc2197__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__1____Vfork_28__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h95fc2197__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__2____Vfork_27__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h20c5c9a5__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h20c5c9a5__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__2____Vfork_27__1(vlSelf, vlSelf->__Vintraval_h20c5c9a5__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__2____Vfork_27__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h20c5c9a5__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__2____Vfork_27__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h20c5c9a5__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__3____Vfork_26__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h204a370e__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_h204a370e__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__3____Vfork_26__1(vlSelf, vlSelf->__Vintraval_h204a370e__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__3____Vfork_26__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h204a370e__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__3____Vfork_26__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h204a370e__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__4____Vfork_25__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h95555504__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h95555504__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__4____Vfork_25__1(vlSelf, vlSelf->__Vintraval_h95555504__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__4____Vfork_25__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h95555504__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__4____Vfork_25__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h95555504__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__5____Vfork_30__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h0cb511f8__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h0cb511f8__0 = vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2.PRDATA;
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__5____Vfork_30__1(vlSelf, vlSelf->__Vintraval_h0cb511f8__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__5____Vfork_30__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h0cb511f8__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__Vtiming__5____Vfork_30__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h0cb511f8__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__0\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__0____Vfork_35__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hb9c4cca5__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_hb9c4cca5__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__0____Vfork_35__1(vlSelf, vlSelf->__Vintraval_hb9c4cca5__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__0____Vfork_35__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hb9c4cca5__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__0____Vfork_35__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_hb9c4cca5__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__1____Vfork_34__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h4db353df__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h4db353df__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__1____Vfork_34__1(vlSelf, vlSelf->__Vintraval_h4db353df__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__1____Vfork_34__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h4db353df__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__1____Vfork_34__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h4db353df__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__2____Vfork_33__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h89a11f0d__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h89a11f0d__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__2____Vfork_33__1(vlSelf, vlSelf->__Vintraval_h89a11f0d__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__2____Vfork_33__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h89a11f0d__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__2____Vfork_33__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h89a11f0d__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__3____Vfork_32__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7353a0bb__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_h7353a0bb__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__3____Vfork_32__1(vlSelf, vlSelf->__Vintraval_h7353a0bb__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__3____Vfork_32__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7353a0bb__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__3____Vfork_32__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h7353a0bb__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__4____Vfork_31__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h3c4830a3__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h3c4830a3__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__4____Vfork_31__1(vlSelf, vlSelf->__Vintraval_h3c4830a3__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__4____Vfork_31__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h3c4830a3__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__4____Vfork_31__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h3c4830a3__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__5____Vfork_36__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h4bc523a2__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h4bc523a2__0 = vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1.PRDATA;
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__5____Vfork_36__1(vlSelf, vlSelf->__Vintraval_h4bc523a2__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__5____Vfork_36__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h4bc523a2__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__Vtiming__5____Vfork_36__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h4bc523a2__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__0\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__0____Vfork_41__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h3d7a887c__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_h3d7a887c__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__0____Vfork_41__1(vlSelf, vlSelf->__Vintraval_h3d7a887c__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__0____Vfork_41__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h3d7a887c__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__0____Vfork_41__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_h3d7a887c__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__1____Vfork_40__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hed1798b9__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_hed1798b9__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__1____Vfork_40__1(vlSelf, vlSelf->__Vintraval_hed1798b9__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__1____Vfork_40__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hed1798b9__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__1____Vfork_40__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_hed1798b9__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__2____Vfork_39__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h2dd31de8__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h2dd31de8__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__2____Vfork_39__1(vlSelf, vlSelf->__Vintraval_h2dd31de8__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__2____Vfork_39__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h2dd31de8__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__2____Vfork_39__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h2dd31de8__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__3____Vfork_38__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7f10a5b4__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_h7f10a5b4__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__3____Vfork_38__1(vlSelf, vlSelf->__Vintraval_h7f10a5b4__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__3____Vfork_38__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7f10a5b4__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__3____Vfork_38__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h7f10a5b4__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__4____Vfork_37__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hca66d8b7__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_hca66d8b7__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__4____Vfork_37__1(vlSelf, vlSelf->__Vintraval_hca66d8b7__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__4____Vfork_37__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hca66d8b7__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__4____Vfork_37__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_hca66d8b7__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__5____Vfork_42__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_hbb5538c0__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_hbb5538c0__0 = vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2.PRDATA;
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__5____Vfork_42__1(vlSelf, vlSelf->__Vintraval_hbb5538c0__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__5____Vfork_42__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_hbb5538c0__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__Vtiming__5____Vfork_42__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_hbb5538c0__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__0\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__0____Vfork_47__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h4c3ccd07__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_h4c3ccd07__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__0____Vfork_47__1(vlSelf, vlSelf->__Vintraval_h4c3ccd07__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__0____Vfork_47__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h4c3ccd07__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__0____Vfork_47__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_h4c3ccd07__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__1____Vfork_46__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_ha8508ec1__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_ha8508ec1__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__1____Vfork_46__1(vlSelf, vlSelf->__Vintraval_ha8508ec1__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__1____Vfork_46__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_ha8508ec1__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__1____Vfork_46__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_ha8508ec1__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__2____Vfork_45__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h620c849d__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h620c849d__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__2____Vfork_45__1(vlSelf, vlSelf->__Vintraval_h620c849d__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__2____Vfork_45__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h620c849d__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__2____Vfork_45__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h620c849d__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__3____Vfork_44__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h193dd012__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_h193dd012__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__3____Vfork_44__1(vlSelf, vlSelf->__Vintraval_h193dd012__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__3____Vfork_44__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h193dd012__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__3____Vfork_44__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h193dd012__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__4____Vfork_43__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h75463d93__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h75463d93__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__4____Vfork_43__1(vlSelf, vlSelf->__Vintraval_h75463d93__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__4____Vfork_43__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h75463d93__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__4____Vfork_43__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h75463d93__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__5____Vfork_48__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_hf6d5b79c__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_hf6d5b79c__0 = ((0x20U 
                                                 & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_addr)
                                                 ? 0U
                                                 : 
                                                ((0x10U 
                                                  & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_addr)
                                                  ? 
                                                 ((8U 
                                                   & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_addr)
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_addr)
                                                    ? (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__r_cmd)
                                                    : (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__r_tx)))
                                                  : 
                                                 ((8U 
                                                   & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_addr)
                                                   ? 
                                                  ((4U 
                                                    & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_addr)
                                                    ? 
                                                   (((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__rxack) 
                                                     << 7U) 
                                                    | (((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__i2c_busy) 
                                                        << 6U) 
                                                       | (((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__al) 
                                                           << 5U) 
                                                          | (((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__tip) 
                                                              << 1U) 
                                                             | (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__irq_flag)))))
                                                    : (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__byte_controller__DOT__sr))
                                                   : 
                                                  ((4U 
                                                    & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_addr)
                                                    ? (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__r_ctrl)
                                                    : (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c0__DOT__r_pre)))));
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__5____Vfork_48__1(vlSelf, vlSelf->__Vintraval_hf6d5b79c__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__5____Vfork_48__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_hf6d5b79c__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__Vtiming__5____Vfork_48__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_hf6d5b79c__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__0\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__0____Vfork_53__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hbc06ab8f__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_hbc06ab8f__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__0____Vfork_53__1(vlSelf, vlSelf->__Vintraval_hbc06ab8f__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__0____Vfork_53__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hbc06ab8f__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__0____Vfork_53__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_hbc06ab8f__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__1____Vfork_52__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h72a5ef14__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h72a5ef14__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__1____Vfork_52__1(vlSelf, vlSelf->__Vintraval_h72a5ef14__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__1____Vfork_52__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h72a5ef14__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__1____Vfork_52__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h72a5ef14__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__2____Vfork_51__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_heab36c15__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_heab36c15__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__2____Vfork_51__1(vlSelf, vlSelf->__Vintraval_heab36c15__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__2____Vfork_51__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_heab36c15__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__2____Vfork_51__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_heab36c15__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__3____Vfork_50__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h47d73fa5__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_h47d73fa5__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__3____Vfork_50__1(vlSelf, vlSelf->__Vintraval_h47d73fa5__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__3____Vfork_50__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h47d73fa5__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__3____Vfork_50__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h47d73fa5__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__4____Vfork_49__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h806a49ab__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h806a49ab__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__4____Vfork_49__1(vlSelf, vlSelf->__Vintraval_h806a49ab__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__4____Vfork_49__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h806a49ab__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__4____Vfork_49__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h806a49ab__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__5____Vfork_54__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h26d1befe__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h26d1befe__0 = ((0x20U 
                                                 & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_addr)
                                                 ? 0U
                                                 : 
                                                ((0x10U 
                                                  & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_addr)
                                                  ? 
                                                 ((8U 
                                                   & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_addr)
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_addr)
                                                    ? (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__r_cmd)
                                                    : (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__r_tx)))
                                                  : 
                                                 ((8U 
                                                   & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_addr)
                                                   ? 
                                                  ((4U 
                                                    & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_addr)
                                                    ? 
                                                   (((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__rxack) 
                                                     << 7U) 
                                                    | (((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__i2c_busy) 
                                                        << 6U) 
                                                       | (((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__al) 
                                                           << 5U) 
                                                          | (((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__tip) 
                                                              << 1U) 
                                                             | (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__irq_flag)))))
                                                    : (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__byte_controller__DOT__sr))
                                                   : 
                                                  ((4U 
                                                    & vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_addr)
                                                    ? (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__r_ctrl)
                                                    : (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_i2c1__DOT__r_pre)))));
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__5____Vfork_54__1(vlSelf, vlSelf->__Vintraval_h26d1befe__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__5____Vfork_54__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h26d1befe__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__Vtiming__5____Vfork_54__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h26d1befe__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__0\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__0____Vfork_59__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hf063e1bd__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__0\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__apb_enable_ena) {
                vlSelf->__Vintraval_hf063e1bd__0 = vlSelf->__PVT__apb_enable_nxt;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__0____Vfork_59__1(vlSelf, vlSelf->__Vintraval_hf063e1bd__0);
            }
        } else {
            vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__0____Vfork_59__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_hf063e1bd__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__0____Vfork_59__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0 
        = __Vintraval_hf063e1bd__0;
    vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__1____Vfork_58__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h62208fa6__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                101);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h62208fa6__0 = 
                    (1U & ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt) 
                           >> 1U));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__1____Vfork_58__1(vlSelf, vlSelf->__Vintraval_h62208fa6__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__1____Vfork_58__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h62208fa6__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__1____Vfork_58__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            106);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 
        = __Vintraval_h62208fa6__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__2____Vfork_57__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h3aff6d7c__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en) {
                vlSelf->__Vintraval_h3aff6d7c__0 = 
                    (1U & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt));
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__2____Vfork_57__1(vlSelf, vlSelf->__Vintraval_h3aff6d7c__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__2____Vfork_57__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h3aff6d7c__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__2____Vfork_57__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h3aff6d7c__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__3____Vfork_56__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7fcd2c10__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__3(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->i_icb_cmd_ready) {
                vlSelf->__Vintraval_h7fcd2c10__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__3____Vfork_56__1(vlSelf, vlSelf->__Vintraval_h7fcd2c10__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__3____Vfork_56__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h7fcd2c10__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__3____Vfork_56__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h7fcd2c10__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__4____Vfork_55__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h542ddfa3__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__4(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__4\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h691aab8b__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                54);
        if (vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
            if (vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) {
                vlSelf->__Vintraval_h542ddfa3__0 = 1U;
                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__4____Vfork_55__1(vlSelf, vlSelf->__Vintraval_h542ddfa3__0);
            }
        } else {
            vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 1U;
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__4____Vfork_55__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, CData/*0:0*/ __Vintraval_h542ddfa3__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__4____Vfork_55__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            59);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 
        = __Vintraval_h542ddfa3__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 1U;
}

VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__5____Vfork_60__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h5381d840__0);

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__5(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__5\n"); );
    // Body
    while (1U) {
        co_await vlSymsp->TOP.__VtrigSched_h4ebf0c7c__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)", 
                                                                "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                                                146);
        if (((IData)(vlSelf->i_icb_cmd_ready) & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r))) {
            vlSelf->__Vintraval_h5381d840__0 = vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_prdata;
            Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__5____Vfork_60__1(vlSelf, vlSelf->__Vintraval_h5381d840__0);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__5____Vfork_60__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf, IData/*31:0*/ __Vintraval_h5381d840__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___eval_initial__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__Vtiming__5____Vfork_60__1\n"); );
    // Body
    co_await vlSymsp->TOP.__VdlySched.delay(0x3e8ULL, 
                                            nullptr, 
                                            "/mnt/d/github/kwt/vendor/e203_hbirdv2-upstream/rtl/e203/general/sirv_gnrl_dffs.v", 
                                            149);
    vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 
        = __Vintraval_h5381d840__0;
    vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 1U;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__0\n"); );
    // Body
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_rsp_ready) 
           & (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__1\n"); );
    // Init
    CData/*0:0*/ __PVT__apb_enable_set;
    __PVT__apb_enable_set = 0;
    // Body
    __PVT__apb_enable_set = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                             & ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                                & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_valid)));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->i_icb_cmd_ready));
    vlSelf->__PVT__apb_enable_ena = ((IData)(__PVT__apb_enable_set) 
                                     | (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__apb_enable_nxt = ((~ (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r)) 
                                     & (IData)(__PVT__apb_enable_set));
}

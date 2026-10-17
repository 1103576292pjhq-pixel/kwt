// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb.h for the primary calling header

#include "Vsoc_cpu_tb__pch.h"
#include "Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20.h"

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0\n"); );
    // Body
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r 
            = vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r = 1U;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r 
            = vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r = 1U;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r 
            = vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r = 1U;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r 
            = vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r = 0U;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 0U;
    }
    if (vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0) {
        vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r 
            = vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1) {
        vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r = 0U;
        vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 0U;
    }
    vlSelf->i_icb_cmd_ready = ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                               & (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (3U & ((IData)(vlSelf->i_icb_cmd_ready) ? 
                 (1U | ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                        << 1U)) : VL_SHIFTR_III(2,2,32, 
                                                (((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                  << 1U) 
                                                 | (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1\n"); );
    // Body
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r 
            = vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r__v0 = 0U;
    }
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r[0U] 
        = vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r;
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__0\n"); );
    // Body
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r 
            = vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r = 1U;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r__v1 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r 
            = vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r = 1U;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r__v1 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r 
            = vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r = 1U;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r__v1 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r 
            = vlSelf->__Vdlyvval__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1) {
        vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r = 0U;
        vlSelf->__Vdlyvset__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r__v1 = 0U;
    }
}

VL_INLINE_OPT void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__2\n"); );
    // Body
    if (vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0) {
        vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r 
            = vlSelf->__Vdlyvval__apb_enable_dfflr__DOT__qout_r__v0;
        vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v0 = 0U;
    }
    if (vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1) {
        vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r = 0U;
        vlSelf->__Vdlyvset__apb_enable_dfflr__DOT__qout_r__v1 = 0U;
    }
    vlSelf->i_icb_cmd_ready = ((~ (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                               & (IData)(vlSelf->__PVT__apb_enable_dfflr__DOT__qout_r));
    vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (3U & ((IData)(vlSelf->i_icb_cmd_ready) ? 
                 (1U | ((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                        << 1U)) : VL_SHIFTR_III(2,2,32, 
                                                (((IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                  << 1U) 
                                                 | (IData)(vlSelf->__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
}

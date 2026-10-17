// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb.h for the primary calling header

#include "Vsoc_cpu_tb__pch.h"
#include "Vsoc_cpu_tb__Syms.h"
#include "Vsoc_cpu_tb___024root.h"

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__4(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__4\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_event_signals 
        = (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3.pwm_o) 
            << 0xcU) | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2.pwm_o) 
                         << 8U) | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1.pwm_o) 
                                    << 4U) | (IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0.pwm_o))));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__5(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__5\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
        = (((QData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3.pwm_o)) 
            << 0x2cU) | (((QData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2.pwm_o)) 
                          << 0x28U) | (((QData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1.pwm_o)) 
                                        << 0x24U) | 
                                       (((QData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0.pwm_o)) 
                                         << 0x20U) 
                                        | (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_gpioA__DOT__r_gpio_sync1))))));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__13(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__13\n"); );
    // Init
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_rsp_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_rsp_ready = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_read;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_read = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o0;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o0 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o1;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o1 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o2;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o2 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o3;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o3 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o4;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o4 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o5;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o5 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o6;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o6 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o7;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o7 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o8;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o8 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o9;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o9 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o10;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o10 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o11;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o11 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o12;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o12 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o13;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o13 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o14;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o14 = 0;
    VlWide<3>/*77:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat;
    VL_ZERO_W(78, soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat);
    QData/*34:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre = 0;
    IData/*31:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_axi_wdata;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_axi_wdata = 0;
    CData/*3:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_axi_wstrb;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_axi_wstrb = 0;
    IData/*31:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_addr;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_addr = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o0;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o0 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o1;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o1 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o3;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o3 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o4;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o4 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o5;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o5 = 0;
    VlWide<3>/*77:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat;
    VL_ZERO_W(78, soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat);
    QData/*34:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__i_icb_cmd_valid_pre;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__i_icb_cmd_valid_pre = 0;
    IData/*31:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_axi_wdata;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_axi_wdata = 0;
    CData/*3:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_axi_wstrb;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_axi_wstrb = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__i_icb_cmd_hsked;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__i_icb_cmd_hsked = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__icb_wr_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__icb_wr_ena = 0;
    CData/*0:0*/ __VdfgTmp_h58350fc7__0;
    __VdfgTmp_h58350fc7__0 = 0;
    CData/*0:0*/ __VdfgTmp_hbd5dd97a__0;
    __VdfgTmp_hbd5dd97a__0 = 0;
    VlWide<3>/*95:0*/ __Vtemp_7;
    VlWide<3>/*95:0*/ __Vtemp_11;
    // Body
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((- (QData)((IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_r))))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
           | ((- (QData)((IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                        >> 1U))))) 
              & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [1U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((- (QData)((IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_r))))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
           | ((- (QData)((IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                        >> 1U))))) 
              & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r) 
            & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__fifo_rf_r
            [0U]) & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [1U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
               >> 2U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [2U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
               >> 3U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [3U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U][0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U][1U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U][2U]);
    __Vtemp_7[1U] = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                     | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                          >> 1U)))) 
                        & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
                        [1U][1U]));
    __Vtemp_7[2U] = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                     | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                          >> 1U)))) 
                        & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
                        [1U][2U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
        = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [1U][0U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
        = __Vtemp_7[1U];
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
        = __Vtemp_7[2U];
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U][0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U][1U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U][2U]);
    __Vtemp_11[1U] = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                      | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                           >> 1U)))) 
                         & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
                         [1U][1U]));
    __Vtemp_11[2U] = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                      | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                           >> 1U)))) 
                         & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
                         [1U][2U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
        = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [1U][0U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
        = __Vtemp_11[1U];
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
        = __Vtemp_11[2U];
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[0xeU] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[3U] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[0xdU] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[0xaU] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[7U] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[9U] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[6U] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[8U] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[5U] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[0xbU] 
        = ((- (IData)((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
           & vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_splt__DOT__o_icb_rsp_rdata[0U] 
        = (IData)((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
                   >> 1U));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__splt_bus_icb_rsp_err 
        = (0x22U | ((0x10U & ((IData)((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
                                       >> 0x22U)) << 4U)) 
                    | (1U & (IData)((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
                                     >> 0x22U)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_splt__DOT__o_icb_rsp_rdata[4U] 
        = (IData)((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__mux_rdat 
                   >> 1U));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_rsp_valid 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read)
                  ? (IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)
                  : (IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__mux_rdat));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o4 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                 & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                    >> 0xcU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o1 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (1U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                  << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                            >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o3 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x400U == (0x1c00U & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U])));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o5 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x800U == (0x1e00U & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U])));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                  << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                            >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x2000U == (0x1ffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                       << 4U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                 >> 0x1cU)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o8 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10025U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o11 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10035U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o2 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10012U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o13 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10040U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o12 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x220U == (0x1fe0U & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U])));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o7 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10024U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o10 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10034U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o5 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10015U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o1 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10008U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o14 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10041U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o4 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10014U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o3 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10013U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o6 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10023U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o9 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (0x10033U == (0xfffffU & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
                                        << 7U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                                                  >> 0x19U)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_rsp_valid 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read)
                  ? (IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)
                  : (IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)));
    __VdfgTmp_hbd5dd97a__0 = (1U & ((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o0)) 
                                    & (~ ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o1) 
                                          | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o3) 
                                             | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o4) 
                                                | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o5)))))));
    __VdfgTmp_h58350fc7__0 = (1U & ((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o0)) 
                                    & (~ ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o1) 
                                          | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o2) 
                                             | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o3) 
                                                | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o4) 
                                                   | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o5) 
                                                      | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o6) 
                                                         | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o7) 
                                                            | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o8) 
                                                               | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o9) 
                                                                  | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o10) 
                                                                     | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o11) 
                                                                        | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o12) 
                                                                           | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o13) 
                                                                              | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o14)))))))))))))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__buf_icb_splt_indic 
        = (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o0) 
            << 8U) | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o1) 
                       << 7U) | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o3) 
                                  << 5U) | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o4) 
                                             << 4U) 
                                            | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o5) 
                                                << 3U) 
                                               | (IData)(__VdfgTmp_hbd5dd97a__0))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
        = (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o0) 
            << 0x10U) | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o1) 
                          << 0xfU) | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o2) 
                                       << 0xeU) | (
                                                   ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o3) 
                                                    << 0xdU) 
                                                   | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o4) 
                                                       << 0xcU) 
                                                      | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o5) 
                                                          << 0xbU) 
                                                         | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o6) 
                                                             << 0xaU) 
                                                            | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o7) 
                                                                << 9U) 
                                                               | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o8) 
                                                                   << 8U) 
                                                                  | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o9) 
                                                                      << 7U) 
                                                                     | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o10) 
                                                                         << 6U) 
                                                                        | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o11) 
                                                                            << 5U) 
                                                                           | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o12) 
                                                                               << 4U) 
                                                                              | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o13) 
                                                                                << 3U) 
                                                                                | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o14) 
                                                                                << 2U) 
                                                                                | (IData)(__VdfgTmp_h58350fc7__0))))))))))))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r)
            ? (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__dat_dfflr__DOT__qout_r)
            : (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__buf_icb_splt_indic));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT____VdfgTmp_h2342b78a__0 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r) 
                     & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__buf_icb_splt_indic) 
                        != (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__dat_dfflr__DOT__qout_r)))) 
                 & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r)
            ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__dat_dfflr__DOT__qout_r
            : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_h2342b78a__0 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r) 
                     & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                        != vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__dat_dfflr__DOT__qout_r))) 
                 & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__sysmem_icb_rsp_ready = 
        (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                   >> 1U)) & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                              >> 4U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                                >> 3U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                                >> 7U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_f_0_d_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                                >> 5U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_ready 
        = (IData)(((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                       >> 1U)) & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                                  >> 8U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__i_icb_cmd_valid_pre 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT____VdfgTmp_h2342b78a__0));
    vlSelf->soc_cpu_tb__DOT__sysper_icb_rsp_ready = 
        (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                   >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                              >> 4U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_rsp_ready 
        = (IData)(((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                       >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                  >> 0x10U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 0xeU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 3U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 0xaU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 7U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 9U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 6U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 8U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 5U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 0xbU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_rsp_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 2U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 0xfU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_d_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                                >> 0xcU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_h2342b78a__0));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_rsp_valid) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_rsp_ready)));
    vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_valid = 
        ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o4) 
         & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT____VdfgTmp_h1b6d41ca__0 
        = ((IData)(__VdfgTmp_hbd5dd97a__0) & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o1) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_f_0_a_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o3) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o5) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__icb_cmd_o0) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_rx__DOT__buf_vld_clr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_rx__DOT__buf_vld_dfflr__DOT__qout_r) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_rsp_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_rsp_valid) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_rsp_ready)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o0) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o2) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o13) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_h1b6d41ca__0 
        = ((IData)(__VdfgTmp_h58350fc7__0) & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_valid = 
        ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o12) 
         & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o7) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o10) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o5) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o1) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o14) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_a_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o4) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o3) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o6) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o9) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o8) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__icb_cmd_o11) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__i_icb_cmd_valid_pre));
    vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_read = 
        ((IData)(vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_valid) 
         & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
            >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_wdata = 
        ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_valid))) 
         & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
             << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                          >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_wmask = 
        (0xfU & ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_valid))) 
                 & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                     << 0x17U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                                  >> 9U))));
    vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_addr = 
        ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_valid))) 
         & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
             << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                          >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__qspi0_ro_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_f_0_a_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_axi_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_axi_wstrb 
        = (0xfU & ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_valid))) 
                   & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                       << 0x17U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                                    >> 9U))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__i_icb_cmd_hsked 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_addr 
        = ((- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_read 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_wdata 
        = ((- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_tx__DOT__vld_set 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioA_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__gpioB_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_wdata = 
        ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_valid))) 
         & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
             << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                          >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_read = 
        ((IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_valid) 
         & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
            >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_wmask = 
        (0xfU & ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_valid))) 
                 & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                     << 0x17U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                                  >> 9U))));
    vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_addr = 
        ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_valid))) 
         & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
             << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                          >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi1_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__spi2_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_axi_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_axi_wstrb 
        = (0xfU & ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_valid))) 
                   & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                       << 0x17U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                                    >> 9U))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_a_bits_data 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_a_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_a_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4897 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_a_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_d_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_a_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c0_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_addr 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_valid) 
           & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[2U] 
              >> 0xdU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_wdata 
        = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i2c1_apb_icb_cmd_valid))) 
           & ((soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[1U] 
               << 0x13U) | (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__mux_rdat[0U] 
                            >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__ram__DOT__address_ok = 
        ((0xa0000000U <= vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_addr) 
         & (0x80000U > (vlSelf->soc_cpu_tb__DOT__sysmem_icb_cmd_addr 
                        - (IData)(0xa0000000U))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_rdata[7U] 
        = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mrom_top__DOT__u_sirv_mrom__DOT__mask_rom
        [(0x3ffU & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_addr 
                    >> 2U))];
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_read)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_ready 
        = (1U & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 3U)) & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_read)
                                 ? (~ ((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                       >> 1U)) : ((~ 
                                                   ((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                    >> 1U)) 
                                                  & (~ 
                                                     ((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                      >> 1U))))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__icb_wr_ena 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_read)) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__i_icb_cmd_hsked));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__rom_dout 
        = ((0x1cU >= (0x1fU & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_addr 
                               >> 2U))) ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_rom__DOT__debug_rom
           [(0x1fU & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_addr 
                      >> 2U))] : 0U);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__icb_access_dbgram_ena 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__i_icb_cmd_hsked) 
           & (0x400U == (0xf00U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_addr)));
    vlSelf->soc_cpu_tb__DOT__accelerator__DOT__address_ok 
        = (IData)((0x11000000U == (0xffffff03U & vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_addr)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__icb_wr_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_valid) 
           & ((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_read)) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_ready)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[0xfU] 
        = (((- (IData)((4U == (0xfffU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_addr)))) 
            & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__hfxoscen_dfflrs__DOT__qout_r) 
               << 0x1eU)) | (((- (IData)((8U == (0xfffU 
                                                 & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_addr)))) 
                              & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__pll_RESET_dfflrs__DOT__qout_r) 
                                  << 0x1eU) | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__pll_ASLEEP_dfflrs__DOT__qout_r) 
                                                << 0x1dU) 
                                               | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__pllbypass_dfflrs__DOT__qout_r) 
                                                   << 0x12U) 
                                                  | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__pll_OD) 
                                                      << 0xdU) 
                                                     | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__pll_M) 
                                                         << 5U) 
                                                        | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__pll_N))))))) 
                             | ((- (IData)((0xcU == 
                                            (0xfffU 
                                             & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_addr)))) 
                                & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__plloutdivby1_dfflrs__DOT__qout_r) 
                                    << 8U) | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__plloutdiv_dfflr__DOT__qout_r)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_read)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_ready 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                 & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_read)
                     ? (~ ((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                           >> 1U)) : ((~ ((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                          >> 1U)) & 
                                      (~ ((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                          >> 1U))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4904 
        = ((4U != ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_read)
                    ? 4U : 0U)) & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4897));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4852 
        = (((IData)(1U) << (0x1fU & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                     >> 2U))) & (0xccc2f38cU 
                                                 | (((0U 
                                                      == 
                                                      (0x3e0U 
                                                       & (0x1dU 
                                                          ^ 
                                                          (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                           >> 2U)))) 
                                                     << 0x1dU) 
                                                    | (((0U 
                                                         == 
                                                         (0x3e0U 
                                                          & (0x1cU 
                                                             ^ 
                                                             (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                              >> 2U)))) 
                                                        << 0x1cU) 
                                                       | (((0U 
                                                            == 
                                                            (0x3e0U 
                                                             & (0x19U 
                                                                ^ 
                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                 >> 2U)))) 
                                                           << 0x19U) 
                                                          | (((0U 
                                                               == 
                                                               (0x3e0U 
                                                                & (0x18U 
                                                                   ^ 
                                                                   (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                    >> 2U)))) 
                                                              << 0x18U) 
                                                             | (((0U 
                                                                  == 
                                                                  (0x3e0U 
                                                                   & (0x15U 
                                                                      ^ 
                                                                      (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                       >> 2U)))) 
                                                                 << 0x15U) 
                                                                | (((0U 
                                                                     == 
                                                                     (0x3e0U 
                                                                      & (0x14U 
                                                                         ^ 
                                                                         (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                          >> 2U)))) 
                                                                    << 0x14U) 
                                                                   | (((0U 
                                                                        == 
                                                                        (0x3e0U 
                                                                         & (0x13U 
                                                                            ^ 
                                                                            (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                             >> 2U)))) 
                                                                       << 0x13U) 
                                                                      | (((0U 
                                                                           == 
                                                                           (0x3e0U 
                                                                            & (0x12U 
                                                                               ^ 
                                                                               (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                                >> 2U)))) 
                                                                          << 0x12U) 
                                                                         | (((0U 
                                                                              == 
                                                                              (0x3e0U 
                                                                               & (0x10U 
                                                                                ^ 
                                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                                >> 2U)))) 
                                                                             << 0x10U) 
                                                                            | (((0U 
                                                                                == 
                                                                                (0x3e0U 
                                                                                & (0xbU 
                                                                                ^ 
                                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                                >> 2U)))) 
                                                                                << 0xbU) 
                                                                               | (((0U 
                                                                                == 
                                                                                (0x3e0U 
                                                                                & (0xaU 
                                                                                ^ 
                                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                                >> 2U)))) 
                                                                                << 0xaU) 
                                                                                | (((0U 
                                                                                == 
                                                                                (0x3e0U 
                                                                                & (6U 
                                                                                ^ 
                                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                                >> 2U)))) 
                                                                                << 6U) 
                                                                                | (((0U 
                                                                                == 
                                                                                (0x3e0U 
                                                                                & (5U 
                                                                                ^ 
                                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                                >> 2U)))) 
                                                                                << 5U) 
                                                                                | (((0U 
                                                                                == 
                                                                                (0x3e0U 
                                                                                & (4U 
                                                                                ^ 
                                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                                >> 2U)))) 
                                                                                << 4U) 
                                                                                | (((0U 
                                                                                == 
                                                                                (0x3e0U 
                                                                                & (1U 
                                                                                ^ 
                                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                                >> 2U)))) 
                                                                                << 1U) 
                                                                                | (0U 
                                                                                == 
                                                                                (0x3e0U 
                                                                                & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__qspi0_icb_cmd_addr 
                                                                                >> 2U))))))))))))))))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 3U)) & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_valid) 
                          & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_ready)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__cleardebint_ena 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__icb_wr_ena) 
           & (0x100U == (0xfffU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_addr)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__sethaltnot_ena 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__icb_wr_ena) 
           & (0x10cU == (0xfffU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_addr)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__icb_wr_en_pllcfg 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__icb_wr_en) 
           & (8U == (0xfffU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_addr)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__plloutdiv_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_hclkgen_regs__DOT__icb_wr_en) 
           & (0xcU == (0xfffU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_addr)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_valid) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_ready)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_3596 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4904) 
           & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4852 
              >> 0x10U));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_3236 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4904) 
           & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4852 
              >> 1U));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_2676 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4904) 
           & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4852 
              >> 0xaU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_3756 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4904) 
           & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4852 
              >> 0xbU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_3356 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4904) 
           & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4852 
              >> 0x1cU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_2796 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4904) 
           & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__u_sirv_flash_qspi__DOT__T_4852 
              >> 0x19U));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (0x1fU & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__wen)
                     ? (1U | ((0x1cU & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                        << 2U)) | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                                   << 1U)))
                     : VL_SHIFTR_III(5,5,32, (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                               << 1U) 
                                              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__dm_debint_clr 
        = ((~ vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_wdata) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__cleardebint_ena));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__dm_haltnot_set 
        = ((~ vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__dm_icb_cmd_wdata) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__sethaltnot_ena));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (3U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                           << 1U)) : VL_SHIFTR_III(2,2,32, 
                                                   (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                     << 1U) 
                                                    | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__14(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__14\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_rdata[3U] 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read)
            ? (IData)((vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__mux_rdat 
                       >> 3U)) : 0U);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_rdata[2U] 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read)
            ? (IData)((vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__mux_rdat 
                       >> 3U)) : 0U);
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__29(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__29\n"); );
    // Init
    IData/*16:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_hb2547522__0;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_hb2547522__0 = 0;
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                 & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 1U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 2U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 3U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 4U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 5U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 6U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 7U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 8U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 9U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 0xaU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 0xbU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 0xcU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 0xdU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 0xeU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 0xfU)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_rsp_err) 
                    >> 0x10U)));
    vlSelf->soc_cpu_tb__DOT__accelerator__DOT__fire 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_rsp_valid)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & (0U != ((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_rx__DOT__buf_vld_dfflr__DOT__qout_r) 
                                   << 0x10U) | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_valid) 
                                                 << 0xfU) 
                                                | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                    << 0xeU) 
                                                   | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                       << 0xdU) 
                                                      | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_a_valid) 
                                                          << 0xcU) 
                                                         | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                             << 0xbU) 
                                                            | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                                << 0xaU) 
                                                               | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                                   << 9U) 
                                                                  | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                                      << 8U) 
                                                                     | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                                         << 7U) 
                                                                        | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                                            << 6U) 
                                                                           | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                                               << 5U) 
                                                                              | (((IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_rsp_valid) 
                                                                                << 4U) 
                                                                                | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb.__PVT__u_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                                                << 3U) 
                                                                                | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_rsp_valid) 
                                                                                << 2U) 
                                                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_h1b6d41ca__0)))))))))))))))) 
                                 & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__i_aon_icb_cmd_ready) 
            << 0x10U) | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__hclkgen_icb_cmd_ready) 
                          << 0xfU) | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb.i_icb_cmd_ready) 
                                       << 0xeU) | (
                                                   ((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb.i_icb_cmd_ready) 
                                                    << 0xdU) 
                                                   | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_qspi0_top__DOT__io_tl_r_0_d_ready) 
                                                       << 0xcU) 
                                                      | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb.i_icb_cmd_ready) 
                                                          << 0xbU) 
                                                         | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb.i_icb_cmd_ready) 
                                                             << 0xaU) 
                                                            | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb.i_icb_cmd_ready) 
                                                                << 9U) 
                                                               | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb.i_icb_cmd_ready) 
                                                                   << 8U) 
                                                                  | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb.i_icb_cmd_ready) 
                                                                      << 7U) 
                                                                     | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb.i_icb_cmd_ready) 
                                                                         << 6U) 
                                                                        | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb.i_icb_cmd_ready) 
                                                                            << 5U) 
                                                                           | ((0x10U 
                                                                               & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_rsp_valid)) 
                                                                                << 4U)) 
                                                                              | (((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb.i_icb_cmd_ready) 
                                                                                << 3U) 
                                                                                | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_ready) 
                                                                                << 2U) 
                                                                                | (1U 
                                                                                & ((~ 
                                                                                ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                                                >> 1U)) 
                                                                                & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__o_icb_rsp_port_id)))))))))))))))));
    vlSelf->soc_cpu_tb__DOT__accelerator__DOT__pop 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__accelerator__DOT__fire) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__accelerator__DOT__address_ok) 
              & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_read)) 
                 & ((0xfU == (IData)(vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_wmask)) 
                    & ((0x2cU == (0xffU & vlSelf->soc_cpu_tb__DOT__sysper_icb_cmd_addr)) 
                       & (8U == (IData)(vlSelf->soc_cpu_tb__DOT__accelerator__DOT__core__DOT__state)))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                 & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 1U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 2U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 3U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 4U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 5U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 6U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 7U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 8U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 9U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 0xaU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 0xbU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 0xcU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 0xdU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 0xeU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 0xfU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready 
        = (1U & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
                 | ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__buf_icb_splt_indic 
                     & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__splt_bus_icb_cmd_ready) 
                    >> 0x10U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__sel_o_apb_cmd_ready) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_h2342b78a__0)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_hb2547522__0 
        = (1U & (~ ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r)) 
                    & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__ren) 
                       & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__wen)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_set 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r)) 
           & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_hb2547522__0) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__ren)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_clr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT__splt_num_gt_1_gen__DOT__fifo_dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r) 
           & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_buf_icb_splt__DOT____VdfgTmp_hb2547522__0) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_sirv_ppi_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__wen)));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__31(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__31\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_prdata 
        = ((0x200U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
            ? 0U : ((0x100U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                     ? ((0x80U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                         ? 0U : ((0x40U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                  ? 0U : ((0x20U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                           ? 0U : (
                                                   (0x10U 
                                                    & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                    ? 0U
                                                    : 
                                                   ((8U 
                                                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                     ? 0U
                                                     : 
                                                    ((4U 
                                                      & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                      ? (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_clk_en)
                                                      : 
                                                     (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_event_en) 
                                                       << 0x10U) 
                                                      | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_event_sel_3) 
                                                          << 0xcU) 
                                                         | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_event_sel_2) 
                                                             << 8U) 
                                                            | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_event_sel_1) 
                                                                << 4U) 
                                                               | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_event_sel_0)))))))))))
                     : ((0x80U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                         ? ((0x40U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                             ? ((0x20U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                 ? ((0x10U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                     ? 0U : ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                              ? ((4U 
                                                  & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                  ? (IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3.__PVT__u_counter__DOT__r_counter)
                                                  : 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch3_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch3_lut)))
                                              : ((4U 
                                                  & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                  ? 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch2_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch2_lut))
                                                  : 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch1_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch1_lut)))))
                                 : ((0x10U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                     ? ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                         ? ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch0_flt) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch0_lut))
                                             : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch3_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch3_th)))
                                         : ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch2_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch2_th))
                                             : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch1_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch1_th))))
                                     : ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                         ? ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch0_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch0_th))
                                             : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_th)
                                         : ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_presc) 
                                                 << 0x10U) 
                                                | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_saw) 
                                                    << 0xcU) 
                                                   | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_in_clk) 
                                                       << 0xbU) 
                                                      | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_in_mode) 
                                                          << 8U) 
                                                         | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_in_sel)))))
                                             : 0U))))
                             : ((0x20U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                 ? ((0x10U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                     ? 0U : ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                              ? ((4U 
                                                  & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                  ? (IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2.__PVT__u_counter__DOT__r_counter)
                                                  : 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch3_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch3_lut)))
                                              : ((4U 
                                                  & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                  ? 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch2_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch2_lut))
                                                  : 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch1_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch1_lut)))))
                                 : ((0x10U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                     ? ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                         ? ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch0_flt) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch0_lut))
                                             : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch3_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch3_th)))
                                         : ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch2_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch2_th))
                                             : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch1_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch1_th))))
                                     : ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                         ? ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch0_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch0_th))
                                             : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_th)
                                         : ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_presc) 
                                                 << 0x10U) 
                                                | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_saw) 
                                                    << 0xcU) 
                                                   | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_in_clk) 
                                                       << 0xbU) 
                                                      | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_in_mode) 
                                                          << 8U) 
                                                         | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_in_sel)))))
                                             : 0U)))))
                         : ((0x40U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                             ? ((0x20U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                 ? ((0x10U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                     ? 0U : ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                              ? ((4U 
                                                  & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                  ? (IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1.__PVT__u_counter__DOT__r_counter)
                                                  : 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch3_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch3_lut)))
                                              : ((4U 
                                                  & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                  ? 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch2_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch2_lut))
                                                  : 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch1_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch1_lut)))))
                                 : ((0x10U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                     ? ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                         ? ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch0_flt) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch0_lut))
                                             : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch3_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch3_th)))
                                         : ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch2_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch2_th))
                                             : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch1_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch1_th))))
                                     : ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                         ? ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch0_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch0_th))
                                             : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_th)
                                         : ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_presc) 
                                                 << 0x10U) 
                                                | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_saw) 
                                                    << 0xcU) 
                                                   | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_in_clk) 
                                                       << 0xbU) 
                                                      | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_in_mode) 
                                                          << 8U) 
                                                         | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_in_sel)))))
                                             : 0U))))
                             : ((0x20U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                 ? ((0x10U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                     ? 0U : ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                              ? ((4U 
                                                  & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                  ? (IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0.__PVT__u_counter__DOT__r_counter)
                                                  : 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch3_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch3_lut)))
                                              : ((4U 
                                                  & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                                  ? 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch2_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch2_lut))
                                                  : 
                                                 (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch1_flt) 
                                                   << 0x10U) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch1_lut)))))
                                 : ((0x10U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                     ? ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                         ? ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch0_flt) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch0_lut))
                                             : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch3_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch3_th)))
                                         : ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch2_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch2_th))
                                             : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch1_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch1_th))))
                                     : ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                         ? ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch0_mode) 
                                                 << 0x10U) 
                                                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch0_th))
                                             : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_th)
                                         : ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__pwm_apb_icb_cmd_addr)
                                             ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_presc) 
                                                 << 0x10U) 
                                                | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_saw) 
                                                    << 0xcU) 
                                                   | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_in_clk) 
                                                       << 0xbU) 
                                                      | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_in_mode) 
                                                          << 8U) 
                                                         | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_in_sel)))))
                                             : 0U))))))));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__34(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__34\n"); );
    // Init
    SData/*8:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err = 0;
    // Body
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err 
        = (1U | ((0x80U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__mrom_icb_cmd_read)) 
                           << 7U)) | (((IData)(vlSelf->soc_cpu_tb__DOT__sysmem_icb_rsp_err) 
                                       << 4U) | (8U 
                                                 & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read)
                                                      ? (IData)(
                                                                (vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__mux_rdat 
                                                                 >> 2U))
                                                      : 
                                                     ((IData)(vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer.__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__mux_rdat) 
                                                      >> 1U)) 
                                                    << 3U)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                 & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                     & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err)) 
                    >> 1U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                     & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err)) 
                    >> 2U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                     & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err)) 
                    >> 3U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                     & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err)) 
                    >> 4U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                     & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err)) 
                    >> 5U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                     & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err)) 
                    >> 6U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                     & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err)) 
                    >> 7U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__splt_num_gt_1_gen__DOT__ptr_1hot_rsp__DOT__sel_i_icb_rsp_err) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_i_icb_splt__DOT__o_icb_rsp_port_id) 
                     & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__splt_bus_icb_rsp_err)) 
                    >> 8U)));
}

void Vsoc_cpu_tb___024root___nba_sequent__TOP__0(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_apb_uart_sv__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0__0(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf);
void Vsoc_cpu_tb_apb_uart_sv__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1__0(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf);
void Vsoc_cpu_tb_apb_uart_sv__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2__0(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf);
void Vsoc_cpu_tb_apb_spi_master__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1__0(Vsoc_cpu_tb_apb_spi_master__A20* vlSelf);
void Vsoc_cpu_tb_apb_spi_master__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2__0(Vsoc_cpu_tb_apb_spi_master__A20* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__1(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_apb_spi_master__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2__1(Vsoc_cpu_tb_apb_spi_master__A20* vlSelf);
void Vsoc_cpu_tb_apb_spi_master__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1__1(Vsoc_cpu_tb_apb_spi_master__A20* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__2(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__3(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__4(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__5(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__6(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__7(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__8(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__9(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__10(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__11(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__0(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__0(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__0(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__0(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__12(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__13(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0(Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0(Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__14(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__15(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__16(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__17(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__18(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__19(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__20(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__21(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__22(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__23(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__24(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__25(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__1(Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__1(Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__26(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__27(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__28(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__29(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__30(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__31(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__32(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__33(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__34(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__35(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__36(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__37(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__38(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__39(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__40(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__0(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__41(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__1(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__42(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__43(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__44(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__2(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__3(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__0(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__0(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__0(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__0(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__6(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__7(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__8(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__9(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__10(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__11(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__12(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0(Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0(Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__0(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb_apb_spi_master__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1__0(Vsoc_cpu_tb_apb_spi_master__A20* vlSelf);
void Vsoc_cpu_tb_apb_spi_master__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2__0(Vsoc_cpu_tb_apb_spi_master__A20* vlSelf);
void Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0__0(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf);
void Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1__0(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf);
void Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2__0(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__15(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__16(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__17(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__18(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__19(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__20(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__21(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__45(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__22(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__46(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__23(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__24(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__25(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__26(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__47(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__27(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__2(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__48(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__1(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__1(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__1(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__1(Vsoc_cpu_tb_timer_module__NB30* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__28(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__30(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_apb_spi_master__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1__1(Vsoc_cpu_tb_apb_spi_master__A20* vlSelf);
void Vsoc_cpu_tb_apb_spi_master__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2__1(Vsoc_cpu_tb_apb_spi_master__A20* vlSelf);
void Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0__1(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf);
void Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1__1(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf);
void Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2__1(Vsoc_cpu_tb_apb_uart_sv__A20* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__32(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__33(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__35(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__36(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__37(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__38(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__39(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__40(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__41(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__42(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__43(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__44(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__45(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__46(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__47(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__48(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__49(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__50(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__49(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__50(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__51(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__52(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__53(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__1(Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__54(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_sequent__TOP__51(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__55(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__56(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__57(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__58(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__59(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__60(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__61(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__62(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__63(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__64(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__65(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__66(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__67(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__68(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__69(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__70(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__71(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__72(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__73(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__74(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__75(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__76(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__77(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__78(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__79(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__80(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__81(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__82(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__83(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__84(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__85(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__86(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__87(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__88(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__89(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__90(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__91(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__92(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__93(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__94(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__95(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__96(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__97(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__98(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__99(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__100(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___nba_comb__TOP__101(Vsoc_cpu_tb___024root* vlSelf);

void Vsoc_cpu_tb___024root___eval_nba(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___eval_nba\n"); );
    // Body
    if ((0x100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__0(vlSelf);
        Vsoc_cpu_tb_apb_uart_sv__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0));
        Vsoc_cpu_tb_apb_uart_sv__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1));
        Vsoc_cpu_tb_apb_uart_sv__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2));
        Vsoc_cpu_tb_apb_spi_master__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1));
        Vsoc_cpu_tb_apb_spi_master__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2));
        Vsoc_cpu_tb___024root___nba_sequent__TOP__1(vlSelf);
        Vsoc_cpu_tb_apb_spi_master__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2));
        Vsoc_cpu_tb_apb_spi_master__A20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1));
    }
    if ((0x1000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((0x20ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__3(vlSelf);
    }
    if ((4ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__4(vlSelf);
    }
    if ((8ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__5(vlSelf);
    }
    if ((0x10000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__6(vlSelf);
    }
    if ((0x8000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__7(vlSelf);
    }
    if ((0x800ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__8(vlSelf);
    }
    if ((0x40ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__9(vlSelf);
    }
    if ((0x80ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__10(vlSelf);
    }
    if ((0x200000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__11(vlSelf);
    }
    if ((0x1000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0));
    }
    if ((0x2000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1));
    }
    if ((0x4000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2));
    }
    if ((0x8000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3));
    }
    if ((0x400ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__12(vlSelf);
    }
    if ((0x20000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__13(vlSelf);
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer));
        Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer));
    }
    if ((0x40000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__14(vlSelf);
    }
    if ((0x200000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__15(vlSelf);
    }
    if ((0x400000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__16(vlSelf);
    }
    if ((0x800000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__17(vlSelf);
    }
    if ((0x80000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__18(vlSelf);
    }
    if ((0x2000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__19(vlSelf);
    }
    if ((0x8000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__20(vlSelf);
    }
    if ((0x20000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__21(vlSelf);
    }
    if ((0x2000000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__22(vlSelf);
    }
    if ((0x200000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__23(vlSelf);
    }
    if ((0x400000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__24(vlSelf);
    }
    if ((0x80000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__25(vlSelf);
        Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer));
    }
    if ((0x10000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__26(vlSelf);
    }
    if ((0x40000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__27(vlSelf);
    }
    if ((0x40000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__28(vlSelf);
    }
    if ((0x800000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__29(vlSelf);
    }
    if ((0x800000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__30(vlSelf);
    }
    if ((0x100000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__31(vlSelf);
    }
    if ((0x80000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__32(vlSelf);
    }
    if ((0x20000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__33(vlSelf);
    }
    if ((0x10000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__34(vlSelf);
    }
    if ((0x4000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__35(vlSelf);
    }
    if ((0x1000000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__36(vlSelf);
    }
    if ((0x100000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__37(vlSelf);
    }
    if ((0x10ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__38(vlSelf);
    }
    if ((0x100000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__39(vlSelf);
    }
    if ((0x1000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__40(vlSelf);
    }
    if ((0x102ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((0x100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__41(vlSelf);
    }
    if ((0x1100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__1(vlSelf);
    }
    if ((0x2000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__42(vlSelf);
    }
    if ((0x20ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__43(vlSelf);
    }
    if ((0x40ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__44(vlSelf);
    }
    if ((0x4000000000080ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__2(vlSelf);
    }
    if ((0x210000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__3(vlSelf);
    }
    if ((0xf000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__4(vlSelf);
    }
    if ((0xf000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__5(vlSelf);
        Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0));
        Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1));
        Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2));
        Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3));
    }
    if ((0x20000004ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__6(vlSelf);
    }
    if ((0x20000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__7(vlSelf);
    }
    if ((0x400000008000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__8(vlSelf);
    }
    if ((0x280000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__9(vlSelf);
    }
    if ((0x420000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__10(vlSelf);
    }
    if ((0x600000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__11(vlSelf);
    }
    if ((0x440000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__12(vlSelf);
    }
    if ((0x80020000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__13(vlSelf);
        Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer));
        Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb));
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb));
        Vsoc_cpu_tb_apb_spi_master__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1));
        Vsoc_cpu_tb_apb_spi_master__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2));
        Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0));
        Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1));
        Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2__0((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2));
        Vsoc_cpu_tb___024root___nba_comb__TOP__14(vlSelf);
    }
    if ((0x18000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__15(vlSelf);
    }
    if ((0x60000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__16(vlSelf);
    }
    if ((0x100040000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__17(vlSelf);
    }
    if ((0x100400000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__18(vlSelf);
    }
    if ((0x100440000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__19(vlSelf);
    }
    if ((0x100080000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__20(vlSelf);
    }
    if ((0xc0000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__21(vlSelf);
    }
    if ((0x200000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__45(vlSelf);
    }
    if ((0x230000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__22(vlSelf);
    }
    if ((0x10000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__46(vlSelf);
    }
    if ((0x30000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__23(vlSelf);
    }
    if ((0x6000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__24(vlSelf);
    }
    if ((0x1800000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__25(vlSelf);
    }
    if ((0x1c0000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__26(vlSelf);
    }
    if ((0x20000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__47(vlSelf);
    }
    if ((0x1800000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__27(vlSelf);
    }
    if ((0x20000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__2((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb));
    }
    if ((0x10ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__48(vlSelf);
    }
    if ((0x1000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0));
    }
    if ((0x2000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1));
    }
    if ((0x4000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2));
    }
    if ((0x8000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_timer_module__NB30___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3));
    }
    if ((0x102ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__28(vlSelf);
    }
    if ((0x80020000004ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__29(vlSelf);
    }
    if ((0x80020000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__30(vlSelf);
        Vsoc_cpu_tb_apb_spi_master__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1));
        Vsoc_cpu_tb_apb_spi_master__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2));
        Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0));
        Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1));
        Vsoc_cpu_tb_apb_uart_sv__A20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2));
    }
    if ((0x8002f000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__31(vlSelf);
    }
    if ((0x80020001100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__32(vlSelf);
    }
    if ((0x280020000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__33(vlSelf);
    }
    if ((0x80020000008ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__34(vlSelf);
    }
    if ((0x100680000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__35(vlSelf);
    }
    if ((0x100480000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__36(vlSelf);
    }
    if ((0x100280000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__37(vlSelf);
    }
    if ((0x4000030000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__38(vlSelf);
    }
    if ((0x6080000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__39(vlSelf);
    }
    if ((0x1e080000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__40(vlSelf);
    }
    if ((0x6000000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__41(vlSelf);
    }
    if ((0x6020000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__42(vlSelf);
    }
    if ((0x86020000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__43(vlSelf);
    }
    if ((0x6020000008ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__44(vlSelf);
    }
    if ((0x6420000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__45(vlSelf);
    }
    if ((0x1800000020000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__46(vlSelf);
    }
    if ((0x1800000030000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__47(vlSelf);
    }
    if ((0x3800000000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__48(vlSelf);
    }
    if ((0x400000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__49(vlSelf);
    }
    if ((0x10000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__50(vlSelf);
    }
    if ((0x230000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__49(vlSelf);
    }
    if ((0x1c00000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__50(vlSelf);
    }
    if ((0x7800000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__51(vlSelf);
    }
    if ((0x7f800000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__52(vlSelf);
    }
    if ((0x17800000c00ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__53(vlSelf);
    }
    if ((0x80020000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20___nba_comb__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb__1((&vlSymsp->TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb));
    }
    if ((0x110ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__54(vlSelf);
    }
    if ((0x20000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_sequent__TOP__51(vlSelf);
    }
    if ((0x80020000108ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__55(vlSelf);
    }
    if ((0x80020000110ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__56(vlSelf);
    }
    if ((0x80020000102ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__57(vlSelf);
    }
    if ((0x80020001104ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__58(vlSelf);
    }
    if ((0x280020000108ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__59(vlSelf);
    }
    if ((0x1006c0000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__60(vlSelf);
    }
    if ((0x100680000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__61(vlSelf);
    }
    if ((0x4000030000040ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__62(vlSelf);
    }
    if ((0x6180000400ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__63(vlSelf);
    }
    if ((0x86020000100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__64(vlSelf);
    }
    if ((0x86020000004ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__65(vlSelf);
    }
    if ((0x1800000230000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__66(vlSelf);
    }
    if ((0x4000000020000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__67(vlSelf);
    }
    if ((0x1800000030000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__68(vlSelf);
    }
    if ((0x3800000230000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__69(vlSelf);
    }
    if ((0x7c80000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__70(vlSelf);
    }
    if ((0x61c00000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__71(vlSelf);
    }
    if ((0x19c00000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__72(vlSelf);
    }
    if ((0x7fc00000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__73(vlSelf);
    }
    if ((0x7f840000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__74(vlSelf);
    }
    if ((0x20020000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__75(vlSelf);
    }
    if ((0x420000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__76(vlSelf);
    }
    if ((0x86020000108ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__77(vlSelf);
    }
    if ((0x40000300000c0ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__78(vlSelf);
    }
    if ((0x1e180000400ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__79(vlSelf);
    }
    if ((0x7ca0000008ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__80(vlSelf);
    }
    if ((0x19c80000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__81(vlSelf);
    }
    if ((0x7fe40000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__82(vlSelf);
    }
    if ((0x7f840000c00ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__83(vlSelf);
    }
    if ((0x7fc40000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__84(vlSelf);
    }
    if ((0x40000300001c0ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__85(vlSelf);
    }
    if ((0x41004f00000c0ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__86(vlSelf);
    }
    if ((0x1e580000400ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__87(vlSelf);
    }
    if ((0x7fe40000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__88(vlSelf);
    }
    if ((0x17fe40000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__89(vlSelf);
    }
    if ((0x7fec0000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__90(vlSelf);
    }
    if ((0x17fec0000000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__91(vlSelf);
    }
    if ((0x17fec0000c00ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__92(vlSelf);
    }
    if ((0x417fef00000c0ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__93(vlSelf);
    }
    if ((0x17fec0000001ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__94(vlSelf);
    }
    if ((0x417fef00000c1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__95(vlSelf);
    }
    if ((0x17fec0000c01ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__96(vlSelf);
    }
    if ((0x17ffc0010401ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__97(vlSelf);
    }
    if ((0x17ffc0000401ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__98(vlSelf);
    }
    if ((0x17ffc0010401ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__99(vlSelf);
    }
    if ((0x417fff00104c1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__100(vlSelf);
    }
    if ((0x17ffe0010409ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_cpu_tb___024root___nba_comb__TOP__101(vlSelf);
    }
}

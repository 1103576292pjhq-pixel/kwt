// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb.h for the primary calling header

#include "Vsoc_cpu_tb__pch.h"
#include "Vsoc_cpu_tb___024root.h"

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__75(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__75\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_aon_top__DOT__isl_icb_cmd_pack[0U] 
        = (IData)((((QData)((IData)((1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_rst)) 
                                           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_tx__DOT__dat_dfflr__DOT__qout_r[1U])))) 
                    << 0x20U) | (QData)((IData)(((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_rst)
                                                  ? 0U
                                                  : 
                                                 vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_tx__DOT__dat_dfflr__DOT__qout_r[0U])))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_aon_top__DOT__isl_icb_cmd_pack[1U] 
        = ((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_rst)
              ? 0U : ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_tx__DOT__dat_dfflr__DOT__qout_r[2U] 
                       << 0x1fU) | (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_tx__DOT__dat_dfflr__DOT__qout_r[1U] 
                                    >> 1U))) << 1U) 
           | (IData)(((((QData)((IData)((1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_rst)) 
                                               & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_tx__DOT__dat_dfflr__DOT__qout_r[1U])))) 
                        << 0x20U) | (QData)((IData)(
                                                    ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_rst)
                                                      ? 0U
                                                      : 
                                                     vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_tx__DOT__dat_dfflr__DOT__qout_r[0U])))) 
                      >> 0x20U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_aon_top__DOT__isl_icb_cmd_pack[2U] 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_rst)
             ? 0U : ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_tx__DOT__dat_dfflr__DOT__qout_r[2U] 
                      << 0x1fU) | (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_aon_icb_cdc_tx__DOT__dat_dfflr__DOT__qout_r[1U] 
                                   >> 1U))) >> 0x1fU);
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__76(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__76\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_aon_top__DOT__u_sirv_aon_wrapper__DOT__ResetCatchAndSync_1_1__DOT__reset_n_catch_reg__DOT__reg_0_rst 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_aon_top__DOT__u_sirv_aon_wrapper__DOT__aonrst_catch__DOT__reset_n_catch_reg__DOT__reg_0_q)) 
                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_rst)));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__77(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__77\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_sirv_mem_fab__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__wen));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__78(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__78\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_hclkgen__DOT__plloutdivclk) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_hclkgen__DOT__u_e203_subsys_gfcm__DOT__u_clk0_clkgate__DOT__enb)) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__clk) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_hclkgen__DOT__u_e203_subsys_gfcm__DOT__u_clk1_clkgate__DOT__enb)));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__79(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__79\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT____VdfgTmp_he0f10288__0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_jalr));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__80(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__80\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_rsp_fifo__DOT__dp_gt0__DOT__wen));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__81(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__81\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_e1_stage__DOT__dp_gt_0__DOT__vld_clr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_e1_stage__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r) 
           & ((2U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_e1_stage__DOT__dp_gt_0__DOT__dat_dfflr__DOT__qout_r))
               ? (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_rsp_ready)
               : (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_rsp_ready)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_o_rdy 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_e1_stage__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r)) 
                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_e1_stage__DOT__dp_gt_0__DOT__vld_clr)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_o_rdy));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__82(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__82\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rcv_data_buf_ena 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__nice_rsp_valid_rowsum) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_rsp_multicyc_ready)) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rcv_data_buf_set));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__fifo_o_rdy 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_rsp_multicyc_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_rsp_multicyc_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__fifo_o_rdy));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__83(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__83\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rowbuf_wdat_mux 
        = (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__lbuf_wr))) 
            & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_rsp_rdata) 
           | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rcv_data_buf_valid_dfflr__DOT__qout_r))) 
              & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rowbuf_r
                 [vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rowbuf_cnt_d_dfflr__DOT__qout_r] 
                 + vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rcv_data_buf_dfflr__DOT__qout_r)));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__84(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__84\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__nice_longp_wbck_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_rsp_multicyc_valid));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__85(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__85\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon)))) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__i_clk_gate_timer0__DOT__enb 
            = (1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_clk_en));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__i_clk_gate_timer1__DOT__enb 
            = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_clk_en) 
                     >> 1U));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__i_clk_gate_timer2__DOT__enb 
            = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_clk_en) 
                     >> 2U));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__i_clk_gate_timer3__DOT__enb 
            = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_clk_en) 
                     >> 3U));
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_clk_timer0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__i_clk_gate_timer0__DOT__enb));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_clk_timer1 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__i_clk_gate_timer1__DOT__enb));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_clk_timer2 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__i_clk_gate_timer2__DOT__enb));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_clk_timer3 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__i_clk_gate_timer3__DOT__enb));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__86(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__86\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon)))) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_exu_clkgate__DOT__enb 
            = (1U & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcgstop_dfflr__DOT__qout_r 
                     | ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty)) 
                        | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__excp_active) 
                           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_dfflr__DOT__qout_r)))));
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_core_exu 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_exu_clkgate__DOT__enb));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__87(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__87\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__jalr_rs1xn_dep 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT____VdfgTmp_he0f10288__0) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__dec_jalr_rs1xn) 
              & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty)) 
                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_dfflr__DOT__qout_r))));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__88(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__88\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_sel_nice 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__nice_longp_wbck_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_ready4nice));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_i_valid 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_sel_lsu) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu_o_valid)) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_sel_nice) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__nice_longp_wbck_valid)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT____VdfgTmp_ha99ec327__0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_i_valid) 
           & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_dfflrs__DOT__qout_r)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT____VdfgTmp_ha8bfb152__0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_i_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_dfflrs__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_flg_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_dfflrs__DOT__qout_r) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_i_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_wbck_o_valid 
        = (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_buserr)) 
            & ((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__oitf_entries__BRA__1__KET____DOT__rdwen_dfflrs__DOT__qout_r) 
                 << 1U) | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__oitf_entries__BRA__0__KET____DOT__rdwen_dfflrs__DOT__qout_r)) 
               >> (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_dfflrs__DOT__qout_r))) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_i_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_valid 
        = (((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_sel_nice) 
                & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_icb_rsp_valid) 
                   & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu_o_wbck_err)))) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_buserr)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_i_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_nxt 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_flg_ena)) 
                 & ((IData)(1U) + (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_dfflrs__DOT__qout_r))));
    vlSelf->__VdfgTmp_hcb9a99a4__0 = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_valid) 
                                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_buserr));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__longp_excp_flush_req_ld_buserr 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_sel_lsu) 
            & (IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_rsp_usr 
                       >> 0x24U))) & (IData)(vlSelf->__VdfgTmp_hcb9a99a4__0));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__longp_excp_flush_req_st_buserr 
        = (((~ (IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_rsp_usr 
                        >> 0x24U))) & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_sel_lsu)) 
           & (IData)(vlSelf->__VdfgTmp_hcb9a99a4__0));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__89(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__89\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_hb91f7aef__0 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__irq_req)) 
                 & ((~ ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__dcause_dfflr__DOT__qout_r)) 
                        & (((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                            & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__step_req_dfflr__DOT__qout_r)) 
                               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_irq_sync__DOT__master_gen__DOT__u_dbg_irq_sync__DOT__sync_gen__BRA__1__KET____DOT__i_is_not_0__DOT__sync_dffr__DOT__qout_r))) 
                           | (((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                               & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h66d90a81__0) 
                                  & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h57fc5267__0))) 
                              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__step_req_dfflr__DOT__qout_r))))) 
                    & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_valid)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__flush_req 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_valid) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__nonalu_dbg_entry_req_raw) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__irq_req)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h76d88b6e__0 
        = (1U & (~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__flush_req) 
                    & (0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)))));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__90(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__90\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h968720ef__0 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_valid)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_pc_vld_dfflr__DOT__qout_r));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__91(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__91\n"); );
    // Init
    CData/*2:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func3;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func3 = 0;
    CData/*6:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func7;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func7 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__opcode_custom3;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__opcode_custom3 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_h50318ff0__0;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_h50318ff0__0 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_h73f9f76d__0;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_h73f9f76d__0 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_read;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_read = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_lock;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_lock = 0;
    CData/*3:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu2biu_icb_cmd_wmask;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu2biu_icb_cmd_wmask = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_misalgn;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_misalgn = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_buserr;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_buserr = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_unalgn;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_unalgn = 0;
    IData/*31:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_gen_op2;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_gen_op2 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_habddf295__0;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_habddf295__0 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h2c30e6a5__0;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h2c30e6a5__0 = 0;
    IData/*31:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1 = 0;
    IData/*31:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_add;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_add = 0;
    QData/*34:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_op2;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_op2 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_addsub;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_addsub = 0;
    IData/*31:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__xorer_res;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__xorer_res = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_scond;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_scond = 0;
    IData/*31:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wdata;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wdata = 0;
    CData/*3:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wmask;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wmask = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_lock;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_lock = 0;
    CData/*1:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_size;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_size = 0;
    CData/*0:0*/ __VdfgTmp_h856f476a__0;
    __VdfgTmp_h856f476a__0 = 0;
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_store 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h76d88b6e__0) 
           & (vlSelf->__VdfgTmp_h5f150f9b__0 >> 5U));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_load 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h76d88b6e__0) 
           & (vlSelf->__VdfgTmp_h5f150f9b__0 >> 4U));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_amo 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h76d88b6e__0) 
           & (vlSelf->__VdfgTmp_h5f150f9b__0 >> 0xaU));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_gen_op2 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_amo) 
            | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_load) 
                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_store)) 
               & (vlSelf->__VdfgTmp_h5f150f9b__0 >> 9U)))
            ? 0U : ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu))) 
                    & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__dec_imm));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h2c30e6a5__0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_amo) 
           & ((2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
              | ((3U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                 | (6U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_add 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu) 
            & (IData)((0x10U == (0x20010U & vlSelf->__VdfgTmp_h32817b85__0)))) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu) 
               & (vlSelf->__VdfgTmp_hc84510d4__0 >> 4U)) 
              | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
                 & (((4U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                     & (vlSelf->__VdfgTmp_h5f150f9b__0 
                        >> 0xcU)) | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h2c30e6a5__0) 
                                     | (0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)))))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1 
        = (((((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu))) 
              << 0xbU) | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu))) 
                          >> 0x15U)) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu_op1) 
           | (((((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu))) 
                 << 0xbU) | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu))) 
                             >> 0x15U)) & ((0x10U & vlSelf->__VdfgTmp_hc84510d4__0)
                                            ? ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu))) 
                                               & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_pc_dfflr__DOT__qout_r)
                                            : ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu))) 
                                               & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_rs1))) 
              | ((((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu))) 
                   << 0xbU) | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu))) 
                               >> 0x15U)) & ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r))
                                              ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs1
                                              : ((4U 
                                                  == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r))
                                                  ? (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r)
                                                  : 
                                                 ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h2c30e6a5__0)
                                                   ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs1
                                                   : 0U))))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2 
        = (((((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu))) 
              << 0xbU) | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu))) 
                          >> 0x15U)) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu_op2) 
           | (((((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu))) 
                 << 0xbU) | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu))) 
                             >> 0x15U)) & ((0x10U & vlSelf->__VdfgTmp_hc84510d4__0)
                                            ? ((8U 
                                                & vlSelf->__VdfgTmp_hc84510d4__0)
                                                ? 4U
                                                : 2U)
                                            : ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu))) 
                                               & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_rs2))) 
              | ((((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu))) 
                   << 0xbU) | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu))) 
                               >> 0x15U)) & ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r))
                                              ? soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_gen_op2
                                              : ((4U 
                                                  == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r))
                                                  ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs2
                                                  : 
                                                 ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h2c30e6a5__0)
                                                   ? soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_gen_op2
                                                   : 0U))))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_addsub 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu)
             ? (((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__booth_code) 
                     >> 2U)) & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel1)) 
                | (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_exe_alu_sub)) 
                    & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel2)) 
                   | (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_quot_corr_alu_sub)) 
                       & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel3)) 
                      | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel4) 
                          & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_quot_corr_alu_sub)) 
                         | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel5)))))
             : (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_add)) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_sub));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__xorer_res 
        = ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_hc1c55508__0 
            & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1) 
           ^ (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_hc1c55508__0 
              & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_op2 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu)
            ? (((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel1))) 
                & (((- (QData)((IData)((1U & (~ (((0U 
                                                   == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__booth_code)) 
                                                  | (7U 
                                                     == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__booth_code))) 
                                                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__booth_sel_two))))))) 
                    & (((QData)((IData)((7U & (- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__mul_rs2_sign)))))) 
                        << 0x20U) | (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_i_rs2)))) 
                   | ((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__booth_sel_two))) 
                      & (((QData)((IData)((3U & (- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__mul_rs2_sign)))))) 
                          << 0x21U) | ((QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_i_rs2)) 
                                       << 1U))))) | 
               (((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel2))) 
                 & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h5c756b1e__0) 
                | ((1ULL & (- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel3)))) 
                   | (((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel4))) 
                       | (- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel5)))) 
                      & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h5c756b1e__0))))
            : (((QData)((IData)((7U & (- (IData)(((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_hd3623de1__0) 
                                                  & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2 
                                                     >> 0x1fU))))))) 
                << 0x20U) | (QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
        = (0x7ffffffffULL & (((- (QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_addsub))) 
                              & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu)
                                  ? (((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel1))) 
                                      & ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r))
                                          ? 0ULL : 
                                         (((QData)((IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r 
                                                                       >> 0x20U))))) 
                                           << 0x22U) 
                                          | vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_remd_corr_alu_op1))) 
                                     | ((0x3ffffffffULL 
                                         & ((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel2))) 
                                            & ((0U 
                                                == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r))
                                                ? (- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_rs1_sign)))
                                                : (
                                                   ((QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__part_remd_sft1_dfflr__DOT__qout_r)) 
                                                    << 0x21U) 
                                                   | vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r)))) 
                                        | (((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel3))) 
                                            & (((QData)((IData)(
                                                                (1U 
                                                                 & (IData)(
                                                                           (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_1_dffl__DOT__qout_r 
                                                                            >> 0x20U))))) 
                                                << 0x21U) 
                                               | vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_1_dffl__DOT__qout_r)) 
                                           | (((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel4))) 
                                               | (- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel5)))) 
                                              & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_remd_corr_alu_op1))))
                                  : (((QData)((IData)(
                                                      (7U 
                                                       & (- (IData)(
                                                                    ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_hd3623de1__0) 
                                                                     & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1 
                                                                        >> 0x1fU))))))) 
                                      << 0x20U) | (QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1))))) 
                             + (((- (QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_addsub))) 
                                 & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_sub)
                                     ? (~ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_op2)
                                     : soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_op2)) 
                                + (QData)((IData)(((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_addsub) 
                                                   & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__adder_sub)))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_remd 
        = (0x1ffffffffULL & ((2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r))
                              ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r
                              : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_need_corrct 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__i_op_div) 
           & (((0U != vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r) 
               & ((IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r 
                           >> 0x20U)) ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_rs1_sign))) 
              | ((~ (IData)((0U != (0x3ffffffffULL 
                                    & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res)))) 
                 | (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r 
                    == (((QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_rs2_sign)) 
                         << 0x20U) | (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_i_rs2)))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_addr[1U] 
        = (((- (IData)((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu) 
                         & (vlSelf->__VdfgTmp_h32817b85__0 
                            >> 0xaU)) | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
                                         & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu_or))))) 
            & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1 
               | soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2)) 
           | (((- (IData)((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu) 
                            & (vlSelf->__VdfgTmp_h32817b85__0 
                               >> 0xbU)) | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
                                            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu_and))))) 
               & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1 
                  & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2)) 
              | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_xor))) 
                  & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__xorer_res) 
                 | (((- (IData)(((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_add) 
                                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_sub)))) 
                     & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res)) 
                    | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_srl))) 
                        & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__srl_res) 
                       | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_sll))) 
                           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sll_res) 
                          | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_sra))) 
                              & ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__srl_res 
                                  & (0xffffffffU >> (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__shifter_in2))) 
                                 | ((~ (0xffffffffU 
                                        >> (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__shifter_in2))) 
                                    & (- (IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu_op1 
                                                  >> 0x1fU)))))) 
                             | (((- (IData)((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu) 
                                              & (vlSelf->__VdfgTmp_h32817b85__0 
                                                 >> 0xeU)) 
                                             | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
                                                & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu_swap))))) 
                                 & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2) 
                                | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_slttu))) 
                                    & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_slttu) 
                                        & (IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                   >> 0x20U)))
                                        ? 1U : 0U)) 
                                   | ((- (IData)(((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_he5ed8cc2__0) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_h3e8a08b0__0)))) 
                                      & ((((~ (IData)(
                                                      (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                       >> 0x20U))) 
                                           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_he5ed8cc2__0)) 
                                          | ((IData)(
                                                     (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                      >> 0x20U)) 
                                             & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_h3e8a08b0__0)))
                                          ? soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1
                                          : soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2)))))))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_branchslv__DOT__brchmis_need_flush 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_bjp) 
            & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_bjp_prdt) 
               ^ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu) 
                  & ((vlSelf->__VdfgTmp_hc84510d4__0 
                      >> 4U) | (((~ (IData)((0U != soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__xorer_res))) 
                                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_cmp_eq)) 
                                | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_cmp_ne) 
                                    & (0U != soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__xorer_res)) 
                                   | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_cmp_lt) 
                                       & (IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                  >> 0x20U))) 
                                      | (((~ (IData)(
                                                     (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                      >> 0x20U))) 
                                          & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_cmp_gt)) 
                                         | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_cmp_ltu) 
                                             & (IData)(
                                                       (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                        >> 0x20U))) 
                                            | ((~ (IData)(
                                                          (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                           >> 0x20U))) 
                                               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_cmp_gtu))))))))))) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_branchslv__DOT____VdfgTmp_h31a1a48a__0));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_addr 
        = (((- (IData)((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu) 
                         & (vlSelf->__VdfgTmp_h32817b85__0 
                            >> 0xaU)) | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
                                         & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu_or))))) 
            & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1 
               | soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2)) 
           | (((- (IData)((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu) 
                            & (vlSelf->__VdfgTmp_h32817b85__0 
                               >> 0xbU)) | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
                                            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu_and))))) 
               & (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1 
                  & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2)) 
              | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_xor))) 
                  & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__xorer_res) 
                 | (((- (IData)(((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_add) 
                                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_sub)))) 
                     & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res)) 
                    | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_srl))) 
                        & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__srl_res) 
                       | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_sll))) 
                           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sll_res) 
                          | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_sra))) 
                              & ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__srl_res 
                                  & (0xffffffffU >> (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__shifter_in2))) 
                                 | ((~ (0xffffffffU 
                                        >> (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__shifter_in2))) 
                                    & (- (IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu_op1 
                                                  >> 0x1fU)))))) 
                             | (((- (IData)((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__alu_req_alu) 
                                              & (vlSelf->__VdfgTmp_h32817b85__0 
                                                 >> 0xeU)) 
                                             | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
                                                & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu_swap))))) 
                                 & soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2) 
                                | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_slttu))) 
                                    & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__op_slttu) 
                                        & (IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                   >> 0x20U)))
                                        ? 1U : 0U)) 
                                   | ((- (IData)(((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_he5ed8cc2__0) 
                                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_h3e8a08b0__0)))) 
                                      & ((((~ (IData)(
                                                      (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                       >> 0x20U))) 
                                           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_he5ed8cc2__0)) 
                                          | ((IData)(
                                                     (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                      >> 0x20U)) 
                                             & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT____VdfgTmp_h3e8a08b0__0)))
                                          ? soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op1
                                          : soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__mux_op2)))))))))));
    if (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_amo) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_wdata[1U] 
            = (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_1_dffl__DOT__qout_r);
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_wmask[1U] 
            = (0xfU & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_leftover_err_dfflr__DOT__qout_r)
                        ? 0U : 0xfU));
    } else {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_wdata[1U] 
            = (((- (IData)((0U == (3U & (vlSelf->__VdfgTmp_h5f150f9b__0 
                                         >> 6U))))) 
                & ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs2 
                    << 0x18U) | ((0xff0000U & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs2 
                                               << 0x10U)) 
                                 | ((0xff00U & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs2 
                                                << 8U)) 
                                    | (0xffU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs2))))) 
               | (((- (IData)((1U == (3U & (vlSelf->__VdfgTmp_h5f150f9b__0 
                                            >> 6U))))) 
                   & ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs2 
                       << 0x10U) | (0xffffU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs2))) 
                  | ((- (IData)((2U == (3U & (vlSelf->__VdfgTmp_h5f150f9b__0 
                                              >> 6U))))) 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_rs2)));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_wmask[1U] 
            = (0xfU & (((- (IData)((0U == (3U & (vlSelf->__VdfgTmp_h5f150f9b__0 
                                                 >> 6U))))) 
                        & ((IData)(1U) << (3U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_addr))) 
                       | (((- (IData)((1U == (3U & 
                                              (vlSelf->__VdfgTmp_h5f150f9b__0 
                                               >> 6U))))) 
                           & ((IData)(3U) << (2U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_addr))) 
                          | (- (IData)((2U == (3U & 
                                               (vlSelf->__VdfgTmp_h5f150f9b__0 
                                                >> 6U))))))));
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_1_nxt 
        = (0x1ffffffffULL & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu)
                              ? ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel1)
                                  ? (((QData)((IData)(
                                                      (3U 
                                                       & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res)))) 
                                      << 0x1fU) | (QData)((IData)(
                                                                  (0x7fffffffU 
                                                                   & ((0U 
                                                                       == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r))
                                                                       ? 
                                                                      (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__mul_rs1_sign) 
                                                                        << 0x1eU) 
                                                                       | (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_i_rs1 
                                                                          >> 2U))
                                                                       : (IData)(
                                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_1_dffl__DOT__qout_r 
                                                                                >> 2U)))))))
                                  : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__corrct_phase)
                                      ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res
                                      : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_hfdf76643__0)
                                          ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_quot
                                          : (((QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h4c5b0848__0)) 
                                              << 1U) 
                                             | (QData)((IData)(
                                                               (1U 
                                                                & (~ 
                                                                   ((IData)(
                                                                            (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                                                             >> 0x21U)) 
                                                                    ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_rs2_sign))))))))))
                              : (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_addr))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__wbck_condi 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__i_b2b) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__special_cases) 
              | (((1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r)) 
                  & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__i_op_div)) 
                     & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_last_cycle))) 
                 | (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_need_corrct)) 
                     & (2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r))) 
                    | (4U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_addr_unalgn 
        = ((IData)(((0x40U == (0xc0U & vlSelf->__VdfgTmp_h5f150f9b__0)) 
                    & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_addr)) 
           | (IData)(((0x80U == (0xc0U & vlSelf->__VdfgTmp_h5f150f9b__0)) 
                      & (0U != (3U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_addr)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_o_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__wbck_condi) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_i_valid));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_unalgn 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r))
            ? (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_addr_unalgn)
            : (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__unalgn_flg_dffl__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_longpipe 
        = ((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_unalgn)) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_load) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_store)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_unalgnamo 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_unalgn) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_amo));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_unalgnldst 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_unalgn) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_load) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_store)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu 
        = ((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_addr_unalgn)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_amo));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_longpipe 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_longpipe) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu)) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_nice));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_misalgn 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_unalgnamo) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_unalgnldst));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_lock[1U] 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu) 
           & (0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__amo_1stuop 
        = ((1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__amo_2nduop 
        = ((3U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_lock 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu) 
           & (0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_buserr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_leftover_err_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_misalgn 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_misalgn));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_sbf_0_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_rsp_valid) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__amo_1stuop) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__amo_2nduop)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__leftover_err_nxt 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__amo_1stuop) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu_o_wbck_err)) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__amo_2nduop) 
              & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu_o_wbck_err) 
                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_leftover_err_dfflr__DOT__qout_r))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_read 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_longpipe) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_load)) 
           | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_lock));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_read[1U] 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_longpipe) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_load)) 
           | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_lock));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_need_wbck 
        = ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_longpipe) 
               | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_alu) 
                   & (IData)((0U != (0x1c0000U & vlSelf->__VdfgTmp_h32817b85__0)))) 
                  | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
                      & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_buserr) 
                         | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_misalgn))) 
                     | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__ifu_excp_op))))) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__dec_rdwen));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_buserr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_cmt_buserr));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_usr[1U] 
        = (((QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu)) 
            << 0x26U) | (((QData)((IData)((1U & (vlSelf->__VdfgTmp_h5f150f9b__0 
                                                 >> 8U)))) 
                          << 0x25U) | (((QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_read)) 
                                        << 0x24U) | 
                                       (((QData)((IData)(
                                                         (3U 
                                                          & (vlSelf->__VdfgTmp_h5f150f9b__0 
                                                             >> 6U)))) 
                                         << 0x22U) 
                                        | (((QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_itag)) 
                                            << 0x21U) 
                                           | (((QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_addr)) 
                                               << 1U) 
                                              | (QData)((IData)(
                                                                (1U 
                                                                 & (vlSelf->__VdfgTmp_h5f150f9b__0 
                                                                    >> 9U))))))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT____VdfgTmp_h5959db31__0 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_need_wbck)) 
                 | (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_wbck_o_valid))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_need_flush 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_misalgn) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_buserr) 
              | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_i_ebreak4excp) 
                 | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_ecall) 
                    | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_err_dfflr__DOT__qout_r) 
                       | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__dec_ilegl))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_ebreakm_flush_req_novld 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_ebreak) 
           & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_need_flush)) 
              & ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__dcause_dfflr__DOT__qout_r)) 
                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__ebreakm_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_ready 
        = (((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_bjp) 
                | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_branchslv__DOT____VdfgTmp_h31a1a48a__0))) 
            | ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__flush_req)) 
               & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_branchslv__DOT__brchmis_need_flush)) 
                  | (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__flush_req))))) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_ebreakm_flush_req_novld)
               ? ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty) 
                  & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h968720ef__0))
               : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_need_flush)
                   ? ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty) 
                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_hb91f7aef__0))
                   : (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_hb91f7aef__0))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_ready 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_ready) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT____VdfgTmp_h5959db31__0));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__csr_i_ready 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_csr) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_o_ready 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_ready 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__nice_o_ready 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_nice) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__wbck_csr_wen 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__csr_i_valid) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__csr_i_ready)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__csr_wr_en));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_o_hsked 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_o_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_o_ready));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_habddf295__0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__nice_i_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__nice_o_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcycle_wr_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__csr_wr_en) 
           & (IData)(((0x2c00000U == (0x3ffc000U & vlSelf->__VdfgTmp_h449685cb__0)) 
                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__wbck_csr_wen))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcycleh_wr_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__csr_wr_en) 
           & (IData)(((0x2e00000U == (0x3ffc000U & vlSelf->__VdfgTmp_h449685cb__0)) 
                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__wbck_csr_wen))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__minstret_wr_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__csr_wr_en) 
           & (IData)(((0x2c08000U == (0x3ffc000U & vlSelf->__VdfgTmp_h449685cb__0)) 
                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__wbck_csr_wen))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__minstreth_wr_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__csr_wr_en) 
           & (IData)(((0x2e08000U == (0x3ffc000U & vlSelf->__VdfgTmp_h449685cb__0)) 
                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__wbck_csr_wen))));
    vlSelf->__VdfgTmp_h8154b759__0 = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__csr_wr_en) 
                                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__wbck_csr_wen));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_valid 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_longpipe) 
            & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_habddf295__0)) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu) 
              & (((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                  & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_habddf295__0)) 
                 | (2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func7 
        = (0x7fU & ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_valid))) 
                    & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_hi_ir_dfflr__DOT__qout_r) 
                       >> 9U)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func3 
        = (7U & ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_valid))) 
                 & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_lo_ir_dfflr__DOT__qout_r) 
                    >> 0xcU)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__opcode_custom3 
        = (0x7bU == (0x7fU & ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_valid))) 
                              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_lo_ir_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcycle_nxt 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcycle_wr_ena)
            ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__wbck_csr_dat
            : ((IData)(1U) + vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcycle_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcycleh_nxt 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcycleh_wr_ena)
            ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__wbck_csr_dat
            : ((IData)(1U) + vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcycleh_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__minstret_nxt 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__minstret_wr_ena)
            ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__wbck_csr_dat
            : ((IData)(1U) + vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__minstret_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__minstreth_nxt 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__minstreth_wr_ena)
            ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__wbck_csr_dat
            : ((IData)(1U) + vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__minstreth_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT____VdfgTmp_h8ed9a67d__0 
        = (IData)(((0xc00000U == (0x3ffc000U & vlSelf->__VdfgTmp_h449685cb__0)) 
                   & (IData)(vlSelf->__VdfgTmp_h8154b759__0)));
    __VdfgTmp_h856f476a__0 = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_mem_holdup)) 
                              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_rowsum 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__opcode_custom3) 
           & ((6U == (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func3)) 
              & (6U == (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func7))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_h73f9f76d__0 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__opcode_custom3) 
           & (2U == (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func3)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_sbuf 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_h73f9f76d__0) 
           & (2U == (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func7)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_lbuf 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_h73f9f76d__0) 
           & (1U == (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rv32_func7)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_ha17b9da3__0 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_sbuf));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom_multi_cyc_op 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_lbuf) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_sbuf) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_rowsum)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_wdata[0U] 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_ha17b9da3__0)
            ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_ha3a2aae3__0
            : ((2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r))
                ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_ha3a2aae3__0
                : 0U));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_h50318ff0__0 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom_multi_cyc_op));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_icb_cmd_valid 
        = (((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
            & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_valid) 
               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom_multi_cyc_op))) 
           | (((1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
               & (2U > (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__lbuf_cnt_dfflr__DOT__qout_r))) 
              | (((2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
                  & ((2U >= (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__sbuf_cmd_cnt_dfflr__DOT__qout_r)) 
                     & (2U != (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__sbuf_cnt_dfflr__DOT__qout_r)))) 
                 | ((3U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
                    & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rowsum_acc_flg)) 
                       & (2U > (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rowbuf_cnt_d_dfflr__DOT__qout_r)))))));
    if (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_h50318ff0__0) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_read[0U] 
            = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_lbuf) 
               | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_rowsum));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_addr[0U] 
            = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_rs1;
    } else {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_read[0U] 
            = (2U != (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_addr[0U] 
            = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__maddr_acc_dfflr__DOT__qout_r;
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__rspid_fifo_i_ready) 
           & ((IData)(__VdfgTmp_h856f476a__0) | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_icb_cmd_valid)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel 
        = ((((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_icb_cmd_valid)) 
             & (IData)(__VdfgTmp_h856f476a__0)) << 1U) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_valid_pos 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_ready));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_lock 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_lock
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_lock 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_lock) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_lock
              [1U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_size 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_size
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_size 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_size) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_size
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_excl 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_excl
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_excl 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_excl) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_excl
              [1U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wdata 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_wdata
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wdata 
        = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wdata 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_wdata
              [1U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wmask 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_wmask
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wmask 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wmask) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_wmask
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_usr 
        = ((- (QData)((IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel))))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_usr
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_usr 
        = (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_usr 
           | ((- (QData)((IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                        >> 1U))))) 
              & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_usr
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_read
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_read) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_read
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_addr
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr 
        = (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__i_icb_cmd_addr
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_lock[0U] 
        = soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_lock;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_size[0U] 
        = soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_size;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_excl[0U] 
        = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_excl;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_wdata[0U] 
        = soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wdata;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_wdata[0U] 
        = soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wdata;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_wdata[0U] 
        = (((QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wdata)) 
            << 0x20U) | (QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wdata)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_read[0U] 
        = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_read;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_read[0U] 
        = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_read;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_read[0U] 
        = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_read;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_scond 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_read)) 
                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_usr)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_addr[0U] 
        = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_addr[0U] 
        = (0xffffU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_addr[0U] 
        = (0xffffU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT____VdfgTmp_h42b16a51__0 
        = ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__excl_addr_dffl__DOT__qout_r 
            == vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__excl_flg_dffl__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_biu 
        = ((0x8000U != (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr 
                        >> 0x10U)) & (0x9000U != (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr 
                                                  >> 0x10U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_scond_true 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_scond) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT____VdfgTmp_h42b16a51__0));
    if (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_scond_true)) 
         & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_scond))) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_wmask[0U] = 0U;
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_wmask[0U] = 0U;
        soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu2biu_icb_cmd_wmask = 0U;
    } else {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_wmask[0U] 
            = soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wmask;
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_wmask[0U] 
            = soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wmask;
        soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu2biu_icb_cmd_wmask 
            = soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_wmask;
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_wmask[0U] 
        = ((4U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr)
            ? ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu2biu_icb_cmd_wmask) 
               << 4U) : (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu2biu_icb_cmd_wmask));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__92(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__92\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_nxt 
        = (0x1ffffffffULL & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu)
                              ? ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel1)
                                  ? (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res 
                                     >> 2U) : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__corrct_phase)
                                                ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res
                                                : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_hfdf76643__0)
                                                    ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_remd
                                                    : 
                                                   (((QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res)) 
                                                     << 1U) 
                                                    | (QData)((IData)(
                                                                      (1U 
                                                                       & (IData)(
                                                                                (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h4c5b0848__0 
                                                                                >> 0x20U)))))))))
                              : (QData)((IData)((((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__amo_1stuop))) 
                                                  & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_rsp_rdata) 
                                                 | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__amo_2nduop))) 
                                                    & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r)))))));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__93(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__93\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon)))) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_lsu_clkgate__DOT__enb 
            = (1U & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcgstop_dfflr__DOT__qout_r 
                     | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__excp_active) 
                        | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_valid) 
                            | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_icb_cmd_valid)) 
                           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_e203_lsu_splt_stage__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r)))));
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_core_lsu 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_lsu_clkgate__DOT__enb));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__94(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__94\n"); );
    // Init
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2dtcm_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2dtcm_icb_cmd_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_ready = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__nice_icb_cmd_hsked;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__nice_icb_cmd_hsked = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_ready = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__commit_mret;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__commit_mret = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_ready = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_wbck_o_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_wbck_o_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_last_exit_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_last_exit_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_idle_exit_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_idle_exit_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_1st_exit_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_1st_exit_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_wait2nd_exit_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_wait2nd_exit_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_2nd_exit_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_2nd_exit_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h5001ee9d__0;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h5001ee9d__0 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_0th_exit_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_0th_exit_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_exec_exit_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_exec_exit_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_chck_exit_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_chck_exit_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_corr_exit_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_corr_exit_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__cmt_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__cmt_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_req;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_req = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__irq_flush_req;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__irq_flush_req = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__excp_taken_ena;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__excp_taken_ena = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_ebreakm_flush_req;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_ebreakm_flush_req = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ld;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ld = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_stamo;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_stamo = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ecall;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ecall = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h1c70f3da__0;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h1c70f3da__0 = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_ready = 0;
    CData/*1:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_bus_icb_cmd_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_bus_icb_cmd_ready = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__all_icb_cmd_ready_excp_itcm;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__all_icb_cmd_ready_excp_itcm = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__o_icb_cmd_ready_real;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__o_icb_cmd_ready_real = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__lsu_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__lsu_icb_cmd_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_icb_cmd_valid = 0;
    CData/*1:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_bus_icb_cmd_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_bus_icb_cmd_ready = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_read;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_read = 0;
    SData/*15:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_addr;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_addr = 0;
    IData/*31:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wdata;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wdata = 0;
    CData/*3:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wmask;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wmask = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid = 0;
    // Body
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2dtcm_icb_cmd_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_valid_pos) 
           & ((0x9000U == (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr 
                           >> 0x10U)) & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_ready) 
                                         & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2itcm_icb_cmd_ready))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_bus_icb_cmd_sel 
        = soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2dtcm_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_icb_cmd_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__rspid_fifo_i_ready) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2dtcm_icb_cmd_valid));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_bus_icb_cmd_ready 
        = ((((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2dtcm_icb_cmd_valid)) 
             & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__o_icb_cmd_ready_real)) 
            << 1U) | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__o_icb_cmd_ready_real));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_read
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_read 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_read) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_read
              [1U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_addr 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_addr
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_addr 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_addr) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_addr
              [1U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wdata 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_wdata
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wdata 
        = (soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wdata 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_wdata
              [1U]));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wmask 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_wmask
           [0U]);
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wmask 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wmask) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__i_icb_cmd_wmask
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__arbt_num_gt_1_gen__DOT__dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_set 
        = (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
            & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_icb_cmd_valid)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__rspid_fifo_i_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
           & ((~ ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_icb_cmd_valid) 
                  & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                     & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_o_rdy)))) 
              & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_icb_cmd_valid)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu2biu_icb_cmd_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_valid_pos) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_biu) 
              & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_bus_icb_cmd_ready) 
                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2itcm_icb_cmd_ready))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__all_icb_cmd_ready_excp_itcm 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_ready) 
                 & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_bus_icb_cmd_ready)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_i_dat 
        = (((QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_read)) 
            << 0x35U) | (((QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_addr)) 
                          << 0x25U) | (((QData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wdata)) 
                                        << 5U) | (QData)((IData)(
                                                                 (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_wmask) 
                                                                   << 1U) 
                                                                  | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_dtcm_icb_arbt__DOT__sel_o_icb_cmd_read)))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (3U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                           << 1U)) : VL_SHIFTR_III(2,2,32, 
                                                   (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                     << 1U) 
                                                    | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_e1_stage__DOT__dp_gt_0__DOT__vld_set 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_o_rdy));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__dtcm_ram_cs 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_o_rdy) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__dtcm_active 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2dtcm_icb_cmd_valid) 
           | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__arbt_icb_cmd_valid) 
              | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid) 
                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_e1_stage__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2itcm_icb_cmd_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_valid_pos) 
           & ((0x8000U == (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_addr 
                           >> 0x10U)) & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__all_icb_cmd_ready_excp_itcm)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_ready 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_ready) 
           & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__all_icb_cmd_ready_excp_itcm) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2itcm_icb_cmd_ready)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)
            ? ((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
               & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__fifo_rf_r
               [0U]) : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_i_dat);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_lsu2itcm_n2w__DOT__fifo_dp_1__DOT__u_sirv_gnrl_n2w_fifo__DOT__dp_gt_0__DOT__vld_set 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2itcm_icb_cmd_ready) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2itcm_icb_cmd_valid)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_lsu2itcm_n2w__DOT__n2w_fifo_i_ready));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__lsu_icb_cmd_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2itcm_icb_cmd_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_lsu2itcm_n2w__DOT__n2w_fifo_i_ready));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_valid) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_ready));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__o_icb_cmd_ready_real 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_icb_cmd_ready) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__rspid_fifo_i_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_srams__DOT__u_e203_dtcm_ram__DOT__u_e203_dtcm_gnrl_ram__DOT__u_sirv_sim_ram__DOT__wen 
        = (0xfU & ((- (IData)(((~ (IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack 
                                           >> 0x35U))) 
                               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__dtcm_ram_cs)))) 
                   & (IData)((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack 
                              >> 1U))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_bus_icb_cmd_sel 
        = soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__lsu_icb_cmd_valid;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__rspid_fifo_i_ready) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__lsu_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__arbt_num_gt_1_gen__DOT__dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_set 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__rspid_fifo_i_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_e203_lsu_splt_stage__DOT__dp_gt_0__DOT__vld_set 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__excl_addr_ena 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_valid) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_usr) 
              & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_excl) 
                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_read))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_bus_icb_cmd_ready 
        = ((((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_icb_cmd_valid)) 
             & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__o_icb_cmd_ready_real)) 
            << 1U) | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__o_icb_cmd_ready_real));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_addr 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_addr
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_addr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_addr) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_addr
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wdata 
        = ((- (QData)((IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_bus_icb_cmd_sel))))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_wdata
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wdata 
        = (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wdata 
           | ((- (QData)((IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                        >> 1U))))) 
              & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_wdata
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wmask 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_wmask
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wmask 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wmask) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_wmask
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_read
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_read) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_bus_icb_cmd_sel) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__i_icb_cmd_read
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__arbt_num_gt_1_gen__DOT__dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_set 
        = (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__rspid_fifo_i_ready));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__nice_icb_cmd_hsked 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_icb_cmd_valid) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_bus_icb_cmd_ready));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_ready 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
           & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom_multi_cyc_op)) 
              | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_bus_icb_cmd_ready)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_ready 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_mem_holdup)) 
           & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__arbt_bus_icb_cmd_ready) 
              >> 1U));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__sbuf_cmd_cnt_incr 
        = ((2U != (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__sbuf_cmd_cnt_dfflr__DOT__qout_r)) 
           & (((2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
               | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_ha17b9da3__0)) 
              & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__nice_icb_cmd_hsked)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__maddr_acc_ena 
        = (((((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_lbuf)) 
             | (1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r))) 
            | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT____VdfgTmp_ha17b9da3__0) 
                | (2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r))) 
               | (((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
                   & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom3_rowsum)) 
                  | (3U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r))))) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__nice_icb_cmd_hsked));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__nice_req_hsked 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_valid) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_ready));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_valid 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_alu) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_valid)) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu) 
               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_valid)) 
              | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_csr) 
                  & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__csr_i_valid)) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
                     & ((6U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                        | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_valid) 
                           & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_i_longpipe) 
                               | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_unalgnldst) 
                                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_unalgnamo))) 
                              & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_ready))))) 
                    | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__ifu_excp_op) 
                        & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_valid)) 
                       | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu) 
                           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_o_valid)) 
                          | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_nice) 
                             & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__nice_i_valid) 
                                & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_ready)))))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__sbuf_cmd_cnt_nxt 
        = (3U & ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__sbuf_cmd_cnt_incr))) 
                 & ((IData)(1U) + (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__sbuf_cmd_cnt_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__maddr_acc_next 
        = ((IData)(4U) + (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__maddr_acc_ena) 
                           & (0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)))
                           ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_rs1
                           : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__maddr_acc_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_idle_exit_ena 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__custom_multi_cyc_op) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__nice_req_hsked)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 3U)) & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__nice_req_hsked));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_wbck_o_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_need_wbck) 
           & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_valid) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_ready)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_valid 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT____VdfgTmp_h5959db31__0));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_idle_exit_ena) 
           | (((1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
               & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__lbuf_wr) 
                  & (2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__lbuf_cnt_dfflr__DOT__qout_r)))) 
              | (((2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
                  & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__sbuf_cnt_clr)) 
                 | ((3U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)) 
                    & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__fifo_o_rdy)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (0x1fU & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__wen)
                     ? (1U | ((0x1cU & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                        << 2U)) | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                                   << 1U)))
                     : VL_SHIFTR_III(5,5,32, (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                               << 1U) 
                                              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_nice__DOT__u_nice_itag_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_wbck__DOT__wbck_sel_alu 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_wbck_o_valid)) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_wbck_o_valid));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__cmt_ena 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__alu_brchmis_flush_req 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__flush_req)) 
           & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_valid) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_branchslv__DOT__brchmis_need_flush)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_ebreakm_flush_req 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_ebreakm_flush_req_novld));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__rf_wbck_rdidx 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_wbck__DOT__wbck_sel_alu)
            ? (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__dec2ifu_rdidx)
            : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__rdidx_r
           [vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_dfflrs__DOT__qout_r]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__rf_wbck_ena 
        = ((~ ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_wbck__DOT__wbck_sel_alu)) 
               & ((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__oitf_entries__BRA__1__KET____DOT__rdfpu_dfflrs__DOT__qout_r) 
                    << 1U) | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__oitf_entries__BRA__0__KET____DOT__rdfpu_dfflrs__DOT__qout_r)) 
                  >> (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__ret_ptr_dfflrs__DOT__qout_r)))) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_wbck__DOT__wbck_sel_alu)
               ? (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_wbck_o_valid)
               : (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_wbck_o_valid)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__wfi_halt_req_set 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__dcause_dfflr__DOT__qout_r)) 
           & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_alu) 
               & (vlSelf->__VdfgTmp_h32817b85__0 >> 0x14U)) 
              & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__cmt_ena)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__cmt_instret_ena 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__alu_brchmis_flush_req)) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__cmt_ena));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__commit_mret 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_mret) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__alu_brchmis_flush_req));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_ebrk_req 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_ebreakm_flush_req) 
           & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__step_req_dfflr__DOT__qout_r)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_irq_req 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_irq_sync__DOT__master_gen__DOT__u_dbg_irq_sync__DOT__sync_gen__BRA__1__KET____DOT__i_is_not_0__DOT__sync_dffr__DOT__qout_r) 
           & ((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_ebreakm_flush_req)) 
              & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__step_req_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_halt_req 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h66d90a81__0) 
           & ((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_ebreakm_flush_req)) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h57fc5267__0)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_req 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__dcause_dfflr__DOT__qout_r)) 
           & (((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_irq_req)) 
              | (((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                  & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_halt_req)) 
                 | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__step_req_dfflr__DOT__qout_r) 
                    | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_ebrk_req)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__wfi_halt_req_clr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__wfi_irq_req) 
           | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_req));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_flush_req 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_req) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h968720ef__0)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h1c70f3da__0 
        = (1U & ((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_req)) 
                 & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_valid))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__wfi_halt_ifu_req 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__wfi_halt_req_clr)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__wfi_halt_req_dfflr__DOT__qout_r));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__irq_flush_req 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__irq_req) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty) 
              & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_pc_vld_dfflr__DOT__qout_r) 
                 & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h1c70f3da__0))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_valid) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_need_flush) 
              & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty) 
                 & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__irq_req)) 
                    & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_h1c70f3da__0)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__halt_ack_clr 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__wfi_halt_ifu_req)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__halt_ack_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__halt_ack_set 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__wfi_halt_ifu_req) 
           & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__halt_ack_dfflr__DOT__qout_r)) 
              & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__out_flag_dfflr__DOT__qout_r)) 
                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_valid))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__wfi_flag_set 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__wfi_halt_ifu_req) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__halt_ack_dfflr__DOT__qout_r) 
              & (((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                  & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty)) 
                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__wfi_halt_req_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ebreak 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_i_ebreak4excp));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ifu_buserr 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_err_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ifu_ilegl 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__dec_ilegl));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ecall 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_ecall));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ld 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
              & ((~ (vlSelf->__VdfgTmp_h5f150f9b__0 
                     >> 9U)) & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_load))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_stamo 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu) 
              & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_store) 
                 | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_amo) 
                    | (vlSelf->__VdfgTmp_h5f150f9b__0 
                       >> 9U)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__all_excp_flush_req 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_valid) 
           | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__excpirq_flush_req 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__longp_excp_o_valid) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_flush_req) 
              | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__irq_flush_req) 
                 | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__excp_flush_req_ld_misalgn 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ld) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_misalgn));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ld_buserr 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ld) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_buserr));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_stamo_misalgn 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_stamo) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_misalgn));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_stamo_buserr 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_stamo) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_buserr));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__excl_flg_clr 
        = (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__splt_fifo_i_valid) 
            & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT__u_lsu_icb_arbt__DOT__sel_o_icb_cmd_read)) 
               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_lsu__DOT__u_e203_lsu_ctrl__DOT____VdfgTmp_h42b16a51__0))) 
           | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__commit_mret) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__excpirq_flush_req)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__cmt_dpc_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_flush_req) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__excpirq_flush_req));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__excp_taken_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__all_excp_flush_req) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__excpirq_flush_req));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__alu_brchmis_flush_req) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__excpirq_flush_req));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__step_req_set 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__dcause_dfflr__DOT__qout_r)) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__step_dfflr__DOT__qout_r) 
              & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__cmt_dpc_ena)) 
                 & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__cmt_ena))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__cmt_cause 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__excp_taken_ena)
            ? ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ifu_buserr)
                ? 1U : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ifu_ilegl)
                         ? 2U : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ebreak)
                                  ? 3U : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__excp_flush_req_ld_misalgn)
                                           ? 4U : (
                                                   ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__longp_excp_flush_req_ld_buserr) 
                                                    | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ld_buserr))
                                                    ? 5U
                                                    : 
                                                   ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_stamo_misalgn)
                                                     ? 6U
                                                     : 
                                                    (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__longp_excp_flush_req_st_buserr) 
                                                      | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_stamo_buserr))
                                                      ? 7U
                                                      : 
                                                     ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__alu_excp_flush_req_ecall)
                                                       ? 0xbU
                                                       : 0x1fU))))))))
            : (0x80000000U | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_hdd740f62__0)
                               ? 3U : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_hd8dcbf69__0)
                                        ? 7U : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT____VdfgTmp_hd3b1f38e__0)
                                                 ? 0xbU
                                                 : 0U)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__cmt_epc_ena 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__dcause_dfflr__DOT__qout_r)) 
           & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__excp_taken_ena) 
              | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__irq_flush_req) 
                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__excpirq_flush_req))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__flushed_clr 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_o_hsked));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_wait2nd_exit_ena 
        = ((2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
           & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_ready) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_idle_exit_ena 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu) 
              & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty) 
                 & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)) 
                    & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_valid) 
                       & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_ready))))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_corr_exit_ena 
        = ((4U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r)) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_o_hsked)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h5001ee9d__0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_rsp_valid) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_0th_exit_ena 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r)) 
           & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)) 
              & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_i_valid) 
                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h99fe1673__0))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_chck_exit_ena 
        = ((2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r)) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_need_corrct) 
              | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_o_hsked) 
                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req))));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_exec_exit_ena 
        = ((1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r)) 
           & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_last_cycle) 
               & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__i_op_div) 
                  | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_o_hsked))) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_last_exit_ena 
        = ((6U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_ready) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pipe_flush_req_real 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__dly_flush_dfflr__DOT__qout_r) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__cmt_badaddr_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__cmt_epc_ena) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__excpirq_flush_req));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__status_mpie_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT____VdfgTmp_h8ed9a67d__0) 
           | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__commit_mret) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__cmt_epc_ena)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__status_mpie_nxt 
        = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__cmt_epc_ena)
                  ? (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__status_mie_dfflr__DOT__qout_r)
                  : ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__commit_mret) 
                     | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT____VdfgTmp_h8ed9a67d__0)
                         ? (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__wbck_csr_dat 
                            >> 7U) : (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__status_mpie_dfflr__DOT__qout_r)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__status_mie_nxt 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__cmt_epc_ena)) 
                 & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__commit_mret)
                     ? (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__status_mpie_dfflr__DOT__qout_r)
                     : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT____VdfgTmp_h8ed9a67d__0)
                         ? (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__wbck_csr_dat 
                            >> 3U) : (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__status_mie_dfflr__DOT__qout_r)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__unalgn_flg_set 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__agu_i_addr_unalgn) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_idle_exit_ena));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_1st_exit_ena 
        = ((1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h5001ee9d__0));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_2nd_exit_ena 
        = ((3U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT____VdfgTmp_h5001ee9d__0));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_ena 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_0th_exit_ena) 
           | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_exec_exit_ena) 
              | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_chck_exit_ena) 
                 | ((3U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r)) 
                    | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_corr_exit_ena)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_nxt 
        = ((1U & (- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_0th_exit_ena)))) 
           | (((- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_exec_exit_ena))) 
               & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)
                   ? 0U : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__i_op_div)
                            ? 2U : 0U))) | (((- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_chck_exit_ena))) 
                                             & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)
                                                 ? 0U
                                                 : 
                                                ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_need_corrct)
                                                  ? 3U
                                                  : 0U))) 
                                            | ((- (IData)(
                                                          (3U 
                                                           == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_dfflr__DOT__qout_r)))) 
                                               & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)
                                                   ? 0U
                                                   : 4U)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__unalgn_flg_clr 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_last_exit_ena) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__unalgn_flg_dffl__DOT__qout_r));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_ready 
        = ((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu)
              ? (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_last_exit_ena)
              : ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_ready) 
                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_o_ready))) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu)) 
           | ((((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__wbck_condi) 
                & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_o_ready)) 
               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu)) 
              | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_alu) 
                  & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_ready)) 
                 | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__ifu_excp_op) 
                     & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_ready)) 
                    | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu) 
                        & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_ready)) 
                       | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__csr_i_ready) 
                           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_csr)) 
                          | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__nice_req_ready) 
                              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__nice_o_ready)) 
                             & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_nice))))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_ena 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_idle_exit_ena) 
           | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_1st_exit_ena) 
              | ((4U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                 | ((5U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)) 
                    | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_wait2nd_exit_ena) 
                       | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_2nd_exit_ena) 
                          | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_last_exit_ena)))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_nxt 
        = ((1U & (- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_idle_exit_ena)))) 
           | (((- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_1st_exit_ena))) 
               & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)
                   ? 0U : 4U)) | (((- (IData)((4U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)))) 
                                   & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)
                                       ? 0U : 5U)) 
                                  | (((- (IData)((5U 
                                                  == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__icb_state_dfflr__DOT__qout_r)))) 
                                      & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)
                                          ? 0U : 2U)) 
                                     | (((- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_wait2nd_exit_ena))) 
                                         & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)
                                             ? 0U : 3U)) 
                                        | ((- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_lsuagu__DOT__state_2nd_exit_ena))) 
                                           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)
                                               ? 0U
                                               : 6U)))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_cnt_set 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_ena) 
           & (1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__muldiv_state_nxt)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_oitf_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_valid) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_longpipe) 
              & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_ready)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu_o_ready 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_disp__DOT__disp_condition) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_alu_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_cnt_nxt 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_cnt_set)
            ? 1U : (0x3fU & ((IData)(1U) + (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_cnt_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__part_prdt_hi_ena 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_cnt_set) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel1)) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_cnt_inc) 
               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel1)) 
              | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_exec_exit_ena)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h157d6ed9__0 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_cnt_set) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__i_op_div)) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__exec_cnt_inc) 
               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__i_op_div)) 
              | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_exec_exit_ena)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT____Vcellinp__oitf_entries__BRA__0__KET____DOT__pc_dfflrs____pinNumber1 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_oitf_ena) 
           & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__alc_ptr_dfflrs__DOT__qout_r)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT____Vcellinp__oitf_entries__BRA__1__KET____DOT__pc_dfflrs____pinNumber1 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_oitf_ena) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__alc_ptr_dfflrs__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__alc_ptr_flg_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__alc_ptr_dfflrs__DOT__qout_r) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__disp_oitf_ena));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_clr 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu_o_ready) 
            | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__part_remd_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h157d6ed9__0) 
           | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__state_remd_corr_exit_ena));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__alc_ptr_nxt 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__alc_ptr_flg_ena)) 
                 & ((IData)(1U) + (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_oitf__DOT__depth_gt1__DOT__alc_ptr_dfflrs__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_ir_i_ready 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_dfflr__DOT__qout_r)) 
                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_clr)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_pc_vld_set 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pc_newpend_dfflr__DOT__qout_r) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_ir_i_ready) 
              & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pipe_flush_req_real))));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__95(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__95\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon)))) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_dtcm_clkgate__DOT__enb 
            = (1U & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcgstop_dfflr__DOT__qout_r 
                     | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__dtcm_active) 
                        | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__dtcm_active_dffr__DOT__qout_r))));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_ifu_clkgate__DOT__enb 
            = (1U & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcgstop_dfflr__DOT__qout_r 
                     | (~ ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__wfi_halt_req_clr)) 
                           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__wfi_flag_dfflr__DOT__qout_r)))));
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_dtcm 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_dtcm_clkgate__DOT__enb));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_core_ifu 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_ifu_clkgate__DOT__enb));
    if ((1U & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_dtcm)))) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_ram_clkgate__DOT__enb 
            = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__dtcm_ram_cs) 
                     | (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcgstop_dfflr__DOT__qout_r 
                        >> 1U)));
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__clk_dtcm_ram 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_dtcm) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_dtcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_ram_clkgate__DOT__enb));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__96(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__96\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__rf_wbck_wdat 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_wbck__DOT__wbck_sel_alu)
            ? (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_alu))) 
                & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_addr) 
               | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__bjp_req_alu))) 
                   & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_addr) 
                  | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__o_sel_csr))) 
                      & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__read_csr_dat) 
                     | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__agu_req_alu))) 
                         & ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__agu_icb_cmd_back2agu))) 
                            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r))) 
                        | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu))) 
                           & (((- (IData)(((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__special_cases)) 
                                           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__i_b2b)))) 
                               & (((- (IData)((1U & 
                                               (vlSelf->__VdfgTmp_h670721a2__0 
                                                >> 4U)))) 
                                   & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_1_dffl__DOT__qout_r) 
                                       << 1U) | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__part_prdt_sft1_dfflr__DOT__qout_r))) 
                                  | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h0d3a4e8c__0))) 
                                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_0_dffl__DOT__qout_r)) 
                                     | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h4b3b81d2__0))) 
                                        & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_1_dffl__DOT__qout_r))))) 
                              | (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__special_cases))) 
                                  & ((0U != vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_i_rs2)
                                      ? ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h4b3b81d2__0)
                                          ? 0x80000000U
                                          : 0U) : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h4b3b81d2__0)
                                                    ? 0xffffffffU
                                                    : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__mdv_i_rs1))) 
                                 | (((- (IData)(((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h99fe1673__0) 
                                                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__i_op_div)))) 
                                     & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h4b3b81d2__0)
                                         ? (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_quot)
                                         : (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__div_remd))) 
                                    | ((- (IData)(((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT____VdfgTmp_h99fe1673__0) 
                                                   & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_muldiv__DOT__req_alu_sel1)))) 
                                       & ((0x10U & vlSelf->__VdfgTmp_h670721a2__0)
                                           ? (IData)(
                                                     (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__u_e203_exu_alu_dpath__DOT__sbf_1_dffl__DOT__qout_r 
                                                      >> 1U))
                                           : (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_alu__DOT__muldiv_req_alu_res)))))))))))
            : (((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_sel_lsu))) 
                & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu_o_wbck_wdat) 
               | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_longpwbck__DOT__wbck_sel_nice))) 
                  & ((- (IData)((3U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__state_dfflr__DOT__qout_r)))) 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_nice_core__DOT__rowsum_acc_dfflr__DOT__qout_r))));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__97(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__97\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_pc 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req)
            ? (0xfffffffeU & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__excpirq_flush_req)
                               ? ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__dbg_entry_flush_req)
                                   ? 0x800U : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_commit__DOT__u_e203_exu_excp__DOT__all_excp_flush_req) 
                                                & (0U 
                                                   != (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__dcause_dfflr__DOT__qout_r)))
                                                ? 0x808U
                                                : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mtvec_dfflr__DOT__qout_r))
                               : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_fencei) 
                                   | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_bjp) 
                                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_bjp_prdt)))
                                   ? (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_pc_dfflr__DOT__qout_r 
                                      + ((8U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__dec_info)
                                          ? 4U : 2U))
                                   : (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_bjp_prdt)) 
                                       & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_bjp))
                                       ? (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__dec_imm 
                                          + vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_pc_dfflr__DOT__qout_r)
                                       : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__alu_cmt_dret)
                                           ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_debug_module__DOT__u_sirv_debug_csr__DOT__dpc_dfflr__DOT__qout_r
                                           : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__epc_dfflr__DOT__qout_r)))))
            : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__dly_flush_dfflr__DOT__qout_r)
                ? (0xfffffffeU & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pc_dfflr__DOT__qout_r)
                : (0xfffffffeU & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bjp_req)
                                    ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_bxx) 
                                        | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_jal))
                                        ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pc_dfflr__DOT__qout_r
                                        : (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_jalr) 
                                            & (0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_jalr_rs1idx)))
                                            ? 0U : 
                                           (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_jalr) 
                                             & (1U 
                                                == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_jalr_rs1idx)))
                                             ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_regfile__DOT__regfile__BRA__1__KET____DOT__rfno0__DOT__rf_dffl__DOT__qout_r
                                             : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__rf2ifu_rs1)))
                                    : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__reset_req_dfflr__DOT__qout_r)
                                        ? (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_aon_top__DOT__u_sirv_aon_wrapper__DOT__bootrom_deglitch__DOT__last) 
                                            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_sirv_aon_top__DOT__u_sirv_aon_wrapper__DOT__bootrom_deglitch__DOT__sync))
                                            ? 0x1000U
                                            : 0x20000000U)
                                        : vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pc_dfflr__DOT__qout_r)) 
                                  + ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bjp_req)
                                      ? vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_bjp_imm
                                      : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__reset_req_dfflr__DOT__qout_r)
                                          ? 0U : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_seq_rv32)
                                                   ? 4U
                                                   : 2U)))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_lane_holdup 
        = ((0x8000U == (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_pc 
                        >> 0x10U)) & ((~ vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__itcmnohold_dfflr__DOT__qout_r) 
                                      & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__ifu_holdup_dffl__DOT__qout_r)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_lane_cross 
        = ((IData)((0x80000006U == (0xffff0006U & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_pc))) 
           | ((0x8000U != (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_pc 
                           >> 0x10U)) & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_pc 
                                         >> 1U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_lane_same 
        = (1U & (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pipe_flush_req_real)) 
                  & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__reset_req_dfflr__DOT__qout_r)) 
                     & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bjp_req)))) 
                 & ((~ ((IData)((0x80000000U == (0xffff0006U 
                                                 & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_pc))) 
                        | ((0x8000U != (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_pc 
                                        >> 0x10U)) 
                           & (~ (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_pc 
                                 >> 1U))))) | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__req_lane_cross_dfflr__DOT__qout_r))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__req_need_0uop 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_lane_same) 
           & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_lane_cross)) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_lane_holdup)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT____VdfgTmp_hea928bc5__0 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_lane_same) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_lane_cross));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__req_same_cross_holdup 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT____VdfgTmp_hea928bc5__0) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_lane_holdup));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_addr 
        = (((- (IData)(((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__req_same_cross_holdup) 
                        | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__icb_addr_sel_2ndnxtalgn)))) 
            & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pc_dfflr__DOT__qout_r 
               + ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__icb_addr_sel_2ndnxtalgn)
                   ? 2U : ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_seq_rv32)
                            ? 6U : 4U)))) | ((- (IData)(
                                                        (1U 
                                                         & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__req_same_cross_holdup)) 
                                                            & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__icb_addr_sel_2ndnxtalgn)))))) 
                                             & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_pc));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_addr[1U] 
        = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_addr;
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_ready 
        = (((0x8000U == (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_addr 
                         >> 0x10U)) & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid)) 
                                       & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)))) 
           | ((0x8000U != (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_addr 
                           >> 0x10U)) & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_ready) 
                                         >> 1U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__state_wait2nd_exit_ena 
        = ((2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__icb_state_dfflr__DOT__qout_r)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_ready 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_ready) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_ready_condi));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__98(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__98\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bpu2rf_rs1_ena 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__rs1xn_rdrf_dfflrs__DOT__qout_r)) 
           & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_valid) 
              & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_jalr) 
                 & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__dec_jalr_rs1xn) 
                    & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__jalr_rs1xn_dep)) 
                       | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__jalr_rs1xn_dep) 
                          & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty) 
                             & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_dfflr__DOT__qout_r) 
                                & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__dec_rs1en)) 
                                   | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_clr))))))))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__rs1xn_rdrf_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bpu2rf_rs1_ena) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__rs1xn_rdrf_dfflrs__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__rs1xn_rdrf_nxt 
        = (1U & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__rs1xn_rdrf_dfflrs__DOT__qout_r)) 
                 | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bpu2rf_rs1_ena)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bpu_wait 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT____VdfgTmp_he0f10288__0) 
            & ((1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_jalr_rs1idx)) 
               & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__oitf_empty)) 
                  | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__dec_rdwen) 
                     & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__dec2ifu_rdidx) 
                         == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__minidec_jalr_rs1idx)) 
                        & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_dfflr__DOT__qout_r)))))) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__u_e203_ifu_litebpu__DOT__jalr_rs1xn_dep) 
              | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bpu2rf_rs1_ena)));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__99(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__99\n"); );
    // Init
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__ifu2itcm_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__ifu2itcm_icb_cmd_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_ready;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_ready = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_valid = 0;
    CData/*1:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_valid = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_read;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_read = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_ifu;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_ifu = 0;
    CData/*0:0*/ soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid;
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid = 0;
    // Body
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_ready 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pipe_flush_req_real) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ifu_ir_i_ready) 
              & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bpu_wait)) 
                 & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_ready))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_ready) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
           & ((~ ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__i_ifu_rsp_valid) 
                  & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                     & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_ready)))) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__i_ifu_rsp_valid)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__out_flag_clr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_valid) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_rsp_ready));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (3U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                           << 1U)) : VL_SHIFTR_III(2,2,32, 
                                                   (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                     << 1U) 
                                                    | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__u_e203_ifetch_rsp_bypbuf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__ir_valid_set 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__out_flag_clr) 
           & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pipe_flush_req_real)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_valid 
        = (1U & ((((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__bpu_wait)) 
                   & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__wfi_halt_ifu_req)) 
                      & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__reset_flag_dffrs__DOT__qout_r)))) 
                  | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__reset_req_dfflr__DOT__qout_r) 
                     | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pipe_flush_req_real))) 
                 & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__out_flag_dfflr__DOT__qout_r)) 
                    | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__out_flag_clr))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_hsked 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_ready) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_valid));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_valid 
        = (((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__req_need_0uop)) 
            & ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__ifu_req_valid) 
               & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_ready_condi))) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__req_need_2uop_dfflr__DOT__qout_r) 
              & (((1U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__icb_state_dfflr__DOT__qout_r)) 
                  & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_rsp_hsked)) 
                 | (2U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__icb_state_dfflr__DOT__qout_r)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__reset_req_clr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__reset_req_dfflr__DOT__qout_r) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_hsked));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__dly_flush_set 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_hsked)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__dly_flush_clr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__dly_flush_dfflr__DOT__qout_r) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_hsked));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ifetch__DOT__pc_ena 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_hsked) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__pipe_flush_req));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__state_idle_exit_ena 
        = ((0U == (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__icb_state_dfflr__DOT__qout_r)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_hsked));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__leftover_ena 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_req_hsked) 
            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__req_same_cross_holdup)) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_rsp_hsked) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__uop1st2leftover_sel)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_hsked 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_ready) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_valid 
        = ((0x8000U != (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_addr 
                        >> 0x10U)) & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_valid));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__ifu2itcm_icb_cmd_valid 
        = ((0x8000U == (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_addr 
                        >> 0x10U)) & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_ifu__DOT__u_e203_ifu_ift2icb__DOT__ifu_icb_cmd_valid));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_valid 
        = (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_valid) 
            << 1U) | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu2biu_icb_cmd_valid));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_ifu 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid)) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__ifu2itcm_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_ready 
        = ((((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_valid)) 
             & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__o_icb_cmd_ready_real)) 
            << 1U) | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__o_icb_cmd_ready_real));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_icb_cmd_valid 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__arbt_num_gt_1_gen__DOT__dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r)) 
           & (0U != (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_valid)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel 
        = (((IData)((2U == (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_valid))) 
            << 1U) | (1U & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_bus_icb_cmd_valid)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_read 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_ifu) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid) 
              & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_read)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_valid 
        = (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_ifu) 
            & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__ifu2itcm_icb_cmd_valid)) 
           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_read
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_read 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_read) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_read
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_burst 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_burst
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_burst 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_burst) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_burst
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_addr 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_addr
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_addr 
        = (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_addr 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_addr
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_wdata 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_wdata
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_wdata 
        = (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_wdata 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_wdata
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_wmask 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_wmask
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_wmask 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_wmask) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_wmask
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_beat 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_beat
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_beat 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_beat) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_beat
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_lock 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_lock
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_lock 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_lock) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_lock
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_excl 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_excl
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_excl 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_excl) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_excl
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_size 
        = ((- (IData)((1U & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel)))) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_size
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_size 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_size) 
           | ((- (IData)((1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
                                >> 1U)))) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_size
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_usr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
           & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_usr
           [0U]);
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_usr 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__sel_o_icb_cmd_usr) 
           | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_bus_icb_cmd_sel) 
               >> 1U) & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__i_icb_cmd_usr
              [1U]));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_i_dat[0U] 
        = (((IData)(((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid))) 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wdata)) 
            << 0xaU) | ((((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid))) 
                          & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wmask)) 
                         << 2U) | (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_ifu) 
                                    << 1U) | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_read))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_i_dat[1U] 
        = (((IData)(((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid))) 
                     & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wdata)) 
            >> 0x16U) | ((IData)((((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid))) 
                                   & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wdata) 
                                  >> 0x20U)) << 0xaU));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_i_dat[2U] 
        = (((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_read) 
            << 0x1aU) | ((0x3fffc00U & ((((- (IData)((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_ifu))) 
                                          & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_addr) 
                                         | ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid))) 
                                            & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_addr))) 
                                        << 0xaU)) | 
                         ((IData)((((- (QData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__arbt_icb_cmd_valid))) 
                                    & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_itcm_icb_arbt__DOT__sel_o_icb_cmd_wdata) 
                                   >> 0x20U)) >> 0x16U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
           & ((~ ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_valid) 
                  & ((~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                     & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_o_rdy)))) 
              & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_valid)));
    soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           | (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_valid));
    if (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__wen) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__arbt_num_gt_1_gen__DOT__dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_set 
            = (1U & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__arbt_num_gt_1_gen__DOT__dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r)));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__outs_cnt_nxt 
            = (1U & ((IData)(1U) + (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__outs_cnt_dfflr__DOT__qout_r)));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_nxt 
            = (3U & (1U | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                           << 1U)));
    } else {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_biu_icb_arbt__DOT__arbt_num_gt_1_gen__DOT__dp_1__DOT__u_sirv_gnrl_rspid_fifo__DOT__dp_gt_0__DOT__vld_set = 0U;
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__outs_cnt_nxt 
            = (1U & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__outs_cnt_dfflr__DOT__qout_r)));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_nxt 
            = (3U & VL_SHIFTR_III(2,2,32, (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U));
    }
    if (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack[0U] 
            = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
               & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__fifo_rf_r
               [0U][0U]);
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack[1U] 
            = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
               & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__fifo_rf_r
               [0U][1U]);
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack[2U] 
            = ((- (IData)((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r))) 
               & vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__fifo_rf_r
               [0U][2U]);
    } else {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack[0U] 
            = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_i_dat[0U];
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack[1U] 
            = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_i_dat[1U];
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack[2U] 
            = vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_i_dat[2U];
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__wen));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (3U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                           << 1U)) : VL_SHIFTR_III(2,2,32, 
                                                   (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                                     << 1U) 
                                                    | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__u_bypbuf_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_e1_stage__DOT__dp_gt_0__DOT__vld_set 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_o_rdy));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__itcm_ram_cs 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_byp_icb_cmd_buf__DOT__fifo_o_rdy) 
           & (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__itcm_active 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__ifu2itcm_icb_cmd_valid) 
           | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__lsu2itcm_icb_cmd_valid) 
              | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_valid) 
                 | ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_valid) 
                    | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_e1_stage__DOT__dp_gt_0__DOT__vld_dfflr__DOT__qout_r)))));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__ifu_holdup_set 
        = ((IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_ifu) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__itcm_ram_cs));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__ifu_holdup_clr 
        = ((~ (IData)(soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__sram_icb_cmd_ifu)) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__itcm_ram_cs));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_srams__DOT__u_e203_itcm_ram__DOT__u_e203_itcm_gnrl_ram__DOT__u_sirv_sim_ram__DOT__wen 
        = (0xffU & ((- (IData)(((~ (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack[2U] 
                                    >> 0x1aU)) & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__itcm_ram_cs)))) 
                    & ((vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack[0U] 
                        << 0x1eU) | (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__byp_icb_cmd_o_pack[0U] 
                                     >> 2U))));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__100(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__100\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon)))) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_biu_clkgate__DOT__enb 
            = (1U & (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__ifu2biu_icb_cmd_valid) 
                      | (((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__arbt_icb_cmd_valid) 
                          | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__outs_cnt_dfflr__DOT__qout_r)) 
                         | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__lsu2biu_icb_cmd_valid))) 
                     | vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcgstop_dfflr__DOT__qout_r));
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_itcm_clkgate__DOT__enb 
            = (1U & (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcgstop_dfflr__DOT__qout_r 
                     | ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__itcm_active) 
                        | (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__itcm_active_dffr__DOT__qout_r))));
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_core_biu 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_biu_clkgate__DOT__enb));
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_itcm 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_aon) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_clk_ctrl__DOT__u_itcm_clkgate__DOT__enb));
    if ((1U & (~ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_itcm)))) {
        vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_ram_clkgate__DOT__enb 
            = (1U & ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__itcm_ram_cs) 
                     | (vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_exu__DOT__u_e203_exu_csr__DOT__mcgstop_dfflr__DOT__qout_r 
                        >> 1U)));
    }
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__clk_itcm_ram 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__clk_itcm) 
           & (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_itcm_ctrl__DOT__u_sram_icb_ctrl__DOT__u_sirv_1cyc_sram_ctrl__DOT__u_ram_clkgate__DOT__enb));
}

VL_INLINE_OPT void Vsoc_cpu_tb___024root___nba_comb__TOP__101(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___nba_comb__TOP__101\n"); );
    // Body
    vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__vec_en 
        = ((IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__ren) 
           ^ (IData)(vlSelf->soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_cpu_top__DOT__u_e203_cpu__DOT__u_e203_core__DOT__u_e203_biu__DOT__u_sirv_gnrl_icb_buffer__DOT__u_sirv_gnrl_cmd_fifo__DOT__dp_gt0__DOT__wen));
}

void Vsoc_cpu_tb___024root___timing_resume(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___timing_resume\n"); );
    // Body
    if ((0x8000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_had69011e__0.resume("@(posedge soc_cpu_tb.clk or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_subsys_hclkgen.plloutclk_rst_n)");
    }
    if ((0x100ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h691aab8b__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)");
    }
    if ((0x10000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h4d165f00__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((0x20000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h049509a0__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_ifu or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((0x40000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h905510fc__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_ifu)");
    }
    if ((0x80000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h69e95abb__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_exu)");
    }
    if ((0x100000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hc23df58f__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_exu or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((0x200000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hee721468__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_lsu or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((0x400000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hd4587b9c__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_lsu)");
    }
    if ((0x800000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h3f13d681__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_biu or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((0x1000000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h4e8810c9__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_biu)");
    }
    if ((0x2000000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h5cd30120__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_itcm or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((0x4000000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h05f2f6a2__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_itcm)");
    }
    if ((0x8000000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h5cec7624__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_dtcm or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((0x200ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_ha9bf999f__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_dtcm)");
    }
    if ((0x1000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h4ebf0c7c__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)");
    }
    if ((0x4000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hedcf1530__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_exu or negedge soc_cpu_tb.cpu.u_subsys.u_sirv_debug_module.u_dm_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(1U))) {
        vlSelf->__VtrigSched_ha0873f9f__0.resume("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_sirv_debug_module.u_dm_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)");
    }
    if ((0x8000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h82d58b05__0.resume("@(negedge soc_cpu_tb.cpu.u_subsys.u_sirv_debug_module.u_jtag_ResetCatchAndSync_3_1.reset_n_catch_reg.reg_0_q)");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(1U))) {
        vlSelf->__VtrigSched_hdb80abc5__0.resume("@(negedge soc_cpu_tb.cpu.u_subsys.u_sirv_aon_top.u_sirv_aon_wrapper.ResetCatchAndSync_1_1.reset_n_catch_reg.reg_0_q or posedge soc_cpu_tb.lfclk)");
    }
    if ((0x10000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_he90e9304__0.resume("@(posedge soc_cpu_tb.lfclk)");
    }
    if ((0x20000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_haa998974__0.resume("@(negedge soc_cpu_tb.cpu.u_subsys.u_sirv_aon_top.u_sirv_aon_wrapper.aonrst_catch.reset_n_catch_reg.reg_0_q or posedge soc_cpu_tb.lfclk)");
    }
    if ((0x4000000000000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vsoc_cpu_tb___024root___timing_commit(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___timing_commit\n"); );
    // Body
    if ((! (0x8000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_had69011e__0.commit("@(posedge soc_cpu_tb.clk or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_subsys_hclkgen.plloutclk_rst_n)");
    }
    if ((! (0x100ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h691aab8b__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_main_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)");
    }
    if ((! (0x10000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h4d165f00__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((! (0x20000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h049509a0__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_ifu or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((! (0x40000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h905510fc__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_ifu)");
    }
    if ((! (0x80000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h69e95abb__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_exu)");
    }
    if ((! (0x100000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hc23df58f__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_exu or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((! (0x200000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hee721468__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_lsu or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((! (0x400000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hd4587b9c__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_lsu)");
    }
    if ((! (0x800000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h3f13d681__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_biu or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((! (0x1000000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h4e8810c9__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_biu)");
    }
    if ((! (0x2000000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h5cd30120__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_itcm or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((! (0x4000000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h05f2f6a2__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_itcm)");
    }
    if ((! (0x8000000000000000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h5cec7624__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_dtcm or negedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.rst_core)");
    }
    if ((! (0x200ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_ha9bf999f__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_dtcm)");
    }
    if ((! (0x1000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h4ebf0c7c__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon)");
    }
    if ((! (0x4000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hedcf1530__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_core_exu or negedge soc_cpu_tb.cpu.u_subsys.u_sirv_debug_module.u_dm_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)");
    }
    if ((! (1ULL & vlSelf->__VactTriggered.word(1U)))) {
        vlSelf->__VtrigSched_ha0873f9f__0.commit("@(posedge soc_cpu_tb.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.clk_aon or negedge soc_cpu_tb.cpu.u_subsys.u_sirv_debug_module.u_dm_ResetCatchAndSync_2_1.reset_n_catch_reg.reg_0_q)");
    }
    if ((! (0x8000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h82d58b05__0.commit("@(negedge soc_cpu_tb.cpu.u_subsys.u_sirv_debug_module.u_jtag_ResetCatchAndSync_3_1.reset_n_catch_reg.reg_0_q)");
    }
    if ((! (2ULL & vlSelf->__VactTriggered.word(1U)))) {
        vlSelf->__VtrigSched_hdb80abc5__0.commit("@(negedge soc_cpu_tb.cpu.u_subsys.u_sirv_aon_top.u_sirv_aon_wrapper.ResetCatchAndSync_1_1.reset_n_catch_reg.reg_0_q or posedge soc_cpu_tb.lfclk)");
    }
    if ((! (0x10000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_he90e9304__0.commit("@(posedge soc_cpu_tb.lfclk)");
    }
    if ((! (0x20000ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_haa998974__0.commit("@(negedge soc_cpu_tb.cpu.u_subsys.u_sirv_aon_top.u_sirv_aon_wrapper.aonrst_catch.reset_n_catch_reg.reg_0_q or posedge soc_cpu_tb.lfclk)");
    }
}

void Vsoc_cpu_tb___024root___eval_triggers__act(Vsoc_cpu_tb___024root* vlSelf);
void Vsoc_cpu_tb___024root___eval_act(Vsoc_cpu_tb___024root* vlSelf);

bool Vsoc_cpu_tb___024root___eval_phase__act(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<66> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vsoc_cpu_tb___024root___eval_triggers__act(vlSelf);
    Vsoc_cpu_tb___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vsoc_cpu_tb___024root___timing_resume(vlSelf);
        Vsoc_cpu_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void Vsoc_cpu_tb___024root___eval_nba(Vsoc_cpu_tb___024root* vlSelf);

bool Vsoc_cpu_tb___024root___eval_phase__nba(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vsoc_cpu_tb___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_cpu_tb___024root___dump_triggers__nba(Vsoc_cpu_tb___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_cpu_tb___024root___dump_triggers__act(Vsoc_cpu_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vsoc_cpu_tb___024root___eval(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vsoc_cpu_tb___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/mnt/d/github/kwt/dv/revd_opt/soc_cpu_tb.sv", 5, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vsoc_cpu_tb___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/mnt/d/github/kwt/dv/revd_opt/soc_cpu_tb.sv", 5, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vsoc_cpu_tb___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vsoc_cpu_tb___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vsoc_cpu_tb___024root___eval_debug_assertions(Vsoc_cpu_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_cpu_tb___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG

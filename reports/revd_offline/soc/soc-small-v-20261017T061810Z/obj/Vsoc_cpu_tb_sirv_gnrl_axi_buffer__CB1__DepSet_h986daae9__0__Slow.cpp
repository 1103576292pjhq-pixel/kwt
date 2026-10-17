// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb.h for the primary calling header

#include "Vsoc_cpu_tb__pch.h"
#include "Vsoc_cpu_tb__Syms.h"
#include "Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1.h"

VL_ATTR_COLD void Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___stl_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0(Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___stl_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0\n"); );
    // Init
    CData/*1:0*/ __PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_r;
    __PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_r = 0;
    CData/*1:0*/ __PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_r;
    __PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_r = 0;
    CData/*1:0*/ __PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r;
    __PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r = 0;
    CData/*1:0*/ __PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r;
    __PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r = 0;
    // Body
    vlSelf->o_axi_ar_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->o_axi_aw_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->o_axi_rdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->o_axi_wdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->o_axi_bresp_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__ren 
        = (1U & ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                 & (~ ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                       >> 1U))));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__ren 
        = (1U & ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                 & (~ ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                       >> 1U))));
    __PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    __PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    __PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    __PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen 
        = (1U & ((~ ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen 
        = (1U & ((~ ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf_r[0U] 
        = vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r;
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf_r[1U] 
        = vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__1__KET____DOT__fifo_rf_dffl__DOT__qout_r;
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read) 
              & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_rsp_ready)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read)) 
              & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_rsp_ready)));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_read) 
                          & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__expl_axi_icb_cmd_valid)));
    vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0) 
                          & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                             & (~ ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                   >> 1U)))));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0) 
                          & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)) 
                             & (~ ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                   >> 1U)))));
    vlSelf->o_axi_ar_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
    vlSelf->o_axi_aw_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
    vlSelf->o_axi_wdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
    vlSelf->o_axi_bresp_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->o_axi_rdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
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

VL_ATTR_COLD void Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___stl_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0(Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1___stl_sequent__TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer__0\n"); );
    // Init
    CData/*1:0*/ __PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_r;
    __PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_r = 0;
    CData/*1:0*/ __PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_r;
    __PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_r = 0;
    CData/*1:0*/ __PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r;
    __PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r = 0;
    // Body
    vlSelf->o_axi_ar_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->o_axi_aw_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->o_axi_rdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->o_axi_wdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->o_axi_bresp_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__wptr_vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wptr_vec_0_dfflrs__DOT__qout_r)), 1U) 
                    >> 1U)));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__ren 
        = (1U & ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                 & (~ ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                       >> 1U))));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__ren 
        = (1U & ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                 & (~ ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                       >> 1U))));
    __PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    __PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    __PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen 
        = (1U & ((~ ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen 
        = (1U & ((~ ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                     >> 1U)) & (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf_r[0U] 
        = vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r;
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf_r[1U] 
        = vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__1__KET____DOT__fifo_rf_dffl__DOT__qout_r;
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf_r[0U] 
        = vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__0__KET____DOT__fifo_rf_dffl__DOT__qout_r;
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf_r[1U] 
        = vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__fifo_rf__BRA__1__KET____DOT__fifo_rf_dffl__DOT__qout_r;
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r 
        = (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r) 
            << 1U) | (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_0_dfflrs__DOT__qout_r));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read) 
              & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_rsp_ready)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__ren 
        = ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
           & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__i_icb_rsp_read)) 
              & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_rsp_ready)));
    vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_read) 
                          & (IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__expl_axi_icb_cmd_valid)));
    vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0) 
                          & ((~ ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                 >> 3U)) & (~ ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                               >> 1U)))));
    vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__wen 
        = ((~ ((IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
               >> 1U)) & ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT____VdfgTmp_h8ae33124__0) 
                          & ((~ ((IData)(vlSymsp->TOP.soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_rw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                 >> 3U)) & (~ ((IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                               >> 1U)))));
    vlSelf->o_axi_ar_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(__PVT__o_axi_ar_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
    vlSelf->o_axi_aw_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(__PVT__o_axi_aw_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
    vlSelf->o_axi_wdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(__PVT__o_axi_wdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
    vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_nxt 
        = (7U & ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__wen)
                  ? (1U | ((4U & ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                  << 2U)) | ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r) 
                                             << 1U)))
                  : VL_SHIFTR_III(3,3,32, (((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_31_dfflr__DOT__qout_r) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__vec_0_dfflrs__DOT__qout_r)), 1U)));
    vlSelf->o_axi_bresp_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((- (IData)((1U & (IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r)))) 
           & vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
           [0U]);
    vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__mux_rdat 
        = ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__mux_rdat) 
           | ((- (IData)((1U & ((IData)(vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__rptr_vec_r) 
                                >> 1U)))) & vlSelf->__PVT__o_axi_bresp_fifo__DOT__dp_gt0__DOT__fifo_rf_r
              [1U]));
    vlSelf->o_axi_rdata_fifo__DOT____Vcellinp__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr____pinNumber2 
        = (1U & ((~ (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__dp_gt1__DOT__rptr_vec_31_dfflr__DOT__qout_r)) 
                 & (VL_SHIFTL_III(2,2,32, (IData)(vlSelf->__PVT__o_axi_rdata_fifo__DOT__dp_gt0__DOT__rptr_vec_r), 1U) 
                    >> 1U)));
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

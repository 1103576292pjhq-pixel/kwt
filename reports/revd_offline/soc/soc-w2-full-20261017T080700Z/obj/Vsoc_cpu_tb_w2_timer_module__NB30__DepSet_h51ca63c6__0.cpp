// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb_w2.h for the primary calling header

#include "Vsoc_cpu_tb_w2__pch.h"
#include "Vsoc_cpu_tb_w2__Syms.h"
#include "Vsoc_cpu_tb_w2_timer_module__NB30.h"

extern const VlUnpacked<CData/*1:0*/, 32> Vsoc_cpu_tb_w2__ConstPool__TABLE_hfb72848a_0;
extern const VlUnpacked<CData/*0:0*/, 32> Vsoc_cpu_tb_w2__ConstPool__TABLE_h22c22758_0;

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__0(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__0\n"); );
    // Init
    CData/*4:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*7:0*/ __Vdly__u_prescaler__DOT__r_counter;
    __Vdly__u_prescaler__DOT__r_counter = 0;
    CData/*0:0*/ __Vdly__u_comp_ch0__DOT__r_value;
    __Vdly__u_comp_ch0__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch0__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch1__DOT__r_value;
    __Vdly__u_comp_ch1__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch1__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch2__DOT__r_value;
    __Vdly__u_comp_ch2__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch2__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch3__DOT__r_value;
    __Vdly__u_comp_ch3__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch3__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0;
    // Body
    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch3__DOT__r_value = vlSelf->__PVT__u_comp_ch3__DOT__r_value;
    __Vdly__u_comp_ch2__DOT__r_value = vlSelf->__PVT__u_comp_ch2__DOT__r_value;
    __Vdly__u_comp_ch1__DOT__r_value = vlSelf->__PVT__u_comp_ch1__DOT__r_value;
    __Vdly__u_comp_ch0__DOT__r_value = vlSelf->__PVT__u_comp_ch0__DOT__r_value;
    __Vdly__u_prescaler__DOT__r_counter = vlSelf->__PVT__u_prescaler__DOT__r_counter;
    if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
        vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync 
            = ((6U & ((IData)(vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync) 
                      << 1U)) | (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__lfclk));
        if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
            vlSelf->__PVT__u_counter__DOT__r_end = vlSelf->__PVT__u_counter__DOT__s_end;
            vlSelf->__PVT__u_counter__DOT__r_start 
                = vlSelf->__PVT__u_counter__DOT__s_start;
        }
        if (vlSelf->__PVT__s_ctrl_rst) {
            __Vdly__u_comp_ch3__DOT__r_value = 0U;
            __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch2__DOT__r_value = 0U;
            __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch1__DOT__r_value = 0U;
            __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch0__DOT__r_value = 0U;
            __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
        } else if (((IData)(vlSelf->__PVT__s_cnt_evt) 
                    & (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) {
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch3__DOT__r_value;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                            __Vdly__u_comp_ch3__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                            __Vdly__u_comp_ch3__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 1U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch3__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch2__DOT__r_value;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                            __Vdly__u_comp_ch2__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                            __Vdly__u_comp_ch2__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 1U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch2__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch1__DOT__r_value;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                            __Vdly__u_comp_ch1__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                            __Vdly__u_comp_ch1__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 1U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch1__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch0__DOT__r_value;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                            __Vdly__u_comp_ch0__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                            __Vdly__u_comp_ch0__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 1U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch0__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value));
            }
        }
        if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
            vlSelf->__PVT__u_counter__DOT__r_sawtooth 
                = vlSelf->__PVT__u_counter__DOT__s_sawtooth;
        }
        if (vlSelf->__PVT__u_in_stage__DOT__r_armed) {
            vlSelf->__PVT__u_in_stage__DOT__r_event 
                = vlSelf->__PVT__u_in_stage__DOT__s_int_evnt;
        } else if (vlSelf->__PVT__s_cnt_end) {
            vlSelf->__PVT__u_in_stage__DOT__r_event = 0U;
        }
        if (vlSelf->__PVT__u_controller__DOT__r_active) {
            if ((1U & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_in_clk)) 
                       | ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_in_clk) 
                          & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk))))) {
                vlSelf->__PVT__u_in_stage__DOT__r_oldval 
                    = vlSelf->__PVT__u_in_stage__DOT__s_int_sig;
            }
            vlSelf->__PVT__u_counter__DOT__r_event 
                = vlSelf->__PVT__s_presc_evt;
        }
        if (((IData)(vlSelf->__PVT__u_counter__DOT__s_do_update) 
             | ((IData)(vlSelf->__PVT__s_presc_evt) 
                & (IData)(vlSelf->__PVT__u_controller__DOT__r_active)))) {
            vlSelf->__PVT__u_counter__DOT__r_direction 
                = vlSelf->__PVT__u_counter__DOT__s_direction;
            vlSelf->__PVT__u_counter__DOT__r_counter 
                = vlSelf->__PVT__u_counter__DOT__s_counter;
        }
        if (vlSelf->__PVT__s_ctrl_rst) {
            __Vdly__u_prescaler__DOT__r_counter = 0U;
            vlSelf->__PVT__s_presc_evt = 0U;
        } else if (vlSelf->__PVT__u_controller__DOT__r_active) {
            if (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_in_clk)
                  ? ((IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_evnt) 
                     & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk))
                  : (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_evnt))) {
                if ((0U == (IData)(vlSelf->__PVT__u_prescaler__DOT__r_presc))) {
                    vlSelf->__PVT__s_presc_evt = 1U;
                } else if (((IData)(vlSelf->__PVT__u_prescaler__DOT__r_counter) 
                            == (IData)(vlSelf->__PVT__u_prescaler__DOT__r_presc))) {
                    vlSelf->__PVT__s_presc_evt = 1U;
                    __Vdly__u_prescaler__DOT__r_counter = 0U;
                } else {
                    __Vdly__u_prescaler__DOT__r_counter 
                        = (0xffU & ((IData)(1U) + (IData)(vlSelf->__PVT__u_prescaler__DOT__r_counter)));
                    vlSelf->__PVT__s_presc_evt = 0U;
                }
            } else {
                vlSelf->__PVT__s_presc_evt = 0U;
            }
        } else {
            __Vdly__u_prescaler__DOT__r_counter = 0U;
            vlSelf->__PVT__s_presc_evt = 0U;
        }
        if (vlSelf->__PVT__s_ctrl_update_all) {
            vlSelf->__PVT__u_comp_ch3__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch3_th;
            vlSelf->__PVT__u_comp_ch2__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch2_th;
            vlSelf->__PVT__u_comp_ch1__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch1_th;
            vlSelf->__PVT__u_comp_ch0__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch0_th;
            vlSelf->__PVT__u_in_stage__DOT__r_mode 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_in_mode;
            vlSelf->__PVT__u_in_stage__DOT__r_sel = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_in_sel;
            vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch3_mode;
            vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch2_mode;
            vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch1_mode;
            vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_ch0_mode;
            vlSelf->__PVT__u_prescaler__DOT__r_presc 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_presc;
        }
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_arm) {
            vlSelf->__PVT__u_in_stage__DOT__r_armed = 1U;
        } else if (vlSelf->__PVT__s_cnt_end) {
            vlSelf->__PVT__u_in_stage__DOT__r_armed = 0U;
        }
    } else {
        vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync = 0U;
        __Vdly__u_comp_ch3__DOT__r_value = 0U;
        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch2__DOT__r_value = 0U;
        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch1__DOT__r_value = 0U;
        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch0__DOT__r_value = 0U;
        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
        vlSelf->__PVT__u_counter__DOT__r_end = 0U;
        vlSelf->__PVT__u_counter__DOT__r_start = 0U;
        vlSelf->__PVT__u_comp_ch3__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch2__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch1__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch0__DOT__r_comp = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_mode = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_sel = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_event = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_oldval = 0U;
        vlSelf->__PVT__u_counter__DOT__r_event = 0U;
        vlSelf->__PVT__u_counter__DOT__r_direction = 0U;
        vlSelf->__PVT__u_counter__DOT__r_counter = 0U;
        vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_counter__DOT__r_sawtooth = 1U;
        vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_armed = 0U;
        __Vdly__u_prescaler__DOT__r_counter = 0U;
        vlSelf->__PVT__s_presc_evt = 0U;
        vlSelf->__PVT__u_prescaler__DOT__r_presc = 0U;
    }
    vlSelf->__PVT__u_counter__DOT__r_pending_update 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) 
           && (IData)(vlSelf->__PVT__u_counter__DOT__s_pending_update));
    vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch3__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch3__DOT__r_value = __Vdly__u_comp_ch3__DOT__r_value;
    vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch2__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch2__DOT__r_value = __Vdly__u_comp_ch2__DOT__r_value;
    vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch1__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch1__DOT__r_value = __Vdly__u_comp_ch1__DOT__r_value;
    vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch0__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch0__DOT__r_value = __Vdly__u_comp_ch0__DOT__r_value;
    vlSelf->pwm_o = (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value) 
                      << 3U) | (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value) 
                                 << 2U) | (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value))));
    vlSelf->__PVT__u_prescaler__DOT__r_counter = __Vdly__u_prescaler__DOT__r_counter;
    vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk = (IData)(
                                                            (2U 
                                                             == 
                                                             (6U 
                                                              & (IData)(vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync))));
    __Vtableidx1 = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_update) 
                     << 4U) | (((IData)(vlSelf->__PVT__s_cnt_evt) 
                                << 3U) | (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_stop) 
                                           << 2U) | 
                                          (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_start) 
                                            << 1U) 
                                           | (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q)))));
    if ((1U & Vsoc_cpu_tb_w2__ConstPool__TABLE_hfb72848a_0
         [__Vtableidx1])) {
        vlSelf->__PVT__u_controller__DOT__r_active 
            = Vsoc_cpu_tb_w2__ConstPool__TABLE_h22c22758_0
            [__Vtableidx1];
    }
    vlSelf->__PVT__s_cnt_evt = ((IData)(vlSelf->__PVT__u_controller__DOT__r_active) 
                                & (IData)(vlSelf->__PVT__u_counter__DOT__r_event));
    vlSelf->__PVT__u_comp_ch0__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch1__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch2__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch3__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_counter__DOT__s_is_update = ((IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)
                                                   ? 
                                                  ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                                   == (IData)(vlSelf->__PVT__u_counter__DOT__r_end))
                                                   : 
                                                  ((IData)(vlSelf->__PVT__u_counter__DOT__r_direction) 
                                                   & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                                      == 
                                                      ((IData)(vlSelf->__PVT__u_counter__DOT__r_start) 
                                                       - (IData)(1U)))));
    vlSelf->__PVT__s_cnt_end = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                & (IData)(vlSelf->__PVT__u_counter__DOT__s_is_update));
    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
        vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
    } else {
        vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch0__DOT__s_match;
        vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch1__DOT__s_match;
        vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch2__DOT__s_match;
        vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch3__DOT__s_match;
    }
}

extern const VlUnpacked<CData/*0:0*/, 512> Vsoc_cpu_tb_w2__ConstPool__TABLE_h49e93408_0;

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__0(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__0\n"); );
    // Init
    CData/*0:0*/ __PVT__u_in_stage__DOT__s_rise;
    __PVT__u_in_stage__DOT__s_rise = 0;
    CData/*0:0*/ __PVT__u_in_stage__DOT__s_fall;
    __PVT__u_in_stage__DOT__s_fall = 0;
    SData/*8:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    // Body
    vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 0U;
    if ((0U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal));
    }
    if ((1U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 1U)));
    }
    if ((2U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 2U)));
    }
    if ((3U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 3U)));
    }
    if ((4U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 4U)));
    }
    if ((5U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 5U)));
    }
    if ((6U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 6U)));
    }
    if ((7U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 7U)));
    }
    if ((8U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 8U)));
    }
    if ((9U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 9U)));
    }
    if ((0xaU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xaU)));
    }
    if ((0xbU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xbU)));
    }
    if ((0xcU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xcU)));
    }
    if ((0xdU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xdU)));
    }
    if ((0xeU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xeU)));
    }
    if ((0xfU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xfU)));
    }
    if ((0x10U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x10U)));
    }
    if ((0x11U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x11U)));
    }
    if ((0x12U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x12U)));
    }
    if ((0x13U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x13U)));
    }
    if ((0x14U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x14U)));
    }
    if ((0x15U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x15U)));
    }
    if ((0x16U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x16U)));
    }
    if ((0x17U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x17U)));
    }
    if ((0x18U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x18U)));
    }
    if ((0x19U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x19U)));
    }
    if ((0x1aU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1aU)));
    }
    if ((0x1bU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1bU)));
    }
    if ((0x1cU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1cU)));
    }
    if ((0x1dU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1dU)));
    }
    if ((0x1eU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1eU)));
    }
    if ((0x1fU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1fU)));
    }
    if ((0x20U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x20U)));
    }
    if ((0x21U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x21U)));
    }
    if ((0x22U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x22U)));
    }
    if ((0x23U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x23U)));
    }
    if ((0x24U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x24U)));
    }
    if ((0x25U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x25U)));
    }
    if ((0x26U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x26U)));
    }
    if ((0x27U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x27U)));
    }
    if ((0x28U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x28U)));
    }
    if ((0x29U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x29U)));
    }
    if ((0x2aU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2aU)));
    }
    if ((0x2bU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2bU)));
    }
    if ((0x2cU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2cU)));
    }
    if ((0x2dU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2dU)));
    }
    if ((0x2eU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2eU)));
    }
    if ((0x2fU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2fU)));
    }
    __PVT__u_in_stage__DOT__s_rise = ((~ (IData)(vlSelf->__PVT__u_in_stage__DOT__r_oldval)) 
                                      & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig));
    __PVT__u_in_stage__DOT__s_fall = ((~ (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig)) 
                                      & (IData)(vlSelf->__PVT__u_in_stage__DOT__r_oldval));
    __Vtableidx2 = (((IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig) 
                     << 8U) | ((((IData)(__PVT__u_in_stage__DOT__s_rise) 
                                 | (IData)(__PVT__u_in_stage__DOT__s_fall)) 
                                << 7U) | (((IData)(__PVT__u_in_stage__DOT__s_rise) 
                                           << 6U) | 
                                          (((IData)(vlSelf->__PVT__u_in_stage__DOT__r_event) 
                                            << 5U) 
                                           | (((IData)(__PVT__u_in_stage__DOT__s_fall) 
                                               << 4U) 
                                              | (((IData)(vlSelf->__PVT__u_in_stage__DOT__r_armed) 
                                                  << 3U) 
                                                 | (IData)(vlSelf->__PVT__u_in_stage__DOT__r_mode)))))));
    vlSelf->__PVT__u_in_stage__DOT__s_int_evnt = Vsoc_cpu_tb_w2__ConstPool__TABLE_h49e93408_0
        [__Vtableidx2];
}

extern const VlUnpacked<CData/*0:0*/, 64> Vsoc_cpu_tb_w2__ConstPool__TABLE_h38c04461_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vsoc_cpu_tb_w2__ConstPool__TABLE_hc6e5c112_0;

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__1(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0__1\n"); );
    // Init
    CData/*5:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    // Body
    vlSelf->__PVT__s_ctrl_update_all = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_start) 
                                         & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                        || (IData)(vlSelf->__PVT__s_cnt_evt));
    vlSelf->__PVT__s_ctrl_rst = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_start) 
                                  & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                 || (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_rst));
    __Vtableidx3 = (((IData)(vlSelf->__PVT__s_ctrl_rst) 
                     << 5U) | (((IData)(vlSelf->__PVT__s_presc_evt) 
                                << 4U) | (((IData)(vlSelf->__PVT__u_counter__DOT__s_is_update) 
                                           << 3U) | 
                                          (((IData)(vlSelf->__PVT__u_controller__DOT__r_active) 
                                            << 2U) 
                                           | (((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_start) 
                                                 & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                                || (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_update)) 
                                               << 1U) 
                                              | (IData)(vlSelf->__PVT__u_counter__DOT__r_pending_update))))));
    vlSelf->__PVT__u_counter__DOT__s_pending_update 
        = Vsoc_cpu_tb_w2__ConstPool__TABLE_h38c04461_0
        [__Vtableidx3];
    vlSelf->__PVT__u_counter__DOT__s_do_update = Vsoc_cpu_tb_w2__ConstPool__TABLE_hc6e5c112_0
        [__Vtableidx3];
    vlSelf->__PVT__u_counter__DOT__s_start = vlSelf->__PVT__u_counter__DOT__r_start;
    vlSelf->__PVT__u_counter__DOT__s_sawtooth = vlSelf->__PVT__u_counter__DOT__r_sawtooth;
    vlSelf->__PVT__u_counter__DOT__s_end = vlSelf->__PVT__u_counter__DOT__r_end;
    vlSelf->__PVT__u_counter__DOT__s_direction = vlSelf->__PVT__u_counter__DOT__r_direction;
    vlSelf->__PVT__u_counter__DOT__s_counter = vlSelf->__PVT__u_counter__DOT__r_counter;
    if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
        vlSelf->__PVT__u_counter__DOT__s_start = (0xffffU 
                                                  & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_th);
        vlSelf->__PVT__u_counter__DOT__s_sawtooth = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_saw;
        vlSelf->__PVT__u_counter__DOT__s_end = (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_th 
                                                >> 0x10U);
        vlSelf->__PVT__u_counter__DOT__s_direction = 0U;
        vlSelf->__PVT__u_counter__DOT__s_counter = 
            (0xffffU & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer0_th);
    } else if (((IData)(vlSelf->__PVT__s_presc_evt) 
                & (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) {
        if (((~ (IData)(vlSelf->__PVT__u_counter__DOT__r_direction)) 
             & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                == (IData)(vlSelf->__PVT__u_counter__DOT__r_end)))) {
            vlSelf->__PVT__u_counter__DOT__s_direction 
                = (1U & (~ (IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)));
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)
                               ? (IData)(vlSelf->__PVT__u_counter__DOT__r_start)
                               : ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                  - (IData)(1U))));
        } else if (((IData)(vlSelf->__PVT__u_counter__DOT__r_direction) 
                    & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                       == (IData)(vlSelf->__PVT__u_counter__DOT__r_start)))) {
            vlSelf->__PVT__u_counter__DOT__s_direction = 0U;
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(1U) + (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
        } else {
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(vlSelf->__PVT__u_counter__DOT__r_direction)
                               ? ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                  - (IData)(1U)) : 
                              ((IData)(1U) + (IData)(vlSelf->__PVT__u_counter__DOT__r_counter))));
        }
    }
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__0(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__0\n"); );
    // Init
    CData/*4:0*/ __Vtableidx4;
    __Vtableidx4 = 0;
    CData/*7:0*/ __Vdly__u_prescaler__DOT__r_counter;
    __Vdly__u_prescaler__DOT__r_counter = 0;
    CData/*0:0*/ __Vdly__u_comp_ch0__DOT__r_value;
    __Vdly__u_comp_ch0__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch0__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch1__DOT__r_value;
    __Vdly__u_comp_ch1__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch1__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch2__DOT__r_value;
    __Vdly__u_comp_ch2__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch2__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch3__DOT__r_value;
    __Vdly__u_comp_ch3__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch3__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0;
    // Body
    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch3__DOT__r_value = vlSelf->__PVT__u_comp_ch3__DOT__r_value;
    __Vdly__u_comp_ch2__DOT__r_value = vlSelf->__PVT__u_comp_ch2__DOT__r_value;
    __Vdly__u_comp_ch1__DOT__r_value = vlSelf->__PVT__u_comp_ch1__DOT__r_value;
    __Vdly__u_comp_ch0__DOT__r_value = vlSelf->__PVT__u_comp_ch0__DOT__r_value;
    __Vdly__u_prescaler__DOT__r_counter = vlSelf->__PVT__u_prescaler__DOT__r_counter;
    if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
        vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync 
            = ((6U & ((IData)(vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync) 
                      << 1U)) | (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__lfclk));
        if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
            vlSelf->__PVT__u_counter__DOT__r_end = vlSelf->__PVT__u_counter__DOT__s_end;
            vlSelf->__PVT__u_counter__DOT__r_start 
                = vlSelf->__PVT__u_counter__DOT__s_start;
        }
        if (vlSelf->__PVT__s_ctrl_rst) {
            __Vdly__u_comp_ch3__DOT__r_value = 0U;
            __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch2__DOT__r_value = 0U;
            __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch1__DOT__r_value = 0U;
            __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch0__DOT__r_value = 0U;
            __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
        } else if (((IData)(vlSelf->__PVT__s_cnt_evt) 
                    & (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) {
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch3__DOT__r_value;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                            __Vdly__u_comp_ch3__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                            __Vdly__u_comp_ch3__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 1U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch3__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch2__DOT__r_value;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                            __Vdly__u_comp_ch2__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                            __Vdly__u_comp_ch2__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 1U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch2__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch1__DOT__r_value;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                            __Vdly__u_comp_ch1__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                            __Vdly__u_comp_ch1__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 1U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch1__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch0__DOT__r_value;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                            __Vdly__u_comp_ch0__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                            __Vdly__u_comp_ch0__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 1U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch0__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value));
            }
        }
        if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
            vlSelf->__PVT__u_counter__DOT__r_sawtooth 
                = vlSelf->__PVT__u_counter__DOT__s_sawtooth;
        }
        if (vlSelf->__PVT__u_in_stage__DOT__r_armed) {
            vlSelf->__PVT__u_in_stage__DOT__r_event 
                = vlSelf->__PVT__u_in_stage__DOT__s_int_evnt;
        } else if (vlSelf->__PVT__s_cnt_end) {
            vlSelf->__PVT__u_in_stage__DOT__r_event = 0U;
        }
        if (vlSelf->__PVT__u_controller__DOT__r_active) {
            if ((1U & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_in_clk)) 
                       | ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_in_clk) 
                          & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk))))) {
                vlSelf->__PVT__u_in_stage__DOT__r_oldval 
                    = vlSelf->__PVT__u_in_stage__DOT__s_int_sig;
            }
            vlSelf->__PVT__u_counter__DOT__r_event 
                = vlSelf->__PVT__s_presc_evt;
        }
        if (((IData)(vlSelf->__PVT__u_counter__DOT__s_do_update) 
             | ((IData)(vlSelf->__PVT__s_presc_evt) 
                & (IData)(vlSelf->__PVT__u_controller__DOT__r_active)))) {
            vlSelf->__PVT__u_counter__DOT__r_direction 
                = vlSelf->__PVT__u_counter__DOT__s_direction;
            vlSelf->__PVT__u_counter__DOT__r_counter 
                = vlSelf->__PVT__u_counter__DOT__s_counter;
        }
        if (vlSelf->__PVT__s_ctrl_rst) {
            __Vdly__u_prescaler__DOT__r_counter = 0U;
            vlSelf->__PVT__s_presc_evt = 0U;
        } else if (vlSelf->__PVT__u_controller__DOT__r_active) {
            if (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_in_clk)
                  ? ((IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_evnt) 
                     & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk))
                  : (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_evnt))) {
                if ((0U == (IData)(vlSelf->__PVT__u_prescaler__DOT__r_presc))) {
                    vlSelf->__PVT__s_presc_evt = 1U;
                } else if (((IData)(vlSelf->__PVT__u_prescaler__DOT__r_counter) 
                            == (IData)(vlSelf->__PVT__u_prescaler__DOT__r_presc))) {
                    vlSelf->__PVT__s_presc_evt = 1U;
                    __Vdly__u_prescaler__DOT__r_counter = 0U;
                } else {
                    __Vdly__u_prescaler__DOT__r_counter 
                        = (0xffU & ((IData)(1U) + (IData)(vlSelf->__PVT__u_prescaler__DOT__r_counter)));
                    vlSelf->__PVT__s_presc_evt = 0U;
                }
            } else {
                vlSelf->__PVT__s_presc_evt = 0U;
            }
        } else {
            __Vdly__u_prescaler__DOT__r_counter = 0U;
            vlSelf->__PVT__s_presc_evt = 0U;
        }
        if (vlSelf->__PVT__s_ctrl_update_all) {
            vlSelf->__PVT__u_comp_ch3__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch3_th;
            vlSelf->__PVT__u_comp_ch2__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch2_th;
            vlSelf->__PVT__u_comp_ch1__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch1_th;
            vlSelf->__PVT__u_comp_ch0__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch0_th;
            vlSelf->__PVT__u_in_stage__DOT__r_mode 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_in_mode;
            vlSelf->__PVT__u_in_stage__DOT__r_sel = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_in_sel;
            vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch3_mode;
            vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch2_mode;
            vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch1_mode;
            vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_ch0_mode;
            vlSelf->__PVT__u_prescaler__DOT__r_presc 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_presc;
        }
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_arm) {
            vlSelf->__PVT__u_in_stage__DOT__r_armed = 1U;
        } else if (vlSelf->__PVT__s_cnt_end) {
            vlSelf->__PVT__u_in_stage__DOT__r_armed = 0U;
        }
    } else {
        vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync = 0U;
        __Vdly__u_comp_ch3__DOT__r_value = 0U;
        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch2__DOT__r_value = 0U;
        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch1__DOT__r_value = 0U;
        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch0__DOT__r_value = 0U;
        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
        vlSelf->__PVT__u_counter__DOT__r_end = 0U;
        vlSelf->__PVT__u_counter__DOT__r_start = 0U;
        vlSelf->__PVT__u_comp_ch3__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch2__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch1__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch0__DOT__r_comp = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_mode = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_sel = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_event = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_oldval = 0U;
        vlSelf->__PVT__u_counter__DOT__r_event = 0U;
        vlSelf->__PVT__u_counter__DOT__r_direction = 0U;
        vlSelf->__PVT__u_counter__DOT__r_counter = 0U;
        vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_counter__DOT__r_sawtooth = 1U;
        vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_armed = 0U;
        __Vdly__u_prescaler__DOT__r_counter = 0U;
        vlSelf->__PVT__s_presc_evt = 0U;
        vlSelf->__PVT__u_prescaler__DOT__r_presc = 0U;
    }
    vlSelf->__PVT__u_counter__DOT__r_pending_update 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) 
           && (IData)(vlSelf->__PVT__u_counter__DOT__s_pending_update));
    vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch3__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch3__DOT__r_value = __Vdly__u_comp_ch3__DOT__r_value;
    vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch2__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch2__DOT__r_value = __Vdly__u_comp_ch2__DOT__r_value;
    vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch1__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch1__DOT__r_value = __Vdly__u_comp_ch1__DOT__r_value;
    vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch0__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch0__DOT__r_value = __Vdly__u_comp_ch0__DOT__r_value;
    vlSelf->pwm_o = (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value) 
                      << 3U) | (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value) 
                                 << 2U) | (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value))));
    vlSelf->__PVT__u_prescaler__DOT__r_counter = __Vdly__u_prescaler__DOT__r_counter;
    vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk = (IData)(
                                                            (2U 
                                                             == 
                                                             (6U 
                                                              & (IData)(vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync))));
    __Vtableidx4 = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_update) 
                     << 4U) | (((IData)(vlSelf->__PVT__s_cnt_evt) 
                                << 3U) | (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_stop) 
                                           << 2U) | 
                                          (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_start) 
                                            << 1U) 
                                           | (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q)))));
    if ((1U & Vsoc_cpu_tb_w2__ConstPool__TABLE_hfb72848a_0
         [__Vtableidx4])) {
        vlSelf->__PVT__u_controller__DOT__r_active 
            = Vsoc_cpu_tb_w2__ConstPool__TABLE_h22c22758_0
            [__Vtableidx4];
    }
    vlSelf->__PVT__s_cnt_evt = ((IData)(vlSelf->__PVT__u_controller__DOT__r_active) 
                                & (IData)(vlSelf->__PVT__u_counter__DOT__r_event));
    vlSelf->__PVT__u_comp_ch0__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch1__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch2__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch3__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_counter__DOT__s_is_update = ((IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)
                                                   ? 
                                                  ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                                   == (IData)(vlSelf->__PVT__u_counter__DOT__r_end))
                                                   : 
                                                  ((IData)(vlSelf->__PVT__u_counter__DOT__r_direction) 
                                                   & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                                      == 
                                                      ((IData)(vlSelf->__PVT__u_counter__DOT__r_start) 
                                                       - (IData)(1U)))));
    vlSelf->__PVT__s_cnt_end = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                & (IData)(vlSelf->__PVT__u_counter__DOT__s_is_update));
    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
        vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
    } else {
        vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch0__DOT__s_match;
        vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch1__DOT__s_match;
        vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch2__DOT__s_match;
        vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch3__DOT__s_match;
    }
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__0(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__0\n"); );
    // Init
    CData/*0:0*/ __PVT__u_in_stage__DOT__s_rise;
    __PVT__u_in_stage__DOT__s_rise = 0;
    CData/*0:0*/ __PVT__u_in_stage__DOT__s_fall;
    __PVT__u_in_stage__DOT__s_fall = 0;
    SData/*8:0*/ __Vtableidx5;
    __Vtableidx5 = 0;
    // Body
    vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 0U;
    if ((0U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal));
    }
    if ((1U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 1U)));
    }
    if ((2U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 2U)));
    }
    if ((3U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 3U)));
    }
    if ((4U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 4U)));
    }
    if ((5U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 5U)));
    }
    if ((6U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 6U)));
    }
    if ((7U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 7U)));
    }
    if ((8U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 8U)));
    }
    if ((9U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 9U)));
    }
    if ((0xaU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xaU)));
    }
    if ((0xbU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xbU)));
    }
    if ((0xcU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xcU)));
    }
    if ((0xdU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xdU)));
    }
    if ((0xeU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xeU)));
    }
    if ((0xfU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xfU)));
    }
    if ((0x10U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x10U)));
    }
    if ((0x11U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x11U)));
    }
    if ((0x12U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x12U)));
    }
    if ((0x13U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x13U)));
    }
    if ((0x14U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x14U)));
    }
    if ((0x15U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x15U)));
    }
    if ((0x16U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x16U)));
    }
    if ((0x17U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x17U)));
    }
    if ((0x18U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x18U)));
    }
    if ((0x19U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x19U)));
    }
    if ((0x1aU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1aU)));
    }
    if ((0x1bU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1bU)));
    }
    if ((0x1cU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1cU)));
    }
    if ((0x1dU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1dU)));
    }
    if ((0x1eU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1eU)));
    }
    if ((0x1fU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1fU)));
    }
    if ((0x20U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x20U)));
    }
    if ((0x21U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x21U)));
    }
    if ((0x22U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x22U)));
    }
    if ((0x23U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x23U)));
    }
    if ((0x24U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x24U)));
    }
    if ((0x25U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x25U)));
    }
    if ((0x26U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x26U)));
    }
    if ((0x27U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x27U)));
    }
    if ((0x28U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x28U)));
    }
    if ((0x29U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x29U)));
    }
    if ((0x2aU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2aU)));
    }
    if ((0x2bU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2bU)));
    }
    if ((0x2cU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2cU)));
    }
    if ((0x2dU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2dU)));
    }
    if ((0x2eU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2eU)));
    }
    if ((0x2fU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2fU)));
    }
    __PVT__u_in_stage__DOT__s_rise = ((~ (IData)(vlSelf->__PVT__u_in_stage__DOT__r_oldval)) 
                                      & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig));
    __PVT__u_in_stage__DOT__s_fall = ((~ (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig)) 
                                      & (IData)(vlSelf->__PVT__u_in_stage__DOT__r_oldval));
    __Vtableidx5 = (((IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig) 
                     << 8U) | ((((IData)(__PVT__u_in_stage__DOT__s_rise) 
                                 | (IData)(__PVT__u_in_stage__DOT__s_fall)) 
                                << 7U) | (((IData)(__PVT__u_in_stage__DOT__s_rise) 
                                           << 6U) | 
                                          (((IData)(vlSelf->__PVT__u_in_stage__DOT__r_event) 
                                            << 5U) 
                                           | (((IData)(__PVT__u_in_stage__DOT__s_fall) 
                                               << 4U) 
                                              | (((IData)(vlSelf->__PVT__u_in_stage__DOT__r_armed) 
                                                  << 3U) 
                                                 | (IData)(vlSelf->__PVT__u_in_stage__DOT__r_mode)))))));
    vlSelf->__PVT__u_in_stage__DOT__s_int_evnt = Vsoc_cpu_tb_w2__ConstPool__TABLE_h49e93408_0
        [__Vtableidx5];
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__1(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1__1\n"); );
    // Init
    CData/*5:0*/ __Vtableidx6;
    __Vtableidx6 = 0;
    // Body
    vlSelf->__PVT__s_ctrl_update_all = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_start) 
                                         & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                        || (IData)(vlSelf->__PVT__s_cnt_evt));
    vlSelf->__PVT__s_ctrl_rst = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_start) 
                                  & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                 || (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_rst));
    __Vtableidx6 = (((IData)(vlSelf->__PVT__s_ctrl_rst) 
                     << 5U) | (((IData)(vlSelf->__PVT__s_presc_evt) 
                                << 4U) | (((IData)(vlSelf->__PVT__u_counter__DOT__s_is_update) 
                                           << 3U) | 
                                          (((IData)(vlSelf->__PVT__u_controller__DOT__r_active) 
                                            << 2U) 
                                           | (((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_start) 
                                                 & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                                || (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_update)) 
                                               << 1U) 
                                              | (IData)(vlSelf->__PVT__u_counter__DOT__r_pending_update))))));
    vlSelf->__PVT__u_counter__DOT__s_pending_update 
        = Vsoc_cpu_tb_w2__ConstPool__TABLE_h38c04461_0
        [__Vtableidx6];
    vlSelf->__PVT__u_counter__DOT__s_do_update = Vsoc_cpu_tb_w2__ConstPool__TABLE_hc6e5c112_0
        [__Vtableidx6];
    vlSelf->__PVT__u_counter__DOT__s_start = vlSelf->__PVT__u_counter__DOT__r_start;
    vlSelf->__PVT__u_counter__DOT__s_sawtooth = vlSelf->__PVT__u_counter__DOT__r_sawtooth;
    vlSelf->__PVT__u_counter__DOT__s_end = vlSelf->__PVT__u_counter__DOT__r_end;
    vlSelf->__PVT__u_counter__DOT__s_direction = vlSelf->__PVT__u_counter__DOT__r_direction;
    vlSelf->__PVT__u_counter__DOT__s_counter = vlSelf->__PVT__u_counter__DOT__r_counter;
    if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
        vlSelf->__PVT__u_counter__DOT__s_start = (0xffffU 
                                                  & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_th);
        vlSelf->__PVT__u_counter__DOT__s_sawtooth = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_saw;
        vlSelf->__PVT__u_counter__DOT__s_end = (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_th 
                                                >> 0x10U);
        vlSelf->__PVT__u_counter__DOT__s_direction = 0U;
        vlSelf->__PVT__u_counter__DOT__s_counter = 
            (0xffffU & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer1_th);
    } else if (((IData)(vlSelf->__PVT__s_presc_evt) 
                & (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) {
        if (((~ (IData)(vlSelf->__PVT__u_counter__DOT__r_direction)) 
             & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                == (IData)(vlSelf->__PVT__u_counter__DOT__r_end)))) {
            vlSelf->__PVT__u_counter__DOT__s_direction 
                = (1U & (~ (IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)));
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)
                               ? (IData)(vlSelf->__PVT__u_counter__DOT__r_start)
                               : ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                  - (IData)(1U))));
        } else if (((IData)(vlSelf->__PVT__u_counter__DOT__r_direction) 
                    & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                       == (IData)(vlSelf->__PVT__u_counter__DOT__r_start)))) {
            vlSelf->__PVT__u_counter__DOT__s_direction = 0U;
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(1U) + (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
        } else {
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(vlSelf->__PVT__u_counter__DOT__r_direction)
                               ? ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                  - (IData)(1U)) : 
                              ((IData)(1U) + (IData)(vlSelf->__PVT__u_counter__DOT__r_counter))));
        }
    }
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__0(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__0\n"); );
    // Init
    CData/*4:0*/ __Vtableidx7;
    __Vtableidx7 = 0;
    CData/*7:0*/ __Vdly__u_prescaler__DOT__r_counter;
    __Vdly__u_prescaler__DOT__r_counter = 0;
    CData/*0:0*/ __Vdly__u_comp_ch0__DOT__r_value;
    __Vdly__u_comp_ch0__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch0__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch1__DOT__r_value;
    __Vdly__u_comp_ch1__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch1__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch2__DOT__r_value;
    __Vdly__u_comp_ch2__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch2__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch3__DOT__r_value;
    __Vdly__u_comp_ch3__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch3__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0;
    // Body
    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch3__DOT__r_value = vlSelf->__PVT__u_comp_ch3__DOT__r_value;
    __Vdly__u_comp_ch2__DOT__r_value = vlSelf->__PVT__u_comp_ch2__DOT__r_value;
    __Vdly__u_comp_ch1__DOT__r_value = vlSelf->__PVT__u_comp_ch1__DOT__r_value;
    __Vdly__u_comp_ch0__DOT__r_value = vlSelf->__PVT__u_comp_ch0__DOT__r_value;
    __Vdly__u_prescaler__DOT__r_counter = vlSelf->__PVT__u_prescaler__DOT__r_counter;
    if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
        vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync 
            = ((6U & ((IData)(vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync) 
                      << 1U)) | (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__lfclk));
        if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
            vlSelf->__PVT__u_counter__DOT__r_end = vlSelf->__PVT__u_counter__DOT__s_end;
            vlSelf->__PVT__u_counter__DOT__r_start 
                = vlSelf->__PVT__u_counter__DOT__s_start;
        }
        if (vlSelf->__PVT__s_ctrl_rst) {
            __Vdly__u_comp_ch3__DOT__r_value = 0U;
            __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch2__DOT__r_value = 0U;
            __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch1__DOT__r_value = 0U;
            __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch0__DOT__r_value = 0U;
            __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
        } else if (((IData)(vlSelf->__PVT__s_cnt_evt) 
                    & (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) {
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch3__DOT__r_value;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                            __Vdly__u_comp_ch3__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                            __Vdly__u_comp_ch3__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 1U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch3__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch2__DOT__r_value;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                            __Vdly__u_comp_ch2__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                            __Vdly__u_comp_ch2__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 1U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch2__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch1__DOT__r_value;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                            __Vdly__u_comp_ch1__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                            __Vdly__u_comp_ch1__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 1U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch1__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch0__DOT__r_value;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                            __Vdly__u_comp_ch0__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                            __Vdly__u_comp_ch0__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 1U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch0__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value));
            }
        }
        if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
            vlSelf->__PVT__u_counter__DOT__r_sawtooth 
                = vlSelf->__PVT__u_counter__DOT__s_sawtooth;
        }
        if (vlSelf->__PVT__u_in_stage__DOT__r_armed) {
            vlSelf->__PVT__u_in_stage__DOT__r_event 
                = vlSelf->__PVT__u_in_stage__DOT__s_int_evnt;
        } else if (vlSelf->__PVT__s_cnt_end) {
            vlSelf->__PVT__u_in_stage__DOT__r_event = 0U;
        }
        if (vlSelf->__PVT__u_controller__DOT__r_active) {
            if ((1U & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_in_clk)) 
                       | ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_in_clk) 
                          & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk))))) {
                vlSelf->__PVT__u_in_stage__DOT__r_oldval 
                    = vlSelf->__PVT__u_in_stage__DOT__s_int_sig;
            }
            vlSelf->__PVT__u_counter__DOT__r_event 
                = vlSelf->__PVT__s_presc_evt;
        }
        if (((IData)(vlSelf->__PVT__u_counter__DOT__s_do_update) 
             | ((IData)(vlSelf->__PVT__s_presc_evt) 
                & (IData)(vlSelf->__PVT__u_controller__DOT__r_active)))) {
            vlSelf->__PVT__u_counter__DOT__r_direction 
                = vlSelf->__PVT__u_counter__DOT__s_direction;
            vlSelf->__PVT__u_counter__DOT__r_counter 
                = vlSelf->__PVT__u_counter__DOT__s_counter;
        }
        if (vlSelf->__PVT__s_ctrl_rst) {
            __Vdly__u_prescaler__DOT__r_counter = 0U;
            vlSelf->__PVT__s_presc_evt = 0U;
        } else if (vlSelf->__PVT__u_controller__DOT__r_active) {
            if (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_in_clk)
                  ? ((IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_evnt) 
                     & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk))
                  : (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_evnt))) {
                if ((0U == (IData)(vlSelf->__PVT__u_prescaler__DOT__r_presc))) {
                    vlSelf->__PVT__s_presc_evt = 1U;
                } else if (((IData)(vlSelf->__PVT__u_prescaler__DOT__r_counter) 
                            == (IData)(vlSelf->__PVT__u_prescaler__DOT__r_presc))) {
                    vlSelf->__PVT__s_presc_evt = 1U;
                    __Vdly__u_prescaler__DOT__r_counter = 0U;
                } else {
                    __Vdly__u_prescaler__DOT__r_counter 
                        = (0xffU & ((IData)(1U) + (IData)(vlSelf->__PVT__u_prescaler__DOT__r_counter)));
                    vlSelf->__PVT__s_presc_evt = 0U;
                }
            } else {
                vlSelf->__PVT__s_presc_evt = 0U;
            }
        } else {
            __Vdly__u_prescaler__DOT__r_counter = 0U;
            vlSelf->__PVT__s_presc_evt = 0U;
        }
        if (vlSelf->__PVT__s_ctrl_update_all) {
            vlSelf->__PVT__u_comp_ch3__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch3_th;
            vlSelf->__PVT__u_comp_ch2__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch2_th;
            vlSelf->__PVT__u_comp_ch1__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch1_th;
            vlSelf->__PVT__u_comp_ch0__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch0_th;
            vlSelf->__PVT__u_in_stage__DOT__r_mode 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_in_mode;
            vlSelf->__PVT__u_in_stage__DOT__r_sel = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_in_sel;
            vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch3_mode;
            vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch2_mode;
            vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch1_mode;
            vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_ch0_mode;
            vlSelf->__PVT__u_prescaler__DOT__r_presc 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_presc;
        }
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_arm) {
            vlSelf->__PVT__u_in_stage__DOT__r_armed = 1U;
        } else if (vlSelf->__PVT__s_cnt_end) {
            vlSelf->__PVT__u_in_stage__DOT__r_armed = 0U;
        }
    } else {
        vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync = 0U;
        __Vdly__u_comp_ch3__DOT__r_value = 0U;
        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch2__DOT__r_value = 0U;
        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch1__DOT__r_value = 0U;
        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch0__DOT__r_value = 0U;
        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
        vlSelf->__PVT__u_counter__DOT__r_end = 0U;
        vlSelf->__PVT__u_counter__DOT__r_start = 0U;
        vlSelf->__PVT__u_comp_ch3__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch2__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch1__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch0__DOT__r_comp = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_mode = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_sel = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_event = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_oldval = 0U;
        vlSelf->__PVT__u_counter__DOT__r_event = 0U;
        vlSelf->__PVT__u_counter__DOT__r_direction = 0U;
        vlSelf->__PVT__u_counter__DOT__r_counter = 0U;
        vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_counter__DOT__r_sawtooth = 1U;
        vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_armed = 0U;
        __Vdly__u_prescaler__DOT__r_counter = 0U;
        vlSelf->__PVT__s_presc_evt = 0U;
        vlSelf->__PVT__u_prescaler__DOT__r_presc = 0U;
    }
    vlSelf->__PVT__u_counter__DOT__r_pending_update 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) 
           && (IData)(vlSelf->__PVT__u_counter__DOT__s_pending_update));
    vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch3__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch3__DOT__r_value = __Vdly__u_comp_ch3__DOT__r_value;
    vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch2__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch2__DOT__r_value = __Vdly__u_comp_ch2__DOT__r_value;
    vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch1__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch1__DOT__r_value = __Vdly__u_comp_ch1__DOT__r_value;
    vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch0__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch0__DOT__r_value = __Vdly__u_comp_ch0__DOT__r_value;
    vlSelf->pwm_o = (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value) 
                      << 3U) | (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value) 
                                 << 2U) | (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value))));
    vlSelf->__PVT__u_prescaler__DOT__r_counter = __Vdly__u_prescaler__DOT__r_counter;
    vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk = (IData)(
                                                            (2U 
                                                             == 
                                                             (6U 
                                                              & (IData)(vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync))));
    __Vtableidx7 = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_update) 
                     << 4U) | (((IData)(vlSelf->__PVT__s_cnt_evt) 
                                << 3U) | (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_stop) 
                                           << 2U) | 
                                          (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_start) 
                                            << 1U) 
                                           | (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q)))));
    if ((1U & Vsoc_cpu_tb_w2__ConstPool__TABLE_hfb72848a_0
         [__Vtableidx7])) {
        vlSelf->__PVT__u_controller__DOT__r_active 
            = Vsoc_cpu_tb_w2__ConstPool__TABLE_h22c22758_0
            [__Vtableidx7];
    }
    vlSelf->__PVT__s_cnt_evt = ((IData)(vlSelf->__PVT__u_controller__DOT__r_active) 
                                & (IData)(vlSelf->__PVT__u_counter__DOT__r_event));
    vlSelf->__PVT__u_comp_ch0__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch1__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch2__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch3__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_counter__DOT__s_is_update = ((IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)
                                                   ? 
                                                  ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                                   == (IData)(vlSelf->__PVT__u_counter__DOT__r_end))
                                                   : 
                                                  ((IData)(vlSelf->__PVT__u_counter__DOT__r_direction) 
                                                   & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                                      == 
                                                      ((IData)(vlSelf->__PVT__u_counter__DOT__r_start) 
                                                       - (IData)(1U)))));
    vlSelf->__PVT__s_cnt_end = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                & (IData)(vlSelf->__PVT__u_counter__DOT__s_is_update));
    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
        vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
    } else {
        vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch0__DOT__s_match;
        vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch1__DOT__s_match;
        vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch2__DOT__s_match;
        vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch3__DOT__s_match;
    }
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__0(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__0\n"); );
    // Init
    CData/*0:0*/ __PVT__u_in_stage__DOT__s_rise;
    __PVT__u_in_stage__DOT__s_rise = 0;
    CData/*0:0*/ __PVT__u_in_stage__DOT__s_fall;
    __PVT__u_in_stage__DOT__s_fall = 0;
    SData/*8:0*/ __Vtableidx8;
    __Vtableidx8 = 0;
    // Body
    vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 0U;
    if ((0U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal));
    }
    if ((1U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 1U)));
    }
    if ((2U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 2U)));
    }
    if ((3U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 3U)));
    }
    if ((4U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 4U)));
    }
    if ((5U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 5U)));
    }
    if ((6U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 6U)));
    }
    if ((7U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 7U)));
    }
    if ((8U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 8U)));
    }
    if ((9U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 9U)));
    }
    if ((0xaU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xaU)));
    }
    if ((0xbU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xbU)));
    }
    if ((0xcU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xcU)));
    }
    if ((0xdU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xdU)));
    }
    if ((0xeU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xeU)));
    }
    if ((0xfU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xfU)));
    }
    if ((0x10U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x10U)));
    }
    if ((0x11U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x11U)));
    }
    if ((0x12U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x12U)));
    }
    if ((0x13U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x13U)));
    }
    if ((0x14U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x14U)));
    }
    if ((0x15U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x15U)));
    }
    if ((0x16U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x16U)));
    }
    if ((0x17U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x17U)));
    }
    if ((0x18U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x18U)));
    }
    if ((0x19U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x19U)));
    }
    if ((0x1aU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1aU)));
    }
    if ((0x1bU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1bU)));
    }
    if ((0x1cU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1cU)));
    }
    if ((0x1dU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1dU)));
    }
    if ((0x1eU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1eU)));
    }
    if ((0x1fU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1fU)));
    }
    if ((0x20U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x20U)));
    }
    if ((0x21U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x21U)));
    }
    if ((0x22U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x22U)));
    }
    if ((0x23U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x23U)));
    }
    if ((0x24U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x24U)));
    }
    if ((0x25U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x25U)));
    }
    if ((0x26U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x26U)));
    }
    if ((0x27U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x27U)));
    }
    if ((0x28U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x28U)));
    }
    if ((0x29U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x29U)));
    }
    if ((0x2aU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2aU)));
    }
    if ((0x2bU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2bU)));
    }
    if ((0x2cU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2cU)));
    }
    if ((0x2dU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2dU)));
    }
    if ((0x2eU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2eU)));
    }
    if ((0x2fU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2fU)));
    }
    __PVT__u_in_stage__DOT__s_rise = ((~ (IData)(vlSelf->__PVT__u_in_stage__DOT__r_oldval)) 
                                      & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig));
    __PVT__u_in_stage__DOT__s_fall = ((~ (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig)) 
                                      & (IData)(vlSelf->__PVT__u_in_stage__DOT__r_oldval));
    __Vtableidx8 = (((IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig) 
                     << 8U) | ((((IData)(__PVT__u_in_stage__DOT__s_rise) 
                                 | (IData)(__PVT__u_in_stage__DOT__s_fall)) 
                                << 7U) | (((IData)(__PVT__u_in_stage__DOT__s_rise) 
                                           << 6U) | 
                                          (((IData)(vlSelf->__PVT__u_in_stage__DOT__r_event) 
                                            << 5U) 
                                           | (((IData)(__PVT__u_in_stage__DOT__s_fall) 
                                               << 4U) 
                                              | (((IData)(vlSelf->__PVT__u_in_stage__DOT__r_armed) 
                                                  << 3U) 
                                                 | (IData)(vlSelf->__PVT__u_in_stage__DOT__r_mode)))))));
    vlSelf->__PVT__u_in_stage__DOT__s_int_evnt = Vsoc_cpu_tb_w2__ConstPool__TABLE_h49e93408_0
        [__Vtableidx8];
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__1(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2__1\n"); );
    // Init
    CData/*5:0*/ __Vtableidx9;
    __Vtableidx9 = 0;
    // Body
    vlSelf->__PVT__s_ctrl_update_all = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_start) 
                                         & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                        || (IData)(vlSelf->__PVT__s_cnt_evt));
    vlSelf->__PVT__s_ctrl_rst = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_start) 
                                  & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                 || (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_rst));
    __Vtableidx9 = (((IData)(vlSelf->__PVT__s_ctrl_rst) 
                     << 5U) | (((IData)(vlSelf->__PVT__s_presc_evt) 
                                << 4U) | (((IData)(vlSelf->__PVT__u_counter__DOT__s_is_update) 
                                           << 3U) | 
                                          (((IData)(vlSelf->__PVT__u_controller__DOT__r_active) 
                                            << 2U) 
                                           | (((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_start) 
                                                 & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                                || (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_update)) 
                                               << 1U) 
                                              | (IData)(vlSelf->__PVT__u_counter__DOT__r_pending_update))))));
    vlSelf->__PVT__u_counter__DOT__s_pending_update 
        = Vsoc_cpu_tb_w2__ConstPool__TABLE_h38c04461_0
        [__Vtableidx9];
    vlSelf->__PVT__u_counter__DOT__s_do_update = Vsoc_cpu_tb_w2__ConstPool__TABLE_hc6e5c112_0
        [__Vtableidx9];
    vlSelf->__PVT__u_counter__DOT__s_start = vlSelf->__PVT__u_counter__DOT__r_start;
    vlSelf->__PVT__u_counter__DOT__s_sawtooth = vlSelf->__PVT__u_counter__DOT__r_sawtooth;
    vlSelf->__PVT__u_counter__DOT__s_end = vlSelf->__PVT__u_counter__DOT__r_end;
    vlSelf->__PVT__u_counter__DOT__s_direction = vlSelf->__PVT__u_counter__DOT__r_direction;
    vlSelf->__PVT__u_counter__DOT__s_counter = vlSelf->__PVT__u_counter__DOT__r_counter;
    if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
        vlSelf->__PVT__u_counter__DOT__s_start = (0xffffU 
                                                  & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_th);
        vlSelf->__PVT__u_counter__DOT__s_sawtooth = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_saw;
        vlSelf->__PVT__u_counter__DOT__s_end = (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_th 
                                                >> 0x10U);
        vlSelf->__PVT__u_counter__DOT__s_direction = 0U;
        vlSelf->__PVT__u_counter__DOT__s_counter = 
            (0xffffU & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer2_th);
    } else if (((IData)(vlSelf->__PVT__s_presc_evt) 
                & (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) {
        if (((~ (IData)(vlSelf->__PVT__u_counter__DOT__r_direction)) 
             & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                == (IData)(vlSelf->__PVT__u_counter__DOT__r_end)))) {
            vlSelf->__PVT__u_counter__DOT__s_direction 
                = (1U & (~ (IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)));
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)
                               ? (IData)(vlSelf->__PVT__u_counter__DOT__r_start)
                               : ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                  - (IData)(1U))));
        } else if (((IData)(vlSelf->__PVT__u_counter__DOT__r_direction) 
                    & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                       == (IData)(vlSelf->__PVT__u_counter__DOT__r_start)))) {
            vlSelf->__PVT__u_counter__DOT__s_direction = 0U;
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(1U) + (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
        } else {
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(vlSelf->__PVT__u_counter__DOT__r_direction)
                               ? ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                  - (IData)(1U)) : 
                              ((IData)(1U) + (IData)(vlSelf->__PVT__u_counter__DOT__r_counter))));
        }
    }
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__0(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__0\n"); );
    // Init
    CData/*4:0*/ __Vtableidx10;
    __Vtableidx10 = 0;
    CData/*7:0*/ __Vdly__u_prescaler__DOT__r_counter;
    __Vdly__u_prescaler__DOT__r_counter = 0;
    CData/*0:0*/ __Vdly__u_comp_ch0__DOT__r_value;
    __Vdly__u_comp_ch0__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch0__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch1__DOT__r_value;
    __Vdly__u_comp_ch1__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch1__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch2__DOT__r_value;
    __Vdly__u_comp_ch2__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch2__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0;
    CData/*0:0*/ __Vdly__u_comp_ch3__DOT__r_value;
    __Vdly__u_comp_ch3__DOT__r_value = 0;
    CData/*0:0*/ __Vdly__u_comp_ch3__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0;
    // Body
    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event;
    __Vdly__u_comp_ch3__DOT__r_value = vlSelf->__PVT__u_comp_ch3__DOT__r_value;
    __Vdly__u_comp_ch2__DOT__r_value = vlSelf->__PVT__u_comp_ch2__DOT__r_value;
    __Vdly__u_comp_ch1__DOT__r_value = vlSelf->__PVT__u_comp_ch1__DOT__r_value;
    __Vdly__u_comp_ch0__DOT__r_value = vlSelf->__PVT__u_comp_ch0__DOT__r_value;
    __Vdly__u_prescaler__DOT__r_counter = vlSelf->__PVT__u_prescaler__DOT__r_counter;
    if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) {
        vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync 
            = ((6U & ((IData)(vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync) 
                      << 1U)) | (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__lfclk));
        if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
            vlSelf->__PVT__u_counter__DOT__r_end = vlSelf->__PVT__u_counter__DOT__s_end;
            vlSelf->__PVT__u_counter__DOT__r_start 
                = vlSelf->__PVT__u_counter__DOT__s_start;
        }
        if (vlSelf->__PVT__s_ctrl_rst) {
            __Vdly__u_comp_ch3__DOT__r_value = 0U;
            __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch2__DOT__r_value = 0U;
            __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch1__DOT__r_value = 0U;
            __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
            __Vdly__u_comp_ch0__DOT__r_value = 0U;
            __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
        } else if (((IData)(vlSelf->__PVT__s_cnt_evt) 
                    & (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) {
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch3__DOT__r_value;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                            __Vdly__u_comp_ch3__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                            __Vdly__u_comp_ch3__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                        __Vdly__u_comp_ch3__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 1U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch3__DOT__s_match) {
                        __Vdly__u_comp_ch3__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch3__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value)));
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch3__DOT__r_value = 0U;
                    __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch3__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch2__DOT__r_value;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                            __Vdly__u_comp_ch2__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                            __Vdly__u_comp_ch2__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                        __Vdly__u_comp_ch2__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 1U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch2__DOT__s_match) {
                        __Vdly__u_comp_ch2__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch2__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value)));
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch2__DOT__r_value = 0U;
                    __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch2__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch1__DOT__r_value;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                            __Vdly__u_comp_ch1__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                            __Vdly__u_comp_ch1__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                        __Vdly__u_comp_ch1__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 1U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch1__DOT__s_match) {
                        __Vdly__u_comp_ch1__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch1__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value)));
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch1__DOT__r_value = 0U;
                    __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch1__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value));
            }
            if ((4U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if ((2U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = vlSelf->__PVT__u_comp_ch0__DOT__r_value;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                            __Vdly__u_comp_ch0__DOT__r_value = 0U;
                        } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    }
                } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                        if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                            __Vdly__u_comp_ch0__DOT__r_value 
                                = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                        } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                            __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        }
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                    } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                                & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                    }
                } else {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = ((~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match)) 
                           & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value));
                }
            } else if ((2U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = (1U & ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match)
                                  ? (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value))
                                  : (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                } else if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                        __Vdly__u_comp_ch0__DOT__r_value = 1U;
                    } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 1U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                }
            } else if ((1U & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op))) {
                if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
                    if (vlSelf->__PVT__u_comp_ch0__DOT__s_match) {
                        __Vdly__u_comp_ch0__DOT__r_value 
                            = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                    } else if (vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event) {
                        __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    }
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event)))) {
                    __Vdly__u_comp_ch0__DOT__r_value 
                        = (1U & (~ (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value)));
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 1U;
                } else if (((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                            & (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event))) {
                    __Vdly__u_comp_ch0__DOT__r_value = 0U;
                    __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
                }
            } else {
                __Vdly__u_comp_ch0__DOT__r_value = 
                    ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__s_match) 
                     | (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value));
            }
        }
        if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
            vlSelf->__PVT__u_counter__DOT__r_sawtooth 
                = vlSelf->__PVT__u_counter__DOT__s_sawtooth;
        }
        if (vlSelf->__PVT__u_in_stage__DOT__r_armed) {
            vlSelf->__PVT__u_in_stage__DOT__r_event 
                = vlSelf->__PVT__u_in_stage__DOT__s_int_evnt;
        } else if (vlSelf->__PVT__s_cnt_end) {
            vlSelf->__PVT__u_in_stage__DOT__r_event = 0U;
        }
        if (vlSelf->__PVT__u_controller__DOT__r_active) {
            if ((1U & ((~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_in_clk)) 
                       | ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_in_clk) 
                          & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk))))) {
                vlSelf->__PVT__u_in_stage__DOT__r_oldval 
                    = vlSelf->__PVT__u_in_stage__DOT__s_int_sig;
            }
            vlSelf->__PVT__u_counter__DOT__r_event 
                = vlSelf->__PVT__s_presc_evt;
        }
        if (((IData)(vlSelf->__PVT__u_counter__DOT__s_do_update) 
             | ((IData)(vlSelf->__PVT__s_presc_evt) 
                & (IData)(vlSelf->__PVT__u_controller__DOT__r_active)))) {
            vlSelf->__PVT__u_counter__DOT__r_direction 
                = vlSelf->__PVT__u_counter__DOT__s_direction;
            vlSelf->__PVT__u_counter__DOT__r_counter 
                = vlSelf->__PVT__u_counter__DOT__s_counter;
        }
        if (vlSelf->__PVT__s_ctrl_rst) {
            __Vdly__u_prescaler__DOT__r_counter = 0U;
            vlSelf->__PVT__s_presc_evt = 0U;
        } else if (vlSelf->__PVT__u_controller__DOT__r_active) {
            if (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_in_clk)
                  ? ((IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_evnt) 
                     & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk))
                  : (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_evnt))) {
                if ((0U == (IData)(vlSelf->__PVT__u_prescaler__DOT__r_presc))) {
                    vlSelf->__PVT__s_presc_evt = 1U;
                } else if (((IData)(vlSelf->__PVT__u_prescaler__DOT__r_counter) 
                            == (IData)(vlSelf->__PVT__u_prescaler__DOT__r_presc))) {
                    vlSelf->__PVT__s_presc_evt = 1U;
                    __Vdly__u_prescaler__DOT__r_counter = 0U;
                } else {
                    __Vdly__u_prescaler__DOT__r_counter 
                        = (0xffU & ((IData)(1U) + (IData)(vlSelf->__PVT__u_prescaler__DOT__r_counter)));
                    vlSelf->__PVT__s_presc_evt = 0U;
                }
            } else {
                vlSelf->__PVT__s_presc_evt = 0U;
            }
        } else {
            __Vdly__u_prescaler__DOT__r_counter = 0U;
            vlSelf->__PVT__s_presc_evt = 0U;
        }
        if (vlSelf->__PVT__s_ctrl_update_all) {
            vlSelf->__PVT__u_comp_ch3__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch3_th;
            vlSelf->__PVT__u_comp_ch2__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch2_th;
            vlSelf->__PVT__u_comp_ch1__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch1_th;
            vlSelf->__PVT__u_comp_ch0__DOT__r_comp 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch0_th;
            vlSelf->__PVT__u_in_stage__DOT__r_mode 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_in_mode;
            vlSelf->__PVT__u_in_stage__DOT__r_sel = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_in_sel;
            vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch3_mode;
            vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch2_mode;
            vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch1_mode;
            vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_ch0_mode;
            vlSelf->__PVT__u_prescaler__DOT__r_presc 
                = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_presc;
        }
        if (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_arm) {
            vlSelf->__PVT__u_in_stage__DOT__r_armed = 1U;
        } else if (vlSelf->__PVT__s_cnt_end) {
            vlSelf->__PVT__u_in_stage__DOT__r_armed = 0U;
        }
    } else {
        vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync = 0U;
        __Vdly__u_comp_ch3__DOT__r_value = 0U;
        __Vdly__u_comp_ch3__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch2__DOT__r_value = 0U;
        __Vdly__u_comp_ch2__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch1__DOT__r_value = 0U;
        __Vdly__u_comp_ch1__DOT__r_is_2nd_event = 0U;
        __Vdly__u_comp_ch0__DOT__r_value = 0U;
        __Vdly__u_comp_ch0__DOT__r_is_2nd_event = 0U;
        vlSelf->__PVT__u_counter__DOT__r_end = 0U;
        vlSelf->__PVT__u_counter__DOT__r_start = 0U;
        vlSelf->__PVT__u_comp_ch3__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch2__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch1__DOT__r_comp = 0U;
        vlSelf->__PVT__u_comp_ch0__DOT__r_comp = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_mode = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_sel = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_event = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_oldval = 0U;
        vlSelf->__PVT__u_counter__DOT__r_event = 0U;
        vlSelf->__PVT__u_counter__DOT__r_direction = 0U;
        vlSelf->__PVT__u_counter__DOT__r_counter = 0U;
        vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_counter__DOT__r_sawtooth = 1U;
        vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op = 0U;
        vlSelf->__PVT__u_in_stage__DOT__r_armed = 0U;
        __Vdly__u_prescaler__DOT__r_counter = 0U;
        vlSelf->__PVT__s_presc_evt = 0U;
        vlSelf->__PVT__u_prescaler__DOT__r_presc = 0U;
    }
    vlSelf->__PVT__u_counter__DOT__r_pending_update 
        = ((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q) 
           && (IData)(vlSelf->__PVT__u_counter__DOT__s_pending_update));
    vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch3__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch3__DOT__r_value = __Vdly__u_comp_ch3__DOT__r_value;
    vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch2__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch2__DOT__r_value = __Vdly__u_comp_ch2__DOT__r_value;
    vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch1__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch1__DOT__r_value = __Vdly__u_comp_ch1__DOT__r_value;
    vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event 
        = __Vdly__u_comp_ch0__DOT__r_is_2nd_event;
    vlSelf->__PVT__u_comp_ch0__DOT__r_value = __Vdly__u_comp_ch0__DOT__r_value;
    vlSelf->pwm_o = (((IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_value) 
                      << 3U) | (((IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_value) 
                                 << 2U) | (((IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_value) 
                                            << 1U) 
                                           | (IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_value))));
    vlSelf->__PVT__u_prescaler__DOT__r_counter = __Vdly__u_prescaler__DOT__r_counter;
    vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk = (IData)(
                                                            (2U 
                                                             == 
                                                             (6U 
                                                              & (IData)(vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync))));
    __Vtableidx10 = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_update) 
                      << 4U) | (((IData)(vlSelf->__PVT__s_cnt_evt) 
                                 << 3U) | (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_stop) 
                                            << 2U) 
                                           | (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_start) 
                                               << 1U) 
                                              | (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_main_ResetCatchAndSync_2_1__DOT__reset_n_catch_reg__DOT__reg_0_q)))));
    if ((1U & Vsoc_cpu_tb_w2__ConstPool__TABLE_hfb72848a_0
         [__Vtableidx10])) {
        vlSelf->__PVT__u_controller__DOT__r_active 
            = Vsoc_cpu_tb_w2__ConstPool__TABLE_h22c22758_0
            [__Vtableidx10];
    }
    vlSelf->__PVT__s_cnt_evt = ((IData)(vlSelf->__PVT__u_controller__DOT__r_active) 
                                & (IData)(vlSelf->__PVT__u_counter__DOT__r_event));
    vlSelf->__PVT__u_comp_ch0__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch0__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch1__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch1__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch2__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch2__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_comp_ch3__DOT__s_match = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                               & ((IData)(vlSelf->__PVT__u_comp_ch3__DOT__r_comp) 
                                                  == (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
    vlSelf->__PVT__u_counter__DOT__s_is_update = ((IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)
                                                   ? 
                                                  ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                                   == (IData)(vlSelf->__PVT__u_counter__DOT__r_end))
                                                   : 
                                                  ((IData)(vlSelf->__PVT__u_counter__DOT__r_direction) 
                                                   & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                                      == 
                                                      ((IData)(vlSelf->__PVT__u_counter__DOT__r_start) 
                                                       - (IData)(1U)))));
    vlSelf->__PVT__s_cnt_end = ((IData)(vlSelf->__PVT__s_cnt_evt) 
                                & (IData)(vlSelf->__PVT__u_counter__DOT__s_is_update));
    if (vlSelf->__PVT__u_counter__DOT__r_sawtooth) {
        vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
        vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event 
            = vlSelf->__PVT__s_cnt_end;
    } else {
        vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch0__DOT__s_match;
        vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch1__DOT__s_match;
        vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch2__DOT__s_match;
        vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event 
            = vlSelf->__PVT__u_comp_ch3__DOT__s_match;
    }
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__0(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__0\n"); );
    // Init
    CData/*0:0*/ __PVT__u_in_stage__DOT__s_rise;
    __PVT__u_in_stage__DOT__s_rise = 0;
    CData/*0:0*/ __PVT__u_in_stage__DOT__s_fall;
    __PVT__u_in_stage__DOT__s_fall = 0;
    SData/*8:0*/ __Vtableidx11;
    __Vtableidx11 = 0;
    // Body
    vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 0U;
    if ((0U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal));
    }
    if ((1U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 1U)));
    }
    if ((2U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 2U)));
    }
    if ((3U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 3U)));
    }
    if ((4U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 4U)));
    }
    if ((5U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 5U)));
    }
    if ((6U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 6U)));
    }
    if ((7U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 7U)));
    }
    if ((8U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 8U)));
    }
    if ((9U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 9U)));
    }
    if ((0xaU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xaU)));
    }
    if ((0xbU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xbU)));
    }
    if ((0xcU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xcU)));
    }
    if ((0xdU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xdU)));
    }
    if ((0xeU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xeU)));
    }
    if ((0xfU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0xfU)));
    }
    if ((0x10U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x10U)));
    }
    if ((0x11U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x11U)));
    }
    if ((0x12U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x12U)));
    }
    if ((0x13U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x13U)));
    }
    if ((0x14U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x14U)));
    }
    if ((0x15U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x15U)));
    }
    if ((0x16U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x16U)));
    }
    if ((0x17U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x17U)));
    }
    if ((0x18U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x18U)));
    }
    if ((0x19U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x19U)));
    }
    if ((0x1aU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1aU)));
    }
    if ((0x1bU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1bU)));
    }
    if ((0x1cU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1cU)));
    }
    if ((0x1dU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1dU)));
    }
    if ((0x1eU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1eU)));
    }
    if ((0x1fU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x1fU)));
    }
    if ((0x20U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x20U)));
    }
    if ((0x21U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x21U)));
    }
    if ((0x22U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x22U)));
    }
    if ((0x23U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x23U)));
    }
    if ((0x24U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x24U)));
    }
    if ((0x25U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x25U)));
    }
    if ((0x26U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x26U)));
    }
    if ((0x27U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x27U)));
    }
    if ((0x28U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x28U)));
    }
    if ((0x29U == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x29U)));
    }
    if ((0x2aU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2aU)));
    }
    if ((0x2bU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2bU)));
    }
    if ((0x2cU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2cU)));
    }
    if ((0x2dU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2dU)));
    }
    if ((0x2eU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2eU)));
    }
    if ((0x2fU == (IData)(vlSelf->__PVT__u_in_stage__DOT__r_sel))) {
        vlSelf->__PVT__u_in_stage__DOT__s_int_sig = 
            (1U & (IData)((vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__s_timer0_signal 
                           >> 0x2fU)));
    }
    __PVT__u_in_stage__DOT__s_rise = ((~ (IData)(vlSelf->__PVT__u_in_stage__DOT__r_oldval)) 
                                      & (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig));
    __PVT__u_in_stage__DOT__s_fall = ((~ (IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig)) 
                                      & (IData)(vlSelf->__PVT__u_in_stage__DOT__r_oldval));
    __Vtableidx11 = (((IData)(vlSelf->__PVT__u_in_stage__DOT__s_int_sig) 
                      << 8U) | ((((IData)(__PVT__u_in_stage__DOT__s_rise) 
                                  | (IData)(__PVT__u_in_stage__DOT__s_fall)) 
                                 << 7U) | (((IData)(__PVT__u_in_stage__DOT__s_rise) 
                                            << 6U) 
                                           | (((IData)(vlSelf->__PVT__u_in_stage__DOT__r_event) 
                                               << 5U) 
                                              | (((IData)(__PVT__u_in_stage__DOT__s_fall) 
                                                  << 4U) 
                                                 | (((IData)(vlSelf->__PVT__u_in_stage__DOT__r_armed) 
                                                     << 3U) 
                                                    | (IData)(vlSelf->__PVT__u_in_stage__DOT__r_mode)))))));
    vlSelf->__PVT__u_in_stage__DOT__s_int_evnt = Vsoc_cpu_tb_w2__ConstPool__TABLE_h49e93408_0
        [__Vtableidx11];
}

VL_INLINE_OPT void Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__1(Vsoc_cpu_tb_w2_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_w2_timer_module__NB30___nba_comb__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3__1\n"); );
    // Init
    CData/*5:0*/ __Vtableidx12;
    __Vtableidx12 = 0;
    // Body
    vlSelf->__PVT__s_ctrl_update_all = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_start) 
                                         & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                        || (IData)(vlSelf->__PVT__s_cnt_evt));
    vlSelf->__PVT__s_ctrl_rst = (((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_start) 
                                  & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                 || (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_rst));
    __Vtableidx12 = (((IData)(vlSelf->__PVT__s_ctrl_rst) 
                      << 5U) | (((IData)(vlSelf->__PVT__s_presc_evt) 
                                 << 4U) | (((IData)(vlSelf->__PVT__u_counter__DOT__s_is_update) 
                                            << 3U) 
                                           | (((IData)(vlSelf->__PVT__u_controller__DOT__r_active) 
                                               << 2U) 
                                              | (((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_start) 
                                                    & (~ (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) 
                                                   || (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_update)) 
                                                  << 1U) 
                                                 | (IData)(vlSelf->__PVT__u_counter__DOT__r_pending_update))))));
    vlSelf->__PVT__u_counter__DOT__s_pending_update 
        = Vsoc_cpu_tb_w2__ConstPool__TABLE_h38c04461_0
        [__Vtableidx12];
    vlSelf->__PVT__u_counter__DOT__s_do_update = Vsoc_cpu_tb_w2__ConstPool__TABLE_hc6e5c112_0
        [__Vtableidx12];
    vlSelf->__PVT__u_counter__DOT__s_start = vlSelf->__PVT__u_counter__DOT__r_start;
    vlSelf->__PVT__u_counter__DOT__s_sawtooth = vlSelf->__PVT__u_counter__DOT__r_sawtooth;
    vlSelf->__PVT__u_counter__DOT__s_end = vlSelf->__PVT__u_counter__DOT__r_end;
    vlSelf->__PVT__u_counter__DOT__s_direction = vlSelf->__PVT__u_counter__DOT__r_direction;
    vlSelf->__PVT__u_counter__DOT__s_counter = vlSelf->__PVT__u_counter__DOT__r_counter;
    if (vlSelf->__PVT__u_counter__DOT__s_do_update) {
        vlSelf->__PVT__u_counter__DOT__s_start = (0xffffU 
                                                  & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_th);
        vlSelf->__PVT__u_counter__DOT__s_sawtooth = vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_saw;
        vlSelf->__PVT__u_counter__DOT__s_end = (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_th 
                                                >> 0x10U);
        vlSelf->__PVT__u_counter__DOT__s_direction = 0U;
        vlSelf->__PVT__u_counter__DOT__s_counter = 
            (0xffffU & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_apb_if__DOT__r_timer3_th);
    } else if (((IData)(vlSelf->__PVT__s_presc_evt) 
                & (IData)(vlSelf->__PVT__u_controller__DOT__r_active))) {
        if (((~ (IData)(vlSelf->__PVT__u_counter__DOT__r_direction)) 
             & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                == (IData)(vlSelf->__PVT__u_counter__DOT__r_end)))) {
            vlSelf->__PVT__u_counter__DOT__s_direction 
                = (1U & (~ (IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)));
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(vlSelf->__PVT__u_counter__DOT__r_sawtooth)
                               ? (IData)(vlSelf->__PVT__u_counter__DOT__r_start)
                               : ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                  - (IData)(1U))));
        } else if (((IData)(vlSelf->__PVT__u_counter__DOT__r_direction) 
                    & ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                       == (IData)(vlSelf->__PVT__u_counter__DOT__r_start)))) {
            vlSelf->__PVT__u_counter__DOT__s_direction = 0U;
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(1U) + (IData)(vlSelf->__PVT__u_counter__DOT__r_counter)));
        } else {
            vlSelf->__PVT__u_counter__DOT__s_counter 
                = (0xffffU & ((IData)(vlSelf->__PVT__u_counter__DOT__r_direction)
                               ? ((IData)(vlSelf->__PVT__u_counter__DOT__r_counter) 
                                  - (IData)(1U)) : 
                              ((IData)(1U) + (IData)(vlSelf->__PVT__u_counter__DOT__r_counter))));
        }
    }
}

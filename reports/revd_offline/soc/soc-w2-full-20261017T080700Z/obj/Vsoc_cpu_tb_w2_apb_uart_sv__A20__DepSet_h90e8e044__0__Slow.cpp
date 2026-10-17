// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb_w2.h for the primary calling header

#include "Vsoc_cpu_tb_w2__pch.h"
#include "Vsoc_cpu_tb_w2__Syms.h"
#include "Vsoc_cpu_tb_w2_apb_uart_sv__A20.h"

extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_cpu_tb_w2__ConstPool__TABLE_hee473934_0;
extern const VlUnpacked<CData/*2:0*/, 4> Vsoc_cpu_tb_w2__ConstPool__TABLE_h1c95f80a_0;

VL_ATTR_COLD void Vsoc_cpu_tb_w2_apb_uart_sv__A20___stl_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0__0(Vsoc_cpu_tb_w2_apb_uart_sv__A20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_w2_apb_uart_sv__A20___stl_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0__0\n"); );
    // Init
    CData/*3:0*/ __PVT__clr_int;
    __PVT__clr_int = 0;
    CData/*2:0*/ __PVT__uart_rx_i__DOT__s_target_bits;
    __PVT__uart_rx_i__DOT__s_target_bits = 0;
    CData/*0:0*/ __PVT__uart_rx_i__DOT__s_rx_fall;
    __PVT__uart_rx_i__DOT__s_rx_fall = 0;
    CData/*2:0*/ __PVT__uart_tx_i__DOT__s_target_bits;
    __PVT__uart_tx_i__DOT__s_target_bits = 0;
    CData/*1:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*1:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*6:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    // Body
    vlSelf->__PVT__rx_valid = 0U;
    vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 0U;
    vlSelf->__PVT__tx_valid = (0U != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements));
    vlSelf->__PVT__uart_tx_fifo_i__DOT__full = (0x10U 
                                                == (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements));
    vlSelf->__PVT__fifo_rx_valid = (0U != (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements));
    vlSelf->__PVT__uart_rx_fifo_i__DOT__full = (0x10U 
                                                == (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements));
    vlSelf->__PVT__uart_rx_i__DOT__sampleData = 0U;
    vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next 
        = vlSelf->__PVT__uart_rx_i__DOT__parity_bit;
    vlSelf->__PVT__uart_rx_i__DOT__reg_data_next = vlSelf->__PVT__uart_rx_i__DOT__reg_data;
    vlSelf->__PVT__uart_rx_i__DOT__set_error = 0U;
    __Vtableidx3 = (((IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements) 
                     << 2U) | (IData)(vlSelf->__PVT__trigger_level_q));
    vlSelf->__PVT__uart_interrupt_i__DOT__trigger_level_reached 
        = Vsoc_cpu_tb_w2__ConstPool__TABLE_hee473934_0
        [__Vtableidx3];
    __Vtableidx2 = (3U & (vlSelf->__PVT__regs_q[0U] 
                          >> 0x18U));
    __PVT__uart_tx_i__DOT__s_target_bits = Vsoc_cpu_tb_w2__ConstPool__TABLE_h1c95f80a_0
        [__Vtableidx2];
    __PVT__uart_rx_i__DOT__s_rx_fall = (IData)((4U 
                                                == 
                                                (6U 
                                                 & (IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync))));
    __Vtableidx1 = (3U & (vlSelf->__PVT__regs_q[0U] 
                          >> 0x18U));
    __PVT__uart_rx_i__DOT__s_target_bits = Vsoc_cpu_tb_w2__ConstPool__TABLE_h1c95f80a_0
        [__Vtableidx1];
    vlSelf->__PVT__tx_ready = 0U;
    vlSelf->__PVT__fifo_rx_data = vlSelf->__PVT__uart_rx_fifo_i__DOT__buffer
        [vlSelf->__PVT__uart_rx_fifo_i__DOT__pointer_out];
    vlSelf->__PVT__fifo_tx_valid = 0U;
    vlSelf->__PVT__tx_fifo_clr_n = 0U;
    vlSelf->__PVT__rx_fifo_clr_n = 0U;
    vlSelf->__PVT__fifo_rx_ready = 0U;
    vlSelf->__PVT__trigger_level_n = vlSelf->__PVT__trigger_level_q;
    __PVT__clr_int = 0U;
    vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count_next 
        = vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count;
    if ((1U & (~ ((IData)(vlSelf->__PVT__uart_tx_i__DOT__CS) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_tx_i__DOT__CS) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS)))) {
                vlSelf->__PVT__tx_ready = 1U;
            }
        }
        if ((2U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS)))) {
                if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
                    vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count_next 
                        = (((IData)(vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count) 
                            == (IData)(__PVT__uart_tx_i__DOT__s_target_bits))
                            ? 0U : (7U & ((IData)(1U) 
                                          + (IData)(vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count))));
                }
            }
        }
    }
    vlSelf->__PVT__uart_tx_i__DOT__NS = vlSelf->__PVT__uart_tx_i__DOT__CS;
    if ((4U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_tx_i__DOT__CS) 
                      >> 1U)))) {
            vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 1U;
        }
        if ((2U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            vlSelf->__PVT__uart_tx_i__DOT__NS = 0U;
        } else if ((1U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
                vlSelf->__PVT__uart_tx_i__DOT__NS = 0U;
            }
        } else if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_tx_i__DOT__NS = ((0x4000000U 
                                                  & vlSelf->__PVT__regs_q[0U])
                                                  ? 5U
                                                  : 0U);
        }
    } else if ((2U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
        vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 1U;
        if ((1U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
                vlSelf->__PVT__uart_tx_i__DOT__NS = 4U;
            }
        } else if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
            if (((IData)(vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count) 
                 == (IData)(__PVT__uart_tx_i__DOT__s_target_bits))) {
                vlSelf->__PVT__uart_tx_i__DOT__NS = 
                    ((0x8000000U & vlSelf->__PVT__regs_q[0U])
                      ? 3U : 4U);
            }
        }
    } else if ((1U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
        vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 1U;
        if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_tx_i__DOT__NS = 2U;
        }
    } else if ((0U != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements))) {
        vlSelf->__PVT__uart_tx_i__DOT__NS = 1U;
    }
    vlSelf->__PVT__uart_rx_i__DOT__start_bit = 0U;
    vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 0U;
    vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count_next 
        = vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count;
    if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__CS) 
                  >> 2U)))) {
        if ((2U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
                vlSelf->__PVT__rx_valid = 1U;
            }
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS)))) {
                if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
                    vlSelf->__PVT__uart_rx_i__DOT__sampleData = 1U;
                    vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count_next 
                        = (((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count) 
                            == (IData)(__PVT__uart_rx_i__DOT__s_target_bits))
                            ? 0U : (7U & ((IData)(1U) 
                                          + (IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count))));
                }
                vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next 
                    = ((IData)(vlSelf->__PVT__uart_rx_i__DOT__parity_bit) 
                       ^ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                          >> 2U));
                vlSelf->__PVT__uart_rx_i__DOT__reg_data_next 
                    = ((0x2000000U & vlSelf->__PVT__regs_q[0U])
                        ? ((0x1000000U & vlSelf->__PVT__regs_q[0U])
                            ? ((0x80U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                         << 5U)) | 
                               (0x7fU & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                         >> 1U))) : 
                           ((0x40U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                      << 4U)) | (0x3fU 
                                                 & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                                    >> 1U))))
                        : ((0x1000000U & vlSelf->__PVT__regs_q[0U])
                            ? ((0x20U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                         << 3U)) | 
                               (0x1fU & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                         >> 1U))) : 
                           ((0x10U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                      << 2U)) | (0xfU 
                                                 & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                                    >> 1U)))));
            }
        } else if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next = 0U;
        }
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__CS) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
                vlSelf->__PVT__uart_rx_i__DOT__start_bit = 1U;
            } else if (__PVT__uart_rx_i__DOT__s_rx_fall) {
                vlSelf->__PVT__uart_rx_i__DOT__start_bit = 1U;
            }
        }
    }
    vlSelf->__PVT__uart_rx_i__DOT__NS = vlSelf->__PVT__uart_rx_i__DOT__CS;
    if ((4U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__CS) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS)))) {
                if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
                    if ((0x20000000U & vlSelf->__PVT__regs_q[0U])) {
                        if ((0x10000000U & vlSelf->__PVT__regs_q[0U])) {
                            if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                          >> 2U)))) {
                                vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                            }
                        } else if ((4U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync))) {
                            vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                        }
                    } else if ((0x10000000U & vlSelf->__PVT__regs_q[0U])) {
                        if (((1U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                    >> 2U)) != (IData)(vlSelf->__PVT__uart_rx_i__DOT__parity_bit))) {
                            vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                        }
                    } else if (((1U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                       >> 2U)) != (1U 
                                                   & (~ (IData)(vlSelf->__PVT__uart_rx_i__DOT__parity_bit))))) {
                        vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                    }
                }
            }
            vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        }
        if ((2U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            vlSelf->__PVT__uart_rx_i__DOT__NS = 0U;
        } else if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
                vlSelf->__PVT__uart_rx_i__DOT__NS = 0U;
            }
        } else if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_rx_i__DOT__NS = 5U;
        }
    } else if ((2U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
        vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            if ((0x10U != (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements))) {
                vlSelf->__PVT__uart_rx_i__DOT__NS = 
                    ((0x8000000U & vlSelf->__PVT__regs_q[0U])
                      ? 4U : 5U);
            }
        } else if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
            if (((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count) 
                 == (IData)(__PVT__uart_rx_i__DOT__s_target_bits))) {
                vlSelf->__PVT__uart_rx_i__DOT__NS = 3U;
            }
        }
    } else if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
        vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_rx_i__DOT__NS = 2U;
        }
    } else if (__PVT__uart_rx_i__DOT__s_rx_fall) {
        vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        vlSelf->__PVT__uart_rx_i__DOT__NS = 1U;
    }
    vlSelf->PRDATA = 0U;
    if ((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_valid) 
          & (IData)(vlSymsp->TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb.__PVT__apb_enable_dfflr__DOT__qout_r)) 
         & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_read))) {
        if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                      >> 4U)))) {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                          >> 3U)))) {
                if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                              >> 2U)))) {
                    if ((1U & (~ (vlSelf->__PVT__regs_q[0U] 
                                  >> 0x1fU)))) {
                        vlSelf->__PVT__fifo_rx_ready = 1U;
                    }
                }
            }
        }
        if ((0x10U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr)) {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                          >> 3U)))) {
                if ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr)) {
                    __PVT__clr_int = 0xcU;
                }
            }
            vlSelf->PRDATA = ((8U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr)
                               ? 0U : ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr)
                                        ? (0xffU & 
                                           (vlSelf->__PVT__regs_q[1U] 
                                            >> 8U))
                                        : 0U));
        } else if ((8U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr)) {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                          >> 2U)))) {
                __PVT__clr_int = 4U;
            }
            vlSelf->PRDATA = ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr)
                               ? (vlSelf->__PVT__regs_q[0U] 
                                  >> 0x18U) : (0xc0U 
                                               | (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__iir_q)));
        } else {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                          >> 2U)))) {
                if ((1U & (~ (vlSelf->__PVT__regs_q[0U] 
                              >> 0x1fU)))) {
                    __PVT__clr_int = 8U;
                }
            }
            vlSelf->PRDATA = ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr)
                               ? ((vlSelf->__PVT__regs_q[0U] 
                                   >> 0x1fU) ? (0xffU 
                                                & (vlSelf->__PVT__regs_q[2U] 
                                                   >> 8U))
                                   : (0xffU & (vlSelf->__PVT__regs_q[0U] 
                                               >> 8U)))
                               : ((vlSelf->__PVT__regs_q[0U] 
                                   >> 0x1fU) ? (0xffU 
                                                & vlSelf->__PVT__regs_q[2U])
                                   : (0xffU & (IData)(vlSelf->__PVT__fifo_rx_data))));
        }
    }
    vlSelf->__PVT__regs_n[0U] = vlSelf->__PVT__regs_q[0U];
    vlSelf->__PVT__regs_n[1U] = vlSelf->__PVT__regs_q[1U];
    vlSelf->__PVT__regs_n[2U] = vlSelf->__PVT__regs_q[2U];
    vlSelf->__PVT__regs_n[1U] = ((0xfffffeffU & vlSelf->__PVT__regs_n[1U]) 
                                 | ((0U != (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements)) 
                                    << 8U));
    vlSelf->__PVT__regs_n[1U] = ((0xfffffbffU & vlSelf->__PVT__regs_n[1U]) 
                                 | (0x400U & ((IData)(vlSelf->__PVT__fifo_rx_data) 
                                              << 2U)));
    vlSelf->__PVT__regs_n[1U] = ((0xffffdfffU & vlSelf->__PVT__regs_n[1U]) 
                                 | (0x2000U & ((~ (IData)(
                                                          (0U 
                                                           != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements)))) 
                                               << 0xdU)));
    vlSelf->__PVT__regs_n[1U] = ((0xffffbfffU & vlSelf->__PVT__regs_n[1U]) 
                                 | (((IData)(vlSelf->__PVT__tx_ready) 
                                     & (~ (IData)((0U 
                                                   != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements))))) 
                                    << 0xeU));
    if ((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_valid) 
          & (IData)(vlSymsp->TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb.__PVT__apb_enable_dfflr__DOT__qout_r)) 
         & (~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_read)))) {
        if ((0U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                          >> 2U)))) {
            if ((1U & (~ (vlSelf->__PVT__regs_q[0U] 
                          >> 0x1fU)))) {
                vlSelf->__PVT__fifo_tx_valid = 1U;
                vlSelf->__PVT__fifo_tx_data = (0xffU 
                                               & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_wdata);
            }
            if ((vlSelf->__PVT__regs_q[0U] >> 0x1fU)) {
                vlSelf->__PVT__regs_n[2U] = ((0xff00U 
                                              & vlSelf->__PVT__regs_n[2U]) 
                                             | (0xffU 
                                                & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_wdata));
            }
        } else if ((1U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                                 >> 2U)))) {
            if ((vlSelf->__PVT__regs_q[0U] >> 0x1fU)) {
                vlSelf->__PVT__regs_n[2U] = ((0xffU 
                                              & vlSelf->__PVT__regs_n[2U]) 
                                             | (0xff00U 
                                                & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_wdata 
                                                   << 8U)));
            } else {
                vlSelf->__PVT__regs_n[0U] = ((0xffff00ffU 
                                              & vlSelf->__PVT__regs_n[0U]) 
                                             | (0xff00U 
                                                & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_wdata 
                                                   << 8U)));
            }
        } else if ((3U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                                 >> 2U)))) {
            vlSelf->__PVT__regs_n[0U] = ((0xffffffU 
                                          & vlSelf->__PVT__regs_n[0U]) 
                                         | (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_wdata 
                                            << 0x18U));
        }
        if ((0U != (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                          >> 2U)))) {
            if ((1U != (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                              >> 2U)))) {
                if ((3U != (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                                  >> 2U)))) {
                    if ((2U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_addr 
                                      >> 2U)))) {
                        vlSelf->__PVT__tx_fifo_clr_n 
                            = (1U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_wdata 
                                     >> 2U));
                        vlSelf->__PVT__rx_fifo_clr_n 
                            = (1U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_wdata 
                                     >> 1U));
                        vlSelf->__PVT__trigger_level_n 
                            = (3U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart0_apb_icb_cmd_wdata 
                                     >> 6U));
                    }
                }
            }
        }
    }
    vlSelf->__PVT__uart_interrupt_i__DOT__iir_n = (
                                                   (0U 
                                                    == (IData)(__PVT__clr_int))
                                                    ? 
                                                   ((0x400U 
                                                     & (vlSelf->__PVT__regs_q[0U] 
                                                        & vlSelf->__PVT__regs_n[1U]))
                                                     ? 0xcU
                                                     : 
                                                    (((vlSelf->__PVT__regs_q[0U] 
                                                       >> 8U) 
                                                      & (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__trigger_level_reached))
                                                      ? 8U
                                                      : 
                                                     (((vlSelf->__PVT__regs_q[0U] 
                                                        >> 9U) 
                                                       & (0U 
                                                          == (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements)))
                                                       ? 4U
                                                       : (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__iir_q))))
                                                    : 
                                                   ((~ (IData)(__PVT__clr_int)) 
                                                    & (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__iir_q)));
}

VL_ATTR_COLD void Vsoc_cpu_tb_w2_apb_uart_sv__A20___stl_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1__0(Vsoc_cpu_tb_w2_apb_uart_sv__A20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_w2_apb_uart_sv__A20___stl_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1__0\n"); );
    // Init
    CData/*3:0*/ __PVT__clr_int;
    __PVT__clr_int = 0;
    CData/*2:0*/ __PVT__uart_rx_i__DOT__s_target_bits;
    __PVT__uart_rx_i__DOT__s_target_bits = 0;
    CData/*0:0*/ __PVT__uart_rx_i__DOT__s_rx_fall;
    __PVT__uart_rx_i__DOT__s_rx_fall = 0;
    CData/*2:0*/ __PVT__uart_tx_i__DOT__s_target_bits;
    __PVT__uart_tx_i__DOT__s_target_bits = 0;
    CData/*1:0*/ __Vtableidx4;
    __Vtableidx4 = 0;
    CData/*1:0*/ __Vtableidx5;
    __Vtableidx5 = 0;
    CData/*6:0*/ __Vtableidx6;
    __Vtableidx6 = 0;
    // Body
    vlSelf->__PVT__rx_valid = 0U;
    vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 0U;
    vlSelf->__PVT__tx_valid = (0U != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements));
    vlSelf->__PVT__uart_tx_fifo_i__DOT__full = (0x10U 
                                                == (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements));
    vlSelf->__PVT__fifo_rx_valid = (0U != (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements));
    vlSelf->__PVT__uart_rx_fifo_i__DOT__full = (0x10U 
                                                == (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements));
    vlSelf->__PVT__uart_rx_i__DOT__sampleData = 0U;
    vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next 
        = vlSelf->__PVT__uart_rx_i__DOT__parity_bit;
    vlSelf->__PVT__uart_rx_i__DOT__reg_data_next = vlSelf->__PVT__uart_rx_i__DOT__reg_data;
    vlSelf->__PVT__uart_rx_i__DOT__set_error = 0U;
    __Vtableidx6 = (((IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements) 
                     << 2U) | (IData)(vlSelf->__PVT__trigger_level_q));
    vlSelf->__PVT__uart_interrupt_i__DOT__trigger_level_reached 
        = Vsoc_cpu_tb_w2__ConstPool__TABLE_hee473934_0
        [__Vtableidx6];
    __Vtableidx5 = (3U & (vlSelf->__PVT__regs_q[0U] 
                          >> 0x18U));
    __PVT__uart_tx_i__DOT__s_target_bits = Vsoc_cpu_tb_w2__ConstPool__TABLE_h1c95f80a_0
        [__Vtableidx5];
    __PVT__uart_rx_i__DOT__s_rx_fall = (IData)((4U 
                                                == 
                                                (6U 
                                                 & (IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync))));
    __Vtableidx4 = (3U & (vlSelf->__PVT__regs_q[0U] 
                          >> 0x18U));
    __PVT__uart_rx_i__DOT__s_target_bits = Vsoc_cpu_tb_w2__ConstPool__TABLE_h1c95f80a_0
        [__Vtableidx4];
    vlSelf->__PVT__tx_ready = 0U;
    vlSelf->__PVT__fifo_rx_data = vlSelf->__PVT__uart_rx_fifo_i__DOT__buffer
        [vlSelf->__PVT__uart_rx_fifo_i__DOT__pointer_out];
    vlSelf->__PVT__fifo_tx_valid = 0U;
    vlSelf->__PVT__tx_fifo_clr_n = 0U;
    vlSelf->__PVT__rx_fifo_clr_n = 0U;
    vlSelf->__PVT__fifo_rx_ready = 0U;
    vlSelf->__PVT__trigger_level_n = vlSelf->__PVT__trigger_level_q;
    __PVT__clr_int = 0U;
    vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count_next 
        = vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count;
    if ((1U & (~ ((IData)(vlSelf->__PVT__uart_tx_i__DOT__CS) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_tx_i__DOT__CS) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS)))) {
                vlSelf->__PVT__tx_ready = 1U;
            }
        }
        if ((2U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS)))) {
                if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
                    vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count_next 
                        = (((IData)(vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count) 
                            == (IData)(__PVT__uart_tx_i__DOT__s_target_bits))
                            ? 0U : (7U & ((IData)(1U) 
                                          + (IData)(vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count))));
                }
            }
        }
    }
    vlSelf->__PVT__uart_tx_i__DOT__NS = vlSelf->__PVT__uart_tx_i__DOT__CS;
    if ((4U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_tx_i__DOT__CS) 
                      >> 1U)))) {
            vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 1U;
        }
        if ((2U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            vlSelf->__PVT__uart_tx_i__DOT__NS = 0U;
        } else if ((1U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
                vlSelf->__PVT__uart_tx_i__DOT__NS = 0U;
            }
        } else if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_tx_i__DOT__NS = ((0x4000000U 
                                                  & vlSelf->__PVT__regs_q[0U])
                                                  ? 5U
                                                  : 0U);
        }
    } else if ((2U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
        vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 1U;
        if ((1U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
                vlSelf->__PVT__uart_tx_i__DOT__NS = 4U;
            }
        } else if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
            if (((IData)(vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count) 
                 == (IData)(__PVT__uart_tx_i__DOT__s_target_bits))) {
                vlSelf->__PVT__uart_tx_i__DOT__NS = 
                    ((0x8000000U & vlSelf->__PVT__regs_q[0U])
                      ? 3U : 4U);
            }
        }
    } else if ((1U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
        vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 1U;
        if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_tx_i__DOT__NS = 2U;
        }
    } else if ((0U != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements))) {
        vlSelf->__PVT__uart_tx_i__DOT__NS = 1U;
    }
    vlSelf->__PVT__uart_rx_i__DOT__start_bit = 0U;
    vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 0U;
    vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count_next 
        = vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count;
    if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__CS) 
                  >> 2U)))) {
        if ((2U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
                vlSelf->__PVT__rx_valid = 1U;
            }
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS)))) {
                if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
                    vlSelf->__PVT__uart_rx_i__DOT__sampleData = 1U;
                    vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count_next 
                        = (((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count) 
                            == (IData)(__PVT__uart_rx_i__DOT__s_target_bits))
                            ? 0U : (7U & ((IData)(1U) 
                                          + (IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count))));
                }
                vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next 
                    = ((IData)(vlSelf->__PVT__uart_rx_i__DOT__parity_bit) 
                       ^ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                          >> 2U));
                vlSelf->__PVT__uart_rx_i__DOT__reg_data_next 
                    = ((0x2000000U & vlSelf->__PVT__regs_q[0U])
                        ? ((0x1000000U & vlSelf->__PVT__regs_q[0U])
                            ? ((0x80U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                         << 5U)) | 
                               (0x7fU & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                         >> 1U))) : 
                           ((0x40U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                      << 4U)) | (0x3fU 
                                                 & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                                    >> 1U))))
                        : ((0x1000000U & vlSelf->__PVT__regs_q[0U])
                            ? ((0x20U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                         << 3U)) | 
                               (0x1fU & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                         >> 1U))) : 
                           ((0x10U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                      << 2U)) | (0xfU 
                                                 & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                                    >> 1U)))));
            }
        } else if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next = 0U;
        }
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__CS) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
                vlSelf->__PVT__uart_rx_i__DOT__start_bit = 1U;
            } else if (__PVT__uart_rx_i__DOT__s_rx_fall) {
                vlSelf->__PVT__uart_rx_i__DOT__start_bit = 1U;
            }
        }
    }
    vlSelf->__PVT__uart_rx_i__DOT__NS = vlSelf->__PVT__uart_rx_i__DOT__CS;
    if ((4U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__CS) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS)))) {
                if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
                    if ((0x20000000U & vlSelf->__PVT__regs_q[0U])) {
                        if ((0x10000000U & vlSelf->__PVT__regs_q[0U])) {
                            if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                          >> 2U)))) {
                                vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                            }
                        } else if ((4U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync))) {
                            vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                        }
                    } else if ((0x10000000U & vlSelf->__PVT__regs_q[0U])) {
                        if (((1U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                    >> 2U)) != (IData)(vlSelf->__PVT__uart_rx_i__DOT__parity_bit))) {
                            vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                        }
                    } else if (((1U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                       >> 2U)) != (1U 
                                                   & (~ (IData)(vlSelf->__PVT__uart_rx_i__DOT__parity_bit))))) {
                        vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                    }
                }
            }
            vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        }
        if ((2U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            vlSelf->__PVT__uart_rx_i__DOT__NS = 0U;
        } else if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
                vlSelf->__PVT__uart_rx_i__DOT__NS = 0U;
            }
        } else if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_rx_i__DOT__NS = 5U;
        }
    } else if ((2U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
        vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            if ((0x10U != (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements))) {
                vlSelf->__PVT__uart_rx_i__DOT__NS = 
                    ((0x8000000U & vlSelf->__PVT__regs_q[0U])
                      ? 4U : 5U);
            }
        } else if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
            if (((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count) 
                 == (IData)(__PVT__uart_rx_i__DOT__s_target_bits))) {
                vlSelf->__PVT__uart_rx_i__DOT__NS = 3U;
            }
        }
    } else if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
        vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_rx_i__DOT__NS = 2U;
        }
    } else if (__PVT__uart_rx_i__DOT__s_rx_fall) {
        vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        vlSelf->__PVT__uart_rx_i__DOT__NS = 1U;
    }
    vlSelf->PRDATA = 0U;
    if ((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_valid) 
          & (IData)(vlSymsp->TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb.__PVT__apb_enable_dfflr__DOT__qout_r)) 
         & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_read))) {
        if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                      >> 4U)))) {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                          >> 3U)))) {
                if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                              >> 2U)))) {
                    if ((1U & (~ (vlSelf->__PVT__regs_q[0U] 
                                  >> 0x1fU)))) {
                        vlSelf->__PVT__fifo_rx_ready = 1U;
                    }
                }
            }
        }
        if ((0x10U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr)) {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                          >> 3U)))) {
                if ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr)) {
                    __PVT__clr_int = 0xcU;
                }
            }
            vlSelf->PRDATA = ((8U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr)
                               ? 0U : ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr)
                                        ? (0xffU & 
                                           (vlSelf->__PVT__regs_q[1U] 
                                            >> 8U))
                                        : 0U));
        } else if ((8U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr)) {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                          >> 2U)))) {
                __PVT__clr_int = 4U;
            }
            vlSelf->PRDATA = ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr)
                               ? (vlSelf->__PVT__regs_q[0U] 
                                  >> 0x18U) : (0xc0U 
                                               | (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__iir_q)));
        } else {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                          >> 2U)))) {
                if ((1U & (~ (vlSelf->__PVT__regs_q[0U] 
                              >> 0x1fU)))) {
                    __PVT__clr_int = 8U;
                }
            }
            vlSelf->PRDATA = ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr)
                               ? ((vlSelf->__PVT__regs_q[0U] 
                                   >> 0x1fU) ? (0xffU 
                                                & (vlSelf->__PVT__regs_q[2U] 
                                                   >> 8U))
                                   : (0xffU & (vlSelf->__PVT__regs_q[0U] 
                                               >> 8U)))
                               : ((vlSelf->__PVT__regs_q[0U] 
                                   >> 0x1fU) ? (0xffU 
                                                & vlSelf->__PVT__regs_q[2U])
                                   : (0xffU & (IData)(vlSelf->__PVT__fifo_rx_data))));
        }
    }
    vlSelf->__PVT__regs_n[0U] = vlSelf->__PVT__regs_q[0U];
    vlSelf->__PVT__regs_n[1U] = vlSelf->__PVT__regs_q[1U];
    vlSelf->__PVT__regs_n[2U] = vlSelf->__PVT__regs_q[2U];
    vlSelf->__PVT__regs_n[1U] = ((0xfffffeffU & vlSelf->__PVT__regs_n[1U]) 
                                 | ((0U != (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements)) 
                                    << 8U));
    vlSelf->__PVT__regs_n[1U] = ((0xfffffbffU & vlSelf->__PVT__regs_n[1U]) 
                                 | (0x400U & ((IData)(vlSelf->__PVT__fifo_rx_data) 
                                              << 2U)));
    vlSelf->__PVT__regs_n[1U] = ((0xffffdfffU & vlSelf->__PVT__regs_n[1U]) 
                                 | (0x2000U & ((~ (IData)(
                                                          (0U 
                                                           != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements)))) 
                                               << 0xdU)));
    vlSelf->__PVT__regs_n[1U] = ((0xffffbfffU & vlSelf->__PVT__regs_n[1U]) 
                                 | (((IData)(vlSelf->__PVT__tx_ready) 
                                     & (~ (IData)((0U 
                                                   != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements))))) 
                                    << 0xeU));
    if ((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_valid) 
          & (IData)(vlSymsp->TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb.__PVT__apb_enable_dfflr__DOT__qout_r)) 
         & (~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_read)))) {
        if ((0U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                          >> 2U)))) {
            if ((1U & (~ (vlSelf->__PVT__regs_q[0U] 
                          >> 0x1fU)))) {
                vlSelf->__PVT__fifo_tx_valid = 1U;
                vlSelf->__PVT__fifo_tx_data = (0xffU 
                                               & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_wdata);
            }
            if ((vlSelf->__PVT__regs_q[0U] >> 0x1fU)) {
                vlSelf->__PVT__regs_n[2U] = ((0xff00U 
                                              & vlSelf->__PVT__regs_n[2U]) 
                                             | (0xffU 
                                                & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_wdata));
            }
        } else if ((1U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                                 >> 2U)))) {
            if ((vlSelf->__PVT__regs_q[0U] >> 0x1fU)) {
                vlSelf->__PVT__regs_n[2U] = ((0xffU 
                                              & vlSelf->__PVT__regs_n[2U]) 
                                             | (0xff00U 
                                                & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_wdata 
                                                   << 8U)));
            } else {
                vlSelf->__PVT__regs_n[0U] = ((0xffff00ffU 
                                              & vlSelf->__PVT__regs_n[0U]) 
                                             | (0xff00U 
                                                & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_wdata 
                                                   << 8U)));
            }
        } else if ((3U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                                 >> 2U)))) {
            vlSelf->__PVT__regs_n[0U] = ((0xffffffU 
                                          & vlSelf->__PVT__regs_n[0U]) 
                                         | (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_wdata 
                                            << 0x18U));
        }
        if ((0U != (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                          >> 2U)))) {
            if ((1U != (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                              >> 2U)))) {
                if ((3U != (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                                  >> 2U)))) {
                    if ((2U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_addr 
                                      >> 2U)))) {
                        vlSelf->__PVT__tx_fifo_clr_n 
                            = (1U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_wdata 
                                     >> 2U));
                        vlSelf->__PVT__rx_fifo_clr_n 
                            = (1U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_wdata 
                                     >> 1U));
                        vlSelf->__PVT__trigger_level_n 
                            = (3U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart1_apb_icb_cmd_wdata 
                                     >> 6U));
                    }
                }
            }
        }
    }
    vlSelf->__PVT__uart_interrupt_i__DOT__iir_n = (
                                                   (0U 
                                                    == (IData)(__PVT__clr_int))
                                                    ? 
                                                   ((0x400U 
                                                     & (vlSelf->__PVT__regs_q[0U] 
                                                        & vlSelf->__PVT__regs_n[1U]))
                                                     ? 0xcU
                                                     : 
                                                    (((vlSelf->__PVT__regs_q[0U] 
                                                       >> 8U) 
                                                      & (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__trigger_level_reached))
                                                      ? 8U
                                                      : 
                                                     (((vlSelf->__PVT__regs_q[0U] 
                                                        >> 9U) 
                                                       & (0U 
                                                          == (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements)))
                                                       ? 4U
                                                       : (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__iir_q))))
                                                    : 
                                                   ((~ (IData)(__PVT__clr_int)) 
                                                    & (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__iir_q)));
}

VL_ATTR_COLD void Vsoc_cpu_tb_w2_apb_uart_sv__A20___stl_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2__0(Vsoc_cpu_tb_w2_apb_uart_sv__A20* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb_w2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vsoc_cpu_tb_w2_apb_uart_sv__A20___stl_sequent__TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2__0\n"); );
    // Init
    CData/*3:0*/ __PVT__clr_int;
    __PVT__clr_int = 0;
    CData/*2:0*/ __PVT__uart_rx_i__DOT__s_target_bits;
    __PVT__uart_rx_i__DOT__s_target_bits = 0;
    CData/*0:0*/ __PVT__uart_rx_i__DOT__s_rx_fall;
    __PVT__uart_rx_i__DOT__s_rx_fall = 0;
    CData/*2:0*/ __PVT__uart_tx_i__DOT__s_target_bits;
    __PVT__uart_tx_i__DOT__s_target_bits = 0;
    CData/*1:0*/ __Vtableidx7;
    __Vtableidx7 = 0;
    CData/*1:0*/ __Vtableidx8;
    __Vtableidx8 = 0;
    CData/*6:0*/ __Vtableidx9;
    __Vtableidx9 = 0;
    // Body
    vlSelf->__PVT__rx_valid = 0U;
    vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 0U;
    vlSelf->__PVT__tx_valid = (0U != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements));
    vlSelf->__PVT__uart_tx_fifo_i__DOT__full = (0x10U 
                                                == (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements));
    vlSelf->__PVT__fifo_rx_valid = (0U != (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements));
    vlSelf->__PVT__uart_rx_fifo_i__DOT__full = (0x10U 
                                                == (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements));
    vlSelf->__PVT__uart_rx_i__DOT__sampleData = 0U;
    vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next 
        = vlSelf->__PVT__uart_rx_i__DOT__parity_bit;
    vlSelf->__PVT__uart_rx_i__DOT__reg_data_next = vlSelf->__PVT__uart_rx_i__DOT__reg_data;
    vlSelf->__PVT__uart_rx_i__DOT__set_error = 0U;
    __Vtableidx9 = (((IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements) 
                     << 2U) | (IData)(vlSelf->__PVT__trigger_level_q));
    vlSelf->__PVT__uart_interrupt_i__DOT__trigger_level_reached 
        = Vsoc_cpu_tb_w2__ConstPool__TABLE_hee473934_0
        [__Vtableidx9];
    __Vtableidx8 = (3U & (vlSelf->__PVT__regs_q[0U] 
                          >> 0x18U));
    __PVT__uart_tx_i__DOT__s_target_bits = Vsoc_cpu_tb_w2__ConstPool__TABLE_h1c95f80a_0
        [__Vtableidx8];
    __PVT__uart_rx_i__DOT__s_rx_fall = (IData)((4U 
                                                == 
                                                (6U 
                                                 & (IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync))));
    __Vtableidx7 = (3U & (vlSelf->__PVT__regs_q[0U] 
                          >> 0x18U));
    __PVT__uart_rx_i__DOT__s_target_bits = Vsoc_cpu_tb_w2__ConstPool__TABLE_h1c95f80a_0
        [__Vtableidx7];
    vlSelf->__PVT__tx_ready = 0U;
    vlSelf->__PVT__fifo_rx_data = vlSelf->__PVT__uart_rx_fifo_i__DOT__buffer
        [vlSelf->__PVT__uart_rx_fifo_i__DOT__pointer_out];
    vlSelf->__PVT__fifo_tx_valid = 0U;
    vlSelf->__PVT__tx_fifo_clr_n = 0U;
    vlSelf->__PVT__rx_fifo_clr_n = 0U;
    vlSelf->__PVT__fifo_rx_ready = 0U;
    vlSelf->__PVT__trigger_level_n = vlSelf->__PVT__trigger_level_q;
    __PVT__clr_int = 0U;
    vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count_next 
        = vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count;
    if ((1U & (~ ((IData)(vlSelf->__PVT__uart_tx_i__DOT__CS) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_tx_i__DOT__CS) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS)))) {
                vlSelf->__PVT__tx_ready = 1U;
            }
        }
        if ((2U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS)))) {
                if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
                    vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count_next 
                        = (((IData)(vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count) 
                            == (IData)(__PVT__uart_tx_i__DOT__s_target_bits))
                            ? 0U : (7U & ((IData)(1U) 
                                          + (IData)(vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count))));
                }
            }
        }
    }
    vlSelf->__PVT__uart_tx_i__DOT__NS = vlSelf->__PVT__uart_tx_i__DOT__CS;
    if ((4U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_tx_i__DOT__CS) 
                      >> 1U)))) {
            vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 1U;
        }
        if ((2U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            vlSelf->__PVT__uart_tx_i__DOT__NS = 0U;
        } else if ((1U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
                vlSelf->__PVT__uart_tx_i__DOT__NS = 0U;
            }
        } else if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_tx_i__DOT__NS = ((0x4000000U 
                                                  & vlSelf->__PVT__regs_q[0U])
                                                  ? 5U
                                                  : 0U);
        }
    } else if ((2U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
        vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 1U;
        if ((1U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
            if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
                vlSelf->__PVT__uart_tx_i__DOT__NS = 4U;
            }
        } else if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
            if (((IData)(vlSelf->__PVT__uart_tx_i__DOT__reg_bit_count) 
                 == (IData)(__PVT__uart_tx_i__DOT__s_target_bits))) {
                vlSelf->__PVT__uart_tx_i__DOT__NS = 
                    ((0x8000000U & vlSelf->__PVT__regs_q[0U])
                      ? 3U : 4U);
            }
        }
    } else if ((1U & (IData)(vlSelf->__PVT__uart_tx_i__DOT__CS))) {
        vlSelf->__PVT__uart_tx_i__DOT__baudgen_en = 1U;
        if (vlSelf->__PVT__uart_tx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_tx_i__DOT__NS = 2U;
        }
    } else if ((0U != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements))) {
        vlSelf->__PVT__uart_tx_i__DOT__NS = 1U;
    }
    vlSelf->__PVT__uart_rx_i__DOT__start_bit = 0U;
    vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 0U;
    vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count_next 
        = vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count;
    if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__CS) 
                  >> 2U)))) {
        if ((2U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
                vlSelf->__PVT__rx_valid = 1U;
            }
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS)))) {
                if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
                    vlSelf->__PVT__uart_rx_i__DOT__sampleData = 1U;
                    vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count_next 
                        = (((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count) 
                            == (IData)(__PVT__uart_rx_i__DOT__s_target_bits))
                            ? 0U : (7U & ((IData)(1U) 
                                          + (IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count))));
                }
                vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next 
                    = ((IData)(vlSelf->__PVT__uart_rx_i__DOT__parity_bit) 
                       ^ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                          >> 2U));
                vlSelf->__PVT__uart_rx_i__DOT__reg_data_next 
                    = ((0x2000000U & vlSelf->__PVT__regs_q[0U])
                        ? ((0x1000000U & vlSelf->__PVT__regs_q[0U])
                            ? ((0x80U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                         << 5U)) | 
                               (0x7fU & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                         >> 1U))) : 
                           ((0x40U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                      << 4U)) | (0x3fU 
                                                 & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                                    >> 1U))))
                        : ((0x1000000U & vlSelf->__PVT__regs_q[0U])
                            ? ((0x20U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                         << 3U)) | 
                               (0x1fU & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                         >> 1U))) : 
                           ((0x10U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                      << 2U)) | (0xfU 
                                                 & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_data) 
                                                    >> 1U)))));
            }
        } else if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            vlSelf->__PVT__uart_rx_i__DOT__parity_bit_next = 0U;
        }
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__CS) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
                vlSelf->__PVT__uart_rx_i__DOT__start_bit = 1U;
            } else if (__PVT__uart_rx_i__DOT__s_rx_fall) {
                vlSelf->__PVT__uart_rx_i__DOT__start_bit = 1U;
            }
        }
    }
    vlSelf->__PVT__uart_rx_i__DOT__NS = vlSelf->__PVT__uart_rx_i__DOT__CS;
    if ((4U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
        if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__CS) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS)))) {
                if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
                    if ((0x20000000U & vlSelf->__PVT__regs_q[0U])) {
                        if ((0x10000000U & vlSelf->__PVT__regs_q[0U])) {
                            if ((1U & (~ ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                          >> 2U)))) {
                                vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                            }
                        } else if ((4U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync))) {
                            vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                        }
                    } else if ((0x10000000U & vlSelf->__PVT__regs_q[0U])) {
                        if (((1U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                    >> 2U)) != (IData)(vlSelf->__PVT__uart_rx_i__DOT__parity_bit))) {
                            vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                        }
                    } else if (((1U & ((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_rx_sync) 
                                       >> 2U)) != (1U 
                                                   & (~ (IData)(vlSelf->__PVT__uart_rx_i__DOT__parity_bit))))) {
                        vlSelf->__PVT__uart_rx_i__DOT__set_error = 1U;
                    }
                }
            }
            vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        }
        if ((2U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            vlSelf->__PVT__uart_rx_i__DOT__NS = 0U;
        } else if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
                vlSelf->__PVT__uart_rx_i__DOT__NS = 0U;
            }
        } else if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_rx_i__DOT__NS = 5U;
        }
    } else if ((2U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
        vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
            if ((0x10U != (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements))) {
                vlSelf->__PVT__uart_rx_i__DOT__NS = 
                    ((0x8000000U & vlSelf->__PVT__regs_q[0U])
                      ? 4U : 5U);
            }
        } else if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
            if (((IData)(vlSelf->__PVT__uart_rx_i__DOT__reg_bit_count) 
                 == (IData)(__PVT__uart_rx_i__DOT__s_target_bits))) {
                vlSelf->__PVT__uart_rx_i__DOT__NS = 3U;
            }
        }
    } else if ((1U & (IData)(vlSelf->__PVT__uart_rx_i__DOT__CS))) {
        vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        if (vlSelf->__PVT__uart_rx_i__DOT__bit_done) {
            vlSelf->__PVT__uart_rx_i__DOT__NS = 2U;
        }
    } else if (__PVT__uart_rx_i__DOT__s_rx_fall) {
        vlSelf->__PVT__uart_rx_i__DOT__baudgen_en = 1U;
        vlSelf->__PVT__uart_rx_i__DOT__NS = 1U;
    }
    vlSelf->PRDATA = 0U;
    if ((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_valid) 
          & (IData)(vlSymsp->TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb.__PVT__apb_enable_dfflr__DOT__qout_r)) 
         & (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_read))) {
        if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                      >> 4U)))) {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                          >> 3U)))) {
                if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                              >> 2U)))) {
                    if ((1U & (~ (vlSelf->__PVT__regs_q[0U] 
                                  >> 0x1fU)))) {
                        vlSelf->__PVT__fifo_rx_ready = 1U;
                    }
                }
            }
        }
        if ((0x10U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr)) {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                          >> 3U)))) {
                if ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr)) {
                    __PVT__clr_int = 0xcU;
                }
            }
            vlSelf->PRDATA = ((8U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr)
                               ? 0U : ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr)
                                        ? (0xffU & 
                                           (vlSelf->__PVT__regs_q[1U] 
                                            >> 8U))
                                        : 0U));
        } else if ((8U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr)) {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                          >> 2U)))) {
                __PVT__clr_int = 4U;
            }
            vlSelf->PRDATA = ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr)
                               ? (vlSelf->__PVT__regs_q[0U] 
                                  >> 0x18U) : (0xc0U 
                                               | (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__iir_q)));
        } else {
            if ((1U & (~ (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                          >> 2U)))) {
                if ((1U & (~ (vlSelf->__PVT__regs_q[0U] 
                              >> 0x1fU)))) {
                    __PVT__clr_int = 8U;
                }
            }
            vlSelf->PRDATA = ((4U & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr)
                               ? ((vlSelf->__PVT__regs_q[0U] 
                                   >> 0x1fU) ? (0xffU 
                                                & (vlSelf->__PVT__regs_q[2U] 
                                                   >> 8U))
                                   : (0xffU & (vlSelf->__PVT__regs_q[0U] 
                                               >> 8U)))
                               : ((vlSelf->__PVT__regs_q[0U] 
                                   >> 0x1fU) ? (0xffU 
                                                & vlSelf->__PVT__regs_q[2U])
                                   : (0xffU & (IData)(vlSelf->__PVT__fifo_rx_data))));
        }
    }
    vlSelf->__PVT__regs_n[0U] = vlSelf->__PVT__regs_q[0U];
    vlSelf->__PVT__regs_n[1U] = vlSelf->__PVT__regs_q[1U];
    vlSelf->__PVT__regs_n[2U] = vlSelf->__PVT__regs_q[2U];
    vlSelf->__PVT__regs_n[1U] = ((0xfffffeffU & vlSelf->__PVT__regs_n[1U]) 
                                 | ((0U != (IData)(vlSelf->__PVT__uart_rx_fifo_i__DOT__elements)) 
                                    << 8U));
    vlSelf->__PVT__regs_n[1U] = ((0xfffffbffU & vlSelf->__PVT__regs_n[1U]) 
                                 | (0x400U & ((IData)(vlSelf->__PVT__fifo_rx_data) 
                                              << 2U)));
    vlSelf->__PVT__regs_n[1U] = ((0xffffdfffU & vlSelf->__PVT__regs_n[1U]) 
                                 | (0x2000U & ((~ (IData)(
                                                          (0U 
                                                           != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements)))) 
                                               << 0xdU)));
    vlSelf->__PVT__regs_n[1U] = ((0xffffbfffU & vlSelf->__PVT__regs_n[1U]) 
                                 | (((IData)(vlSelf->__PVT__tx_ready) 
                                     & (~ (IData)((0U 
                                                   != (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements))))) 
                                    << 0xeU));
    if ((((IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_valid) 
          & (IData)(vlSymsp->TOP__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb.__PVT__apb_enable_dfflr__DOT__qout_r)) 
         & (~ (IData)(vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_read)))) {
        if ((0U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                          >> 2U)))) {
            if ((1U & (~ (vlSelf->__PVT__regs_q[0U] 
                          >> 0x1fU)))) {
                vlSelf->__PVT__fifo_tx_valid = 1U;
                vlSelf->__PVT__fifo_tx_data = (0xffU 
                                               & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_wdata);
            }
            if ((vlSelf->__PVT__regs_q[0U] >> 0x1fU)) {
                vlSelf->__PVT__regs_n[2U] = ((0xff00U 
                                              & vlSelf->__PVT__regs_n[2U]) 
                                             | (0xffU 
                                                & vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_wdata));
            }
        } else if ((1U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                                 >> 2U)))) {
            if ((vlSelf->__PVT__regs_q[0U] >> 0x1fU)) {
                vlSelf->__PVT__regs_n[2U] = ((0xffU 
                                              & vlSelf->__PVT__regs_n[2U]) 
                                             | (0xff00U 
                                                & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_wdata 
                                                   << 8U)));
            } else {
                vlSelf->__PVT__regs_n[0U] = ((0xffff00ffU 
                                              & vlSelf->__PVT__regs_n[0U]) 
                                             | (0xff00U 
                                                & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_wdata 
                                                   << 8U)));
            }
        } else if ((3U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                                 >> 2U)))) {
            vlSelf->__PVT__regs_n[0U] = ((0xffffffU 
                                          & vlSelf->__PVT__regs_n[0U]) 
                                         | (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_wdata 
                                            << 0x18U));
        }
        if ((0U != (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                          >> 2U)))) {
            if ((1U != (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                              >> 2U)))) {
                if ((3U != (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                                  >> 2U)))) {
                    if ((2U == (7U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_addr 
                                      >> 2U)))) {
                        vlSelf->__PVT__tx_fifo_clr_n 
                            = (1U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_wdata 
                                     >> 2U));
                        vlSelf->__PVT__rx_fifo_clr_n 
                            = (1U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_wdata 
                                     >> 1U));
                        vlSelf->__PVT__trigger_level_n 
                            = (3U & (vlSymsp->TOP.soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__uart2_apb_icb_cmd_wdata 
                                     >> 6U));
                    }
                }
            }
        }
    }
    vlSelf->__PVT__uart_interrupt_i__DOT__iir_n = (
                                                   (0U 
                                                    == (IData)(__PVT__clr_int))
                                                    ? 
                                                   ((0x400U 
                                                     & (vlSelf->__PVT__regs_q[0U] 
                                                        & vlSelf->__PVT__regs_n[1U]))
                                                     ? 0xcU
                                                     : 
                                                    (((vlSelf->__PVT__regs_q[0U] 
                                                       >> 8U) 
                                                      & (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__trigger_level_reached))
                                                      ? 8U
                                                      : 
                                                     (((vlSelf->__PVT__regs_q[0U] 
                                                        >> 9U) 
                                                       & (0U 
                                                          == (IData)(vlSelf->__PVT__uart_tx_fifo_i__DOT__elements)))
                                                       ? 4U
                                                       : (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__iir_q))))
                                                    : 
                                                   ((~ (IData)(__PVT__clr_int)) 
                                                    & (IData)(vlSelf->__PVT__uart_interrupt_i__DOT__iir_q)));
}

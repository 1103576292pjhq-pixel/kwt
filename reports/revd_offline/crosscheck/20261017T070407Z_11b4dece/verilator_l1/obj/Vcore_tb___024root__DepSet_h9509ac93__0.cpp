// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore_tb.h for the primary calling header

#include "Vcore_tb__pch.h"
#include "Vcore_tb___024root.h"

VlCoroutine Vcore_tb___024root___eval_initial__TOP__Vtiming__0(Vcore_tb___024root* vlSelf);
VlCoroutine Vcore_tb___024root___eval_initial__TOP__Vtiming__1(Vcore_tb___024root* vlSelf);

void Vcore_tb___024root___eval_initial(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_initial\n"); );
    // Body
    Vcore_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vcore_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__core_tb__DOT__clk__0 
        = vlSelf->core_tb__DOT__clk;
    vlSelf->__Vtrigprevexpr_h78b21af8__0 = ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                            & (IData)(vlSelf->core_tb__DOT__out_last));
    vlSelf->__Vtrigprevexpr_h07439b72__0 = ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                            & (0x62feU 
                                               == vlSelf->core_tb__DOT__out_y_index));
    vlSelf->__Vtrigprevexpr___TOP__core_tb__DOT__fault__0 
        = vlSelf->core_tb__DOT__fault;
    vlSelf->__Vtrigprevexpr_h7be2f429__0 = ((IData)(vlSelf->core_tb__DOT__core_done) 
                                            | (IData)(vlSelf->core_tb__DOT__fault));
    vlSelf->__Vtrigprevexpr_hf506ef54__0 = ((4U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                            & (3ULL 
                                               < vlSelf->core_tb__DOT__dut__DOT__issue_count));
    vlSelf->__Vtrigprevexpr_hc537c130__0 = (7U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state));
    vlSelf->__Vtrigprevexpr_hc537d19d__0 = (8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state));
    vlSelf->__Vtrigprevexpr_hfc024315__0 = ((IData)(vlSelf->core_tb__DOT__dut__DOT__tag_valid) 
                                            & (0U == 
                                               vlSelf->core_tb__DOT__dut__DOT__tag_g
                                               [0U]));
    vlSelf->__Vtrigprevexpr_h88b84a6b__0 = ((IData)(vlSelf->core_tb__DOT__dut__DOT__product_valid) 
                                            & (1U < (IData)(vlSelf->core_tb__DOT__dut__DOT__product_k)));
    vlSelf->__Vtrigprevexpr_ha6663f55__0 = (8U != (IData)(vlSelf->core_tb__DOT__dut__DOT__state));
}

VL_INLINE_OPT VlCoroutine Vcore_tb___024root___eval_initial__TOP__Vtiming__1(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSelf->__VdlySched.delay(0x1388ULL, 
                                           nullptr, 
                                           "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                           4);
        vlSelf->core_tb__DOT__clk = (1U & (~ (IData)(vlSelf->core_tb__DOT__clk)));
    }
}

void Vcore_tb___024root___eval_act(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vcore_tb___024root___nba_sequent__TOP__1(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___nba_sequent__TOP__1\n"); );
    // Body
    vlSelf->core_tb__DOT__rng = ((vlSelf->core_tb__DOT__rng 
                                  << 1U) | (1U & VL_REDXOR_32(
                                                              (0x80200003U 
                                                               & vlSelf->core_tb__DOT__rng))));
    if (vlSelf->core_tb__DOT__rst_n) {
        if (VL_LTES_III(32, 0U, vlSelf->core_tb__DOT__boundary_ready)) {
            vlSelf->core_tb__DOT__out_ready = (0U != vlSelf->core_tb__DOT__boundary_ready);
        } else if ((0U != vlSelf->core_tb__DOT__force_ready)) {
            vlSelf->core_tb__DOT__out_ready = 1U;
        } else if ((0U != vlSelf->core_tb__DOT__sink_hold)) {
            vlSelf->core_tb__DOT__out_ready = 0U;
        } else if (VL_LTS_III(32, 0U, vlSelf->core_tb__DOT__stall)) {
            vlSelf->core_tb__DOT__stall = (vlSelf->core_tb__DOT__stall 
                                           - (IData)(1U));
            vlSelf->core_tb__DOT__out_ready = 0U;
        } else if (((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                    & (~ (IData)((0U != vlSelf->core_tb__DOT__retracted))))) {
            vlSelf->core_tb__DOT__out_ready = 0U;
            vlSelf->core_tb__DOT__stall = 7U;
            vlSelf->core_tb__DOT__retracted = 1U;
        } else if ((((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                     & (IData)(vlSelf->core_tb__DOT__out_last)) 
                    & (~ (IData)((0U != vlSelf->core_tb__DOT__last_stalled))))) {
            vlSelf->core_tb__DOT__out_ready = 0U;
            vlSelf->core_tb__DOT__stall = 0xbU;
            vlSelf->core_tb__DOT__last_stalled = 1U;
        } else {
            vlSelf->core_tb__DOT__out_ready = (0U != 
                                               (7U 
                                                & vlSelf->core_tb__DOT__rng));
        }
    } else {
        vlSelf->core_tb__DOT__out_ready = 0U;
        vlSelf->core_tb__DOT__stall = 0U;
        vlSelf->core_tb__DOT__last_stalled = 0U;
        vlSelf->core_tb__DOT__retracted = 0U;
    }
}

void Vcore_tb___024root___nba_sequent__TOP__0(Vcore_tb___024root* vlSelf);

void Vcore_tb___024root___eval_nba(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_nba\n"); );
    // Body
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vcore_tb___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vcore_tb___024root___nba_sequent__TOP__1(vlSelf);
    }
}

void Vcore_tb___024root___timing_resume(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___timing_resume\n"); );
    // Body
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h81e7d9aa__0.resume("@(negedge core_tb.clk)");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hec86538a__0.resume("@([changed] ((4'h8 == core_tb.dut.state) & core_tb.out_last))");
    }
    if ((8ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h5ef4d410__0.resume("@([changed] ((4'h8 == core_tb.dut.state) & (32'h62fe == core_tb.out_y_index)))");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h81e7d9f7__0.resume("@(posedge core_tb.clk)");
    }
    if ((0x10ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_he7308b1f__0.resume("@([changed] core_tb.fault)");
    }
    if ((0x20ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hebd52a47__0.resume("@([changed] (core_tb.core_done | core_tb.fault))");
    }
    if ((0x40ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h70b12766__0.resume("@([changed] ((4'h4 == core_tb.dut.state) & (64'h3 < core_tb.dut.issue_count)))");
    }
    if ((0x80ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h2100f542__0.resume("@([changed] (4'h7 == core_tb.dut.state))");
    }
    if ((0x100ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h2100062b__0.resume("@([changed] (4'h8 == core_tb.dut.state))");
    }
    if ((0x200ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h6bb67ba3__0.resume("@([changed] (core_tb.dut.tag_valid & (2'h0 == (core_tb.dut.tag_g[1'h0]))))");
    }
    if ((0x400ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hdc7f84fd__0.resume("@([changed] (core_tb.dut.product_valid & (6'h1 < core_tb.dut.product_k)))");
    }
    if ((0x800ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h02527763__0.resume("@([changed] (4'h8 != core_tb.dut.state))");
    }
    if ((0x1000ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vcore_tb___024root___timing_commit(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___timing_commit\n"); );
    // Body
    if ((! (1ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h81e7d9aa__0.commit("@(negedge core_tb.clk)");
    }
    if ((! (4ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hec86538a__0.commit("@([changed] ((4'h8 == core_tb.dut.state) & core_tb.out_last))");
    }
    if ((! (8ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h5ef4d410__0.commit("@([changed] ((4'h8 == core_tb.dut.state) & (32'h62fe == core_tb.out_y_index)))");
    }
    if ((! (2ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h81e7d9f7__0.commit("@(posedge core_tb.clk)");
    }
    if ((! (0x10ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_he7308b1f__0.commit("@([changed] core_tb.fault)");
    }
    if ((! (0x20ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hebd52a47__0.commit("@([changed] (core_tb.core_done | core_tb.fault))");
    }
    if ((! (0x40ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h70b12766__0.commit("@([changed] ((4'h4 == core_tb.dut.state) & (64'h3 < core_tb.dut.issue_count)))");
    }
    if ((! (0x80ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h2100f542__0.commit("@([changed] (4'h7 == core_tb.dut.state))");
    }
    if ((! (0x100ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h2100062b__0.commit("@([changed] (4'h8 == core_tb.dut.state))");
    }
    if ((! (0x200ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h6bb67ba3__0.commit("@([changed] (core_tb.dut.tag_valid & (2'h0 == (core_tb.dut.tag_g[1'h0]))))");
    }
    if ((! (0x400ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hdc7f84fd__0.commit("@([changed] (core_tb.dut.product_valid & (6'h1 < core_tb.dut.product_k)))");
    }
    if ((! (0x800ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h02527763__0.commit("@([changed] (4'h8 != core_tb.dut.state))");
    }
}

void Vcore_tb___024root___eval_triggers__act(Vcore_tb___024root* vlSelf);

bool Vcore_tb___024root___eval_phase__act(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<13> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vcore_tb___024root___eval_triggers__act(vlSelf);
    Vcore_tb___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vcore_tb___024root___timing_resume(vlSelf);
        Vcore_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vcore_tb___024root___eval_phase__nba(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vcore_tb___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore_tb___024root___dump_triggers__nba(Vcore_tb___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore_tb___024root___dump_triggers__act(Vcore_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vcore_tb___024root___eval(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vcore_tb___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vcore_tb___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 2, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vcore_tb___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vcore_tb___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vcore_tb___024root___eval_debug_assertions(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG

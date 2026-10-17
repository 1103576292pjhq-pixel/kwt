// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore_tb.h for the primary calling header

#include "Vcore_tb__pch.h"
#include "Vcore_tb___024root.h"

VL_ATTR_COLD void Vcore_tb___024root___eval_static__TOP(Vcore_tb___024root* vlSelf);

VL_ATTR_COLD void Vcore_tb___024root___eval_static(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_static\n"); );
    // Body
    Vcore_tb___024root___eval_static__TOP(vlSelf);
}

VL_ATTR_COLD void Vcore_tb___024root___eval_static__TOP(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_static__TOP\n"); );
    // Body
    vlSelf->core_tb__DOT__clk = 0U;
    vlSelf->core_tb__DOT__rst_n = 0U;
    vlSelf->core_tb__DOT__in_valid = 0U;
    vlSelf->core_tb__DOT__out_ready = 0U;
    vlSelf->core_tb__DOT__in_op = 0U;
    vlSelf->core_tb__DOT__in_layer_id = 0U;
    vlSelf->core_tb__DOT__in_task_id = 0U;
    vlSelf->core_tb__DOT__in_tile_id = 0U;
    vlSelf->core_tb__DOT__in_index = 0U;
    vlSelf->core_tb__DOT__in_data = 0ULL;
    vlSelf->core_tb__DOT__in_shift = 0U;
    vlSelf->core_tb__DOT__cycles = 0U;
    vlSelf->core_tb__DOT__accepted = 0U;
    vlSelf->core_tb__DOT__received = 0U;
    vlSelf->core_tb__DOT__dones = 0U;
    vlSelf->core_tb__DOT__cold_first = 0xffffffffU;
    vlSelf->core_tb__DOT__cold_start = 0xffffffffU;
    vlSelf->core_tb__DOT__cold_last = 0xffffffffU;
    vlSelf->core_tb__DOT__stall = 0U;
    vlSelf->core_tb__DOT__last_stalled = 0U;
    vlSelf->core_tb__DOT__retracted = 0U;
    vlSelf->core_tb__DOT__gap = 0U;
    vlSelf->core_tb__DOT__last_done_received = 0U;
    vlSelf->core_tb__DOT__expect_fault = 0U;
    vlSelf->core_tb__DOT__sink_hold = 0U;
    vlSelf->core_tb__DOT__force_ready = 0U;
    vlSelf->core_tb__DOT__boundary_ready = 0xffffffffU;
    vlSelf->core_tb__DOT__rng = 0xca05e123U;
    vlSelf->core_tb__DOT__blocked = 0U;
}

VL_ATTR_COLD void Vcore_tb___024root___eval_final(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore_tb___024root___dump_triggers__stl(Vcore_tb___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vcore_tb___024root___eval_phase__stl(Vcore_tb___024root* vlSelf);

VL_ATTR_COLD void Vcore_tb___024root___eval_settle(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vcore_tb___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 2, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vcore_tb___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore_tb___024root___dump_triggers__stl(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcore_tb___024root___stl_sequent__TOP__0(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___stl_sequent__TOP__0\n"); );
    // Init
    CData/*0:0*/ core_tb__DOT__dut__DOT__int16_ok;
    core_tb__DOT__dut__DOT__int16_ok = 0;
    CData/*0:0*/ core_tb__DOT__dut__DOT__x_write;
    core_tb__DOT__dut__DOT__x_write = 0;
    CData/*0:0*/ core_tb__DOT__dut__DOT__w_write;
    core_tb__DOT__dut__DOT__w_write = 0;
    QData/*47:0*/ core_tb__DOT__dut__DOT____Vcellinp__quant__in_bias;
    core_tb__DOT__dut__DOT____Vcellinp__quant__in_bias = 0;
    QData/*47:0*/ core_tb__DOT__dut__DOT____Vcellinp__quant__in_sum;
    core_tb__DOT__dut__DOT____Vcellinp__quant__in_sum = 0;
    IData/*31:0*/ core_tb__DOT__dut__DOT____VdfgTmp_hff5a03ba__0;
    core_tb__DOT__dut__DOT____VdfgTmp_hff5a03ba__0 = 0;
    CData/*0:0*/ core_tb__DOT__dut__DOT____VdfgTmp_h109f94df__0;
    core_tb__DOT__dut__DOT____VdfgTmp_h109f94df__0 = 0;
    CData/*0:0*/ core_tb__DOT__dut__DOT____VdfgTmp_hb9770c27__0;
    core_tb__DOT__dut__DOT____VdfgTmp_hb9770c27__0 = 0;
    QData/*48:0*/ core_tb__DOT__dut__DOT__quant__DOT__added;
    core_tb__DOT__dut__DOT__quant__DOT__added = 0;
    QData/*47:0*/ core_tb__DOT__dut__DOT__quant__DOT__magnitude;
    core_tb__DOT__dut__DOT__quant__DOT__magnitude = 0;
    QData/*47:0*/ core_tb__DOT__dut__DOT__quant__DOT__quotient;
    core_tb__DOT__dut__DOT__quant__DOT__quotient = 0;
    QData/*47:0*/ core_tb__DOT__dut__DOT__quant__DOT__remainder;
    core_tb__DOT__dut__DOT__quant__DOT__remainder = 0;
    QData/*47:0*/ core_tb__DOT__dut__DOT__quant__DOT__half;
    core_tb__DOT__dut__DOT__quant__DOT__half = 0;
    QData/*48:0*/ core_tb__DOT__dut__DOT__quant__DOT__rounded;
    core_tb__DOT__dut__DOT__quant__DOT__rounded = 0;
    // Body
    vlSelf->core_tb__DOT__out_valid = (8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state));
    vlSelf->core_tb__DOT__dut__DOT__row_mask = ((VL_GTS_III(32, 0x63U, 
                                                            ((IData)(3U) 
                                                             + vlSelf->core_tb__DOT__dut__DOT__row0)) 
                                                 << 3U) 
                                                | ((VL_GTS_III(32, 0x63U, 
                                                               ((IData)(2U) 
                                                                + vlSelf->core_tb__DOT__dut__DOT__row0)) 
                                                    << 2U) 
                                                   | ((VL_GTS_III(32, 0x63U, 
                                                                  ((IData)(1U) 
                                                                   + vlSelf->core_tb__DOT__dut__DOT__row0)) 
                                                       << 1U) 
                                                      | VL_GTS_III(32, 0x63U, vlSelf->core_tb__DOT__dut__DOT__row0))));
    vlSelf->core_tb__DOT__dut__DOT__effective_rows 
        = (VL_GTS_III(32, 4U, ((IData)(0x63U) - vlSelf->core_tb__DOT__dut__DOT__row0))
            ? ((IData)(0x63U) - vlSelf->core_tb__DOT__dut__DOT__row0)
            : 4U);
    vlSelf->core_tb__DOT__dut__DOT__returned = (1U 
                                                & ((IData)(vlSelf->core_tb__DOT__dut__DOT__tag_valid) 
                                                   >> 1U));
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__quant__in_valid 
        = ((~ (IData)(vlSelf->core_tb__DOT__fault)) 
           & (6U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)));
    vlSelf->core_tb__DOT__dut__DOT__qe_ready = (1U 
                                                & ((~ (IData)(vlSelf->core_tb__DOT__dut__DOT__qe_valid)) 
                                                   | ((~ (IData)(vlSelf->core_tb__DOT__fault)) 
                                                      & (7U 
                                                         == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)))));
    vlSelf->core_tb__DOT__dut__DOT__x_data[0U] = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe
        [1U];
    vlSelf->core_tb__DOT__dut__DOT__x_data[1U] = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe
        [1U];
    vlSelf->core_tb__DOT__dut__DOT__x_data[2U] = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe
        [1U];
    vlSelf->core_tb__DOT__dut__DOT__x_data[3U] = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe
        [1U];
    vlSelf->core_tb__DOT__dut__DOT__w_data[0U] = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe
        [1U];
    vlSelf->core_tb__DOT__dut__DOT__w_data[1U] = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe
        [1U];
    vlSelf->core_tb__DOT__dut__DOT__w_data[2U] = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe
        [1U];
    vlSelf->core_tb__DOT__dut__DOT__w_data[3U] = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe
        [1U];
    vlSelf->core_tb__DOT__out_data = vlSelf->core_tb__DOT__dut__DOT__result_data
        [(0x3fU & vlSelf->core_tb__DOT__dut__DOT__out_pos)];
    vlSelf->core_tb__DOT__out_overflow = vlSelf->core_tb__DOT__dut__DOT__result_overflow
        [(0x3fU & vlSelf->core_tb__DOT__dut__DOT__out_pos)];
    vlSelf->core_tb__DOT__out_saturated = vlSelf->core_tb__DOT__dut__DOT__result_saturated
        [(0x3fU & vlSelf->core_tb__DOT__dut__DOT__out_pos)];
    core_tb__DOT__dut__DOT____Vcellinp__quant__in_sum 
        = vlSelf->core_tb__DOT__dut__DOT__acc[(3U & vlSelf->core_tb__DOT__dut__DOT__g)]
        [(3U & vlSelf->core_tb__DOT__dut__DOT__qrow)]
        [(3U & vlSelf->core_tb__DOT__dut__DOT__qcol)];
    core_tb__DOT__dut__DOT____Vcellinp__quant__in_bias 
        = vlSelf->core_tb__DOT__dut__DOT__biases[(0xffU 
                                                  & (VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__tile) 
                                                     + 
                                                     (VL_MULS_III(32, (IData)(4U), vlSelf->core_tb__DOT__dut__DOT__g) 
                                                      + vlSelf->core_tb__DOT__dut__DOT__qcol)))];
    core_tb__DOT__dut__DOT____VdfgTmp_hff5a03ba__0 
        = (vlSelf->core_tb__DOT__dut__DOT__row0 + VL_DIVS_III(32, vlSelf->core_tb__DOT__dut__DOT__out_pos, (IData)(0x10U)));
    vlSelf->core_tb__DOT__dut__DOT__retire_event = 
        ((~ (IData)(vlSelf->core_tb__DOT__fault)) & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_valid));
    core_tb__DOT__dut__DOT__int16_ok = (vlSelf->core_tb__DOT__dut__DOT__q_data 
                                        == (((QData)((IData)(
                                                             (- (IData)(
                                                                        (1U 
                                                                         & (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__q_data 
                                                                                >> 0xfU))))))) 
                                             << 0x10U) 
                                            | (QData)((IData)(
                                                              (0xffffU 
                                                               & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_data))))));
    core_tb__DOT__dut__DOT__quant__DOT__added = (0x1ffffffffffffULL 
                                                 & ((((QData)((IData)(
                                                                      (1U 
                                                                       & (IData)(
                                                                                (core_tb__DOT__dut__DOT____Vcellinp__quant__in_sum 
                                                                                >> 0x2fU))))) 
                                                      << 0x30U) 
                                                     | core_tb__DOT__dut__DOT____Vcellinp__quant__in_sum) 
                                                    + 
                                                    (((QData)((IData)(
                                                                      (1U 
                                                                       & (IData)(
                                                                                (core_tb__DOT__dut__DOT____Vcellinp__quant__in_bias 
                                                                                >> 0x2fU))))) 
                                                      << 0x30U) 
                                                     | core_tb__DOT__dut__DOT____Vcellinp__quant__in_bias)));
    vlSelf->core_tb__DOT__dut__DOT__quant__DOT__overflow = 0U;
    if (VL_LTS_IQQ(49, 0x7fffffffffffULL, core_tb__DOT__dut__DOT__quant__DOT__added)) {
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__clipped = 0x7fffffffffffULL;
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__overflow = 1U;
    } else if (VL_GTS_IQQ(49, 0x1800000000000ULL, core_tb__DOT__dut__DOT__quant__DOT__added)) {
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__clipped = 0x800000000000ULL;
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__overflow = 1U;
    } else {
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__clipped 
            = (0xffffffffffffULL & core_tb__DOT__dut__DOT__quant__DOT__added);
    }
    core_tb__DOT__dut__DOT__quant__DOT__magnitude = 
        (0xffffffffffffULL & ((1U & (IData)((vlSelf->core_tb__DOT__dut__DOT__quant__DOT__clipped 
                                             >> 0x2fU)))
                               ? (1ULL + (~ vlSelf->core_tb__DOT__dut__DOT__quant__DOT__clipped))
                               : vlSelf->core_tb__DOT__dut__DOT__quant__DOT__clipped));
    core_tb__DOT__dut__DOT__quant__DOT__quotient = core_tb__DOT__dut__DOT__quant__DOT__magnitude;
    core_tb__DOT__dut__DOT__quant__DOT__remainder = 0ULL;
    core_tb__DOT__dut__DOT__quant__DOT__half = 0ULL;
    if ((0U != (IData)(vlSelf->core_tb__DOT__dut__DOT__shift))) {
        core_tb__DOT__dut__DOT__quant__DOT__quotient 
            = (0xffffffffffffULL & (core_tb__DOT__dut__DOT__quant__DOT__magnitude 
                                    >> (IData)(vlSelf->core_tb__DOT__dut__DOT__shift)));
        core_tb__DOT__dut__DOT__quant__DOT__remainder 
            = (core_tb__DOT__dut__DOT__quant__DOT__magnitude 
               & ((1ULL << (IData)(vlSelf->core_tb__DOT__dut__DOT__shift)) 
                  - 1ULL));
        core_tb__DOT__dut__DOT__quant__DOT__half = 
            (0xffffffffffffULL & (1ULL << (0x3fU & 
                                           ((IData)(vlSelf->core_tb__DOT__dut__DOT__shift) 
                                            - (IData)(1U)))));
        if (((core_tb__DOT__dut__DOT__quant__DOT__remainder 
              > core_tb__DOT__dut__DOT__quant__DOT__half) 
             | ((core_tb__DOT__dut__DOT__quant__DOT__remainder 
                 == core_tb__DOT__dut__DOT__quant__DOT__half) 
                & (IData)(core_tb__DOT__dut__DOT__quant__DOT__quotient)))) {
            core_tb__DOT__dut__DOT__quant__DOT__quotient 
                = (0xffffffffffffULL & (1ULL + core_tb__DOT__dut__DOT__quant__DOT__quotient));
        }
    }
    core_tb__DOT__dut__DOT__quant__DOT__rounded = (0x1ffffffffffffULL 
                                                   & ((1U 
                                                       & (IData)(
                                                                 (vlSelf->core_tb__DOT__dut__DOT__quant__DOT__clipped 
                                                                  >> 0x2fU)))
                                                       ? 
                                                      (- core_tb__DOT__dut__DOT__quant__DOT__quotient)
                                                       : core_tb__DOT__dut__DOT__quant__DOT__quotient));
    vlSelf->core_tb__DOT__dut__DOT__quant__DOT__saturated = 0U;
    if (VL_LTS_IQQ(49, 0x7fffffffULL, core_tb__DOT__dut__DOT__quant__DOT__rounded)) {
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__result = 0x7fffffffU;
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__saturated = 1U;
    } else if (VL_GTS_IQQ(49, 0x1ffff80000000ULL, core_tb__DOT__dut__DOT__quant__DOT__rounded)) {
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__result = 0x80000000U;
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__saturated = 1U;
    } else {
        vlSelf->core_tb__DOT__dut__DOT__quant__DOT__result 
            = (IData)(core_tb__DOT__dut__DOT__quant__DOT__rounded);
    }
    vlSelf->core_tb__DOT__out_y_index = (VL_MULS_III(32, (IData)(0x100U), core_tb__DOT__dut__DOT____VdfgTmp_hff5a03ba__0) 
                                         + (VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__tile) 
                                            + VL_MODDIVS_III(32, vlSelf->core_tb__DOT__dut__DOT__out_pos, (IData)(0x10U))));
    vlSelf->core_tb__DOT__out_last = ((0x62U == core_tb__DOT__dut__DOT____VdfgTmp_hff5a03ba__0) 
                                      & ((0xfU == vlSelf->core_tb__DOT__dut__DOT__tile) 
                                         & (0xfU == 
                                            VL_MODDIVS_III(32, vlSelf->core_tb__DOT__dut__DOT__out_pos, (IData)(0x10U)))));
    core_tb__DOT__dut__DOT____VdfgTmp_h109f94df__0 
        = ((IData)(vlSelf->core_tb__DOT__dut__DOT__retire_event) 
           & (1U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)));
    vlSelf->core_tb__DOT__dut__DOT__command_ok = 0U;
    if ((0U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))) {
        vlSelf->core_tb__DOT__dut__DOT__command_ok 
            = ((((0U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                 & (0x2fU >= (IData)(vlSelf->core_tb__DOT__dut__DOT__q_shift))) 
                & (1U <= (IData)(vlSelf->core_tb__DOT__dut__DOT__q_layer))) 
               & (0xcU >= (IData)(vlSelf->core_tb__DOT__dut__DOT__q_layer)));
    } else if (((1U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                & (vlSelf->core_tb__DOT__dut__DOT__q_task 
                   == vlSelf->core_tb__DOT__dut__DOT__task_id))) {
        vlSelf->core_tb__DOT__dut__DOT__command_ok 
            = ((1U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))
                ? (((((~ (IData)(vlSelf->core_tb__DOT__dut__DOT__tile_open)) 
                      & (0U == vlSelf->core_tb__DOT__dut__DOT__next_tile)) 
                     & ((IData)(vlSelf->core_tb__DOT__dut__DOT__q_index) 
                        == vlSelf->core_tb__DOT__dut__DOT__x_count)) 
                    & VL_GTS_III(32, 0x18c0U, vlSelf->core_tb__DOT__dut__DOT__x_count)) 
                   & (IData)(core_tb__DOT__dut__DOT__int16_ok))
                : ((2U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))
                    ? ((((0x18c0U == vlSelf->core_tb__DOT__dut__DOT__x_count) 
                         & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT__tile_open))) 
                        & VL_GTS_III(32, 0x10U, vlSelf->core_tb__DOT__dut__DOT__next_tile)) 
                       & ((IData)(vlSelf->core_tb__DOT__dut__DOT__q_tile) 
                          == vlSelf->core_tb__DOT__dut__DOT__next_tile))
                    : ((3U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))
                        ? ((((((IData)(vlSelf->core_tb__DOT__dut__DOT__tile_open) 
                               & ((IData)(vlSelf->core_tb__DOT__dut__DOT__q_tile) 
                                  == vlSelf->core_tb__DOT__dut__DOT__next_tile)) 
                              & ((IData)(vlSelf->core_tb__DOT__dut__DOT__q_index) 
                                 == vlSelf->core_tb__DOT__dut__DOT__w_count)) 
                             & VL_GTS_III(32, 0x400U, vlSelf->core_tb__DOT__dut__DOT__w_count)) 
                            & (0U == vlSelf->core_tb__DOT__dut__DOT__b_count)) 
                           & (IData)(core_tb__DOT__dut__DOT__int16_ok))
                        : ((4U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))
                            ? (((((IData)(vlSelf->core_tb__DOT__dut__DOT__tile_open) 
                                  & ((IData)(vlSelf->core_tb__DOT__dut__DOT__q_tile) 
                                     == vlSelf->core_tb__DOT__dut__DOT__next_tile)) 
                                 & (0x400U == vlSelf->core_tb__DOT__dut__DOT__w_count)) 
                                & ((IData)(vlSelf->core_tb__DOT__dut__DOT__q_index) 
                                   == vlSelf->core_tb__DOT__dut__DOT__b_count)) 
                               & VL_GTS_III(32, 0x10U, vlSelf->core_tb__DOT__dut__DOT__b_count))
                            : ((5U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))
                                ? ((((IData)(vlSelf->core_tb__DOT__dut__DOT__tile_open) 
                                     & ((IData)(vlSelf->core_tb__DOT__dut__DOT__q_tile) 
                                        == vlSelf->core_tb__DOT__dut__DOT__next_tile)) 
                                    & (0x400U == vlSelf->core_tb__DOT__dut__DOT__w_count)) 
                                   & (0x10U == vlSelf->core_tb__DOT__dut__DOT__b_count))
                                : ((6U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op)) 
                                   && (((~ (IData)(vlSelf->core_tb__DOT__dut__DOT__tile_open)) 
                                        & (0x10U == vlSelf->core_tb__DOT__dut__DOT__committed)) 
                                       & (0x18c0U == vlSelf->core_tb__DOT__dut__DOT__x_count))))))));
    }
    vlSelf->core_tb__DOT__in_ready = (1U & ((~ (IData)(vlSelf->core_tb__DOT__fault)) 
                                            & ((~ (IData)(vlSelf->core_tb__DOT__core_done)) 
                                               & ((~ 
                                                   ((8U 
                                                     == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                                    & (IData)(vlSelf->core_tb__DOT__out_last))) 
                                                  & ((~ (IData)(vlSelf->core_tb__DOT__dut__DOT__q_valid)) 
                                                     | (IData)(vlSelf->core_tb__DOT__dut__DOT__retire_event))))));
    vlSelf->core_tb__DOT__payload[0U] = ((vlSelf->core_tb__DOT__out_data 
                                          << 3U) | 
                                         (((IData)(vlSelf->core_tb__DOT__out_overflow) 
                                           << 2U) | 
                                          (((IData)(vlSelf->core_tb__DOT__out_saturated) 
                                            << 1U) 
                                           | (IData)(vlSelf->core_tb__DOT__out_last))));
    vlSelf->core_tb__DOT__payload[1U] = ((vlSelf->core_tb__DOT__out_data 
                                          >> 0x1dU) 
                                         | ((IData)(
                                                    (((QData)((IData)(vlSelf->core_tb__DOT__dut__DOT__task_id)) 
                                                      << 0x20U) 
                                                     | (QData)((IData)(vlSelf->core_tb__DOT__out_y_index)))) 
                                            << 3U));
    vlSelf->core_tb__DOT__payload[2U] = (((IData)((
                                                   ((QData)((IData)(vlSelf->core_tb__DOT__dut__DOT__task_id)) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(vlSelf->core_tb__DOT__out_y_index)))) 
                                          >> 0x1dU) 
                                         | ((IData)(
                                                    ((((QData)((IData)(vlSelf->core_tb__DOT__dut__DOT__task_id)) 
                                                       << 0x20U) 
                                                      | (QData)((IData)(vlSelf->core_tb__DOT__out_y_index))) 
                                                     >> 0x20U)) 
                                            << 3U));
    vlSelf->core_tb__DOT__payload[3U] = ((IData)(((
                                                   ((QData)((IData)(vlSelf->core_tb__DOT__dut__DOT__task_id)) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(vlSelf->core_tb__DOT__out_y_index))) 
                                                  >> 0x20U)) 
                                         >> 0x1dU);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en 
        = ((3U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
           & ((~ (IData)(vlSelf->core_tb__DOT__fault)) 
              & (~ ((~ (IData)(vlSelf->core_tb__DOT__dut__DOT__command_ok)) 
                    & (IData)(vlSelf->core_tb__DOT__dut__DOT__retire_event)))));
    core_tb__DOT__dut__DOT__x_write = ((IData)(core_tb__DOT__dut__DOT____VdfgTmp_h109f94df__0) 
                                       & ((1U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op)) 
                                          & (IData)(vlSelf->core_tb__DOT__dut__DOT__command_ok)));
    core_tb__DOT__dut__DOT__w_write = ((IData)(core_tb__DOT__dut__DOT____VdfgTmp_h109f94df__0) 
                                       & ((3U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op)) 
                                          & (IData)(vlSelf->core_tb__DOT__dut__DOT__command_ok)));
    core_tb__DOT__dut__DOT____VdfgTmp_hb9770c27__0 
        = ((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en) 
           & (0U == vlSelf->core_tb__DOT__dut__DOT__req_g));
    if (core_tb__DOT__dut__DOT__x_write) {
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr 
            = (0x7ffU & ((0x7c0U & ((IData)(vlSelf->core_tb__DOT__dut__DOT__q_index) 
                                    >> 2U)) + (0x3fU 
                                               & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index))));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__wr_en 
            = (3U == (3U & VL_SHIFTR_III(32,32,32, (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index), 6U)));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__wr_en 
            = (2U == (3U & VL_SHIFTR_III(32,32,32, (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index), 6U)));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__wr_en 
            = (1U == (3U & VL_SHIFTR_III(32,32,32, (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index), 6U)));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__wr_en 
            = (0U == (3U & VL_SHIFTR_III(32,32,32, (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index), 6U)));
    } else {
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr 
            = (0x7ffU & (VL_MULS_III(32, (IData)(0x40U), 
                                     VL_DIVS_III(32, vlSelf->core_tb__DOT__dut__DOT__row0, (IData)(4U))) 
                         + vlSelf->core_tb__DOT__dut__DOT__req_k));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__wr_en = 0U;
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__wr_en = 0U;
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__wr_en = 0U;
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__wr_en = 0U;
    }
    if (core_tb__DOT__dut__DOT__w_write) {
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr 
            = (0xfffU & (VL_SHIFTL_III(12,12,32, vlSelf->core_tb__DOT__dut__DOT__next_tile, 8U) 
                         + ((0xc0U & VL_SHIFTL_III(12,12,32, (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index), 4U)) 
                            + ((IData)(vlSelf->core_tb__DOT__dut__DOT__q_index) 
                               >> 4U))));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__3__KET____DOT__ram__wr_en 
            = (3U == (3U & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index)));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__2__KET____DOT__ram__wr_en 
            = (2U == (3U & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index)));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__1__KET____DOT__ram__wr_en 
            = (1U == (3U & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index)));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__wr_en 
            = (0U == (3U & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_index)));
    } else {
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr 
            = (0xfffU & (VL_MULS_III(32, (IData)(0x100U), vlSelf->core_tb__DOT__dut__DOT__tile) 
                         + (VL_MULS_III(32, (IData)(0x40U), vlSelf->core_tb__DOT__dut__DOT__req_g) 
                            + vlSelf->core_tb__DOT__dut__DOT__req_k)));
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__3__KET____DOT__ram__wr_en = 0U;
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__2__KET____DOT__ram__wr_en = 0U;
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__1__KET____DOT__ram__wr_en = 0U;
        vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__wr_en = 0U;
    }
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__rd_en 
        = ((IData)(core_tb__DOT__dut__DOT____VdfgTmp_hb9770c27__0) 
           & VL_GTS_III(32, 0x63U, ((IData)(3U) + vlSelf->core_tb__DOT__dut__DOT__row0)));
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__rd_en 
        = ((IData)(core_tb__DOT__dut__DOT____VdfgTmp_hb9770c27__0) 
           & VL_GTS_III(32, 0x63U, ((IData)(2U) + vlSelf->core_tb__DOT__dut__DOT__row0)));
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__rd_en 
        = ((IData)(core_tb__DOT__dut__DOT____VdfgTmp_hb9770c27__0) 
           & VL_GTS_III(32, 0x63U, ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__row0)));
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__rd_en 
        = ((IData)(core_tb__DOT__dut__DOT____VdfgTmp_hb9770c27__0) 
           & VL_GTS_III(32, 0x63U, vlSelf->core_tb__DOT__dut__DOT__row0));
    vlSelf->core_tb__DOT__dut__DOT__x_wr = (((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__wr_en) 
                                             << 3U) 
                                            | (((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__wr_en) 
                                                << 2U) 
                                               | (((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__wr_en) 
                                                   << 1U) 
                                                  | (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__wr_en))));
    vlSelf->core_tb__DOT__dut__DOT__w_wr = (((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__3__KET____DOT__ram__wr_en) 
                                             << 3U) 
                                            | (((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__2__KET____DOT__ram__wr_en) 
                                                << 2U) 
                                               | (((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__1__KET____DOT__ram__wr_en) 
                                                   << 1U) 
                                                  | (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__wr_en))));
    vlSelf->core_tb__DOT__dut__DOT__x_rd = (((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__rd_en) 
                                             << 3U) 
                                            | (((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__rd_en) 
                                                << 2U) 
                                               | (((IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__rd_en) 
                                                   << 1U) 
                                                  | (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__rd_en))));
}

VL_ATTR_COLD void Vcore_tb___024root___eval_stl(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vcore_tb___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vcore_tb___024root___eval_triggers__stl(Vcore_tb___024root* vlSelf);

VL_ATTR_COLD bool Vcore_tb___024root___eval_phase__stl(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vcore_tb___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vcore_tb___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore_tb___024root___dump_triggers__act(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(negedge core_tb.clk)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge core_tb.clk)\n");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 2 is active: @([changed] ((4'h8 == core_tb.dut.state) & core_tb.out_last))\n");
    }
    if ((8ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 3 is active: @([changed] ((4'h8 == core_tb.dut.state) & (32'h62fe == core_tb.out_y_index)))\n");
    }
    if ((0x10ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 4 is active: @([changed] core_tb.fault)\n");
    }
    if ((0x20ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 5 is active: @([changed] (core_tb.core_done | core_tb.fault))\n");
    }
    if ((0x40ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 6 is active: @([changed] ((4'h4 == core_tb.dut.state) & (64'h3 < core_tb.dut.issue_count)))\n");
    }
    if ((0x80ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 7 is active: @([changed] (4'h7 == core_tb.dut.state))\n");
    }
    if ((0x100ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 8 is active: @([changed] (4'h8 == core_tb.dut.state))\n");
    }
    if ((0x200ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 9 is active: @([changed] (core_tb.dut.tag_valid[1] & (2'h0 == (core_tb.dut.tag_g[1'h1]))))\n");
    }
    if ((0x400ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 10 is active: @([changed] (core_tb.dut.product_valid & (6'h1 < core_tb.dut.product_k)))\n");
    }
    if ((0x800ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 11 is active: @([changed] (4'h8 != core_tb.dut.state))\n");
    }
    if ((0x1000ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 12 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore_tb___024root___dump_triggers__nba(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(negedge core_tb.clk)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge core_tb.clk)\n");
    }
    if ((4ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 2 is active: @([changed] ((4'h8 == core_tb.dut.state) & core_tb.out_last))\n");
    }
    if ((8ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 3 is active: @([changed] ((4'h8 == core_tb.dut.state) & (32'h62fe == core_tb.out_y_index)))\n");
    }
    if ((0x10ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 4 is active: @([changed] core_tb.fault)\n");
    }
    if ((0x20ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 5 is active: @([changed] (core_tb.core_done | core_tb.fault))\n");
    }
    if ((0x40ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 6 is active: @([changed] ((4'h4 == core_tb.dut.state) & (64'h3 < core_tb.dut.issue_count)))\n");
    }
    if ((0x80ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 7 is active: @([changed] (4'h7 == core_tb.dut.state))\n");
    }
    if ((0x100ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 8 is active: @([changed] (4'h8 == core_tb.dut.state))\n");
    }
    if ((0x200ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 9 is active: @([changed] (core_tb.dut.tag_valid[1] & (2'h0 == (core_tb.dut.tag_g[1'h1]))))\n");
    }
    if ((0x400ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 10 is active: @([changed] (core_tb.dut.product_valid & (6'h1 < core_tb.dut.product_k)))\n");
    }
    if ((0x800ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 11 is active: @([changed] (4'h8 != core_tb.dut.state))\n");
    }
    if ((0x1000ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 12 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcore_tb___024root___ctor_var_reset(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->core_tb__DOT__clk = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__rst_n = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__in_valid = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__out_ready = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__in_op = VL_RAND_RESET_I(4);
    vlSelf->core_tb__DOT__in_layer_id = VL_RAND_RESET_I(4);
    vlSelf->core_tb__DOT__in_task_id = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__in_tile_id = VL_RAND_RESET_I(8);
    vlSelf->core_tb__DOT__in_index = VL_RAND_RESET_I(16);
    vlSelf->core_tb__DOT__in_data = VL_RAND_RESET_Q(48);
    vlSelf->core_tb__DOT__in_shift = VL_RAND_RESET_I(6);
    vlSelf->core_tb__DOT__in_ready = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__out_valid = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__out_overflow = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__out_saturated = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__out_last = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__core_done = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__fault = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__out_y_index = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__out_data = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__error_code = VL_RAND_RESET_I(8);
    vlSelf->core_tb__DOT__of = 0;
    vlSelf->core_tb__DOT__sf = 0;
    vlSelf->core_tb__DOT__rc = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__op = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__task_no = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__tile_no = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__idx = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__shift_no = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__layer_no = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__word_data = VL_RAND_RESET_Q(48);
    vlSelf->core_tb__DOT__cycles = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__accepted = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__received = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dones = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__cold_first = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__cold_start = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__cold_last = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__stall = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__last_stalled = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__retracted = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__gap = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__last_done_received = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__expect_fault = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__sink_hold = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__force_ready = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__boundary_ready = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__rng = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__blocked = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(99, vlSelf->core_tb__DOT__held);
    VL_RAND_RESET_W(99, vlSelf->core_tb__DOT__payload);
    vlSelf->core_tb__DOT__dut__DOT__state = VL_RAND_RESET_I(4);
    vlSelf->core_tb__DOT__dut__DOT__q_valid = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__q_op = VL_RAND_RESET_I(4);
    vlSelf->core_tb__DOT__dut__DOT__q_layer = VL_RAND_RESET_I(4);
    vlSelf->core_tb__DOT__dut__DOT__q_task = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__q_tile = VL_RAND_RESET_I(8);
    vlSelf->core_tb__DOT__dut__DOT__q_index = VL_RAND_RESET_I(16);
    vlSelf->core_tb__DOT__dut__DOT__q_data = VL_RAND_RESET_Q(48);
    vlSelf->core_tb__DOT__dut__DOT__q_shift = VL_RAND_RESET_I(6);
    vlSelf->core_tb__DOT__dut__DOT__task_id = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__shift = VL_RAND_RESET_I(6);
    vlSelf->core_tb__DOT__dut__DOT__x_count = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__w_count = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__b_count = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__next_tile = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__committed = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__tile_open = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__row0 = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__tile = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__g = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__qrow = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__qcol = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__out_pos = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            for (int __Vi2 = 0; __Vi2 < 4; ++__Vi2) {
                vlSelf->core_tb__DOT__dut__DOT__acc[__Vi0][__Vi1][__Vi2] = VL_RAND_RESET_Q(48);
            }
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__x_hold[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->core_tb__DOT__dut__DOT__product[__Vi0][__Vi1] = VL_RAND_RESET_I(32);
        }
    }
    vlSelf->core_tb__DOT__dut__DOT__product_mask = VL_RAND_RESET_I(4);
    vlSelf->core_tb__DOT__dut__DOT__product_k = VL_RAND_RESET_I(6);
    vlSelf->core_tb__DOT__dut__DOT__product_g = VL_RAND_RESET_I(2);
    vlSelf->core_tb__DOT__dut__DOT__product_valid = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__product_task = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__product_row = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__product_tile = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__tag_valid = VL_RAND_RESET_I(2);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__tag_k[__Vi0] = VL_RAND_RESET_I(6);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__tag_g[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__tag_mask[__Vi0] = VL_RAND_RESET_I(4);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__tag_task[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__tag_row[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__tag_tile[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->core_tb__DOT__dut__DOT__req_g = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__req_k = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__biases[__Vi0] = VL_RAND_RESET_Q(48);
    }
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__result_data[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__result_overflow[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__result_saturated[__Vi0] = VL_RAND_RESET_I(1);
    }
    vlSelf->core_tb__DOT__dut__DOT__row_mask = VL_RAND_RESET_I(4);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__x_data[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__w_data[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->core_tb__DOT__dut__DOT__x_rd = VL_RAND_RESET_I(4);
    vlSelf->core_tb__DOT__dut__DOT__x_wr = VL_RAND_RESET_I(4);
    vlSelf->core_tb__DOT__dut__DOT__w_wr = VL_RAND_RESET_I(4);
    vlSelf->core_tb__DOT__dut__DOT__retire_event = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__command_ok = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__returned = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__qe_ready = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__qe_valid = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__unused_qe_raw = VL_RAND_RESET_Q(48);
    vlSelf->core_tb__DOT__dut__DOT__qe_data = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__qe_overflow = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__qe_saturated = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__quant__in_valid = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__load_cycles = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__compute_cycles = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__output_cycles = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__wait_cycles = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__core_cycles = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__frontend_cycles = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__issue_count = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__retire_count = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__effective_macs = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__virtual_macs = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__input_accepts = VL_RAND_RESET_Q(64);
    vlSelf->core_tb__DOT__dut__DOT__event_retires = VL_RAND_RESET_Q(64);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__x_reads[__Vi0] = VL_RAND_RESET_Q(64);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__x_writes[__Vi0] = VL_RAND_RESET_Q(64);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__w_reads[__Vi0] = VL_RAND_RESET_Q(64);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__w_writes[__Vi0] = VL_RAND_RESET_Q(64);
    }
    vlSelf->core_tb__DOT__dut__DOT__core_active = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__effective_rows = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr = VL_RAND_RESET_I(11);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__rd_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__wr_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__rd_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__wr_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__rd_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__wr_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__rd_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__wr_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr = VL_RAND_RESET_I(12);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__wr_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__1__KET____DOT__ram__wr_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__2__KET____DOT__ram__wr_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__3__KET____DOT__ram__wr_en = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__quant__DOT__clipped = VL_RAND_RESET_Q(48);
    vlSelf->core_tb__DOT__dut__DOT__quant__DOT__result = VL_RAND_RESET_I(32);
    vlSelf->core_tb__DOT__dut__DOT__quant__DOT__overflow = VL_RAND_RESET_I(1);
    vlSelf->core_tb__DOT__dut__DOT__quant__DOT__saturated = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 1600; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__valid_pipe = VL_RAND_RESET_I(2);
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0 = VL_RAND_RESET_I(16);
    for (int __Vi0 = 0; __Vi0 < 1600; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__valid_pipe = VL_RAND_RESET_I(2);
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0 = VL_RAND_RESET_I(16);
    for (int __Vi0 = 0; __Vi0 < 1600; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__valid_pipe = VL_RAND_RESET_I(2);
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0 = VL_RAND_RESET_I(16);
    for (int __Vi0 = 0; __Vi0 < 1600; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__valid_pipe = VL_RAND_RESET_I(2);
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0 = VL_RAND_RESET_I(16);
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__valid_pipe = VL_RAND_RESET_I(2);
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__valid_pipe = VL_RAND_RESET_I(2);
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__valid_pipe = VL_RAND_RESET_I(2);
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__valid_pipe = VL_RAND_RESET_I(2);
    vlSelf->__Vtrigprevexpr___TOP__core_tb__DOT__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_h78b21af8__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_h07439b72__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__core_tb__DOT__fault__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_h7be2f429__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_hf506ef54__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_hc537c130__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_hc537d19d__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_h4fe0a6ca__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_h88b84a6b__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_ha6663f55__0 = VL_RAND_RESET_I(1);
    vlSelf->__VactDidInit = 0;
}

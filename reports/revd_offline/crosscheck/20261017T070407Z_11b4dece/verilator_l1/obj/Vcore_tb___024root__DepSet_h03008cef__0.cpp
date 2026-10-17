// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore_tb.h for the primary calling header

#include "Vcore_tb__pch.h"
#include "Vcore_tb__Syms.h"
#include "Vcore_tb___024root.h"

VL_INLINE_OPT VlCoroutine Vcore_tb___024root___eval_initial__TOP__Vtiming__0(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    // Init
    IData/*31:0*/ core_tb__DOT__cf;
    core_tb__DOT__cf = 0;
    IData/*31:0*/ core_tb__DOT____Vrepeat6;
    core_tb__DOT____Vrepeat6 = 0;
    // Body
    if (VL_UNLIKELY((((! VL_VALUEPLUSARGS_INN(64, std::string{"CMD=%s"}, 
                                              vlSelf->core_tb__DOT__cmd_path)) 
                      || (! VL_VALUEPLUSARGS_INN(64, 
                                                 std::string{"OUT=%s"}, 
                                                 vlSelf->core_tb__DOT__out_path))) 
                     || (! VL_VALUEPLUSARGS_INN(64, 
                                                std::string{"STATS=%s"}, 
                                                vlSelf->core_tb__DOT__stats_path))))) {
        VL_WRITEF("[%0t] %%Fatal: core_tb.sv:36: Assertion failed in %Ncore_tb: missing paths\n",
                  64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 36, "");
    }
    core_tb__DOT__cf = VL_FOPEN_NN(VL_CVT_PACK_STR_NN(vlSelf->core_tb__DOT__cmd_path)
                                   , std::string{"r"});
    ;
    vlSelf->core_tb__DOT__of = VL_FOPEN_NN(VL_CVT_PACK_STR_NN(vlSelf->core_tb__DOT__out_path)
                                           , std::string{"w"});
    ;
    vlSelf->core_tb__DOT__sf = VL_FOPEN_NN(VL_CVT_PACK_STR_NN(vlSelf->core_tb__DOT__stats_path)
                                           , std::string{"w"});
    ;
    if (VL_UNLIKELY((1U & (((~ (IData)((0U != core_tb__DOT__cf))) 
                            | (~ (IData)((0U != vlSelf->core_tb__DOT__of)))) 
                           | (~ (IData)((0U != vlSelf->core_tb__DOT__sf))))))) {
        VL_WRITEF("[%0t] %%Fatal: core_tb.sv:38: Assertion failed in %Ncore_tb: open failure\n",
                  64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 38, "");
    }
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       39);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       39);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       39);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       39);
    vlSelf->core_tb__DOT__rst_n = 1U;
    while ((! (core_tb__DOT__cf ? feof(VL_CVT_I_FP(core_tb__DOT__cf)) : true))) {
        vlSelf->core_tb__DOT__rc = VL_FSCANF_IX(core_tb__DOT__cf,"%x %x %x %x %x %x %x\n",
                                                32,
                                                &(vlSelf->core_tb__DOT__op),
                                                32,
                                                &(vlSelf->core_tb__DOT__task_no),
                                                32,
                                                &(vlSelf->core_tb__DOT__tile_no),
                                                32,
                                                &(vlSelf->core_tb__DOT__idx),
                                                48,
                                                &(vlSelf->core_tb__DOT__word_data),
                                                32,
                                                &(vlSelf->core_tb__DOT__shift_no),
                                                32,
                                                &(vlSelf->core_tb__DOT__layer_no)) ;
        if (VL_UNLIKELY((7U != vlSelf->core_tb__DOT__rc))) {
            VL_WRITEF("[%0t] %%Fatal: core_tb.sv:42: Assertion failed in %Ncore_tb: bad command %0d\n",
                      64,VL_TIME_UNITED_Q(1000),-9,
                      vlSymsp->name(),32,vlSelf->core_tb__DOT__rc);
            VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 42, "");
        }
        if (VL_UNLIKELY((9U == vlSelf->core_tb__DOT__op))) {
            vlSelf->core_tb__DOT__in_valid = 0U;
            vlSelf->core_tb__DOT__boundary_ready = 1U;
            if (((0U == vlSelf->core_tb__DOT__idx) 
                 | (3U == vlSelf->core_tb__DOT__idx))) {
                while ((1U & (~ ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                 & (IData)(vlSelf->core_tb__DOT__out_last))))) {
                    co_await vlSelf->__VtrigSched_hec86538a__0.trigger(1U, 
                                                                       nullptr, 
                                                                       "@([changed] ((4'h8 == core_tb.dut.state) & core_tb.out_last))", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       46);
                }
            } else {
                while ((1U & (~ ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                 & (0x62feU == vlSelf->core_tb__DOT__out_y_index))))) {
                    co_await vlSelf->__VtrigSched_h5ef4d410__0.trigger(1U, 
                                                                       nullptr, 
                                                                       "@([changed] ((4'h8 == core_tb.dut.state) & (32'h62fe == core_tb.out_y_index)))", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       47);
                }
            }
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               48);
            if ((2U == vlSelf->core_tb__DOT__idx)) {
                vlSelf->core_tb__DOT__boundary_ready = 0U;
                vlSelf->core_tb__DOT__out_ready = 0U;
            } else {
                vlSelf->core_tb__DOT__boundary_ready = 1U;
                vlSelf->core_tb__DOT__out_ready = 1U;
            }
            vlSelf->core_tb__DOT__in_op = ((3U == vlSelf->core_tb__DOT__idx)
                                            ? 0U : 7U);
            vlSelf->core_tb__DOT__in_task_id = vlSelf->core_tb__DOT__task_no;
            vlSelf->core_tb__DOT__in_tile_id = 0U;
            vlSelf->core_tb__DOT__in_index = 0U;
            vlSelf->core_tb__DOT__in_data = 0ULL;
            vlSelf->core_tb__DOT__in_shift = (0x3fU 
                                              & vlSelf->core_tb__DOT__shift_no);
            vlSelf->core_tb__DOT__in_layer_id = (0xfU 
                                                 & vlSelf->core_tb__DOT__layer_no);
            vlSelf->core_tb__DOT__in_valid = 1U;
            co_await vlSelf->__VtrigSched_h81e7d9f7__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               52);
            VL_FWRITEF(vlSelf->core_tb__DOT__sf,"BOUNDARY %0d 0 %b %b %b %b %b %b %b %b\n",
                       32,vlSelf->core_tb__DOT__idx,
                       1,(IData)(vlSelf->core_tb__DOT__in_ready),
                       1,((IData)(vlSelf->core_tb__DOT__in_valid) 
                          & (IData)(vlSelf->core_tb__DOT__in_ready)),
                       1,(8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)),
                       1,(IData)(vlSelf->core_tb__DOT__out_last),
                       1,vlSelf->core_tb__DOT__out_ready,
                       1,(IData)(vlSelf->core_tb__DOT__core_done),
                       1,vlSelf->core_tb__DOT__fault,
                       1,(IData)(vlSelf->core_tb__DOT__dut__DOT__q_valid));
            if (vlSelf->core_tb__DOT__in_ready) {
                vlSelf->core_tb__DOT__accepted = ((IData)(1U) 
                                                  + vlSelf->core_tb__DOT__accepted);
            }
            if (VL_UNLIKELY(((1U == vlSelf->core_tb__DOT__idx) 
                             | (2U == vlSelf->core_tb__DOT__idx)))) {
                if (VL_UNLIKELY((1U & ((~ (IData)(vlSelf->core_tb__DOT__in_ready)) 
                                       | (IData)(vlSelf->core_tb__DOT__out_last))))) {
                    VL_WRITEF("[%0t] %%Fatal: core_tb.sv:56: Assertion failed in %Ncore_tb: pending-event setup did not accept before last\n",
                              64,VL_TIME_UNITED_Q(1000),
                              -9,vlSymsp->name());
                    VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 56, "");
                }
                co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(negedge core_tb.clk)", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   57);
                vlSelf->core_tb__DOT__in_valid = 0U;
                vlSelf->core_tb__DOT__boundary_ready 
                    = ((2U == vlSelf->core_tb__DOT__idx)
                        ? 0U : 1U);
                if ((2U == vlSelf->core_tb__DOT__idx)) {
                    vlSelf->core_tb__DOT__boundary_ready = 1U;
                    vlSelf->core_tb__DOT__out_ready = 1U;
                    co_await vlSelf->__VtrigSched_h81e7d9f7__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(posedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       60);
                    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(negedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       60);
                    vlSelf->core_tb__DOT__boundary_ready = 0U;
                    vlSelf->core_tb__DOT__out_ready = 0U;
                }
                vlSelf->core_tb__DOT__expect_fault = 1U;
                while ((1U & (~ (IData)(vlSelf->core_tb__DOT__fault)))) {
                    co_await vlSelf->__VtrigSched_he7308b1f__0.trigger(1U, 
                                                                       nullptr, 
                                                                       "@([changed] core_tb.fault)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       62);
                }
                co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(negedge core_tb.clk)", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   62);
                if (VL_UNLIKELY(vlSelf->core_tb__DOT__core_done)) {
                    VL_WRITEF("[%0t] %%Fatal: core_tb.sv:63: Assertion failed in %Ncore_tb: success before accepted illegal event fault\n",
                              64,VL_TIME_UNITED_Q(1000),
                              -9,vlSymsp->name());
                    VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 63, "");
                }
                if ((2U == vlSelf->core_tb__DOT__idx)) {
                    if (VL_UNLIKELY((1U & ((8U != (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                           | (~ (IData)(vlSelf->core_tb__DOT__out_last)))))) {
                        VL_WRITEF("[%0t] %%Fatal: core_tb.sv:65: Assertion failed in %Ncore_tb: last output lost during fault\n",
                                  64,VL_TIME_UNITED_Q(1000),
                                  -9,vlSymsp->name());
                        VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 65, "");
                    }
                    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(negedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       66);
                    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(negedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       66);
                    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(negedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       66);
                    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(negedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       66);
                    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(negedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       66);
                    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(negedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       66);
                    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(negedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       66);
                }
                VL_FWRITEF(vlSelf->core_tb__DOT__sf,"BOUNDARY %0d 1 %b %b %b %b %b %b %b %b\n",
                           32,vlSelf->core_tb__DOT__idx,
                           1,(IData)(vlSelf->core_tb__DOT__in_ready),
                           1,((IData)(vlSelf->core_tb__DOT__in_valid) 
                              & (IData)(vlSelf->core_tb__DOT__in_ready)),
                           1,(8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)),
                           1,(IData)(vlSelf->core_tb__DOT__out_last),
                           1,vlSelf->core_tb__DOT__out_ready,
                           1,(IData)(vlSelf->core_tb__DOT__core_done),
                           1,vlSelf->core_tb__DOT__fault,
                           1,(IData)(vlSelf->core_tb__DOT__dut__DOT__q_valid));
                vlSelf->core_tb__DOT__boundary_ready = 1U;
                vlSelf->core_tb__DOT__out_ready = 1U;
            } else if ((0U == vlSelf->core_tb__DOT__idx)) {
                co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(negedge core_tb.clk)", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   71);
                vlSelf->core_tb__DOT__in_valid = 0U;
                while ((1U & (~ ((IData)(vlSelf->core_tb__DOT__core_done) 
                                 | (IData)(vlSelf->core_tb__DOT__fault))))) {
                    co_await vlSelf->__VtrigSched_hebd52a47__0.trigger(1U, 
                                                                       nullptr, 
                                                                       "@([changed] (core_tb.core_done | core_tb.fault))", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       72);
                }
                co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(negedge core_tb.clk)", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   72);
                if (VL_UNLIKELY(vlSelf->core_tb__DOT__fault)) {
                    VL_WRITEF("[%0t] %%Fatal: core_tb.sv:73: Assertion failed in %Ncore_tb: unaccepted terminal input faulted completed task\n",
                              64,VL_TIME_UNITED_Q(1000),
                              -9,vlSymsp->name());
                    VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 73, "");
                }
            } else if (VL_LIKELY((3U == vlSelf->core_tb__DOT__idx))) {
                while ((1U & (~ (IData)(vlSelf->core_tb__DOT__in_ready)))) {
                    co_await vlSelf->__VtrigSched_h81e7d9f7__0.trigger(0U, 
                                                                       nullptr, 
                                                                       "@(posedge core_tb.clk)", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       76);
                }
                VL_FWRITEF(vlSelf->core_tb__DOT__sf,"BOUNDARY %0d 2 %b %b %b %b %b %b %b %b\n",
                           32,vlSelf->core_tb__DOT__idx,
                           1,(IData)(vlSelf->core_tb__DOT__in_ready),
                           1,((IData)(vlSelf->core_tb__DOT__in_valid) 
                              & (IData)(vlSelf->core_tb__DOT__in_ready)),
                           1,(8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)),
                           1,(IData)(vlSelf->core_tb__DOT__out_last),
                           1,vlSelf->core_tb__DOT__out_ready,
                           1,(IData)(vlSelf->core_tb__DOT__core_done),
                           1,vlSelf->core_tb__DOT__fault,
                           1,(IData)(vlSelf->core_tb__DOT__dut__DOT__q_valid));
                if (VL_UNLIKELY((((IData)(vlSelf->core_tb__DOT__core_done) 
                                  | (8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) 
                                 | (IData)(vlSelf->core_tb__DOT__fault)))) {
                    VL_WRITEF("[%0t] %%Fatal: core_tb.sv:78: Assertion failed in %Ncore_tb: next BEGIN accepted before completion boundary cleared\n",
                              64,VL_TIME_UNITED_Q(1000),
                              -9,vlSymsp->name());
                    VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 78, "");
                }
                vlSelf->core_tb__DOT__accepted = ((IData)(1U) 
                                                  + vlSelf->core_tb__DOT__accepted);
                co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(negedge core_tb.clk)", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   79);
                vlSelf->core_tb__DOT__in_valid = 0U;
            } else {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:80: Assertion failed in %Ncore_tb: unknown boundary mode\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name());
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 80, "");
            }
        } else if ((0xaU == vlSelf->core_tb__DOT__op)) {
            vlSelf->core_tb__DOT__sink_hold = 0U;
            vlSelf->core_tb__DOT__force_ready = 1U;
            vlSelf->core_tb__DOT__out_ready = 1U;
        } else if (VL_UNLIKELY((0xeU == vlSelf->core_tb__DOT__op))) {
            vlSelf->core_tb__DOT__in_valid = 0U;
            if ((1U == vlSelf->core_tb__DOT__idx)) {
                while ((1U & (~ ((4U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                 & (3ULL < vlSelf->core_tb__DOT__dut__DOT__issue_count))))) {
                    co_await vlSelf->__VtrigSched_h70b12766__0.trigger(1U, 
                                                                       nullptr, 
                                                                       "@([changed] ((4'h4 == core_tb.dut.state) & (64'h3 < core_tb.dut.issue_count)))", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       85);
                }
            }
            if ((2U == vlSelf->core_tb__DOT__idx)) {
                while ((7U != (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                    co_await vlSelf->__VtrigSched_h2100f542__0.trigger(1U, 
                                                                       nullptr, 
                                                                       "@([changed] (4'h7 == core_tb.dut.state))", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       86);
                }
            }
            if ((3U == vlSelf->core_tb__DOT__idx)) {
                while ((8U != (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                    co_await vlSelf->__VtrigSched_h2100062b__0.trigger(1U, 
                                                                       nullptr, 
                                                                       "@([changed] (4'h8 == core_tb.dut.state))", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       87);
                }
            }
            if ((4U == vlSelf->core_tb__DOT__idx)) {
                while ((1U & (~ ((IData)(vlSelf->core_tb__DOT__dut__DOT__tag_valid) 
                                 & (0U == vlSelf->core_tb__DOT__dut__DOT__tag_g
                                    [0U]))))) {
                    co_await vlSelf->__VtrigSched_h6bb67ba3__0.trigger(1U, 
                                                                       nullptr, 
                                                                       "@([changed] (core_tb.dut.tag_valid & (2'h0 == (core_tb.dut.tag_g[1'h0]))))", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       89);
                }
            }
            if ((5U == vlSelf->core_tb__DOT__idx)) {
                while ((1U & (~ ((IData)(vlSelf->core_tb__DOT__dut__DOT__product_valid) 
                                 & (1U < (IData)(vlSelf->core_tb__DOT__dut__DOT__product_k)))))) {
                    co_await vlSelf->__VtrigSched_hdc7f84fd__0.trigger(1U, 
                                                                       nullptr, 
                                                                       "@([changed] (core_tb.dut.product_valid & (6'h1 < core_tb.dut.product_k)))", 
                                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                       90);
                }
            }
            VL_FWRITEF(vlSelf->core_tb__DOT__sf,"RESET %0d %0#\n",
                       32,vlSelf->core_tb__DOT__idx,
                       4,(IData)(vlSelf->core_tb__DOT__dut__DOT__state));
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               93);
            vlSelf->core_tb__DOT__rst_n = 0U;
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               94);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               94);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               94);
            vlSelf->core_tb__DOT__rst_n = 1U;
            vlSelf->core_tb__DOT__sink_hold = 0U;
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               95);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               95);
            if (VL_UNLIKELY((((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                              | (IData)(vlSelf->core_tb__DOT__fault)) 
                             | (IData)(vlSelf->core_tb__DOT__core_done)))) {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:96: Assertion failed in %Ncore_tb: reset residual valid/fault/done\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name());
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 96, "");
            }
        } else if ((0xdU == vlSelf->core_tb__DOT__op)) {
            vlSelf->core_tb__DOT__in_valid = 0U;
            vlSelf->core_tb__DOT__sink_hold = 1U;
            while ((8U != (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                co_await vlSelf->__VtrigSched_h2100062b__0.trigger(1U, 
                                                                   nullptr, 
                                                                   "@([changed] (4'h8 == core_tb.dut.state))", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   98);
            }
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               98);
        } else if ((0xcU == vlSelf->core_tb__DOT__op)) {
            vlSelf->core_tb__DOT__in_valid = 0U;
            vlSelf->core_tb__DOT__expect_fault = 1U;
            while ((1U & (~ (IData)(vlSelf->core_tb__DOT__fault)))) {
                co_await vlSelf->__VtrigSched_he7308b1f__0.trigger(1U, 
                                                                   nullptr, 
                                                                   "@([changed] core_tb.fault)", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   100);
            }
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               100);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               101);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               101);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               101);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               101);
            if (VL_UNLIKELY(((IData)(vlSelf->core_tb__DOT__core_done) 
                             | (IData)(vlSelf->core_tb__DOT__in_ready)))) {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:102: Assertion failed in %Ncore_tb: fault falsely completed/accepted\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name());
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 102, "");
            }
            vlSelf->core_tb__DOT__sink_hold = 0U;
            while ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                co_await vlSelf->__VtrigSched_h02527763__0.trigger(1U, 
                                                                   nullptr, 
                                                                   "@([changed] (4'h8 != core_tb.dut.state))", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   103);
            }
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               103);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               103);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               103);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               103);
        } else if ((0xbU == vlSelf->core_tb__DOT__op)) {
            vlSelf->core_tb__DOT__sink_hold = 1U;
        } else if ((0xfU == vlSelf->core_tb__DOT__op)) {
            vlSelf->core_tb__DOT__in_valid = 0U;
            while ((1U & (~ ((IData)(vlSelf->core_tb__DOT__core_done) 
                             | (IData)(vlSelf->core_tb__DOT__fault))))) {
                co_await vlSelf->__VtrigSched_hebd52a47__0.trigger(1U, 
                                                                   nullptr, 
                                                                   "@([changed] (core_tb.core_done | core_tb.fault))", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   108);
            }
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               108);
            if (VL_UNLIKELY(vlSelf->core_tb__DOT__fault)) {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:109: Assertion failed in %Ncore_tb: unexpected fault %0#\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name(),8,(IData)(vlSelf->core_tb__DOT__error_code));
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 109, "");
            }
        } else {
            vlSelf->core_tb__DOT__gap = ((7U == VL_MODDIVS_III(32, vlSelf->core_tb__DOT__accepted, (IData)(0xdU)))
                                          ? 3U : 0U);
            core_tb__DOT____Vrepeat6 = vlSelf->core_tb__DOT__gap;
            while (VL_LTS_III(32, 0U, core_tb__DOT____Vrepeat6)) {
                co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(negedge core_tb.clk)", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   112);
                core_tb__DOT____Vrepeat6 = (core_tb__DOT____Vrepeat6 
                                            - (IData)(1U));
            }
            vlSelf->core_tb__DOT__in_op = (0xfU & vlSelf->core_tb__DOT__op);
            vlSelf->core_tb__DOT__in_task_id = vlSelf->core_tb__DOT__task_no;
            vlSelf->core_tb__DOT__in_tile_id = (0xffU 
                                                & vlSelf->core_tb__DOT__tile_no);
            vlSelf->core_tb__DOT__in_index = (0xffffU 
                                              & vlSelf->core_tb__DOT__idx);
            vlSelf->core_tb__DOT__in_data = vlSelf->core_tb__DOT__word_data;
            vlSelf->core_tb__DOT__in_shift = (0x3fU 
                                              & vlSelf->core_tb__DOT__shift_no);
            vlSelf->core_tb__DOT__in_layer_id = (0xfU 
                                                 & vlSelf->core_tb__DOT__layer_no);
            vlSelf->core_tb__DOT__in_valid = 1U;
            co_await vlSelf->__VtrigSched_h81e7d9f7__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               115);
            while ((1U & (~ (IData)(vlSelf->core_tb__DOT__in_ready)))) {
                co_await vlSelf->__VtrigSched_h81e7d9f7__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge core_tb.clk)", 
                                                                   "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                                   115);
            }
            vlSelf->core_tb__DOT__accepted = ((IData)(1U) 
                                              + vlSelf->core_tb__DOT__accepted);
            co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(negedge core_tb.clk)", 
                                                               "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                               116);
            vlSelf->core_tb__DOT__in_valid = 0U;
        }
    }
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       120);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       120);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       120);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       120);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       120);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       120);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       120);
    co_await vlSelf->__VtrigSched_h81e7d9aa__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge core_tb.clk)", 
                                                       "/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 
                                                       120);
    if (VL_UNLIKELY(((((~ (IData)((0U != vlSelf->core_tb__DOT__expect_fault))) 
                       & ((0U == vlSelf->core_tb__DOT__dones) 
                          | (IData)(vlSelf->core_tb__DOT__fault))) 
                      | (8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) 
                     | ((0U != vlSelf->core_tb__DOT__expect_fault) 
                        & ((~ (IData)(vlSelf->core_tb__DOT__fault)) 
                           | (0U != vlSelf->core_tb__DOT__dones)))))) {
        VL_WRITEF("[%0t] %%Fatal: core_tb.sv:121: Assertion failed in %Ncore_tb: incomplete task\n",
                  64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 121, "");
    }
    VL_FWRITEF(vlSelf->core_tb__DOT__sf,"SUMMARY %0d %0d %0d %0d\n",
               32,vlSelf->core_tb__DOT__cycles,32,vlSelf->core_tb__DOT__accepted,
               32,vlSelf->core_tb__DOT__received,32,
               vlSelf->core_tb__DOT__dones);
    VL_FCLOSE_I(core_tb__DOT__cf); VL_FCLOSE_I(vlSelf->core_tb__DOT__of); VL_FCLOSE_I(vlSelf->core_tb__DOT__sf); VL_WRITEF("RTL_COMPLETE outputs=%0d tasks=%0d fault=%0#\n",
                                                                                32,
                                                                                vlSelf->core_tb__DOT__received,
                                                                                32,
                                                                                vlSelf->core_tb__DOT__dones,
                                                                                1,
                                                                                (IData)(vlSelf->core_tb__DOT__fault));
    VL_FINISH_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 124, "");
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore_tb___024root___dump_triggers__act(Vcore_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vcore_tb___024root___eval_triggers__act(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___eval_triggers__act\n"); );
    // Body
    CData/*0:0*/ __Vtrigcurrexpr_h78b21af8__0;
    __Vtrigcurrexpr_h78b21af8__0 = 0;
    CData/*0:0*/ __Vtrigcurrexpr_h07439b72__0;
    __Vtrigcurrexpr_h07439b72__0 = 0;
    CData/*0:0*/ __Vtrigcurrexpr_h7be2f429__0;
    __Vtrigcurrexpr_h7be2f429__0 = 0;
    CData/*0:0*/ __Vtrigcurrexpr_hf506ef54__0;
    __Vtrigcurrexpr_hf506ef54__0 = 0;
    CData/*0:0*/ __Vtrigcurrexpr_hc537c130__0;
    __Vtrigcurrexpr_hc537c130__0 = 0;
    CData/*0:0*/ __Vtrigcurrexpr_hc537d19d__0;
    __Vtrigcurrexpr_hc537d19d__0 = 0;
    CData/*0:0*/ __Vtrigcurrexpr_hfc024315__0;
    __Vtrigcurrexpr_hfc024315__0 = 0;
    CData/*0:0*/ __Vtrigcurrexpr_h88b84a6b__0;
    __Vtrigcurrexpr_h88b84a6b__0 = 0;
    CData/*0:0*/ __Vtrigcurrexpr_ha6663f55__0;
    __Vtrigcurrexpr_ha6663f55__0 = 0;
    __Vtrigcurrexpr_h78b21af8__0 = ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                    & (IData)(vlSelf->core_tb__DOT__out_last));
    __Vtrigcurrexpr_h07439b72__0 = ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                    & (0x62feU == vlSelf->core_tb__DOT__out_y_index));
    __Vtrigcurrexpr_h7be2f429__0 = ((IData)(vlSelf->core_tb__DOT__core_done) 
                                    | (IData)(vlSelf->core_tb__DOT__fault));
    __Vtrigcurrexpr_hf506ef54__0 = ((4U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                    & (3ULL < vlSelf->core_tb__DOT__dut__DOT__issue_count));
    __Vtrigcurrexpr_hc537c130__0 = (7U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state));
    __Vtrigcurrexpr_hc537d19d__0 = (8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state));
    __Vtrigcurrexpr_hfc024315__0 = ((IData)(vlSelf->core_tb__DOT__dut__DOT__tag_valid) 
                                    & (0U == vlSelf->core_tb__DOT__dut__DOT__tag_g
                                       [0U]));
    __Vtrigcurrexpr_h88b84a6b__0 = ((IData)(vlSelf->core_tb__DOT__dut__DOT__product_valid) 
                                    & (1U < (IData)(vlSelf->core_tb__DOT__dut__DOT__product_k)));
    __Vtrigcurrexpr_ha6663f55__0 = (8U != (IData)(vlSelf->core_tb__DOT__dut__DOT__state));
    vlSelf->__VactTriggered.set(0U, ((~ (IData)(vlSelf->core_tb__DOT__clk)) 
                                     & (IData)(vlSelf->__Vtrigprevexpr___TOP__core_tb__DOT__clk__0)));
    vlSelf->__VactTriggered.set(1U, ((IData)(vlSelf->core_tb__DOT__clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__core_tb__DOT__clk__0))));
    vlSelf->__VactTriggered.set(2U, ((IData)(__Vtrigcurrexpr_h78b21af8__0) 
                                     != (IData)(vlSelf->__Vtrigprevexpr_h78b21af8__0)));
    vlSelf->__VactTriggered.set(3U, ((IData)(__Vtrigcurrexpr_h07439b72__0) 
                                     != (IData)(vlSelf->__Vtrigprevexpr_h07439b72__0)));
    vlSelf->__VactTriggered.set(4U, ((IData)(vlSelf->core_tb__DOT__fault) 
                                     != (IData)(vlSelf->__Vtrigprevexpr___TOP__core_tb__DOT__fault__0)));
    vlSelf->__VactTriggered.set(5U, ((IData)(__Vtrigcurrexpr_h7be2f429__0) 
                                     != (IData)(vlSelf->__Vtrigprevexpr_h7be2f429__0)));
    vlSelf->__VactTriggered.set(6U, ((IData)(__Vtrigcurrexpr_hf506ef54__0) 
                                     != (IData)(vlSelf->__Vtrigprevexpr_hf506ef54__0)));
    vlSelf->__VactTriggered.set(7U, ((IData)(__Vtrigcurrexpr_hc537c130__0) 
                                     != (IData)(vlSelf->__Vtrigprevexpr_hc537c130__0)));
    vlSelf->__VactTriggered.set(8U, ((IData)(__Vtrigcurrexpr_hc537d19d__0) 
                                     != (IData)(vlSelf->__Vtrigprevexpr_hc537d19d__0)));
    vlSelf->__VactTriggered.set(9U, ((IData)(__Vtrigcurrexpr_hfc024315__0) 
                                     != (IData)(vlSelf->__Vtrigprevexpr_hfc024315__0)));
    vlSelf->__VactTriggered.set(0xaU, ((IData)(__Vtrigcurrexpr_h88b84a6b__0) 
                                       != (IData)(vlSelf->__Vtrigprevexpr_h88b84a6b__0)));
    vlSelf->__VactTriggered.set(0xbU, ((IData)(__Vtrigcurrexpr_ha6663f55__0) 
                                       != (IData)(vlSelf->__Vtrigprevexpr_ha6663f55__0)));
    vlSelf->__VactTriggered.set(0xcU, vlSelf->__VdlySched.awaitingCurrentTime());
    vlSelf->__Vtrigprevexpr___TOP__core_tb__DOT__clk__0 
        = vlSelf->core_tb__DOT__clk;
    vlSelf->__Vtrigprevexpr_h78b21af8__0 = __Vtrigcurrexpr_h78b21af8__0;
    vlSelf->__Vtrigprevexpr_h07439b72__0 = __Vtrigcurrexpr_h07439b72__0;
    vlSelf->__Vtrigprevexpr___TOP__core_tb__DOT__fault__0 
        = vlSelf->core_tb__DOT__fault;
    vlSelf->__Vtrigprevexpr_h7be2f429__0 = __Vtrigcurrexpr_h7be2f429__0;
    vlSelf->__Vtrigprevexpr_hf506ef54__0 = __Vtrigcurrexpr_hf506ef54__0;
    vlSelf->__Vtrigprevexpr_hc537c130__0 = __Vtrigcurrexpr_hc537c130__0;
    vlSelf->__Vtrigprevexpr_hc537d19d__0 = __Vtrigcurrexpr_hc537d19d__0;
    vlSelf->__Vtrigprevexpr_hfc024315__0 = __Vtrigcurrexpr_hfc024315__0;
    vlSelf->__Vtrigprevexpr_h88b84a6b__0 = __Vtrigcurrexpr_h88b84a6b__0;
    vlSelf->__Vtrigprevexpr_ha6663f55__0 = __Vtrigcurrexpr_ha6663f55__0;
    if (VL_UNLIKELY((1U & (~ (IData)(vlSelf->__VactDidInit))))) {
        vlSelf->__VactDidInit = 1U;
        vlSelf->__VactTriggered.set(2U, 1U);
        vlSelf->__VactTriggered.set(3U, 1U);
        vlSelf->__VactTriggered.set(4U, 1U);
        vlSelf->__VactTriggered.set(5U, 1U);
        vlSelf->__VactTriggered.set(6U, 1U);
        vlSelf->__VactTriggered.set(7U, 1U);
        vlSelf->__VactTriggered.set(8U, 1U);
        vlSelf->__VactTriggered.set(9U, 1U);
        vlSelf->__VactTriggered.set(0xaU, 1U);
        vlSelf->__VactTriggered.set(0xbU, 1U);
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcore_tb___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vcore_tb___024root___nba_sequent__TOP__0(Vcore_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcore_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore_tb___024root___nba_sequent__TOP__0\n"); );
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
    CData/*3:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__tag_mask__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__tag_mask__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__tag_mask__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__tag_mask__v0 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__tag_task__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__tag_task__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__tag_task__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__tag_task__v0 = 0;
    CData/*5:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__tag_k__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__tag_k__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__tag_k__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__tag_k__v0 = 0;
    CData/*1:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__tag_g__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__tag_g__v0 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__tag_row__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__tag_row__v0 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__tag_tile__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__tag_tile__v0 = 0;
    CData/*0:0*/ __Vdly__core_tb__DOT__dut__DOT__product_valid;
    __Vdly__core_tb__DOT__dut__DOT__product_valid = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v0 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v0 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v1;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v1 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v1;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v1 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v1;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v1 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v2;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v2 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v2;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v2 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v2;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v2 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v3;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v3 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v3;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v3 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v3;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v3 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v4;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v4 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v4;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v4 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v4;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v4 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v5;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v5 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v5;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v5 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v5;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v5 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v6;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v6 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v6;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v6 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v6;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v6 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v7;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v7 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v7;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v7 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v7;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v7 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v8;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v8 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v8;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v8 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v8;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v8 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v9;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v9 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v9;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v9 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v9;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v9 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v10;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v10 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v10;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v10 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v10;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v10 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v11;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v11 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v11;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v11 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v11;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v11 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v12;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v12 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v12;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v12 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v12;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v12 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v13;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v13 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v13;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v13 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v13;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v13 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v14;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v14 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v14;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v14 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v14;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v14 = 0;
    CData/*1:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v15;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v15 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__acc__v15;
    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v15 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v15;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v15 = 0;
    CData/*1:0*/ __Vdly__core_tb__DOT__dut__DOT__product_g;
    __Vdly__core_tb__DOT__dut__DOT__product_g = 0;
    CData/*5:0*/ __Vdly__core_tb__DOT__dut__DOT__product_k;
    __Vdly__core_tb__DOT__dut__DOT__product_k = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v0 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__product__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__product__v0 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v1;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v1 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v2;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v2 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v3;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v3 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v1;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v1 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v1;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v1 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v4;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v4 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__product__v4;
    __Vdlyvset__core_tb__DOT__dut__DOT__product__v4 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v5;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v5 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v6;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v6 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v7;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v7 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v2;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v2 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v2;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v2 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v8;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v8 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__product__v8;
    __Vdlyvset__core_tb__DOT__dut__DOT__product__v8 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v9;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v9 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v10;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v10 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v11;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v11 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v3;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v3 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v3;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v3 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v12;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v12 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__product__v12;
    __Vdlyvset__core_tb__DOT__dut__DOT__product__v12 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v13;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v13 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v14;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v14 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__product__v15;
    __Vdlyvval__core_tb__DOT__dut__DOT__product__v15 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v0 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v0 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v1;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v1 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v1;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v1 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v1;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v1 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v1;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v1 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v2;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v2 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v2;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v2 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v2;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v2 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v2;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v2 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v3;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v3 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v3;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v3 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v3;
    __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v3 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v3;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v3 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v0 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v0 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v1;
    __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v1 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v1;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v1 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v1;
    __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v1 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v1;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v1 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v2;
    __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v2 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v2;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v2 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v2;
    __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v2 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v2;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v2 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v3;
    __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v3 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v3;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v3 = 0;
    QData/*63:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v3;
    __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v3 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v3;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v3 = 0;
    CData/*3:0*/ __Vdly__core_tb__DOT__dut__DOT__state;
    __Vdly__core_tb__DOT__dut__DOT__state = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__x_count;
    __Vdly__core_tb__DOT__dut__DOT__x_count = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__w_count;
    __Vdly__core_tb__DOT__dut__DOT__w_count = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__b_count;
    __Vdly__core_tb__DOT__dut__DOT__b_count = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__next_tile;
    __Vdly__core_tb__DOT__dut__DOT__next_tile = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__committed;
    __Vdly__core_tb__DOT__dut__DOT__committed = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__row0;
    __Vdly__core_tb__DOT__dut__DOT__row0 = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__tile;
    __Vdly__core_tb__DOT__dut__DOT__tile = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__g;
    __Vdly__core_tb__DOT__dut__DOT__g = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__qrow;
    __Vdly__core_tb__DOT__dut__DOT__qrow = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__qcol;
    __Vdly__core_tb__DOT__dut__DOT__qcol = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__out_pos;
    __Vdly__core_tb__DOT__dut__DOT__out_pos = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__req_g;
    __Vdly__core_tb__DOT__dut__DOT__req_g = 0;
    IData/*31:0*/ __Vdly__core_tb__DOT__dut__DOT__req_k;
    __Vdly__core_tb__DOT__dut__DOT__req_k = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v4;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v4 = 0;
    CData/*7:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__biases__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__biases__v0 = 0;
    QData/*47:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__biases__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__biases__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__biases__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__biases__v0 = 0;
    CData/*5:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__result_data__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__result_data__v0 = 0;
    IData/*31:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__result_data__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__result_data__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__result_data__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__result_data__v0 = 0;
    CData/*5:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__result_overflow__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__result_overflow__v0 = 0;
    CData/*0:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__result_overflow__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__result_overflow__v0 = 0;
    CData/*5:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__result_saturated__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__result_saturated__v0 = 0;
    CData/*0:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__result_saturated__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__result_saturated__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v16;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v16 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__acc__v18;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v18 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v8;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v8 = 0;
    SData/*10:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    SData/*10:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    SData/*10:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    SData/*10:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    SData/*11:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    SData/*11:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    SData/*11:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    SData/*11:0*/ __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    CData/*0:0*/ __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 = 0;
    // Body
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__tag_mask__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 0U;
    __Vdly__core_tb__DOT__dut__DOT__product_k = vlSelf->core_tb__DOT__dut__DOT__product_k;
    __Vdly__core_tb__DOT__dut__DOT__product_g = vlSelf->core_tb__DOT__dut__DOT__product_g;
    __Vdly__core_tb__DOT__dut__DOT__product_valid = vlSelf->core_tb__DOT__dut__DOT__product_valid;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v1 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v2 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v3 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v1 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v2 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v3 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v1 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v2 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v3 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v1 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v2 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v3 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v1 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v2 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v3 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__tag_k__v0 = 0U;
    __Vdly__core_tb__DOT__dut__DOT__req_k = vlSelf->core_tb__DOT__dut__DOT__req_k;
    __Vdlyvset__core_tb__DOT__dut__DOT__product__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__product__v4 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__product__v8 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__product__v12 = 0U;
    __Vdly__core_tb__DOT__dut__DOT__qrow = vlSelf->core_tb__DOT__dut__DOT__qrow;
    __Vdlyvset__core_tb__DOT__dut__DOT__biases__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v4 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v8 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__result_data__v0 = 0U;
    __Vdly__core_tb__DOT__dut__DOT__req_g = vlSelf->core_tb__DOT__dut__DOT__req_g;
    __Vdly__core_tb__DOT__dut__DOT__qcol = vlSelf->core_tb__DOT__dut__DOT__qcol;
    __Vdly__core_tb__DOT__dut__DOT__g = vlSelf->core_tb__DOT__dut__DOT__g;
    __Vdly__core_tb__DOT__dut__DOT__tile = vlSelf->core_tb__DOT__dut__DOT__tile;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v0 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v1 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v2 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v3 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v4 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v5 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v6 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v7 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v8 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v9 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v10 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v11 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v12 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v13 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v14 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v15 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v16 = 0U;
    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v18 = 0U;
    __Vdly__core_tb__DOT__dut__DOT__row0 = vlSelf->core_tb__DOT__dut__DOT__row0;
    __Vdly__core_tb__DOT__dut__DOT__out_pos = vlSelf->core_tb__DOT__dut__DOT__out_pos;
    __Vdly__core_tb__DOT__dut__DOT__committed = vlSelf->core_tb__DOT__dut__DOT__committed;
    __Vdly__core_tb__DOT__dut__DOT__b_count = vlSelf->core_tb__DOT__dut__DOT__b_count;
    __Vdly__core_tb__DOT__dut__DOT__w_count = vlSelf->core_tb__DOT__dut__DOT__w_count;
    __Vdly__core_tb__DOT__dut__DOT__x_count = vlSelf->core_tb__DOT__dut__DOT__x_count;
    __Vdly__core_tb__DOT__dut__DOT__next_tile = vlSelf->core_tb__DOT__dut__DOT__next_tile;
    __Vdly__core_tb__DOT__dut__DOT__state = vlSelf->core_tb__DOT__dut__DOT__state;
    __Vdlyvset__core_tb__DOT__dut__DOT__tag_task__v0 = 0U;
    vlSelf->core_tb__DOT__cycles = ((IData)(1U) + vlSelf->core_tb__DOT__cycles);
    if (VL_UNLIKELY(VL_LTS_III(32, 0x4c4b40U, vlSelf->core_tb__DOT__cycles))) {
        VL_WRITEF("[%0t] %%Fatal: core_tb.sv:139: Assertion failed in %Ncore_tb: timeout\n",
                  64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 139, "");
    }
    if (vlSelf->core_tb__DOT__rst_n) {
        if ((((IData)(vlSelf->core_tb__DOT__in_valid) 
              & (IData)(vlSelf->core_tb__DOT__in_ready)) 
             & (0U == (IData)(vlSelf->core_tb__DOT__in_op)))) {
            vlSelf->core_tb__DOT__cold_first = vlSelf->core_tb__DOT__cycles;
        }
        if ((((IData)(vlSelf->core_tb__DOT__dut__DOT__retire_event) 
              & (IData)(vlSelf->core_tb__DOT__dut__DOT__command_ok)) 
             & (6U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op)))) {
            vlSelf->core_tb__DOT__cold_start = vlSelf->core_tb__DOT__cycles;
        }
        if (((IData)(vlSelf->core_tb__DOT__dut__DOT__tag_valid) 
             & (~ (IData)(vlSelf->core_tb__DOT__fault)))) {
            if (VL_UNLIKELY((0xfU != (((IData)(vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__valid_pipe) 
                                       << 3U) | (((IData)(vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__valid_pipe) 
                                                  << 2U) 
                                                 | (((IData)(vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__valid_pipe) 
                                                     << 1U) 
                                                    | (IData)(vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__valid_pipe))))))) {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:147: Assertion failed in %Ncore_tb: PIPE_W_RETURN_WITHOUT_VALID\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name());
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 147, "");
            }
            if (VL_UNLIKELY(((0U == vlSelf->core_tb__DOT__dut__DOT__tag_g
                              [0U]) & (0xfU != (0xfU 
                                                & ((((IData)(vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__valid_pipe) 
                                                     << 3U) 
                                                    | (((IData)(vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__valid_pipe) 
                                                        << 2U) 
                                                       | (((IData)(vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__valid_pipe) 
                                                           << 1U) 
                                                          | (IData)(vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__valid_pipe)))) 
                                                   | (~ 
                                                      vlSelf->core_tb__DOT__dut__DOT__tag_mask
                                                      [0U]))))))) {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:150: Assertion failed in %Ncore_tb: PIPE_X_RETURN_WITHOUT_VALID\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name());
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 150, "");
            }
            if (VL_UNLIKELY((((vlSelf->core_tb__DOT__dut__DOT__tag_task
                               [0U] != vlSelf->core_tb__DOT__dut__DOT__task_id) 
                              | (vlSelf->core_tb__DOT__dut__DOT__tag_row
                                 [0U] != vlSelf->core_tb__DOT__dut__DOT__row0)) 
                             | (vlSelf->core_tb__DOT__dut__DOT__tag_tile
                                [0U] != vlSelf->core_tb__DOT__dut__DOT__tile)))) {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:153: Assertion failed in %Ncore_tb: PIPE_RESPONSE_OWNER\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name());
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 153, "");
            }
        }
        if (VL_UNLIKELY((((IData)(vlSelf->core_tb__DOT__dut__DOT__product_valid) 
                          & (~ (IData)(vlSelf->core_tb__DOT__fault))) 
                         & (((vlSelf->core_tb__DOT__dut__DOT__product_task 
                              != vlSelf->core_tb__DOT__dut__DOT__task_id) 
                             | (vlSelf->core_tb__DOT__dut__DOT__product_row 
                                != vlSelf->core_tb__DOT__dut__DOT__row0)) 
                            | (vlSelf->core_tb__DOT__dut__DOT__product_tile 
                               != vlSelf->core_tb__DOT__dut__DOT__tile))))) {
            VL_WRITEF("[%0t] %%Fatal: core_tb.sv:157: Assertion failed in %Ncore_tb: PIPE_PRODUCT_OWNER\n",
                      64,VL_TIME_UNITED_Q(1000),-9,
                      vlSymsp->name());
            VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 157, "");
        }
        if (VL_UNLIKELY(((IData)(vlSelf->core_tb__DOT__blocked) 
                         & ((8U != (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                            | (0U != ((((vlSelf->core_tb__DOT__payload[0U] 
                                         ^ vlSelf->core_tb__DOT__held[0U]) 
                                        | (vlSelf->core_tb__DOT__payload[1U] 
                                           ^ vlSelf->core_tb__DOT__held[1U])) 
                                       | (vlSelf->core_tb__DOT__payload[2U] 
                                          ^ vlSelf->core_tb__DOT__held[2U])) 
                                      | (vlSelf->core_tb__DOT__payload[3U] 
                                         ^ vlSelf->core_tb__DOT__held[3U]))))))) {
            VL_WRITEF("[%0t] %%Fatal: core_tb.sv:159: Assertion failed in %Ncore_tb: unstable blocked output\n",
                      64,VL_TIME_UNITED_Q(1000),-9,
                      vlSymsp->name());
            VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 159, "");
        }
        vlSelf->core_tb__DOT__blocked = ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                                         & (~ (IData)(vlSelf->core_tb__DOT__out_ready)));
        vlSelf->core_tb__DOT__held[0U] = vlSelf->core_tb__DOT__payload[0U];
        vlSelf->core_tb__DOT__held[1U] = vlSelf->core_tb__DOT__payload[1U];
        vlSelf->core_tb__DOT__held[2U] = vlSelf->core_tb__DOT__payload[2U];
        vlSelf->core_tb__DOT__held[3U] = vlSelf->core_tb__DOT__payload[3U];
        if (VL_UNLIKELY(((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                         & (IData)(vlSelf->core_tb__DOT__out_ready)))) {
            VL_FWRITEF(vlSelf->core_tb__DOT__of,"%08x %08x %08x %b %b %b\n",
                       32,vlSelf->core_tb__DOT__dut__DOT__task_id,
                       32,vlSelf->core_tb__DOT__out_y_index,
                       32,vlSelf->core_tb__DOT__out_data,
                       1,(IData)(vlSelf->core_tb__DOT__out_overflow),
                       1,vlSelf->core_tb__DOT__out_saturated,
                       1,(IData)(vlSelf->core_tb__DOT__out_last));
            vlSelf->core_tb__DOT__received = ((IData)(1U) 
                                              + vlSelf->core_tb__DOT__received);
            if (vlSelf->core_tb__DOT__out_last) {
                vlSelf->core_tb__DOT__cold_last = vlSelf->core_tb__DOT__cycles;
            }
        }
        if (VL_UNLIKELY(((7U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                         & (IData)(vlSelf->core_tb__DOT__dut__DOT__qe_valid)))) {
            VL_FWRITEF(vlSelf->core_tb__DOT__sf,"RAW %0# %0d %012x %012x\n",
                       32,vlSelf->core_tb__DOT__dut__DOT__task_id,
                       32,(((VL_MULS_III(32, (IData)(0x100U), 
                                         (vlSelf->core_tb__DOT__dut__DOT__row0 
                                          + vlSelf->core_tb__DOT__dut__DOT__qrow)) 
                             + VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__tile)) 
                            + VL_MULS_III(32, (IData)(4U), vlSelf->core_tb__DOT__dut__DOT__g)) 
                           + vlSelf->core_tb__DOT__dut__DOT__qcol),
                       48,vlSelf->core_tb__DOT__dut__DOT__acc
                       [(3U & vlSelf->core_tb__DOT__dut__DOT__g)]
                       [(3U & vlSelf->core_tb__DOT__dut__DOT__qrow)]
                       [(3U & vlSelf->core_tb__DOT__dut__DOT__qcol)],
                       48,vlSelf->core_tb__DOT__dut__DOT__unused_qe_raw);
        }
        if (VL_UNLIKELY(vlSelf->core_tb__DOT__core_done)) {
            if (VL_UNLIKELY(((IData)(vlSelf->core_tb__DOT__dut__DOT__q_valid) 
                             | (vlSelf->core_tb__DOT__dut__DOT__input_accepts 
                                != vlSelf->core_tb__DOT__dut__DOT__event_retires)))) {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:176: Assertion failed in %Ncore_tb: DONE_WITH_PENDING_INPUT\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name());
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 176, "");
            }
            vlSelf->core_tb__DOT__dones = ((IData)(1U) 
                                           + vlSelf->core_tb__DOT__dones);
            if (VL_UNLIKELY((((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                              | (0x6300U != (vlSelf->core_tb__DOT__received 
                                             - vlSelf->core_tb__DOT__last_done_received))) 
                             | (IData)(vlSelf->core_tb__DOT__fault)))) {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:177: Assertion failed in %Ncore_tb: early done\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name());
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 177, "");
            }
            vlSelf->core_tb__DOT__last_done_received 
                = vlSelf->core_tb__DOT__received;
            if (VL_UNLIKELY(((VL_GTS_III(32, 0U, vlSelf->core_tb__DOT__cold_first) 
                              | VL_LTS_III(32, vlSelf->core_tb__DOT__cold_start, vlSelf->core_tb__DOT__cold_first)) 
                             | VL_LTS_III(32, vlSelf->core_tb__DOT__cold_last, vlSelf->core_tb__DOT__cold_start)))) {
                VL_WRITEF("[%0t] %%Fatal: core_tb.sv:181: Assertion failed in %Ncore_tb: invalid cold task timestamps\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9,vlSymsp->name());
                VL_STOP_MT("/mnt/d/github/kwt/dv/revd_opt/core_tb.sv", 181, "");
            }
            VL_FWRITEF(vlSelf->core_tb__DOT__sf,"WINDOW %0# %0d %0d %0d %0d %0d\nTASK %0# %0# %0# %0# %0# %0# %0# %0# %0# %0# %0# %0# %0#\nX 0 %0# %0#\nX 1 %0# %0#\nX 2 %0# %0#\nX 3 %0# %0#\nW 0 %0# %0#\nW 1 %0# %0#\nW 2 %0# %0#\nW 3 %0# %0#\n",
                       32,vlSelf->core_tb__DOT__dut__DOT__task_id,
                       32,vlSelf->core_tb__DOT__cold_first,
                       32,vlSelf->core_tb__DOT__cold_start,
                       32,vlSelf->core_tb__DOT__cold_last,
                       32,(vlSelf->core_tb__DOT__cold_last 
                           - vlSelf->core_tb__DOT__cold_first),
                       32,(vlSelf->core_tb__DOT__cold_last 
                           - vlSelf->core_tb__DOT__cold_start),
                       32,vlSelf->core_tb__DOT__dut__DOT__task_id,
                       64,vlSelf->core_tb__DOT__dut__DOT__load_cycles,
                       64,vlSelf->core_tb__DOT__dut__DOT__compute_cycles,
                       64,vlSelf->core_tb__DOT__dut__DOT__output_cycles,
                       64,vlSelf->core_tb__DOT__dut__DOT__wait_cycles,
                       64,vlSelf->core_tb__DOT__dut__DOT__core_cycles,
                       64,vlSelf->core_tb__DOT__dut__DOT__frontend_cycles,
                       64,vlSelf->core_tb__DOT__dut__DOT__issue_count,
                       64,vlSelf->core_tb__DOT__dut__DOT__retire_count,
                       64,vlSelf->core_tb__DOT__dut__DOT__effective_macs,
                       64,vlSelf->core_tb__DOT__dut__DOT__virtual_macs,
                       64,vlSelf->core_tb__DOT__dut__DOT__input_accepts,
                       64,vlSelf->core_tb__DOT__dut__DOT__event_retires,
                       64,vlSelf->core_tb__DOT__dut__DOT__x_reads
                       [0U],64,vlSelf->core_tb__DOT__dut__DOT__x_writes
                       [0U],64,vlSelf->core_tb__DOT__dut__DOT__x_reads
                       [1U],64,vlSelf->core_tb__DOT__dut__DOT__x_writes
                       [1U],64,vlSelf->core_tb__DOT__dut__DOT__x_reads
                       [2U],64,vlSelf->core_tb__DOT__dut__DOT__x_writes
                       [2U],64,vlSelf->core_tb__DOT__dut__DOT__x_reads
                       [3U],64,vlSelf->core_tb__DOT__dut__DOT__x_writes
                       [3U],64,vlSelf->core_tb__DOT__dut__DOT__w_reads
                       [0U],64,vlSelf->core_tb__DOT__dut__DOT__w_writes
                       [0U],64,vlSelf->core_tb__DOT__dut__DOT__w_reads
                       [1U],64,vlSelf->core_tb__DOT__dut__DOT__w_writes
                       [1U],64,vlSelf->core_tb__DOT__dut__DOT__w_reads
                       [2U],64,vlSelf->core_tb__DOT__dut__DOT__w_writes
                       [2U],64,vlSelf->core_tb__DOT__dut__DOT__w_reads
                       [3U],64,vlSelf->core_tb__DOT__dut__DOT__w_writes
                       [3U]);
        }
    } else {
        vlSelf->core_tb__DOT__blocked = 0U;
    }
    if (vlSelf->core_tb__DOT__rst_n) {
        if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__wr_en)))) {
            if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__rd_en) {
                __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 
                    = ((0x63fU >= (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr))
                        ? vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem
                       [vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr]
                        : 0U);
                __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 = 1U;
            }
        }
        if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__wr_en)))) {
            if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__rd_en) {
                __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 
                    = ((0x63fU >= (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr))
                        ? vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem
                       [vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr]
                        : 0U);
                __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 = 1U;
            }
        }
        if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__wr_en)))) {
            if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__rd_en) {
                __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 
                    = ((0x63fU >= (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr))
                        ? vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem
                       [vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr]
                        : 0U);
                __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 = 1U;
            }
        }
        if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__wr_en)))) {
            if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__rd_en) {
                __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 
                    = ((0x63fU >= (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr))
                        ? vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem
                       [vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr]
                        : 0U);
                __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 = 1U;
            }
        }
        if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__3__KET____DOT__ram__wr_en)))) {
            if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en) {
                __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 
                    = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem
                    [vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr];
                __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0 = 1U;
            }
        }
        if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__2__KET____DOT__ram__wr_en)))) {
            if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en) {
                __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 
                    = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem
                    [vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr];
                __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0 = 1U;
            }
        }
        if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__1__KET____DOT__ram__wr_en)))) {
            if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en) {
                __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 
                    = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem
                    [vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr];
                __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0 = 1U;
            }
        }
        if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__wr_en)))) {
            if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en) {
                __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 
                    = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem
                    [vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr];
                __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0 = 1U;
            }
        }
        if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en) {
            __Vdlyvval__core_tb__DOT__dut__DOT__tag_mask__v0 
                = ((VL_GTS_III(32, 0x63U, ((IData)(3U) 
                                           + vlSelf->core_tb__DOT__dut__DOT__row0)) 
                    << 3U) | ((VL_GTS_III(32, 0x63U, 
                                          ((IData)(2U) 
                                           + vlSelf->core_tb__DOT__dut__DOT__row0)) 
                               << 2U) | ((VL_GTS_III(32, 0x63U, 
                                                     ((IData)(1U) 
                                                      + vlSelf->core_tb__DOT__dut__DOT__row0)) 
                                          << 1U) | 
                                         VL_GTS_III(32, 0x63U, vlSelf->core_tb__DOT__dut__DOT__row0))));
            __Vdlyvset__core_tb__DOT__dut__DOT__tag_mask__v0 = 1U;
            __Vdlyvval__core_tb__DOT__dut__DOT__tag_task__v0 
                = vlSelf->core_tb__DOT__dut__DOT__task_id;
            __Vdlyvset__core_tb__DOT__dut__DOT__tag_task__v0 = 1U;
            __Vdlyvval__core_tb__DOT__dut__DOT__tag_k__v0 
                = (0x3fU & vlSelf->core_tb__DOT__dut__DOT__req_k);
            __Vdlyvset__core_tb__DOT__dut__DOT__tag_k__v0 = 1U;
            __Vdlyvval__core_tb__DOT__dut__DOT__tag_g__v0 
                = (3U & vlSelf->core_tb__DOT__dut__DOT__req_g);
            __Vdlyvval__core_tb__DOT__dut__DOT__tag_row__v0 
                = vlSelf->core_tb__DOT__dut__DOT__row0;
            __Vdlyvval__core_tb__DOT__dut__DOT__tag_tile__v0 
                = vlSelf->core_tb__DOT__dut__DOT__tile;
            __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v0 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__w_reads
                   [0U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v0 = 1U;
            __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v1 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__w_reads
                   [1U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v1 = 1U;
            __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v2 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__w_reads
                   [2U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v2 = 1U;
            __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v3 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__w_reads
                   [3U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v3 = 1U;
        }
        if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__3__KET____DOT__ram__wr_en) {
            __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0 
                = (0xffffU & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_data));
            __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 1U;
            __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0 
                = vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr;
        }
        if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__2__KET____DOT__ram__wr_en) {
            __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0 
                = (0xffffU & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_data));
            __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 1U;
            __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0 
                = vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr;
        }
        if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__1__KET____DOT__ram__wr_en) {
            __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0 
                = (0xffffU & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_data));
            __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 1U;
            __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0 
                = vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr;
        }
        if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__wr_en) {
            __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0 
                = (0xffffU & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_data));
            __Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 1U;
            __Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0 
                = vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__addr;
        }
        if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__wr_en) {
            vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0 
                = (0xffffU & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_data));
            if ((0x63fU >= (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr))) {
                __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0 
                    = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0;
                __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0 = 1U;
                __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0 
                    = vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr;
            }
        }
        if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__wr_en) {
            vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0 
                = (0xffffU & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_data));
            if ((0x63fU >= (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr))) {
                __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0 
                    = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0;
                __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0 = 1U;
                __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0 
                    = vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr;
            }
        }
        if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__wr_en) {
            vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0 
                = (0xffffU & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_data));
            if ((0x63fU >= (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr))) {
                __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0 
                    = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0;
                __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0 = 1U;
                __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0 
                    = vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr;
            }
        }
        if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__wr_en) {
            vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0 
                = (0xffffU & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_data));
            if ((0x63fU >= (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr))) {
                __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0 
                    = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT____Vlvbound_h8bbbb6df__0;
                __Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0 = 1U;
                __Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0 
                    = vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__addr;
            }
        }
        vlSelf->core_tb__DOT__core_done = 0U;
        if ((0U != (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
            vlSelf->core_tb__DOT__dut__DOT__frontend_cycles 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__frontend_cycles);
        }
        if ((1U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
            vlSelf->core_tb__DOT__dut__DOT__load_cycles 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__load_cycles);
        }
        if (vlSelf->core_tb__DOT__dut__DOT__core_active) {
            vlSelf->core_tb__DOT__dut__DOT__core_cycles 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__core_cycles);
        }
        if (((2U <= (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
             & (7U >= (IData)(vlSelf->core_tb__DOT__dut__DOT__state)))) {
            vlSelf->core_tb__DOT__dut__DOT__compute_cycles 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__compute_cycles);
        }
        if ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
            vlSelf->core_tb__DOT__dut__DOT__output_cycles 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__output_cycles);
        }
        if (((4U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
             | ((8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)) 
                & (~ (IData)(vlSelf->core_tb__DOT__out_ready))))) {
            vlSelf->core_tb__DOT__dut__DOT__wait_cycles 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__wait_cycles);
        }
        vlSelf->core_tb__DOT__dut__DOT__tag_valid = vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en;
        __Vdly__core_tb__DOT__dut__DOT__product_valid = 0U;
        if ((1U & (IData)(vlSelf->core_tb__DOT__dut__DOT__x_rd))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v0 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__x_reads
                   [0U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v0 = 1U;
        }
        if ((1U & (IData)(vlSelf->core_tb__DOT__dut__DOT__x_wr))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v0 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__x_writes
                   [0U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v0 = 1U;
        }
        if ((2U & (IData)(vlSelf->core_tb__DOT__dut__DOT__x_rd))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v1 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__x_reads
                   [1U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v1 = 1U;
        }
        if ((2U & (IData)(vlSelf->core_tb__DOT__dut__DOT__x_wr))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v1 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__x_writes
                   [1U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v1 = 1U;
        }
        if ((4U & (IData)(vlSelf->core_tb__DOT__dut__DOT__x_rd))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v2 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__x_reads
                   [2U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v2 = 1U;
        }
        if ((4U & (IData)(vlSelf->core_tb__DOT__dut__DOT__x_wr))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v2 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__x_writes
                   [2U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v2 = 1U;
        }
        if ((8U & (IData)(vlSelf->core_tb__DOT__dut__DOT__x_rd))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v3 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__x_reads
                   [3U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v3 = 1U;
        }
        if ((8U & (IData)(vlSelf->core_tb__DOT__dut__DOT__x_wr))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v3 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__x_writes
                   [3U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v3 = 1U;
        }
        if ((1U & (IData)(vlSelf->core_tb__DOT__dut__DOT__w_wr))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v0 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__w_writes
                   [0U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v0 = 1U;
        }
        if ((2U & (IData)(vlSelf->core_tb__DOT__dut__DOT__w_wr))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v1 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__w_writes
                   [1U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v1 = 1U;
        }
        if ((4U & (IData)(vlSelf->core_tb__DOT__dut__DOT__w_wr))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v2 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__w_writes
                   [2U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v2 = 1U;
        }
        if ((8U & (IData)(vlSelf->core_tb__DOT__dut__DOT__w_wr))) {
            __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v3 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__w_writes
                   [3U]);
            __Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v3 = 1U;
        }
        if ((1U & ((~ (IData)(vlSelf->core_tb__DOT__fault)) 
                   & (~ ((IData)(vlSelf->core_tb__DOT__dut__DOT__retire_event) 
                         & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT__command_ok))))))) {
            if (vlSelf->core_tb__DOT__dut__DOT__product_valid) {
                if ((1U & (IData)(vlSelf->core_tb__DOT__dut__DOT__product_mask))) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v0 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [0U]
                                                [0U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [0U]
                                                                                [0U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [0U]
                                                                     [0U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v0 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v0 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v1 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [0U]
                                                [1U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [0U]
                                                                                [1U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [0U]
                                                                     [1U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v1 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v1 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v2 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [0U]
                                                [2U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [0U]
                                                                                [2U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [0U]
                                                                     [2U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v2 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v2 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v3 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [0U]
                                                [3U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [0U]
                                                                                [3U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [0U]
                                                                     [3U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v3 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v3 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                }
                vlSelf->core_tb__DOT__dut__DOT__retire_count 
                    = (1ULL + vlSelf->core_tb__DOT__dut__DOT__retire_count);
                vlSelf->core_tb__DOT__dut__DOT__effective_macs 
                    = (vlSelf->core_tb__DOT__dut__DOT__effective_macs 
                       + VL_MULS_QQQ(64, 4ULL, VL_EXTENDS_QI(64,32, vlSelf->core_tb__DOT__dut__DOT__effective_rows)));
                vlSelf->core_tb__DOT__dut__DOT__virtual_macs 
                    = (vlSelf->core_tb__DOT__dut__DOT__virtual_macs 
                       + VL_EXTENDS_QI(64,32, VL_MULS_III(32, (IData)(4U), 
                                                          ((IData)(4U) 
                                                           - vlSelf->core_tb__DOT__dut__DOT__effective_rows))));
                if ((2U & (IData)(vlSelf->core_tb__DOT__dut__DOT__product_mask))) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v4 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [1U]
                                                [0U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [1U]
                                                                                [0U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [1U]
                                                                     [0U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v4 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v4 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v5 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [1U]
                                                [1U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [1U]
                                                                                [1U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [1U]
                                                                     [1U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v5 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v5 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v6 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [1U]
                                                [2U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [1U]
                                                                                [2U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [1U]
                                                                     [2U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v6 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v6 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v7 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [1U]
                                                [3U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [1U]
                                                                                [3U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [1U]
                                                                     [3U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v7 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v7 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                }
                if ((4U & (IData)(vlSelf->core_tb__DOT__dut__DOT__product_mask))) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v8 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [2U]
                                                [0U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [2U]
                                                                                [0U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [2U]
                                                                     [0U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v8 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v8 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v9 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [2U]
                                                [1U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [2U]
                                                                                [1U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [2U]
                                                                     [1U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v9 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v9 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v10 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [2U]
                                                [2U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [2U]
                                                                                [2U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [2U]
                                                                     [2U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v10 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v10 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v11 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [2U]
                                                [3U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [2U]
                                                                                [3U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [2U]
                                                                     [3U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v11 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v11 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                }
                if ((8U & (IData)(vlSelf->core_tb__DOT__dut__DOT__product_mask))) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v12 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [3U]
                                                [0U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [3U]
                                                                                [0U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [3U]
                                                                     [0U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v12 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v12 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v13 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [3U]
                                                [1U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [3U]
                                                                                [1U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [3U]
                                                                     [1U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v13 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v13 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v14 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [3U]
                                                [2U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [3U]
                                                                                [2U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [3U]
                                                                     [2U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v14 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v14 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                    __Vdlyvval__core_tb__DOT__dut__DOT__acc__v15 
                        = (0xffffffffffffULL & (vlSelf->core_tb__DOT__dut__DOT__acc
                                                [vlSelf->core_tb__DOT__dut__DOT__product_g]
                                                [3U]
                                                [3U] 
                                                + (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (- (IData)(
                                                                                (vlSelf->core_tb__DOT__dut__DOT__product
                                                                                [3U]
                                                                                [3U] 
                                                                                >> 0x1fU)))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->core_tb__DOT__dut__DOT__product
                                                                     [3U]
                                                                     [3U])))));
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v15 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v15 
                        = vlSelf->core_tb__DOT__dut__DOT__product_g;
                }
            }
            if (vlSelf->core_tb__DOT__dut__DOT__returned) {
                vlSelf->core_tb__DOT__dut__DOT__issue_count 
                    = (1ULL + vlSelf->core_tb__DOT__dut__DOT__issue_count);
                __Vdly__core_tb__DOT__dut__DOT__product_valid = 1U;
                __Vdly__core_tb__DOT__dut__DOT__product_g 
                    = vlSelf->core_tb__DOT__dut__DOT__tag_g
                    [0U];
                __Vdly__core_tb__DOT__dut__DOT__product_k 
                    = vlSelf->core_tb__DOT__dut__DOT__tag_k
                    [0U];
                vlSelf->core_tb__DOT__dut__DOT__product_mask 
                    = vlSelf->core_tb__DOT__dut__DOT__tag_mask
                    [0U];
                vlSelf->core_tb__DOT__dut__DOT__product_task 
                    = vlSelf->core_tb__DOT__dut__DOT__tag_task
                    [0U];
                vlSelf->core_tb__DOT__dut__DOT__product_row 
                    = vlSelf->core_tb__DOT__dut__DOT__tag_row
                    [0U];
                vlSelf->core_tb__DOT__dut__DOT__product_tile 
                    = vlSelf->core_tb__DOT__dut__DOT__tag_tile
                    [0U];
                if (((0U == vlSelf->core_tb__DOT__dut__DOT__tag_g
                      [0U]) & vlSelf->core_tb__DOT__dut__DOT__tag_mask
                     [0U])) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v0 
                        = vlSelf->core_tb__DOT__dut__DOT__x_data
                        [0U];
                    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v0 = 1U;
                }
                if ((1U & vlSelf->core_tb__DOT__dut__DOT__tag_mask
                     [0U])) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v0 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [0U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [0U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [0U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v1 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [0U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [0U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [1U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v2 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [0U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [0U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [2U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v3 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [0U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [0U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [3U]));
                } else {
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v0 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v1 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v2 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v3 = 0U;
                }
                __Vdlyvset__core_tb__DOT__dut__DOT__product__v0 = 1U;
                if (((0U == vlSelf->core_tb__DOT__dut__DOT__tag_g
                      [0U]) & (vlSelf->core_tb__DOT__dut__DOT__tag_mask
                               [0U] >> 1U))) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v1 
                        = vlSelf->core_tb__DOT__dut__DOT__x_data
                        [1U];
                    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v1 = 1U;
                }
                if ((2U & vlSelf->core_tb__DOT__dut__DOT__tag_mask
                     [0U])) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v4 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [1U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [1U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [0U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v5 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [1U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [1U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [1U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v6 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [1U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [1U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [2U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v7 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [1U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [1U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [3U]));
                } else {
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v4 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v5 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v6 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v7 = 0U;
                }
                __Vdlyvset__core_tb__DOT__dut__DOT__product__v4 = 1U;
                if (((0U == vlSelf->core_tb__DOT__dut__DOT__tag_g
                      [0U]) & (vlSelf->core_tb__DOT__dut__DOT__tag_mask
                               [0U] >> 2U))) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v2 
                        = vlSelf->core_tb__DOT__dut__DOT__x_data
                        [2U];
                    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v2 = 1U;
                }
                if ((4U & vlSelf->core_tb__DOT__dut__DOT__tag_mask
                     [0U])) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v8 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [2U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [2U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [0U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v9 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [2U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [2U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [1U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v10 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [2U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [2U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [2U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v11 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [2U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [2U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [3U]));
                } else {
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v8 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v9 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v10 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v11 = 0U;
                }
                __Vdlyvset__core_tb__DOT__dut__DOT__product__v8 = 1U;
                if (((0U == vlSelf->core_tb__DOT__dut__DOT__tag_g
                      [0U]) & (vlSelf->core_tb__DOT__dut__DOT__tag_mask
                               [0U] >> 3U))) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v3 
                        = vlSelf->core_tb__DOT__dut__DOT__x_data
                        [3U];
                    __Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v3 = 1U;
                }
                if ((8U & vlSelf->core_tb__DOT__dut__DOT__tag_mask
                     [0U])) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v12 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [3U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [3U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [0U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v13 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [3U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [3U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [1U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v14 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [3U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [3U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [2U]));
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v15 
                        = VL_MULS_III(32, VL_EXTENDS_II(32,16, 
                                                        ((0U 
                                                          == 
                                                          vlSelf->core_tb__DOT__dut__DOT__tag_g
                                                          [0U])
                                                          ? 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_data
                                                         [3U]
                                                          : 
                                                         vlSelf->core_tb__DOT__dut__DOT__x_hold
                                                         [3U])), 
                                      VL_EXTENDS_II(32,16, 
                                                    vlSelf->core_tb__DOT__dut__DOT__w_data
                                                    [3U]));
                } else {
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v12 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v13 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v14 = 0U;
                    __Vdlyvval__core_tb__DOT__dut__DOT__product__v15 = 0U;
                }
                __Vdlyvset__core_tb__DOT__dut__DOT__product__v12 = 1U;
            }
        }
        if (((IData)(vlSelf->core_tb__DOT__in_valid) 
             & (IData)(vlSelf->core_tb__DOT__in_ready))) {
            vlSelf->core_tb__DOT__dut__DOT__q_layer 
                = vlSelf->core_tb__DOT__in_layer_id;
            vlSelf->core_tb__DOT__dut__DOT__q_tile 
                = vlSelf->core_tb__DOT__in_tile_id;
            vlSelf->core_tb__DOT__dut__DOT__q_index 
                = vlSelf->core_tb__DOT__in_index;
        }
        if (vlSelf->core_tb__DOT__dut__DOT__retire_event) {
            vlSelf->core_tb__DOT__dut__DOT__q_valid = 0U;
        }
        if (((IData)(vlSelf->core_tb__DOT__in_valid) 
             & (IData)(vlSelf->core_tb__DOT__in_ready))) {
            vlSelf->core_tb__DOT__dut__DOT__q_valid = 1U;
            vlSelf->core_tb__DOT__dut__DOT__input_accepts 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__input_accepts);
        }
        if (vlSelf->core_tb__DOT__dut__DOT__retire_event) {
            vlSelf->core_tb__DOT__dut__DOT__event_retires 
                = (1ULL + vlSelf->core_tb__DOT__dut__DOT__event_retires);
            if (vlSelf->core_tb__DOT__dut__DOT__command_ok) {
                if ((0U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))) {
                    vlSelf->core_tb__DOT__dut__DOT__issue_count = 0ULL;
                    vlSelf->core_tb__DOT__dut__DOT__retire_count = 0ULL;
                    vlSelf->core_tb__DOT__dut__DOT__effective_macs = 0ULL;
                    vlSelf->core_tb__DOT__dut__DOT__virtual_macs = 0ULL;
                    __Vdly__core_tb__DOT__dut__DOT__state = 1U;
                    vlSelf->core_tb__DOT__dut__DOT__task_id 
                        = vlSelf->core_tb__DOT__dut__DOT__q_task;
                    vlSelf->core_tb__DOT__dut__DOT__shift 
                        = vlSelf->core_tb__DOT__dut__DOT__q_shift;
                    __Vdly__core_tb__DOT__dut__DOT__x_count = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__w_count = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__b_count = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__next_tile = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__committed = 0U;
                    vlSelf->core_tb__DOT__dut__DOT__tile_open = 0U;
                    vlSelf->core_tb__DOT__dut__DOT__core_active = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__row0 = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__tile = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__g = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__qrow = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__qcol = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__out_pos = 0U;
                    vlSelf->core_tb__DOT__dut__DOT__product_mask = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__req_g = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__req_k = 0U;
                    vlSelf->core_tb__DOT__dut__DOT__tag_valid = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__product_valid = 0U;
                    vlSelf->core_tb__DOT__dut__DOT__load_cycles = 0ULL;
                    vlSelf->core_tb__DOT__dut__DOT__compute_cycles = 0ULL;
                    vlSelf->core_tb__DOT__dut__DOT__output_cycles = 0ULL;
                    vlSelf->core_tb__DOT__dut__DOT__wait_cycles = 0ULL;
                    vlSelf->core_tb__DOT__dut__DOT__core_cycles = 0ULL;
                    vlSelf->core_tb__DOT__dut__DOT__frontend_cycles = 0ULL;
                    vlSelf->core_tb__DOT__dut__DOT__input_accepts 
                        = (1ULL + (((IData)(vlSelf->core_tb__DOT__in_valid) 
                                    & (IData)(vlSelf->core_tb__DOT__in_ready))
                                    ? 1ULL : 0ULL));
                    vlSelf->core_tb__DOT__dut__DOT__event_retires = 1ULL;
                    __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v4 = 1U;
                } else if ((1U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))) {
                    __Vdly__core_tb__DOT__dut__DOT__x_count 
                        = ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__x_count);
                } else if ((2U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))) {
                    vlSelf->core_tb__DOT__dut__DOT__tile_open = 1U;
                    __Vdly__core_tb__DOT__dut__DOT__w_count = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__b_count = 0U;
                } else if ((3U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))) {
                    __Vdly__core_tb__DOT__dut__DOT__w_count 
                        = ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__w_count);
                } else if ((4U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))) {
                    __Vdlyvval__core_tb__DOT__dut__DOT__biases__v0 
                        = vlSelf->core_tb__DOT__dut__DOT__q_data;
                    __Vdlyvset__core_tb__DOT__dut__DOT__biases__v0 = 1U;
                    __Vdlyvdim0__core_tb__DOT__dut__DOT__biases__v0 
                        = (0xffU & (VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__next_tile) 
                                    + vlSelf->core_tb__DOT__dut__DOT__b_count));
                    __Vdly__core_tb__DOT__dut__DOT__b_count 
                        = ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__b_count);
                } else if ((5U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))) {
                    __Vdly__core_tb__DOT__dut__DOT__next_tile 
                        = ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__next_tile);
                    __Vdly__core_tb__DOT__dut__DOT__committed 
                        = ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__committed);
                    vlSelf->core_tb__DOT__dut__DOT__tile_open = 0U;
                } else if ((6U == (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op))) {
                    __Vdly__core_tb__DOT__dut__DOT__state = 2U;
                    __Vdly__core_tb__DOT__dut__DOT__row0 = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__tile = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__g = 0U;
                    vlSelf->core_tb__DOT__dut__DOT__core_active = 1U;
                }
            } else {
                vlSelf->core_tb__DOT__error_code = 
                    (0xffU & ((IData)(0x10U) + (IData)(vlSelf->core_tb__DOT__dut__DOT__q_op)));
            }
        }
        if (((IData)(vlSelf->core_tb__DOT__in_valid) 
             & (IData)(vlSelf->core_tb__DOT__in_ready))) {
            vlSelf->core_tb__DOT__dut__DOT__q_task 
                = vlSelf->core_tb__DOT__in_task_id;
            vlSelf->core_tb__DOT__dut__DOT__q_shift 
                = vlSelf->core_tb__DOT__in_shift;
            vlSelf->core_tb__DOT__dut__DOT__q_data 
                = vlSelf->core_tb__DOT__in_data;
            vlSelf->core_tb__DOT__dut__DOT__q_op = vlSelf->core_tb__DOT__in_op;
        }
        if ((1U & ((~ (IData)(vlSelf->core_tb__DOT__fault)) 
                   & (~ ((IData)(vlSelf->core_tb__DOT__dut__DOT__retire_event) 
                         & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT__command_ok))))))) {
            if ((8U & (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                if ((1U & (~ ((IData)(vlSelf->core_tb__DOT__dut__DOT__state) 
                              >> 2U)))) {
                    if ((1U & (~ ((IData)(vlSelf->core_tb__DOT__dut__DOT__state) 
                                  >> 1U)))) {
                        if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT__state)))) {
                            if (vlSelf->core_tb__DOT__out_ready) {
                                if (VL_LTS_III(32, 
                                               ((IData)(1U) 
                                                + vlSelf->core_tb__DOT__dut__DOT__out_pos), 
                                               VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__effective_rows))) {
                                    __Vdly__core_tb__DOT__dut__DOT__out_pos 
                                        = ((IData)(1U) 
                                           + vlSelf->core_tb__DOT__dut__DOT__out_pos);
                                } else if (VL_GTS_III(32, 0x63U, 
                                                      ((IData)(4U) 
                                                       + vlSelf->core_tb__DOT__dut__DOT__row0))) {
                                    __Vdly__core_tb__DOT__dut__DOT__row0 
                                        = ((IData)(4U) 
                                           + vlSelf->core_tb__DOT__dut__DOT__row0);
                                    __Vdly__core_tb__DOT__dut__DOT__g = 0U;
                                    __Vdly__core_tb__DOT__dut__DOT__state = 2U;
                                } else if (VL_GTS_III(32, 0x10U, 
                                                      ((IData)(1U) 
                                                       + vlSelf->core_tb__DOT__dut__DOT__tile))) {
                                    __Vdly__core_tb__DOT__dut__DOT__tile 
                                        = ((IData)(1U) 
                                           + vlSelf->core_tb__DOT__dut__DOT__tile);
                                    __Vdly__core_tb__DOT__dut__DOT__row0 = 0U;
                                    __Vdly__core_tb__DOT__dut__DOT__g = 0U;
                                    __Vdly__core_tb__DOT__dut__DOT__state = 2U;
                                } else {
                                    __Vdly__core_tb__DOT__dut__DOT__state = 0U;
                                    vlSelf->core_tb__DOT__dut__DOT__core_active = 0U;
                                    vlSelf->core_tb__DOT__core_done = 1U;
                                }
                            }
                        }
                    }
                }
            } else if ((4U & (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                if ((2U & (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                    if ((1U & (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                        if (vlSelf->core_tb__DOT__dut__DOT__qe_valid) {
                            __Vdlyvval__core_tb__DOT__dut__DOT__result_data__v0 
                                = vlSelf->core_tb__DOT__dut__DOT__qe_data;
                            __Vdlyvset__core_tb__DOT__dut__DOT__result_data__v0 = 1U;
                            __Vdlyvdim0__core_tb__DOT__dut__DOT__result_data__v0 
                                = (0x3fU & ((VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__qrow) 
                                             + VL_MULS_III(32, (IData)(4U), vlSelf->core_tb__DOT__dut__DOT__g)) 
                                            + vlSelf->core_tb__DOT__dut__DOT__qcol));
                            __Vdlyvval__core_tb__DOT__dut__DOT__result_overflow__v0 
                                = vlSelf->core_tb__DOT__dut__DOT__qe_overflow;
                            __Vdlyvdim0__core_tb__DOT__dut__DOT__result_overflow__v0 
                                = (0x3fU & ((VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__qrow) 
                                             + VL_MULS_III(32, (IData)(4U), vlSelf->core_tb__DOT__dut__DOT__g)) 
                                            + vlSelf->core_tb__DOT__dut__DOT__qcol));
                            __Vdlyvval__core_tb__DOT__dut__DOT__result_saturated__v0 
                                = vlSelf->core_tb__DOT__dut__DOT__qe_saturated;
                            __Vdlyvdim0__core_tb__DOT__dut__DOT__result_saturated__v0 
                                = (0x3fU & ((VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__qrow) 
                                             + VL_MULS_III(32, (IData)(4U), vlSelf->core_tb__DOT__dut__DOT__g)) 
                                            + vlSelf->core_tb__DOT__dut__DOT__qcol));
                            if (VL_GTS_III(32, 3U, vlSelf->core_tb__DOT__dut__DOT__qcol)) {
                                __Vdly__core_tb__DOT__dut__DOT__qcol 
                                    = ((IData)(1U) 
                                       + vlSelf->core_tb__DOT__dut__DOT__qcol);
                                __Vdly__core_tb__DOT__dut__DOT__state = 6U;
                            } else if (VL_LTS_III(32, 
                                                  ((IData)(1U) 
                                                   + vlSelf->core_tb__DOT__dut__DOT__qrow), vlSelf->core_tb__DOT__dut__DOT__effective_rows)) {
                                __Vdly__core_tb__DOT__dut__DOT__qrow 
                                    = ((IData)(1U) 
                                       + vlSelf->core_tb__DOT__dut__DOT__qrow);
                                __Vdly__core_tb__DOT__dut__DOT__qcol = 0U;
                                __Vdly__core_tb__DOT__dut__DOT__state = 6U;
                            } else if (VL_GTS_III(32, 3U, vlSelf->core_tb__DOT__dut__DOT__g)) {
                                __Vdly__core_tb__DOT__dut__DOT__g 
                                    = ((IData)(1U) 
                                       + vlSelf->core_tb__DOT__dut__DOT__g);
                                __Vdly__core_tb__DOT__dut__DOT__qrow = 0U;
                                __Vdly__core_tb__DOT__dut__DOT__qcol = 0U;
                                __Vdly__core_tb__DOT__dut__DOT__state = 6U;
                            } else {
                                __Vdly__core_tb__DOT__dut__DOT__out_pos = 0U;
                                __Vdly__core_tb__DOT__dut__DOT__state = 8U;
                            }
                        }
                    } else if (vlSelf->core_tb__DOT__dut__DOT__qe_ready) {
                        __Vdly__core_tb__DOT__dut__DOT__state = 7U;
                    }
                } else if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT__state)))) {
                    if ((((IData)(vlSelf->core_tb__DOT__dut__DOT__product_valid) 
                          & (0x3fU == (IData)(vlSelf->core_tb__DOT__dut__DOT__product_k))) 
                         & (3U == (IData)(vlSelf->core_tb__DOT__dut__DOT__product_g)))) {
                        __Vdly__core_tb__DOT__dut__DOT__g = 0U;
                        __Vdly__core_tb__DOT__dut__DOT__qrow = 0U;
                        __Vdly__core_tb__DOT__dut__DOT__qcol = 0U;
                        __Vdly__core_tb__DOT__dut__DOT__state = 6U;
                    }
                }
            } else if ((2U & (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                if ((1U & (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) {
                    if (VL_GTS_III(32, 3U, vlSelf->core_tb__DOT__dut__DOT__req_g)) {
                        __Vdly__core_tb__DOT__dut__DOT__req_g 
                            = ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__req_g);
                    } else {
                        __Vdly__core_tb__DOT__dut__DOT__req_g = 0U;
                        if ((0x3fU == vlSelf->core_tb__DOT__dut__DOT__req_k)) {
                            __Vdly__core_tb__DOT__dut__DOT__state = 4U;
                        } else {
                            __Vdly__core_tb__DOT__dut__DOT__req_k 
                                = ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__req_k);
                        }
                    }
                } else {
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v16 = 1U;
                    __Vdly__core_tb__DOT__dut__DOT__req_g = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__req_k = 0U;
                    __Vdly__core_tb__DOT__dut__DOT__state = 3U;
                    __Vdlyvset__core_tb__DOT__dut__DOT__acc__v18 = 1U;
                }
            }
        }
        if (vlSelf->core_tb__DOT__dut__DOT__qe_ready) {
            if (vlSelf->core_tb__DOT__dut__DOT____Vcellinp__quant__in_valid) {
                vlSelf->core_tb__DOT__dut__DOT__unused_qe_raw 
                    = vlSelf->core_tb__DOT__dut__DOT__quant__DOT__clipped;
                vlSelf->core_tb__DOT__dut__DOT__qe_data 
                    = vlSelf->core_tb__DOT__dut__DOT__quant__DOT__result;
                vlSelf->core_tb__DOT__dut__DOT__qe_overflow 
                    = vlSelf->core_tb__DOT__dut__DOT__quant__DOT__overflow;
                vlSelf->core_tb__DOT__dut__DOT__qe_saturated 
                    = vlSelf->core_tb__DOT__dut__DOT__quant__DOT__saturated;
                vlSelf->core_tb__DOT__dut__DOT__qe_valid = 1U;
            } else {
                vlSelf->core_tb__DOT__dut__DOT__qe_valid = 0U;
            }
        }
        if ((((((IData)(vlSelf->core_tb__DOT__fault) 
                | ((IData)(vlSelf->core_tb__DOT__dut__DOT__retire_event) 
                   & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT__command_ok)))) 
               & (8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state))) 
              & (IData)(vlSelf->core_tb__DOT__out_ready)) 
             & (IData)(vlSelf->core_tb__DOT__out_valid))) {
            if (VL_LTS_III(32, ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__out_pos), 
                           VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__effective_rows))) {
                __Vdly__core_tb__DOT__dut__DOT__out_pos 
                    = ((IData)(1U) + vlSelf->core_tb__DOT__dut__DOT__out_pos);
            } else {
                __Vdly__core_tb__DOT__dut__DOT__state = 0U;
            }
        }
        if (vlSelf->core_tb__DOT__dut__DOT__retire_event) {
            if ((1U & (~ (IData)(vlSelf->core_tb__DOT__dut__DOT__command_ok)))) {
                vlSelf->core_tb__DOT__fault = 1U;
            }
        }
    } else {
        vlSelf->core_tb__DOT__dut__DOT__unused_qe_raw = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__q_valid = 0U;
        __Vdly__core_tb__DOT__dut__DOT__g = 0U;
        __Vdly__core_tb__DOT__dut__DOT__qrow = 0U;
        __Vdly__core_tb__DOT__dut__DOT__qcol = 0U;
        vlSelf->core_tb__DOT__dut__DOT__issue_count = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__retire_count = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__effective_macs = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__virtual_macs = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__event_retires = 0ULL;
        __Vdly__core_tb__DOT__dut__DOT__state = 0U;
        vlSelf->core_tb__DOT__error_code = 0U;
        vlSelf->core_tb__DOT__core_done = 0U;
        vlSelf->core_tb__DOT__dut__DOT__core_active = 0U;
        vlSelf->core_tb__DOT__dut__DOT__task_id = 0U;
        vlSelf->core_tb__DOT__dut__DOT__shift = 0U;
        __Vdly__core_tb__DOT__dut__DOT__x_count = 0U;
        __Vdly__core_tb__DOT__dut__DOT__w_count = 0U;
        __Vdly__core_tb__DOT__dut__DOT__b_count = 0U;
        __Vdly__core_tb__DOT__dut__DOT__next_tile = 0U;
        __Vdly__core_tb__DOT__dut__DOT__committed = 0U;
        vlSelf->core_tb__DOT__dut__DOT__tile_open = 0U;
        __Vdly__core_tb__DOT__dut__DOT__row0 = 0U;
        __Vdly__core_tb__DOT__dut__DOT__tile = 0U;
        __Vdly__core_tb__DOT__dut__DOT__out_pos = 0U;
        vlSelf->core_tb__DOT__dut__DOT__product_mask = 0U;
        __Vdly__core_tb__DOT__dut__DOT__product_k = 0U;
        __Vdly__core_tb__DOT__dut__DOT__req_g = 0U;
        __Vdly__core_tb__DOT__dut__DOT__req_k = 0U;
        vlSelf->core_tb__DOT__dut__DOT__tag_valid = 0U;
        __Vdly__core_tb__DOT__dut__DOT__product_valid = 0U;
        __Vdly__core_tb__DOT__dut__DOT__product_g = 0U;
        vlSelf->core_tb__DOT__dut__DOT__product_task = 0U;
        vlSelf->core_tb__DOT__dut__DOT__product_row = 0U;
        vlSelf->core_tb__DOT__dut__DOT__product_tile = 0U;
        vlSelf->core_tb__DOT__dut__DOT__load_cycles = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__compute_cycles = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__output_cycles = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__wait_cycles = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__core_cycles = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__frontend_cycles = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__input_accepts = 0ULL;
        __Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v8 = 1U;
        vlSelf->core_tb__DOT__dut__DOT__qe_valid = 0U;
        vlSelf->core_tb__DOT__dut__DOT__qe_data = 0U;
        vlSelf->core_tb__DOT__dut__DOT__qe_overflow = 0U;
        vlSelf->core_tb__DOT__dut__DOT__qe_saturated = 0U;
        vlSelf->core_tb__DOT__fault = 0U;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem[__Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__mem__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem[__Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__mem__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem[__Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__mem__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0) {
        vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem[__Vdlyvdim0__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__mem__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem[__Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__mem__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem[__Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__mem__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem[__Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__mem__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0) {
        vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem[__Vdlyvdim0__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__mem__v0;
    }
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__valid_pipe 
        = ((IData)(vlSelf->core_tb__DOT__rst_n) && (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__3__KET____DOT__ram__rd_en));
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__valid_pipe 
        = ((IData)(vlSelf->core_tb__DOT__rst_n) && (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__2__KET____DOT__ram__rd_en));
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__valid_pipe 
        = ((IData)(vlSelf->core_tb__DOT__rst_n) && (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__1__KET____DOT__ram__rd_en));
    vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__valid_pipe 
        = ((IData)(vlSelf->core_tb__DOT__rst_n) && (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__xbank__BRA__0__KET____DOT__ram__rd_en));
    vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__valid_pipe 
        = ((IData)(vlSelf->core_tb__DOT__rst_n) && (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en));
    vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__valid_pipe 
        = ((IData)(vlSelf->core_tb__DOT__rst_n) && (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en));
    vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__valid_pipe 
        = ((IData)(vlSelf->core_tb__DOT__rst_n) && (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en));
    vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__valid_pipe 
        = ((IData)(vlSelf->core_tb__DOT__rst_n) && (IData)(vlSelf->core_tb__DOT__dut__DOT____Vcellinp__wbank__BRA__0__KET____DOT__ram__rd_en));
    vlSelf->core_tb__DOT__dut__DOT__product_valid = __Vdly__core_tb__DOT__dut__DOT__product_valid;
    vlSelf->core_tb__DOT__dut__DOT__product_g = __Vdly__core_tb__DOT__dut__DOT__product_g;
    vlSelf->core_tb__DOT__dut__DOT__product_k = __Vdly__core_tb__DOT__dut__DOT__product_k;
    if (__Vdlyvset__core_tb__DOT__dut__DOT__tag_mask__v0) {
        vlSelf->core_tb__DOT__dut__DOT__tag_mask[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__tag_mask__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__tag_task__v0) {
        vlSelf->core_tb__DOT__dut__DOT__tag_task[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__tag_task__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v0) {
        vlSelf->core_tb__DOT__dut__DOT__x_hold[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v1) {
        vlSelf->core_tb__DOT__dut__DOT__x_hold[1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v1;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v2) {
        vlSelf->core_tb__DOT__dut__DOT__x_hold[2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v2;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_hold__v3) {
        vlSelf->core_tb__DOT__dut__DOT__x_hold[3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_hold__v3;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__tag_k__v0) {
        vlSelf->core_tb__DOT__dut__DOT__tag_tile[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__tag_tile__v0;
        vlSelf->core_tb__DOT__dut__DOT__tag_row[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__tag_row__v0;
        vlSelf->core_tb__DOT__dut__DOT__tag_g[0U] = __Vdlyvval__core_tb__DOT__dut__DOT__tag_g__v0;
        vlSelf->core_tb__DOT__dut__DOT__tag_k[0U] = __Vdlyvval__core_tb__DOT__dut__DOT__tag_k__v0;
    }
    vlSelf->core_tb__DOT__dut__DOT__req_k = __Vdly__core_tb__DOT__dut__DOT__req_k;
    if (__Vdlyvset__core_tb__DOT__dut__DOT__product__v0) {
        vlSelf->core_tb__DOT__dut__DOT__product[0U][0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v0;
        vlSelf->core_tb__DOT__dut__DOT__product[0U][1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v1;
        vlSelf->core_tb__DOT__dut__DOT__product[0U][2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v2;
        vlSelf->core_tb__DOT__dut__DOT__product[0U][3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v3;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__product__v4) {
        vlSelf->core_tb__DOT__dut__DOT__product[1U][0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v4;
        vlSelf->core_tb__DOT__dut__DOT__product[1U][1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v5;
        vlSelf->core_tb__DOT__dut__DOT__product[1U][2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v6;
        vlSelf->core_tb__DOT__dut__DOT__product[1U][3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v7;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__product__v8) {
        vlSelf->core_tb__DOT__dut__DOT__product[2U][0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v8;
        vlSelf->core_tb__DOT__dut__DOT__product[2U][1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v9;
        vlSelf->core_tb__DOT__dut__DOT__product[2U][2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v10;
        vlSelf->core_tb__DOT__dut__DOT__product[2U][3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v11;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__product__v12) {
        vlSelf->core_tb__DOT__dut__DOT__product[3U][0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v12;
        vlSelf->core_tb__DOT__dut__DOT__product[3U][1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v13;
        vlSelf->core_tb__DOT__dut__DOT__product[3U][2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v14;
        vlSelf->core_tb__DOT__dut__DOT__product[3U][3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__product__v15;
    }
    vlSelf->core_tb__DOT__dut__DOT__x_data[0U] = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__0__KET____DOT__ram__DOT__data_pipe
        [0U];
    vlSelf->core_tb__DOT__dut__DOT__x_data[1U] = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__1__KET____DOT__ram__DOT__data_pipe
        [0U];
    vlSelf->core_tb__DOT__dut__DOT__x_data[2U] = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__2__KET____DOT__ram__DOT__data_pipe
        [0U];
    vlSelf->core_tb__DOT__dut__DOT__x_data[3U] = vlSelf->core_tb__DOT__dut__DOT__xbank__BRA__3__KET____DOT__ram__DOT__data_pipe
        [0U];
    vlSelf->core_tb__DOT__dut__DOT__w_data[0U] = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__0__KET____DOT__ram__DOT__data_pipe
        [0U];
    vlSelf->core_tb__DOT__dut__DOT__w_data[1U] = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__1__KET____DOT__ram__DOT__data_pipe
        [0U];
    vlSelf->core_tb__DOT__dut__DOT__w_data[2U] = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__2__KET____DOT__ram__DOT__data_pipe
        [0U];
    vlSelf->core_tb__DOT__dut__DOT__w_data[3U] = vlSelf->core_tb__DOT__dut__DOT__wbank__BRA__3__KET____DOT__ram__DOT__data_pipe
        [0U];
    vlSelf->core_tb__DOT__dut__DOT__qrow = __Vdly__core_tb__DOT__dut__DOT__qrow;
    if (__Vdlyvset__core_tb__DOT__dut__DOT__biases__v0) {
        vlSelf->core_tb__DOT__dut__DOT__biases[__Vdlyvdim0__core_tb__DOT__dut__DOT__biases__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__biases__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v0) {
        vlSelf->core_tb__DOT__dut__DOT__w_writes[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v1) {
        vlSelf->core_tb__DOT__dut__DOT__w_writes[1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v1;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v2) {
        vlSelf->core_tb__DOT__dut__DOT__w_writes[2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v2;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__w_writes__v3) {
        vlSelf->core_tb__DOT__dut__DOT__w_writes[3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__w_writes__v3;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v0) {
        vlSelf->core_tb__DOT__dut__DOT__w_reads[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v1) {
        vlSelf->core_tb__DOT__dut__DOT__w_reads[1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v1;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v2) {
        vlSelf->core_tb__DOT__dut__DOT__w_reads[2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v2;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__w_reads__v3) {
        vlSelf->core_tb__DOT__dut__DOT__w_reads[3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__w_reads__v3;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v0) {
        vlSelf->core_tb__DOT__dut__DOT__x_writes[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v1) {
        vlSelf->core_tb__DOT__dut__DOT__x_writes[1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v1;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v2) {
        vlSelf->core_tb__DOT__dut__DOT__x_writes[2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v2;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_writes__v3) {
        vlSelf->core_tb__DOT__dut__DOT__x_writes[3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_writes__v3;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v4) {
        vlSelf->core_tb__DOT__dut__DOT__w_writes[0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_writes[1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_writes[2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_writes[3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_reads[0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_reads[1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_reads[2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_reads[3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_writes[0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_writes[1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_writes[2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_writes[3U] = 0ULL;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v0) {
        vlSelf->core_tb__DOT__dut__DOT__x_reads[0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v1) {
        vlSelf->core_tb__DOT__dut__DOT__x_reads[1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v1;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v2) {
        vlSelf->core_tb__DOT__dut__DOT__x_reads[2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v2;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v3) {
        vlSelf->core_tb__DOT__dut__DOT__x_reads[3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__x_reads__v3;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v4) {
        vlSelf->core_tb__DOT__dut__DOT__x_reads[0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_reads[1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_reads[2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_reads[3U] = 0ULL;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__x_reads__v8) {
        vlSelf->core_tb__DOT__dut__DOT__w_writes[0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_writes[1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_writes[2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_writes[3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_reads[0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_reads[1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_reads[2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__w_reads[3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_writes[0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_writes[1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_writes[2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_writes[3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_reads[0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_reads[1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_reads[2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__x_reads[3U] = 0ULL;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__result_data__v0) {
        vlSelf->core_tb__DOT__dut__DOT__result_saturated[__Vdlyvdim0__core_tb__DOT__dut__DOT__result_saturated__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__result_saturated__v0;
        vlSelf->core_tb__DOT__dut__DOT__result_overflow[__Vdlyvdim0__core_tb__DOT__dut__DOT__result_overflow__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__result_overflow__v0;
        vlSelf->core_tb__DOT__dut__DOT__result_data[__Vdlyvdim0__core_tb__DOT__dut__DOT__result_data__v0] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__result_data__v0;
    }
    vlSelf->core_tb__DOT__dut__DOT__req_g = __Vdly__core_tb__DOT__dut__DOT__req_g;
    vlSelf->core_tb__DOT__dut__DOT__g = __Vdly__core_tb__DOT__dut__DOT__g;
    vlSelf->core_tb__DOT__dut__DOT__qcol = __Vdly__core_tb__DOT__dut__DOT__qcol;
    vlSelf->core_tb__DOT__dut__DOT__tile = __Vdly__core_tb__DOT__dut__DOT__tile;
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v0) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v0][0U][0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v0;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v1) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v1][0U][1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v1;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v2) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v2][0U][2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v2;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v3) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v3][0U][3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v3;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v4) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v4][1U][0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v4;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v5) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v5][1U][1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v5;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v6) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v6][1U][2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v6;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v7) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v7][1U][3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v7;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v8) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v8][2U][0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v8;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v9) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v9][2U][1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v9;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v10) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v10][2U][2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v10;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v11) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v11][2U][3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v11;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v12) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v12][3U][0U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v12;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v13) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v13][3U][1U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v13;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v14) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v14][3U][2U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v14;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v15) {
        vlSelf->core_tb__DOT__dut__DOT__acc[__Vdlyvdim0__core_tb__DOT__dut__DOT__acc__v15][3U][3U] 
            = __Vdlyvval__core_tb__DOT__dut__DOT__acc__v15;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v16) {
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][0U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][0U][1U] = 0ULL;
    }
    if (__Vdlyvset__core_tb__DOT__dut__DOT__acc__v18) {
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][0U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][0U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][1U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][1U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][1U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][1U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][2U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][2U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][2U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][2U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][3U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][3U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][3U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[0U][3U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][0U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][0U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][0U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][0U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][1U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][1U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][1U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][1U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][2U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][2U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][2U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][2U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][3U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][3U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][3U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[1U][3U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][0U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][0U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][0U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][0U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][1U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][1U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][1U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][1U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][2U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][2U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][2U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][2U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][3U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][3U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][3U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[2U][3U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][0U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][0U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][0U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][0U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][1U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][1U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][1U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][1U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][2U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][2U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][2U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][2U][3U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][3U][0U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][3U][1U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][3U][2U] = 0ULL;
        vlSelf->core_tb__DOT__dut__DOT__acc[3U][3U][3U] = 0ULL;
    }
    vlSelf->core_tb__DOT__dut__DOT__row0 = __Vdly__core_tb__DOT__dut__DOT__row0;
    vlSelf->core_tb__DOT__dut__DOT__out_pos = __Vdly__core_tb__DOT__dut__DOT__out_pos;
    vlSelf->core_tb__DOT__dut__DOT__x_count = __Vdly__core_tb__DOT__dut__DOT__x_count;
    vlSelf->core_tb__DOT__dut__DOT__w_count = __Vdly__core_tb__DOT__dut__DOT__w_count;
    vlSelf->core_tb__DOT__dut__DOT__b_count = __Vdly__core_tb__DOT__dut__DOT__b_count;
    vlSelf->core_tb__DOT__dut__DOT__committed = __Vdly__core_tb__DOT__dut__DOT__committed;
    vlSelf->core_tb__DOT__dut__DOT__next_tile = __Vdly__core_tb__DOT__dut__DOT__next_tile;
    vlSelf->core_tb__DOT__dut__DOT__state = __Vdly__core_tb__DOT__dut__DOT__state;
    vlSelf->core_tb__DOT__dut__DOT__returned = vlSelf->core_tb__DOT__dut__DOT__tag_valid;
    core_tb__DOT__dut__DOT____Vcellinp__quant__in_bias 
        = vlSelf->core_tb__DOT__dut__DOT__biases[(0xffU 
                                                  & (VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__tile) 
                                                     + 
                                                     (VL_MULS_III(32, (IData)(4U), vlSelf->core_tb__DOT__dut__DOT__g) 
                                                      + vlSelf->core_tb__DOT__dut__DOT__qcol)))];
    core_tb__DOT__dut__DOT____Vcellinp__quant__in_sum 
        = vlSelf->core_tb__DOT__dut__DOT__acc[(3U & vlSelf->core_tb__DOT__dut__DOT__g)]
        [(3U & vlSelf->core_tb__DOT__dut__DOT__qrow)]
        [(3U & vlSelf->core_tb__DOT__dut__DOT__qcol)];
    vlSelf->core_tb__DOT__dut__DOT__effective_rows 
        = (VL_GTS_III(32, 4U, ((IData)(0x63U) - vlSelf->core_tb__DOT__dut__DOT__row0))
            ? ((IData)(0x63U) - vlSelf->core_tb__DOT__dut__DOT__row0)
            : 4U);
    vlSelf->core_tb__DOT__out_data = vlSelf->core_tb__DOT__dut__DOT__result_data
        [(0x3fU & vlSelf->core_tb__DOT__dut__DOT__out_pos)];
    vlSelf->core_tb__DOT__out_overflow = vlSelf->core_tb__DOT__dut__DOT__result_overflow
        [(0x3fU & vlSelf->core_tb__DOT__dut__DOT__out_pos)];
    vlSelf->core_tb__DOT__out_saturated = vlSelf->core_tb__DOT__dut__DOT__result_saturated
        [(0x3fU & vlSelf->core_tb__DOT__dut__DOT__out_pos)];
    core_tb__DOT__dut__DOT____VdfgTmp_hff5a03ba__0 
        = (vlSelf->core_tb__DOT__dut__DOT__row0 + VL_DIVS_III(32, vlSelf->core_tb__DOT__dut__DOT__out_pos, (IData)(0x10U)));
    vlSelf->core_tb__DOT__out_valid = (8U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state));
    vlSelf->core_tb__DOT__out_y_index = (VL_MULS_III(32, (IData)(0x100U), core_tb__DOT__dut__DOT____VdfgTmp_hff5a03ba__0) 
                                         + (VL_MULS_III(32, (IData)(0x10U), vlSelf->core_tb__DOT__dut__DOT__tile) 
                                            + VL_MODDIVS_III(32, vlSelf->core_tb__DOT__dut__DOT__out_pos, (IData)(0x10U))));
    vlSelf->core_tb__DOT__out_last = ((0x62U == core_tb__DOT__dut__DOT____VdfgTmp_hff5a03ba__0) 
                                      & ((0xfU == vlSelf->core_tb__DOT__dut__DOT__tile) 
                                         & (0xfU == 
                                            VL_MODDIVS_III(32, vlSelf->core_tb__DOT__dut__DOT__out_pos, (IData)(0x10U)))));
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
    vlSelf->core_tb__DOT__dut__DOT____Vcellinp__quant__in_valid 
        = ((~ (IData)(vlSelf->core_tb__DOT__fault)) 
           & (6U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)));
    vlSelf->core_tb__DOT__dut__DOT__qe_ready = (1U 
                                                & ((~ (IData)(vlSelf->core_tb__DOT__dut__DOT__qe_valid)) 
                                                   | ((~ (IData)(vlSelf->core_tb__DOT__fault)) 
                                                      & (7U 
                                                         == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)))));
    vlSelf->core_tb__DOT__dut__DOT__retire_event = 
        ((~ (IData)(vlSelf->core_tb__DOT__fault)) & (IData)(vlSelf->core_tb__DOT__dut__DOT__q_valid));
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
    core_tb__DOT__dut__DOT____VdfgTmp_h109f94df__0 
        = ((IData)(vlSelf->core_tb__DOT__dut__DOT__retire_event) 
           & (1U == (IData)(vlSelf->core_tb__DOT__dut__DOT__state)));
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

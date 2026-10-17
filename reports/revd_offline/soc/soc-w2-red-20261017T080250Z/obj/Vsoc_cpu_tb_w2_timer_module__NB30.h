// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsoc_cpu_tb_w2.h for the primary calling header

#ifndef VERILATED_VSOC_CPU_TB_W2_TIMER_MODULE__NB30_H_
#define VERILATED_VSOC_CPU_TB_W2_TIMER_MODULE__NB30_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vsoc_cpu_tb_w2__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsoc_cpu_tb_w2_timer_module__NB30 final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk_i,0,0);
        VL_IN8(rstn_i,0,0);
        VL_IN8(cfg_start_i,0,0);
        VL_IN8(cfg_stop_i,0,0);
        VL_IN8(cfg_rst_i,0,0);
        VL_IN8(cfg_update_i,0,0);
        VL_IN8(cfg_arm_i,0,0);
        VL_IN8(cfg_sel_i,7,0);
        VL_IN8(cfg_sel_clk_i,0,0);
        VL_IN8(cfg_mode_i,2,0);
        VL_IN8(cfg_presc_i,7,0);
        VL_IN8(cfg_sawtooth_i,0,0);
        VL_IN8(cfg_comp_op_ch0_i,2,0);
        VL_IN8(cfg_comp_op_ch1_i,2,0);
        VL_IN8(cfg_comp_op_ch2_i,2,0);
        VL_IN8(cfg_comp_op_ch3_i,2,0);
        VL_IN8(ls_clk_i,0,0);
        VL_OUT8(pwm_o,3,0);
        VL_OUT8(status_o,7,0);
        CData/*0:0*/ __PVT__s_ctrl_update_all;
        CData/*0:0*/ __PVT__s_ctrl_rst;
        CData/*0:0*/ __PVT__s_presc_evt;
        CData/*0:0*/ __PVT__s_cnt_end;
        CData/*0:0*/ __PVT__s_cnt_evt;
        CData/*0:0*/ __PVT__u_controller__DOT__r_active;
        CData/*0:0*/ __PVT__u_in_stage__DOT__s_rise_ls_clk;
        CData/*0:0*/ __PVT__u_in_stage__DOT__s_int_evnt;
        CData/*0:0*/ __PVT__u_in_stage__DOT__r_event;
        CData/*0:0*/ __PVT__u_in_stage__DOT__r_oldval;
        CData/*0:0*/ __PVT__u_in_stage__DOT__s_int_sig;
        CData/*7:0*/ __PVT__u_in_stage__DOT__r_sel;
        CData/*2:0*/ __PVT__u_in_stage__DOT__r_mode;
        CData/*0:0*/ __PVT__u_in_stage__DOT__r_armed;
        CData/*2:0*/ __PVT__u_in_stage__DOT__r_ls_clk_sync;
        CData/*7:0*/ __PVT__u_prescaler__DOT__r_presc;
        CData/*7:0*/ __PVT__u_prescaler__DOT__r_counter;
        CData/*0:0*/ __PVT__u_counter__DOT__r_direction;
        CData/*0:0*/ __PVT__u_counter__DOT__r_sawtooth;
        CData/*0:0*/ __PVT__u_counter__DOT__r_event;
        CData/*0:0*/ __PVT__u_counter__DOT__s_direction;
        CData/*0:0*/ __PVT__u_counter__DOT__s_sawtooth;
        CData/*0:0*/ __PVT__u_counter__DOT__s_is_update;
        CData/*0:0*/ __PVT__u_counter__DOT__s_do_update;
        CData/*0:0*/ __PVT__u_counter__DOT__s_pending_update;
        CData/*0:0*/ __PVT__u_counter__DOT__r_pending_update;
        CData/*2:0*/ __PVT__u_comp_ch0__DOT__r_comp_op;
        CData/*0:0*/ __PVT__u_comp_ch0__DOT__r_value;
        CData/*0:0*/ __PVT__u_comp_ch0__DOT__r_is_2nd_event;
        CData/*0:0*/ __PVT__u_comp_ch0__DOT__s_match;
        CData/*0:0*/ __PVT__u_comp_ch0__DOT__s_2nd_event;
        CData/*2:0*/ __PVT__u_comp_ch1__DOT__r_comp_op;
        CData/*0:0*/ __PVT__u_comp_ch1__DOT__r_value;
        CData/*0:0*/ __PVT__u_comp_ch1__DOT__r_is_2nd_event;
        CData/*0:0*/ __PVT__u_comp_ch1__DOT__s_match;
        CData/*0:0*/ __PVT__u_comp_ch1__DOT__s_2nd_event;
        CData/*2:0*/ __PVT__u_comp_ch2__DOT__r_comp_op;
        CData/*0:0*/ __PVT__u_comp_ch2__DOT__r_value;
        CData/*0:0*/ __PVT__u_comp_ch2__DOT__r_is_2nd_event;
        CData/*0:0*/ __PVT__u_comp_ch2__DOT__s_match;
        CData/*0:0*/ __PVT__u_comp_ch2__DOT__s_2nd_event;
        CData/*2:0*/ __PVT__u_comp_ch3__DOT__r_comp_op;
        CData/*0:0*/ __PVT__u_comp_ch3__DOT__r_value;
        CData/*0:0*/ __PVT__u_comp_ch3__DOT__r_is_2nd_event;
        CData/*0:0*/ __PVT__u_comp_ch3__DOT__s_match;
    };
    struct {
        CData/*0:0*/ __PVT__u_comp_ch3__DOT__s_2nd_event;
        VL_IN16(cfg_cnt_start_i,15,0);
        VL_IN16(cfg_cnt_end_i,15,0);
        VL_IN16(cfg_comp_ch0_i,15,0);
        VL_IN16(cfg_comp_ch1_i,15,0);
        VL_IN16(cfg_comp_ch2_i,15,0);
        VL_IN16(cfg_comp_ch3_i,15,0);
        VL_OUT16(counter_o,15,0);
        SData/*15:0*/ __PVT__u_counter__DOT__r_counter;
        SData/*15:0*/ __PVT__u_counter__DOT__r_start;
        SData/*15:0*/ __PVT__u_counter__DOT__r_end;
        SData/*15:0*/ __PVT__u_counter__DOT__s_counter;
        SData/*15:0*/ __PVT__u_counter__DOT__s_start;
        SData/*15:0*/ __PVT__u_counter__DOT__s_end;
        SData/*15:0*/ __PVT__u_comp_ch0__DOT__r_comp;
        SData/*15:0*/ __PVT__u_comp_ch1__DOT__r_comp;
        SData/*15:0*/ __PVT__u_comp_ch2__DOT__r_comp;
        SData/*15:0*/ __PVT__u_comp_ch3__DOT__r_comp;
        VL_IN64(signal_i,47,0);
    };

    // INTERNAL VARIABLES
    Vsoc_cpu_tb_w2__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsoc_cpu_tb_w2_timer_module__NB30(Vsoc_cpu_tb_w2__Syms* symsp, const char* v__name);
    ~Vsoc_cpu_tb_w2_timer_module__NB30();
    VL_UNCOPYABLE(Vsoc_cpu_tb_w2_timer_module__NB30);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

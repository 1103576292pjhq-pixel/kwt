// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb.h for the primary calling header

#include "Vsoc_cpu_tb__pch.h"
#include "Vsoc_cpu_tb_timer_module__NB30.h"

VL_ATTR_COLD void Vsoc_cpu_tb_timer_module__NB30___ctor_var_reset(Vsoc_cpu_tb_timer_module__NB30* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_cpu_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                  Vsoc_cpu_tb_timer_module__NB30___ctor_var_reset\n"); );
    // Body
    vlSelf->clk_i = VL_RAND_RESET_I(1);
    vlSelf->rstn_i = VL_RAND_RESET_I(1);
    vlSelf->cfg_start_i = VL_RAND_RESET_I(1);
    vlSelf->cfg_stop_i = VL_RAND_RESET_I(1);
    vlSelf->cfg_rst_i = VL_RAND_RESET_I(1);
    vlSelf->cfg_update_i = VL_RAND_RESET_I(1);
    vlSelf->cfg_arm_i = VL_RAND_RESET_I(1);
    vlSelf->cfg_sel_i = VL_RAND_RESET_I(8);
    vlSelf->cfg_sel_clk_i = VL_RAND_RESET_I(1);
    vlSelf->cfg_mode_i = VL_RAND_RESET_I(3);
    vlSelf->cfg_presc_i = VL_RAND_RESET_I(8);
    vlSelf->cfg_sawtooth_i = VL_RAND_RESET_I(1);
    vlSelf->cfg_cnt_start_i = VL_RAND_RESET_I(16);
    vlSelf->cfg_cnt_end_i = VL_RAND_RESET_I(16);
    vlSelf->cfg_comp_ch0_i = VL_RAND_RESET_I(16);
    vlSelf->cfg_comp_op_ch0_i = VL_RAND_RESET_I(3);
    vlSelf->cfg_comp_ch1_i = VL_RAND_RESET_I(16);
    vlSelf->cfg_comp_op_ch1_i = VL_RAND_RESET_I(3);
    vlSelf->cfg_comp_ch2_i = VL_RAND_RESET_I(16);
    vlSelf->cfg_comp_op_ch2_i = VL_RAND_RESET_I(3);
    vlSelf->cfg_comp_ch3_i = VL_RAND_RESET_I(16);
    vlSelf->cfg_comp_op_ch3_i = VL_RAND_RESET_I(3);
    vlSelf->ls_clk_i = VL_RAND_RESET_I(1);
    vlSelf->signal_i = VL_RAND_RESET_Q(48);
    vlSelf->counter_o = VL_RAND_RESET_I(16);
    vlSelf->pwm_o = VL_RAND_RESET_I(4);
    vlSelf->status_o = VL_RAND_RESET_I(8);
    vlSelf->__PVT__s_ctrl_update_all = VL_RAND_RESET_I(1);
    vlSelf->__PVT__s_ctrl_rst = VL_RAND_RESET_I(1);
    vlSelf->__PVT__s_presc_evt = VL_RAND_RESET_I(1);
    vlSelf->__PVT__s_cnt_end = VL_RAND_RESET_I(1);
    vlSelf->__PVT__s_cnt_evt = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_controller__DOT__r_active = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_in_stage__DOT__s_rise_ls_clk = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_in_stage__DOT__s_int_evnt = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_in_stage__DOT__r_event = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_in_stage__DOT__r_oldval = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_in_stage__DOT__s_int_sig = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_in_stage__DOT__r_sel = VL_RAND_RESET_I(8);
    vlSelf->__PVT__u_in_stage__DOT__r_mode = VL_RAND_RESET_I(3);
    vlSelf->__PVT__u_in_stage__DOT__r_armed = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_in_stage__DOT__r_ls_clk_sync = VL_RAND_RESET_I(3);
    vlSelf->__PVT__u_prescaler__DOT__r_presc = VL_RAND_RESET_I(8);
    vlSelf->__PVT__u_prescaler__DOT__r_counter = VL_RAND_RESET_I(8);
    vlSelf->__PVT__u_counter__DOT__r_counter = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_counter__DOT__r_start = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_counter__DOT__r_end = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_counter__DOT__s_counter = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_counter__DOT__s_start = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_counter__DOT__s_end = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_counter__DOT__r_direction = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_counter__DOT__r_sawtooth = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_counter__DOT__r_event = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_counter__DOT__s_direction = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_counter__DOT__s_sawtooth = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_counter__DOT__s_is_update = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_counter__DOT__s_do_update = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_counter__DOT__s_pending_update = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_counter__DOT__r_pending_update = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch0__DOT__r_comp = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_comp_ch0__DOT__r_comp_op = VL_RAND_RESET_I(3);
    vlSelf->__PVT__u_comp_ch0__DOT__r_value = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch0__DOT__r_is_2nd_event = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch0__DOT__s_match = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch0__DOT__s_2nd_event = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch1__DOT__r_comp = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_comp_ch1__DOT__r_comp_op = VL_RAND_RESET_I(3);
    vlSelf->__PVT__u_comp_ch1__DOT__r_value = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch1__DOT__r_is_2nd_event = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch1__DOT__s_match = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch1__DOT__s_2nd_event = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch2__DOT__r_comp = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_comp_ch2__DOT__r_comp_op = VL_RAND_RESET_I(3);
    vlSelf->__PVT__u_comp_ch2__DOT__r_value = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch2__DOT__r_is_2nd_event = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch2__DOT__s_match = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch2__DOT__s_2nd_event = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch3__DOT__r_comp = VL_RAND_RESET_I(16);
    vlSelf->__PVT__u_comp_ch3__DOT__r_comp_op = VL_RAND_RESET_I(3);
    vlSelf->__PVT__u_comp_ch3__DOT__r_value = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch3__DOT__r_is_2nd_event = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch3__DOT__s_match = VL_RAND_RESET_I(1);
    vlSelf->__PVT__u_comp_ch3__DOT__s_2nd_event = VL_RAND_RESET_I(1);
}

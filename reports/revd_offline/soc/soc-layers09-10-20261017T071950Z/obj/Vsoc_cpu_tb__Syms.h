// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSOC_CPU_TB__SYMS_H_
#define VERILATED_VSOC_CPU_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vsoc_cpu_tb.h"

// INCLUDE MODULE CLASSES
#include "Vsoc_cpu_tb___024root.h"
#include "Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20.h"
#include "Vsoc_cpu_tb_apb_uart_sv__A20.h"
#include "Vsoc_cpu_tb_apb_spi_master__A20.h"
#include "Vsoc_cpu_tb_timer_module__NB30.h"
#include "Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vsoc_cpu_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vsoc_cpu_tb* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vsoc_cpu_tb___024root          TOP;
    Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer;
    Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb;
    Vsoc_cpu_tb_timer_module__NB30 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0;
    Vsoc_cpu_tb_timer_module__NB30 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1;
    Vsoc_cpu_tb_timer_module__NB30 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2;
    Vsoc_cpu_tb_timer_module__NB30 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3;
    Vsoc_cpu_tb_apb_spi_master__A20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1;
    Vsoc_cpu_tb_apb_spi_master__A20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2;
    Vsoc_cpu_tb_apb_uart_sv__A20   TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0;
    Vsoc_cpu_tb_apb_uart_sv__A20   TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1;
    Vsoc_cpu_tb_apb_uart_sv__A20   TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb;
    Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20 TOP__soc_cpu_tb__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb;

    // SCOPE NAMES
    VerilatedScope __Vscope_soc_cpu_tb;

    // CONSTRUCTORS
    Vsoc_cpu_tb__Syms(VerilatedContext* contextp, const char* namep, Vsoc_cpu_tb* modelp);
    ~Vsoc_cpu_tb__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard

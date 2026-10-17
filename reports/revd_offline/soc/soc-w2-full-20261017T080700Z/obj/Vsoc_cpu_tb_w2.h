// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VSOC_CPU_TB_W2_H_
#define VERILATED_VSOC_CPU_TB_W2_H_  // guard

#include "verilated.h"

class Vsoc_cpu_tb_w2__Syms;
class Vsoc_cpu_tb_w2___024root;
class Vsoc_cpu_tb_w2_apb_spi_master__A20;
class Vsoc_cpu_tb_w2_apb_uart_sv__A20;
class Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1;
class Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20;
class Vsoc_cpu_tb_w2_timer_module__NB30;


// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) Vsoc_cpu_tb_w2 VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vsoc_cpu_tb_w2__Syms* const vlSymsp;

  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioA_apb_icb2apb;
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_gpioB_apb_icb2apb;
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart0_apb_icb2apb;
    Vsoc_cpu_tb_w2_apb_uart_sv__A20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart0;
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart1_apb_icb2apb;
    Vsoc_cpu_tb_w2_apb_uart_sv__A20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart1;
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_uart2_apb_icb2apb;
    Vsoc_cpu_tb_w2_apb_uart_sv__A20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_uart2;
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi1_apb_icb2apb;
    Vsoc_cpu_tb_w2_apb_spi_master__A20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi1;
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_spi2_apb_icb2apb;
    Vsoc_cpu_tb_w2_apb_spi_master__A20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_spi2;
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c0_apb_icb2apb;
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_i2c1_apb_icb2apb;
    Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_pwm_apb_icb2apb;
    Vsoc_cpu_tb_w2_timer_module__NB30* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim0;
    Vsoc_cpu_tb_w2_timer_module__NB30* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim1;
    Vsoc_cpu_tb_w2_timer_module__NB30* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim2;
    Vsoc_cpu_tb_w2_timer_module__NB30* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_perips_apb_pwm__DOT__u_tim3;
    Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_perips__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer;
    Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1* const __PVT__soc_cpu_tb_w2__DOT__cpu__DOT__u_subsys__DOT__u_e203_subsys_main__DOT__u_e203_subsys_mems__DOT__u_expl_axi_icb2axi__DOT__u_sirv_gnrl_axi_buffer;

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vsoc_cpu_tb_w2___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vsoc_cpu_tb_w2(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vsoc_cpu_tb_w2(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vsoc_cpu_tb_w2();
  private:
    VL_UNCOPYABLE(Vsoc_cpu_tb_w2);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    /// Prepare for cloning the model at the process level (e.g. fork in Linux)
    /// Release necessary resources. Called before cloning.
    void prepareClone() const;
    /// Re-init after cloning the model at the process level (e.g. fork in Linux)
    /// Re-allocate necessary resources. Called after cloning.
    void atClone() const;
};

#endif  // guard

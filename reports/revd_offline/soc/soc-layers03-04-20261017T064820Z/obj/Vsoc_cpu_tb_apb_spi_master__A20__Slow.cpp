// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb.h for the primary calling header

#include "Vsoc_cpu_tb__pch.h"
#include "Vsoc_cpu_tb__Syms.h"
#include "Vsoc_cpu_tb_apb_spi_master__A20.h"

void Vsoc_cpu_tb_apb_spi_master__A20___ctor_var_reset(Vsoc_cpu_tb_apb_spi_master__A20* vlSelf);

Vsoc_cpu_tb_apb_spi_master__A20::Vsoc_cpu_tb_apb_spi_master__A20(Vsoc_cpu_tb__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vsoc_cpu_tb_apb_spi_master__A20___ctor_var_reset(this);
}

void Vsoc_cpu_tb_apb_spi_master__A20::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vsoc_cpu_tb_apb_spi_master__A20::~Vsoc_cpu_tb_apb_spi_master__A20() {
}

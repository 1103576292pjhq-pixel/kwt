// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb_w2.h for the primary calling header

#include "Vsoc_cpu_tb_w2__pch.h"
#include "Vsoc_cpu_tb_w2__Syms.h"
#include "Vsoc_cpu_tb_w2_apb_spi_master__A20.h"

void Vsoc_cpu_tb_w2_apb_spi_master__A20___ctor_var_reset(Vsoc_cpu_tb_w2_apb_spi_master__A20* vlSelf);

Vsoc_cpu_tb_w2_apb_spi_master__A20::Vsoc_cpu_tb_w2_apb_spi_master__A20(Vsoc_cpu_tb_w2__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vsoc_cpu_tb_w2_apb_spi_master__A20___ctor_var_reset(this);
}

void Vsoc_cpu_tb_w2_apb_spi_master__A20::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vsoc_cpu_tb_w2_apb_spi_master__A20::~Vsoc_cpu_tb_w2_apb_spi_master__A20() {
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_cpu_tb_w2.h for the primary calling header

#include "Vsoc_cpu_tb_w2__pch.h"
#include "Vsoc_cpu_tb_w2__Syms.h"
#include "Vsoc_cpu_tb_w2___024root.h"

void Vsoc_cpu_tb_w2___024root___ctor_var_reset(Vsoc_cpu_tb_w2___024root* vlSelf);

Vsoc_cpu_tb_w2___024root::Vsoc_cpu_tb_w2___024root(Vsoc_cpu_tb_w2__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __VdlySched{*symsp->_vm_contextp__}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vsoc_cpu_tb_w2___024root___ctor_var_reset(this);
}

void Vsoc_cpu_tb_w2___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vsoc_cpu_tb_w2___024root::~Vsoc_cpu_tb_w2___024root() {
}

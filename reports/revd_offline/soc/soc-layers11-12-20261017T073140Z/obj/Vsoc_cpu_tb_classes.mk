# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Make include file with class lists
#
# This file lists generated Verilated files, for including in higher level makefiles.
# See Vsoc_cpu_tb.mk for the caller.

### Switches...
# C11 constructs required?  0/1 (always on now)
VM_C11 = 1
# Timing enabled?  0/1
VM_TIMING = 1
# Coverage output mode?  0/1 (from --coverage)
VM_COVERAGE = 0
# Parallel builds?  0/1 (from --output-split)
VM_PARALLEL_BUILDS = 1
# Tracing output mode?  0/1 (from --trace/--trace-fst)
VM_TRACE = 0
# Tracing output mode in VCD format?  0/1 (from --trace)
VM_TRACE_VCD = 0
# Tracing output mode in FST format?  0/1 (from --trace-fst)
VM_TRACE_FST = 0

### Object file lists...
# Generated module classes, fast-path, compile with highest optimization
VM_CLASSES_FAST += \
	Vsoc_cpu_tb \
	Vsoc_cpu_tb___024root__DepSet_ha44f0ae4__0 \
	Vsoc_cpu_tb___024root__DepSet_ha44f0ae4__1 \
	Vsoc_cpu_tb___024root__DepSet_h2fcc2a77__0 \
	Vsoc_cpu_tb___024root__DepSet_h2fcc2a77__1 \
	Vsoc_cpu_tb___024root__DepSet_h2fcc2a77__2 \
	Vsoc_cpu_tb___024root__DepSet_h2fcc2a77__3 \
	Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20__DepSet_h467f9c57__0 \
	Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20__DepSet_h0dbc9ce6__0 \
	Vsoc_cpu_tb_apb_uart_sv__A20__DepSet_h70a0db64__0 \
	Vsoc_cpu_tb_apb_spi_master__A20__DepSet_h92bcb535__0 \
	Vsoc_cpu_tb_timer_module__NB30__DepSet_hc5f9bab7__0 \
	Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1__DepSet_h986daae9__0 \
	Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1__DepSet_h3baa8a74__0 \
	Vsoc_cpu_tb__main \

# Generated module classes, non-fast-path, compile with low/medium optimization
VM_CLASSES_SLOW += \
	Vsoc_cpu_tb__ConstPool_0 \
	Vsoc_cpu_tb___024root__Slow \
	Vsoc_cpu_tb___024root__DepSet_ha44f0ae4__0__Slow \
	Vsoc_cpu_tb___024root__DepSet_ha44f0ae4__1__Slow \
	Vsoc_cpu_tb___024root__DepSet_h2fcc2a77__0__Slow \
	Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20__Slow \
	Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20__DepSet_h467f9c57__0__Slow \
	Vsoc_cpu_tb_sirv_gnrl_icb2apb__D20__DepSet_h0dbc9ce6__0__Slow \
	Vsoc_cpu_tb_apb_uart_sv__A20__Slow \
	Vsoc_cpu_tb_apb_uart_sv__A20__DepSet_h70a0db64__0__Slow \
	Vsoc_cpu_tb_apb_uart_sv__A20__DepSet_he3755bf7__0__Slow \
	Vsoc_cpu_tb_apb_spi_master__A20__Slow \
	Vsoc_cpu_tb_apb_spi_master__A20__DepSet_h92bcb535__0__Slow \
	Vsoc_cpu_tb_apb_spi_master__A20__DepSet_h41797648__0__Slow \
	Vsoc_cpu_tb_timer_module__NB30__Slow \
	Vsoc_cpu_tb_timer_module__NB30__DepSet_hc5f9bab7__0__Slow \
	Vsoc_cpu_tb_timer_module__NB30__DepSet_h903e7ac6__0__Slow \
	Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1__Slow \
	Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1__DepSet_h986daae9__0__Slow \
	Vsoc_cpu_tb_sirv_gnrl_axi_buffer__CB1__DepSet_h3baa8a74__0__Slow \

# Generated support classes, fast-path, compile with highest optimization
VM_SUPPORT_FAST += \

# Generated support classes, non-fast-path, compile with low/medium optimization
VM_SUPPORT_SLOW += \
	Vsoc_cpu_tb__Syms \

# Global classes, need linked once per executable, fast-path, compile with highest optimization
VM_GLOBAL_FAST += \
	verilated \
	verilated_timing \
	verilated_threads \

# Global classes, need linked once per executable, non-fast-path, compile with low/medium optimization
VM_GLOBAL_SLOW += \


# Verilated -*- Makefile -*-

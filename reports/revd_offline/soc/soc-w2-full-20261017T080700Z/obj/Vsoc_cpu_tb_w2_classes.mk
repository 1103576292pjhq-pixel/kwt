# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Make include file with class lists
#
# This file lists generated Verilated files, for including in higher level makefiles.
# See Vsoc_cpu_tb_w2.mk for the caller.

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
	Vsoc_cpu_tb_w2 \
	Vsoc_cpu_tb_w2___024root__DepSet_h3f2d4af8__0 \
	Vsoc_cpu_tb_w2___024root__DepSet_h3f2d4af8__1 \
	Vsoc_cpu_tb_w2___024root__DepSet_h52230a33__0 \
	Vsoc_cpu_tb_w2___024root__DepSet_h52230a33__1 \
	Vsoc_cpu_tb_w2___024root__DepSet_h52230a33__2 \
	Vsoc_cpu_tb_w2___024root__DepSet_h52230a33__3 \
	Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20__DepSet_hbafeb42e__0 \
	Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20__DepSet_hcf54635d__0 \
	Vsoc_cpu_tb_w2_apb_uart_sv__A20__DepSet_h90e8e044__0 \
	Vsoc_cpu_tb_w2_apb_spi_master__A20__DepSet_h4d39f7b6__0 \
	Vsoc_cpu_tb_w2_timer_module__NB30__DepSet_h51ca63c6__0 \
	Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1__DepSet_haa6e86c8__0 \
	Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1__DepSet_hbee45603__0 \
	Vsoc_cpu_tb_w2__main \

# Generated module classes, non-fast-path, compile with low/medium optimization
VM_CLASSES_SLOW += \
	Vsoc_cpu_tb_w2__ConstPool_0 \
	Vsoc_cpu_tb_w2___024root__Slow \
	Vsoc_cpu_tb_w2___024root__DepSet_h3f2d4af8__0__Slow \
	Vsoc_cpu_tb_w2___024root__DepSet_h3f2d4af8__1__Slow \
	Vsoc_cpu_tb_w2___024root__DepSet_h52230a33__0__Slow \
	Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20__Slow \
	Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20__DepSet_hbafeb42e__0__Slow \
	Vsoc_cpu_tb_w2_sirv_gnrl_icb2apb__D20__DepSet_hcf54635d__0__Slow \
	Vsoc_cpu_tb_w2_apb_uart_sv__A20__Slow \
	Vsoc_cpu_tb_w2_apb_uart_sv__A20__DepSet_h90e8e044__0__Slow \
	Vsoc_cpu_tb_w2_apb_uart_sv__A20__DepSet_he55eaf87__0__Slow \
	Vsoc_cpu_tb_w2_apb_spi_master__A20__Slow \
	Vsoc_cpu_tb_w2_apb_spi_master__A20__DepSet_h4d39f7b6__0__Slow \
	Vsoc_cpu_tb_w2_apb_spi_master__A20__DepSet_h200fa4f5__0__Slow \
	Vsoc_cpu_tb_w2_timer_module__NB30__Slow \
	Vsoc_cpu_tb_w2_timer_module__NB30__DepSet_h51ca63c6__0__Slow \
	Vsoc_cpu_tb_w2_timer_module__NB30__DepSet_h24403105__0__Slow \
	Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1__Slow \
	Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1__DepSet_haa6e86c8__0__Slow \
	Vsoc_cpu_tb_w2_sirv_gnrl_axi_buffer__CB1__DepSet_hbee45603__0__Slow \

# Generated support classes, fast-path, compile with highest optimization
VM_SUPPORT_FAST += \

# Generated support classes, non-fast-path, compile with low/medium optimization
VM_SUPPORT_SLOW += \
	Vsoc_cpu_tb_w2__Syms \

# Global classes, need linked once per executable, fast-path, compile with highest optimization
VM_GLOBAL_FAST += \
	verilated \
	verilated_timing \
	verilated_threads \

# Global classes, need linked once per executable, non-fast-path, compile with low/medium optimization
VM_GLOBAL_SLOW += \


# Verilated -*- Makefile -*-

// Thin public E203 shell; upstream CPU, ROM, ITCM, DTCM and peripherals are unchanged.
// Default PLL bypass is retained. Software must not reprogram clock/PMU registers.
module e203_cpu_shell(
  input wire clk, lfclk, rst_n,
  output wire  sysper_icb_cmd_valid,
  input wire  sysper_icb_cmd_ready,
  output wire [31:0] sysper_icb_cmd_addr,
  output wire  sysper_icb_cmd_read,
  output wire [31:0] sysper_icb_cmd_wdata,
  output wire [3:0] sysper_icb_cmd_wmask,
  input wire  sysper_icb_rsp_valid,
  output wire  sysper_icb_rsp_ready,
  input wire [31:0] sysper_icb_rsp_rdata,
  input wire  sysper_icb_rsp_err,
  output wire  sysmem_icb_cmd_valid,
  input wire  sysmem_icb_cmd_ready,
  output wire [31:0] sysmem_icb_cmd_addr,
  output wire  sysmem_icb_cmd_read,
  output wire [31:0] sysmem_icb_cmd_wdata,
  output wire [3:0] sysmem_icb_cmd_wmask,
  input wire  sysmem_icb_rsp_valid,
  output wire  sysmem_icb_rsp_ready,
  input wire [31:0] sysmem_icb_rsp_rdata,
  input wire  sysmem_icb_rsp_err,
  output wire bus_clk, bus_rst_n
);
  assign bus_clk=clk;
  assign bus_rst_n=rst_n;
  wire sysfio_valid;
  wire sysfio_ready;
  wire sysfio_rsp_ready;
  reg sysfio_pending;
  assign sysfio_ready=~sysfio_pending;
  always @(posedge clk or negedge rst_n)
    if (!rst_n) sysfio_pending<=0;
    else if (sysfio_valid && sysfio_ready) sysfio_pending<=1;
    else if (sysfio_pending && sysfio_rsp_ready) sysfio_pending<=0;
  e203_subsys_top u_subsys(
    .hfextclk(clk),
    .lfextclk(lfclk),
    .io_pads_aon_erst_n_i_ival(rst_n),
    .io_pads_dbgmode0_n_i_ival(1'b1),
    .io_pads_dbgmode1_n_i_ival(1'b1),
    .io_pads_dbgmode2_n_i_ival(1'b1),
    .io_pads_bootrom_n_i_ival('0),
    .io_pads_aon_pmu_dwakeup_n_i_ival(1'b1),
    .io_pads_aon_pmu_vddpaden_i_ival(1'b1),
    .io_pads_aon_pmu_padrst_i_ival(1'b1),
    .core_mhartid('0),
    .ext2itcm_icb_cmd_valid('0),
    .ext2itcm_icb_cmd_addr('0),
    .ext2itcm_icb_cmd_read('0),
    .ext2itcm_icb_cmd_wdata('0),
    .ext2itcm_icb_cmd_wmask('0),
    .ext2itcm_icb_rsp_ready('0),
    .ext2dtcm_icb_cmd_valid('0),
    .ext2dtcm_icb_cmd_addr('0),
    .ext2dtcm_icb_cmd_read('0),
    .ext2dtcm_icb_cmd_wdata('0),
    .ext2dtcm_icb_cmd_wmask('0),
    .ext2dtcm_icb_rsp_ready('0),
    .sysper_icb_cmd_ready(sysper_icb_cmd_ready),
    .sysper_icb_rsp_valid(sysper_icb_rsp_valid),
    .sysper_icb_rsp_err(sysper_icb_rsp_err),
    .sysper_icb_rsp_rdata(sysper_icb_rsp_rdata),
    .sysfio_icb_cmd_ready(sysfio_ready),
    .sysfio_icb_rsp_valid(sysfio_pending),
    .sysfio_icb_rsp_ready(sysfio_rsp_ready),
    .sysfio_icb_rsp_err(1'b1),
    .sysfio_icb_rsp_rdata(32'b0),
    .sysmem_icb_cmd_ready(sysmem_icb_cmd_ready),
    .sysmem_icb_rsp_valid(sysmem_icb_rsp_valid),
    .sysmem_icb_rsp_err(sysmem_icb_rsp_err),
    .sysmem_icb_rsp_rdata(sysmem_icb_rsp_rdata),
    .io_pads_gpioA_i_ival('0),
    .io_pads_gpioB_i_ival('0),
    .io_pads_qspi0_sck_i_ival(1'b1),
    .io_pads_qspi0_dq_0_i_ival(1'b1),
    .io_pads_qspi0_dq_1_i_ival(1'b1),
    .io_pads_qspi0_dq_2_i_ival(1'b1),
    .io_pads_qspi0_dq_3_i_ival(1'b1),
    .io_pads_qspi0_cs_0_i_ival(1'b1),
    .io_pads_jtag_TCK_i_ival('0),
    .io_pads_jtag_TMS_i_ival(1'b1),
    .io_pads_jtag_TDI_i_ival(1'b1),
    .io_pads_jtag_TDO_i_ival(1'b1),
    .io_pads_jtag_TRST_n_i_ival(1'b1),
    .test_iso_override('0),
    .test_mode('0),
    .sysper_icb_cmd_valid(sysper_icb_cmd_valid),
    .sysper_icb_cmd_addr(sysper_icb_cmd_addr),
    .sysper_icb_cmd_read(sysper_icb_cmd_read),
    .sysper_icb_cmd_wdata(sysper_icb_cmd_wdata),
    .sysper_icb_cmd_wmask(sysper_icb_cmd_wmask),
    .sysper_icb_rsp_ready(sysper_icb_rsp_ready),
    .sysmem_icb_cmd_valid(sysmem_icb_cmd_valid),
    .sysmem_icb_cmd_addr(sysmem_icb_cmd_addr),
    .sysmem_icb_cmd_read(sysmem_icb_cmd_read),
    .sysmem_icb_cmd_wdata(sysmem_icb_cmd_wdata),
    .sysmem_icb_cmd_wmask(sysmem_icb_cmd_wmask),
    .sysmem_icb_rsp_ready(sysmem_icb_rsp_ready),
    .sysfio_icb_cmd_valid(sysfio_valid)
  );
endmodule

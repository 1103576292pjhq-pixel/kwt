 /*                                                                      
 Copyright 2018-2020 Nuclei System Technology, Inc.                
                                                                         
 Licensed under the Apache License, Version 2.0 (the "License");         
 you may not use this file except in compliance with the License.        
 You may obtain a copy of the License at                                 
                                                                         
     http://www.apache.org/licenses/LICENSE-2.0                          
                                                                         
  Unless required by applicable law or agreed to in writing, software    
 distributed under the License is distributed on an "AS IS" BASIS,       
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and     
 limitations under the License.                                          
 */                                                                      
                                                                         
                                                                         
                                                                         
module kwt_dma_soc_top(

    // This clock should comes from the crystal pad generated high speed clock (16MHz)
  input  hfextclk,
  output hfxoscen,// The signal to enable the crystal pad generated clock

  // This clock should comes from the crystal pad generated low speed clock (32.768KHz)
  input  lfextclk,
  output lfxoscen,// The signal to enable the crystal pad generated clock


  // The JTAG TCK is input, need to be pull-up
  input   io_pads_jtag_TCK_i_ival,

  // The JTAG TMS is input, need to be pull-up
  input   io_pads_jtag_TMS_i_ival,

  // The JTAG TDI is input, need to be pull-up
  input   io_pads_jtag_TDI_i_ival,

  // The JTAG TDO is output have enable
  output  io_pads_jtag_TDO_o_oval,
  output  io_pads_jtag_TDO_o_oe,

  // The GPIO are all bidir pad have enables
  input  [32-1:0] io_pads_gpioA_i_ival,
  output [32-1:0] io_pads_gpioA_o_oval,
  output [32-1:0] io_pads_gpioA_o_oe,

  input  [32-1:0] io_pads_gpioB_i_ival,
  output [32-1:0] io_pads_gpioB_o_oval,
  output [32-1:0] io_pads_gpioB_o_oe,

  //QSPI0 SCK and CS is output without enable
  output  io_pads_qspi0_sck_o_oval,
  output  io_pads_qspi0_cs_0_o_oval,

  //QSPI0 DQ is bidir I/O with enable, and need pull-up enable
  input   io_pads_qspi0_dq_0_i_ival,
  output  io_pads_qspi0_dq_0_o_oval,
  output  io_pads_qspi0_dq_0_o_oe,
  input   io_pads_qspi0_dq_1_i_ival,
  output  io_pads_qspi0_dq_1_o_oval,
  output  io_pads_qspi0_dq_1_o_oe,
  input   io_pads_qspi0_dq_2_i_ival,
  output  io_pads_qspi0_dq_2_o_oval,
  output  io_pads_qspi0_dq_2_o_oe,
  input   io_pads_qspi0_dq_3_i_ival,
  output  io_pads_qspi0_dq_3_o_oval,
  output  io_pads_qspi0_dq_3_o_oe,
  
  // Erst is input need to be pull-up by default
  input   io_pads_aon_erst_n_i_ival,

  // dbgmode are inputs need to be pull-up by default
  input  io_pads_dbgmode0_n_i_ival,
  input  io_pads_dbgmode1_n_i_ival,
  input  io_pads_dbgmode2_n_i_ival,

  // BootRom is input need to be pull-up by default
  input  io_pads_bootrom_n_i_ival,


  // dwakeup is input need to be pull-up by default
  input  io_pads_aon_pmu_dwakeup_n_i_ival,

      // PMU output is just output without enable
  output io_pads_aon_pmu_padrst_o_oval,
  output io_pads_aon_pmu_vddpaden_o_oval 
);
wire kwt_dma_mem_cmd_valid;
wire kwt_dma_mem_cmd_ready;
wire [31:0] kwt_dma_mem_cmd_addr;
wire kwt_dma_mem_cmd_read;
wire [31:0] kwt_dma_mem_cmd_wdata;
wire [3:0] kwt_dma_mem_cmd_wmask;
wire kwt_dma_mem_rsp_valid;
wire kwt_dma_mem_rsp_ready;
wire [31:0] kwt_dma_mem_rsp_rdata;
wire kwt_dma_mem_rsp_err;



 
 wire sysper_icb_cmd_valid;
 wire sysper_icb_cmd_ready;

 // KWT integration wires; SysPer is connected to one accelerator slave.
 wire kwt_bus_clk;
 wire kwt_bus_rst_n;
 wire [`E203_ADDR_SIZE-1:0] sysper_icb_cmd_addr;
 wire sysper_icb_cmd_read;
 wire [`E203_XLEN-1:0] sysper_icb_cmd_wdata;
 wire [`E203_XLEN/8-1:0] sysper_icb_cmd_wmask;
 wire sysper_icb_rsp_valid;
 wire sysper_icb_rsp_ready;
 wire sysper_icb_rsp_err;
 wire [`E203_XLEN-1:0] sysper_icb_rsp_rdata;


 wire sysfio_icb_cmd_valid;
 wire sysfio_icb_cmd_ready;

 wire sysmem_icb_cmd_valid;
 wire sysmem_icb_cmd_ready;

 // Shared SRAM is separate from accelerator-local X/W SRAM.
 wire [31:0] sysmem_icb_cmd_addr;
 wire sysmem_icb_cmd_read;
 wire [31:0] sysmem_icb_cmd_wdata;
 wire [3:0] sysmem_icb_cmd_wmask;
 wire sysmem_icb_rsp_valid,sysmem_icb_rsp_ready,sysmem_icb_rsp_err;
 wire [31:0] sysmem_icb_rsp_rdata;


 e203_subsys_top u_e203_subsys_top(
      .kwt_dma_mem_cmd_valid(kwt_dma_mem_cmd_valid),
  .kwt_dma_mem_cmd_ready(kwt_dma_mem_cmd_ready),
  .kwt_dma_mem_cmd_addr(kwt_dma_mem_cmd_addr),
  .kwt_dma_mem_cmd_read(kwt_dma_mem_cmd_read),
  .kwt_dma_mem_cmd_wdata(kwt_dma_mem_cmd_wdata),
  .kwt_dma_mem_cmd_wmask(kwt_dma_mem_cmd_wmask),
  .kwt_dma_mem_rsp_valid(kwt_dma_mem_rsp_valid),
  .kwt_dma_mem_rsp_ready(kwt_dma_mem_rsp_ready),
  .kwt_dma_mem_rsp_rdata(kwt_dma_mem_rsp_rdata),
  .kwt_dma_mem_rsp_err(kwt_dma_mem_rsp_err),
.kwt_bus_clk(kwt_bus_clk),
    .kwt_bus_rst_n(kwt_bus_rst_n),

    .core_mhartid      (1'b0),
  



  `ifdef E203_HAS_ITCM_EXTITF //{
    .ext2itcm_icb_cmd_valid  (1'b0),
    .ext2itcm_icb_cmd_ready  (),
    .ext2itcm_icb_cmd_addr   (`E203_ITCM_ADDR_WIDTH'b0 ),
    .ext2itcm_icb_cmd_read   (1'b0 ),
    .ext2itcm_icb_cmd_wdata  (32'b0),
    .ext2itcm_icb_cmd_wmask  (4'b0),
    
    .ext2itcm_icb_rsp_valid  (),
    .ext2itcm_icb_rsp_ready  (1'b0),
    .ext2itcm_icb_rsp_err    (),
    .ext2itcm_icb_rsp_rdata  (),
  `endif//}

  `ifdef E203_HAS_DTCM_EXTITF //{
    .ext2dtcm_icb_cmd_valid  (1'b0),
    .ext2dtcm_icb_cmd_ready  (),
    .ext2dtcm_icb_cmd_addr   (`E203_DTCM_ADDR_WIDTH'b0 ),
    .ext2dtcm_icb_cmd_read   (1'b0 ),
    .ext2dtcm_icb_cmd_wdata  (32'b0),
    .ext2dtcm_icb_cmd_wmask  (4'b0),
    
    .ext2dtcm_icb_rsp_valid  (),
    .ext2dtcm_icb_rsp_ready  (1'b0),
    .ext2dtcm_icb_rsp_err    (),
    .ext2dtcm_icb_rsp_rdata  (),
  `endif//}

  .sysper_icb_cmd_valid(sysper_icb_cmd_valid),
  .sysper_icb_cmd_ready(sysper_icb_cmd_ready),
  .sysper_icb_cmd_read(sysper_icb_cmd_read), 
  .sysper_icb_cmd_addr(sysper_icb_cmd_addr), 
  .sysper_icb_cmd_wdata(sysper_icb_cmd_wdata), 
  .sysper_icb_cmd_wmask(sysper_icb_cmd_wmask), 
  
  .sysper_icb_rsp_valid(sysper_icb_rsp_valid),
  .sysper_icb_rsp_ready(sysper_icb_rsp_ready),
  .sysper_icb_rsp_err(sysper_icb_rsp_err),
  .sysper_icb_rsp_rdata(sysper_icb_rsp_rdata),


  .sysfio_icb_cmd_valid(sysfio_icb_cmd_valid),
  .sysfio_icb_cmd_ready(sysfio_icb_cmd_ready),
  .sysfio_icb_cmd_read (), 
  .sysfio_icb_cmd_addr (), 
  .sysfio_icb_cmd_wdata(), 
  .sysfio_icb_cmd_wmask(), 
   
  .sysfio_icb_rsp_valid(sysfio_icb_cmd_valid),
  .sysfio_icb_rsp_ready(sysfio_icb_cmd_ready),
  .sysfio_icb_rsp_err  (1'b0  ),
  .sysfio_icb_rsp_rdata(32'b0),

  .sysmem_icb_cmd_valid(sysmem_icb_cmd_valid),
  .sysmem_icb_cmd_ready(sysmem_icb_cmd_ready),
  .sysmem_icb_cmd_read(sysmem_icb_cmd_read), 
  .sysmem_icb_cmd_addr(sysmem_icb_cmd_addr), 
  .sysmem_icb_cmd_wdata(sysmem_icb_cmd_wdata), 
  .sysmem_icb_cmd_wmask(sysmem_icb_cmd_wmask), 

  .sysmem_icb_rsp_valid(sysmem_icb_rsp_valid),
  .sysmem_icb_rsp_ready(sysmem_icb_rsp_ready),
  .sysmem_icb_rsp_err(sysmem_icb_rsp_err),
  .sysmem_icb_rsp_rdata(sysmem_icb_rsp_rdata),

  .io_pads_jtag_TCK_i_ival    (io_pads_jtag_TCK_i_ival    ),
  .io_pads_jtag_TCK_o_oval    (),
  .io_pads_jtag_TCK_o_oe      (),
  .io_pads_jtag_TCK_o_ie      (),
  .io_pads_jtag_TCK_o_pue     (),
  .io_pads_jtag_TCK_o_ds      (),

  .io_pads_jtag_TMS_i_ival    (io_pads_jtag_TMS_i_ival    ),
  .io_pads_jtag_TMS_o_oval    (),
  .io_pads_jtag_TMS_o_oe      (),
  .io_pads_jtag_TMS_o_ie      (),
  .io_pads_jtag_TMS_o_pue     (),
  .io_pads_jtag_TMS_o_ds      (),

  .io_pads_jtag_TDI_i_ival    (io_pads_jtag_TDI_i_ival    ),
  .io_pads_jtag_TDI_o_oval    (),
  .io_pads_jtag_TDI_o_oe      (),
  .io_pads_jtag_TDI_o_ie      (),
  .io_pads_jtag_TDI_o_pue     (),
  .io_pads_jtag_TDI_o_ds      (),

  .io_pads_jtag_TDO_i_ival    (1'b1    ),
  .io_pads_jtag_TDO_o_oval    (io_pads_jtag_TDO_o_oval    ),
  .io_pads_jtag_TDO_o_oe      (io_pads_jtag_TDO_o_oe      ),
  .io_pads_jtag_TDO_o_ie      (),
  .io_pads_jtag_TDO_o_pue     (),
  .io_pads_jtag_TDO_o_ds      (),

  .io_pads_jtag_TRST_n_i_ival (1'b1 ),
  .io_pads_jtag_TRST_n_o_oval (),
  .io_pads_jtag_TRST_n_o_oe   (),
  .io_pads_jtag_TRST_n_o_ie   (),
  .io_pads_jtag_TRST_n_o_pue  (),
  .io_pads_jtag_TRST_n_o_ds   (),

  .test_mode(1'b0),
  .test_iso_override(1'b0),

  .io_pads_gpioA_i_ival       (io_pads_gpioA_i_ival),
  .io_pads_gpioA_o_oval       (io_pads_gpioA_o_oval),
  .io_pads_gpioA_o_oe         (io_pads_gpioA_o_oe), 

  .io_pads_gpioB_i_ival       (io_pads_gpioB_i_ival),
  .io_pads_gpioB_o_oval       (io_pads_gpioB_o_oval),
  .io_pads_gpioB_o_oe         (io_pads_gpioB_o_oe), 

  .io_pads_qspi0_sck_i_ival   (1'b1),
  .io_pads_qspi0_sck_o_oval   (io_pads_qspi0_sck_o_oval),
  .io_pads_qspi0_sck_o_oe     (),
  .io_pads_qspi0_dq_0_i_ival  (io_pads_qspi0_dq_0_i_ival),
  .io_pads_qspi0_dq_0_o_oval  (io_pads_qspi0_dq_0_o_oval),
  .io_pads_qspi0_dq_0_o_oe    (io_pads_qspi0_dq_0_o_oe),
  .io_pads_qspi0_dq_1_i_ival  (io_pads_qspi0_dq_1_i_ival),
  .io_pads_qspi0_dq_1_o_oval  (io_pads_qspi0_dq_1_o_oval),
  .io_pads_qspi0_dq_1_o_oe    (io_pads_qspi0_dq_1_o_oe),
  .io_pads_qspi0_dq_2_i_ival  (io_pads_qspi0_dq_2_i_ival),
  .io_pads_qspi0_dq_2_o_oval  (io_pads_qspi0_dq_2_o_oval),
  .io_pads_qspi0_dq_2_o_oe    (io_pads_qspi0_dq_2_o_oe),
  .io_pads_qspi0_dq_3_i_ival  (io_pads_qspi0_dq_3_i_ival),
  .io_pads_qspi0_dq_3_o_oval  (io_pads_qspi0_dq_3_o_oval),
  .io_pads_qspi0_dq_3_o_oe    (io_pads_qspi0_dq_3_o_oe),
  .io_pads_qspi0_cs_0_i_ival  (1'b1),
  .io_pads_qspi0_cs_0_o_oval  (io_pads_qspi0_cs_0_o_oval),
  .io_pads_qspi0_cs_0_o_oe    (), 

    .hfextclk        (hfextclk),
    .hfxoscen        (hfxoscen),
    .lfextclk        (lfextclk),
    .lfxoscen        (lfxoscen),

  .io_pads_aon_erst_n_i_ival        (io_pads_aon_erst_n_i_ival       ), 
  .io_pads_aon_erst_n_o_oval        (),
  .io_pads_aon_erst_n_o_oe          (),
  .io_pads_aon_erst_n_o_ie          (),
  .io_pads_aon_erst_n_o_pue         (),
  .io_pads_aon_erst_n_o_ds          (),
  .io_pads_aon_pmu_dwakeup_n_i_ival (io_pads_aon_pmu_dwakeup_n_i_ival),
  .io_pads_aon_pmu_dwakeup_n_o_oval (),
  .io_pads_aon_pmu_dwakeup_n_o_oe   (),
  .io_pads_aon_pmu_dwakeup_n_o_ie   (),
  .io_pads_aon_pmu_dwakeup_n_o_pue  (),
  .io_pads_aon_pmu_dwakeup_n_o_ds   (),
  .io_pads_aon_pmu_vddpaden_i_ival  (1'b1 ),
  .io_pads_aon_pmu_vddpaden_o_oval  (io_pads_aon_pmu_vddpaden_o_oval ),
  .io_pads_aon_pmu_vddpaden_o_oe    (),
  .io_pads_aon_pmu_vddpaden_o_ie    (),
  .io_pads_aon_pmu_vddpaden_o_pue   (),
  .io_pads_aon_pmu_vddpaden_o_ds    (),

  
    .io_pads_aon_pmu_padrst_i_ival    (1'b1 ),
    .io_pads_aon_pmu_padrst_o_oval    (io_pads_aon_pmu_padrst_o_oval ),
    .io_pads_aon_pmu_padrst_o_oe      (),
    .io_pads_aon_pmu_padrst_o_ie      (),
    .io_pads_aon_pmu_padrst_o_pue     (),
    .io_pads_aon_pmu_padrst_o_ds      (),

    .io_pads_bootrom_n_i_ival       (io_pads_bootrom_n_i_ival),
    .io_pads_bootrom_n_o_oval       (),
    .io_pads_bootrom_n_o_oe         (),
    .io_pads_bootrom_n_o_ie         (),
    .io_pads_bootrom_n_o_pue        (),
    .io_pads_bootrom_n_o_ds         (),

    .io_pads_dbgmode0_n_i_ival       (io_pads_dbgmode0_n_i_ival),

    .io_pads_dbgmode1_n_i_ival       (io_pads_dbgmode1_n_i_ival),

    .io_pads_dbgmode2_n_i_ival       (io_pads_dbgmode2_n_i_ival) 


  );



 // Project development address; software polls the current custom ICB ABI.
 // Functional SRAM configuration: ARM_UD_MODEL at compilation, EMA=2/EMAW=0.
 kwt_dma_accelerator #(
   .BASE_ADDR(32'h11000000),
   .SRAM_EMA(3'd2),
   .SRAM_EMAW(2'd0)
 ) u_kwt_accelerator(
.clk(kwt_bus_clk),
.rst_n(kwt_bus_rst_n),
.icb_cmd_valid(sysper_icb_cmd_valid),
.icb_cmd_ready(sysper_icb_cmd_ready),
.icb_cmd_addr(sysper_icb_cmd_addr),
.icb_cmd_read(sysper_icb_cmd_read),
.icb_cmd_wdata(sysper_icb_cmd_wdata),
.icb_cmd_wmask(sysper_icb_cmd_wmask),
.icb_rsp_valid(sysper_icb_rsp_valid),
.icb_rsp_ready(sysper_icb_rsp_ready),
.icb_rsp_rdata(sysper_icb_rsp_rdata),
.icb_rsp_err(sysper_icb_rsp_err),
.mem_cmd_valid(kwt_dma_mem_cmd_valid),
.mem_cmd_ready(kwt_dma_mem_cmd_ready),
.mem_cmd_addr(kwt_dma_mem_cmd_addr),
.mem_cmd_read(kwt_dma_mem_cmd_read),
.mem_cmd_wdata(kwt_dma_mem_cmd_wdata),
.mem_cmd_wmask(kwt_dma_mem_cmd_wmask),
.mem_rsp_valid(kwt_dma_mem_rsp_valid),
.mem_rsp_ready(kwt_dma_mem_rsp_ready),
.mem_rsp_rdata(kwt_dma_mem_rsp_rdata),
.mem_rsp_err(kwt_dma_mem_rsp_err),
.irq()
);


 // DEVELOPMENT shared window, pending official address-map confirmation.
 kwt_shared_sram #(.BASE_ADDR(32'ha0000000),.SRAM_EMA(3'd2),.SRAM_EMAW(2'd0)) u_shared_sram(
   .clk(kwt_bus_clk),.rst_n(kwt_bus_rst_n),
   .icb_cmd_valid(sysmem_icb_cmd_valid),.icb_cmd_ready(sysmem_icb_cmd_ready),
   .icb_cmd_addr(sysmem_icb_cmd_addr),.icb_cmd_read(sysmem_icb_cmd_read),
   .icb_cmd_wdata(sysmem_icb_cmd_wdata),.icb_cmd_wmask(sysmem_icb_cmd_wmask),
   .icb_rsp_valid(sysmem_icb_rsp_valid),.icb_rsp_ready(sysmem_icb_rsp_ready),
   .icb_rsp_rdata(sysmem_icb_rsp_rdata),.icb_rsp_err(sysmem_icb_rsp_err));



endmodule

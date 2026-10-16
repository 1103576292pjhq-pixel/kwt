// Public E203 shell + shared 512KiB RAM + original FFN1 and new encoder windows.
module e203_encoder_soc #(parameter M=99,D=64,H=256)(input wire clk,lfclk,rst_n,
 output wire observed_mmio_valid,output wire [31:0] observed_mmio_addr,
 output wire [31:0] observed_mmio_data,output wire [31:0] observed_response);
 wire bus_clk,bus_rst_n;
 wire sysper_icb_cmd_valid,sysper_icb_cmd_ready,sysper_icb_cmd_read;
 wire [31:0] sysper_icb_cmd_addr,sysper_icb_cmd_wdata;
 wire [3:0] sysper_icb_cmd_wmask;
 wire sysper_icb_rsp_valid,sysper_icb_rsp_ready,sysper_icb_rsp_err;
 wire [31:0] sysper_icb_rsp_rdata;
 wire sysmem_icb_cmd_valid,sysmem_icb_cmd_ready,sysmem_icb_cmd_read;
 wire [31:0] sysmem_icb_cmd_addr,sysmem_icb_cmd_wdata;
 wire [3:0] sysmem_icb_cmd_wmask;
 wire sysmem_icb_rsp_valid,sysmem_icb_rsp_ready,sysmem_icb_rsp_err;
 wire [31:0] sysmem_icb_rsp_rdata;
 assign observed_mmio_valid=sysper_icb_cmd_valid;
 assign observed_mmio_addr=sysper_icb_cmd_addr;
 assign observed_mmio_data=sysper_icb_cmd_wdata;
 assign observed_response=sysper_icb_rsp_rdata;
 e203_cpu_shell cpu(.*);
 encoder_shared_ram ram(.clk(bus_clk),.rst_n(bus_rst_n),
  .icb_cmd_valid(sysmem_icb_cmd_valid),.icb_cmd_ready(sysmem_icb_cmd_ready),
  .icb_cmd_addr(sysmem_icb_cmd_addr),.icb_cmd_read(sysmem_icb_cmd_read),
  .icb_cmd_wdata(sysmem_icb_cmd_wdata),.icb_cmd_wmask(sysmem_icb_cmd_wmask),
  .icb_rsp_valid(sysmem_icb_rsp_valid),.icb_rsp_ready(sysmem_icb_rsp_ready),
  .icb_rsp_rdata(sysmem_icb_rsp_rdata),.icb_rsp_err(sysmem_icb_rsp_err));
 wire is_ffn=(sysper_icb_cmd_addr[31:8]==24'h110000);
 reg pending,selected_ffn;
 wire fready,frvalid,frerr,eready,ervalid,ererr;
 wire [31:0] frdata,erdata;
 assign sysper_icb_cmd_ready=!pending&&(is_ffn?fready:eready);
 assign sysper_icb_rsp_valid=pending&&(selected_ffn?frvalid:ervalid);
 assign sysper_icb_rsp_rdata=selected_ffn?frdata:erdata;
 assign sysper_icb_rsp_err=selected_ffn?frerr:ererr;
 always @(posedge bus_clk)begin
  if(!bus_rst_n)begin pending<=0;selected_ffn<=0;end
  else if(sysper_icb_cmd_valid&&sysper_icb_cmd_ready)begin pending<=1;selected_ffn<=is_ffn;end
  else if(sysper_icb_rsp_valid&&sysper_icb_rsp_ready)pending<=0;
 end
 ffn1_icb #(.M(M),.N(H)) ffn1(.clk(bus_clk),.rst_n(bus_rst_n),
  .icb_cmd_valid(sysper_icb_cmd_valid&&!pending&&is_ffn),.icb_cmd_ready(fready),
  .icb_cmd_addr(sysper_icb_cmd_addr),.icb_cmd_read(sysper_icb_cmd_read),
  .icb_cmd_wdata(sysper_icb_cmd_wdata),.icb_cmd_wmask(sysper_icb_cmd_wmask),
  .icb_rsp_valid(frvalid),.icb_rsp_ready(pending&&selected_ffn&&sysper_icb_rsp_ready),
  .icb_rsp_rdata(frdata),.icb_rsp_err(frerr));
 encoder_icb #(.M(M),.D(D),.H(H)) encoder(.clk(bus_clk),.rst_n(bus_rst_n),
  .icb_cmd_valid(sysper_icb_cmd_valid&&!pending&&!is_ffn),.icb_cmd_ready(eready),
  .icb_cmd_addr(sysper_icb_cmd_addr),.icb_cmd_read(sysper_icb_cmd_read),
  .icb_cmd_wdata(sysper_icb_cmd_wdata),.icb_cmd_wmask(sysper_icb_cmd_wmask),
  .icb_rsp_valid(ervalid),.icb_rsp_ready(pending&&!selected_ffn&&sysper_icb_rsp_ready),
  .icb_rsp_rdata(erdata),.icb_rsp_err(ererr));
endmodule

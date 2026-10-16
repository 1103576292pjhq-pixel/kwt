`timescale 1ns/1ps
`include "e203_defines.v"
module tb_e203_encoder;
 parameter M=99,D=64,H=256;
 localparam WORDS=4*D*D+2*D*H+H+6*D;
 reg clk=0,lfclk=0,rst_n=0;
 always #2 clk=~clk;always #33 lfclk=~lfclk;
 e203_encoder_soc #(.M(M),.D(D),.H(H)) dut(.clk(clk),.lfclk(lfclk),.rst_n(rst_n));
 `define ITCM dut.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_srams.u_e203_itcm_ram.u_e203_itcm_gnrl_ram.u_sirv_sim_ram
 `define DTCM dut.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_srams.u_e203_dtcm_ram.u_e203_dtcm_gnrl_ram.u_sirv_sim_ram
 `define CORE dut.cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.u_e203_core
 reg [7:0] firmware[0:65535];reg [31:0] expected[0:12*M*D-1];
 reg [31:0] host_weights[0:WORDS-1];
 string path;integer bytes,i,j,outfile,index,policy,neuralfile,progressfile;
 integer cycles=0,instructions=0,outputs=0,starts=0,weight_writes=0,input_writes=0,requests=0;
 integer mmio_reads=0,mmio_writes=0,bus_waits=0,load_start,load_end;
 integer neural_words=0,shared_reads=0,shared_writes=0,first_cycle=-1,last_cycle=-1;
 integer host_word_writes=0,final_shared_reads=0,final_shared_writes=0;
 reg host_pending=0,terminal=0;integer requested_layer;
 initial begin
  if(!$value$plusargs("BYTES=%d",bytes))$fatal(1,"firmware bytes");
  if(!$value$plusargs("POLICY=%d",policy))policy=0;
  if(bytes<1||bytes>65536)$fatal(1,"firmware size");
  for(i=0;i<65536;i=i+1)firmware[i]=0;
  $readmemh("firmware.hex",firmware,0,bytes-1);
  for(i=0;i<`E203_ITCM_RAM_DP;i=i+1)
   `ITCM.mem_r[i]={firmware[8*i+7],firmware[8*i+6],firmware[8*i+5],firmware[8*i+4],firmware[8*i+3],firmware[8*i+2],firmware[8*i+1],firmware[8*i]};
  for(i=0;i<`E203_DTCM_RAM_DP;i=i+1)`DTCM.mem_r[i]=32'ha5a5a5a5;
  // Fixture writes only public shared RAM, never an encoder internal array.
  for(i=0;i<64;i=i+1)dut.ram.mem[i]=0;
  $readmemh("input.hex",dut.ram.mem,1024,1024+M*D-1);
  $readmemh("expected.hex",expected);
  outfile=$fopen("cpu-output.hex","w");if(!outfile)$fatal(1,"output file");
  neuralfile=$fopen("neural-output.hex","w");if(!neuralfile)$fatal(1,"neural output file");
  #120 rst_n=1;
 end
 // Host is an external parameter supplier at an explicit CPU mailbox boundary.
 // It consumes a real cycle per word. ready is published only after all writes.
 initial begin
  forever begin
   wait(host_pending);requested_layer=dut.ram.mem[8];
   if(requested_layer!==requests || requested_layer>=12)$fatal(1,"layer request sequence");
   path=$sformatf("weights/layer_%02d.hex",requested_layer);
   $readmemh(path,host_weights);load_start=cycles;
   for(j=0;j<WORDS;j=j+1)begin @(negedge clk);dut.ram.mem[8192+j]=host_weights[j];host_word_writes=host_word_writes+1;end
   @(negedge clk);dut.ram.mem[9]=requested_layer;load_end=cycles;
   $display("HOST_LAYER_LOAD layer=%0d words=%0d begin=%0d end=%0d cycles=%0d",requested_layer,WORDS,load_start,load_end,load_end-load_start);$fflush();
   requests=requests+1;host_pending=0;
  end
 end
 always @(posedge clk)if(rst_n)begin
  cycles<=cycles+1;
  if(`CORE.ifu_o_valid&&`CORE.ifu_o_ready)instructions<=instructions+1;
  if(cycles%1000000==0)begin
   $display("E203_ENCODER_PROGRESS cycles=%0d layers=%0d outputs=%0d instructions=%0d pc=%h",cycles,starts,outputs,instructions,`CORE.ifu_o_pc);$fflush();
   progressfile=$fopen("cycle-progress.json","w");
   $fdisplay(progressfile,"{\"cycles\":%0d,\"started_layers\":%0d,\"neural_words\":%0d,\"cpu_outputs\":%0d,\"instructions\":%0d}",cycles,starts,neural_words,outputs,instructions);$fclose(progressfile);
  end
  // Passive monitor validates each actual neural output regardless of CPU policy.
  if(dut.encoder.core.trace_valid&&dut.encoder.core.trace_stage==13)begin
   if(dut.encoder.core.trace_addr!==neural_words%(M*D)||dut.encoder.core.trace_data!==expected[neural_words])$fatal(1,"passive neural output mismatch word=%0d",neural_words);
   $fdisplay(neuralfile,"%08x",dut.encoder.core.trace_data);neural_words<=neural_words+1;
  end
  if(dut.sysper_icb_cmd_valid&&!dut.sysper_icb_cmd_ready)bus_waits<=bus_waits+1;
  if(dut.sysper_icb_cmd_valid&&dut.sysper_icb_cmd_ready)begin
   if(first_cycle<0)first_cycle<=cycles;
   if(dut.sysper_icb_cmd_read)mmio_reads<=mmio_reads+1;
   else begin
    mmio_writes<=mmio_writes+1;
    case(dut.sysper_icb_cmd_addr)
     32'h11010008:if(dut.sysper_icb_cmd_wdata==3)begin starts<=starts+1;$display("CPU_ENCODER_START layer=%0d cycle=%0d",starts,cycles);end
     32'h11010014:input_writes<=input_writes+1;
     32'h11010018:weight_writes<=weight_writes+1;
     default:begin end
    endcase
   end
  end
  if(dut.sysmem_icb_cmd_valid&&dut.sysmem_icb_cmd_ready)begin
   if(dut.sysmem_icb_cmd_read)shared_reads<=shared_reads+1;
   else shared_writes<=shared_writes+1;
  end
  if(dut.sysmem_icb_cmd_valid&&dut.sysmem_icb_cmd_ready&&!dut.sysmem_icb_cmd_read)begin
   if(dut.sysmem_icb_cmd_addr==32'ha0000028&&dut.sysmem_icb_cmd_wdata==32'h4c4f4144)begin
    if(host_pending)$fatal(1,"overlapping parameter request");host_pending<=1;
   end
   if(dut.sysmem_icb_cmd_addr>=32'ha0040000&&dut.sysmem_icb_cmd_addr<32'ha0040000+M*D*4)begin
    index=(dut.sysmem_icb_cmd_addr-32'ha0040000)/4;
    if(index!=outputs%(M*D)||dut.sysmem_icb_cmd_wmask!=15)$fatal(1,"CPU output order/mask");
    if(dut.sysmem_icb_cmd_wdata!==expected[(policy==1?11*M*D:0)+outputs])$fatal(1,"CPU output mismatch word=%0d got=%08x",outputs,dut.sysmem_icb_cmd_wdata);
    $fdisplay(outfile,"%08x",dut.sysmem_icb_cmd_wdata);outputs<=outputs+1;
    last_cycle<=cycles;
    final_shared_reads<=shared_reads;final_shared_writes<=shared_writes+1;
   end
   if(dut.sysmem_icb_cmd_addr==32'ha0000000)terminal<=1;
  end
  if(terminal&&dut.sysmem_icb_rsp_valid&&dut.sysmem_icb_rsp_ready)begin
   $fclose(outfile);$fclose(neuralfile);
   if(dut.ram.mem[0]!==32'h424f4f54||dut.ram.mem[1]!==0)$fatal(1,"CPU failure code=%h cause=%h pc=%h",dut.ram.mem[1],dut.ram.mem[2],dut.ram.mem[3]);
   if(starts!=12||requests!=12||outputs!=(policy==1?M*D:12*M*D)||neural_words!=12*M*D||input_writes!=(policy==2?12*M*D:M*D)||weight_writes!=12*WORDS||instructions<100)$fatal(1,"CPU incomplete coverage");
   $display("E203_ENCODER_PASS layers=12 outputs=%0d neural_words=%0d cycles=%0d instructions=%0d mmio_reads=%0d mmio_writes=%0d bus_waits=%0d host_words=%0d cpu_weight_words=%0d shared_reads=%0d shared_writes=%0d begin_cycle=%0d final_write_cycle=%0d end_to_end_cycles=%0d policy=%0d",outputs,neural_words,cycles,instructions,mmio_reads,mmio_writes,bus_waits,host_word_writes,weight_writes,final_shared_reads,final_shared_writes,first_cycle,last_cycle,last_cycle-first_cycle+1,policy);
   $finish;
  end
  if(cycles==1000000000)$fatal(1,"CPU watchdog pc=%h layer=%0d outputs=%0d",`CORE.ifu_o_pc,starts,outputs);
 end
endmodule

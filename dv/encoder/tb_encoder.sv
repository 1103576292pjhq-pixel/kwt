`timescale 1ns/1ps
module tb_encoder;
 parameter M=3,D=4,H=8;
 localparam WORDS=4*D*D+2*D*H+H+6*D;
 reg clk=0; always #5 clk=~clk;
 reg rst_n=0,req_valid=0,rsp_ready=0;
 reg [2:0] req_op=0; reg [31:0] req_addr=0,req_data=0;
 wire req_ready,rsp_valid,rsp_error,busy,done,job_done,fault;
 wire [31:0] rsp_data,x_count,w_count,layer_index;
 wire [63:0] cycles; wire [4:0] flags;
 wire trace_valid; wire [3:0] trace_stage; wire [31:0] trace_addr,trace_data;
 encoder_core #(.M(M),.D(D),.H(H)) dut(.*);
 reg [31:0] input_words[0:M*D-1],weights[0:WORDS-1],expected[0:M*D-1];
 string directory,weight_dir,case_dir,path,output_path;
 integer i,l,layer_total,checks=0,outfile,tracefile,watchdog=0;
 reg [31:0] got; reg bad;
 always @(posedge clk) begin
  watchdog<=watchdog+1;
  if(watchdog>1500000000) $fatal(1,"watchdog phase=%0d",dut.phase);
  if(trace_valid && tracefile) $fdisplay(tracefile,"%0d %0d %0d %08x",layer_index,trace_stage,trace_addr,trace_data);
 end
 task transaction(input [2:0] op,input [31:0] addr,input [31:0] data,input bit error_expected);
  reg [31:0] held; reg held_err; integer n;
  begin
   @(negedge clk); req_valid=1;req_op=op;req_addr=addr;req_data=data;rsp_ready=0;
   do @(posedge clk); while(!req_ready);
   @(negedge clk);req_valid=0;
   n=0;
   while(!rsp_valid) begin @(negedge clk);n=n+1;if(n>40)$fatal(1,"command timeout op=%d",op);end
   held=rsp_data;held_err=rsp_error;
   repeat(2) begin @(negedge clk);if(!rsp_valid || rsp_data!==held || rsp_error!==held_err)$fatal(1,"response backpressure");end
   if(rsp_error!==error_expected)$fatal(1,"command op=%d error=%b expected=%b",op,rsp_error,error_expected);
   got=rsp_data;bad=rsp_error;checks=checks+1;
   rsp_ready=1;@(negedge clk);rsp_ready=0;
  end
 endtask
 initial begin
  tracefile=0;
  repeat(3)@(negedge clk);rst_n=1;
  transaction(0,0,0,0);
  transaction(3,0,0,1); // Missing load must be rejected by a running implementation.
  transaction(1,1,0,1); // Noncontiguous input.
  transaction(4,0,0,1); // Read before done.
  transaction(7,0,0,1);
  if(!$value$plusargs("CASE=%s",case_dir)) begin
   $display("ENCODER_PROTOCOL_PASS checks=%0d",checks);$finish;
  end else begin
  if(!$value$plusargs("WEIGHTS=%s",weight_dir)) $fatal(1,"missing weights");
  if(!$value$plusargs("LAYERS=%d",layer_total))layer_total=1;
  if(!$value$plusargs("OUTPUT=%s",output_path))output_path="output.hex";
  outfile=$fopen(output_path,"w");if(!outfile)$fatal(1,"output open");
  if($test$plusargs("TRACE"))tracefile=$fopen("trace.txt","w");
  path={case_dir,"/input.hex"};$readmemh(path,input_words);
  for(i=0;i<M*D;i=i+1)transaction(1,i,input_words[i],0);
  for(l=0;l<layer_total;l=l+1)begin
   if(layer_total==1)path={weight_dir,"/weights.hex"};
   else path=$sformatf("%s/layer_%02d.hex",weight_dir,l);
   $readmemh(path,weights);
   for(i=0;i<WORDS;i=i+1)transaction(2,i,weights[i],0);
   transaction(3,0,l+1,1); // Wrong layer cannot start.
   transaction($test$plusargs("ATTENTION")?6:3,0,l,0);
   transaction(0,0,0,1); // Busy rejection.
   wait(done);@(negedge clk);
   if($test$plusargs("ATTENTION"))path={case_dir,"/attn.hex"};
   else if(layer_total==1)path={case_dir,"/y.hex"};
   else path=$sformatf("%s/layer_%02d/y.hex",case_dir,l);
   $readmemh(path,expected);
   transaction(4,M*D,0,1);
   for(i=0;i<M*D;i=i+1)begin
    transaction(4,i,0,0);
    if(got!==expected[i])$fatal(1,"word mismatch layer=%0d addr=%0d actual=%08x expected=%08x",l,i,got,expected[i]);
    if(got[30:23]==255)$fatal(1,"nonfinite");
    $fdisplay(outfile,"%08x",got);
   end
   $display("ENCODER_LAYER_PASS layer=%0d words=%0d cycles=%0d flags=%02x",l,M*D,cycles,flags);
   $fflush();
   if($test$plusargs("ATTENTION"))transaction(5,0,0,1);
   if(l+1<layer_total)transaction(5,0,0,0);
  end
  if(layer_total==12 && !job_done)$fatal(1,"job_done missing");
  $fclose(outfile);if(tracefile)$fclose(tracefile);
  rst_n=0;repeat(2)@(negedge clk);rst_n=1;
  transaction(3,0,0,1);
  $display("ENCODER_PASS layers=%0d words=%0d checks=%0d",layer_total,layer_total*M*D,checks);$finish;
  end
 end
endmodule

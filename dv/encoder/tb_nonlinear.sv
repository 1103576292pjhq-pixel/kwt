`timescale 1ns/1ps
module tb_nonlinear;
 reg clk=0;always #5 clk=~clk;
 reg rst_n=0,req_valid=0,req_gelu=0,rsp_ready=0;reg [31:0] req_x=0;
 wire req_ready,rsp_valid,rsp_error;wire [31:0] rsp_data;wire [4:0] rsp_flags;
 wire fp_req_valid,fp_req_ready,fp_rsp_valid,fp_rsp_ready,fp_rsp_error,unused_busy;
 wire [3:0] fp_req_op;wire [31:0] fp_req_a,fp_req_b,fp_req_c,fp_rsp_data;wire [4:0] fp_rsp_flags;
 encoder_nonlinear dut(.*);
 encoder_fp32 fpu(.clk(clk),.rst_n(rst_n),.req_valid(fp_req_valid),.req_ready(fp_req_ready),
  .req_op(fp_req_op),.req_a(fp_req_a),.req_b(fp_req_b),.req_c(fp_req_c),
  .rsp_valid(fp_rsp_valid),.rsp_ready(fp_rsp_ready),.rsp_data(fp_rsp_data),
  .rsp_flags(fp_rsp_flags),.rsp_error(fp_rsp_error),.busy(unused_busy));
 integer file,rc,count=0,n,i,watchdog=0;reg [31:0] mode,x,expected,err,held;reg [4:0] held_flags;
 always @(posedge clk)begin watchdog<=watchdog+1;if(watchdog>5000000)$fatal(1,"NL watchdog");end
 always @(posedge clk)if($test$plusargs("DEBUG")&&fp_rsp_valid&&fp_rsp_ready)
  $display("DBG vector=%0d pc=%0d op=%0d a=%h b=%h c=%h result=%h",count,dut.pc,fp_req_op,fp_req_a,fp_req_b,fp_req_c,fp_rsp_data);
 initial begin
  repeat(3)@(negedge clk);rst_n=1;
  file=$fopen("vectors.txt","r");if(!file)$fatal(1,"vectors");
  while(!$feof(file))begin
   rc=$fscanf(file,"%h %h %h %h\n",mode,x,expected,err);
   if(rc!=4)$fatal(1,"vector parse");
   @(negedge clk);req_valid=1;req_gelu=mode[0];req_x=x;rsp_ready=0;
   do @(posedge clk);while(!req_ready);
   @(negedge clk);req_valid=0;n=0;
   while(!rsp_valid)begin @(negedge clk);n=n+1;if(n>500)$fatal(1,"NL timeout");end
   if(rsp_data!==expected||rsp_error!==err[0])$fatal(1,"NL mismatch vector=%0d mode=%0d x=%h got=%h expected=%h",count,mode,x,rsp_data,expected);
   held=rsp_data;held_flags=rsp_flags;
   repeat(count%5)begin @(negedge clk);if(!rsp_valid||rsp_data!==held||rsp_flags!==held_flags)$fatal(1,"NL response hold");end
   rsp_ready=1;@(negedge clk);rsp_ready=0;count=count+1;
  end
  $fclose(file);
  // Interrupt actual internal range-reduction and DIV waits, then no late rsp.
  for(i=0;i<2;i=i+1)begin
   @(negedge clk);req_valid=1;req_gelu=1;req_x=32'h3f000000;
   do @(posedge clk);while(!req_ready);
   @(negedge clk);req_valid=0;
   if(i==0)wait(dut.pc==15);else wait(fp_req_valid&&fp_req_op==4);
   @(negedge clk);rst_n=0;repeat(2)@(negedge clk);rst_n=1;
   repeat(40)@(negedge clk);if(rsp_valid||!req_ready)$fatal(1,"NL reset leaked response");
  end
  $display("ENCODER_NONLINEAR_PASS vectors=%0d reset_interruptions=2",count);$finish;
 end
endmodule

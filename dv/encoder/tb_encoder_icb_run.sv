`timescale 1ns/1ps
module tb_encoder_icb_run;
 reg clk=0;always #5 clk=~clk;
 reg rst_n=0,icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=0;
 reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;reg [3:0] icb_cmd_wmask=15;
 wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;wire [31:0] icb_rsp_rdata;
 encoder_icb #(.M(3),.D(4),.H(8)) dut(.*);
 integer checks=0,n,i,l,watchdog=0;reg [31:0] got;reg [31:0] beta[0:3];
 always @(posedge clk)begin watchdog<=watchdog+1;if(watchdog>100000)$fatal(1,"ICB run watchdog");end
 task bus(input [31:0] offset,input bit reading,input [31:0] value,input bit expect_error);
  reg [31:0] held;reg err;
  begin
   @(negedge clk);icb_cmd_addr=32'h11010000+offset;icb_cmd_read=reading;icb_cmd_wdata=value;
   icb_cmd_valid=1;icb_rsp_ready=0;
   do @(posedge clk);while(!icb_cmd_ready);
   @(negedge clk);icb_cmd_valid=0;n=0;
   while(!icb_rsp_valid)begin @(negedge clk);n=n+1;if(n>20000)$fatal(1,"ICB run transaction timeout");end
   held=icb_rsp_rdata;err=icb_rsp_err;
   repeat(2)begin @(negedge clk);if(!icb_rsp_valid||icb_rsp_rdata!==held||icb_rsp_err!==err)$fatal(1,"ICB run response not held");end
   if(err!==expect_error)$fatal(1,"ICB run offset=%h got err=%b",offset,err);
   got=held;checks=checks+1;icb_rsp_ready=1;@(negedge clk);icb_rsp_ready=0;
  end
 endtask
 task load_data(input bit reload_input);
  begin
   bus(16,0,0,0);
   for(i=0;i<12;i=i+1)bus(20,0,reload_input?beta[i%4]:0,0);
   bus(16,0,0,0);
   for(i=0;i<160;i=i+1)bus(24,0,i>=156?beta[i-156]:0,0);
  end
 endtask
 initial begin
  beta[0]=32'h3f800000;beta[1]=32'hc0000000;beta[2]=32'h3f000000;beta[3]=32'h40800000;
  repeat(3)@(negedge clk);rst_n=1;bus(8,0,0,0);
  for(l=0;l<2;l=l+1)begin
   load_data(l!=0);bus(8,0,3,0);
   bus(16,0,99,1);bus(12,0,7,0); // Busy rejection must not prevent completion.
   bus(68,1,0,0);
   if(n<1000||got[2:0]!=2)$fatal(1,"WAIT_DONE did not wait for real full result n=%0d status=%h",n,got);
   bus(16,0,0,0);
   for(i=0;i<12;i=i+1)begin bus(28,1,0,0);if(got!==beta[i%4])$fatal(1,"ICB complete output");end
   if(l==0)begin
    bus(8,0,7,0);bus(36,1,0,0);if(got!=0)$fatal(1,"RELOAD input validity not cleared");
    bus(8,0,3,1);bus(12,0,7,0);
   end
  end
  bus(8,0,0,0);load_data(0);bus(8,0,6,0);bus(68,1,0,0);
  if(got[2:0]!=2)$fatal(1,"attention done/job_done");
  bus(16,0,0,0);
  for(i=0;i<12;i=i+1)begin bus(28,1,0,0);if(got!==0)$fatal(1,"attention public read");end
  bus(8,0,5,1);bus(8,0,7,1);
  $display("ENCODER_ICB_RUN_PASS checks=%0d full_layers=2 attention_layers=1 wait_done=3 outputs=36",checks);$finish;
 end
endmodule

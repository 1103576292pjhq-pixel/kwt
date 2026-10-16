`timescale 1ns/1ps
module tb_encoder_icb;
 reg clk=0;always #5 clk=~clk;
 reg rst_n=0,icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=0;
 reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;reg [3:0] icb_cmd_wmask=15;
 wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;wire [31:0] icb_rsp_rdata;
 encoder_icb #(.M(3),.D(4),.H(8)) dut(.*);
 integer checks=0,n;reg [31:0] got;
 task transaction(input [31:0] offset,input bit reading,input [31:0] value,input [3:0] mask,input bit error_expected);
  reg [31:0] held;reg err;
  begin
   @(negedge clk);icb_cmd_addr=32'h11010000+offset;icb_cmd_read=reading;
   icb_cmd_wdata=value;icb_cmd_wmask=mask;icb_cmd_valid=1;icb_rsp_ready=0;
   do @(posedge clk);while(!icb_cmd_ready);
   @(negedge clk);icb_cmd_valid=0;n=0;
   while(!icb_rsp_valid)begin @(negedge clk);n=n+1;if(n>50)$fatal(1,"ICB timeout");end
   held=icb_rsp_rdata;err=icb_rsp_err;
   repeat(3)begin @(negedge clk);if(!icb_rsp_valid||icb_rsp_rdata!==held||icb_rsp_err!==err)$fatal(1,"ICB response not held");end
   if(err!==error_expected)$fatal(1,"ICB offset=%h error=%b expected=%b",offset,err,error_expected);
   got=held;checks=checks+1;icb_rsp_ready=1;@(negedge clk);icb_rsp_ready=0;
  end
 endtask
 initial begin
  repeat(3)@(negedge clk);rst_n=1;
  transaction(0,1,0,15,0);if(got!==32'h454e4331)$fatal(1,"ID");
  transaction(1,1,0,15,1);transaction(0,1,0,15,0); // Old sticky must not poison valid response.
  transaction(12,1,0,15,0);if(got!=1)$fatal(1,"sticky address");
  transaction(12,0,1,15,0);transaction(12,1,0,15,0);if(got!=0)$fatal(1,"W1C");
  transaction(0,0,0,15,1);transaction(8,1,0,15,1);
  transaction(16,0,0,3,1);transaction(8,0,1,15,1);
  transaction(8,0,0,15,0);transaction(8,0,3,15,1);
  transaction(12,1,0,15,0);if((got&2)==0)$fatal(1,"core rejection sticky");
  transaction(8,0,5,15,1);transaction(28,1,0,15,1);
  transaction(16,0,1,15,0);transaction(20,0,0,15,1);
  transaction(16,1,0,15,0);if(got!=1)$fatal(1,"failed load changed address");
  transaction(16,0,0,15,0);transaction(20,0,32'h3f800000,15,0);
  transaction(16,1,0,15,0);if(got!=1)$fatal(1,"load did not increment exactly once");
  transaction(36,1,0,15,0);if(got!=1)$fatal(1,"load count");
  transaction(56,1,0,15,0);if(got!=((3<<16)|4))$fatal(1,"geometry");
  transaction(64,1,0,15,0);if(got!=160)$fatal(1,"weight size");
  transaction(72,1,0,15,1);transaction(256,1,0,15,1);
  rst_n=0;repeat(2)@(negedge clk);rst_n=1;
  transaction(12,1,0,15,0);if(got!=0)$fatal(1,"reset sticky");
  transaction(36,1,0,15,0);if(got!=0)$fatal(1,"reset validity");
  $display("ENCODER_ICB_PASS checks=%0d",checks);$finish;
 end
endmodule

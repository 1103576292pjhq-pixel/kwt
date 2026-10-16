`timescale 1ns/1ps
// A new OS simulator process is required for each invocation of this TB.
// No preceding arithmetic, reset interrupt or warm-up operation is allowed.
module tb_fp32_cold;
  reg clk=0;always #5 clk=~clk;
  reg rst_n=0,req_valid=0,rsp_ready=0;
  reg [3:0] req_op=0;
  reg [31:0] req_a=0,req_b=0,req_c=0;
  wire req_ready,rsp_valid,rsp_error,busy;
  wire [31:0] rsp_data;
  wire [4:0] rsp_flags;
  encoder_fp32 dut(.*);
  reg [31:0] expected,saved_data;
  reg [4:0] expected_flags,saved_flags;
  reg expected_error,saved_error;
  integer waited=0,j,count=0;
  reg [1023:0] results_path;
  integer fo;
  initial begin
    if(!$value$plusargs("OP=%h",req_op)) $fatal(1,"NO_OP");
    if(!$value$plusargs("A=%h",req_a)) $fatal(1,"NO_A");
    if(!$value$plusargs("B=%h",req_b)) $fatal(1,"NO_B");
    if(!$value$plusargs("C=%h",req_c)) $fatal(1,"NO_C");
    if(!$value$plusargs("EXPECTED=%h",expected)) $fatal(1,"NO_EXPECTED");
    if(!$value$plusargs("FLAGS=%h",expected_flags)) $fatal(1,"NO_FLAGS");
    if(!$value$plusargs("ERROR=%h",expected_error)) $fatal(1,"NO_ERROR");
    if(!$value$plusargs("RESULTS=%s",results_path)) $fatal(1,"NO_RESULTS");
    fo=$fopen(results_path,"w");if(!fo) $fatal(1,"RESULT_OPEN_FAILED");
    repeat(3) @(posedge clk);
    #1;
    if(rsp_valid || busy || !req_ready) $fatal(1,"COLD_RESET_NOT_IDLE");
    @(negedge clk);rst_n=1;req_valid=1;
    @(posedge clk);#1;
    if(req_ready || !busy) $fatal(1,"COLD_ACCEPT_FAILED");
    @(negedge clk);req_valid=0;
    // Four-state-only negative test: an unknown class must never be coerced
    // to a known zero by casez/casex/default-special shortcuts.
    if($test$plusargs("INJECT_UNKNOWN_CLASS")) force dut.div_rec[31:29]=3'b0x0;
    while(!rsp_valid) begin
      @(posedge clk);#1;waited=waited+1;
      if(waited>80) $fatal(1,"COLD_RESPONSE_TIMEOUT");
      if(!busy || req_ready) $fatal(1,"COLD_BUSY_DROPPED");
    end
    $display("COLD_OBSERVE op=%h a=%h b=%h result=%h flags=%h recoded=%h rec_class=%b raw_sExp=%h raw_sig=%h raw_round=%b",req_op,req_a,req_b,rsp_data,rsp_flags,dut.div_rec,dut.div_rec[31:29],dut.divide_sqrt.divSqrtRecFNToRaw.sExp_Z,dut.divide_sqrt.divSqrtRecFNToRaw.sigX_Z,dut.divide_sqrt.divSqrtRecFNToRaw.roundingMode_Z);
    if($test$plusargs("INJECT_UNKNOWN_CLASS")) begin
      if((^rsp_data)!==1'bx) $fatal(1,"COLD_UNKNOWN_CLASS_MASKED result=%h",rsp_data);
      $display("FP32_COLD_UNKNOWN_PROPAGATED accepted_requests=1");
      $fclose(fo);$finish;
    end
    if(rsp_data!==expected || rsp_flags!==expected_flags || rsp_error!==expected_error)
      $fatal(1,"COLD_MISMATCH op=%h a=%h b=%h c=%h expected=%h/%h/%b got=%h/%h/%b",req_op,req_a,req_b,req_c,expected,expected_flags,expected_error,rsp_data,rsp_flags,rsp_error);
    saved_data=rsp_data;saved_flags=rsp_flags;saved_error=rsp_error;
    repeat(7) begin
      @(negedge clk);req_valid=1;req_a=32'h7fc00000;req_b=32'h3f800000;req_c=32'hffffffff;
      @(posedge clk);#1;
      if(!rsp_valid || !busy || req_ready || rsp_data!==saved_data || rsp_flags!==saved_flags || rsp_error!==saved_error)
        $fatal(1,"COLD_STALLED_RESPONSE_CHANGED");
    end
    @(negedge clk);req_valid=0;rsp_ready=1;
    @(posedge clk);#1;
    if(rsp_valid || busy || !req_ready) $fatal(1,"COLD_RESPONSE_NOT_CONSUMED");
    $fwrite(fo,"%08h %02h %b\n",saved_data,saved_flags,saved_error);$fclose(fo);
    $display("FP32_COLD_PASS accepted_requests=1 wait=%0d stalled_cycles=7",waited);
    $finish;
  end
endmodule

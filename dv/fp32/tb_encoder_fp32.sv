`timescale 1ns/1ps
module tb_encoder_fp32;
  reg clk=0; always #5 clk=~clk;
  reg rst_n=0,req_valid=0,rsp_ready=0;
  reg [3:0] req_op=0;
  reg [31:0] req_a=0,req_b=0,req_c=0;
  wire req_ready,rsp_valid,rsp_error,busy;
  wire [31:0] rsp_data;
  wire [4:0] rsp_flags;
  encoder_fp32 dut(.*);
  integer fd,fo,scanned,count=0,cycles=0,waited,stall,j;
  integer coverage[0:15];
  integer max_latency[0:15];
  reg [3:0] op;
  reg [31:0] a,b,c,expected;
  reg [4:0] fl;
  reg err;
  reg [31:0] saved_data;
  reg [4:0] saved_flags;
  reg saved_error;
  reg [1023:0] vectors_path,results_path;
  always @(posedge clk) begin
    cycles=cycles+1;
    if(cycles>4000000) $fatal(1,"GLOBAL_TIMEOUT");
  end
  task reset_dut;
    begin
      @(negedge clk); rst_n=0; req_valid=0; rsp_ready=0;
      repeat(3) @(posedge clk);
      #1;
      if(rsp_valid || busy || !req_ready) $fatal(1,"RESET_NOT_IDLE");
      @(negedge clk); rst_n=1;
    end
  endtask
  task interrupt_request(input [3:0] reset_op, input integer delay_cycles);
    begin
      @(negedge clk);
      if(!req_ready) $fatal(1,"INTERRUPT_NOT_IDLE");
      req_valid=1; req_op=reset_op; req_a=32'h40400000; req_b=32'h40000000;
      @(posedge clk); #1;
      if(!busy || req_ready) $fatal(1,"REQUEST_NOT_ACCEPTED_BEFORE_RESET");
      @(negedge clk); req_valid=0;
      repeat(delay_cycles) @(posedge clk);
      reset_dut();
      repeat(40) begin
        @(posedge clk); #1;
        if(rsp_valid || busy || !req_ready) $fatal(1,"ABORTED_RESPONSE_LEAKED");
      end
    end
  endtask
  initial begin
    for(j=0;j<16;j=j+1) begin coverage[j]=0;max_latency[j]=0;end
    if(!$value$plusargs("VECTORS=%s",vectors_path)) $fatal(1,"NO_VECTORS");
    if(!$value$plusargs("RESULTS=%s",results_path)) $fatal(1,"NO_RESULTS");
    fd=$fopen(vectors_path,"r"); fo=$fopen(results_path,"w");
    if(fd==0 || fo==0) $fatal(1,"FILE_OPEN_FAILED");
    reset_dut();
    /* Reset before any div/sqrt completion and while a fast response stalls. */
    interrupt_request(4,0); interrupt_request(4,4);
    interrupt_request(5,2); interrupt_request(0,2);
    while(!$feof(fd)) begin
      scanned=$fscanf(fd,"%h %h %h %h %h %h %h\n",op,a,b,c,expected,fl,err);
      if(scanned!=7) $fatal(1,"BAD_VECTOR count=%0d scanned=%0d",count,scanned);
      @(negedge clk);
      if(!req_ready || busy || rsp_valid) $fatal(1,"IDLE_HANDSHAKE count=%0d",count);
      req_op=op;req_a=a;req_b=b;req_c=c;req_valid=1;rsp_ready=0;
      @(posedge clk); #1;
      if(req_ready || !busy) $fatal(1,"SINGLE_OUTSTANDING count=%0d",count);
      @(negedge clk); req_valid=0;req_op=15;req_a=32'h7fc00000;req_b=0;req_c=32'hffffffff;
      waited=0;
      while(!rsp_valid) begin
        @(posedge clk); #1; waited=waited+1;
        if(req_ready || !busy) $fatal(1,"BUSY_DROPPED count=%0d",count);
        if(waited>80) $fatal(1,"RESPONSE_TIMEOUT count=%0d op=%0d",count,op);
      end
      if(rsp_data!==expected || rsp_flags!==fl || rsp_error!==err)
        $fatal(1,"MISMATCH count=%0d op=%0d a=%h b=%h c=%h expected=%h/%h/%b got=%h/%h/%b",count,op,a,b,c,expected,fl,err,rsp_data,rsp_flags,rsp_error);
      saved_data=rsp_data;saved_flags=rsp_flags;saved_error=rsp_error;
      stall=(count*13+7)%8;
      repeat(stall) begin
        @(negedge clk); req_valid=1;req_op=0;req_a=32'h41200000;req_b=32'h3f800000;
        @(posedge clk); #1;
        if(req_ready || !busy || !rsp_valid || rsp_data!==saved_data || rsp_flags!==saved_flags || rsp_error!==saved_error)
          $fatal(1,"STALLED_RESPONSE_CHANGED count=%0d",count);
      end
      @(negedge clk);req_valid=0;rsp_ready=1;
      @(posedge clk); #1;
      if(rsp_valid || busy || !req_ready) $fatal(1,"RESPONSE_NOT_CONSUMED count=%0d",count);
      @(negedge clk);rsp_ready=0;
      $fwrite(fo,"%x %08h %02h %b\n",op,saved_data,saved_flags,saved_error);
      coverage[op]=coverage[op]+1;
      if(waited>max_latency[op]) max_latency[op]=waited;
      count=count+1;
    end
    $fclose(fd);$fclose(fo);
    for(j=0;j<16;j=j+1) begin
      if(coverage[j]==0) $fatal(1,"UNCOVERED_OP %0d",j);
      $display("COVERAGE op=%0d count=%0d maximum_wait=%0d",j,coverage[j],max_latency[j]);
    end
    $display("FP32_PASS transactions=%0d cycles=%0d reset_interruptions=4",count,cycles);
    $finish;
  end
endmodule

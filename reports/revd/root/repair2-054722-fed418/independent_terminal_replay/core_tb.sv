`timescale 1ns/1ps
module core_tb;
  parameter integer M=5, N=32, PM=4, READ_LATENCY=1;
  reg clk=0; always #5 clk=~clk;
  reg rst_n=0, in_valid=0, out_ready=0;
  reg [3:0] in_op=0, in_layer_id=0;
  reg [31:0] in_task_id=0;
  reg [7:0] in_tile_id=0;
  reg [15:0] in_index=0;
  reg signed [47:0] in_data=0;
  reg [5:0] in_shift=0;
  wire in_ready, out_valid, out_overflow, out_saturated, out_last, core_done, fault;
  wire [31:0] out_task_id, out_y_index;
  wire signed [31:0] out_data;
  wire [7:0] error_code;
  core_stream_frontend #(.M(M),.N(N),.PM(PM),.READ_LATENCY(READ_LATENCY)) dut(.*);
  string cmd_path, out_path, stats_path;
  integer cf, of, sf, rc, op, task_no, tile_no, idx, shift_no, layer_no;
  reg [47:0] word_data;
  integer cycles=0, accepted=0, received=0, dones=0, source_done=0;
  integer stall=0, last_stalled=0, retracted=0, gap=0, last_done_received=0;
  integer expect_fault=0, sink_hold=0, force_ready=0;
  reg [31:0] rng=32'hca05e123;
  reg blocked=0;
  reg [98:0] held;
  wire [98:0] payload={out_task_id,out_y_index,out_data,out_overflow,out_saturated,out_last};
  initial begin
    if (!$value$plusargs("CMD=%s",cmd_path) || !$value$plusargs("OUT=%s",out_path) ||
        !$value$plusargs("STATS=%s",stats_path)) $fatal(1,"missing paths");
    cf=$fopen(cmd_path,"r"); of=$fopen(out_path,"w"); sf=$fopen(stats_path,"w");
    if (!cf || !of || !sf) $fatal(1,"open failure");
    repeat(4) @(negedge clk); rst_n=1;
    while (!$feof(cf)) begin
      rc=$fscanf(cf,"%h %h %h %h %h %h %h\n",op,task_no,tile_no,idx,word_data,shift_no,layer_no);
      if(rc!=7) $fatal(1,"bad command %0d",rc);
      if(op==9) begin
        in_valid=0;
        wait(out_valid && out_last);
        @(negedge clk);
        force_ready=1; sink_hold=0; out_ready=1;
        in_op=7; in_task_id=27; in_tile_id=0; in_index=0;
        in_data=0; in_shift=0; in_layer_id=0; in_valid=1;
        @(posedge clk); while(!in_ready) @(posedge clk);
        $display("ROOT_INPUT_ACCEPT_AFTER_OLD_COMPLETION out_valid=%0d done_count=%0d", out_valid, dones);
        if(out_valid || dones!=1) $fatal(1,"input accepted before old task completed");
        @(negedge clk); in_valid=0;
        wait(fault);
        repeat(3) @(negedge clk);
        if(dones!=1 || received!=M*N || out_valid || core_done || in_ready)
          $fatal(1,"old task completion or following invalid-input fault inconsistent");
        $display("ROOT_TERMINAL_REPLAY_PASS outputs=%0d dones=%0d fault=%0d",received,dones,fault);
        $fclose(cf);$fclose(of);$fclose(sf);$finish;
      end else if(op==10) begin
        sink_hold=0;force_ready=1;out_ready=1;
      end else if(op==14) begin
        in_valid=0;
        if(idx==1) wait(dut.state==4 && dut.issue_count>3);
        if(idx==2) wait(dut.state==7);
        if(idx==3) wait(out_valid);
        @(negedge clk);rst_n=0;
        repeat(3) @(negedge clk);rst_n=1;sink_hold=0;
        repeat(2) @(negedge clk);
        if(out_valid||fault||core_done) $fatal(1,"reset residual valid/fault/done");
      end else if(op==13) begin
        in_valid=0;sink_hold=1;wait(out_valid);@(negedge clk);
      end else if(op==12) begin
        in_valid=0;expect_fault=1;wait(fault);@(negedge clk);
        repeat(4) @(negedge clk);
        if(core_done||in_ready) $fatal(1,"fault falsely completed/accepted");
        sink_hold=0;wait(!out_valid);repeat(4) @(negedge clk);
      end else if(op==11) begin
        sink_hold=1;
      end else if(op==15) begin
        in_valid=0;
        wait(core_done || fault); @(negedge clk);
        if(fault) $fatal(1,"unexpected fault %0d",error_code);
      end else begin
        gap=(accepted%13==7)?3:0;
        repeat(gap) @(negedge clk);
        in_op=op[3:0]; in_task_id=task_no; in_tile_id=tile_no[7:0]; in_index=idx[15:0];
        in_data=word_data; in_shift=shift_no[5:0]; in_layer_id=layer_no[3:0]; in_valid=1;
        @(posedge clk); while(!in_ready) @(posedge clk);
        accepted=accepted+1; @(negedge clk); in_valid=0;
      end
    end
    source_done=1;
    repeat(8) @(negedge clk);
    if((!expect_fault&&(dones==0||fault)) || out_valid || (expect_fault&&(!fault||dones!=0))) $fatal(1,"incomplete task");
    $fdisplay(sf,"SUMMARY %0d %0d %0d %0d",cycles,accepted,received,dones);
    $fclose(cf);$fclose(of);$fclose(sf);
    $display("RTL_COMPLETE outputs=%0d tasks=%0d fault=%0d",received,dones,fault);$finish;
  end
  always @(negedge clk) begin
    rng={rng[30:0],rng[31]^rng[21]^rng[1]^rng[0]};
    if(!rst_n) begin out_ready=0;stall=0;last_stalled=0;retracted=0;end
    else if(force_ready) out_ready=1;
    else if(sink_hold) out_ready=0;
    else if(stall>0) begin out_ready=0;stall=stall-1;end
    else if(out_valid && !retracted) begin out_ready=0;stall=7;retracted=1;end
    else if(out_valid && out_last && !last_stalled) begin out_ready=0;stall=11;last_stalled=1;end
    else out_ready=(rng[2:0]!=0);
  end
  always @(posedge clk) begin
    cycles=cycles+1;
    if(cycles>5000000) $fatal(1,"timeout");
    if(!rst_n) blocked=0;
    else begin
      if(blocked && (!out_valid || payload!==held)) $fatal(1,"unstable blocked output");
      blocked=out_valid&&!out_ready;held=payload;
      if(out_valid && out_ready) begin
        if($isunknown(payload)) $fatal(1,"unknown output");
        $fdisplay(of,"%08h %08h %08h %b %b %b",out_task_id,out_y_index,out_data,out_overflow,out_saturated,out_last);
        received=received+1;
      end
      if(core_done) begin
        if(dut.q_valid) $fatal(1,"DONE_WITH_PENDING_INPUT");
        if(out_valid || received-last_done_received!=M*N || fault) $fatal(1,"early done");
        last_done_received=received;
        dones=dones+1;
        $fdisplay(sf,"TASK %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d",dut.task_id,
          dut.load_cycles,dut.compute_cycles,dut.output_cycles,dut.wait_cycles,dut.core_cycles,dut.frontend_cycles,
          dut.issue_count,dut.retire_count,dut.effective_macs,dut.virtual_macs,dut.input_accepts,dut.event_retires);
        for(integer b=0;b<PM;b=b+1) $fdisplay(sf,"X %0d %0d %0d",b,dut.x_reads[b],dut.x_writes[b]);
        for(integer b=0;b<4;b=b+1) $fdisplay(sf,"W %0d %0d %0d",b,dut.w_reads[b],dut.w_writes[b]);
      end
    end
  end
endmodule

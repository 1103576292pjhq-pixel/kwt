`timescale 1ns/1ps
module tiled_w2_core_tb;
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
  `ifdef TILED_W2_RED_REFERENCE
  core_stream_tiled_opt
  `else
  core_stream_tiled_w2_opt
  `endif
 #(.M(M),.N(N),.PM(PM),.READ_LATENCY(READ_LATENCY)) dut(.*);
  string cmd_path, out_path, stats_path;
  integer cf, of, sf, rc, op, task_no, tile_no, idx, shift_no, layer_no;
  reg [47:0] word_data;
  integer cycles=0, accepted=0, received=0, dones=0, source_done=0;
  integer cold_first=-1,cold_start=-1,cold_last=-1;
  integer stall=0, last_stalled=0, retracted=0, gap=0, last_done_received=0;
  integer expect_fault=0, sink_hold=0, force_ready=0;
  integer boundary_ready=-1;
  reg [31:0] rng=32'hca05e123;
  reg blocked=0;
  reg [98:0] held;
  reg pending_held=0;
  reg [117:0] held_command;
  integer deferred_cycles=0;
  integer overlap_writes=0,max_owned=0;
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
        // Test controls only public ports. idx selects a terminal boundary scenario.
        in_valid=0;boundary_ready=1;
        if(idx==0 || idx==3) wait(out_valid && out_last);
        else wait(out_valid && out_y_index==M*N-2);
        @(negedge clk);
        boundary_ready=(idx==2)?0:1;out_ready=(idx==2)?0:1;
        in_op=(idx==3)?0:7;in_task_id=task_no;in_tile_id=0;in_index=0;
        in_data=0;in_shift=shift_no[5:0];in_layer_id=layer_no[3:0];in_valid=1;
        @(posedge clk);
        $fdisplay(sf,"BOUNDARY %0d 0 %b %b %b %b %b %b %b %b",idx,in_ready,in_valid&&in_ready,out_valid,out_last,out_ready,core_done,fault,dut.q_valid);
        if(in_ready) accepted=accepted+1;
        if(idx==1 || idx==2) begin
          if(!in_ready || out_last) $fatal(1,"pending-event setup did not accept before last");
          @(negedge clk);in_valid=0;boundary_ready=(idx==2)?0:1;
          if(idx==2) begin
            // Advance penultimate output, then keep the final output blocked through fault retirement.
            boundary_ready=1;out_ready=1;@(posedge clk);@(negedge clk);boundary_ready=0;out_ready=0;
          end
          expect_fault=1;wait(fault);@(negedge clk);
          if(core_done) $fatal(1,"success before accepted illegal event fault");
          if(idx==2) begin
            if(!out_valid || !out_last) $fatal(1,"last output lost during fault");
            repeat(7) @(negedge clk);
          end
          $fdisplay(sf,"BOUNDARY %0d 1 %b %b %b %b %b %b %b %b",idx,in_ready,in_valid&&in_ready,out_valid,out_last,out_ready,core_done,fault,dut.q_valid);
          boundary_ready=1;out_ready=1;
        end else if(idx==0) begin
          @(negedge clk);in_valid=0;
          wait(core_done || fault);@(negedge clk);
          if(fault) $fatal(1,"unaccepted terminal input faulted completed task");
        end else if(idx==3) begin
          // BEGIN remains stable until its actual handshake after old-task completion.
          while(!in_ready) @(posedge clk);
          $fdisplay(sf,"BOUNDARY %0d 2 %b %b %b %b %b %b %b %b",idx,in_ready,in_valid&&in_ready,out_valid,out_last,out_ready,core_done,fault,dut.q_valid);
          if(core_done || out_valid || fault) $fatal(1,"next BEGIN accepted before completion boundary cleared");
          accepted=accepted+1;@(negedge clk);in_valid=0;
        end else $fatal(1,"unknown boundary mode");
      end else if(op==10) begin
        sink_hold=0;force_ready=1;out_ready=1;
      end else if(op==14) begin
        in_valid=0;
        if(idx==1) wait(dut.state==4 && dut.issue_count>3);
        if(idx==2) wait(dut.state==7);
        if(idx==3) wait(out_valid);
        `ifndef TILED_W2_RED_REFERENCE
        if(idx==4) wait(dut.returned && dut.tag_g[READ_LATENCY-1]==0);
        if(idx==5) wait(dut.product_valid && dut.product_k>1);
         if(idx==6) wait(dut.deferred_open);
         if(idx==7) wait(dut.state==9);
        `endif
        $fdisplay(sf,"RESET %0d %0d",idx,dut.state);
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
    else if(boundary_ready>=0) out_ready=(boundary_ready!=0);
    else if(force_ready) out_ready=1;
    else if(sink_hold) out_ready=0;
    else if(stall>0) begin out_ready=0;stall=stall-1;end
    else if(out_valid && !retracted) begin out_ready=0;stall=7;retracted=1;end
    else if(out_valid && out_last && !last_stalled) begin out_ready=0;stall=11;last_stalled=1;end
    else out_ready=(rng[2:0]!=0);
  end
  always @(posedge clk) begin
    cycles=cycles+1;
    if(cycles>10000000) $fatal(1,"timeout");
    if(!rst_n) begin blocked=0;pending_held=0;last_done_received=received;end
    else begin
      if(fault && !expect_fault) $fatal(1,"unexpected fault code=%0d",error_code);
      if(in_valid && in_ready && in_op==0) begin cold_first=cycles;deferred_cycles=0;overlap_writes=0;max_owned=0;end
      if(dut.w_write&&dut.processing) overlap_writes=overlap_writes+1;
      `ifndef TILED_W2_RED_REFERENCE
      if((32'(dut.slot_state[0]!=0)+32'(dut.slot_state[1]!=0))>max_owned)
        max_owned=32'(dut.slot_state[0]!=0)+32'(dut.slot_state[1]!=0);
      `endif
      if(dut.retire_event && dut.command_ok && dut.q_op==6) cold_start=cycles;
      `ifndef TILED_W2_RED_REFERENCE
      // Passive observations only: no writes to private memories or DUT state.
      if(dut.returned && !fault) begin
        if(dut.w_valid!==4'hf) $fatal(1,"PIPE_W_RETURN_WITHOUT_VALID");
        if(dut.tag_g[READ_LATENCY-1]==0 &&
           (dut.x_valid | ~dut.tag_mask[READ_LATENCY-1])!=={PM{1'b1}})
          $fatal(1,"PIPE_X_RETURN_WITHOUT_VALID");
        if(dut.tag_task[READ_LATENCY-1]!==dut.task_id ||
           dut.tag_row[READ_LATENCY-1]!=dut.row0 || dut.tag_tile[READ_LATENCY-1]!=dut.tile)
          $fatal(1,"PIPE_RESPONSE_OWNER");
      end
      if(dut.product_valid && !fault &&
         (dut.product_task!==dut.task_id || dut.product_row!=dut.row0 || dut.product_tile!=dut.tile))
        $fatal(1,"PIPE_PRODUCT_OWNER");
      if((dut.returned||dut.product_valid||out_valid) && !dut.owner_valid && !fault)
        $fatal(1,"TILE_OWNER_RELEASED_EARLY");
      if((dut.w_rd&dut.w_wr)!==8'h00) $fatal(1,"W2_SINGLE_PORT_COLLISION");
      if(dut.owner_valid && dut.slot_tile[dut.active_slot]!=dut.tile) $fatal(1,"W2_ACTIVE_TILE_OWNER");
      if(dut.tile_open && dut.owner_valid && dut.load_slot==dut.active_slot) $fatal(1,"W2_LOAD_ACTIVE_ALIAS");
      if(dut.returned && dut.tag_slot[READ_LATENCY-1]!==dut.active_slot) $fatal(1,"W2_RESPONSE_SLOT_OWNER");
      if(dut.product_valid && dut.product_slot!==dut.active_slot) $fatal(1,"W2_PRODUCT_SLOT_OWNER");
      if(pending_held && !fault &&
         (!dut.q_valid || {dut.q_op,dut.q_layer,dut.q_task,dut.q_tile,dut.q_index,dut.q_data,dut.q_shift}!==held_command))
        $fatal(1,"TILE_DEFERRED_PAYLOAD_CHANGED");
      pending_held=dut.deferred_open;
      held_command={dut.q_op,dut.q_layer,dut.q_task,dut.q_tile,dut.q_index,dut.q_data,dut.q_shift};
      if(dut.deferred_open) deferred_cycles=deferred_cycles+1;
      `endif
      if(blocked && (!out_valid || payload!==held)) $fatal(1,"unstable blocked output");
      blocked=out_valid&&!out_ready;held=payload;
      if(out_valid && out_ready) begin
        if($isunknown(payload)) $fatal(1,"unknown output");
        $fdisplay(of,"%08h %08h %08h %b %b %b",out_task_id,out_y_index,out_data,out_overflow,out_saturated,out_last);
        received=received+1;
        if(out_last) cold_last=cycles;
      end
      if(dut.state==7 && dut.qe_valid) begin
        `ifdef TILED_W2_RED_REFERENCE
        $fdisplay(sf,"RAW %0d %0d %012h %012h",dut.task_id,(dut.row0+dut.qrow)*N+dut.tile*16+dut.g*4+dut.qcol,dut.acc[dut.g][dut.qrow][dut.qcol],dut.unused_qe_raw);
        `else
        $fdisplay(sf,"RAW %0d %0d %012h %012h",dut.task_id,(dut.row0+dut.qrow)*N+dut.tile*16+dut.g*4+dut.qcol,dut.acc[dut.g][dut.qrow][dut.qcol],dut.unused_qe_raw);
        `endif
      end
      if(core_done) begin
        // Passive observation: every accepted old-task event must have retired before success.
        if(dut.q_valid || dut.input_accepts!=dut.event_retires) $fatal(1,"DONE_WITH_PENDING_INPUT");
        if(out_valid || received-last_done_received!=M*N || fault) $fatal(1,"early done");
        last_done_received=received;
        dones=dones+1;
        if(N>16 && overlap_writes==0) $fatal(1,"W2_NO_LOAD_COMPUTE_OVERLAP");
        $fdisplay(sf,"W2_STATS %0d %0d %0d",dut.task_id,overlap_writes,max_owned);
        `ifndef TILED_W2_RED_REFERENCE
        $fdisplay(sf,"TILE_STATS %0d %0d %0d %0d %0d %0d",dut.task_id,dut.post_start_load_cycles,dut.slot_wait_cycles,dut.owner_acquires,dut.owner_releases,deferred_cycles);
        if(dut.core_cycles!=dut.compute_cycles+dut.output_cycles+dut.post_start_load_cycles+dut.slot_wait_cycles)
          $fatal(1,"tiled core partition mismatch");
        if(dut.owner_acquires!=N/16 || dut.owner_releases!=N/16 || dut.owner_valid)
          $fatal(1,"tile owner lifetime incomplete");
        `endif
        if(cold_first<0 || cold_start<cold_first || cold_last<cold_start)
          $fatal(1,"invalid cold task timestamps");
        $fdisplay(sf,"WINDOW %0d %0d %0d %0d %0d %0d",dut.task_id,cold_first,cold_start,cold_last,
          cold_last-cold_first,cold_last-cold_start);
        $fdisplay(sf,"TASK %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d %0d",dut.task_id,
          dut.load_cycles,dut.compute_cycles,dut.output_cycles,dut.wait_cycles,dut.core_cycles,dut.frontend_cycles,
          dut.issue_count,dut.retire_count,dut.effective_macs,dut.virtual_macs,dut.input_accepts,dut.event_retires);
        for(integer b=0;b<PM;b=b+1) $fdisplay(sf,"X %0d %0d %0d",b,dut.x_reads[b],dut.x_writes[b]);
        `ifdef TILED_W2_RED_REFERENCE
        for(integer b=0;b<4;b=b+1) $fdisplay(sf,"W %0d %0d %0d",b,dut.w_reads[b],dut.w_writes[b]);
        `else
        for(integer b=0;b<8;b=b+1) $fdisplay(sf,"W %0d %0d %0d",b,dut.w_reads[b],dut.w_writes[b]);
        `endif
      end
    end
  end
endmodule

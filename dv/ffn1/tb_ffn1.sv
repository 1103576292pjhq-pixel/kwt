`timescale 1ns/1ps
module tb_ffn1;
  parameter integer M=3, N=4;
  reg clk=0;
  always #5 clk=~clk;
  reg rst_n=0, load_begin=0, load_valid=0, start=0, row_ack=0, row_rd_en=0;
  reg [1:0] load_kind=0;
  reg [31:0] load_addr=0, row_ack_index=0, row_rd_addr=0;
  reg signed [47:0] load_data=0;
  reg [5:0] shift=0;
  wire load_ready, loaded, busy, done, command_error, row_ready, row_rd_valid;
  wire [31:0] row_index;
  wire signed [31:0] row_rd_data;
  wire row_rd_overflow, row_rd_saturated;
  ffn1_top #(.M(M),.N(N)) dut(.*);
  integer cycles=0;
  always @(posedge clk) cycles <= cycles+1;
  integer accepted_pairs=0;
  // Read-only instrumentation of the real DOT64 handshake; never writes DUT state.
  always @(posedge clk) if(rst_n && dut.mac.in_valid && dut.mac.in_ready)
    accepted_pairs <= accepted_pairs+1;
  task tick; begin @(posedge clk); #1; end endtask
  task idle(input integer count); integer i; begin
    for(i=0;i<count;i=i+1) tick();
  end endtask
  task reset_dut; begin
    @(negedge clk); rst_n=0; load_valid=0; start=0; row_ack=0; row_rd_en=0; load_begin=0;
    idle(2); @(negedge clk); rst_n=1; tick();
    if ((busy||done||loaded||row_ready||row_rd_valid) !== 1'b0) $fatal(1,"reset leaked state");
  end endtask
  task begin_load; begin
    @(negedge clk); load_begin=1; tick();
    @(negedge clk); load_begin=0;
    if ((loaded) !== 1'b0) $fatal(1,"load_begin did not invalidate");
  end endtask
  task put(input integer kind,input integer addr,input reg signed [47:0] data); begin
    @(negedge clk); load_valid=1; load_kind=kind[1:0]; load_addr=addr; load_data=data;
    if ((!load_ready) !== 1'b0) $fatal(1,"load not ready");
    tick(); @(negedge clk); load_valid=0;
  end endtask
  task bad_start; begin
    @(negedge clk); start=1; tick();
    if ((!command_error) !== 1'b0) $fatal(1,"illegal start accepted without error");
    @(negedge clk); start=0;
  end endtask
  task launch; begin
    @(negedge clk); start=1; tick();
    if ((!busy||command_error) !== 1'b0) $fatal(1,"valid start rejected");
    @(negedge clk); start=0;
  end endtask
  task ack(input integer row); begin
    @(negedge clk); row_ack=1; row_ack_index=row; tick();
    if ((command_error) !== 1'b0) $fatal(1,"valid ack rejected");
    @(negedge clk); row_ack=0;
  end endtask
  task read_cell(input integer col,output reg signed [31:0] value,output reg ov,output reg sat); begin
    @(negedge clk); row_rd_en=1; row_rd_addr=col;
    tick(); if ((!row_rd_valid) !== 1'b0) $fatal(1,"sync row read missing");
    value=row_rd_data; ov=row_rd_overflow; sat=row_rd_saturated;
    @(negedge clk); row_rd_en=0;
  end endtask
  task wait_row(input integer row); integer timeout; begin
    timeout=0;
    while(!row_ready && timeout<N*80+100) begin tick(); timeout=timeout+1; end
    if ((!row_ready||row_index!=row||!busy||done) !== 1'b0) $fatal(1,"row timeout/order row=%0d cycles=%0d",row,timeout);
  end endtask
  integer i,j,k,r,fd,scan,job,job_count,sh,trace;
  integer load_cycles,calc_cycles,wait_cycles,read_cycles,t0,t1,t2,t3,tmac;
  integer unsigned rng=32'h20261015;
  reg signed [31:0] got;
  reg ov,sat;
  reg [15:0] xmem[0:M*64-1],wmem[0:N*64-1];
  reg [47:0] bmem[0:N-1];
  reg [33:0] expected[0:M*N-1];
  reg [33:0] actual;
  string jobfile,xfile,wfile,bfile,yfile,outfile,case_id;
  task synthetic_load; begin
    begin_load();
    // Only k=0 is nonzero. Exact signed result: (row+1)*(col+2)-col.
    for(i=0;i<M*64;i=i+1) put(0,i,(i%64==0)?(i/64+1):0);
    for(i=0;i<N*64;i=i+1) put(1,i,(i%64==0)?(i/64+2):0);
    for(i=0;i<N;i=i+1) put(2,i,-i);
    if ((!loaded) !== 1'b0) $fatal(1,"complete load not marked");
  end endtask
  initial begin
    if($value$plusargs("trace=%d",trace) && trace!=0) begin
      $dumpfile("protocol.vcd"); $dumpvars(0,tb_ffn1);
    end
    reset_dut();
    if(M==3 && N==4) begin
    bad_start();
    begin_load();
    put(0,1,123); if ((!command_error||loaded) !== 1'b0) $fatal(1,"out of order write accepted");
    put(3,0,123); if ((!command_error) !== 1'b0) $fatal(1,"invalid bank accepted");
    put(0,0,48'sd32768); if ((!command_error) !== 1'b0) $fatal(1,"non-int16 X accepted");
    put(0,0,123); bad_start();
    synthetic_load(); shift=48; bad_start(); shift=0;
    launch(); idle(13); reset_dut(); bad_start();
    synthetic_load(); launch();
    // Busy commands cannot change loaded arrays or interrupt execution.
    @(negedge clk); load_begin=1; tick(); if ((!command_error) !== 1'b0) $fatal(1,"busy load_begin accepted");
    @(negedge clk); load_begin=0;
    put_busy_probe();
    for(r=0;r<M;r=r+1) begin
      wait_row(r);
      @(negedge clk); row_ack=1; row_ack_index=r+1; tick();
      if ((!command_error||!row_ready||row_index!=r) !== 1'b0) $fatal(1,"wrong ack consumed row");
      @(negedge clk); row_ack=0;
      idle(11);
      if ((!row_ready||row_index!=r||!busy) !== 1'b0) $fatal(1,"row wait unstable");
      @(negedge clk); row_rd_en=1; row_rd_addr=N; tick();
      if ((!command_error||row_rd_valid) !== 1'b0) $fatal(1,"out of range row read accepted");
      @(negedge clk); row_rd_en=0;
      for(j=0;j<N;j=j+1) begin
        read_cell(j,got,ov,sat);
        if ((got!=(r+1)*(j+2)-j||ov||sat) !== 1'b0) $fatal(1,"handcalc mismatch row=%0d col=%0d got=%0d",r,j,got);
      end
      read_cell(0,got,ov,sat);
      if ((got!=(r+1)*2) !== 1'b0) $fatal(1,"reread unstable");
      ack(r);
      if ((r==M-1 && (!done||busy||row_ready)) !== 1'b0) $fatal(1,"last ACK did not complete");
    end
    @(negedge clk); row_ack=1; tick(); if ((!command_error) !== 1'b0) $fatal(1,"duplicate ACK accepted");
    @(negedge clk); row_ack=0;
    // Reset while ROW_READY invalidates buffered data and completion.
    synthetic_load(); launch(); wait_row(0); reset_dut(); bad_start();
    // Endpoint shifts and row flag propagation, with independently known answers.
    for(sh=0;sh<=47;sh=sh+47) begin
      begin_load(); shift=sh[5:0];
      for(i=0;i<M*64;i=i+1) put(0,i,32767);
      for(i=0;i<N*64;i=i+1) put(1,i,(i/64)%2==0?32767:-32768);
      for(i=0;i<N;i=i+1) put(2,i,i%2==0?48'sh7fffffffffff:48'sh800000000000);
      launch();
      for(r=0;r<M;r=r+1) begin
        wait_row(r);
        for(j=0;j<N;j=j+1) begin
          read_cell(j,got,ov,sat);
          if ((!ov) !== 1'b0) $fatal(1,"raw overflow not propagated");
          if ((sh==0 && (!sat || got!==(j%2==0?32'sh7fffffff:32'sh80000000))) !== 1'b0) $fatal(1,"sat32 flags/data");
          if ((sh==47 && (sat || got!==(j%2==0?32'sd1:-32'sd1))) !== 1'b0) $fatal(1,"shift47 flags/data");
        end
        ack(r);
      end
    end
    $display("PROTOCOL_PASS M=%0d N=%0d",M,N);
    end
    if(!$value$plusargs("jobs=%s",jobfile)) $finish;
    fd=$fopen(jobfile,"r"); if ((!fd) !== 1'b0) $fatal(1,"jobs absent");
    scan=$fscanf(fd,"%d\n",job_count); if ((scan!=1||job_count<1) !== 1'b0) $fatal(1,"jobs count invalid");
    for(job=0;job<job_count;job=job+1) begin
      scan=$fscanf(fd,"%s %d %s %s %s %s %s\n",case_id,sh,xfile,wfile,bfile,yfile,outfile);
      if ((scan!=7) !== 1'b0) $fatal(1,"job malformed");
      $readmemh(xfile,xmem); $readmemh(wfile,wmem); $readmemh(bfile,bmem); $readmemh(yfile,expected);
      $display("CASE_START %0d %s",job,case_id); $fflush();
      t0=cycles; begin_load(); shift=sh[5:0];
      for(i=0;i<M*64;i=i+1) begin
        rng=rng^(rng<<13); rng=rng^(rng>>17); rng=rng^(rng<<5);
        if((rng&255)==0) idle(1);
        put(0,i,{{32{xmem[i][15]}},xmem[i]});
      end
      for(i=0;i<N*64;i=i+1) put(1,i,{{32{wmem[i][15]}},wmem[i]});
      for(i=0;i<N;i=i+1) put(2,i,bmem[i]);
      if ((!loaded) !== 1'b0) $fatal(1,"full load incomplete");
      load_cycles=cycles-t0; tmac=accepted_pairs; launch(); calc_cycles=0; wait_cycles=0; read_cycles=0;
      trace=$fopen(outfile,"w"); if ((!trace) !== 1'b0) $fatal(1,"cannot create output");
      for(r=0;r<M;r=r+1) begin
        t1=cycles; wait_row(r); t2=cycles; calc_cycles=calc_cycles+t2-t1;
        rng=rng^(rng<<13); rng=rng^(rng>>17); rng=rng^(rng<<5);
        idle(rng%23); t3=cycles; wait_cycles=wait_cycles+t3-t2;
        for(j=0;j<N;j=j+1) begin
          read_cell(j,got,ov,sat); actual={sat,ov,got};
          if ((actual!==expected[r*N+j]) !== 1'b0) $fatal(1,"mismatch %s row=%0d col=%0d got=%h expected=%h",case_id,r,j,actual,expected[r*N+j]);
          $fdisplay(trace,"%09h",actual);
        end
        if ((!row_ready||row_index!=r) !== 1'b0) $fatal(1,"read changed row");
        read_cycles=read_cycles+cycles-t3; ack(r);
        if(r%25==0||r==M-1) begin $display("ROW_DONE %s %0d/%0d",case_id,r+1,M); $fflush(); end
      end
      $fclose(trace);
      if ((!done||busy) !== 1'b0) $fatal(1,"case did not complete");
      if ((accepted_pairs-tmac!=M*N*64) !== 1'b0) $fatal(1,"actual MAC count mismatch");
      $display("CASE_PASS %s outputs=%0d load=%0d compute=%0d wait=%0d read=%0d macs=%0d",case_id,M*N,load_cycles,calc_cycles,wait_cycles,read_cycles,accepted_pairs-tmac); $fflush();
    end
    $fclose(fd); $display("ALL_PASS cases=%0d",job_count); $finish;
  end
  task put_busy_probe; begin
    @(negedge clk); load_valid=1; load_kind=0; load_addr=0; load_data=1000; start=1;
    tick(); if ((!command_error||load_ready) !== 1'b0) $fatal(1,"busy command accepted");
    @(negedge clk); load_valid=0; start=0;
  end endtask
  initial begin #20000000000; $fatal(1,"global timeout"); end
endmodule

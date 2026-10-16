`timescale 1ns/1ps
module tb_icb;
 parameter integer M=3,N=4;
 reg clk=0,rst_n=0;
 always #5 clk=~clk;
 reg icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=0;
 reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;
 reg [3:0] icb_cmd_wmask=15;
 wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
 wire [31:0] icb_rsp_rdata;
 ffn1_icb #(.M(M),.N(N)) dut(.*);
 integer cycles=0,transactions=0,outputs=0,randomize=1;
 integer unsigned rng=32'h20261016;
 reg [31:0] got;
 reg err;
 always @(posedge clk) cycles<=cycles+1;
 task tick; begin @(posedge clk); #1; end endtask
 task idle(input integer count); integer z; begin for(z=0;z<count;z=z+1) tick(); end endtask
 task reset_dut; begin
   @(negedge clk); rst_n=0;icb_cmd_valid=0;icb_rsp_ready=0;idle(3);
   @(negedge clk);rst_n=1;idle(2);
 end endtask
 task bus(input reg rd,input reg [31:0] addr,data,input reg [3:0] mask,
          input reg want_err,output reg [31:0] value);
   integer t,stall,delay; reg [31:0] held;reg held_err;
   begin
     rng=rng*1664525+1013904223;delay=randomize?((rng>>8)%3):0;idle(delay);
     @(negedge clk);icb_cmd_valid=1;icb_cmd_read=rd;icb_cmd_addr=addr;
     icb_cmd_wdata=data;icb_cmd_wmask=mask;icb_rsp_ready=0;
     t=0;while(!icb_cmd_ready && t<30) begin tick();t=t+1;end
     if(!icb_cmd_ready) $fatal(1,"command timeout");
     tick();
     // Leave cmd_valid asserted after its single acceptance on random cases.
     // The wrapper must neither execute it again nor advertise ready early.
     if(randomize&&rng[4])begin idle(2);if(icb_cmd_ready)$fatal(1,"duplicate command acceptance");end
     @(negedge clk);icb_cmd_valid=0;
     t=0;while(!icb_rsp_valid && t<30) begin tick();t=t+1;end
     if(!icb_rsp_valid) $fatal(1,"response timeout address=%h",addr);
     held=icb_rsp_rdata;held_err=icb_rsp_err;
     rng=rng*1664525+1013904223;stall=randomize?((rng>>8)%4):0;
     repeat(stall) begin tick();
       if(!icb_rsp_valid || icb_rsp_rdata!==held || icb_rsp_err!==held_err || icb_cmd_ready)
         $fatal(1,"response unstable under backpressure");
     end
     if(held_err!==want_err) $fatal(1,"rsp_err mismatch addr=%h data=%h got=%b want=%b",addr,data,held_err,want_err);
     value=held;@(negedge clk);icb_rsp_ready=1;tick();
     @(negedge clk);icb_rsp_ready=0;transactions=transactions+1;
   end
 endtask
 task wr(input [31:0] off,data,input reg fail);begin bus(0,32'h11000000+off,data,15,fail,got);end endtask
 task rd(input [31:0] off,input reg fail);begin bus(1,32'h11000000+off,0,15,fail,got);end endtask
 task expect_reg(input[31:0] off,value);begin rd(off,0);if(got!==value)$fatal(1,"reg %h got %h want %h",off,got,value);end endtask
 task put(input integer kind,addr,input [47:0] value);begin
   wr('h14,kind,0);wr('h18,addr,0);wr('h1c,kind==2?value[31:0]:{{16{value[15]}},value[15:0]},0);
   if(kind==2)wr('h20,{16'b0,value[47:32]},0);
   wr('h24,1,0);
 end endtask
 task wait_row(input integer row);integer t;begin
   t=0;rd(4,0);while(!got[2]&&t<N*80+100)begin idle(20);rd(4,0);t=t+20;end
   if(!got[2]||!got[0]||got[3])$fatal(1,"row wait failed");expect_reg('h28,row);
 end endtask
 integer i,j,r,job,job_count,fd,outfd,scan,sh,t0,macs_before,trace;
 reg [15:0] xmem[0:M*64-1],wmem[0:N*64-1];
 reg [47:0] bmem[0:N-1];
 reg [33:0] expected[0:M*N-1],actual;
 string jobs,case_id,xfile,wfile,bfile,yfile,outfile;
 integer macs=0;
 always @(posedge clk) if(rst_n&&dut.core.mac.in_valid&&dut.core.mac.in_ready) macs<=macs+1;
 task run_matrix; begin
   wr(8,1,0);wr('h10,sh,0);
   for(i=0;i<M*64;i=i+1)put(0,i,{{32{xmem[i][15]}},xmem[i]});
   for(i=0;i<N*64;i=i+1)put(1,i,{{32{wmem[i][15]}},wmem[i]});
   for(i=0;i<N;i=i+1)put(2,i,bmem[i]);
   rd(4,0);if(!got[1])$fatal(1,"full load not marked loaded");
   macs_before=macs;t0=cycles;wr(8,2,0);
   // Busy configuration writes must not alter accepted job.
   wr('h10,1,1);wr('h14,1,1);wr('h18,0,1);wr('h1c,1,1);wr('h20,1,1);
   wr(8,2,1);wr(8,1,1);wr('h24,1,1);wr('h2c,0,1);
   for(r=0;r<M;r=r+1)begin
     wait_row(r);expect_reg('h34,0);
     if(r==0)wr('h38,1,1);
     for(j=0;j<N;j=j+1)begin
       wr('h2c,j,0);rd('h30,0);actual[31:0]=got;rd('h34,0);
       if(got[31:3]!==0||!got[2])$fatal(1,"row flags invalid");actual[33:32]=got[1:0];
       if(actual!==expected[r*N+j])$fatal(1,"matrix mismatch r=%0d n=%0d got=%h expected=%h",r,j,actual,expected[r*N+j]);
       if(outfd)$fdisplay(outfd,"%09h",actual);outputs=outputs+1;
     end
     idle(11);expect_reg('h28,r);wr('h38,r,0);expect_reg('h34,0);
     wr('h38,r,1); // consumed ACK cannot be replayed.
   end
   rd(4,0);if(got[0]||!got[3]||got[2])$fatal(1,"final done status invalid");
   if(macs-macs_before!=M*N*64)$fatal(1,"actual MAC count mismatch");
   $display("CASE_PASS %s outputs=%0d cycles=%0d macs=%0d",case_id,M*N,cycles-t0,macs-macs_before);
   $fflush();
 end endtask
 initial begin
   outfd=0;trace=0;if($value$plusargs("trace=%d",trace)&&trace)begin $dumpfile("protocol.vcd");$dumpvars(0,tb_icb);end
   reset_dut();expect_reg(0,32'h4b575431);expect_reg('h3c,(N<<16)|M);expect_reg('h40,64);expect_reg(4,0);
   if($value$plusargs("jobs=%s",jobs))begin
     randomize=0;fd=$fopen(jobs,"r");if(!fd)$fatal(1,"missing jobs");scan=$fscanf(fd,"%d\n",job_count);
     for(job=0;job<job_count;job=job+1)begin
       scan=$fscanf(fd,"%s %d %s %s %s %s %s\n",case_id,sh,xfile,wfile,bfile,yfile,outfile);
       if(scan!=7)$fatal(1,"invalid jobs");$readmemh(xfile,xmem);$readmemh(wfile,wmem);$readmemh(bfile,bmem);$readmemh(yfile,expected);
       outfd=$fopen(outfile,"w");if(!outfd)$fatal(1,"output missing");run_matrix();$fclose(outfd);outfd=0;
     end
     $fclose(fd);$display("ALL_PASS cases=%0d outputs=%0d transactions=%0d",job_count,outputs,transactions);$finish;
   end
   // Access classes and each sticky bit; old sticky must not poison valid rsp.
   bus(1,32'h11000100,0,15,1,got);bus(1,32'h11000001,0,15,1,got);rd('h44,1);
   wr(0,0,1);wr(4,0,1);wr('h28,0,1);wr('h30,0,1);wr('h34,0,1);wr('h3c,0,1);wr('h40,0,1);
   rd(8,1);rd('h24,1);rd('h38,1);bus(0,32'h11000010,0,7,1,got);
   wr(8,3,1);wr('h10,47,0);expect_reg('h10,47);wr('h10,48,1);expect_reg('h10,47);
   wr('h14,3,1);wr('h20,32'h10000,1);wr('h2c,N,1);wr('hc,32'h20,1);
   wr(8,2,1);rd('h30,1);wr('h38,0,1);wr('h24,1,1);
   expect_reg('hc,31);expect_reg(0,32'h4b575431);wr('hc,1,0);expect_reg('hc,30);wr('hc,30,0);expect_reg('hc,0);
   // Complete fresh data still cannot load before load_begin.
   wr('h1c,0,0);wr('h24,1,1);expect_reg('hc,16);wr('hc,31,0);
   // Every commit consumes new halves, even rejected attempts.
   wr(8,1,0);wr('h14,2,0);wr('h1c,0,0);wr('h24,1,1);wr('h20,0,0);wr('h24,1,1);
   wr('h1c,32'hffffffff,0);wr('h20,32'h7fff,0);wr('h18,0,0);wr('h24,1,0);wr('h24,1,1);
   put(2,1,48'h800000000000); // signed48 minimum survives packing exactly.
   wr('h1c,0,0);wr('h20,0,0);bus(0,32'h11000024,1,7,1,got);wr('h24,1,1);
   wr(8,1,0);wr('h14,0,0);wr('h18,0,0);wr('h1c,32'h00008000,0);wr('h24,1,1);
   wr('h24,2,1);wr('h24,1,1); // wrong command cannot leave fresh.
   wr('h18,1,0);wr('h1c,0,0);wr('h24,1,1); // discontinuous load rejected by core.
   wr('h18,0,0);wr('h1c,32'hffff8000,0);wr('h24,1,0); // valid negative int16.
   wr('h1c,0,0);wr('h24,1,1); // consumed word cannot be written twice.
   // Stalled response reset cancels the response and invalidates all load state.
   @(negedge clk);icb_cmd_valid=1;icb_cmd_read=1;icb_cmd_addr=32'h11000000;icb_rsp_ready=0;
   tick();@(negedge clk);icb_cmd_valid=0;idle(4);if(!icb_rsp_valid)$fatal(1,"no pending response");
   reset_dut();if(icb_rsp_valid)$fatal(1,"response survived reset");expect_reg(4,0);expect_reg('hc,0);
   // Synthetic corner case creates overflow and output saturation flags.
   for(i=0;i<M*64;i=i+1)xmem[i]=(i%64==0)?16'hffff:0;
   for(i=0;i<N*64;i=i+1)wmem[i]=(i%64==0)?1:0;
   for(i=0;i<N;i=i+1)begin
     case(i%4)
       0:begin bmem[i]=48'h800000000000;expected[i]=34'h380000000;end
       1:begin bmem[i]=48'h7fffffffffff;expected[i]=34'h27fffffff;end
       2:begin bmem[i]=3;expected[i]=2;end
       3:begin bmem[i]=48'hffffffffffff;expected[i]=34'h0fffffffe;end
     endcase
   end
   for(i=N;i<M*N;i=i+1)expected[i]=expected[i%N];
   sh=0;case_id="synthetic_flags";run_matrix();run_matrix();
   // Reset mid-computation and prove reload required.
   wr(8,1,0);for(i=0;i<M*64;i=i+1)put(0,i,0);for(i=0;i<N*64;i=i+1)put(1,i,0);for(i=0;i<N;i=i+1)put(2,i,0);
   wr(8,2,0);idle(7);reset_dut();expect_reg(4,0);wr(8,2,1);
   $display("PROTOCOL_PASS M=%0d N=%0d outputs=%0d transactions=%0d",M,N,outputs,transactions);$finish;
 end
 initial begin #3000000000;$fatal(1,"global timeout");end
endmodule

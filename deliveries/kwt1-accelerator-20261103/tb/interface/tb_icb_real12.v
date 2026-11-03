// 真实12层回归：沿用tb_icb_system握手/结果检查，独立扩展任务数；不改生产RTL。
`timescale 1ns/1ps
`include "kwt_icb_config.vh"

// CPU总线发起端TB：全部装载与结果事务经过ICB，不直接操作内部存储。
// 单个过程模拟软件：提交命令遇满先服务结果，再重试同一命令。
module tb_icb_real12;
    reg clk=0;always #10 clk=~clk;
    reg rst_n=0,icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=0,external_abort_req=0;
    wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
    reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;
    reg [3:0] icb_cmd_wmask=15;
    wire [31:0] icb_rsp_rdata;
    wire busy,compute_done,task_done,fault,abort_pending,abort_done;
    wire [7:0] error_code;
    kwt_accelerator #(.SRAM_EMA(3'd2),.SRAM_EMAW(2'd0)) dut(.*);
    reg [15:0] xv[0:6335],wv[0:16383];
    reg [31:0] bv[0:255],gold[0:25343];
    reg [4095:0] basepath,filename,tracepath;
    reg [31:0] rng=32'hc42a1031,last_data,cache_data,current_task;
    reg last_error,cache_valid=0,started=0,previous_stall=0;
    reg [31:0] stalled_data;reg stalled_error;
    integer cache_tile=-1,cache_index=-1;
    integer cycles=0,transactions=0,responses=0,errors=0,holds=0;
    integer blocks=0,reads=0,total_blocks=0,total_reads=0,retries=0,tasknum=0;
    integer ti,ix,wi,fd=0,timeout_count,aborted=0;
    reg [31:0] poll,meta,seq,owner,got,stat;
    integer row,coltile,count,pos,global_index;

    always @(posedge clk) begin
        cycles=cycles+1;
        if(cycles>24000000)$fatal(1,"FAIL ICB_SYSTEM timeout blocks=%0d retry=%0d",total_blocks,retries);
        if(rst_n)begin
            if(fault)$fatal(1,"FAIL ICB_SYSTEM fault %h",error_code);
            if(icb_cmd_valid&&icb_cmd_ready)transactions=transactions+1;
            if(icb_rsp_valid&&icb_rsp_ready)begin responses=responses+1;if(icb_rsp_err)errors=errors+1;end
            if(previous_stall && (!icb_rsp_valid||icb_rsp_rdata!==stalled_data||icb_rsp_err!==stalled_error))
                $fatal(1,"FAIL ICB_SYSTEM response did not hold");
            previous_stall=icb_rsp_valid&&!icb_rsp_ready;
            stalled_data=icb_rsp_rdata;stalled_error=icb_rsp_err;
            if(previous_stall)holds=holds+1;
        end
    end
    task random_step;
        begin rng=rng^(rng<<13);rng=rng^(rng>>17);rng=rng^(rng<<5);end
    endtask
    task mmio;
        input integer read0;input [7:0] offset;input [31:0] data0;input integer pause0;
        integer guard;
        begin
            @(negedge clk);icb_cmd_valid=1;icb_cmd_read=read0;
            icb_cmd_addr=`KWT_ICB_DEFAULT_BASE+offset;icb_cmd_wdata=data0;icb_rsp_ready=0;
            guard=0;
            @(posedge clk);while(!icb_cmd_ready)begin @(posedge clk);guard=guard+1;if(guard>1000)$fatal(1,"FAIL ICB_SYSTEM cmd wait offset%h",offset);end
            @(negedge clk);icb_cmd_valid=0;
            guard=0;
            while(!icb_rsp_valid)begin @(negedge clk);guard=guard+1;if(guard>1000)$fatal(1,"FAIL ICB_SYSTEM rsp wait");end
            repeat(pause0)@(negedge clk);
            last_data=icb_rsp_rdata;last_error=icb_rsp_err;
            icb_rsp_ready=1;@(posedge clk);
            @(negedge clk);icb_rsp_ready=0;
        end
    endtask
    task write_reg;input [7:0] off;input [31:0] data0;
        begin mmio(0,off,data0,0);if(last_error)$fatal(1,"FAIL ICB_SYSTEM register write %h",off);end
    endtask
    task read_reg;input [7:0] off;
        begin mmio(1,off,0,0);if(last_error)$fatal(1,"FAIL ICB_SYSTEM register read %h",off);end
    endtask

    task drain_block;
        integer waitcount;
        begin
            waitcount=0;read_reg(`KWT_ICB_STATUS);poll=last_data;
            while(!poll[5])begin
                repeat(3)@(negedge clk);read_reg(`KWT_ICB_STATUS);poll=last_data;
                waitcount=waitcount+1;if(waitcount>2000)$fatal(1,"FAIL ICB_SYSTEM no result during retry");
            end
            read_reg(`KWT_ICB_RESULT_TASK);owner=last_data;
            read_reg(`KWT_ICB_RESULT_META);meta=last_data;
            read_reg(`KWT_ICB_RESULT_SEQ);seq=last_data;
            row=meta[6:0];coltile=meta[11:8];count=meta[22:16];
            if(owner!==current_task||seq!==blocks+1||row!==(blocks%25)*4||coltile!==blocks/25||count!==((blocks%25==24)?48:64))
                $fatal(1,"FAIL ICB_SYSTEM descriptor seq%0d block%0d",seq,blocks);
            // 第一次读取前错误ACK必须不释放owner，后续仍能正常读。
            if(blocks==0)begin
                write_reg(`KWT_ICB_ACK_TASK,current_task);write_reg(`KWT_ICB_ACK_SEQ,seq);write_reg(`KWT_ICB_ACK_COUNT,count);
                mmio(0,`KWT_ICB_ACK,1,3);if(!last_error)$fatal(1,"FAIL ICB_SYSTEM early ACK accepted");
            end
            for(pos=0;pos<count;pos=pos+1)begin
                random_step;
                mmio(1,`KWT_ICB_RESULT_DATA,0,(pos==count-1)?7:(rng[2:0]==0));
                global_index=(row+pos/16)*256+coltile*16+pos%16;
                if(last_error||last_data!==gold[global_index])
                    $fatal(1,"FAIL ICB_SYSTEM Y case%0d index%0d got%h expected%h",tasknum,global_index,last_data,gold[global_index]);
                if(fd)$fdisplay(fd,"R %0d %0d %08h",tasknum,global_index,last_data);
                reads=reads+1;total_reads=total_reads+1;
            end
            read_reg(`KWT_ICB_RESULT_CURSOR);if(last_data!==count)$fatal(1,"FAIL ICB_SYSTEM cursor after read");
            write_reg(`KWT_ICB_ACK_TASK,current_task);write_reg(`KWT_ICB_ACK_SEQ,seq);write_reg(`KWT_ICB_ACK_COUNT,count);
            mmio(0,`KWT_ICB_ACK,1,(blocks==399)?20:2);
            if(last_error)$fatal(1,"FAIL ICB_SYSTEM correct ACK rejected");
            blocks=blocks+1;total_blocks=total_blocks+1;
        end
    endtask
    task send_command;
        input integer op,tile0,index0;input [31:0] data0;
        integer attempts;
        begin
            if(!cache_valid||tile0!=cache_tile)begin write_reg(`KWT_ICB_TILE,tile0);cache_tile=tile0;end
            if(!cache_valid||index0!=cache_index)begin write_reg(`KWT_ICB_INDEX,index0);cache_index=index0;end
            if(!cache_valid||data0!==cache_data)begin write_reg(`KWT_ICB_DATA,data0);cache_data=data0;end
            cache_valid=1;attempts=0;
            mmio(0,`KWT_ICB_COMMAND,op,0);
            while(last_error)begin
                if(!started)$fatal(1,"FAIL ICB_SYSTEM unexpected command rejection before start");
                retries=retries+1;drain_block;attempts=attempts+1;
                if(attempts>401)$fatal(1,"FAIL ICB_SYSTEM no command progress");
                mmio(0,`KWT_ICB_COMMAND,op,0);
            end
        end
    endtask
    initial begin
        if(!$value$plusargs("fixtures=%s",basepath))$fatal(1,"FAIL ICB_SYSTEM no fixture path");
        if($value$plusargs("trace=%s",tracepath))begin
            fd=$fopen(tracepath,"w");
            if(!fd)$fatal(1,"FAIL ICB_REAL12 cannot open trace file");
        end
        repeat(4)@(negedge clk);rst_n=1;
        for(tasknum=0;tasknum<12;tasknum=tasknum+1)begin
            $sformat(filename,"%0s/case%0d-x.hex",basepath,tasknum+1);$readmemh(filename,xv);
            $sformat(filename,"%0s/case%0d-w.hex",basepath,tasknum+1);$readmemh(filename,wv);
            $sformat(filename,"%0s/case%0d-b.hex",basepath,tasknum+1);$readmemh(filename,bv);
            $sformat(filename,"%0s/case%0d-y.hex",basepath,tasknum+1);$readmemh(filename,gold);
            if($test$plusargs("corrupt_first") && tasknum==0)gold[0]=gold[0]^1;
            blocks=0;reads=0;started=0;cache_valid=0;current_task=32'h51200000+tasknum;
            write_reg(`KWT_ICB_TASK,current_task);write_reg(`KWT_ICB_LAYER,tasknum);
            send_command(0,0,0,0);
            for(ix=0;ix<6336;ix=ix+1)send_command(1,0,ix,{{16{xv[ix][15]}},xv[ix]});
            for(ti=0;ti<16;ti=ti+1)begin
                send_command(2,ti,0,0);
                for(ix=0;ix<1024;ix=ix+1)begin wi=(ti*16+ix%16)*64+ix/16;send_command(3,ti,ix,{{16{wv[wi][15]}},wv[wi]});end
                for(ix=0;ix<16;ix=ix+1)send_command(4,ti,ix,bv[ti*16+ix]);
                send_command(5,ti,0,0);
                if(ti==0)begin send_command(6,0,0,0);started=1;end
            end
            while(blocks<400)drain_block;
            wait(task_done);repeat(3)@(negedge clk);
            // CPU必须能从状态寄存器读到完成，不能因这次读请求本身而永远读到0。
            read_reg(`KWT_ICB_STATUS);stat=last_data;
            if(!stat[3]||stat[1]||!stat[2])$fatal(1,"FAIL ICB_SYSTEM completion status unreadable %h",stat);
            if(reads!=25344)$fatal(1,"FAIL ICB_SYSTEM missing results");
            $display("CASE ICB_SYSTEM task=%0d blocks=%0d reads=%0d",tasknum,blocks,reads);
        end
        // 新会话装载中止：CPU写ABORT的响应必须先退休，配置/队列随后清空。
        write_reg(`KWT_ICB_TASK,32'h51200100);cache_valid=0;send_command(0,0,0,0);
        send_command(1,0,0,32'hffff8000);
        mmio(0,`KWT_ICB_ABORT,1,12);if(last_error)$fatal(1,"FAIL ICB_SYSTEM abort rejected");
        timeout_count=0;while(abort_pending)begin @(negedge clk);timeout_count=timeout_count+1;if(timeout_count>50)$fatal(1,"FAIL ICB_SYSTEM abort drain timeout");end
        read_reg(`KWT_ICB_TASK);if(last_data!=0||fault)$fatal(1,"FAIL ICB_SYSTEM abort config");
        aborted=aborted+1;
        if(transactions!=responses||total_blocks!=4800||total_reads!=304128||retries==0||holds==0)$fatal(1,"FAIL ICB_SYSTEM ledger");
        $display("PASS ICB_REAL12_CONTRACT cycles=%0d tasks=12 blocks=%0d outputs=%0d transactions=%0d responses=%0d busy_retries=%0d errors=%0d holds=%0d aborts=%0d",cycles,total_blocks,total_reads,transactions,responses,retries,errors,holds,aborted);
        if(fd)$fclose(fd);$finish;
    end
endmodule

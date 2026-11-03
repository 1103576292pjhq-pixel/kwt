`timescale 1ns/1ps
`include "kwt_icb_config.vh"

// 正常ICB性能基线：不改生产RTL。文件预读/逐项golden检查均在计时窗外。
// 6.667ns是1ps取整的约150MHz功能时钟；报告统一按150MHz折算，不能代替STA。
module tb_icb_perf12;
    reg clk=0;always begin #3.333 clk=1;#3.334 clk=0;end
    reg rst_n=0,icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=0,external_abort_req=0;
    reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;
    reg [3:0] icb_cmd_wmask=15;
    wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
    wire [31:0] icb_rsp_rdata;
    wire busy,compute_done,task_done,fault,abort_pending,abort_done;
    wire [7:0] error_code;
    kwt_accelerator #(.SRAM_EMA(3'd2),.SRAM_EMAW(2'd0)) dut(.*);
    reg [15:0] xv[0:6335],wv[0:16383];
    reg [31:0] bv[0:255],gold[0:25343],actual[0:25343];
    reg [4095:0] basepath,filename,tracepath,metricspath;
    reg [31:0] last_data,current_task,cache_data,poll,owner,meta,seq,stat;
    reg last_error,cache_valid=0,measure_active=0,measure_finished=0;
    reg pending_read=0;reg [7:0] pending_offset=0;
    integer cache_tile=-1,cache_index=-1,operation_class=0;
    integer cycles=0,tasknum=0,task_limit=12,blocks=0,reads=0;
    integer ti,ix,wi,row,tile,count,pos,global_index,fd=0,mfd=0,guard0,unused;
    integer sum_cycles=0,sum_requests=0,sum_responses=0;
    integer start_cycle,first_core_cycle,final_commit_cycle,last_core_cycle,last_read_cycle,last_ack_cycle,complete_cycle;
    integer span_count,load_cycles,status_cycles,output_cycles,ack_cycles,gap_cycles;
    integer core_cycles,groups,core_stalls,core_blocks0,core_outputs0,read_outputs0,ack_blocks0;
    integer requests,responses,error_responses,hold_cycles,cmd_backpressure,ready_polls,result_polls;

    // 只在posedge采样实际握手；总周期分类和重叠的core观察量分开。
    always @(posedge clk)begin
        cycles=cycles+1;
        if(cycles>24000000)$fatal(1,"FAIL PERF watchdog task=%0d blocks=%0d",tasknum,blocks);
        if(rst_n)begin
            if(fault)$fatal(1,"FAIL PERF fault %h",error_code);
            if(measure_active)begin
                span_count=span_count+1;
                case(operation_class)
                    1:load_cycles=load_cycles+1;
                    2:status_cycles=status_cycles+1;
                    3:output_cycles=output_cycles+1;
                    4:ack_cycles=ack_cycles+1;
                    default:gap_cycles=gap_cycles+1;
                endcase
                if(dut.core_busy)core_cycles=core_cycles+1;
                if(dut.operands_valid&&dut.operands_ready)groups=groups+1;
                if(dut.core_out_valid&&!dut.core_out_ready)core_stalls=core_stalls+1;
                if(dut.core_start_valid&&dut.core_start_ready)begin
                    if(first_core_cycle<0)first_core_cycle=cycles;
                    core_blocks0=core_blocks0+1;
                end
                if(dut.core_out_valid&&dut.core_out_ready)core_outputs0=core_outputs0+1;
                if(dut.core_block_done)last_core_cycle=cycles;
                if(dut.load_cmd_valid&&dut.load_cmd_ready&&dut.load_cmd_op==`KWT_CMD_COMMIT&&dut.load_cmd_tile_id==15)
                    final_commit_cycle=cycles;
                if(icb_cmd_valid&&!icb_cmd_ready)cmd_backpressure=cmd_backpressure+1;
                if(icb_rsp_valid&&!icb_rsp_ready)hold_cycles=hold_cycles+1;
            end
            if(icb_cmd_valid&&icb_cmd_ready)begin
                if(!measure_active&&!measure_finished&&icb_cmd_addr==`KWT_ICB_DEFAULT_BASE+`KWT_ICB_TASK&&!icb_cmd_read)begin
                    measure_active=1;start_cycle=cycles;
                end
                if(!measure_active)$fatal(1,"FAIL PERF request outside measurement");
                requests=requests+1;pending_read=icb_cmd_read;pending_offset=icb_cmd_addr[7:0];
            end
            if(icb_rsp_valid&&icb_rsp_ready)begin
                responses=responses+1;
                if(icb_rsp_err)begin error_responses=error_responses+1;$fatal(1,"FAIL PERF ICB error offset=%h",pending_offset);end
                if(pending_read&&pending_offset==`KWT_ICB_RESULT_DATA)begin
                    read_outputs0=read_outputs0+1;
                    if(read_outputs0==25344)last_read_cycle=cycles;
                end
                if(!pending_read&&pending_offset==`KWT_ICB_ACK)begin
                    ack_blocks0=ack_blocks0+1;
                    if(ack_blocks0==400)last_ack_cycle=cycles;
                end
                if(pending_read&&pending_offset==`KWT_ICB_STATUS&&icb_rsp_rdata[3]&&ack_blocks0==400&&read_outputs0==25344)begin
                    complete_cycle=cycles;measure_active=0;measure_finished=1;
                end
            end
        end
    end

    task clear_stats;
        begin
            start_cycle=-1;first_core_cycle=-1;final_commit_cycle=-1;last_core_cycle=-1;
            last_read_cycle=-1;last_ack_cycle=-1;complete_cycle=-1;
            span_count=0;load_cycles=0;status_cycles=0;output_cycles=0;ack_cycles=0;gap_cycles=0;
            core_cycles=0;groups=0;core_stalls=0;core_blocks0=0;core_outputs0=0;read_outputs0=0;ack_blocks0=0;
            requests=0;responses=0;error_responses=0;hold_cycles=0;cmd_backpressure=0;ready_polls=0;result_polls=0;
            measure_active=0;measure_finished=0;operation_class=0;
        end
    endtask
    task mmio;
        input integer read0;input [7:0] off;input [31:0] data0;
        integer guard;
        begin
            @(negedge clk);
            if(off==`KWT_ICB_STATUS||off==`KWT_ICB_ERROR)operation_class=2;
            else if(off>=`KWT_ICB_ACK_TASK)operation_class=4;
            else if(read0&&off>=`KWT_ICB_RESULT_TASK)operation_class=3;
            else operation_class=1;
            icb_cmd_valid=1;icb_cmd_read=read0;icb_cmd_addr=`KWT_ICB_DEFAULT_BASE+off;icb_cmd_wdata=data0;icb_rsp_ready=0;
            guard=0;
            @(posedge clk);while(!icb_cmd_ready)begin @(posedge clk);guard=guard+1;if(guard>1000)$fatal(1,"FAIL PERF cmd timeout");end
            @(negedge clk);icb_cmd_valid=0;guard=0;
            while(!icb_rsp_valid)begin @(negedge clk);guard=guard+1;if(guard>1000)$fatal(1,"FAIL PERF rsp timeout");end
            last_data=icb_rsp_rdata;last_error=icb_rsp_err;
            icb_rsp_ready=1;@(posedge clk);
            @(negedge clk);icb_rsp_ready=0;operation_class=0;
            if(last_error)$fatal(1,"FAIL PERF unexpected response error");
        end
    endtask
    task write_reg;input [7:0] off;input [31:0] data0;begin mmio(0,off,data0);end endtask
    task read_reg;input [7:0] off;begin mmio(1,off,0);end endtask

    task drain_block;
        integer guard;
        begin
            guard=0;read_reg(`KWT_ICB_STATUS);poll=last_data;
            while(!poll[5])begin
                result_polls=result_polls+1;guard=guard+1;
                if(guard>100000)$fatal(1,"FAIL PERF no result");
                read_reg(`KWT_ICB_STATUS);poll=last_data;
            end
            read_reg(`KWT_ICB_RESULT_TASK);owner=last_data;
            read_reg(`KWT_ICB_RESULT_META);meta=last_data;
            read_reg(`KWT_ICB_RESULT_SEQ);seq=last_data;
            row=meta[6:0];tile=meta[11:8];count=meta[22:16];
            if(owner!==current_task||seq!==blocks+1||row!==(blocks%25)*4||tile!==blocks/25||count!==((blocks%25==24)?48:64))
                $fatal(1,"FAIL PERF descriptor");
            read_reg(`KWT_ICB_RESULT_CURSOR);if(last_data!==0)$fatal(1,"FAIL PERF initial cursor");
            for(pos=0;pos<count;pos=pos+1)begin
                mmio(1,`KWT_ICB_RESULT_DATA,0);
                global_index=(row+pos/16)*256+tile*16+pos%16;
                actual[global_index]=last_data;
                $fdisplay(fd,"R %0d %0d %08h",tasknum,global_index,last_data);
                reads=reads+1;
            end
            read_reg(`KWT_ICB_RESULT_CURSOR);if(last_data!==count)$fatal(1,"FAIL PERF final cursor");
            write_reg(`KWT_ICB_ACK_TASK,current_task);write_reg(`KWT_ICB_ACK_SEQ,seq);write_reg(`KWT_ICB_ACK_COUNT,count);
            mmio(0,`KWT_ICB_ACK,1);blocks=blocks+1;
        end
    endtask
    task send_command;
        input integer op,tile0,index0;input [31:0] data0;
        integer guard;reg accepted;
        begin
            if(!cache_valid||tile0!=cache_tile)begin write_reg(`KWT_ICB_TILE,tile0);cache_tile=tile0;end
            if(!cache_valid||index0!=cache_index)begin write_reg(`KWT_ICB_INDEX,index0);cache_index=index0;end
            if(!cache_valid||data0!==cache_data)begin write_reg(`KWT_ICB_DATA,data0);cache_data=data0;end
            cache_valid=1;guard=0;accepted=0;
            while(!accepted)begin
                read_reg(`KWT_ICB_STATUS);poll=last_data;
                if(poll[4]||poll[7])$fatal(1,"FAIL PERF bad status");
                if(poll[5])drain_block;
                else if(poll[0])begin write_reg(`KWT_ICB_COMMAND,op);accepted=1;end
                else ready_polls=ready_polls+1;
                guard=guard+1;if(guard>100000)$fatal(1,"FAIL PERF command readiness timeout");
            end
        end
    endtask

    initial begin
        clear_stats;
        if(!$value$plusargs("fixtures=%s",basepath)||!$value$plusargs("trace=%s",tracepath)||!$value$plusargs("metrics=%s",metricspath))
            $fatal(1,"FAIL PERF paths missing");
        unused=$value$plusargs("task_count=%d",task_limit);
        if(task_limit<1||task_limit>12)$fatal(1,"FAIL PERF invalid task_count");
        fd=$fopen(tracepath,"w");mfd=$fopen(metricspath,"w");if(!fd||!mfd)$fatal(1,"FAIL PERF output open");
        $fdisplay(mfd,"task,start_cycle,first_core_cycle,final_commit_cycle,last_core_cycle,last_read_cycle,last_ack_cycle,complete_cycle,span_cycles,load_bus_cycles,status_bus_cycles,output_bus_cycles,ack_bus_cycles,tb_gap_cycles,core_busy_cycles,operand_groups,core_output_stall_cycles,core_blocks,core_outputs,read_outputs,ack_blocks,mmio_requests,mmio_responses,error_responses,response_hold_cycles,command_backpressure_cycles,ready_wait_polls,result_wait_polls");
        repeat(4)@(negedge clk);rst_n=1;
        for(tasknum=0;tasknum<task_limit;tasknum=tasknum+1)begin
            $sformat(filename,"%0s/case%0d-x.hex",basepath,tasknum+1);$readmemh(filename,xv);
            $sformat(filename,"%0s/case%0d-w.hex",basepath,tasknum+1);$readmemh(filename,wv);
            $sformat(filename,"%0s/case%0d-b.hex",basepath,tasknum+1);$readmemh(filename,bv);
            $sformat(filename,"%0s/case%0d-y.hex",basepath,tasknum+1);$readmemh(filename,gold);
            if($test$plusargs("corrupt_first")&&tasknum==0)gold[0]=gold[0]^1;
            @(negedge clk);clear_stats;blocks=0;reads=0;cache_valid=0;current_task=32'h62000000+tasknum;
            write_reg(`KWT_ICB_TASK,current_task);write_reg(`KWT_ICB_LAYER,tasknum);send_command(0,0,0,0);
            for(ix=0;ix<6336;ix=ix+1)send_command(1,0,ix,{{16{xv[ix][15]}},xv[ix]});
            for(ti=0;ti<16;ti=ti+1)begin
                send_command(2,ti,0,0);
                for(ix=0;ix<1024;ix=ix+1)begin wi=(ti*16+ix%16)*64+ix/16;send_command(3,ti,ix,{{16{wv[wi][15]}},wv[wi]});end
                for(ix=0;ix<16;ix=ix+1)send_command(4,ti,ix,bv[ti*16+ix]);
                send_command(5,ti,0,0);
                if(ti==0)send_command(6,0,0,0);
            end
            while(blocks<400)drain_block;
            guard0=0;
            while(!measure_finished)begin read_reg(`KWT_ICB_STATUS);stat=last_data;guard0=guard0+1;if(guard0>100000)$fatal(1,"FAIL PERF completion timeout");end
            if(!stat[3]||!stat[2]||stat[1]||stat[4]||stat[7])$fatal(1,"FAIL PERF completion state");
            if(span_count!=complete_cycle-start_cycle||span_count!=load_cycles+status_cycles+output_cycles+ack_cycles+gap_cycles)
                $fatal(1,"FAIL PERF cycle accounting");
            if(core_blocks0!=400||groups!=102400||core_outputs0!=25344||read_outputs0!=25344||ack_blocks0!=400||requests!=responses||error_responses!=0||hold_cycles!=0)
                $fatal(1,"FAIL PERF task ledger blocks%0d groups%0d outputs%0d read%0d ack%0d req%0d rsp%0d hold%0d",core_blocks0,groups,core_outputs0,read_outputs0,ack_blocks0,requests,responses,hold_cycles);
            // 已结束测量，比较不增加计时窗口中的CPU/TB计算开销。
            for(ix=0;ix<25344;ix=ix+1)if(actual[ix]!==gold[ix])$fatal(1,"FAIL PERF_GOLDEN task%0d index%0d",tasknum,ix);
            $fdisplay(mfd,"%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d,%0d",tasknum,start_cycle,first_core_cycle,final_commit_cycle,last_core_cycle,last_read_cycle,last_ack_cycle,complete_cycle,span_count,load_cycles,status_cycles,output_cycles,ack_cycles,gap_cycles,core_cycles,groups,core_stalls,core_blocks0,core_outputs0,read_outputs0,ack_blocks0,requests,responses,error_responses,hold_cycles,cmd_backpressure,ready_polls,result_polls);
            $fflush(mfd);$fflush(fd);
            sum_cycles=sum_cycles+span_count;sum_requests=sum_requests+requests;sum_responses=sum_responses+responses;
            $display("PERF_TASK task=%0d cycles=%0d core_busy=%0d requests=%0d errors=%0d",tasknum,span_count,core_cycles,requests,error_responses);
        end
        $display("PASS ICB_PERF12 tasks=%0d window_cycles=%0d outputs=%0d requests=%0d responses=%0d errors=0",task_limit,sum_cycles,task_limit*25344,sum_requests,sum_responses);
        $fclose(fd);$fclose(mfd);$finish;
    end
endmodule

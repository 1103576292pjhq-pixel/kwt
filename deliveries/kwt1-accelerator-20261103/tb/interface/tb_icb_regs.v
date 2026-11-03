`timescale 1ns/1ps
`include "kwt_icb_config.vh"
`default_nettype none

// 仅测试当前自主寄存器接口；命令消费者/结果端点为外部独立mock，不读DUT内部状态。
module tb_icb_regs;
    reg clk=0;always #10 clk=~clk;
    reg rst_n=0,icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=0;
    reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;
    reg [3:0] icb_cmd_wmask=4'hf;
    wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
    wire [31:0] icb_rsp_rdata;
    wire command_valid;
    reg command_ready=1;
    wire [`KWT_ICB_COMMAND_WIDTH-1:0] command_data;
    wire result_req_valid,result_req_ack;
    reg result_req_ready=1;
    wire [31:0] result_req_task_id;
    wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] result_req_sequence;
    wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_req_count;
    reg result_rsp_valid=0,result_rsp_error=0;
    wire result_rsp_ready;
    reg [31:0] result_rsp_data=0;
    reg busy=0,compute_done=0,task_done=0,fault=0;
    reg [7:0] error_code=0;
    reg block_valid=0,block_read_complete=0;
    reg [31:0] block_task_id=0;
    reg [`KWT_RESULT_ROW_WIDTH-1:0] block_row=0;
    reg [`KWT_CMD_TILE_WIDTH-1:0] block_tile=0;
    reg [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] block_count=0;
    reg [`KWT_RESULT_SEQUENCE_WIDTH-1:0] block_sequence=0;
    reg [`KWT_RESULT_COUNT_WIDTH-1:0] block_cursor=0;
    reg abort_pending=0,abort_done=0,external_abort_req=0;
    wire abort_req,transport_empty;
    kwt_icb_regs dut(.*);

    reg [31:0] gold_task=0,gold_data=0,gold_ack_task=0;
    reg [`KWT_LAYER_ID_WIDTH-1:0] gold_layer=0;
    reg [`KWT_CMD_TILE_WIDTH-1:0] gold_tile=0;
    reg [`KWT_CMD_INDEX_WIDTH-1:0] gold_index=0;
    reg [`KWT_RESULT_SEQUENCE_WIDTH-1:0] gold_seq=0;
    reg [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] gold_count=0;
    reg [31:0] rng=32'h91fc247b;
    integer cycles=0,accepted=0,responses=0,commands=0,backend_requests=0,backend_retired=0;
    integer errors=0,holds=0,aborts=0,backpressure_cycles=0;
    integer i,j,off,idx,guard,old_cmd,old_backend,old_abort,old_retired;
    reg expected_command=0,expected_route=0;
    reg backend_pending=0;
    integer backend_delay=0;
    reg [31:0] next_backend_data=32'h00051234;
    reg next_backend_error=0;
    reg [31:0] captured_backend_data;
    reg captured_backend_error;
    reg [31:0] trial_value,expected_read;
    reg trial_error;
    reg [31:0] selected_offset;
    reg [31:0] snapshot_data;
    reg snapshot_error;
    reg snapshot_test=0;

    task random_step;
        begin rng=rng^(rng<<13);rng=rng^(rng>>17);rng=rng^(rng<<5);end
    endtask
    function [31:0] config_value;
        input integer offset;
        begin
            case(offset)
                4:config_value=gold_task;
                8:config_value=gold_layer;
                12:config_value=gold_tile;
                16:config_value=gold_index;
                20:config_value=gold_data;
                52:config_value=gold_ack_task;
                56:config_value=gold_seq;
                60:config_value=gold_count;
                default:config_value=0;
            endcase
        end
    endfunction
    function integer config_offset;
        input integer n;
        begin
            case(n)
                0:config_offset=4;1:config_offset=8;2:config_offset=12;3:config_offset=16;
                4:config_offset=20;5:config_offset=52;6:config_offset=56;default:config_offset=60;
            endcase
        end
    endfunction
    task clear_gold;
        begin gold_task=0;gold_layer=0;gold_tile=0;gold_index=0;gold_data=0;gold_ack_task=0;gold_seq=0;gold_count=0;end
    endtask
    task apply_config;
        input integer offset;
        input [31:0] data;
        begin
            case(offset)
                4:gold_task=data;8:gold_layer=data;12:gold_tile=data;16:gold_index=data;
                20:gold_data=data;52:gold_ack_task=data;56:gold_seq=data;60:gold_count=data;
            endcase
        end
    endtask

    // 后端只根据真正的result请求接受生成一次响应，延时2拍且支持无限背压。
    // 即使external_abort_req/fault变化也保持已接受响应，模拟后端排空合同。
    always @(posedge clk) begin
        if(!rst_n) begin backend_pending<=0;result_rsp_valid<=0;backend_delay<=0;abort_pending<=0;end
        else begin
            if(abort_req||external_abort_req)abort_pending<=1;
            else if(abort_done)abort_pending<=0;
            if(result_req_valid&&result_req_ready)begin
                if(backend_pending||result_rsp_valid)$fatal(1,"two backend transactions");
                backend_pending<=1;backend_delay<=2;
                captured_backend_data<=next_backend_data;
                captured_backend_error<=next_backend_error;
            end
            if(backend_pending&&!result_rsp_valid)begin
                if(backend_delay>0)backend_delay<=backend_delay-1;
                else begin result_rsp_valid<=1;result_rsp_data<=captured_backend_data;result_rsp_error<=captured_backend_error;end
            end
            if(result_rsp_valid&&result_rsp_ready)begin backend_pending<=0;result_rsp_valid<=0;end
        end
    end
    always @(posedge clk)begin
        cycles=cycles+1;
        if(cycles>150000)$fatal(1,"regs timeout");
        if(rst_n)begin
            if(icb_cmd_valid&&icb_cmd_ready)begin accepted=accepted+1;if(transport_empty)$fatal(1,"accept reported transport empty");end
            if(icb_rsp_valid&&icb_rsp_ready)begin responses=responses+1;if(icb_rsp_err)errors=errors+1;end
            if(command_valid)begin
                if(!expected_command||!command_ready)$fatal(1,"unexpected command enqueue");
                if(command_data!=={icb_cmd_wdata[0+:`KWT_CMD_OP_WIDTH],gold_layer,gold_task,gold_tile,gold_index,gold_data})
                    $fatal(1,"command snapshot mismatch");
                commands=commands+1;
            end
            if(result_req_valid)begin
                if(!expected_route)$fatal(1,"unexpected result request");
                if(result_req_ack)begin
                    if(result_req_task_id!==gold_ack_task||result_req_sequence!==gold_seq||result_req_count!==gold_count)
                        $fatal(1,"ACK snapshot mismatch");
                end else if(result_req_task_id!==gold_task)$fatal(1,"read task snapshot mismatch");
                if(result_req_ready)backend_requests=backend_requests+1;
                else backpressure_cycles=backpressure_cycles+1;
            end
            if(result_rsp_valid&&result_rsp_ready)begin
                if(!icb_rsp_valid||!icb_rsp_ready)$fatal(1,"backend retired before ICB response");
                backend_retired=backend_retired+1;
            end
            if(abort_req)aborts=aborts+1;
        end
    end

    // 一次事务：独立给定预期响应、是否产生后端请求；每次故意阻塞响应并探测新请求。
    task access;
        input [31:0] address;
        input rd;
        input [31:0] data;
        input [3:0] mask;
        input err;
        input [31:0] expected;
        input route_expected;
        input integer request_stall;
        integer wait_n,stall_n;
        begin
            old_cmd=commands;old_backend=backend_requests;old_abort=aborts;old_retired=backend_retired;
            expected_route=route_expected;
            expected_command=!err&&!rd&&(address==(`KWT_ICB_DEFAULT_BASE+24));
            @(negedge clk);
            icb_cmd_addr=address;icb_cmd_read=rd;icb_cmd_wdata=data;icb_cmd_wmask=mask;icb_cmd_valid=1;icb_rsp_ready=0;
            if(route_expected&&request_stall>0)result_req_ready=0;
            wait_n=0;
            @(posedge clk);
            while(!icb_cmd_ready)begin
                if(icb_rsp_valid)$fatal(1,"response before command accepted");
                @(negedge clk);wait_n=wait_n+1;
                if(route_expected&&wait_n>=request_stall)result_req_ready=1;
                if(wait_n>100)$fatal(1,"command acceptance timeout address=%h",address);
                @(posedge clk);
            end
            @(negedge clk);icb_cmd_valid=0;
            // 原请求接受后改变总线字段，响应和提交内容应使用接受时快照。
            icb_cmd_addr=32'hdead0000;icb_cmd_wdata=32'hbad0bad0;
            if(snapshot_test)begin busy=0;compute_done=1;error_code=8'hfe;end
            guard=0;
            while(!icb_rsp_valid)begin @(negedge clk);guard=guard+1;if(guard>30)$fatal(1,"response timeout");end
            if(icb_rsp_err!==err||icb_rsp_rdata!==expected)
                $fatal(1,"response mismatch address=%h rd=%b data=%h/%h err=%b/%b",address,rd,icb_rsp_rdata,expected,icb_rsp_err,err);
            snapshot_data=icb_rsp_rdata;snapshot_error=icb_rsp_err;
            // 假装CPU尝试第二条写请求，必须阻塞且无任何副作用。
            icb_cmd_valid=1;icb_cmd_addr=`KWT_ICB_DEFAULT_BASE+4;icb_cmd_read=0;icb_cmd_wdata=32'hcafefeed;
            random_step;stall_n=3+rng[2:0];
            repeat(stall_n)begin
                @(negedge clk);
                if(icb_cmd_ready||command_valid||result_req_valid||!icb_rsp_valid||
                    icb_rsp_rdata!==snapshot_data||icb_rsp_err!==snapshot_error)
                    $fatal(1,"response/new request not held");
                if(route_expected&&result_rsp_ready)$fatal(1,"hidden early backend retire");
                holds=holds+1;
            end
            icb_cmd_valid=0;icb_rsp_ready=1;
            @(posedge clk);
            @(negedge clk);icb_rsp_ready=0;
            if(icb_rsp_valid)$fatal(1,"response repeated after retirement");
            if(route_expected)begin
                if(backend_requests!=old_backend+1||backend_retired!=old_retired+1)$fatal(1,"backend ledger mismatch");
            end else if(backend_requests!=old_backend||backend_retired!=old_retired)$fatal(1,"local access touched backend");
            if(commands!=(old_cmd+(expected_command?1:0)))$fatal(1,"command enqueue count mismatch");
            if(!err&&!rd)begin
                if(address==(`KWT_ICB_DEFAULT_BASE+68))begin
                    if(aborts!=old_abort+1)$fatal(1,"ABORT not a single event");
                    clear_gold;
                end else apply_config(address-`KWT_ICB_DEFAULT_BASE,data);
            end
            expected_command=0;expected_route=0;result_req_ready=1;
        end
    endtask
    task wr;
        input integer offset;input [31:0] data;input err;
        begin access(`KWT_ICB_DEFAULT_BASE+offset,0,data,4'hf,err,0,0,0);end
    endtask
    task rd;
        input integer offset;input [31:0] expected;input err;
        begin access(`KWT_ICB_DEFAULT_BASE+offset,1,0,4'h0,err,expected,0,0);end
    endtask
    task read_configs;
        integer n;
        begin for(n=0;n<8;n=n+1)rd(config_offset(n),config_value(config_offset(n)),0);end
    endtask
    task end_abort;
        begin @(negedge clk);abort_done=1;@(negedge clk);abort_done=0;repeat(2)@(negedge clk);end
    endtask

    initial begin
        repeat(2)@(negedge clk);rst_n=1;
        read_configs;rd(0,1,0);rd(28,0,0);
        wr(4,32'h1234fedc,0);wr(8,15,0);wr(12,15,0);wr(16,8191,0);wr(20,32'h80000000,0);
        wr(52,32'h98761234,0);wr(56,511,0);wr(60,127,0);read_configs;
        // 字段高位、所有非完整写mask、非对齐、高地址别名，均不得改变配置。
        wr(8,16,1);wr(12,16,1);wr(16,8192,1);wr(56,512,1);wr(60,128,1);
        for(i=0;i<15;i=i+1)access(`KWT_ICB_DEFAULT_BASE+4,0,32'hffffffff,i[3:0],1,0,0,0);
        for(i=1;i<4;i=i+1)access(`KWT_ICB_DEFAULT_BASE+4+i,0,32'hffffffff,4'hf,1,0,0,0);
        access(`KWT_ICB_DEFAULT_BASE+32'h100,0,32'hffffffff,4'hf,1,0,0,0);
        access(32'h21000004,0,32'hffffffff,4'hf,1,0,0,0);
        read_configs;
        for(i=0;i<7;i=i+1)wr(24,i,0);
        wr(24,7,1);wr(24,32'h80000000,1);
        command_ready=0;wr(24,1,1);rd(0,0,0);read_configs;
        // 满命令缓冲不应阻止读结果；后端req_ready阻塞5拍，响应阻塞若干拍。
        block_valid=1;block_task_id=32'h6a0197fd;block_row=96;block_tile=15;block_count=48;block_sequence=400;block_cursor=47;
        rd(32,block_task_id,0);rd(36,32'h00300f60,0);rd(40,400,0);rd(44,47,0);
        next_backend_data=32'h0005c123;
        access(`KWT_ICB_DEFAULT_BASE+48,1,0,0,0,next_backend_data,1,5);
        next_backend_error=1;next_backend_data=0;
        access(`KWT_ICB_DEFAULT_BASE+48,1,0,0,1,0,1,1);
        next_backend_error=0;next_backend_data=0;
        access(`KWT_ICB_DEFAULT_BASE+64,0,1,4'hf,0,0,1,2);
        wr(64,0,1);wr(64,2,1);command_ready=1;
        // 状态读响应必须是接受时快照，而不是随输入状态继续变化。
        busy=1;compute_done=0;task_done=0;fault=0;block_valid=0;block_read_complete=0;
        snapshot_test=1;rd(0,3,0);snapshot_test=0;rd(28,8'hfe,0);
        // 只读/未知偏移必须返回错误，未知读数据为0。
        wr(0,1,1);wr(28,1,1);wr(32,1,1);wr(36,1,1);wr(40,1,1);wr(44,1,1);wr(48,1,1);
        rd(24,0,1);rd(64,0,1);rd(68,0,1);
        for(i=72;i<256;i=i+4)begin rd(i,0,1);wr(i,32'hc1a0ffed,1);end
        // 固定种子随机配置合法/高位非法写，每笔随后读回，黄金状态独立维护。
        for(i=0;i<500;i=i+1)begin
            random_step;idx=rng[2:0];off=config_offset(idx);trial_value=rng;trial_error=0;
            if(idx==1||idx==2)begin trial_value=rng&15;if(rng[8])begin trial_value=trial_value|32'h100;trial_error=1;end end
            if(idx==3)begin trial_value=rng&8191;if(rng[8])begin trial_value=trial_value|32'h10000;trial_error=1;end end
            if(idx==6)begin trial_value=rng&511;if(rng[8])begin trial_value=trial_value|32'h10000;trial_error=1;end end
            if(idx==7)begin trial_value=rng&127;if(rng[8])begin trial_value=trial_value|32'h10000;trial_error=1;end end
            wr(off,trial_value,trial_error);rd(off,config_value(off),0);
        end
        // fault期间可读状态/错误，禁止命令、配置和结果，ABORT仍可接受。
        fault=1;error_code=8'h31;busy=0;compute_done=0;
        rd(0,32'h11,0);rd(28,32'h31,0);wr(4,5,1);wr(24,1,1);rd(48,0,1);wr(64,1,1);
        wr(68,0,1);wr(68,1,0);wr(68,1,1);rd(0,32'h91,0);read_configs;
        fault=0;end_abort;rd(0,1,0);
        wr(4,32'h13579bdf,0);
        // 在已接受的结果响应背压中外部中止，不能隐藏退休或清掉原响应。
        next_backend_data=32'h00021234;
        fork
            begin access(`KWT_ICB_DEFAULT_BASE+48,1,0,0,0,next_backend_data,1,0);end
            begin
                wait(result_rsp_valid);@(negedge clk);external_abort_req=1;
                @(negedge clk);external_abort_req=0;clear_gold;
            end
        join
        end_abort;read_configs;
        // 已接受本地读响应同样必须保持中止前快照。
        wr(4,32'h42a0197f,0);
        fork
            begin rd(4,32'h42a0197f,0);end
            begin wait(icb_rsp_valid);@(negedge clk);external_abort_req=1;@(negedge clk);external_abort_req=0;clear_gold;end
        join
        end_abort;read_configs;
        repeat(3)@(negedge clk);
        if(accepted!=responses||backend_requests!=backend_retired||commands!=7||aborts!=1||holds<1000||backpressure_cycles<5||!transport_empty)
            $fatal(1,"regs ledger/coverage short acc=%0d rsp=%0d backend=%0d/%0d cmd=%0d abort=%0d holds=%0d",accepted,responses,backend_requests,backend_retired,commands,aborts,holds);
        $display("PASS ICB_REGS cycles=%0d accepted=%0d responses=%0d commands=%0d result_requests=%0d result_retired=%0d errors=%0d holds=%0d aborts=%0d request_stalls=%0d",cycles,accepted,responses,commands,backend_requests,backend_retired,errors,holds,aborts,backpressure_cycles);
        $finish;
    end
endmodule
`default_nettype wire

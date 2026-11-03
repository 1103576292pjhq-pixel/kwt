`timescale 1ns/1ps
`include "kwt_icb_config.vh"

// 实际结果模块作为后端；ready/响应门控只用于主动制造接口等待，不改DUT内部状态。
// 黄金由TB发送的块序号、外部index和字面数据生成，禁止读内部payload算期望。
module tb_result_access;
    reg clk=0;always #10 clk=~clk;
    reg rst_n=0,req_valid=0,req_ack=0,access_enable=1;
    wire req_ready;
    reg [`KWT_TASK_ID_WIDTH-1:0] req_task_id=0;
    reg [`KWT_RESULT_SEQUENCE_WIDTH-1:0] req_sequence=0;
    reg [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] req_count=0;
    wire block_valid,rsp_valid,rsp_error,idle;
    wire [`KWT_ICB_DATA_WIDTH-1:0] rsp_data;
    reg rsp_ready=0;
    wire result_cmd_valid,result_cmd_ready,result_cmd_ack;
    wire [`KWT_TASK_ID_WIDTH-1:0] result_cmd_task_id;
    wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] result_cmd_sequence;
    wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_cmd_count;
    wire result_rsp_valid,result_rsp_ready,result_rsp_error;
    wire [`KWT_ICB_DATA_WIDTH-1:0] result_rsp_data;
    kwt_result_access dut(.*);

    reg begin_valid=0;wire begin_ready;
    reg [`KWT_TASK_ID_WIDTH-1:0] begin_task_id=0;
    reg alloc_valid=0;wire alloc_ready;
    reg [`KWT_TASK_ID_WIDTH-1:0] alloc_task_id=0;
    reg [`KWT_RESULT_ROW_WIDTH-1:0] alloc_row=0;
    reg [`KWT_CMD_TILE_WIDTH-1:0] alloc_tile=0;
    reg [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] alloc_count=0;
    reg alloc_final=0,fill_valid=0;wire fill_ready;
    reg [`KWT_RESULT_INDEX_WIDTH-1:0] fill_index=0;
    reg signed [`KWT_Y_WIDTH-1:0] fill_y=0;
    reg [`KWT_FLAGS_WIDTH-1:0] fill_flags=0;
    reg fill_block_last=0,publish_valid=0;wire publish_ready;
    reg abort_req=0;wire abort_pending,abort_done,response_empty,compute_done,fault;
    wire [`KWT_ERROR_CODE_WIDTH-1:0] error_code;
    wire [`KWT_RESULT_BLOCK_COUNT-1:0] owned;
    wire block_read_complete;
    wire [`KWT_TASK_ID_WIDTH-1:0] block_task_id;
    wire [`KWT_RESULT_ROW_WIDTH-1:0] block_row;
    wire [`KWT_CMD_TILE_WIDTH-1:0] block_tile;
    wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] block_count;
    wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] block_sequence;
    wire [`KWT_RESULT_COUNT_WIDTH-1:0] block_cursor;
    wire [`KWT_RESULT_PAYLOAD_WIDTH-1:0] peek_data;

    reg backend_allow=1,backend_rsp_allow=1;
    wire actual_cmd_ready,actual_rsp_valid,actual_rsp_error;
    wire [`KWT_ICB_DATA_WIDTH-1:0] actual_rsp_data;
    assign result_cmd_ready=actual_cmd_ready&&backend_allow;
    assign result_rsp_valid=actual_rsp_valid&&backend_rsp_allow;
    assign result_rsp_data=actual_rsp_data;
    assign result_rsp_error=actual_rsp_error;
    kwt_result_blocks results(
        .clk(clk),.rst_n(rst_n),.begin_valid(begin_valid),.begin_ready(begin_ready),.begin_task_id(begin_task_id),
        .alloc_valid(alloc_valid),.alloc_ready(alloc_ready),.alloc_task_id(alloc_task_id),
        .alloc_row(alloc_row),.alloc_tile(alloc_tile),.alloc_count(alloc_count),.alloc_final(alloc_final),
        .fill_valid(fill_valid),.fill_ready(fill_ready),.fill_index(fill_index),.fill_y(fill_y),
        .fill_flags(fill_flags),.fill_block_last(fill_block_last),.publish_valid(publish_valid),.publish_ready(publish_ready),
        .cmd_valid(result_cmd_valid&&backend_allow),.cmd_ready(actual_cmd_ready),.cmd_ack(result_cmd_ack),
        .cmd_task_id(result_cmd_task_id),.cmd_sequence(result_cmd_sequence),.cmd_count(result_cmd_count),
        .rsp_valid(actual_rsp_valid),.rsp_ready(result_rsp_ready&&backend_rsp_allow),.rsp_data(actual_rsp_data),.rsp_error(actual_rsp_error),
        .block_valid(block_valid),.block_read_complete(block_read_complete),.block_task_id(block_task_id),
        .block_row(block_row),.block_tile(block_tile),.block_count(block_count),.block_sequence(block_sequence),
        .block_cursor(block_cursor),.peek_data(peek_data),.abort_req(abort_req),.abort_pending(abort_pending),
        .abort_done(abort_done),.owned(owned),.response_empty(response_empty),.compute_done(compute_done),.fault(fault),.error_code(error_code)
    );

    integer cycles=0,requests=0,backend_requests=0,responses=0,backend_responses=0;
    integer local_errors=0,backend_errors=0,read_checks=0,stalls=0,abort_checks=0,enable_drop_checks=0;
    reg [31:0] rng=32'hf15a8c31;
    reg [`KWT_TASK_ID_WIDTH-1:0] current_task;
    reg [`KWT_RESULT_PAYLOAD_WIDTH-1:0] expected [0:`KWT_RESULT_WORDS-1];
    integer current_count;
    string vcd_path;
    function [31:0] random_word;
        input [31:0] s;reg [31:0] x;
        begin x=s;x=x^(x<<13);x=x^(x>>17);x=x^(x<<5);random_word=x;end
    endfunction
    function [`KWT_Y_WIDTH-1:0] y_value;
        input integer b,i;
        begin
            case(i%5)
                0:y_value=16'h8000;1:y_value=16'h7fff;2:y_value=16'hffff;
                default:y_value=(b*181+i*941)^16'h55ac;
            endcase
        end
    endfunction
    always @(posedge clk)begin
        cycles=cycles+1;if(cycles>30000)$fatal(1,"result access timeout");
        if(rst_n)begin
            if(req_valid&&req_ready)requests=requests+1;
            if(result_cmd_valid&&result_cmd_ready)backend_requests=backend_requests+1;
            if(rsp_valid&&rsp_ready)responses=responses+1;
            if(result_rsp_valid&&result_rsp_ready)backend_responses=backend_responses+1;
            if(fault)$fatal(1,"result producer fault %h",error_code);
        end
    end
    task tick;begin @(posedge clk);#1;end endtask
    task fresh;
        begin
            @(negedge clk);rst_n=0;req_valid=0;rsp_ready=0;access_enable=1;
            backend_allow=1;backend_rsp_allow=1;abort_req=0;
            begin_valid=0;alloc_valid=0;fill_valid=0;publish_valid=0;
            repeat(3)tick;@(negedge clk);rst_n=1;tick;
            if(!idle||rsp_valid||result_cmd_valid||!begin_ready)$fatal(1,"hard reset isolation");
        end
    endtask
    task new_session;
        input [`KWT_TASK_ID_WIDTH-1:0] identity;
        begin
            @(negedge clk);begin_valid=1;begin_task_id=identity;
            @(posedge clk);if(!begin_ready)$fatal(1,"session not ready");#1;
            @(negedge clk);begin_valid=0;current_task=identity;
        end
    endtask
    task produce;
        input integer b;input tail,final_flag;
        integer g,p,q,i,n;
        reg [`KWT_FLAGS_WIDTH-1:0] flags;
        begin
            current_count=tail?48:64;
            @(negedge clk);alloc_valid=1;alloc_task_id=current_task;
            alloc_row=tail?96:0;alloc_tile=final_flag?15:0;alloc_count=current_count;alloc_final=final_flag;
            @(posedge clk);if(!alloc_ready)$fatal(1,"allocation blocked");#1;
            @(negedge clk);alloc_valid=0;n=0;
            for(g=0;g<4;g=g+1)for(p=0;p<(tail?3:4);p=p+1)for(q=0;q<4;q=q+1)begin
                i=p*16+g*4+q;flags={final_flag&&(n==current_count-1),((i+b)%3==0),((i+b)%7==0)};
                expected[i]={flags,y_value(b,i)};
                @(negedge clk);fill_valid=1;fill_index=i;fill_y=y_value(b,i);fill_flags=flags;fill_block_last=(n==current_count-1);
                @(posedge clk);if(!fill_ready)$fatal(1,"fill blocked");#1;
                @(negedge clk);fill_valid=0;n=n+1;
            end
            @(negedge clk);publish_valid=1;
            @(posedge clk);if(!publish_ready)$fatal(1,"publish blocked");#1;
            @(negedge clk);publish_valid=0;
            if(!block_valid||block_cursor!=0||block_count!=current_count)$fatal(1,"publish descriptor");
        end
    endtask

    task transaction;
        input ack_flag;
        input [`KWT_TASK_ID_WIDTH-1:0] identity;
        input [`KWT_RESULT_SEQUENCE_WIDTH-1:0] sequence_value;
        input [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] count_value;
        input expected_error;
        input [`KWT_ICB_DATA_WIDTH-1:0] expected_data;
        input integer request_stall,response_delay,response_stall;
        input drop_enable;
        integer i,guard,old_backend;
        reg old_valid,expect_local;
        reg [`KWT_RESULT_COUNT_WIDTH-1:0] old_cursor;
        begin
            @(negedge clk);req_valid=1;req_ack=ack_flag;req_task_id=identity;
            req_sequence=sequence_value;req_count=count_value;rsp_ready=0;
            backend_allow=(request_stall==0);backend_rsp_allow=(response_delay==0);
            old_cursor=block_cursor;old_valid=block_valid;expect_local=!access_enable||!block_valid;
            old_backend=backend_requests;
            if(!expect_local)begin
                for(i=0;i<request_stall;i=i+1)begin
                    tick;stalls=stalls+1;
                    if(req_ready||!idle||!result_cmd_valid||result_cmd_ack!==ack_flag||
                       result_cmd_task_id!==identity||result_cmd_sequence!==sequence_value||result_cmd_count!==count_value)
                        $fatal(1,"backend request wait lost fields or accepted early");
                end
                if(request_stall>0)begin @(negedge clk);backend_allow=1;end
            end
            @(posedge clk);if(!req_ready)$fatal(1,"request not accepted");#1;
            if(idle||req_ready)$fatal(1,"transaction not held busy");
            if(expect_local&&backend_requests!=old_backend)$fatal(1,"local error reached backend");
            if(!expect_local&&backend_requests!=old_backend+1)$fatal(1,"legal request not same-edge backend handshake");
            @(negedge clk);
            // 提供一条不同的下一请求，但当前响应未结束时绝不能接受。
            req_valid=1;req_ack=!ack_flag;req_task_id=~identity;req_sequence=~sequence_value;req_count=~count_value;
            if(drop_enable)begin access_enable=0;enable_drop_checks=enable_drop_checks+1;end
            if(!expect_local)for(i=0;i<response_delay;i=i+1)begin
                tick;stalls=stalls+1;
                if(rsp_valid||idle||req_ready||result_rsp_ready)$fatal(1,"waiting backend response mishandled");
                if(!ack_flag&&block_cursor!==old_cursor)$fatal(1,"cursor moved before delayed response");
            end
            @(negedge clk);backend_rsp_allow=1;
            #1;
            if(!rsp_valid||rsp_error!==expected_error||rsp_data!==expected_data)$fatal(1,"response mismatch ack=%b err=%b/%b data=%h/%h",ack_flag,rsp_error,expected_error,rsp_data,expected_data);
            for(i=0;i<response_stall;i=i+1)begin
                tick;stalls=stalls+1;
                if(!rsp_valid||rsp_error!==expected_error||rsp_data!==expected_data||idle||req_ready||result_cmd_valid)
                    $fatal(1,"response stall not stable");
                if(result_rsp_ready)$fatal(1,"backend retired before upstream response");
                if(!ack_flag&&old_valid&&block_cursor!==old_cursor)$fatal(1,"cursor advanced before upstream retirement");
            end
            @(negedge clk);rsp_ready=1;
            #1;
            if(!expect_local&&!result_rsp_ready)$fatal(1,"backend response ready not directly propagated");
            if(req_ready)$fatal(1,"same-cycle retire and next accept incorrectly allowed");
            tick;
            if(!idle||rsp_valid)$fatal(1,"transaction did not retire");
            if(!ack_flag&&!expected_error&&block_cursor!==(old_cursor+1'b1))$fatal(1,"cursor retirement wrong");
            if(expect_local)local_errors=local_errors+1;
            else if(expected_error)backend_errors=backend_errors+1;
            else if(!ack_flag)read_checks=read_checks+1;
            @(negedge clk);req_valid=0;rsp_ready=0;access_enable=1;backend_allow=1;backend_rsp_allow=1;
        end
    endtask

    task abort_stalled_read;
        integer i;
        reg [`KWT_ICB_DATA_WIDTH-1:0] snapshot;
        begin
            snapshot={{(`KWT_ICB_DATA_WIDTH-`KWT_RESULT_PAYLOAD_WIDTH){1'b0}},expected[block_cursor]};
            @(negedge clk);req_valid=1;req_ack=0;req_task_id=current_task;req_sequence=0;req_count=0;rsp_ready=0;
            @(posedge clk);if(!req_ready)$fatal(1,"abort read request blocked");#1;
            @(negedge clk);req_valid=0;abort_req=1;access_enable=0;
            tick;@(negedge clk);abort_req=0;
            for(i=0;i<8;i=i+1)begin
                tick;
                if(!abort_pending||!rsp_valid||rsp_data!==snapshot||rsp_error||result_rsp_ready||idle)
                    $fatal(1,"enable drop/ABORT swallowed accepted response");
            end
            @(negedge clk);rsp_ready=1;tick;
            if(!idle||rsp_valid||abort_done)$fatal(1,"abort response boundary wrong");
            tick;if(!abort_done||owned!==0||!begin_ready)$fatal(1,"abort did not drain response");
            @(negedge clk);rsp_ready=0;access_enable=1;
            abort_checks=abort_checks+1;
        end
    endtask

    integer i;
    initial begin
        if($value$plusargs("vcd=%s",vcd_path))begin $dumpfile(vcd_path);$dumpvars(0,tb_result_access);end
        fresh;
        access_enable=0;
        transaction(0,0,0,0,1,0,4,0,5,0);
        transaction(1,0,0,0,1,0,4,0,4,0);
        access_enable=1;
        transaction(0,0,0,0,1,0,0,0,3,0);
        transaction(1,0,0,0,1,0,0,0,2,0);
        new_session(32'h5030a012);produce(0,0,0);
        transaction(1,current_task,1,64,1,0,5,3,4,1); // 未读完ACK由实际后端拒绝
        transaction(0,current_task^1,0,0,1,0,3,2,3,0); // 身份错误由后端拒绝
        for(i=0;i<64;i=i+1)begin
            rng=random_word(rng);
            if(i%8==0)begin
                access_enable=0;
                transaction(i[0],current_task,1,64,1,0,0,0,2,0);
            end
            transaction(0,current_task,0,0,0,{{(`KWT_ICB_DATA_WIDTH-`KWT_RESULT_PAYLOAD_WIDTH){1'b0}},expected[i]},rng[1:0],rng[3:2],rng[5:4],(i%9==0));
        end
        if(!block_read_complete)$fatal(1,"complete cursor not reached");
        transaction(1,current_task,2,64,1,0,1,2,3,0);
        transaction(1,current_task,1,63,1,0,2,1,2,0);
        transaction(1,current_task^1,1,64,1,0,1,1,1,0);
        // ACK接受后block_valid下降，但成功响应必须独立保留直到上游接收。
        transaction(1,current_task,1,64,0,0,4,3,7,1);
        transaction(0,current_task,0,0,1,0,0,0,4,0);
        produce(1,1,0);
        for(i=0;i<8;i=i+1)transaction(0,current_task,0,0,0,{{(`KWT_ICB_DATA_WIDTH-`KWT_RESULT_PAYLOAD_WIDTH){1'b0}},expected[i]},1,1,2,0);
        abort_stalled_read;
        new_session(32'h5030a013);produce(2,1,1);
        for(i=0;i<48;i=i+1)transaction(0,current_task,0,0,0,{{(`KWT_ICB_DATA_WIDTH-`KWT_RESULT_PAYLOAD_WIDTH){1'b0}},expected[i]},0,0,i%4,0);
        transaction(1,current_task,1,48,0,0,1,1,5,1);
        if(!compute_done||!begin_ready)$fatal(1,"final response/session boundary");
        new_session(32'h5030a014);
        if(compute_done)$fatal(1,"new session inherited completion");
        if(requests!=responses||backend_requests!=backend_responses)$fatal(1,"transaction ledger mismatch req=%0d rsp=%0d backend=%0d/%0d",requests,responses,backend_requests,backend_responses);
        if(read_checks!=120||abort_checks!=1||backend_errors!=5)$fatal(1,"coverage tally wrong");
        $display("PASS RESULT_ACCESS cycles=%0d requests=%0d responses=%0d backend_requests=%0d backend_responses=%0d local_errors=%0d backend_errors=%0d reads=%0d stalls=%0d aborts=%0d enable_drops=%0d",cycles,requests,responses,backend_requests,backend_responses,local_errors,backend_errors,read_checks,stalls,abort_checks,enable_drop_checks);
        $finish;
    end
endmodule

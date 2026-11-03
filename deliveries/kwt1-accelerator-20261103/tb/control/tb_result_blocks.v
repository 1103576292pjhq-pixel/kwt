`timescale 1ns/1ps
`include "kwt_control_config.vh"

// 双结果块独立自检：黄金仅由外部发送的块身份、index和字面向量生成。
// 不读取DUT内部payload、指针、mask或计数器。固定种子使暂停可重放。
module tb_result_blocks;
    reg clk=0;
    always #10 clk=~clk;
    reg rst_n=0;
    reg begin_valid=0; wire begin_ready; reg [31:0] begin_task_id=0;
    reg alloc_valid=0; wire alloc_ready;
    reg [31:0] alloc_task_id=0;
    reg [`KWT_RESULT_ROW_WIDTH-1:0] alloc_row=0;
    reg [`KWT_CMD_TILE_WIDTH-1:0] alloc_tile=0;
    reg [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] alloc_count=0;
    reg alloc_final=0;
    reg fill_valid=0; wire fill_ready;
    reg [5:0] fill_index=0; reg signed [15:0] fill_y=0;
    reg [2:0] fill_flags=0; reg fill_block_last=0;
    reg publish_valid=0; wire publish_ready;
    reg cmd_valid=0; wire cmd_ready; reg cmd_ack=0;
    reg [31:0] cmd_task_id=0;
    reg [`KWT_RESULT_SEQUENCE_WIDTH-1:0] cmd_sequence=0;
    reg [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] cmd_count=0;
    wire rsp_valid; reg rsp_ready=0; wire [31:0] rsp_data; wire rsp_error;
    wire block_valid,block_read_complete;
    wire [31:0] block_task_id;
    wire [`KWT_RESULT_ROW_WIDTH-1:0] block_row;
    wire [`KWT_CMD_TILE_WIDTH-1:0] block_tile;
    wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] block_count;
    wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] block_sequence;
    wire [6:0] block_cursor; wire [18:0] peek_data;
    reg abort_req=0; wire abort_pending,abort_done; wire [1:0] owned;
    wire response_empty,compute_done,fault; wire [7:0] error_code;

    // 小上限用于真实运行64次publish后检查序号耗尽，不能强改内部寄存器。
    kwt_result_blocks #(.SEQUENCE_MAX(9'd64)) dut(.*);
    integer cycles=0,allocations=0,fills=0,publishes=0,reads=0,acks=0;
    integer errors=0,aborts=0,fault_cases=0,stalls=0,blocks_checked=0,concurrent_fill_read=0;
    reg [31:0] rng=32'h8af031cd;
    integer seed_dummy;
    reg [31:0] current_task;
    reg [18:0] expected [0:16383];
    integer counts[0:255],rows[0:255],tiles[0:255],seqs[0:255];
    reg finals[0:255];
    string vcd_path;
    function [31:0] random_word;
        input [31:0] value;
        reg [31:0] r;
        begin r=value; r=r^(r<<13); r=r^(r>>17); r=r^(r<<5); random_word=r; end
    endfunction
    function [15:0] y_value;
        input integer b,i;
        begin
            case(i%8)
                0:y_value=16'h8000; 1:y_value=16'h7fff;
                2:y_value=16'hffff; 3:y_value=16'h0000;
                default:y_value=(b*1009+i*173)^16'hb631;
            endcase
        end
    endfunction
    function [2:0] flag_value;
        input integer b,i; input final_flag,last_flag;
        begin flag_value={final_flag&&last_flag,((b+i)%3==0),((b+i)%5==0)}; end
    endfunction

    always @(posedge clk) begin
        cycles=cycles+1;
        if (cycles>200000) $fatal(1,"result timeout");
        if(rst_n) begin
            if(alloc_valid&&alloc_ready) allocations=allocations+1;
            if(fill_valid&&fill_ready) fills=fills+1;
            if(publish_valid&&publish_ready) publishes=publishes+1;
            if(fill_valid&&fill_ready&&cmd_valid&&cmd_ready&&!cmd_ack)
                concurrent_fill_read=concurrent_fill_read+1;
            if(rsp_valid&&rsp_ready) begin
                if(rsp_error) errors=errors+1;
                else if(cmd_ack) acks=acks+1;
                else reads=reads+1;
            end
        end
    end

    task tick;
        begin @(posedge clk); #1; end
    endtask
    task fresh;
        begin
            @(negedge clk); rst_n=0;
            begin_valid=0; alloc_valid=0; fill_valid=0; publish_valid=0;
            cmd_valid=0; rsp_ready=0; abort_req=0;
            repeat(3) tick;
            @(negedge clk); rst_n=1;
            tick;
            if(owned!==0||rsp_valid||fault||compute_done||!begin_ready)
                $fatal(1,"reset state isolation");
        end
    endtask
    task new_session;
        input [31:0] identity;
        integer guard;
        begin
            @(negedge clk); begin_valid=1; begin_task_id=identity;
            guard=0;
            @(posedge clk);
            while(!begin_ready) begin guard=guard+1; if(guard>20)$fatal(1,"BEGIN stalled"); @(posedge clk); end
            #1;
            @(negedge clk); begin_valid=0; current_task=identity;
            if(fault||compute_done||owned!==0) $fatal(1,"BEGIN identity reset");
        end
    endtask
    task allocate;
        input integer b,r,t,sequence_number;
        input final_flag;
        integer guard;
        begin
            counts[b]=(r==96)?48:64; rows[b]=r; tiles[b]=t;
            seqs[b]=sequence_number; finals[b]=final_flag;
            @(negedge clk); alloc_valid=1; alloc_task_id=current_task;
            alloc_row=r; alloc_tile=t; alloc_count=counts[b]; alloc_final=final_flag;
            guard=0; @(posedge clk);
            while(!alloc_ready) begin guard=guard+1; if(guard>5000)$fatal(1,"ALLOC stalled"); @(posedge clk); end
            #1; if(fault)$fatal(1,"legal ALLOC rejected %h",error_code);
            @(negedge clk); alloc_valid=0;
        end
    endtask
    task one_fill;
        input integer idx;
        input [15:0] value;
        input [2:0] flags;
        input last_flag;
        begin
            @(negedge clk); fill_valid=1; fill_index=idx; fill_y=value;
            fill_flags=flags; fill_block_last=last_flag;
            @(posedge clk); if(!fill_ready)$fatal(1,"unexpected fill backpressure"); #1;
            @(negedge clk); fill_valid=0;
        end
    endtask
    task fill_block;
        input integer b;
        integer g,p,q,idx,n;
        reg last_flag;
        begin
            n=0;
            for(g=0;g<4;g=g+1)for(p=0;p<(counts[b]/16);p=p+1)for(q=0;q<4;q=q+1)begin
                idx=p*16+g*4+q; last_flag=(n==counts[b]-1);
                expected[b*64+idx]={flag_value(b,idx,finals[b],last_flag),y_value(b,idx)};
                rng=random_word(rng);
                if(rng[2:0]==0) repeat(2) tick;
                one_fill(idx,y_value(b,idx),flag_value(b,idx,finals[b],last_flag),last_flag);
                if(fault)$fatal(1,"valid fill fault b=%0d idx=%0d code=%h",b,idx,error_code);
                n=n+1;
            end
            if(block_valid&&owned==1&&blocks_checked==0)
                $fatal(1,"FILL became visible before publish");
        end
    endtask
    task publish;
        begin
            @(negedge clk); publish_valid=1;
            @(posedge clk); if(!publish_ready)$fatal(1,"unexpected publish stall"); #1;
            @(negedge clk); publish_valid=0;
        end
    endtask
    task make_block;
        input integer b,r,t,s;
        input final_flag;
        begin allocate(b,r,t,s,final_flag); fill_block(b); publish; if(fault)$fatal(1,"legal publish rejected"); end
    endtask

    // 一笔CPU事务；命令接受后扰动命令字段，确保响应来自快照。
    task cpu_transaction;
        input ack_flag;
        input [31:0] task_value;
        input [`KWT_RESULT_SEQUENCE_WIDTH-1:0] seq_value;
        input [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] count_value;
        input expect_error;
        input [31:0] expect_data;
        input integer pause_cycles;
        integer guard,j;
        reg [6:0] previous_cursor;
        reg [1:0] previous_owned;
        begin
            @(negedge clk); cmd_valid=1; cmd_ack=ack_flag;
            cmd_task_id=task_value; cmd_sequence=seq_value; cmd_count=count_value; rsp_ready=0;
            guard=0; previous_cursor=block_cursor; previous_owned=owned;
            @(posedge clk);
            while(!cmd_ready) begin guard=guard+1; if(guard>50)$fatal(1,"CPU cmd stalled"); @(posedge clk); end
            #1;
            if(!rsp_valid||rsp_error!==expect_error||rsp_data!==expect_data)
                $fatal(1,"response snapshot ack=%b err=%b/%b data=%h/%h",ack_flag,rsp_error,expect_error,rsp_data,expect_data);
            if(ack_flag&&!expect_error&&owned===previous_owned)$fatal(1,"ACK did not release at accept");
            if((!ack_flag||expect_error)&&block_cursor!==previous_cursor)$fatal(1,"cursor advanced on command accept");
            @(negedge clk); cmd_valid=0; cmd_task_id=~task_value; cmd_sequence=~seq_value; cmd_count=~count_value;
            for(j=0;j<pause_cycles;j=j+1) begin
                tick; stalls=stalls+1;
                if(!rsp_valid||rsp_error!==expect_error||rsp_data!==expect_data||response_empty)
                    $fatal(1,"response changed under stall");
                if((!ack_flag||expect_error)&&block_cursor!==previous_cursor)$fatal(1,"cursor advanced under stall");
                if(cmd_ready)$fatal(1,"accepted second request with response pending");
                if(begin_ready)$fatal(1,"BEGIN allowed with response pending");
            end
            @(negedge clk); rsp_ready=1;
            tick;
            if(rsp_valid)$fatal(1,"response did not retire");
            if(!ack_flag&&!expect_error&&block_cursor!==(previous_cursor+1'b1))$fatal(1,"successful read did not advance exactly once");
            if(expect_error&&block_cursor!==previous_cursor)$fatal(1,"error changed cursor");
            if(fault)$fatal(1,"CPU error set production fault");
            @(negedge clk); rsp_ready=0;
            // 保留ack位到响应退休，监测器据此统计本次事务类别。
        end
    endtask
    task check_descriptor;
        input integer b;
        begin
            if(!block_valid||block_task_id!==current_task||block_row!==rows[b]||
               block_tile!==tiles[b]||block_count!==counts[b]||block_sequence!==seqs[b]||block_cursor!==0)
                $fatal(1,"descriptor/order b=%0d task=%h row=%0d tile=%0d count=%0d seq=%0d cursor=%0d",b,block_task_id,block_row,block_tile,block_count,block_sequence,block_cursor);
        end
    endtask
    task consume;
        input integer b;
        input inject_errors;
        integer i,pause_count;
        begin
            check_descriptor(b);
            if(inject_errors)begin
                cpu_transaction(0,current_task^32'h80000000,0,0,1,0,3);
                cpu_transaction(1,current_task,seqs[b],counts[b],1,0,2);
            end
            for(i=0;i<counts[b];i=i+1)begin
                if(block_cursor!==i||peek_data!==expected[b*64+i])$fatal(1,"peek/order b=%0d i=%0d",b,i);
                rng=random_word(rng); pause_count=rng[1:0];
                if(i==counts[b]-1)pause_count=7;
                cpu_transaction(0,current_task,0,0,0,{13'd0,expected[b*64+i]},pause_count);
            end
            if(!block_read_complete||peek_data!==0)$fatal(1,"complete cursor wraps payload");
            if(inject_errors)begin
                cpu_transaction(1,current_task^1,seqs[b],counts[b],1,0,3);
                cpu_transaction(1,current_task,seqs[b]+1,counts[b],1,0,2);
                cpu_transaction(1,current_task,seqs[b],counts[b]-1,1,0,1);
            end
            cpu_transaction(1,current_task,seqs[b],counts[b],0,0,4);
            blocks_checked=blocks_checked+1;
        end
    endtask
    task abort_clean;
        integer guard;
        begin
            @(negedge clk); abort_req=1;
            tick;
            @(negedge clk); abort_req=0; #1;
            guard=0;
            while(!abort_done)begin tick; guard=guard+1; if(guard>20)$fatal(1,"abort cleanup timeout"); end
            if(owned!==0||fault||rsp_valid||compute_done||!begin_ready)$fatal(1,"abort did not invalidate state");
            aborts=aborts+1;
        end
    endtask
    task expect_fault;
        input [7:0] code;
        begin
            if(!fault||error_code!==code)$fatal(1,"expected production fault %h got %b/%h",code,fault,error_code);
            if(alloc_ready||fill_ready||publish_ready||cmd_ready)$fatal(1,"fault did not stop new operations");
            repeat(3)begin tick; if(!fault||error_code!==code)$fatal(1,"fault not sticky"); end
            fault_cases=fault_cases+1;
            abort_clean;
        end
    endtask
    task abort_with_response;
        input ack_flag;
        input integer b;
        integer i;
        reg [31:0] snapshot;
        begin
            snapshot=ack_flag?0:{13'd0,expected[b*64]};
            @(negedge clk); cmd_valid=1;cmd_ack=ack_flag;cmd_task_id=current_task;
            cmd_sequence=seqs[b];cmd_count=counts[b];rsp_ready=0;
            @(posedge clk);if(!cmd_ready)$fatal(1,"abort test cmd stalled");#1;
            if(!rsp_valid||rsp_error||rsp_data!==snapshot)$fatal(1,"abort response initial");
            @(negedge clk);cmd_valid=0;abort_req=1;
            tick;
            @(negedge clk);abort_req=0;
            for(i=0;i<8;i=i+1)begin
                tick;stalls=stalls+1;
                if(!abort_pending||abort_done||!rsp_valid||rsp_data!==snapshot||rsp_error)
                    $fatal(1,"ABORT swallowed stalled response");
            end
            @(negedge clk);rsp_ready=1;tick;
            if(rsp_valid||abort_done)$fatal(1,"abort retirement boundary");
            tick;
            if(!abort_done||abort_pending||owned!==0||fault||!begin_ready)$fatal(1,"abort response cleanup");
            @(negedge clk);rsp_ready=0;
            aborts=aborts+1;
        end
    endtask

    integer b,i,j;
    initial begin
        if($value$plusargs("vcd=%s",vcd_path))begin $dumpfile(vcd_path);$dumpvars(0,tb_result_blocks);end
        fresh;new_session(32'h10203040);
        // 两块同时READY，第三次分配必须等CPU ACK释放；且指针回绕后不改变顺序。
        make_block(0,0,0,1,0);make_block(1,96,0,2,0);
        if(owned!==3||alloc_ready)$fatal(1,"two-block capacity");
        fork
            begin allocate(2,4,1,3,0);end
            begin repeat(7)tick;consume(0,1);end
        join
        fill_block(2);publish;
        consume(1,1);consume(2,0);
        for(b=3;b<19;b=b+2)begin
            make_block(b,((b%25)*4),b%15,b+1,0);
            make_block(b+1,96,(b+1)%15,b+2,0);
            consume(b,0);consume(b+1,0);
        end
        // 老块的CPU读取与新块核填写真正并行，不能混用生产/消费块身份。
        make_block(20,44,7,20,0);
        fork
            begin make_block(21,96,8,21,0);end
            begin consume(20,0);end
        join
        consume(21,0);
        if(concurrent_fill_read==0)$fatal(1,"missing simultaneous fill/read coverage");
        if(owned!==0||compute_done)$fatal(1,"nonfinal completion meaning");
        abort_clean;

        // 读响应和ACK响应受阻期间中止：均必须先交付已接受响应。
        new_session(32'habcdef00);make_block(30,0,0,1,0);abort_with_response(0,30);
        new_session(32'habcdef01);make_block(31,0,0,1,0);
        for(i=0;i<64;i=i+1)cpu_transaction(0,current_task,0,0,0,{13'd0,expected[31*64+i]},0);
        abort_with_response(1,31);

        // 生产侧非法输入：每例通过公开接口建立前提，绝不强改内部状态。
        new_session(32'h2000);allocate(40,0,0,1,0);
        one_fill(0,0,0,0);one_fill(0,1,0,0);expect_fault(8'h22);
        new_session(32'h2001);allocate(40,0,0,1,0);
        one_fill(0,0,0,1);expect_fault(8'h22);
        new_session(32'h2002);allocate(40,0,0,1,0);
        one_fill(0,0,3'b100,0);expect_fault(8'h22);
        new_session(32'h2003);allocate(40,96,0,1,0);
        one_fill(48,0,0,0);expect_fault(8'h22);
        new_session(32'h2004);allocate(40,0,0,1,0);
        one_fill(0,0,0,0);publish;expect_fault(8'h23);
        new_session(32'h2005);
        @(negedge clk);alloc_valid=1;alloc_task_id=current_task;alloc_row=0;alloc_tile=0;alloc_count=48;alloc_final=0;
        @(posedge clk);if(!alloc_ready)$fatal(1,"bad alloc readiness");#1;
        @(negedge clk);alloc_valid=0;expect_fault(8'h21);

        // 最终块：compute_done仅在publish后出现；ACK后响应未排空也不能重开会话。
        new_session(32'h3000);allocate(50,96,15,1,1);fill_block(50);
        if(compute_done)$fatal(1,"compute_done before publish");
        publish;if(!compute_done||alloc_ready)$fatal(1,"final publish status");
        consume(50,1);
        if(!begin_ready)$fatal(1,"new session not allowed after final ACK retires");
        new_session(32'h3001);make_block(51,0,0,1,0);consume(51,0);
        abort_clean;

        // 在真实事务中达到SEQUENCE_MAX，随后分配必须拒绝，不能回绕覆盖旧身份。
        new_session(32'h4000);
        for(b=64;b<128;b=b+1)begin make_block(b,0,0,b-63,0);consume(b,0);end
        @(negedge clk);alloc_valid=1;alloc_task_id=current_task;alloc_row=0;alloc_tile=0;alloc_count=64;alloc_final=0;
        @(posedge clk);if(!alloc_ready)$fatal(1,"exhaustion test not accepted");#1;
        @(negedge clk);alloc_valid=0;expect_fault(8'h21);
        if(blocks_checked!=87||fault_cases!=7)$fatal(1,"coverage tally blocks=%0d faults=%0d",blocks_checked,fault_cases);
        $display("PASS CONTROL_RESULT cycles=%0d allocations=%0d fills=%0d publishes=%0d reads=%0d acks=%0d errors=%0d aborts=%0d fault_cases=%0d stalls=%0d blocks=%0d concurrent_fill_read=%0d",cycles,allocations,fills,publishes,reads,acks,errors,aborts,fault_cases,stalls,blocks_checked,concurrent_fill_read);
        $finish;
    end
endmodule

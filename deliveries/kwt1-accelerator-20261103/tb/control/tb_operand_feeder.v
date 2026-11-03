`timescale 1ns/1ps
`include "kwt_control_config.vh"
`default_nettype none

// 供数器独立自检：不读取DUT内部计数/数组，期望值只来自外部启动和请求合同。
// 模型为测试专用L1端点，不是官方SRAM模型；E0请求，E1沿DUT消费返回。
module tb_operand_feeder;
    reg clk=0;
    always #10 clk=~clk;
    reg rst_n=0, start_valid=0;
    wire start_ready;
    reg [`KWT_ROW_GROUP_WIDTH-1:0] start_row_group=0;
    reg start_w_slot=0;
    wire [3:0] x_rd_en;
    wire [43:0] x_addr;
    reg [63:0] x_rd_data=0;
    reg [3:0] x_rd_valid=0,x_access_error=0;
    wire [7:0] w_rd_en;
    wire [63:0] w_addr;
    reg [127:0] w_rd_data=0;
    reg [7:0] w_rd_valid=0,w_access_error=0;
    wire out_valid;
    reg out_ready=0;
    wire [63:0] out_x,out_w;
    wire busy,feed_done,fault;
    kwt_operand_feeder dut(.*);

    integer cycles=0, blocks=0, groups=0, faults=0, resets=0, canceled=0;
    integer reqs=0, delivered=0, x_groups=0, row=0, slot=0;
    integer model_b, mon_b, kk, gg, guard, r, s, local_cycle;
    integer stall_cycles=0,max_outstanding=0,held_checks=0,final_hold_count=0,final_stalls=0;
    reg active=0, held=0, previous_done=0;
    reg [63:0] held_x,held_w;
    reg [31:0] rng=32'hf3a0197d;
    integer inject_mode=0;
    reg inject_armed=0;
    reg [15:0] expected_x,expected_w;
    reg [3:0] expected_mask;
    reg [7:0] expected_wmask;

    // 编码同时区分row、k、bank、slot和g，含正负16位位图，不做算术量化。
    function [15:0] x_word;
        input integer rowgroup,bank,k;
        begin x_word=((rowgroup*4051) ^ (bank*16'h3927) ^ (k*251) ^ 16'ha55a); end
    endfunction
    function [15:0] w_word;
        input integer wslot,bank,g,k;
        begin w_word=((wslot*16'h6b17) ^ (bank*16'h1973) ^ (g*16'h247d) ^ (k*479) ^ 16'hc33c); end
    endfunction
    task rand_step;
        begin rng=rng^(rng<<13);rng=rng^(rng>>17);rng=rng^(rng<<5);end
    endtask

    // 独立L1读端点：只依据端口地址生成返回，不窥视DUT的标签/状态。
    always @(posedge clk) begin
        if (!rst_n) begin
            x_rd_valid<=0;w_rd_valid<=0;
            x_access_error<=0;w_access_error<=0;
        end else begin
            x_rd_valid<=x_rd_en;
            w_rd_valid<=w_rd_en;
            x_access_error<=0;w_access_error<=0;
            for(model_b=0;model_b<4;model_b=model_b+1) begin
                if(x_rd_en[model_b])
                    x_rd_data[model_b*16+:16]<=x_word(x_addr[model_b*11+:11]/64,model_b,x_addr[model_b*11+:11]%64);
                else x_rd_data[model_b*16+:16]<=16'hxxxx;
            end
            for(model_b=0;model_b<8;model_b=model_b+1) begin
                if(w_rd_en[model_b])
                    w_rd_data[model_b*16+:16]<=w_word(model_b/4,model_b%4,w_addr[model_b*8+:8]/64,w_addr[model_b*8+:8]%64);
                else w_rd_data[model_b*16+:16]<=16'hxxxx;
            end
            // 未参与本次请求的槽/尾行故意返回噪声，测试只检查相关bank。
            if (w_rd_en==8'h0f) begin w_rd_valid[7:4]<=4'hf;w_access_error[7:4]<=4'hf;end
            if (w_rd_en==8'hf0) begin w_rd_valid[3:0]<=4'hf;w_access_error[3:0]<=4'hf;end
            if (x_rd_en==4'h7) begin x_rd_valid[3]<=1'b0;x_access_error[3]<=1'b1;end
            if (inject_armed && (|w_rd_en)) begin
                inject_armed=0;
                case(inject_mode)
                    1: if(w_rd_en[0]) w_rd_valid[0]<=0;else w_rd_valid[4]<=0;
                    2: x_rd_valid[0]<=0;
                    3: if(w_rd_en[0]) w_access_error[0]<=1;else w_access_error[4]<=1;
                    4: x_access_error[0]<=1;
                endcase
            end
        end
    end

    // 在上升沿NBA更新前检查：与真实下游触发器采样时刻一致。
    always @(posedge clk) begin
        cycles=cycles+1;
        if(cycles>200000) $fatal(1,"feeder global timeout");
        if(!rst_n) begin
            active=0;held=0;previous_done=0;reqs=0;delivered=0;x_groups=0;
            if((|x_rd_en)||(|w_rd_en)||out_valid||start_ready)
                $fatal(1,"reset did not isolate interface");
        end else begin
            if(start_valid&&start_ready) begin
                if(active) $fatal(1,"double accepted start");
                row=start_row_group;slot=start_w_slot;
                reqs=0;delivered=0;x_groups=0;
                active=(start_row_group<25);
            end
            if(held && !fault) begin
                if(!out_valid || out_x!==held_x || out_w!==held_w)
                    $fatal(1,"output changed under backpressure row=%0d slot=%0d delivered=%0d",row,slot,delivered);
                held_checks=held_checks+1;
            end
            held=out_valid&&!out_ready;
            if(held) begin held_x=out_x;held_w=out_w;stall_cycles=stall_cycles+1;end
            if(out_valid&&out_ready) begin
                if(!active||delivered>=256) $fatal(1,"extra output");
                kk=delivered/4;gg=delivered%4;
                for(mon_b=0;mon_b<4;mon_b=mon_b+1) begin
                    expected_x=(row==24&&mon_b==3)?16'h0000:x_word(row,mon_b,kk);
                    expected_w=w_word(slot,mon_b,gg,kk);
                    if(out_x[mon_b*16+:16]!==expected_x || out_w[mon_b*16+:16]!==expected_w)
                        $fatal(1,"data mismatch row=%0d slot=%0d group=%0d lane=%0d x=%h/%h w=%h/%h",row,slot,delivered,mon_b,out_x[mon_b*16+:16],expected_x,out_w[mon_b*16+:16],expected_w);
                end
                delivered=delivered+1;groups=groups+1;
            end
            if(|w_rd_en) begin
                if(!active||reqs>=256) $fatal(1,"extra request");
                kk=reqs/4;gg=reqs%4;
                expected_wmask=slot?8'hf0:8'h0f;
                expected_mask=(gg==0)?((row==24)?4'h7:4'hf):4'h0;
                if(w_rd_en!==expected_wmask || x_rd_en!==expected_mask)
                    $fatal(1,"request bank mask req=%0d row=%0d x=%h w=%h",reqs,row,x_rd_en,w_rd_en);
                for(mon_b=0;mon_b<4;mon_b=mon_b+1) begin
                    if(w_addr[(slot*4+mon_b)*8+:8] !== (gg*64+kk))
                        $fatal(1,"W address req=%0d lane=%0d",reqs,mon_b);
                    if(x_rd_en[mon_b] && x_addr[mon_b*11+:11] !== (row*64+kk))
                        $fatal(1,"X address req=%0d lane=%0d",reqs,mon_b);
                end
                reqs=reqs+1;
                if(gg==0) x_groups=x_groups+1;
            end else if(|x_rd_en) $fatal(1,"X request without W group");
            if(reqs-delivered>2) $fatal(1,"queue plus in-flight exceeds two groups");
            if(reqs-delivered>max_outstanding) max_outstanding=reqs-delivered;
            if(feed_done) begin
                if(previous_done) $fatal(1,"feed_done not a pulse");
                if(!active || busy || reqs!=256 || delivered!=256 || x_groups!=64)
                    $fatal(1,"incorrect completion req=%0d delivered=%0d xgroups=%0d",reqs,delivered,x_groups);
                blocks=blocks+1;active=0;
            end
            previous_done=feed_done;
            if(fault && ((|x_rd_en)||(|w_rd_en)||out_valid||start_ready||feed_done))
                $fatal(1,"fault not isolating new operations");
        end
    end

    task fresh;
        begin
            @(negedge clk);rst_n=0;start_valid=0;out_ready=0;
            if(active) canceled=canceled+1;
            repeat(2) @(negedge clk);
            rst_n=1;inject_mode=0;inject_armed=0;resets=resets+1;
        end
    endtask
    task launch;
        input integer rg,ws;
        begin
            @(negedge clk);start_row_group=rg;start_w_slot=ws;start_valid=1;
            @(posedge clk);while(!start_ready) @(posedge clk);
            @(negedge clk);start_valid=0;
            // 故意改变非valid启动输入，检查内部已保存块身份。
            start_row_group=31;start_w_slot=!ws;
        end
    endtask
    task complete_block;
        input integer rg,ws,style;
        integer goal;
        begin
            goal=blocks+1;out_ready=0;launch(rg,ws);local_cycle=0;final_hold_count=0;
            while(blocks<goal) begin
                @(negedge clk);local_cycle=local_cycle+1;rand_step;
                // 明确让最后一组受阻17拍，防止提前done或最后一项丢失。
                if(style!=0 && delivered==255 && final_hold_count<17) begin
                    out_ready=0;final_hold_count=final_hold_count+1;final_stalls=final_stalls+1;
                end else if(style==0) out_ready=1;
                else if(local_cycle<25 || (local_cycle%131)<43) out_ready=0;
                else out_ready=(rng[3:0]>3);
                if(fault) $fatal(1,"unexpected fault normal block");
                if(local_cycle>5000) $fatal(1,"block timeout");
            end
            @(negedge clk);out_ready=0;
        end
    endtask
    task expect_fault;
        begin
            guard=0;
            while(!fault) begin @(negedge clk);guard=guard+1;if(guard>30)$fatal(1,"expected fault absent");end
            active=0;held=0;faults=faults+1;
            repeat(4) @(negedge clk);
            if(!fault) $fatal(1,"fault did not latch");
        end
    endtask

    initial begin
        fresh;
        // 所有25个行组、两个W槽均完成；第一块连续ready，其余混合长停顿和随机ready。
        for(s=0;s<2;s=s+1) for(r=0;r<25;r=r+1)
            complete_block(r,s,(r==0&&s==0)?0:1);
        // 在途一项时取消，再在缓存已满时取消；恢复后完整新块不能混入旧数据。
        launch(3,0);wait(reqs==1);fresh;
        complete_block(24,1,1);
        launch(8,1);wait(reqs==2);repeat(4)@(negedge clk);fresh;
        complete_block(17,0,0);
        // 非法启动无读请求。
        launch(25,0);expect_fault;fresh;
        launch(31,1);expect_fault;fresh;
        // 在第一个g0返回分别破坏W/X valid、W/X access_error。
        for(r=1;r<=4;r=r+1) begin
            inject_mode=r;inject_armed=1;launch(2,r%2);expect_fault;fresh;
        end
        complete_block(0,1,0);
        if(blocks!=53 || groups!=53*256 || faults!=6 || canceled!=2 || max_outstanding!=2 || held_checks<100 || final_stalls<17)
            $fatal(1,"coverage short blocks=%0d groups=%0d faults=%0d canceled=%0d max=%0d hold=%0d",blocks,groups,faults,canceled,max_outstanding,held_checks);
        $display("PASS OPERAND_FEEDER blocks=%0d groups=%0d faults=%0d canceled=%0d resets=%0d cycles=%0d stalls=%0d hold_checks=%0d max_outstanding=%0d final_stalls=%0d",blocks,groups,faults,canceled,resets,cycles,stall_cycles,held_checks,max_outstanding,final_stalls);
        $finish;
    end
endmodule
`default_nettype wire

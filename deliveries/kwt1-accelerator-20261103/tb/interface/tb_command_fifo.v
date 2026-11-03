`timescale 1ns/1ps
`include "kwt_icb_config.vh"
`default_nettype none

// 最小单项命令缓冲独立TB：外部黄金队列，不读取DUT寄存器。
module tb_command_fifo;
    reg clk=0;
    always #10 clk=~clk;
    reg rst_n=0,clear=0,in_valid=0,out_ready=0;
    wire in_ready,out_valid,empty;
    reg [`KWT_ICB_COMMAND_WIDTH-1:0] in_data=0;
    wire [`KWT_ICB_COMMAND_WIDTH-1:0] out_data;
    kwt_command_fifo dut(.*);
    reg golden_valid=0;
    reg [`KWT_ICB_COMMAND_WIDTH-1:0] golden_data=0;
    reg held=0;
    reg [`KWT_ICB_COMMAND_WIDTH-1:0] held_data;
    reg [31:0] rng=32'hb4197e21;
    integer cycles=0,pushes=0,pops=0,canceled=0,clears=0,replacements=0,hold_checks=0;
    integer i,word;
    reg take_in,take_out;
    task random_step;
        begin rng=rng^(rng<<13);rng=rng^(rng>>17);rng=rng^(rng<<5);end
    endtask
    task new_data;
        begin
            for(word=0;word<`KWT_ICB_COMMAND_WIDTH;word=word+1) begin
                random_step;in_data[word]=rng[17];
            end
        end
    endtask
    always @(posedge clk) begin
        cycles=cycles+1;
        if(!rst_n||clear) begin
            if(in_ready!==0||out_valid!==0)
                $fatal(1,"reset/clear accepted data");
            if(golden_valid)canceled=canceled+1;
            golden_valid=0;held=0;
            if(clear)clears=clears+1;
        end else begin
            // empty包含“本拍正在入队”，防止任务控制过早报告输入排空。
            if(empty!==(!golden_valid&&!(in_valid&&in_ready)) || out_valid!==golden_valid)
                $fatal(1,"FIFO occupancy mismatch cycle=%0d",cycles);
            if(in_ready!==(!golden_valid||out_ready))
                $fatal(1,"FIFO in_ready mismatch cycle=%0d",cycles);
            if(out_valid&&out_data!==golden_data)
                $fatal(1,"FIFO data mismatch cycle=%0d",cycles);
            if(held)begin
                if(!out_valid||out_data!==held_data)$fatal(1,"stalled output changed");
                hold_checks=hold_checks+1;
            end
            held=out_valid&&!out_ready;
            if(held)held_data=out_data;
            take_in=in_valid&&in_ready;
            take_out=out_valid&&out_ready;
            if(take_out)begin pops=pops+1;golden_valid=0;end
            if(take_in)begin pushes=pushes+1;golden_data=in_data;golden_valid=1;end
            if(take_in&&take_out)replacements=replacements+1;
        end
    end
    initial begin
        repeat(2)@(negedge clk);rst_n=1;
        // 单项填满后，输入可以改变但不能覆盖阻塞中的已有快照。
        @(negedge clk);in_valid=1;new_data;out_ready=0;
        repeat(12)begin @(negedge clk);new_data;end
        // 连续每拍同进同出替换，检查不会丢失旧项或跳过新项。
        out_ready=1;
        repeat(200)begin @(negedge clk);new_data;end
        // 清除优先，即使输入输出都valid/ready也不能发生事务。
        @(negedge clk);clear=1;in_valid=1;out_ready=1;new_data;
        @(negedge clk);clear=0;out_ready=0;
        @(negedge clk);rst_n=0;
        @(negedge clk);rst_n=1;in_valid=0;
        for(i=0;i<15000;i=i+1)begin
            @(negedge clk);random_step;
            in_valid=rng[0]||rng[1];out_ready=rng[3];clear=(rng[11:4]==8'hc7);
            new_data;
        end
        @(negedge clk);clear=0;in_valid=0;out_ready=1;
        repeat(3)@(negedge clk);
        if(golden_valid||!empty||pushes!=pops+canceled||replacements<200||hold_checks<500||clears<5)
            $fatal(1,"FIFO ledger/coverage fail pushes=%0d pops=%0d canceled=%0d replace=%0d holds=%0d clear=%0d",pushes,pops,canceled,replacements,hold_checks,clears);
        $display("PASS COMMAND_FIFO cycles=%0d pushes=%0d pops=%0d canceled=%0d replacements=%0d hold_checks=%0d clears=%0d",cycles,pushes,pops,canceled,replacements,hold_checks,clears);
        $finish;
    end
endmodule
`default_nettype wire

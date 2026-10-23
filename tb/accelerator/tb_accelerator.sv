`timescale 1ns/1ps
module tb_accelerator;
    localparam M=`TEST_M,N=`TEST_N,LAYERS=`TEST_LAYERS;
    reg clk=0;always #5 clk=~clk;
    reg rst_n=0,abort_i=0,in_valid=0;
    wire in_ready;
    reg [3:0] in_op=0,in_layer_id=1;
    reg [31:0] in_task_id=0;
    reg [7:0] in_tile_id=0;
    reg [15:0] in_index=0;
    reg signed [47:0] in_data=0;
    reg [5:0] in_shift=16;
    wire out_valid;reg out_ready=0;
    wire [31:0] out_task_id,out_y_index;
    wire signed [31:0] out_data;
    wire [2:0] out_flags;
    wire task_done,busy,fault;wire [7:0] error_code;
    integer cycle=0,layer=0,i,t,k,c,outputs=0,total_outputs=0,tasks=0;
    integer pause_outputs=0,checking=0,prebegun=0;
    reg seen[0:M*N-1];
    reg signed [15:0] xv[0:LAYERS*M*64-1],wv[0:LAYERS*64*N-1];
    reg signed [31:0] bv[0:LAYERS*N-1],yv[0:LAYERS*M*N-1];
    reg [3:0] fv[0:LAYERS*M*N-1];
    reg stalled=0;reg [98:0] held;
    integer expected_index;
    accelerator_top #(.M(M),.N(N),.READ_LATENCY(`TEST_LATENCY),.USE_MACRO(`TEST_MACRO)) dut(.*);
    always @(negedge clk)begin
        // 短暂停顿与周期性长暂停，覆盖块末和tile末结果保持。
        out_ready=rst_n&&!abort_i&&!pause_outputs&&(cycle%7<4)&&(cycle%503<450);
    end
    always @(posedge clk)begin
        if(!rst_n||abort_i||fault)begin cycle=0;stalled=0;end
        else begin
            cycle++;
            if(stalled&&(!out_valid||{out_task_id,out_y_index,out_data,out_flags}!==held))
                $fatal(1,"output changed while stalled");
            stalled=out_valid&&!out_ready;
            held={out_task_id,out_y_index,out_data,out_flags};
            if(checking&&fault)$fatal(1,"unexpected protocol fault=%h layer=%0d",error_code,layer);
            if(checking&&out_valid&&out_ready)begin
                // V07 tile优先；每个tile内按有效行、局部列递增。
                expected_index=((outputs%(M*16))/16)*N+(outputs/(M*16))*16+outputs%16;
                if(out_y_index!==expected_index||out_y_index>=M*N)
                    $fatal(1,"index order got=%0d expected=%0d",out_y_index,expected_index);
                if(seen[out_y_index])$fatal(1,"duplicate index");
                if(out_task_id!==(32'h1000+layer)||out_data!==yv[layer*M*N+out_y_index]||
                    out_flags!==fv[layer*M*N+out_y_index][2:0])
                    $fatal(1,"numeric/tag mismatch layer=%0d index=%0d got=%0d/%b expected=%0d/%b task=%h",
                        layer,out_y_index,out_data,out_flags,yv[layer*M*N+out_y_index],fv[layer*M*N+out_y_index],out_task_id);
                seen[out_y_index]=1;outputs++;total_outputs++;
            end
            if(checking&&task_done)begin
                if(outputs!=M*N)$fatal(1,"done before complete writeback: %0d",outputs);
                for(integer z=0;z<M*N;z++)if(!seen[z])$fatal(1,"missing result");
                tasks++;
            end
        end
    end
    task send(input integer op,input integer tile,input integer idx,input reg signed [47:0] value);
        begin
            @(negedge clk);in_valid=0;
            // 在k内部和加载过程随机样式插空，不依赖DUT时序。
            if((idx+op)%19==3)repeat(2)@(negedge clk);
            in_op=op;in_tile_id=tile;in_index=idx;in_data=value;in_valid=1;
            @(posedge clk);while(!in_ready)@(posedge clk);
            @(negedge clk);in_valid=0;
        end
    endtask
    task cancel;
        begin
            @(negedge clk);in_valid=0;abort_i=1;
            @(negedge clk);abort_i=0;
            repeat(2)@(negedge clk);
            if(busy||fault||out_valid)$fatal(1,"abort did not empty accelerator");
        end
    endtask
    task load_first_tile;
        begin
            if(!prebegun)send(0,0,0,0);
            prebegun=0;
            // 连续每拍加载X：验证没有命令队列时的相邻写入/计数更新。
            @(negedge clk);in_valid=1;in_op=1;in_tile_id=0;
            for(integer a=0;a<M*64;a++)begin
                in_index=a;in_data=xv[layer*M*64+a];
                @(posedge clk);while(!in_ready)@(posedge clk);
                @(negedge clk);
            end
            in_valid=0;
            send(2,0,0,0);
            for(integer a=0;a<1024;a++)send(3,0,a,wv[layer*64*N+(a/16)*N+a%16]);
            for(integer a=0;a<16;a++)send(4,0,a,bv[layer*N+a]);
            send(5,0,0,0);send(6,0,0,0);
        end
    endtask
    initial begin
        $readmemh("out/accelerator-vectors/x.hex",xv);
        $readmemh("out/accelerator-vectors/w.hex",wv);
        $readmemh("out/accelerator-vectors/bias.hex",bv);
        $readmemh("out/accelerator-vectors/y.hex",yv);
        $readmemh("out/accelerator-vectors/flags.hex",fv);
        for(i=0;i<LAYERS*M*N;i++)if((^yv[i]===1'bx)||(^fv[i]===1'bx))$fatal(1,"unknown golden");
        repeat(3)@(negedge clk);rst_n=1;
        // 明确的非法命令：未装载便START；故障必须锁存，abort后可重新开始。
        in_task_id=32'h1000;send(0,0,0,0);send(6,0,0,0);
        if(!fault)$fatal(1,"early START not rejected");cancel;
        // X必须是signed16的正确扩展，不能静默截断。
        send(0,0,0,0);send(1,0,0,48'd65535);
        if(!fault)$fatal(1,"invalid X extension accepted");cancel;
        // 重复加载同一个index和错误task身份都不能污染新任务。
        send(0,0,0,0);send(1,0,0,1);send(1,0,0,2);
        if(!fault)$fatal(1,"duplicate X index accepted");cancel;
        send(0,0,0,0);in_task_id=99;send(1,0,0,1);
        if(!fault)$fatal(1,"wrong task accepted");cancel;in_task_id=32'h1000;
        // 计算进行中同步中止，再从独立输入完整重算。
        load_first_tile;repeat(25)@(negedge clk);cancel;
        // 在运行期收到非法BEGIN，必须撤销在途计算并锁存fault。
        load_first_tile;repeat(25)@(negedge clk);send(0,0,0,0);
        if(!fault||out_valid)$fatal(1,"running fault did not cancel backend");cancel;
        // 输出背压时中止，不得遗留转换valid或旧存储返回。
        pause_outputs=1;load_first_tile;wait(out_valid===1);
        repeat(3)@(negedge clk);cancel;pause_outputs=0;
        pause_outputs=1;load_first_tile;wait(out_valid===1);
        send(6,0,0,0);
        if(!fault||out_valid)$fatal(1,"stalled output survived protocol fault");
        cancel;pause_outputs=0;
        // 同步复位也清掉在途任务，不依靠数组清零保证隔离。
        load_first_tile;repeat(10)@(negedge clk);
        rst_n=0;repeat(2)@(negedge clk);rst_n=1;repeat(2)@(negedge clk);
        if(busy||fault||out_valid)$fatal(1,"reset did not empty accelerator");
        for(layer=0;layer<LAYERS;layer++)begin
            outputs=0;for(i=0;i<M*N;i++)seen[i]=0;
            in_task_id=32'h1000+layer;in_layer_id=layer+1;checking=1;
            load_first_tile;
            for(t=1;t<N/16;t++)begin
                send(2,t,0,0); // 无空槽时保持命令等待，不能提前覆盖ACTIVE槽。
                for(k=0;k<64;k++)for(c=0;c<16;c++)send(3,t,k*16+c,wv[layer*64*N+k*N+t*16+c]);
                for(c=0;c<16;c++)send(4,t,c,bv[layer*N+t*16+c]);
                send(5,t,0,0);
            end
            wait(task_done===1);
            if(layer+1<LAYERS)begin
                // 完成通知当拍即可接收下一任务的BEGIN，不能误报旧任务仍忙。
                @(negedge clk);in_valid=1;in_op=0;in_task_id=32'h1000+layer+1;in_layer_id=layer+2;
                in_tile_id=0;in_index=0;in_data=0;
                @(posedge clk);if(!in_ready)$fatal(1,"completion boundary BEGIN stalled");
                #1;if(fault)$fatal(1,"completion boundary BEGIN faulted");
                @(negedge clk);in_valid=0;prebegun=1;
            end else begin @(posedge clk);#1;@(negedge clk);end
            checking=0;
            repeat(2)@(negedge clk);
            if(!prebegun&&busy)$fatal(1,"busy held after task completion");
        end
        if(tasks!=LAYERS)$fatal(1,"task count mismatch");
        $display("PASS: accelerator M=%0d N=%0d L=%0d latency=%0d macro=%0d: %0d Y/flags/index checks; faults/reset/abort/backpressure",M,N,LAYERS,`TEST_LATENCY,`TEST_MACRO,total_outputs);
        $finish;
    end
    initial begin #400000000;$fatal(1,"accelerator timeout layer=%0d outputs=%0d",layer,outputs);end
endmodule

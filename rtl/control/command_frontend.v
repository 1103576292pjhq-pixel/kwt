`timescale 1ns/1ps
// 简单有序命令流：valid&&ready的边沿就是命令执行/存储写入的边沿。
// 不另设命令队列，所以COMMIT不可能越过前一个尚未完成的写入。
module command_frontend #(parameter integer M=99,N=256)(
    input wire clk,rst_n,abort_i,
    input wire in_valid,output wire in_ready,
    input wire [3:0] in_op,in_layer_id,
    input wire [31:0] in_task_id,
    input wire [7:0] in_tile_id,
    input wire [15:0] in_index,
    input wire signed [47:0] in_data,
    input wire [5:0] in_shift,
    input wire task_done_i,
    input wire open_ready_i,load_open_i,tile_available_i,
    input wire [4:0] next_load_tile_i,
    output wire new_task_o,x_load_o,tile_open_o,w_load_o,bias_load_o,tile_commit_o,start_o,
    output reg session_o,running_o,
    output reg [31:0] task_id_o,
    output reg fault_o,output reg [7:0] error_code_o
);
    reg [3:0] layer_id;
    reg [12:0] x_count;
    reg [10:0] w_count;
    reg [4:0] bias_count;
    reg command_ok;
    wire xw_fits=in_data=={{32{in_data[15]}},in_data[15:0]};
    wire bias_fits=in_data=={{16{in_data[31]}},in_data[31:0]};
    wire same_task=session_o&&in_task_id==task_id_o&&in_layer_id==layer_id&&in_shift==16;
    always @* begin
        command_ok=0;
        // task_done有效时旧任务已经排空，可在通知当拍接受下一BEGIN。
        if(in_op==0)command_ok=(!session_o||task_done_i)&&in_layer_id>=1&&in_layer_id<=12&&in_shift==16;
        else if(same_task)case(in_op)
            1:command_ok=!running_o&&!load_open_i&&next_load_tile_i==0&&
                x_count<M*64&&in_index=={3'b0,x_count}&&xw_fits;
            2:command_ok=x_count==M*64&&!load_open_i&&next_load_tile_i<N/16&&
                in_tile_id=={3'b0,next_load_tile_i}&&(running_o||next_load_tile_i==0);
            3:command_ok=load_open_i&&in_tile_id=={3'b0,next_load_tile_i}&&
                w_count<1024&&bias_count==0&&in_index=={5'b0,w_count}&&xw_fits;
            4:command_ok=load_open_i&&in_tile_id=={3'b0,next_load_tile_i}&&
                w_count==1024&&bias_count<16&&in_index=={11'b0,bias_count}&&bias_fits;
            5:command_ok=load_open_i&&in_tile_id=={3'b0,next_load_tile_i}&&w_count==1024&&bias_count==16;
            6:command_ok=!running_o&&x_count==M*64&&!load_open_i&&next_load_tile_i==1&&tile_available_i;
            default:command_ok=0;
        endcase
    end
    // 合法OPEN但两个槽都被占用：反压等空槽；非法命令：接收后锁存fault。
    // 两者必须区分，否则错误命令可能永久等待而没有错误报告。
    wire wait_for_slot=in_op==2&&command_ok&&!open_ready_i;
    assign in_ready=rst_n&&!abort_i&&!fault_o&&!wait_for_slot;
    wire fire=in_valid&&in_ready;
    wire accepted=fire&&command_ok;
    assign new_task_o=accepted&&in_op==0;
    assign x_load_o=accepted&&in_op==1;
    assign tile_open_o=accepted&&in_op==2;
    assign w_load_o=accepted&&in_op==3;
    assign bias_load_o=accepted&&in_op==4;
    assign tile_commit_o=accepted&&in_op==5;
    assign start_o=accepted&&in_op==6;
    always @(posedge clk)begin
        if(!rst_n||abort_i)begin
            session_o<=0;running_o<=0;task_id_o<=0;layer_id<=0;
            x_count<=0;w_count<=0;bias_count<=0;fault_o<=0;error_code_o<=0;
        end else begin
            if(task_done_i)begin session_o<=0;running_o<=0;end
            if(fire&&!command_ok)begin fault_o<=1;error_code_o<=8'h10+{4'b0,in_op};end
            if(new_task_o)begin
                session_o<=1;running_o<=0;task_id_o<=in_task_id;layer_id<=in_layer_id;
                x_count<=0;w_count<=0;bias_count<=0;
            end
            if(x_load_o)x_count<=x_count+1'b1;
            if(tile_open_o)begin w_count<=0;bias_count<=0;end
            if(w_load_o)w_count<=w_count+1'b1;
            if(bias_load_o)bias_count<=bias_count+1'b1;
            if(start_o)running_o<=1;
        end
    end
endmodule

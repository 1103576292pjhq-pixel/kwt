`timescale 1ns/1ps
`include "kwt_control_config.vh"

// 独立装载控制自检：黄金事务按上游真实接受的命令排队，不读DUT内部状态。
// 检查写沿的物理逻辑bank端口，再以command_done判断哪条合法命令执行完成。
module tb_load_ctrl;
    reg clk=0; always #10 clk=~clk;
    reg rst_n=0,cmd_valid=0;
    wire cmd_ready;
    reg [`KWT_CMD_OP_WIDTH-1:0] cmd_op=0;
    reg [`KWT_LAYER_ID_WIDTH-1:0] cmd_layer_id=1;
    reg [31:0] cmd_task_id=32'h10203040;
    reg [`KWT_CMD_TILE_WIDTH-1:0] cmd_tile_id=0;
    reg [`KWT_CMD_INDEX_WIDTH-1:0] cmd_index=0;
    reg signed [`KWT_CMD_DATA_WIDTH-1:0] cmd_data=0;
    wire begin_valid,start_valid;
    reg begin_ready=1,start_ready=1;
    wire [31:0] begin_task_id;
    wire [3:0] begin_layer_id;
    reg activate_valid=0,activate_slot=0,release_valid=0,release_slot=0;
    wire activate_ready,release_ready;
    wire [3:0] x_wr_en;
    wire [43:0] x_addr;
    wire [63:0] x_wr_data;
    wire [7:0] w_wr_en;
    wire [63:0] w_addr;
    wire [127:0] w_wr_data;
    wire bias_wr_en,bias_wr_slot;
    wire [3:0] bias_wr_addr;
    wire signed [31:0] bias_wr_data;
    wire session_valid,task_started,x_ready,command_empty,command_done,fault;
    wire [31:0] session_task_id;
    wire [3:0] session_layer_id,slot_state;
    wire [7:0] slot_tile,error_code;
    kwt_load_ctrl dut(.*);

    // 每条接受命令携带TB预期错误码；0表示合法。判断来自测试场景，不来自DUT。
    reg [7:0] expected_error=0;
    reg [`KWT_CMD_OP_WIDTH-1:0] queue_op[0:65535];
    reg [`KWT_LAYER_ID_WIDTH-1:0] queue_layer[0:65535];
    reg [31:0] queue_task[0:65535];
    integer queue_tile[0:65535],queue_index[0:65535];
    reg signed [`KWT_CMD_DATA_WIDTH-1:0] queue_data[0:65535];
    reg [7:0] queue_error[0:65535];
    integer qread=0,qwrite=0;
    integer mx=0,mw=0,mb=0,mnext=0,mloadslot=0;
    integer mstate[0:1],mtile[0:1];
    reg msession=0,mstarted=0,mopen=0;
    reg [31:0] mtask;
    reg [3:0] mlayer;
    reg [6335:0] x_seen;
    reg [1023:0] w_seen;
    reg [15:0] b_seen;
    reg previous_fault=0;
    reg [3:0] sxen;
    reg [7:0] swen;
    reg [43:0] sxa;
    reg [63:0] sxd,swa;
    reg [127:0] swd;
    reg sben,sbs,sa,sr;
    reg [3:0] sba;
    reg [31:0] sbd;
    integer sas,srs,op,tile,index,bank,addr,chosen;
    integer cycles=0,commands=0,xwrites=0,wwrites=0,bwrites=0;
    integer resets=0,negative_cases=0,activations=0,releases=0;
    integer begin_stalls=0,start_stalls=0,open_stalls=0,pipelined=0;
    integer total_commits=0,sessions=0;
    reg [31:0] random_state=32'h19e52bd1;
    reg pipelining=0;
    function [31:0] next_random;
        input [31:0] a;
        reg [31:0] b;
        begin b=a^(a<<13);b=b^(b>>17);next_random=b^(b<<5);end
    endfunction
    function signed [`KWT_CMD_DATA_WIDTH-1:0] scalar;
        input integer a,b;
        reg signed [15:0] value;
        begin
            case(a%7)
                0:value=-32768;1:value=32767;2:value=-1;3:value=0;
                default:value=(a*179+b*331)^16'h52ac;
            endcase
            scalar={{16{value[15]}},value};
        end
    endfunction
    function signed [`KWT_CMD_DATA_WIDTH-1:0] bias_value;
        input integer a,b;
        reg signed [31:0] value;
        begin
            case(a%5)
                0:value=32'sh80000000;1:value=32'sh7fffffff;2:value=-1;
                default:value=(a*8593+b*131071)^32'h25ace790;
            endcase
            bias_value=value;
        end
    endfunction

    // 沿前采样写使能/地址/数据，沿后检查执行完成、会话和槽状态。
    always @(posedge clk) begin
        cycles=cycles+1;
        if(cycles>500000)$fatal(1,"LOAD timeout");
        if(!rst_n) begin
            qread=0;qwrite=0;mx=0;mw=0;mb=0;mnext=0;mloadslot=0;
            mstate[0]=0;mstate[1]=0;mtile[0]=0;mtile[1]=0;
            msession=0;mstarted=0;mopen=0;x_seen=0;w_seen=0;b_seen=0;
            previous_fault=0;
            // rst_n为同步复位；首复位沿前q_valid尚未初始化，沿后才检查确定值。
            #1;
            if(x_wr_en!==0||w_wr_en!==0||bias_wr_en!==0)$fatal(1,"writes after reset edge");
        end else begin
            sxen=x_wr_en;swen=w_wr_en;sben=bias_wr_en;
            sxa=x_addr;sxd=x_wr_data;swa=w_addr;swd=w_wr_data;
            sbs=bias_wr_slot;sba=bias_wr_addr;sbd=bias_wr_data;
            sa=activate_valid&&activate_ready;sas=activate_slot;
            sr=release_valid&&release_ready;srs=release_slot;
            if(begin_valid&&!begin_ready)begin_stalls=begin_stalls+1;
            if(start_valid&&!start_ready)start_stalls=start_stalls+1;
            if(!command_empty&&!cmd_ready&&!begin_valid&&!start_valid&&!fault)open_stalls=open_stalls+1;
            if(cmd_valid&&cmd_ready) begin
                if(qwrite>=65536)$fatal(1,"test command queue overflow");
                queue_op[qwrite]=cmd_op;queue_layer[qwrite]=cmd_layer_id;
                queue_task[qwrite]=cmd_task_id;queue_tile[qwrite]=cmd_tile_id;
                queue_index[qwrite]=cmd_index;queue_data[qwrite]=cmd_data;
                queue_error[qwrite]=expected_error;qwrite=qwrite+1;
            end
            #1;
            if(command_done) begin
                if(qread>=qwrite||queue_error[qread]!=0)$fatal(1,"unexpected legal command_done");
                op=queue_op[qread];tile=queue_tile[qread];index=queue_index[qread];
                commands=commands+1;
                if(pipelining)pipelined=pipelined+1;
                if(op!=1&&sxen!==0)$fatal(1,"unexpected X write op=%0d",op);
                if(op!=3&&swen!==0)$fatal(1,"unexpected W write op=%0d",op);
                if(op!=4&&sben!==0)$fatal(1,"unexpected bias write op=%0d",op);
                case(op)
                    0:begin
                        msession=1;mtask=queue_task[qread];mlayer=queue_layer[qread];
                        mx=0;mw=0;mb=0;mnext=0;mloadslot=0;mopen=0;mstarted=0;
                        mstate[0]=0;mstate[1]=0;mtile[0]=0;mtile[1]=0;
                        x_seen=0;w_seen=0;b_seen=0;sessions=sessions+1;
                    end
                    1:begin
                        bank=(index/64)%4;addr=(index/256)*64+index%64;
                        if(sxen!==(4'b0001<<bank)||sxa[bank*11+:11]!==addr||
                           sxd[bank*16+:16]!==queue_data[qread][15:0])
                            $fatal(1,"X map index=%0d bank=%0d addr=%0d got=%0d",index,bank,addr,sxa[bank*11+:11]);
                        if(index!=mx||x_seen[index])$fatal(1,"X order/duplicate");
                        x_seen[index]=1;mx=mx+1;xwrites=xwrites+1;
                    end
                    2:begin
                        chosen=(mstate[0]==0)?0:1;
                        if(mstate[chosen]!=0||mopen||tile!=mnext)$fatal(1,"bad reference OPEN");
                        mloadslot=chosen;mstate[chosen]=1;mtile[chosen]=tile;
                        mopen=1;mnext=mnext+1;mw=0;mb=0;w_seen=0;b_seen=0;
                    end
                    3:begin
                        bank=mloadslot*4+index%4;addr=((index%16)/4)*64+index/16;
                        if(swen!==(8'b00000001<<bank)||swa[bank*8+:8]!==addr||
                           swd[bank*16+:16]!==queue_data[qread][15:0])
                            $fatal(1,"W map tile=%0d index=%0d bank=%0d addr=%0d got=%0d",tile,index,bank,addr,swa[bank*8+:8]);
                        if(mstate[mloadslot]!=1||index!=mw||w_seen[index])$fatal(1,"W order/owner");
                        w_seen[index]=1;mw=mw+1;wwrites=wwrites+1;
                    end
                    4:begin
                        if(sben!==1||sbs!==mloadslot||sba!==index||sbd!==queue_data[qread][31:0])
                            $fatal(1,"bias mapping tile=%0d index=%0d",tile,index);
                        if(mstate[mloadslot]!=1||index!=mb||b_seen[index])$fatal(1,"bias order/owner");
                        b_seen[index]=1;mb=mb+1;bwrites=bwrites+1;
                    end
                    5:begin
                        if(mw!=1024||mb!=16||w_seen!=={1024{1'b1}}||b_seen!==16'hffff)
                            $fatal(1,"incomplete COMMIT accepted");
                        mstate[mloadslot]=2;mopen=0;total_commits=total_commits+1;
                    end
                    6:begin
                        if(mstarted)$fatal(1,"START repeated");mstarted=1;
                    end
                    default:$fatal(1,"unexpected command opcode");
                endcase
                qread=qread+1;
            end else if(sxen!==0||swen!==0||sben!==0)$fatal(1,"write without successful execute");
            if(fault&&!previous_fault)begin
                if(qread>=qwrite||queue_error[qread]==0||error_code!==queue_error[qread])
                    $fatal(1,"unexpected fault=%h expected=%h op=%0d",error_code,queue_error[qread],queue_op[qread]);
                if(sxen!==0||swen!==0||sben!==0)$fatal(1,"illegal command wrote storage");
                qread=qread+1;negative_cases=negative_cases+1;
            end
            if(sa)begin
                if(!mstarted||mstate[sas]!=2||mstate[1-sas]==3)$fatal(1,"illegal activate");
                mstate[sas]=3;activations=activations+1;
            end
            if(sr)begin
                if(mstate[srs]!=3)$fatal(1,"illegal release");
                mstate[srs]=0;releases=releases+1;
            end
            if(slot_state!=={2'(mstate[1]),2'(mstate[0])}||slot_tile!=={4'(mtile[1]),4'(mtile[0])})
                $fatal(1,"slot scoreboard state=%h expected=%0d/%0d tiles=%h",slot_state,mstate[0],mstate[1],slot_tile);
            if(session_valid!==msession||task_started!==mstarted)$fatal(1,"session/start status");
            if(msession&&(session_task_id!==mtask||session_layer_id!==mlayer))$fatal(1,"session identity");
            if(x_ready!==(msession&&!fault&&(mx==6336)))$fatal(1,"x_ready progress");
            if(fault&&cmd_ready)$fatal(1,"fault did not stop command acceptance");
            previous_fault=fault;
        end
    end

    task fresh;
        begin
            @(negedge clk);rst_n=0;cmd_valid=0;activate_valid=0;release_valid=0;
            begin_ready=1;start_ready=1;expected_error=0;
            cmd_task_id=32'h10203040;cmd_layer_id=1;
            repeat(2)@(negedge clk);rst_n=1;resets=resets+1;
        end
    endtask
    task drain;
        integer limit;
        begin
            limit=0;
            while(!command_empty&&!fault)begin @(negedge clk);limit=limit+1;if(limit>100)$fatal(1,"drain timeout");end
        end
    endtask
    task enqueue;
        input integer op,tile,index;
        input signed [`KWT_CMD_DATA_WIDTH-1:0] data;
        input [7:0] error;
        integer limit;
        begin
            if(op<0||op>7||tile<0||tile>=16||index<0||index>=8192)
                $fatal(1,"TB command cannot fit current port op=%0d tile=%0d index=%0d",op,tile,index);
            @(negedge clk);cmd_valid=1;cmd_op=op;cmd_tile_id=tile;cmd_index=index;
            cmd_data=data;expected_error=error;limit=0;
            @(posedge clk);
            while(!cmd_ready)begin @(posedge clk);limit=limit+1;if(limit>100)$fatal(1,"command acceptance timeout");end
            @(negedge clk);cmd_valid=0;
        end
    endtask
    task send;
        input integer op,tile,index;
        input signed [`KWT_CMD_DATA_WIDTH-1:0] data;
        begin enqueue(op,tile,index,data,0);drain;end
    endtask
    task bad;
        input integer op,tile,index;
        input signed [`KWT_CMD_DATA_WIDTH-1:0] data;
        input [7:0] error;
        integer limit;
        begin
            enqueue(op,tile,index,data,error);limit=0;
            while(!fault)begin @(negedge clk);limit=limit+1;if(limit>20)$fatal(1,"expected fault timeout");end
            repeat(3)@(negedge clk);
        end
    endtask
    task burst_x;
        integer i;
        begin
            pipelining=1;
            @(negedge clk);cmd_valid=1;cmd_op=1;cmd_tile_id=0;expected_error=0;
            for(i=0;i<6336;i=i+1)begin
                cmd_index=i;cmd_data=scalar(i,0);
                @(posedge clk);while(!cmd_ready)@(posedge clk);
                @(negedge clk);
                random_state=next_random(random_state);
                if(random_state[4:0]==0)begin cmd_valid=0;@(negedge clk);cmd_valid=1;end
            end
            cmd_valid=0;drain;pipelining=0;
            if(!x_ready||x_seen!=={6336{1'b1}})$fatal(1,"full X coverage");
        end
    endtask
    task setup_x;
        begin fresh;send(0,0,0,0);burst_x;end
    endtask
    task load_tile;
        input integer tile;
        integer i;
        begin
            // W/bias分别有序但交错，验证两条独立进度。
            for(i=0;i<1024;i=i+1)begin
                send(3,tile,i,scalar(i,tile));
                if(i<16)send(4,tile,i,bias_value(i,tile));
            end
            send(5,tile,0,0);
        end
    endtask
    task activate;
        input integer slot;
        integer limit;
        begin
            @(negedge clk);activate_slot=slot;activate_valid=1;limit=0;
            @(posedge clk);while(!activate_ready)begin @(posedge clk);limit=limit+1;if(limit>30)$fatal(1,"activate timeout");end
            @(negedge clk);activate_valid=0;
        end
    endtask
    task release_active;
        input integer slot;
        integer limit;
        begin
            @(negedge clk);release_slot=slot;release_valid=1;limit=0;
            @(posedge clk);while(!release_ready)begin @(posedge clk);limit=limit+1;if(limit>30)$fatal(1,"release timeout");end
            @(negedge clk);release_valid=0;
        end
    endtask

    integer t,i,active,other,before_commands;
    initial begin
        // 完整16tile合法事务及活动/装载双槽交错。
        setup_x;send(2,0,0,0);load_tile(0);
        start_ready=0;enqueue(6,0,0,0,0);
        repeat(13)begin @(negedge clk);if(task_started||!start_valid)$fatal(1,"START wait not held");end
        start_ready=1;drain;activate(0);active=0;
        send(2,1,0,0);load_tile(1);
        for(t=2;t<16;t=t+1)begin
            before_commands=commands;enqueue(2,t,0,0,0);
            repeat(9)begin @(negedge clk);if(command_empty||commands!=before_commands||fault)$fatal(1,"full slots must wait OPEN");end
            other=1-active;release_active(active);activate(other);active=other;
            drain;load_tile(t);
        end
        release_active(active);activate(1-active);release_active(1-active);
        if(slot_state!==0||wwrites!=16384||bwrites!=256||total_commits!=16||activations!=16||releases!=16)
            $fatal(1,"incomplete full legal task");
        // 同一实例在无owner时新BEGIN替换会话身份，旧装载进度不能沿用。
        cmd_task_id=32'h55667788;cmd_layer_id=7;send(0,0,0,0);
        if(x_ready||task_started||session_task_id!==32'h55667788)$fatal(1,"new session isolation");
        send(1,0,0,-32768);

        // BEGIN等待时q字段保持；外部命令变化不能污染已接受命令。
        fresh;begin_ready=0;enqueue(0,0,0,0,0);
        repeat(11)begin @(negedge clk);if(!begin_valid||command_empty||session_valid)$fatal(1,"BEGIN wait");end
        cmd_data=32'h56789abc;cmd_task_id=32'hffffffff;
        begin_ready=1;drain;
        if(session_task_id!==32'h10203040)$fatal(1,"q did not snapshot identity");
        // 在q等待时复位，未执行BEGIN必须取消。
        fresh;begin_ready=0;enqueue(0,0,0,0,0);repeat(3)@(negedge clk);
        fresh;repeat(3)@(negedge clk);if(session_valid||!command_empty)$fatal(1,"reset did not cancel q");

        fresh;bad(1,0,0,0,8'h19);
        fresh;send(0,0,0,0);cmd_task_id=32'hffffffff;bad(1,0,0,0,8'h17);
        fresh;send(0,0,0,0);cmd_layer_id=2;bad(1,0,0,0,8'h17);
        fresh;send(0,0,0,0);bad(1,0,1,0,8'h11);
        fresh;send(0,0,0,0);send(1,0,0,0);bad(1,0,0,0,8'h11);
        fresh;send(0,0,0,0);bad(1,0,0,32'h00008000,8'h11);
        fresh;send(0,0,0,0);bad(1,0,0,32'hffff7fff,8'h11);
        fresh;send(0,0,0,0);bad(1,1,0,0,8'h11);
        fresh;send(0,0,0,0);bad(1,0,8191,0,8'h11);
        fresh;send(0,0,0,0);bad(7,0,0,0,8'h18);
        fresh;send(0,0,0,0);bad(2,0,0,0,8'h12);
        fresh;send(0,0,0,0);bad(6,0,0,0,8'h16);
        fresh;send(0,0,0,0);bad(3,0,0,0,8'h13);
        fresh;send(0,0,0,0);bad(4,0,0,0,8'h14);
        fresh;send(0,0,0,0);bad(5,0,0,0,8'h15);
        setup_x;bad(1,0,6336,0,8'h11);
        setup_x;bad(2,1,0,0,8'h12);
        setup_x;send(2,0,0,0);bad(3,0,1,0,8'h13);
        setup_x;send(2,0,0,0);bad(3,0,0,32'h00008000,8'h13);
        setup_x;send(2,0,0,0);bad(3,1,0,0,8'h13);
        setup_x;send(2,0,0,0);bad(4,0,16,0,8'h14);
        // bias端口已完整signed32，所有数据位图均合法；错误用身份/位置验证。
        setup_x;send(2,0,0,0);cmd_task_id=32'h01020304;bad(4,0,0,32'h80000000,8'h17);
        setup_x;send(2,0,0,0);cmd_layer_id=3;bad(4,0,0,32'h7fffffff,8'h17);
        setup_x;send(2,0,0,0);bad(4,1,0,32'h80000000,8'h14);
        setup_x;send(2,0,0,0);bad(5,0,0,0,8'h15);
        setup_x;send(2,0,0,0);load_tile(0);bad(2,1,0,0,8'h12);
        setup_x;send(2,0,0,0);load_tile(0);send(6,0,0,0);bad(6,0,0,0,8'h16);
        setup_x;send(2,0,0,0);for(i=0;i<16;i=i+1)send(4,0,i,bias_value(i,0));bad(4,0,16,0,8'h14);
        setup_x;send(2,0,0,0);for(i=0;i<1024;i=i+1)send(3,0,i,scalar(i,0));bad(3,0,1024,0,8'h13);
        fresh;send(0,0,0,0);send(1,0,0,32767);drain;
        if(negative_cases!=29||begin_stalls<11||start_stalls<13||open_stalls<100||pipelined<6336)
            $fatal(1,"missing requested coverage negatives=%0d",negative_cases);
        $display("PASS LOAD_CTRL cycles=%0d commands=%0d x_writes=%0d w_writes=%0d bias_writes=%0d negatives=%0d resets=%0d sessions=%0d activations=%0d releases=%0d begin_stalls=%0d start_stalls=%0d open_stalls=%0d pipelined=%0d commits=%0d",cycles,commands,xwrites,wwrites,bwrites,negative_cases,resets,sessions,activations,releases,begin_stalls,start_stalls,open_stalls,pipelined,total_commits);
        $finish;
    end
endmodule



`timescale 1ns/1ps
`include "kwt_storage_config.vh"
`default_nettype none

// 逻辑存储接口自检：黄金数组只由TB实际发出的合法请求更新。
// 在下一上升沿、DUT非阻塞更新之前检查旧返回，模拟真实下游的采样时刻。
// 当前周期的新地址在前一下降沿后改变，可检出“用当前地址选择旧Q”的错误。
// 只有编译时接入完整官方模型，才能作为官方宏集成证据。
module tb_storage_wrapper;
    parameter real CLK_HALF = 10.0; // 默认周期20ns，只用于功能检查，不代表150MHz验收
    reg clk=0;
    always #(CLK_HALF) clk=~clk;
    reg rst_n=0;
    reg [`KWT_X_BANK_COUNT-1:0] x_rd_en=0, x_wr_en=0;
    reg [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] x_addr=0;
    reg [`KWT_X_BANK_COUNT*`KWT_X_WIDTH-1:0] x_wr_data=0;
    wire [`KWT_X_BANK_COUNT*`KWT_X_WIDTH-1:0] x_rd_data;
    wire [`KWT_X_BANK_COUNT-1:0] x_rd_valid, x_access_error;
    reg [`KWT_W_BANK_COUNT-1:0] w_rd_en=0, w_wr_en=0;
    reg [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] w_addr=0;
    reg [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0] w_wr_data=0;
    wire [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0] w_rd_data;
    wire [`KWT_W_BANK_COUNT-1:0] w_rd_valid, w_access_error;
    reg bias_wr_en=0, bias_wr_slot=0, bias_rd_slot=0;
    reg [`KWT_BIAS_ADDR_WIDTH-1:0] bias_wr_addr=0, bias_rd_addr=0;
    reg signed [`KWT_BIAS_WIDTH-1:0] bias_wr_data=0;
    wire signed [`KWT_BIAS_WIDTH-1:0] bias_rd_data;
    kwt_storage_wrapper dut(.*);

    // 独立逻辑地址空间，不使用DUT内部SRAM数组或返回选择位计算期望。
    reg [15:0] golden_x[0:6399], golden_w[0:2047];
    reg known_x[0:6399], known_w[0:2047];
    reg [31:0] golden_bias[0:31]; reg known_bias[0:31];
    reg [3:0] pending_x=0, next_x_error=0;
    reg [7:0] pending_w=0, next_w_error=0;
    reg [15:0] pending_x_data[0:3], pending_w_data[0:7];
    integer pending_x_addr[0:3], pending_w_addr[0:7];
    reg [7:0] expected_x_cen, expected_x_gwen;
    reg [15:0] expected_w_cen, expected_w_gwen;
    reg [127:0] expected_x_wen;
    reg [255:0] expected_w_wen;
    integer cycles=0, x_writes=0, w_writes=0, x_reads=0, w_reads=0;
    integer x_returns=0, w_returns=0, x_errors=0, w_errors=0, canceled=0;
    integer bias_writes=0, bias_checks=0, resets=0, parallel_rw_cycles=0;
    integer trace_fd=0, mb, ma, mi, mid, mpart, bc;
    integer i,b,j,mode,init_index;
    reg bad;
    reg [31:0] rng=32'h20261029;
    reg [4095:0] trace_path,vcd_path;

    task fail;
        input [1023:0] reason;
        begin $display("FAIL STORAGE_WRAPPER cycle=%0d: %0s",cycles,reason);$fatal(1);end
    endtask
    function [31:0] advance;
        input [31:0] state;
        reg [31:0] value;
        begin value=state^(state<<13);value=value^(value>>17);advance=value^(value<<5);end
    endfunction
    function [15:0] pattern;
        input integer bank,address,kind;
        begin pattern=(address^(address<<3))^((bank+1)*16'h1357)^(kind*16'h6b29);end
    endfunction

    // 返回检查和当前请求建账分开；复位取消待返回事务，但保留黄金存储内容。
    always @(posedge clk) begin
        cycles=cycles+1;
        if(cycles>30000)fail("timeout");
        if(rst_n)begin
            if(x_rd_valid!==pending_x || w_rd_valid!==pending_w)fail("L1 valid mismatch before edge");
            if(x_access_error!==next_x_error || w_access_error!==next_w_error)fail("error flag mismatch");
            for(mb=0;mb<4;mb=mb+1)if(pending_x[mb])begin
                if(x_rd_data[mb*16+:16]!==pending_x_data[mb])begin
                    $display("X bank=%0d addr=%0d got=%h expected=%h",mb,pending_x_addr[mb],x_rd_data[mb*16+:16],pending_x_data[mb]);
                    fail("X data/return selection mismatch");
                end
                x_returns=x_returns+1;
                if(trace_fd)$fdisplay(trace_fd,"XR %0d %0d %0d %h",cycles,mb,pending_x_addr[mb],x_rd_data[mb*16+:16]);
            end
            for(mb=0;mb<8;mb=mb+1)if(pending_w[mb])begin
                if(w_rd_data[mb*16+:16]!==pending_w_data[mb])begin
                    $display("W bank=%0d addr=%0d got=%h expected=%h",mb,pending_w_addr[mb],w_rd_data[mb*16+:16],pending_w_data[mb]);
                    fail("W data/slot/return selection mismatch");
                end
                w_returns=w_returns+1;
                if(trace_fd)$fdisplay(trace_fd,"WR %0d %0d %0d %h",cycles,mb,pending_w_addr[mb],w_rd_data[mb*16+:16]);
            end
        end else begin
            resets=resets+1;
            for(mb=0;mb<4;mb=mb+1)if(pending_x[mb])canceled=canceled+1;
            for(mb=0;mb<8;mb=mb+1)if(pending_w[mb])canceled=canceled+1;
        end

        pending_x=0;pending_w=0;next_x_error=0;next_w_error=0;
        expected_x_cen='1;expected_x_gwen='1;expected_x_wen='1;
        expected_w_cen='1;expected_w_gwen='1;expected_w_wen='1;
        if(rst_n)begin
            if((|w_rd_en)&&(|w_wr_en))parallel_rw_cycles=parallel_rw_cycles+1;
            for(mb=0;mb<4;mb=mb+1)begin
                ma=x_addr[mb*11+:11];mi=mb*1600+ma;
                bad=(x_rd_en[mb]&&x_wr_en[mb])||((x_rd_en[mb]||x_wr_en[mb])&&ma>=1600);
                next_x_error[mb]=bad;
                if(bad)x_errors=x_errors+1;
                else if(x_rd_en[mb]||x_wr_en[mb])begin
                    // 用除法/余数独立描述物理映射，与DUT的地址位切片交叉核对。
                    mpart=ma/1024;mid=mb*2+mpart;
                    expected_x_cen[mid]=0;
                    if(dut.u_storage.x_a[mid*10+:10]!==ma%1024)fail("X physical address");
                    if(x_wr_en[mb])begin
                        expected_x_gwen[mid]=0;expected_x_wen[mid*16+:16]=0;
                        golden_x[mi]=x_wr_data[mb*16+:16];known_x[mi]=1;x_writes=x_writes+1;
                        if(trace_fd)$fdisplay(trace_fd,"XW %0d %0d %0d %h",cycles,mb,ma,golden_x[mi]);
                    end else begin
                        if(!known_x[mi])fail("TB read unwritten X");
                        pending_x[mb]=1;pending_x_data[mb]=golden_x[mi];pending_x_addr[mb]=ma;x_reads=x_reads+1;
                    end
                end
            end
            for(mb=0;mb<8;mb=mb+1)begin
                ma=w_addr[mb*8+:8];mi=mb*256+ma;
                bad=w_rd_en[mb]&&w_wr_en[mb];next_w_error[mb]=bad;
                if(bad)w_errors=w_errors+1;
                else if(w_rd_en[mb]||w_wr_en[mb])begin
                    mpart=ma/128;mid=mb*2+mpart;expected_w_cen[mid]=0;
                    if(dut.u_storage.w_a[mid*7+:7]!==ma%128)fail("W physical address");
                    if(w_wr_en[mb])begin
                        expected_w_gwen[mid]=0;expected_w_wen[mid*16+:16]=0;
                        golden_w[mi]=w_wr_data[mb*16+:16];known_w[mi]=1;w_writes=w_writes+1;
                        if(trace_fd)$fdisplay(trace_fd,"WW %0d %0d %0d %h",cycles,mb,ma,golden_w[mi]);
                    end else begin
                        if(!known_w[mi])fail("TB read unwritten W");
                        pending_w[mb]=1;pending_w_data[mb]=golden_w[mi];pending_w_addr[mb]=ma;w_reads=w_reads+1;
                    end
                end
            end
            if(bias_wr_en)begin
                bc=bias_wr_slot*16+bias_wr_addr;
                golden_bias[bc]=bias_wr_data;known_bias[bc]=1;bias_writes=bias_writes+1;
            end
        end
        // 被拒绝请求必须真的没有选通物理宏；仅检查error、不检查使能是不够的。
        if(dut.u_storage.x_cen!==expected_x_cen || dut.u_storage.x_gwen!==expected_x_gwen || dut.u_storage.x_wen!==expected_x_wen)fail("X CEN/GWEN/WEN");
        if(dut.u_storage.w_cen!==expected_w_cen || dut.u_storage.w_gwen!==expected_w_gwen || dut.u_storage.w_wen!==expected_w_wen)fail("W CEN/GWEN/WEN");
        if(dut.u_storage.sram_ema!==3'b000 || dut.u_storage.sram_emaw!==2'b00 || dut.u_storage.sram_ret1n!==1'b1)fail("configuration pins");
        #1;
        if(x_rd_valid!==pending_x || w_rd_valid!==pending_w || x_access_error!==next_x_error || w_access_error!==next_w_error)fail("registered flags after edge");
        bc=bias_rd_slot*16+bias_rd_addr;
        if(known_bias[bc])begin
            if(bias_rd_data!==golden_bias[bc])fail("bias combinational read / same-edge write");
            bias_checks=bias_checks+1;
        end
    end

    // step返回时位于下降沿之后，随后修改请求，避免与DUT上升沿采样竞争。
    task step;begin @(posedge clk);#2;@(negedge clk);#1;end endtask
    task idle;begin x_rd_en=0;x_wr_en=0;w_rd_en=0;w_wr_en=0;bias_wr_en=0;end endtask
    task read_all;
        begin
            idle;
            for(i=0;i<1600;i=i+1)begin
                x_rd_en=4'hf;w_rd_en=i<256?8'hff:0;
                for(b=0;b<4;b=b+1)x_addr[b*11+:11]=i;
                for(b=0;b<8;b=b+1)w_addr[b*8+:8]=i%256;
                bias_rd_slot=(i/16)%2;bias_rd_addr=i%16;step;
            end
            idle;step;step;
        end
    endtask
    initial begin
        if(`KWT_X_BANK_COUNT!=4 || `KWT_W_BANK_COUNT!=8 || `KWT_X_BANK_DEPTH!=1600 || `KWT_W_BANK_DEPTH!=256)fail("unsupported frozen geometry");
        for(init_index=0;init_index<6400;init_index=init_index+1)known_x[init_index]=0;
        for(init_index=0;init_index<2048;init_index=init_index+1)known_w[init_index]=0;
        for(init_index=0;init_index<32;init_index=init_index+1)known_bias[init_index]=0;
        if($value$plusargs("trace=%s",trace_path))begin trace_fd=$fopen(trace_path,"w");if(!trace_fd)fail("trace open");end
        if($value$plusargs("vcd=%s",vcd_path))begin $dumpfile(vcd_path);$dumpvars(0,dut);end
        step;step;rst_n=1;

        // 1. 遍历完整逻辑地址。bank3尾64项在本测试中主动装载，仅验证存储容量，
        //    不表示正式99行矩阵会使用这些位置，也不替代上层尾行mask验证。
        for(i=0;i<1600;i=i+1)begin
            x_wr_en=4'hf;w_wr_en=i<256?8'hff:0;
            for(b=0;b<4;b=b+1)begin x_addr[b*11+:11]=i;x_wr_data[b*16+:16]=pattern(b,i,0);end
            for(b=0;b<8;b=b+1)begin w_addr[b*8+:8]=i%256;w_wr_data[b*16+:16]=pattern(b,i,1);end
            bias_wr_en=i<32;bias_wr_slot=i/16;bias_wr_addr=i%16;bias_rd_slot=bias_wr_slot;bias_rd_addr=bias_wr_addr;
            case(i)
                0:bias_wr_data=32'h80000000;
                1:bias_wr_data=32'h7fffffff;
                2:bias_wr_data=32'hffffffff;
                3:bias_wr_data=0;
                default:bias_wr_data=32'hf13579bd^(i*32'h01020307);
            endcase
            step;
        end
        read_all;

        // 2. 连续交替访问宏分界；新请求地址在旧返回被消费前就已变化。
        for(j=0;j<32;j=j+1)begin
            x_rd_en=4'hf;w_rd_en=8'hff;
            for(b=0;b<4;b=b+1)x_addr[b*11+:11]=(j+b)%2?1024:1023;
            for(b=0;b<8;b=b+1)w_addr[b*8+:8]=(j+b)%2?128:127;
            step;
        end
        idle;step;

        // 3. 不同W槽并行读写，再交换；验证两槽不会别名或相互覆盖。
        for(j=0;j<64;j=j+1)begin
            w_rd_en=j%2?8'hf0:8'h0f;w_wr_en=~w_rd_en;
            x_rd_en=j%2?4'b0101:4'b1010;x_wr_en=~x_rd_en;
            for(b=0;b<4;b=b+1)begin x_addr[b*11+:11]=(j*29+b*131)%1600;x_wr_data[b*16+:16]=pattern(b,j,2);end
            for(b=0;b<8;b=b+1)begin w_addr[b*8+:8]=(j*17+b*31)%256;w_wr_data[b*16+:16]=pattern(b,j,3);end
            step;
        end
        idle;step;

        // 4. 同bank读写冲突，以及X所有448个越界地址。非法访问不能改变存储。
        x_rd_en=4'hf;x_wr_en=4'hf;w_rd_en=8'hff;w_wr_en=8'hff;step;
        idle;step;
        for(i=1600;i<2048;i=i+1)begin
            x_rd_en=i%2?4'hf:0;x_wr_en=i%2?0:4'hf;
            for(b=0;b<4;b=b+1)begin x_addr[b*11+:11]=i;x_wr_data[b*16+:16]=16'hdead;end
            step;
        end
        idle;step;step;

        // 5. 有返回在途时复位；带着写使能复位也不能误写已有数据。
        x_rd_en=4'hf;w_rd_en=8'hff;x_addr=0;w_addr=0;step;
        rst_n=0;x_wr_en=4'hf;w_wr_en=8'hff;x_wr_data='1;w_wr_data='1;
        bias_wr_en=1;bias_wr_slot=0;bias_wr_addr=0;bias_wr_data=32'hdeadbeef;
        step;step;idle;rst_n=1;step;

        // 6. 以接口方式演示尾行屏蔽：bank3不发读，故其valid必须为0。
        x_rd_en=4'b0111;x_addr=0;step;idle;step;

        // 7. 固定种子随机读写/空拍/冲突/越界及bias同址读写。
        for(j=0;j<4000;j=j+1)begin
            idle;
            for(b=0;b<4;b=b+1)begin
                rng=advance(rng);mode=rng%6;x_addr[b*11+:11]=(rng>>8)%1600;x_wr_data[b*16+:16]=rng[15:0];
                case(mode)
                    1:x_rd_en[b]=1;
                    2:x_wr_en[b]=1;
                    3:begin x_rd_en[b]=1;x_wr_en[b]=1;end
                    4:begin x_rd_en[b]=1;x_addr[b*11+:11]=1600+(rng%448);end
                    5:begin x_wr_en[b]=1;x_addr[b*11+:11]=1600+(rng%448);end
                    default:begin end
                endcase
            end
            for(b=0;b<8;b=b+1)begin
                rng=advance(rng);mode=rng%4;w_addr[b*8+:8]=rng[15:8];w_wr_data[b*16+:16]=rng[15:0];
                w_rd_en[b]=(mode==1||mode==3);w_wr_en[b]=(mode==2||mode==3);
            end
            rng=advance(rng);bias_wr_en=rng[0];bias_wr_slot=rng[1];bias_wr_addr=rng[5:2];bias_wr_data=rng;
            bias_rd_slot=j%2?bias_wr_slot:rng[6];bias_rd_addr=j%2?bias_wr_addr:rng[10:7];
            rst_n=(j!=123&&j!=2500);step;
        end
        idle;rst_n=1;step;step;read_all;
        for(j=0;j<32;j=j+1)begin bias_rd_slot=j/16;bias_rd_addr=j%16;step;end
        idle;step;step;
        if(x_reads+w_reads!=x_returns+w_returns+canceled)fail("read transaction ledger");
        if(!parallel_rw_cycles||!x_errors||!w_errors||canceled==0)fail("missing directed coverage");
        $display("PASS STORAGE_WRAPPER cycles=%0d x_writes=%0d x_reads=%0d x_returns=%0d w_writes=%0d w_reads=%0d w_returns=%0d x_errors=%0d w_errors=%0d canceled=%0d bias_writes=%0d bias_checks=%0d resets=%0d parallel_rw_cycles=%0d",cycles,x_writes,x_reads,x_returns,w_writes,w_reads,w_returns,x_errors,w_errors,canceled,bias_writes,bias_checks,resets,parallel_rw_cycles);
        if(trace_fd)$fclose(trace_fd);$finish;
    end
endmodule
`default_nettype wire

// Shared binary32 execution interface for the KWT-1 encoder prototype.
// Arithmetic is implemented by Berkeley HardFloat Release 1 (BSD-3-Clause).
// See work/encoder_fp32_contract.md and dv/fp32/README.md.
module encoder_fp32 (
    input wire clk,
    input wire rst_n,
    input wire req_valid,
    output wire req_ready,
    input wire [3:0] req_op,
    input wire [31:0] req_a,
    input wire [31:0] req_b,
    input wire [31:0] req_c,
    output wire rsp_valid,
    input wire rsp_ready,
    output reg [31:0] rsp_data,
    output reg [4:0] rsp_flags,
    output reg rsp_error,
    output wire busy
);
    localparam [1:0] IDLE=2'd0, DIV_WAIT=2'd1, RESPONSE=2'd2;
    // HardFloat control bit 0: detect tininess after rounding.
    localparam CONTROL=1'b1;
    localparam [2:0] ROUND_NEAR_EVEN=3'b000;
    reg [1:0] state;
    wire [32:0] a_rec,b_rec,c_rec;
    wire [32:0] add_rec,mul_rec,fma_rec,div_rec,int_rec;
    wire [31:0] add_data,mul_data,fma_data,div_data,toint_data,fromint_data;
    wire [31:0] add_ieee_raw,mul_ieee_raw,fma_ieee_raw,div_ieee_raw,int_ieee_raw;
    wire [4:0] add_flags,mul_flags,fma_flags,div_flags,fromint_flags;
    wire [2:0] toint_flags;
    wire div_ready,div_valid,div_sqrt;
    wire accept=req_valid && req_ready;
    wire start_div=accept && ((req_op==4'd4) || (req_op==4'd5));
    reg [31:0] fast_data;
    reg [4:0] fast_flags;
    reg fast_error;

    assign req_ready=(state==IDLE);
    assign busy=(state!=IDLE);
    assign rsp_valid=(state==RESPONSE);

    fNToRecFN #(8,24) decode_a(req_a,a_rec);
    fNToRecFN #(8,24) decode_b(req_b,b_rec);
    fNToRecFN #(8,24) decode_c(req_c,c_rec);
    addRecFN #(8,24) add_sub(CONTROL,req_op==4'd1,a_rec,b_rec,
                             ROUND_NEAR_EVEN,add_rec,add_flags);
    mulRecFN #(8,24) multiply(CONTROL,a_rec,b_rec,ROUND_NEAR_EVEN,mul_rec,mul_flags);
    mulAddRecFN #(8,24) fused_multiply_add(CONTROL,2'b00,a_rec,b_rec,c_rec,
                                           ROUND_NEAR_EVEN,fma_rec,fma_flags);
    divSqrtRecFN_small #(8,24,0) divide_sqrt(
        rst_n,clk,CONTROL,div_ready,start_div,req_op==4'd5,a_rec,b_rec,
        ROUND_NEAR_EVEN,div_valid,div_sqrt,div_rec,div_flags);
    recFNToIN #(8,24,32) float_to_integer(CONTROL,a_rec,ROUND_NEAR_EVEN,1'b1,
                                         toint_data,toint_flags);
    iNToRecFN #(32,8,24) integer_to_float(CONTROL,1'b1,req_a,ROUND_NEAR_EVEN,
                                         int_rec,fromint_flags);
    recFNToFN #(8,24) encode_add(add_rec,add_ieee_raw);
    recFNToFN #(8,24) encode_mul(mul_rec,mul_ieee_raw);
    recFNToFN #(8,24) encode_fma(fma_rec,fma_ieee_raw);
    recFNToFN #(8,24) encode_div(div_rec,div_ieee_raw);
    recFNToFN #(8,24) encode_int(int_rec,int_ieee_raw);

    // HardFloat's sequential divider intentionally leaves fields used only
    // by normal results uninitialized on a first special operation. Its
    // recoded class/sign remain valid, while irrelevant exponent/significand
    // bits can be X in four-state simulation. recFNToFN compares the complete
    // exponent, so explicitly decode the three fully known special classes.
    // Use an exact case: unknown class bits must retain X through raw_ieee.
    // This boundary applies only to floating results, never toint_data.
    function [31:0] canonical_ieee;
        input [32:0] recoded;
        input [31:0] raw_ieee;
        begin
            case(recoded[31:29])
                3'b000: canonical_ieee={recoded[32],31'b0};
                3'b110: canonical_ieee={recoded[32],8'hff,23'b0};
                3'b111: canonical_ieee=32'h7fc00000;
                default: canonical_ieee=raw_ieee;
            endcase
        end
    endfunction
    assign add_data=canonical_ieee(add_rec,add_ieee_raw);
    assign mul_data=canonical_ieee(mul_rec,mul_ieee_raw);
    assign fma_data=canonical_ieee(fma_rec,fma_ieee_raw);
    assign div_data=canonical_ieee(div_rec,div_ieee_raw);
    assign fromint_data=canonical_ieee(int_rec,int_ieee_raw);

    always @* begin
        fast_data=32'h7fc00000;
        fast_flags=5'b0;
        fast_error=1'b0;
        case(req_op)
            4'd0,4'd1: begin fast_data=add_data;fast_flags=add_flags;end
            4'd2: begin fast_data=mul_data;fast_flags=mul_flags;end
            4'd3: begin fast_data=fma_data;fast_flags=fma_flags;end
            // Conversion's integer overflow is an IEEE invalid conversion,
            // not a floating-point overflow. Results saturate per RISCV.
            4'd6: begin
                fast_data=toint_data;
                fast_flags={toint_flags[2] | toint_flags[1],3'b000,toint_flags[0]};
            end
            4'd7: begin fast_data=fromint_data;fast_flags=fromint_flags;end
            4'd4,4'd5: begin end
            default: fast_error=1'b1;
        endcase
    end

    always @(posedge clk) begin
        if(!rst_n) begin
            state<=IDLE;
            rsp_data<=32'b0;
            rsp_flags<=5'b0;
            rsp_error<=1'b0;
        end else begin
            case(state)
                IDLE: if(accept) begin
                    if(start_div) begin
                        // div_ready is high whenever this single-outstanding
                        // wrapper is idle: no previous operation remains.
                        state<=DIV_WAIT;
                    end else begin
                        rsp_data<=fast_data;
                        rsp_flags<=fast_flags;
                        rsp_error<=fast_error;
                        state<=RESPONSE;
                    end
                end
                DIV_WAIT: if(div_valid) begin
                    // HardFloat pulses outValid. Buffer the complete result
                    // independently of the consumer's response readiness.
                    rsp_data<=div_data;
                    rsp_flags<=div_flags;
                    rsp_error<=1'b0;
                    state<=RESPONSE;
                end
                RESPONSE: if(rsp_ready) state<=IDLE;
                default: state<=IDLE;
            endcase
        end
    end
endmodule

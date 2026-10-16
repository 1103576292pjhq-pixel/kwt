// Deliberately incorrect protocol-compatible RED fixture. Replaced after RED evidence.
module dot64 (
    input wire clk, rst_n,
    input wire start_valid,
    output wire start_ready,
    input wire signed [47:0] start_bias,
    input wire [5:0] start_shift,
    input wire in_valid,
    output wire in_ready,
    input wire signed [15:0] in_x, in_w,
    output wire out_valid,
    input wire out_ready,
    output wire signed [31:0] out_data,
    output wire signed [47:0] out_raw,
    output wire out_overflow, out_saturated, out_error, busy
);
    reg [1:0] state;
    reg [5:0] count;
    wire unused_inputs = ^{start_bias, start_shift, in_x, in_w};
    assign start_ready = (state == 0);
    assign in_ready = (state == 1);
    assign out_valid = (state == 3);
    assign busy = (state != 0);
    assign out_data = 32'sd0;
    assign out_raw = 48'sd0;
    assign out_overflow = 1'b0;
    assign out_saturated = 1'b0;
    assign out_error = unused_inputs & 1'b0;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin state <= 0; count <= 0; end
        else case (state)
            0: if (start_valid) begin state <= 1; count <= 0; end
            1: if (in_valid) begin
                if (count == 63) state <= 2;
                else count <= count + 1'b1;
            end
            2: state <= 3;
            3: if (out_ready) state <= 0;
            default: state <= 0;
        endcase
    end
endmodule

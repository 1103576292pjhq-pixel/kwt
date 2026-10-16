// Single-MAC dot product with post-dot bias, explicit overflow and RNE output.
// Interface and cycle contract: dv/dot64/README.md.
module dot64 (
    input  wire clk,
    input  wire rst_n,
    input  wire start_valid,
    output wire start_ready,
    input  wire signed [47:0] start_bias,
    input  wire [5:0] start_shift,
    input  wire in_valid,
    output wire in_ready,
    input  wire signed [15:0] in_x,
    input  wire signed [15:0] in_w,
    output wire out_valid,
    input  wire out_ready,
    output reg signed [31:0] out_data,
    output reg signed [47:0] out_raw,
    output reg out_overflow,
    output reg out_saturated,
    output reg out_error,
    output wire busy
);
    localparam [1:0] IDLE = 2'd0, COLLECT = 2'd1,
                     FINALIZE = 2'd2, OUTPUT = 2'd3;
    localparam signed [48:0] MAX48 = 49'sd140737488355327;
    localparam signed [48:0] MIN48 = -49'sd140737488355328;
    localparam signed [48:0] MAX32 = 49'sd2147483647;
    localparam signed [48:0] MIN32 = -49'sd2147483648;

    reg [1:0] state;
    reg [5:0] count;
    reg [5:0] shift;
    reg signed [47:0] bias;
    reg signed [47:0] accumulator;
    wire signed [31:0] product = in_x * in_w;
    wire signed [47:0] product_extended = {{16{product[31]}}, product};
    wire signed [48:0] biased_sum = {accumulator[47], accumulator}
                                     + {bias[47], bias};

    reg signed [47:0] raw_next;
    reg overflow_next;
    reg [48:0] magnitude;
    reg [48:0] quotient;
    reg [48:0] remainder_bits;
    reg [48:0] half;
    reg signed [48:0] rounded;
    reg signed [31:0] data_next;
    reg saturated_next;

    assign start_ready = (state == IDLE);
    assign in_ready = (state == COLLECT);
    assign out_valid = (state == OUTPUT);
    assign busy = (state != IDLE);

    // Signed48 saturation precedes magnitude-based symmetric RNE.
    // Every intermediate has an explicit width, including abs(MIN48).
    always @* begin
        overflow_next = 1'b0;
        if (biased_sum > MAX48) begin
            raw_next = MAX48[47:0];
            overflow_next = 1'b1;
        end else if (biased_sum < MIN48) begin
            raw_next = MIN48[47:0];
            overflow_next = 1'b1;
        end else begin
            raw_next = biased_sum[47:0];
        end

        magnitude = raw_next[47] ? -$signed({raw_next[47], raw_next})
                                  : {1'b0, raw_next};
        quotient = magnitude >> shift;
        remainder_bits = 49'd0;
        half = 49'd0;
        if (shift != 0) begin
            remainder_bits = magnitude & ((49'd1 << shift) - 49'd1);
            half = 49'd1 << (shift - 6'd1);
            if ((remainder_bits > half) ||
                ((remainder_bits == half) && quotient[0]))
                quotient = quotient + 49'd1;
        end
        rounded = raw_next[47] ? -$signed(quotient) : $signed(quotient);
        saturated_next = 1'b0;
        if (rounded > MAX32) begin
            data_next = MAX32[31:0];
            saturated_next = 1'b1;
        end else if (rounded < MIN32) begin
            data_next = MIN32[31:0];
            saturated_next = 1'b1;
        end else begin
            data_next = rounded[31:0];
        end
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state <= IDLE;
            count <= 6'd0;
            shift <= 6'd0;
            bias <= 48'sd0;
            accumulator <= 48'sd0;
            out_data <= 32'sd0;
            out_raw <= 48'sd0;
            out_overflow <= 1'b0;
            out_saturated <= 1'b0;
            out_error <= 1'b0;
        end else begin
            case (state)
                IDLE: if (start_valid) begin
                    accumulator <= 48'sd0;
                    count <= 6'd0;
                    bias <= start_bias;
                    shift <= start_shift;
                    out_error <= 1'b0;
                    if (start_shift > 6'd47) begin
                        out_data <= 32'sd0;
                        out_raw <= 48'sd0;
                        out_overflow <= 1'b0;
                        out_saturated <= 1'b0;
                        out_error <= 1'b1;
                        state <= OUTPUT;
                    end else begin
                        state <= COLLECT;
                    end
                end
                COLLECT: if (in_valid) begin
                    accumulator <= accumulator + product_extended;
                    if (count == 6'd63)
                        state <= FINALIZE;
                    else
                        count <= count + 6'd1;
                end
                FINALIZE: begin
                    out_data <= data_next;
                    out_raw <= raw_next;
                    out_overflow <= overflow_next;
                    out_saturated <= saturated_next;
                    state <= OUTPUT;
                end
                OUTPUT: if (out_ready) state <= IDLE;
                default: state <= IDLE;
            endcase
        end
    end
endmodule

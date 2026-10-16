module child(input signed [15:0] x); endmodule
module top(input [15:0] x); child u(.x($signed(x))); endmodule

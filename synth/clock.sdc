# Clock target only. This is not a complete platform timing constraint set.
# Add actual input/output delays, loads, clock uncertainty and macro corners
# for the chosen platform before making any formal timing claim.
create_clock -name clk -period 6.666667 [get_ports clk]

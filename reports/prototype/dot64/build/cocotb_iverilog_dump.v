module cocotb_iverilog_dump();
initial begin
    string dumpfile_path;    if ($value$plusargs("dumpfile_path=%s", dumpfile_path)) begin
        $dumpfile(dumpfile_path);
    end else begin
        $dumpfile("/mnt/c/Users/11035/Desktop/ic/kwt—1/reports/prototype/dot64/build/dot64.fst");
    end
    $dumpvars(0, dot64);
end
endmodule

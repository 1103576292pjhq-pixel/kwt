from prepare_soc import BUS
def fixture():
    declarations=['input kwt_bus_clk,kwt_bus_rst_n']
    for prefix in ['sysper_icb','sysmem_icb']:
        for name in BUS:
            direction='output' if name in ['cmd_ready','rsp_valid','rsp_rdata','rsp_err'] else 'input'
            width='[31:0] ' if name in ['cmd_addr','cmd_wdata','rsp_rdata'] else ('[3:0] ' if name=='cmd_wmask' else '')
            declarations.append(direction+' '+width+prefix+'_'+name)
    text='module kwt_shared_soc_top('+',\n'.join(declarations)+');\n'
    for module,instance,prefix in [('kwt_accelerator','u_kwt_accelerator','sysper_icb'),('kwt_shared_sram','u_shared_sram','sysmem_icb')]:
        ports=['.clk(kwt_bus_clk)','.rst_n(kwt_bus_rst_n)']+['.icb_'+name+'('+prefix+'_'+name+')' for name in BUS]
        if module=='kwt_accelerator':ports+=['.external_abort_req(1\'b0)','.busy()','.compute_done()','.task_done()','.fault()','.error_code()','.abort_pending()','.abort_done()']
        text+=module+" #(.SRAM_EMA(3'd2)) "+instance+'('+',\n'.join(ports)+');\n'
    return text+'endmodule\n'

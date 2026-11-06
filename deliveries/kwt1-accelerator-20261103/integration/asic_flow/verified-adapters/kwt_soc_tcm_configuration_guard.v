`include "e203_defines.v"
module kwt_soc_tcm_configuration_guard;
`ifndef E203_HAS_ITCM
  KWT_TCM_REQUIRES_EXISTING_ITCM bad_itcm();
`endif
`ifndef E203_HAS_DTCM
  KWT_TCM_REQUIRES_EXISTING_DTCM bad_dtcm();
`endif
`ifdef E203_HAS_ECC
  KWT_TCM_ECC_CONFIGURATION_NEEDS_REVIEW bad_ecc();
`endif
generate
 if (`E203_ITCM_RAM_AW != 15 || `E203_ITCM_RAM_DW != 64 || `E203_ITCM_RAM_MW != 8 ||
     `E203_ITCM_RAM_DP != 32768) begin : invalid_itcm
   KWT_TCM_ITCM_CONFIGURATION_MISMATCH stop();
 end
 if (`E203_DTCM_RAM_AW != 16 || `E203_DTCM_RAM_DW != 32 || `E203_DTCM_RAM_MW != 4 ||
     `E203_DTCM_RAM_DP != 65536) begin : invalid_dtcm
   KWT_TCM_DTCM_CONFIGURATION_MISMATCH stop();
 end
endgenerate
endmodule

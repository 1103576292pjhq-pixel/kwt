# Source this file in the synthesis tool. It reads the canonical RTL file list.
# Technology libraries and I/O timing constraints are supplied by the integrator.
set ffn_v07_root [file normalize [file join [file dirname [info script]] ..]]
set ffn_v07_top accelerator_top
set ffn_v07_defines {SYNTHESIS}
set ffn_v07_parameters {M=99 N=256 READ_LATENCY=1 USE_MACRO=1}
set ffn_v07_include_dirs {}
set ffn_v07_sources {}
set ffn_v07_list [open [file join $ffn_v07_root synth rtl.f] r]
while {[gets $ffn_v07_list ffn_v07_line] >= 0} {
    set ffn_v07_line [string trim $ffn_v07_line]
    if {$ffn_v07_line eq "" || [string match "#*" $ffn_v07_line]} {continue}
    if {[string match "+incdir+*" $ffn_v07_line]} {
        lappend ffn_v07_include_dirs [file join $ffn_v07_root [string range $ffn_v07_line 8 end]]
    } else {
        set ffn_v07_source [file join $ffn_v07_root $ffn_v07_line]
        if {![file isfile $ffn_v07_source]} {error "Missing RTL: $ffn_v07_source"}
        lappend ffn_v07_sources $ffn_v07_source
    }
}
close $ffn_v07_list
puts "FFN V07: $ffn_v07_top, [llength $ffn_v07_sources] RTL files"

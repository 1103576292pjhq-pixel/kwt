# =============================================================================
# accelerator_top -- Synopsys Design Compiler, logical/non-topographical flow.
# Based on the uploaded flow(4).tcl and kwt standalone FFN V07.
# Reference revision: 78f63dec27f6cf3d5853ffcbc54a2d1dd98cd9b9 (not a local hash check).
# Install as <project>/scr/flow.tcl; keep the new branch's rtl/ and synth/ trees.
# Fresh dc_shell: source /absolute/project/scr/flow.tcl
# Does NOT exit dc_shell. See README for a batch command with a reliable exit code.
# =============================================================================
set FLOW_FILE [file normalize [info script]]
set script_dir [file dirname $FLOW_FILE]
set project_dir [file dirname $script_dir]

# --------------------------- USER CONFIGURATION ------------------------------
set DESIGN_TOP accelerator_top
set SDC_FILE [file join $project_dir sdc accelerator_top.sdc]
set SOURCE_SETUP [file join $project_dir synth sources.tcl]

# 保留你上传文件中的标准单元路径。以服务器真实文件名为准，不猜测另一种拼写。
set STD_CELL_DB "/home/EDA/Desktop/ffn1_icb/library/tcbn28hpcplusbwp7t40p140_180a/tcbn28hpcplusbwp7t40p140tt0p9v25c.db"
set SRAM_DB "/home/EDA/Desktop/ffn1_icb/library/TS1N28HPCPL2LVTB2048X32M4MWBASO_tt0p9v25c.db"                    ;# 必填：下述 SRAM cell 对应的真实 .db。
set EXTRA_LINK_DB_LIST [list]      ;# 其他确实被实例化的 IP 库；通常留空。
set SRAM_REF TS1N28HPCPL2LVTB2048X32M4MWBASO
set EXPECTED_SRAM_COUNT 12

set FFN_M 99
set FFN_N 256
set FFN_READ_LATENCY 1
# 本 Flow 专门用于 ASIC 宏综合，强制 USE_MACRO=1，防止意外综合行为 RAM。
set USE_COMPILE_ULTRA 1            ;# 无 DC Ultra 许可时设 0，不自动静默降级。
set ENABLE_HOOKS 0                 ;# 默认不执行 hook/ 中可能残留的旧 dot64 脚本。
set HOOK_DIR [file join $project_dir hook]
set POWER_SAIF ""                 ;# 可选，用于综合后的功耗估计，不据此优化功耗。
set POWER_SAIF_INSTANCE ""        ;# 非空 SAIF 时填写，如 tb_accelerator/dut。

# 逻辑综合可选 WLM。留空使用 DC/库默认选择，并在 report_design 中记录结果。
# 没有适合的 WLM 时不要编造一个；无布局寄生的结果仅作为初步估计。
set WIRE_LOAD_MODEL ""
set WIRE_LOAD_LIBRARY ""          ;# Liberty 内部 library 名，非文件路径。
set WIRE_LOAD_MODE ""             ;# 空 / top / enclosed / segmented。

# 环境变量覆盖；所有相对路径均相对 project_dir，与启动目录无关。
foreach {_env _var} {
    FFN_STD_CELL_DB STD_CELL_DB
    FFN_SRAM_DB SRAM_DB
    FFN_USE_COMPILE_ULTRA USE_COMPILE_ULTRA
    FFN_M FFN_M
    FFN_N FFN_N
    FFN_READ_LATENCY FFN_READ_LATENCY
    FFN_POWER_SAIF POWER_SAIF
    FFN_POWER_SAIF_INSTANCE POWER_SAIF_INSTANCE
} {
    if {[info exists env($_env)]} {set $_var $env($_env)}
}
# 时钟/I-O/单位配置见 sdc/accelerator_top.sdc；不 source synth/clock.sdc。
# ------------------------- END USER CONFIGURATION ----------------------------

proc ffn_path {path} {
    if {$path eq ""} {return ""}
    return [file normalize [file join $::project_dir $path]]
}
proc ffn_require_file {path description} {
    if {$path eq "" || ![file isfile $path] || ![file readable $path]} {
        error "Missing/unreadable $description: '$path'"
    }
}
# 仅对明确返回成功/失败状态的命令使用本包装。report/check_timing 不套此判断。
proc ffn_checked {label command} {
    if {[catch {uplevel 1 $command} value]} {error "$label failed: $value"}
    if {$value eq "0"} {error "$label returned failure; inspect dc_run.log"}
    return $value
}
proc ffn_report {filename command} {
    set result [uplevel 1 [list redirect -file [file join $::report_dir $filename] $command]]
    # check_timing 的诊断结果不是工具执行状态；不能把时序问题当作 Tcl 异常。
    if {$result eq "0" && [string first "check_timing" $command] < 0} {
        error "Report command returned failure: $filename; inspect the report/log"
    }
    return $result
}
proc ffn_optional_report {filename command} {
    if {[catch {uplevel 1 [list ffn_report $filename $command]} message]} {
        puts "WARNING: optional report $filename unavailable: $message"
        set f [open [file join $::report_dir ${filename}.unavailable.txt] w]
        puts $f $message
        close $f
    }
}
proc ffn_status {state detail} {
    set ::FFN_RUN_STATUS $state
    set f [open [file join $::report_dir status.rpt] w]
    puts $f "status=$state"
    puts $f "stage=$::FFN_STAGE"
    puts $f "detail=$detail"
    puts $f "output_dir=$::output_dir"
    puts $f "report_dir=$::report_dir"
    puts $f "timing_signoff=NOT_ASSESSED"
    close $f
}
proc ffn_check_macros {tag} {
    set cells [get_cells -quiet -hierarchical -filter "ref_name == $::SRAM_REF"]
    set n [sizeof_collection $cells]
    set f [open [file join $::report_dir ${tag}_sram_instances.rpt] w]
    puts $f "reference=$::SRAM_REF expected=$::EXPECTED_SRAM_COUNT actual=$n"
    foreach_in_collection c $cells {puts $f [get_object_name $c]}
    close $f
    if {$n != $::EXPECTED_SRAM_COUNT} {
        error "SRAM count $n != $::EXPECTED_SRAM_COUNT; check USE_MACRO/RTL/optimization"
    }
    # 一次只链接一个 mapping corner，拒绝同名 SRAM cell 的歧义定义。
    set libcells [get_lib_cells -quiet */$::SRAM_REF]
    if {[sizeof_collection $libcells] != 1} {
        error "Expected exactly one library cell */$::SRAM_REF; check SRAM_DB/corner"
    }
    # get_lib_cells -of_objects 验证实例实际引用库单元，而非未解析的 RTL 占位。
    foreach_in_collection c $cells {
        if {[sizeof_collection [get_lib_cells -quiet -of_objects $c]] != 1} {
            error "SRAM instance has no unique library binding: [get_object_name $c]"
        }
    }
    return $cells
}
proc ffn_snapshot {path} {
    set prefix "${::project_dir}/"
    if {[string first $prefix $path] != 0} {
        error "Snapshot expects a project-local source file: $path"
    }
    set relative [string range $path [string length $prefix] end]
    set dest [file join $::output_dir inputs $relative]
    file mkdir [file dirname $dest]
    file copy -force $path $dest
    return $dest
}
proc ffn_hook {name} {
    if {!$::ENABLE_HOOKS} {return}
    set path [file join $::HOOK_DIR $name]
    if {[file isfile $path]} {
        ffn_snapshot $path
        puts "INFO: source hook $path"
        uplevel #0 [list source $path]
    }
}

set RUN_ID "[clock format [clock seconds] -format %Y%m%d_%H%M%S]_[pid]"
set report_dir [file join $project_dir rpt dc $DESIGN_TOP $RUN_ID]
set output_dir [file join $project_dir work outputs dc $DESIGN_TOP $RUN_ID]
set work_dir [file join $project_dir work dc $DESIGN_TOP $RUN_ID]
if {[file exists $report_dir] || [file exists $output_dir] || [file exists $work_dir]} {
    error "Run directory already exists; use a fresh session/run"
}
foreach _dir [list $report_dir $output_dir [file join $work_dir WORK]] {file mkdir $_dir}
set FFN_STAGE preflight
set _ffn_svf_open 0
set _ffn_design_ready 0
set _ffn_start_dir [pwd]
ffn_status RUNNING "Starting synthesis"

# 在全局作用域执行，便于 source 后查看设计、集合和配置变量。
proc ffn_run {} {uplevel #0 {
    puts "INFO: project=$project_dir"
    puts "INFO: reports=$report_dir"
    puts "INFO: outputs=$output_dir"
    puts "INFO: Tcl version=[info patchlevel]"
    if {[info exists sh_product_version]} {puts "INFO: DC=$sh_product_version"}
    foreach _cmd {
        set_app_var analyze elaborate current_design get_designs sizeof_collection
        define_design_lib link check_design redirect set_svf rename_design
        get_cells get_lib_cells get_libs get_pins get_attribute get_object_name
        foreach_in_collection filter_collection remove_from_collection
        all_registers all_inputs all_outputs all_clocks get_ports get_clocks
        create_clock set_clock_uncertainty set_clock_transition set_input_delay
        set_output_delay set_input_transition set_load set_fix_multiple_port_nets
        change_names write write_sdc report_units report_design report_lib list_libs
        check_timing report_clock report_port report_qor report_area
        report_reference report_constraint report_timing
    } {
        if {[llength [info commands $_cmd]] == 0} {
            error "Missing DC command $_cmd. Run in supported Synopsys dc_shell, not plain Tcl"
        }
    }
    if {[sizeof_collection [get_designs -quiet *]] > 0} {
        error "Designs already loaded. Start a fresh DC session; existing designs will not be deleted"
    }
    if {[llength [info commands shell_is_in_topographical_mode]] > 0 &&
        [shell_is_in_topographical_mode]} {
        error "This flow configures logical synthesis only; use non-topographical dc_shell"
    }
    foreach _v {USE_COMPILE_ULTRA ENABLE_HOOKS} {
        if {![string is boolean -strict [set $_v]]} {error "$_v must be Boolean"}
    }
    foreach _v {FFN_M FFN_N FFN_READ_LATENCY} {
        if {![string is integer -strict [set $_v]]} {error "$_v must be an integer"}
    }
    if {$FFN_M < 1 || $FFN_M > 99 || $FFN_N < 16 || $FFN_N > 256 || $FFN_N % 16 != 0} {
        error "Supported dimensions: M=1..99, N=16..256 and N divisible by 16"
    }
    if {$FFN_READ_LATENCY != 1 && $FFN_READ_LATENCY != 2} {
        error "FFN_READ_LATENCY must be 1 or 2"
    }
    set _compile_cmd compile
    if {$USE_COMPILE_ULTRA} {set _compile_cmd compile_ultra}
    if {[llength [info commands $_compile_cmd]] == 0} {error "Missing command $_compile_cmd"}
    foreach _v {SDC_FILE SOURCE_SETUP STD_CELL_DB SRAM_DB HOOK_DIR POWER_SAIF} {
        set $_v [ffn_path [set $_v]]
    }
    ffn_require_file $SDC_FILE SDC
    ffn_require_file $SOURCE_SETUP "canonical synth/sources.tcl"
    ffn_require_file $STD_CELL_DB "standard-cell .db (FFN_STD_CELL_DB)"
    ffn_require_file $SRAM_DB "SRAM .db (set SRAM_DB or FFN_SRAM_DB)"
    set _extra [list]
    foreach _lib $EXTRA_LINK_DB_LIST {lappend _extra [ffn_path $_lib]}
    set EXTRA_LINK_DB_LIST $_extra
    set LIB_DB_FILES [concat [list $STD_CELL_DB $SRAM_DB] $EXTRA_LINK_DB_LIST]
    foreach _lib $LIB_DB_FILES {
        ffn_require_file $_lib "compiled library"
        if {[string tolower [file extension $_lib]] ne ".db"} {
            error "Expected compiled .db, not .lib/.v: $_lib"
        }
    }
    if {$POWER_SAIF ne ""} {
        ffn_require_file $POWER_SAIF SAIF
        if {$POWER_SAIF_INSTANCE eq ""} {error "Set POWER_SAIF_INSTANCE for the selected SAIF scope"}
    }
    if {$WIRE_LOAD_MODE ne "" && [lsearch -exact {top enclosed segmented} $WIRE_LOAD_MODE] < 0} {
        error "Invalid WIRE_LOAD_MODE: $WIRE_LOAD_MODE"
    }
    if {$WIRE_LOAD_MODEL ne "" && $WIRE_LOAD_LIBRARY eq ""} {
        error "Explicit WIRE_LOAD_MODEL also requires its internal WIRE_LOAD_LIBRARY name"
    }

    source $SOURCE_SETUP
    if {$ffn_v07_top ne $DESIGN_TOP || [llength $ffn_v07_sources] != 12} {
        error "Canonical top/source count changed; review this flow against the new RTL revision"
    }
    set RTL_FILES $ffn_v07_sources
    set RTL_INCLUDE_DIRS $ffn_v07_include_dirs
    set RTL_DEFINES $ffn_v07_defines
    if {[lsearch -exact $RTL_DEFINES SYNTHESIS] < 0} {error "Canonical defines must include SYNTHESIS"}
    set RTL_PARAMETERS [list M=$FFN_M N=$FFN_N READ_LATENCY=$FFN_READ_LATENCY USE_MACRO=1]
    set RTL_HEADER [file join $project_dir rtl include kwt_numeric_config.vh]
    ffn_require_file $RTL_HEADER "numeric-format header"
    foreach _rtl $RTL_FILES {ffn_require_file $_rtl RTL}
    foreach _dir $RTL_INCLUDE_DIRS {
        if {![file isdirectory $_dir]} {error "Missing include directory: $_dir"}
    }
    puts "INFO: top=$DESIGN_TOP parameters=$RTL_PARAMETERS defines=$RTL_DEFINES"
    puts "WARNING: Check standard-cell/SRAM process option, voltage and PVT consistency."

    # 快照读取的源码和头文件；不把商业库复制进输出目录。
    set REF_RTL_FILES [list]
    foreach _rtl $RTL_FILES {lappend REF_RTL_FILES [ffn_snapshot $_rtl]}
    foreach _path [list $FLOW_FILE $SDC_FILE $SOURCE_SETUP $RTL_HEADER \
        [file join $project_dir synth rtl.f]] {ffn_snapshot $_path}
    set REF_INCLUDE_DIRS [list [file join $output_dir inputs rtl include]]
    set SVF_FILE [file join $output_dir ${DESIGN_TOP}.svf]
    set IMPL_NETLIST [file join $output_dir ${DESIGN_TOP}_mapped.v]
    set _manifest [open [file join $output_dir run_inputs.tcl] w]
    puts $_manifest "# Data manifest for this run; no synthesis/Formality commands."
    foreach _v {DESIGN_TOP REF_RTL_FILES REF_INCLUDE_DIRS RTL_DEFINES RTL_PARAMETERS LIB_DB_FILES SVF_FILE IMPL_NETLIST} {
        puts $_manifest [list set $_v [set $_v]]
    }
    close $_manifest

    set _lib_dirs [list]
    foreach _lib $LIB_DB_FILES {lappend _lib_dirs [file dirname $_lib]}
    # 必须在 cd 前解析用户已有的相对 search_path，保留 DC/DesignWare 默认路径。
    set _original_search [list]
    foreach _dir $search_path {
        lappend _original_search [file normalize [file join $_ffn_start_dir $_dir]]
    }
    set_app_var search_path [concat [list $project_dir $script_dir] \
        $RTL_INCLUDE_DIRS $_lib_dirs $_original_search]
    set_app_var target_library [list $STD_CELL_DB]
    if {$USE_COMPILE_ULTRA} {set_app_var synthetic_library [list dw_foundation.sldb]}
    set_app_var link_library [concat [list "*"] [list $STD_CELL_DB $SRAM_DB] \
        $EXTRA_LINK_DB_LIST $synthetic_library]
    cd $work_dir
    ffn_optional_report 00_command_help.rpt {
        foreach _c {analyze elaborate rename_design compile compile_ultra report_timing} {
            if {[llength [info commands $_c]] > 0} {help -verbose $_c}
        }
    }

    # SVF 从 analyze 前开启，覆盖 elaboration、compile 和改名，导出后关闭。
    ffn_checked set_svf [list set_svf $SVF_FILE]
    set _ffn_svf_open 1
    ffn_checked define_work [list define_design_lib WORK -path [file join $work_dir WORK]]
    set FFN_STAGE analyze
    ffn_checked analyze [list analyze -format sverilog -define $RTL_DEFINES $RTL_FILES]
    set FFN_STAGE elaborate
    ffn_checked elaborate [list elaborate $DESIGN_TOP -parameters [join $RTL_PARAMETERS ,]]
    set _elaborated_top [get_object_name [current_design]]
    if {$_elaborated_top eq ""} {error "Elaboration did not select a current design"}
    set _ffn_design_ready 1
    # 参数化 elaboration 在部分版本产生带参数后缀的设计名，导出前统一顶层名。
    if {$_elaborated_top ne $DESIGN_TOP} {
        if {[sizeof_collection [get_designs -quiet $DESIGN_TOP]] != 0} {
            error "Cannot rename elaborated top: $DESIGN_TOP already exists"
        }
        ffn_checked rename_top [list rename_design $_elaborated_top $DESIGN_TOP]
    }
    current_design $DESIGN_TOP
    set FFN_STAGE link
    ffn_checked link [list link]
    ffn_report 00_check_design_pre.rpt {set _design_ok [check_design]}
    if {$_design_ok eq "0"} {error "Pre-compile check_design failed"}
    set _sram_pre [ffn_check_macros 00]
    ffn_report 00_units.rpt {report_units}
    ffn_report 00_libraries.rpt {
        list_libs
        foreach_in_collection _lib [get_libs *] {report_lib [get_object_name $_lib]}
    }
    ffn_report 00_references_pre.rpt {report_reference -hierarchy}
    ffn_optional_report 00_resources_pre.rpt {report_resources -hierarchy}

    set FFN_STAGE constraints
    if {$WIRE_LOAD_MODEL ne ""} {
        ffn_checked wire_load [list set_wire_load_model -name $WIRE_LOAD_MODEL -library $WIRE_LOAD_LIBRARY]
    }
    if {$WIRE_LOAD_MODE ne ""} {set_wire_load_mode $WIRE_LOAD_MODE}
    source $SDC_FILE
    ffn_hook ffn_pre_compile.tcl
    if {[sizeof_collection [all_clocks]] != 1} {error "Expected exactly one functional clock"}
    ffn_report 01_check_timing_pre.rpt {check_timing}
    ffn_report 01_clock.rpt {report_clock}
    ffn_report 01_ports.rpt {report_port -verbose}
    ffn_report 01_design_environment.rpt {report_design}
    ffn_checked precompile_checkpoint [list write -format ddc -hierarchy \
        -output [file join $output_dir ${DESIGN_TOP}_elaborated.ddc]]
    set _cfg [open [file join $report_dir run_config.rpt] w]
    puts $_cfg "flow_reference_revision=78f63dec27f6cf3d5853ffcbc54a2d1dd98cd9b9; actual inputs are snapshotted"
    puts $_cfg "stage=logical synthesis; ideal clock; no extracted physical parasitics"
    foreach _v {DESIGN_TOP RTL_FILES RTL_HEADER RTL_INCLUDE_DIRS RTL_DEFINES RTL_PARAMETERS
        STD_CELL_DB SRAM_DB EXTRA_LINK_DB_LIST USE_COMPILE_ULTRA ENABLE_HOOKS
        WIRE_LOAD_MODEL WIRE_LOAD_LIBRARY WIRE_LOAD_MODE POWER_SAIF POWER_SAIF_INSTANCE} {
        puts $_cfg "$_v=[set $_v]"
    }
    foreach _v [lsort [info globals SYNTH_*]] {puts $_cfg "$_v=[set $_v]"}
    close $_cfg

    set FFN_STAGE compile
    set_fix_multiple_port_nets -all -buffer_constants [get_designs $DESIGN_TOP]
    puts "INFO: $_compile_cmd at ${SYNTH_FREQUENCY_MHZ} MHz; no explicit retiming or clock gating."
    ffn_checked $_compile_cmd [list $_compile_cmd]
    ffn_hook ffn_post_compile.tcl
    ffn_checked change_names [list change_names -rules verilog -hierarchy]
    current_design $DESIGN_TOP
    set FFN_STAGE post_compile_checks
    ffn_checked post_compile_link [list link]
    ffn_report check_design.rpt {set _design_ok [check_design]}
    if {$_design_ok eq "0"} {error "Post-compile check_design failed"}
    set _sram_cells [ffn_check_macros mapped]
    set _unmapped [get_cells -quiet -hierarchical -filter {is_unmapped == true}]
    if {[sizeof_collection $_unmapped] > 0} {
        error "Unmapped cells remain: [get_object_name $_unmapped]"
    }
    # 只检查宏外部逻辑，不把 SRAM 内部存储实现归为 RTL latch。
    set _latches [remove_from_collection [all_registers -level_sensitive] $_sram_cells]
    if {[sizeof_collection $_latches] > 0} {
        error "Unexpected latches outside SRAM macros: [get_object_name $_latches]"
    }
    set FFN_STAGE export
    ffn_checked write_verilog [list write -format verilog -hierarchy -output $IMPL_NETLIST]
    ffn_checked write_ddc [list write -format ddc -hierarchy -output [file join $output_dir ${DESIGN_TOP}.ddc]]
    ffn_checked write_sdc [list write_sdc [file join $output_dir ${DESIGN_TOP}_mapped.sdc]]
    ffn_checked close_svf [list set_svf -off]
    set _ffn_svf_open 0
    foreach _path [list $IMPL_NETLIST $SVF_FILE [file join $output_dir ${DESIGN_TOP}.ddc] \
        [file join $output_dir ${DESIGN_TOP}_mapped.sdc]] {
        ffn_require_file $_path output
        if {[file size $_path] == 0} {error "Empty output: $_path"}
    }

    set FFN_STAGE reports
    ffn_report check_timing.rpt {check_timing}
    ffn_report qor.rpt {report_qor}
    ffn_report area.rpt {report_area -hierarchy}
    ffn_report references.rpt {report_reference -hierarchy}
    ffn_report design_environment.rpt {report_design}
    ffn_report constraints.rpt {report_constraint -all_violators}
    ffn_report timing_setup.rpt {report_timing -delay_type max -max_paths 50 -nworst 3 -input_pins -nets}
    ffn_report timing_hold_preCTS.rpt {report_timing -delay_type min -max_paths 30 -nworst 3 -input_pins -nets}
    # 编译/改名后重新查询集合，避免使用已失效的综合前对象。
    set _inputs [remove_from_collection [all_inputs] [get_ports clk]]
    set _outputs [all_outputs]
    set _reg_d [all_registers -data_pins]
    set _reg_ck [all_registers -clock_pins]
    foreach {_name _from _to} [list \
        i2r $_inputs $_reg_d r2r $_reg_ck $_reg_d \
        r2o $_reg_ck $_outputs i2o $_inputs $_outputs] {
        if {[sizeof_collection $_from] == 0 || [sizeof_collection $_to] == 0} {
            error "Empty endpoint collection for timing_$_name"
        }
        ffn_report timing_${_name}.rpt [list report_timing -delay_type max \
            -from $_from -to $_to -max_paths 20 -input_pins -nets]
    }
    foreach _delay {max min} {
        ffn_report timing_sync_control_${_delay}.rpt [list report_timing -delay_type $_delay \
            -from [get_ports {rst_n abort_i}] -max_paths 20 -input_pins -nets]
    }
    set _sram_pins [get_pins -of_objects $_sram_cells]
    set _sram_inputs [filter_collection $_sram_pins {direction == in && full_name !~ */CLK}]
    set _sram_outputs [filter_collection $_sram_pins {direction == out}]
    set _sram_clocks [filter_collection $_sram_pins {full_name =~ */CLK}]
    if {[sizeof_collection $_sram_clocks] != $EXPECTED_SRAM_COUNT ||
        [sizeof_collection $_sram_inputs] == 0 || [sizeof_collection $_sram_outputs] == 0} {
        error "Unexpected SRAM pin interface; inspect macro binding and library pins"
    }
    foreach _delay {max min} {
        ffn_report timing_to_sram_${_delay}.rpt [list report_timing -delay_type $_delay \
            -to $_sram_inputs -max_paths 30 -input_pins -nets]
        ffn_report timing_from_sram_${_delay}.rpt [list report_timing -delay_type $_delay \
            -from $_sram_outputs -max_paths 30 -input_pins -nets]
    }
    # 空的 SRAM timing 报告不代表通过，须核对时钟传播、宏 setup/hold/CLK->Q 弧。
    if {$POWER_SAIF ne ""} {
        set FFN_STAGE activity
        ffn_checked read_saif [list read_saif -input $POWER_SAIF -instance_name $POWER_SAIF_INSTANCE]
        ffn_optional_report activity_coverage.rpt {report_switching_activity}
    } else {
        puts "WARNING: No SAIF; power uses assumed activity, not measured workload activity."
    }
    ffn_optional_report power_estimate.rpt {report_power}
    set FFN_STAGE complete
    ffn_status SYNTHESIS_COMPLETE_STA_REVIEW_REQUIRED "Mapped outputs written; inspect checks/constraints/timing reports"
    puts "INFO: SYNTHESIS COMPLETE. This is not timing/physical sign-off."
    puts "INFO: Output=$output_dir"
    puts "INFO: Reports=$report_dir"
}}

# 内层 catch 记录主流程错误；外层 catch 处理日志重定向本身的错误。
set _ffn_rc 0
set _ffn_log_rc [catch {
    redirect -tee -file [file join $report_dir dc_run.log] {
        set _ffn_rc [catch {ffn_run} _ffn_message _ffn_options]
        if {$_ffn_rc} {puts "ERROR: stage=$FFN_STAGE: $_ffn_message"}
    }
} _ffn_log_message _ffn_log_options]
if {$_ffn_log_rc} {
    set _ffn_rc $_ffn_log_rc
    set _ffn_message $_ffn_log_message
    set _ffn_options $_ffn_log_options
}
if {$_ffn_rc} {
    # 保留失败现场。不得把 debug_failed.ddc 当作正式 mapped 交付。
    if {$_ffn_design_ready} {
        catch {write -format ddc -hierarchy -output [file join $output_dir debug_failed.ddc]}
    }
    if {$_ffn_svf_open} {catch {set_svf -off}; set _ffn_svf_open 0}
    set _error_file [open [file join $report_dir error_details.rpt] w]
    puts $_error_file "stage=$FFN_STAGE\n$_ffn_message"
    if {[dict exists $_ffn_options -errorinfo]} {puts $_error_file [dict get $_ffn_options -errorinfo]}
    close $_error_file
    ffn_status ERROR $_ffn_message
    cd $_ffn_start_dir
    return -code error "FFN synthesis failed at $FFN_STAGE: $_ffn_message; reports=$report_dir"
}
cd $_ffn_start_dir
# 故意不 exit：保留设计，便于交互 debug；新一轮综合请启动新 DC 会话。

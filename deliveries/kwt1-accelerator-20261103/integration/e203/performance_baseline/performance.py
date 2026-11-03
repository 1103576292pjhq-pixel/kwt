"""Cycle/throughput audit for the explicitly scoped accelerator-only baseline."""
import csv
import math

BUCKETS=('load_bus_cycles','status_bus_cycles','output_bus_cycles','ack_bus_cycles','tb_gap_cycles')


def analyse_metrics(path,task_count=12,frequency_mhz=150.):
    if not math.isfinite(frequency_mhz) or frequency_mhz<=0:
        raise ValueError('Positive finite normalization frequency required')
    with path.open(newline='',encoding='ascii') as stream:
        rows=[{k:int(v) for k,v in row.items()} for row in csv.DictReader(stream)]
    if len(rows)!=task_count or task_count<=0:
        raise ValueError('Wrong number of performance tasks')
    previous_end=-1;tasks=[]
    for index,row in enumerate(rows):
        if any(value<0 for value in row.values()): raise ValueError('Negative counters/events')
        if row['task']!=index or row['start_cycle']<=previous_end:
            raise ValueError('Duplicate task or overlapping measurement windows')
        end=row['complete_cycle'];span=end-row['start_cycle']
        if span<=0 or row['span_cycles']!=span or sum(row[name] for name in BUCKETS)!=span:
            raise ValueError('Cycle span/bucket sum mismatch')
        events=[row[name] for name in ('start_cycle','first_core_cycle','last_core_cycle',
                                       'last_read_cycle','last_ack_cycle','complete_cycle')]
        if events!=sorted(events) or not row['start_cycle']<=row['final_commit_cycle']<=row['last_core_cycle']:
            raise ValueError('Invalid event ordering')
        required=dict(core_blocks=400,operand_groups=102400,core_outputs=25344,read_outputs=25344,
                      ack_blocks=400,error_responses=0,response_hold_cycles=0)
        if any(row[name]!=want for name,want in required.items()):
            raise ValueError('Wrong data ledger or unexpected error/response hold')
        if row['mmio_requests']!=row['mmio_responses'] or row['mmio_requests']<row['read_outputs']+row['ack_blocks']:
            raise ValueError('Unbalanced or insufficient ICB transactions')
        if not row['operand_groups']<=row['core_busy_cycles']<=span or row['core_output_stall_cycles']>row['core_busy_cycles']:
            raise ValueError('Invalid compute counter bounds')
        result=dict(row,layer=index+1,normalized_time_ms=span/(frequency_mhz*1000),
                    normalized_tasks_per_second=frequency_mhz*1e6/span,
                    useful_mac_utilization_total=(99*256*64)/(16*span),
                    useful_mac_utilization_core_busy=(99*256*64)/(16*row['core_busy_cycles']),
                    operand_issue_fraction_core_busy=row['operand_groups']/row['core_busy_cycles'],
                    initial_loading_cycles=row['first_core_cycle']-row['start_cycle'],
                    core_span_cycles=row['last_core_cycle']-row['first_core_cycle'],
                    last_core_to_last_read_cycles=row['last_read_cycle']-row['last_core_cycle'],
                    last_read_to_complete_cycles=end-row['last_read_cycle'])
        tasks.append(result);previous_end=end
    total=sum(row['span_cycles'] for row in rows)
    return dict(scope='ACCELERATOR_ICB_TB_BASELINE_EXCLUDES_CPU_AND_SHARED_RAM',
                tasks=tasks,task_count=task_count,total_cycles=total,normalization_frequency_mhz=frequency_mhz,
                normalized_total_time_ms=total/(frequency_mhz*1000),
                normalized_tasks_per_second=task_count*frequency_mhz*1e6/total,
                mean_cycles_per_task=total/task_count,
                exclusive_bucket_totals={name:sum(row[name] for row in rows) for name in BUCKETS},
                overlapping_core_busy_cycles=sum(row['core_busy_cycles'] for row in rows),
                timing_convention='accepted first TASK request edge to final completed STATUS response retirement; (start,end]',
                simulated_clock_period_ns=6.667,sta_verified=False,
                exclusions=['CPU instruction timing','shared SRAM accesses and input/parameter source loading',
                            'result writeback to shared SRAM','file parsing and golden comparisons',
                            'power/energy and physical timing qualification'])

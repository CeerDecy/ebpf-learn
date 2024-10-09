#include <uapi/linux/openat2.h>
#include <linux/sched.h>

struct data_t {
    u32 pid;
    char comm[TASK_COMM_LEN];
    int retval;
    unsigned int args_size;
    char argv[FULL_MAX_ARGS_ARR];
};

BPF_PERF_OUTPUT(events);
BPF_HASH(tasks, u32, struct data_t);

TRACEPOINT_PROBE(syscalls, sys_enter_execve) {
    struct data_t data;
    u32 pid = bpf_get_current_pid_tgid();
    data.pid = pid;
    bpf_get_current_comm(&data.comm, sizeof(data.comm));
}

TRACEPOINT_PROBE(syscalls, sys_exit_execve) {
    
}
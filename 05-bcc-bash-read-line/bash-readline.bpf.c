#include <uapi/linux/ptrace.h>

struct data_t{
    u32 uid;
    char cmd[64];
};

BPF_PERF_OUTPUT(events);

int bash_readline (struct pt_regs *ctx) {
    struct data_t data = {};
    data.uid = bpf_get_current_uid_gid();

    bpf_probe_read_user(&data.cmd, sizeof(data.cmd), (void *)PT_REGS_RC(ctx));

    events.perf_submit(ctx, &data, sizeof(data));
    return 0;
}
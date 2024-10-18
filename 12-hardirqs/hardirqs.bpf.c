#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_core_read.h>
#include <bpf/bpf_tracing.h>
#include "hardirqs.h"
#include "bits.bpf.h"
#include "maps.bpf.h"

#define MAX_ENTRIES 256

const volatile bool filter_cg = false;
const volatile bool targ_dist = false;
const volatile bool targ_ns = false;
const volatile bool do_count = false;

struct irq_key {
    char name[32];
};

struct {
    __uint(type, BPF_MAP_TYPE_CGROUP_ARRAY);
    __type(key, u32);
    __type(value, u32);
    __uint(max_entries, 1);
} cgroup_map SEC(".maps");

struct {
    __uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
    __uint(max_entries,1);
    __type(key, u32);
    __type(value, u64);
} start SEC(".maps");

struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, MAX_ENTRIES);
    __type(key, struct irq_key);
    __type(value, struct info);
}  infos SEC(".maps");

static struct info zero;

static int handle_entry(int irq, struct irqaction *action) {
    if (filter_cg && !bpf_current_task_under_cgroup(&cgroup_map, 0)) return 0;

    if (do_count) {
        struct irq_key key = {};
        struct info *info;

        bpf_probe_read_kernel_str(&key.name, sizeof(key.name), BPF_CORE_READ(action, name));
        info = bpf_map_lookup_or_try_init(&infos, &key, &zero);

        if (!info) return 0;

        info->count += 1;
        return 0;
    } else {
        u64 ts = bpf_ktime_get_ns();
        
    }
}
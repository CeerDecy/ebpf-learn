
from bcc import BPF

b = BPF(src_file="helloworld.bpf.c")

b.attach_kprobe(event="do_sys_openat2", fn_name="hello_world")

print("%-18s %-16s %-6s %-16s" % ("TIME(s)","COMM","PID","FILE"))

start = 0
def print_event(cpu, data, size):
    global start
    event = b["events"].event(data)
    if start == 0:
        start = event.ts
    time_s = (float(event.ts - start)) / 1000000000
    print("%-18.9f %-16s %-6d %-16s" % (time_s, event.comm, event.pid, event.fname))

b["events"].open_perf_buffer(print_event)

while 1:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()


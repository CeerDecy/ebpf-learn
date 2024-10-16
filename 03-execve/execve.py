from bcc import BPF
from bcc.utils import printb

b = BPF(src_file="execve.bpf.c")

print("%-6s %-16s %-3s %s" % ("PID", "COMM", "RET", "ARGS"))

def print_event(cpu, data, size):
    event = b["events"].event(data)
    print("%-6s %-16s %-3s %s" % (event.pid, event.comm, event.retval, event.argv))

b["events"].open_perf_buffer(print_event)

while 1:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
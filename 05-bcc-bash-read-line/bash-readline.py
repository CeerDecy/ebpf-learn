from bcc import BPF
from time import strftime

b = BPF(src_file="bash-readline.bpf.c")

b.attach_uretprobe(name="/usr/bin/bash", sym="readline", fn_name="bash_readline")

def print_event(cpu,data,size):
    event = b["events"].event(data)
    print("%-9s %-6s %s" % (strftime("%H:%M:%S"),event.uid,event.cmd.decode("utf-8")))

print("%-9s %-6s %s" % ("TIME","UID","CMD"))

b["events"].open_perf_buffer(print_event)

while 1:
    try:
        b.perf_buffer_poll()
    except:
        exit()
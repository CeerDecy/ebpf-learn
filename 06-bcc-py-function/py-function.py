from bcc import BPF, USDT
import subprocess

# find the PID for "python3 -m http.server"
cmd = subprocess.Popen(
    ["pgrep", "-f", "http.server"], stdout=subprocess.PIPE, shell=False
).communicate()
if cmd[0]:
    pid = int(cmd[0].decode("ascii").strip())
else:
    print("ERROR: cannot find PID for python3 -m http.server")
    exit()

u = USDT(pid=pid)

u.enable_probe(probe="function__entry",fn_name="print_functions")
b = BPF(src_file="py-function.bpf.c", usdt_contexts=[u])

def print_event(cpu,data,size):
    event = b["events"].event(data)
    print("%-9s %-6s %s" % (data.filename,data.funcname,data.lineno))

print("%-9s %-6s %s" % ("FILE","FUNC","LINE"))

b["events"].open_perf_buffer(print_event)

while 1:
    try:
        b.perf_buffer_poll()
    except:
        exit()
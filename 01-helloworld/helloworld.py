
from bcc import BPF

b = BPF(src_file="helloworld.bpf.c")

b.attach_kprobe(event="do_sys_openat2", fn_name="hello_world")

b.trace_print()

## eBPF Hello World

`helloworld.bpf.c`是一个ebpf内核程序，通过`helloworld.py`Python程序将ebpf程序注入到内核中，并执行。通过`bpf_trace_printk()`函数将信息打印出来。

这个函数其实是读取的内核调试文件`/sys/kernel/debug/tracing/trace_pipe`
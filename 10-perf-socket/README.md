
将sockops.bpf.o程序加载到内核
```bash
bpftool prog load sockops.bpf.o /sys/fs/bpf/sockops type sockops pinmaps /sys/fs/bpf
```
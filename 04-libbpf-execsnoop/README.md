## 程序启动监控
> execsnoop by libbpf

| 文件名            | 说明       |
|------------------|------------|
|`execsnoop.bpf.c` | bpf内核程序源文件 |
|`execsnoop.bpf.o` | bpf内核程序字节码 |
|`execsnoop.skel.h` | bpf内核程序脚手架 |
|`execsnoop.c` | bpf用户态程序 |
|`execsnoop.o` | bpf用户态程序字节码 |
|`execsnoop` | bpf用户态程序可执行文件 |

### 构建步骤

1. 生成字节码
``` bash
clang -g -O2 -target bpf -D__TARGET_ARCH_x86_64 -I/usr/include/x86_64-linux-gnu -I. -c execsnoop.bpf.c -o execsnoop.bpf.o
```

2. 生成脚手架头文件
``` bash
bpftool gen skeleton execsnoop.bpf.o > execsnoop.skel.h
```

3. 生成BPF前端程序字节码文件
``` bash
clang -g -O2 -Wall -I . -c execsnoop.c -o execsnoop.o
```

4. 生成前端程序可执行文件
``` bash
clang -Wall -O2 -g execsnoop.o -static -lbpf -lelf -lz -lzstd -o execsnoop
```
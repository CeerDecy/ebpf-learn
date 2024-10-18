#ifndef __HARDIRQS_H
#define __HARDIRQS_H

#include "vmlinux.h"

#define MAX_SLOTS 20

struct info {
    __u64 count;
    __u32 slots[MAX_SLOTS];
};


#endif
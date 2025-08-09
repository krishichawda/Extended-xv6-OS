#ifndef PARAM_H
#define PARAM_H

#define NPROC        64  // maximum number of processes
#define NCPU          8  // maximum number of CPUs
#define NOFILE       16  // open files per process
#define NFILE       100  // open files per system
#define NINODE       50  // maximum number of active i-nodes
#define NDEV         10  // maximum major device number
#define ROOTDEV       1  // device number of file system root disk
#define MAXARG       32  // max exec arguments
#define MAXOPBLOCKS  10  // max # of blocks any FS op writes
#define LOGSIZE      (MAXOPBLOCKS*3)  // max data blocks in on-disk log
#define NBUF         (MAXOPBLOCKS*3)  // size of disk block cache
#define FSSIZE       1000  // size of file system in blocks

// Scheduler parameters
#define TIME_QUANTUM     4    // Time quantum for RR scheduling (ticks)
#define AGING_FACTOR     1    // Aging factor for priority boost
#define MAX_PRIORITY     31   // Maximum priority value
#define MIN_PRIORITY     0    // Minimum priority value
#define SJF_THRESHOLD    100  // Burst time threshold for SJF vs RR

// Memory management
#define PGSIZE          4096  // bytes mapped by a page
#define PGSHIFT         12    // log2(PGSIZE)
#define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE-1))

// Virtual memory layout
#define KERNBASE     0x80000000         // First kernel virtual address
#define KERNLINK     (KERNBASE+EXTMEM)  // Address where kernel is linked
#define PHYSTOP      0xE000000          // Top physical memory
#define DEVSPACE     0xFE000000         // Other devices are at high addresses

// Memory layout
#define EXTMEM   0x100000            // Start of extended memory
#define V2P(a)   (((uint) (a)) - KERNBASE)
#define P2V(a)   ((void*)(((char*) (a)) + KERNBASE))

#define V2P_WO(x) ((x) - KERNBASE)    // same as V2P, but without casts
#define P2V_WO(x) ((x) + KERNBASE)    // same as P2V, but without casts

// Swap space parameters
#define NSWAP        1000    // Number of swap slots
#define SWAPBLOCKS   8       // Blocks per swap slot

#endif // PARAM_H 
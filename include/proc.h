#ifndef PROC_H
#define PROC_H

#include "param.h"

// Per-CPU state
struct cpu {
  uchar apicid;                // Local APIC ID
  struct context *scheduler;   // swtch() here to enter scheduler
  struct taskstate ts;         // Used by x86 to find stack for interrupt
  struct segdesc gdt[NSEGS];   // x86 global descriptor table
  volatile uint started;       // Has the CPU started?
  int ncli;                    // Depth of pushcli nesting.
  int intena;                  // Were interrupts enabled before pushcli?
  struct proc *proc;           // The process running on this cpu or null
};

extern struct cpu cpus[NCPU];
extern int ncpu;

//PAGEBREAK: 17
// Saved registers for kernel context switches.
// Don't need to save all the segment registers (%cs, etc),
// because they are constant across kernel contexts.
// Don't need to save %eax, %ecx, %edx, because the
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.
struct context {
  uint edi;
  uint esi;
  uint ebx;
  uint ebp;
  uint eip;
};

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;               // Page table
  char *kstack;               // Bottom of kernel stack for this process
  enum procstate state;       // Process state
  int pid;                    // Process ID
  struct proc *parent;        // Parent process
  struct trapframe *tf;       // Trap frame for current syscall
  struct context *context;    // swtch() here to run process
  void *chan;                 // If non-zero, sleeping on chan
  int killed;                 // If non-zero, have been killed
  struct file *ofile[NOFILE]; // Open files
  struct inode *cwd;          // Current directory
  char name[16];              // Process name (debugging)
  
  // Enhanced scheduler fields
  int priority;               // Process priority (0-31, lower is higher priority)
  int burst_time;             // Expected CPU burst time
  int actual_burst;           // Actual CPU burst time used
  int wait_time;              // Time spent waiting
  int turnaround_time;        // Total turnaround time
  uint creation_time;         // Process creation time
  uint last_run_time;         // Last time process was scheduled
  int time_slice;             // Remaining time slice for RR
  int aging_ticks;            // Ticks since last priority boost
  int nice;                   // Nice value for priority adjustment
  
  // Memory management fields
  uint swap_pages;            // Number of pages swapped out
  uint page_faults;           // Number of page faults
  uint last_access[16];       // LRU tracking for page replacement
  
  // IPC fields
  int msg_queue;              // Message queue ID
  void* shm_addr[8];          // Shared memory addresses
  int sem_count[16];          // Semaphore usage count
};

// Process memory allocator
extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

// Scheduler statistics
struct sched_stats {
  uint total_switches;
  uint sjf_switches;
  uint rr_switches;
  uint aging_boosts;
  uint avg_turnaround;
  uint avg_waiting;
};

extern struct sched_stats sched_stats;

#endif // PROC_H 
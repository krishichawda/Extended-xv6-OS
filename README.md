# Extended xv6 Operating System

This is an enhanced version of the xv6 teaching operating system with several advanced features that demonstrate modern OS concepts.

## Key Features

### 1. Hybrid SJF/RR Scheduler with Aging
- **Shortest Job First (SJF)**: Selects processes with the shortest estimated CPU burst time
- **Round Robin (RR)**: Uses time-slicing for fair scheduling when SJF might cause starvation
- **Aging Mechanism**: Prevents starvation by gradually increasing the priority of waiting processes
- **Dynamic Algorithm Selection**: Automatically switches between SJF and RR based on system state

### 2. Demand Paging and Dynamic Swapping
- **On-demand page loading**: Pages are loaded into memory only when accessed
- **Background pager**: Kernel thread that proactively manages memory pressure
- **LRU page replacement**: Uses Least Recently Used algorithm for page eviction
- **Swap space management**: Dynamic allocation and management of swap slots
- **Page fault handling**: Transparent handling of page faults and swap-in operations

### 3. IPC and Synchronization System Calls
- **Semaphores**: System V style semaphore operations (semget, semop, semctl)
- **Message Queues**: Inter-process message passing (msgget, msgsnd, msgrcv, msgctl)
- **Shared Memory**: Shared memory segments between processes (shmget, shmat, shmdt, shmctl)
- **Synchronization**: Proper locking and coordination mechanisms

### 4. Enhanced File System with Metadata Caching
- **Inode caching**: LRU-based metadata cache for frequently accessed inodes
- **Hash table lookup**: Fast O(1) average case inode lookups
- **Cache statistics**: Detailed performance metrics and hit/miss ratios
- **Automatic cache management**: Dynamic eviction and maintenance

## Building the System

### Prerequisites
- GCC cross-compiler for i386 target
- QEMU emulator
- Standard build tools (make, etc.)

### Build Commands
```bash
# Build the complete system
make

# Build and run in QEMU
make qemu

# Run without graphics
make qemu-nox

# Clean build artifacts
make clean
```

## Testing the Features

The system includes several test programs to demonstrate the enhanced features:

### Scheduler Testing
```bash
# Run the scheduler test
schedtest
```
This creates processes with different CPU burst characteristics to test the hybrid SJF/RR scheduler.

### Memory Management Testing
```bash
# Run the swap/paging test
swaptest
```
This allocates large amounts of memory and accesses it in patterns that trigger demand paging and swapping.

### IPC Testing
```bash
# Test semaphores
semtest

# Test message queues
msgtest

# Test shared memory
shmtest
```

## Architecture Overview

### Kernel Modules
- `kernel/sched.c`: Hybrid scheduler implementation
- `kernel/swap.c`: Demand paging and swapping system
- `kernel/sysipc.c`: IPC system calls
- `kernel/fs_cache.c`: File system metadata caching

### User Programs
- `user/schedtest.c`: Scheduler demonstration
- `user/swaptest.c`: Memory management testing
- `user/semtest.c`: Semaphore testing
- `user/msgtest.c`: Message queue testing
- `user/shmtest.c`: Shared memory testing

## Performance Monitoring

The system provides detailed statistics for monitoring performance:

- **Scheduler Statistics**: Context switch counts, algorithm usage, turnaround times
- **Memory Statistics**: Page fault counts, swap operations, cache hit ratios
- **IPC Statistics**: Operation counts and resource usage
- **File System Statistics**: Cache performance and access patterns

## Technical Implementation Details

### Scheduler Algorithm
```
if (max_waiting_time > threshold):
    use Round Robin
else:
    use Shortest Job First
    
for each process:
    priority = base_priority + aging_factor * wait_time
```

### Memory Management
```
on page_fault(virtual_address):
    if page_is_swapped(virtual_address):
        swap_in(virtual_address)
    else:
        allocate_new_page(virtual_address)
        
background_pager():
    while true:
        if memory_pressure_high():
            evict_lru_pages()
        sleep(interval)
```

### IPC Operations
- Semaphores: Atomic increment/decrement with blocking
- Message Queues: FIFO queuing with type-based filtering
- Shared Memory: Virtual memory mapping with reference counting

## Development and Debugging

### Debug Information
The kernel provides extensive debug output for all subsystems. Key debugging features:

- Process state transitions
- Memory allocation/deallocation
- IPC operation tracing
- File system cache operations

### Monitoring Tools
Built-in monitoring commands provide real-time system statistics:
- Scheduler performance metrics
- Memory usage and paging activity
- IPC resource utilization
- File system cache efficiency

## Educational Value

This extended xv6 demonstrates several important operating system concepts:

1. **Advanced Scheduling**: Real-world scheduling algorithms with starvation prevention
2. **Virtual Memory**: Demand paging and memory management under pressure
3. **Inter-Process Communication**: Modern IPC mechanisms for process coordination
4. **File System Optimization**: Caching strategies for improved I/O performance

Each feature is implemented with educational clarity while maintaining production-quality design principles.

## Future Enhancements

Potential areas for further development:
- Network stack implementation
- Multi-core scheduling improvements
- Advanced file system features (journaling, compression)
- Security enhancements (capabilities, access control)
- Real-time scheduling support

---

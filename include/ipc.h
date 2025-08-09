#ifndef IPC_H
#define IPC_H

#include "param.h"
#include "spinlock.h"

// IPC key types
#define IPC_PRIVATE    0
#define IPC_CREAT      01000
#define IPC_EXCL       02000

// Semaphore operations
#define SEM_UNDO       010000

// Message queue types
#define MSG_NOERROR    010000

// Shared memory flags
#define SHM_RDONLY     010000

// Maximum IPC objects
#define MAX_SEM        32
#define MAX_MSG        32
#define MAX_SHM        32

// Semaphore structure
struct semaphore {
  int semid;                    // Semaphore ID
  int key;                      // IPC key
  int nsems;                    // Number of semaphores in set
  int semval[16];               // Semaphore values
  int sempid[16];               // Last process to operate
  uint semtime;                 // Last operation time
  struct proc *waiting[16];     // Waiting processes
  int nwait[16];                // Number waiting for each semaphore
  struct spinlock lock;         // Protection lock
  int valid;                    // 1 if valid, 0 if deleted
};

// Message structure
struct message {
  long mtype;                   // Message type
  char mtext[256];              // Message text
  int msize;                    // Message size
  struct message *next;         // Next message in queue
};

// Message queue structure
struct msgqueue {
  int msgid;                    // Message queue ID
  int key;                      // IPC key
  struct message *head;         // First message
  struct message *tail;         // Last message
  int msgcount;                 // Number of messages
  int maxbytes;                 // Maximum bytes in queue
  int totalbytes;               // Current bytes in queue
  struct proc *readers;         // Processes waiting to read
  struct proc *writers;         // Processes waiting to write
  struct spinlock lock;         // Protection lock
  int valid;                    // 1 if valid, 0 if deleted
};

// Shared memory segment
struct shmem {
  int shmid;                    // Shared memory ID
  int key;                      // IPC key
  uint size;                    // Size in bytes
  char *addr;                   // Physical address
  int nattach;                  // Number of attachments
  int attached_procs[NPROC];    // Attached process PIDs
  uint atime;                   // Last attach time
  uint dtime;                   // Last detach time
  struct spinlock lock;         // Protection lock
  int valid;                    // 1 if valid, 0 if deleted
};

// System-wide IPC structures
extern struct semaphore semtab[MAX_SEM];
extern struct msgqueue msgtab[MAX_MSG];
extern struct shmem shmtab[MAX_SHM];

// IPC statistics
struct ipc_stats {
  int sem_used;                 // Number of semaphores in use
  int msg_used;                 // Number of message queues in use
  int shm_used;                 // Number of shared memory segments in use
  int total_operations;         // Total IPC operations
};

extern struct ipc_stats ipc_stats;

// Function prototypes
void ipc_init(void);
int find_ipc_slot(int type);
int generate_ipc_key(void);

#endif // IPC_H 
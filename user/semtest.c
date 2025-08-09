#include "types.h"
#include "stat.h"
#include "user.h"

// Test semaphore functionality
int
main(int argc, char *argv[])
{
  int semid;
  int i;
  
  printf(1, "Semaphore Test Starting...\n");
  
  // Create a semaphore set with 2 semaphores
  semid = semget(1234, 2, 0600 | 0001000); // IPC_CREAT = 01000
  if(semid < 0){
    printf(1, "semget failed\n");
    exit();
  }
  
  printf(1, "Created semaphore set %d\n", semid);
  
  // Initialize semaphores
  if(semctl(semid, 0, 1, 1) < 0){  // Set semaphore 0 to 1
    printf(1, "semctl set failed\n");
    exit();
  }
  
  if(semctl(semid, 1, 1, 3) < 0){  // Set semaphore 1 to 3
    printf(1, "semctl set failed\n");
    exit();
  }
  
  printf(1, "Initialized semaphores: sem[0]=1, sem[1]=3\n");
  
  // Test semaphore operations
  for(i = 0; i < 3; i++){
    if(fork() == 0){
      // Child process
      int pid = getpid();
      printf(1, "Child %d: Trying to acquire semaphore 0...\n", pid);
      
      // Try to decrement semaphore 0
      struct sembuf sops;
      sops.sem_num = 0;
      sops.sem_op = -1;  // P operation (wait)
      sops.sem_flg = 0;
      
      if(semop(semid, &sops, 1) < 0){
        printf(1, "Child %d: semop failed\n", pid);
        exit();
      }
      
      printf(1, "Child %d: Acquired semaphore 0, working...\n", pid);
      sleep(10);  // Simulate work
      
      // Release semaphore 0
      sops.sem_op = 1;   // V operation (signal)
      if(semop(semid, &sops, 1) < 0){
        printf(1, "Child %d: semop release failed\n", pid);
        exit();
      }
      
      printf(1, "Child %d: Released semaphore 0\n", pid);
      exit();
    }
  }
  
  // Parent waits for children
  for(i = 0; i < 3; i++){
    wait();
  }
  
  // Check final semaphore values
  int val0 = semctl(semid, 0, 0, 0);  // Get value
  int val1 = semctl(semid, 1, 0, 0);  // Get value
  
  printf(1, "Final semaphore values: sem[0]=%d, sem[1]=%d\n", val0, val1);
  
  // Clean up
  if(semctl(semid, 0, 2, 0) < 0){  // IPC_RMID = 2
    printf(1, "semctl remove failed\n");
  } else {
    printf(1, "Semaphore set removed\n");
  }
  
  printf(1, "Semaphore test completed successfully!\n");
  exit();
} 
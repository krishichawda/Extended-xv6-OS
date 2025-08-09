#include "types.h"
#include "stat.h"
#include "user.h"

// Test the hybrid SJF/RR scheduler
int
main(int argc, char *argv[])
{
  int i, pid;
  
  printf(1, "Scheduler Test Starting...\n");
  printf(1, "Testing hybrid SJF/RR scheduler with aging\n");
  
  // Create processes with different characteristics
  for(i = 0; i < 5; i++){
    pid = fork();
    if(pid == 0){
      int my_pid = getpid();
      int work_amount = (i + 1) * 10;  // Different burst times
      
      printf(1, "Process %d (burst=%d): Starting work\n", my_pid, work_amount);
      
      // Simulate different types of work
      if(i % 2 == 0){
        // CPU-intensive process
        for(int j = 0; j < work_amount * 1000; j++){
          // Busy work
          int dummy = j * j;
          dummy = dummy + 1;
        }
        printf(1, "Process %d: CPU-intensive work completed\n", my_pid);
      } else {
        // I/O-bound process (simulated with sleep)
        for(int j = 0; j < work_amount; j++){
          sleep(1);
          printf(1, "Process %d: I/O operation %d\n", my_pid, j);
        }
        printf(1, "Process %d: I/O-bound work completed\n", my_pid);
      }
      
      exit();
    } else if(pid < 0){
      printf(1, "fork failed\n");
      exit();
    }
  }
  
  // Create some short-burst processes to test SJF
  printf(1, "Creating short-burst processes for SJF testing...\n");
  for(i = 0; i < 3; i++){
    pid = fork();
    if(pid == 0){
      int my_pid = getpid();
      printf(1, "Short process %d: Quick work\n", my_pid);
      
      // Very short burst
      for(int j = 0; j < 100; j++){
        int dummy = j;
        dummy++;
      }
      
      printf(1, "Short process %d: Completed quickly\n", my_pid);
      exit();
    }
  }
  
  // Wait for all children
  printf(1, "Parent: Waiting for all children to complete...\n");
  for(i = 0; i < 8; i++){
    wait();
  }
  
  printf(1, "Scheduler test completed!\n");
  printf(1, "Check kernel messages for scheduler statistics\n");
  exit();
} 
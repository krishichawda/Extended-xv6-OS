#include "types.h"
#include "stat.h"
#include "user.h"

#define PAGE_SIZE 4096
#define NUM_PAGES 20

// Test demand paging and swapping
int
main(int argc, char *argv[])
{
  char *pages[NUM_PAGES];
  int i, j;
  
  printf(1, "Swap Test Starting...\n");
  printf(1, "Testing demand paging and dynamic swapping\n");
  
  // Allocate multiple pages of memory
  printf(1, "Allocating %d pages of memory...\n", NUM_PAGES);
  for(i = 0; i < NUM_PAGES; i++){
    pages[i] = sbrk(PAGE_SIZE);
    if((int)pages[i] == -1){
      printf(1, "sbrk failed at page %d\n", i);
      exit();
    }
    printf(1, "Allocated page %d at address %p\n", i, pages[i]);
    
    // Write a pattern to the page
    for(j = 0; j < PAGE_SIZE; j += 4){
      *((int*)(pages[i] + j)) = i * 1000 + j;
    }
  }
  
  printf(1, "Memory allocation completed\n");
  
  // Access pages in a pattern that might cause swapping
  printf(1, "Testing random access pattern (may trigger swapping)...\n");
  for(i = 0; i < 100; i++){
    int page_num = i % NUM_PAGES;
    int offset = (i * 13) % (PAGE_SIZE - 4);  // Random-ish offset
    
    // Read from the page
    int value = *((int*)(pages[page_num] + offset));
    int expected = page_num * 1000 + offset;
    
    if(value != expected){
      printf(1, "Data corruption detected! Page %d, offset %d: got %d, expected %d\n", 
             page_num, offset, value, expected);
    }
    
    if(i % 10 == 0){
      printf(1, "Access %d: Page %d, value %d\n", i, page_num, value);
    }
    
    // Modify the page
    *((int*)(pages[page_num] + offset)) = value + 1;
  }
  
  // Test sequential access
  printf(1, "Testing sequential access pattern...\n");
  for(i = 0; i < NUM_PAGES; i++){
    printf(1, "Accessing page %d sequentially...\n", i);
    
    // Read entire page
    int sum = 0;
    for(j = 0; j < PAGE_SIZE; j += 4){
      sum += *((int*)(pages[i] + j));
    }
    
    printf(1, "Page %d checksum: %d\n", i, sum);
  }
  
  // Test fork with copy-on-write (if implemented)
  printf(1, "Testing fork with large memory footprint...\n");
  int pid = fork();
  if(pid == 0){
    // Child process
    printf(1, "Child: Modifying shared pages...\n");
    
    // Modify some pages to trigger copy-on-write
    for(i = 0; i < NUM_PAGES / 2; i++){
      *((int*)pages[i]) = 0xDEADBEEF;
      printf(1, "Child: Modified page %d\n", i);
    }
    
    printf(1, "Child: Completed modifications\n");
    exit();
  } else if(pid > 0){
    // Parent process
    wait();  // Wait for child to complete
    
    // Verify parent's pages are unchanged
    printf(1, "Parent: Verifying page integrity after child modifications...\n");
    for(i = 0; i < NUM_PAGES / 2; i++){
      int value = *((int*)pages[i]);
      if(value == 0xDEADBEEF){
        printf(1, "ERROR: Page %d was modified in parent!\n", i);
      } else {
        printf(1, "Page %d intact in parent: %d\n", i, value);
      }
    }
  } else {
    printf(1, "fork failed\n");
  }
  
  printf(1, "Swap test completed!\n");
  printf(1, "Check kernel messages for memory management statistics\n");
  exit();
} 
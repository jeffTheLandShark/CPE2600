/*
 * Filename: fork_mmap.c
 * Description: using fork and share memory 2 processes one program
 * Author: Bob Turney
 * Date: 3/24/2024
 * Note: gcc -o pipe pipe.c
 * observe the pid and ppid in another terminal window while running
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#define PAGESIZE 4096

int main(void) {
  int x = 5;
  // allocated some share memory so both processes can share the area
  int *my_mem = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  *my_mem = 0; // set the first int to e
  int pid = fork();
  printf("process forked into two\n");
  printf("these are the pids %d\n\n",
         getpid()); // note how runs this 2 times, it has forked
  sleep(1);
  if (pid == 0) { // this is the child
    x = 42;
    *my_mem = 42;
    printf("x is in the child %d\n", x);
    printf("shared mem is in the child %d\n", *my_mem);
    sleep(10);
    printf("shared nem is in the child %d\n", *my_mem);
    printf("x is in the child %d\n", x);
  } else { // this is the parent
    x = 1042;
    printf("x is in the parent %d\n", x);
    sleep(1);
    printf("shared mem is in the parent %d\n", *my_mem);
    sleep(5);
    *my_mem = 1042;
    printf("x is in the parent %d\n", x);
    printf("shared mem is in the parent %d\n", *my_mem);
  }
  // sleep(50); // used to see the pid values with another terminal and ps all
  wait(NULL);
  munmap(my_mem, PAGESIZE);
  return 0;
}
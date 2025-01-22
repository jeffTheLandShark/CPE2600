#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wait.h>

#define _USE MATH_DEFINES
#define LENGTH 50

int main(void) {
  int *constants = mmap(NULL, LENGTH * sizeof(int), PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  int *results = mmap(NULL, LENGTH * sizeof(int), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  // Set to constant
  for (int i = 0; i < LENGTH; i++) {
    constants[i] = i;
  }
  printf("\n");

  int pid = fork();
  if (pid == 0) // this is the child
  {
    for (int i = 0; i < LENGTH / 2; i++) {
      results[i] = constants[i] * 2;
    }
  } else { // this is the parent
    for (int i = LENGTH / 2; i < LENGTH; i++) {
      results[i] = constants[i] * 2;
    }
  }

  // print out the results
  for (int i = 0; i < LENGTH; i++) {
    printf("results[%d] = %d\n", i, results[i]);
  }
  wait(NULL);

  munmap(constants, LENGTH * sizeof(int));
  munmap(results, LENGTH * sizeof(int));
  return 0;
}

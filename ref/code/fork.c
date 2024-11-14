/*
 * Filename: fork.c
 * Description: using fork
 * Author: Bob Turney
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int pid = fork();
  printf("pid is %d\n", pid);
  if (pid == 0) {
    printf("pid of child is %d\n", getpid());
  } else {
    printf("pid of parent is %d\n", getpid());
  }
  sleep(20);
  wait(NULL);
  return 0;
}
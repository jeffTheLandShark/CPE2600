/*
 * Filename: fork2.c
 * Description: using fork
 * Author: Bob Turney'
 * Note: observe the pid and ppid in another terminal window while running
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int pid = fork();
  printf("pid is %d\n", pid); // note how runs this 2 times, it has forked

  if (pid == 0) {
    sleep(1);
    printf("id of child and pid of child returned to parent is %d and %d\n",
           pid, getpid());
  } else {
    sleep(2);
    printf("id of child returned to parent and pid of parent is %d and %d\n",
           pid, getpid());
    printf("on the command line of another window do a $ ps all to see the "
           "processes\n");
  }
  sleep(20);
  wait(NULL);
  return 0;
}
/*
 * Filename: syscall.c
 * Description: sample system call
 * Author: Bob Turney
 */

#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t mypid = getpid();
  printf("Pid: %d\n", mypid);

  // indirect version
  mypid = syscall(39);
  printf("Pid: %d\n", mypid);

  return 0;
}

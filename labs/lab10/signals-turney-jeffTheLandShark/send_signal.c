/**
 * File: send_signal.c
 * Modified by: Leigh Goetsch
 *
 * Brief summary of program:
 *    Send SIGUSR1 along with a random integer to a process using sigqueue
 *    Print the random integer that was sent
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
    return 1;
  }

  int pid = atoi(argv[1]);
  if (pid <= 0) {
    fprintf(stderr, "Invalid PID: %s\n", argv[1]);
    return 1;
  }

  union sigval value;
  srand(time(NULL));
  value.sival_int = rand();
  if (sigqueue(pid, SIGUSR1, value) == -1) {
    perror("sigqueue");
    return 1;
  }

  printf("Sent signal with value %d\n", value.sival_int);

  return 0;
}
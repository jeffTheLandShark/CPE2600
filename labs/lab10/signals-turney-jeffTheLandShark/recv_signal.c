/**
 * File: recv_signal.c
 * Modified by: Leigh Goetsch
 *
 * Brief summary of program:
 *     Uses sigaction to register a handler for the SIGUSR1 signal
 *     Wait in an infinite loop for the signal to be received
 *     In signal handler, retrieve sival_int from siginfo_t struct and print
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sig_handler(int signo, siginfo_t *info, void *extra) {
  printf("Received signal %d with value %d\n", signo, info->si_value.sival_int);
}

int main() {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = sig_handler;
  sa.sa_flags = SA_SIGINFO;
  sigaction(SIGUSR1, &sa, NULL);

  while (1) {
    sleep(1);
  }

  return 0;
}
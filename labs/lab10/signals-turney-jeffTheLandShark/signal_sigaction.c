/**
 * @file signal_sigaction.c
 * Modified by: Leigh Goetsch
 *
 * @brief This program demonstrates the use of the sigaction system call to
 * establish a signal handler for the SIGUSR1 signal.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Signal handler for the SIGUSR1 signal.
 * Prints the pid of the process that sent the signal
 *
 * @param signum The signal number.
 */
void sigusr1_handler(int signo, siginfo_t *info, void *ucontext) {

  // Access information about the signal using 'info'

  printf("Caught signal %d, sent by PID: %d\n", signo, info->si_pid);
}

int main() {
  struct sigaction sa;

  // Register the signal handler
  sa.sa_sigaction = sigusr1_handler;
  sa.sa_flags = SA_SIGINFO;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGUSR1, &sa, NULL);

  // Wait in an infinite loop
  while (1) {
  }

  return 0;
}
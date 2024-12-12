/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and
 * then quits
 */

/**
 * Modified by: Leigh Goetsch
 *
 * Brief summary of modifications:
 * 1. removed the exit(0) from the handle_signal function
 * 2. updated printf statement to the handle_signal function
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGINT - prints a message and exits
 */
void handle_signal() {
  printf("Received SIGINT signal, but continuing execution\n");
}

int main() {

  // Register for the signal
  signal(SIGINT, handle_signal);

  // Wait until a signal is received
  while (1) {
    printf("Sleeping\n");
    sleep(1);
  }

  return 0;
}
/**
 * @file signal_alarm.c
 * Modified by: Leigh Goetsch
 *
 * @brief Schedules an alarm to go off in 5 seconds.
 * has signal handler to print that message was received.
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGALRM - prints a message
 */
void handle_signal() { printf("Received SIGALRM signal\n"); }

int main() {

  // Register for the signal
  signal(SIGALRM, handle_signal);

  // Schedule an alarm to go off in 5 seconds
  alarm(5);

  // Wait until a signal is received
  while (1) {
    printf("Sleeping\n");
    sleep(1);
  }

  return 0;
}
/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Leigh Goetsch
 *
 * Brief summary of modifications:
 * 1. imported signal.h
 * 2. added signal handler function
 * 3. registered signal handler
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal() {
  printf("Caught a segmentation fault\n");
  sleep(1);
}

int main(int argc, char *argv[]) {
  // Register the signal handler
  signal(SIGSEGV, handle_signal);

  // Declare a null pointer
  int *i = NULL;

  // Dereference the null pointer
  printf("The value of i is: %d\n", *i);

  // Return to exit the program
  return 0;
}
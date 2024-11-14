/**
 * @file main.c
 * @brief Runs the main program for a matlab clone that does vector math
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 5
 * Name: Leigh Goetsch
 *
 */

#include "parser.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc > 1) {
    // help text here
    printf("To use this program, add cmds\n");
  } else {
    printf("Welcome, plz send things");
    int run = 1;
    while (run) {
      printf("\n> ");
      run = parse();
    }
    printf("\nEnding Program.");
  }
  return 0;
}
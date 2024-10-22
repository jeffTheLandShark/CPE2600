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
#include "csvparser.h"
#include "vectstore.h"

#include <stdio.h>
#include <strings.h>

int main(int argc, char *argv[]) {
  if (argc > 1 && (!strcasecmp(argv[1], "-h") || !strcasecmp(argv[1], "-help"))) {
    // help text here
    printf("To use this program, add cmds\nAvailable commands: list, clear, quit");
  } else {
    init();
    if (argc > 2 && !strcasecmp(argv[1], "-f")) {
      parse_csv(argv[2]);
    }
    printf("Welcome, plz send things");
    int run = 1;
    while (run) {
      printf("\n> ");
      run = parse();
    }
    printf("\nEnding Program.\n");
  }
  return 0;
}

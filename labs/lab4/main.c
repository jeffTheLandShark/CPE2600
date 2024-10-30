/**
 * @file main.c
 * @brief parse cmd args and print out ascii charaters according to the commands
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 4
 * Name: Leigh Goetsch
 *
 * compile with $ gcc -o ascii main.c ainfo.c
 * or with $ make
 *
 * to run live: $ ./ascii
 */

#include "ainfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if (argc > 1) {
    // -c command: number of columns
    if (!strcmp(argv[1], "-c")) {
      if (argc == 3) {
        // convert arg to int
        int cols = strtol(argv[2], NULL, 10);
        // must be between 1 and 9
        if (cols > 0 && cols < 10) {
          printAscii(cols);
        } else {
          printErrorText();
        }
      } else {
        printErrorText();
      }
    } else if (!strcmp(argv[1], "-h")) {
      // print help text
      printHelpText();
    } else {
      // default behaviour for char
      printAsciiChar(*argv[1]);
    }
  } else {
    printAsciiDefault();
  }
}

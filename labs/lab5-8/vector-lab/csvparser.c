/**
 * @file csvparser.c
 * @brief parses csv file to populate vector list
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 7
 * Name: Leigh Goetsch
 *
 */
#include "vectstore.h"

#include <stdio.h>

void parse_csv(const char *filename) {
  FILE *input_csv;

  input_csv = fopen(filename, "r");
  if (!input_csv) {
    printf("Error opening file: %s\n", filename);
    return;
  }
}

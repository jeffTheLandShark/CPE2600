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
#include "Vect.h"

#include <stdio.h>

void parse_csv(const char *filename) {
  FILE *input_csv;

  input_csv = fopen(filename, "r");
  if (!input_csv) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  char line[1024];
  char *name;
  int x, y, z;
  // Read and process each line of the CSV file
  while (fgets(line, sizeof(line), input_csv) != NULL) {
    sscanf(line, "%s, %d, %d, %d", name, &x, &y, &z);
    Vect vect = vectEquals(name, x, y, z);
    assignVect(vect, getVect(name));
    display(name);
  }

  fclose(input_csv);
}
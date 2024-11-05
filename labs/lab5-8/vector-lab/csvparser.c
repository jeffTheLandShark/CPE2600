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
#include "Vect.h"
#include "vectstore.h"

#include <stdio.h>

void parse_csv(const char *filename) {
  FILE *input_csv;

  input_csv = fopen(filename, "r");
  if (!input_csv) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  char line[1024];
  char name[20];
  int x, y, z;
  // Read and process each line of the CSV file
  while (fgets(line, sizeof(line), input_csv) != NULL) {
    int result = sscanf(line, "%[^,],%d,%d,%d", name, &x, &y, &z);

    if (result != 4) {
      printf("File is formatted incorrectly on line: %s\n", line);
      return;
    }
    Vect vect = vectEquals(name, x, y, z);
    assignVect(vect, getVect(name));
    display(name);
  }

  fclose(input_csv);
}

void output_csv(const char *filename) {
  FILE *output_csv;

  output_csv = fopen(filename, "wr+");
  if (!output_csv) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  for (int i = 0; i < getSize(); i++) {
    Vect vect = fromStorage(i);
    fprintf(output_csv, "%s, %d, %d, %d\n", vect.name, vect.x, vect.y, vect.z);
  }
}
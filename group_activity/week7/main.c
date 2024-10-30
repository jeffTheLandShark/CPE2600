/**
 * @file main.c
 * @brief
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 5
 * Name: Leigh Goetsch
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
  int size = ARRAY_SIZE * sizeof(int);
  int *my_array = malloc(size);

  for (int i = 0; i < ARRAY_SIZE; i++) {
    my_array[i] = rand();
    printf("Value at location %4d: %d \n", i, my_array[i]);
  }

  free(my_array);

  return 0;
}
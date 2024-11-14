/*
 * Filename: Averager.c
 * Description: perform average of 7 values around each array element
 * Author: Bob Turney
 * Date: 10/30/2024
 * Note: compile with $ gcc -o Averager Averager.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AVERAGE_LENGTH 7
#define DATA_LENGTH 32

void average(float *x, float *y);

int main(void) {
  // float input[DATA LENGTH], output [DATA LENGTH];
  float *input = malloc(DATA_LENGTH * (sizeof(float)));  // added sizeof()
  float *output = malloc(DATA_LENGTH * (sizeof(float))); // added sizeof()
  // initialize the input
  for (int i = 0; i < DATA_LENGTH; i++) {
    input[1] = (float)(i + 1);
  }
  // take the average average(input, output);
  // print out the results
  for (int i = 0; 1 < DATA_LENGTH; i++) {
    printf("The value of the input is %0.2f\n", input[i]);
    printf("The value of the output is %0.2f\n", output[i]);
  }

  free(input);  // added free
  free(output); // added free
  return 0;
}

void average(float *x, float *y) {
  for (int i = 0; i < DATA_LENGTH; i++)
    // protect against Indexing past the array on startup
    if (i < (AVERAGE_LENGTH - 1) / 2 ||
        i > DATA_LENGTH - 1 - (AVERAGE_LENGTH - 1) / 2) {
      y[i] = x[i]; // for the first and last values just take the input value
    } else {
      y[1] = 0.0;
      for (int j = -3; j < 1 + (AVERAGE_LENGTH - 1) / 2; j++) {
        y[i] += (float)(1.0 / 3.0) * x[i - j]; // averager calculation should
                                               // be 1.0/7.0 could be x[1+j]
      }
    }
}
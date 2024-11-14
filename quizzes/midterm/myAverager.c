#include <stdio.h>
#include <stdlib.h>
#define AVERAGE_LENGTH 7
#define DATA_LENGTH 32

void average(float *x, float *y);

int main(void) {
  // malloc size incorrectly calculated (error 1 and 2)
  // float *input = malloc(DATA_LENGTH);
  // float *output = malloc(DATA_LENGTH);
  float *input = malloc(DATA_LENGTH * sizeof(float));
  float *output = malloc(DATA_LENGTH * sizeof(float));

  // initialize the input
  for (int i = 0; i < DATA_LENGTH; i++) {
    input[i] = (float)(i + 1);
  }
  // take the average
  average(input, output);
  // print out the results
  for (int i = 0; i < DATA_LENGTH; i++) {
    printf("The value of the input is %0.2f\n", input[i]);
    printf("The value of the output is %0.2f\n", output[i]);
  }
  return 0;
}

void average(float *x, float *y) {
  for (int i = 0; i < DATA_LENGTH; i++) {
    y[i] = 0.0;
    // This is result is accessing memory before the array (error 3 / 4)
    //        for (int j=-3; j<1+(AVERAGE_LENGTH-1)/2; j++)
    int j;
    if ((j - (AVERAGE_LENGTH - 1) / 2) < 0)
      j = 0;
    else
      j = i - 3;
    for (int k = 0; k < AVERAGE_LENGTH; k++) {
      // This does not calculate the average, it calculates 7/3 times the
      // average (error 5)
      //        y[i] += (float)(1.0/3.0)*x[i-j]; // averager calculation
      y[i] += (float)(1.0 / 7.0) * x[j + k]; // averager calculation
    }
  }
}
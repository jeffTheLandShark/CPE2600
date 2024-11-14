#include <stdio.h>
#include <stdlib.h>
#define DATA_LENGTH 32

int add(int *x, int *y);

int main(void) {
  int inputX[DATA_LENGTH], inputY[DATA_LENGTH], sum;
  int *xPtr = &inputX[0];
  int *yPtr = &inputY[0];
  // initialize the input
  for (int i = 0; i < DATA_LENGTH; i++) {
    //        inputX[i] = i+1;
    //        inputY[i] = 32-i;
    *(xPtr + i) = i + 1;
    *(yPtr + i) = 32 - i;
  }
  // add and sum
  // sum = add(inputX, inputY);
  sum = add(xPtr, yPtr);
  // print out the results
  for (int i = 0; i < DATA_LENGTH; i++) {
    //        printf("The value of the inputX is %d\n", inputX[i] );
    //        printf("The value of the inputY is %d\n", inputY[i] );
    printf("The value of the inputX is %d\n", *(xPtr + i));
    printf("The value of the inputY is %d\n", *(yPtr + i));
  }
  printf("Sum is %d\n", sum);
  return 0;
}

int add(int *x, int *y) {
  int sum = 0;
  for (int i = 0; i < DATA_LENGTH; i++) {
    //        sum += x[i] + y[i];
    sum += *(x + i) + *(y + i);
  }
  return sum;
}
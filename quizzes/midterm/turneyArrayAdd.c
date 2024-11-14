/*
 * Filename : ArrayAdd.c
 * Description : sum element by element
 * Author : Bob Turney
 * Date : 10 / 30 / 2024
 * Note : compile with $ gcc -o ArrayAdd ArrayAdd.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_LENGTH 32

int add(int *x, int *y);

int main(void) {
  int inputX[DATA_LENGTH], inputY[DATA_LENGTH], sum;
  int *myx = inputX;
  int *myy = inputY;
  // initialize the input
  for (int i = 0; i < DATA_LENGTH; i++) {
    *(myx + i) = i + 1;
    *(myy + i) = 32 - i;
  }
  // take the average
  sum = add(myx, myy);
  // print out the results
  for (int i = 0; i < DATA_LENGTH; i++) {
    printf("The value of the inputX is %d\n", *(myx + i));
    printf("The value of the inputy is %d\n", *(myy + i));
  }
  printf("Sum is %d\n", sum);
  return 0;
}

int add(int *x, int *y) {
  int sum = 0;
  for (int i = 0; i < DATA_LENGTH; i++)
    sum += *(x + i) + *(y + i);
  return sum;
}
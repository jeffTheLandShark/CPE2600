
/**********************************************
 *  Filename: pthread.c
 *  Description: easy case of doing pthread
 *               use time ./FirstPthread to see time differences
 *  Author: Bob Turney
 *  Date: 3/24/2024
 *  Note: gcc -o pthread pthread.c -lpthread
 ***********************************************/
#include <pthread.h>
#include <stdio.h>

void *compute(void *x);

int main(void) {
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;
  pthread_t thread4;
  pthread_t thread5;
  pthread_t thread6;
  pthread_t thread7;
  pthread_t thread8;
  pthread_t thread9;
  pthread_t thread10;

  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  int e = 5;
  int f = 6;
  int g = 7;
  int h = 8;
  int i = 9;
  int j = 10;

  // compute(&value1);
  // compute(&value2);

  pthread_create(&thread1, NULL, &compute, (void *)&a);
  pthread_create(&thread2, NULL, &compute, (void *)&b);
  pthread_create(&thread3, NULL, &compute, (void *)&c);
  pthread_create(&thread4, NULL, &compute, (void *)&d);
  pthread_create(&thread5, NULL, &compute, (void *)&e);
  pthread_create(&thread6, NULL, &compute, (void *)&f);
  pthread_create(&thread7, NULL, &compute, (void *)&g);
  pthread_create(&thread8, NULL, &compute, (void *)&h);
  pthread_create(&thread9, NULL, &compute, (void *)&i);
  pthread_create(&thread10, NULL, &compute, (void *)&j);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);
  pthread_join(thread5, NULL);
  pthread_join(thread6, NULL);
  pthread_join(thread7, NULL);
  pthread_join(thread8, NULL);
  pthread_join(thread9, NULL);
  pthread_join(thread10, NULL);

  return 0;
}

void *compute(void *x) {
  int myadd = 1;
  int sum = 0;

  printf("Start of compute %d\n", *(int *)x);
  for (int i = 0; i < 1000000000; i++) {
    sum += myadd;
    // printf("Value: %d\n", *add_num);
  }
  printf("End of compute %d\n", *(int *)(x));
  printf("sum is %d\n", sum);
  return NULL;
}

#include <stdio.h>
int a = 1;
int b = 2;
int c = 7;
int f(a, b) {
  a = b;
  return c;
}
int g(a, b) {
  c = b;
  return c;
}
int main(void) {
  int a = 3;
  int b = 4;
  int c = 5;
  a = f(a, b);
  b = g(b, c);
  c = a + b;
  printf("The value of %d + %d is %d\n", a, b, c);
  return 0;
}

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#define _USE MATH_DEFINES
#define DFT_SIZE 655
// #define DFT_SIZE 65536

int main(void) {
  float mypi = M_PI;
  // float complex xn malloc(DFT SIZE*sizeof(float)*2);
  // float complex *xk malloc(DFT SIZE*sizeof(float)*2);
  float complex *xn =
      mmap(NULL, DFT_SIZE * sizeof(float) * 2, PROT_READ | PROT_WRITE,
           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  float complex *xk =
      mmap(NULL, DFT_SIZE * sizeof(float) * 2, PROT_READ | PROT_WRITE,
           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  // Set an to constant
  for (int i = 0; i < DFT_SIZE; i++) {
    xn[i] = 32.0 + I * 0.0;
  }
  printf("\n");
  int pid = fork();
  if (pid == 0) // this is the child
  {
    // Discrete Fourier Transform calculation
    for (int k = 0; k < DFT_SIZE / 2; k++) {
      xk[k] = 0.0;
      for (int n = 0; n < DFT_SIZE; n++) {
        xk[k] = xk[k] + xn[n] * cexp(-I * 2 * M_PI * (k)*n / DFT_SIZE);
      }
    }
  } else { // this is the parent
    // Discrete Fourier Transform calculation
    for (int k = DFT_SIZE / 2; k < DFT_SIZE; k++) {
      xk[k] = 0.0;
      for (int n = 0; n < DFT_SIZE; n++) {
        xk[k] = xk[k] + xn[n] * cexp(-I * 2 * M_PI * (k)*n / DFT_SIZE);
      }
    }
  }
  // print out the results
  for (int i = 0; i < DFT_SIZE; i++) {
    printf("Xk[%d] = %f j%f\n", i, creal(xk[i]), cimag(xk[i]));
  }
  wait(NULL);

  munmap(xn, DFT_SIZE * sizeof(float) * 2);
  munmap(xk, DFT_SIZE * sizeof(float) * 2);
  // free(xn);
  // free(xk);
  return 0;
}
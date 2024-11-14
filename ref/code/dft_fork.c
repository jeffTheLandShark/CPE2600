/*
 * Filename: dft_fork.c
 * Description: Try simple use of Complex Numbers - FORK
 * gcc -o exename dft_fork.c-1m
 * Author: Bob Turney
 * Date: 4/9/2024
 */

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define _USE_MATH_DEFINES
#define DFT_SIZE 65536

int main(void) {
  float mypi = M_PI;
  float complex *xn = malloc(DFT_SIZE * sizeof(float) * 2);
  float complex *xk = malloc(DFT_SIZE * sizeof(float) * 2);

  // Set xn to constant
  for (int i = 0; i < DFT_SIZE; i++) {
    xn[i] = 32.0 + I * 0.0;
  }
  printf("\n");

  // FORK
  int pid = fork();
  int pid2 = fork();
  if (pid == 0 && pid2 == 0) { // this is the child, child

    // Discrete Fourier Transform calculation
    for (int k = 0; k < DFT_SIZE / 4; k++) {
      xk[k] = 0.0;
      for (int n = 0; n < DFT_SIZE; n++) {
        xk[k] = xk[k] + xn[n] * cexp(-I * 2 * M_PI * (k)*n / DFT_SIZE);
      }
    }
    // Print out the Resulting xk
    for (int i = 0; i < 10; i++) {
      printf("The value of xk[%d] is %f + j%f\n", i, creal(xk[i]),
             cimag(xk[i]));
    }

  } else if (pid > 0 && pid2 == 0) { // this is the parent, child
    // Discrete Fourier Transform calculation
    for (int k = DFT_SIZE / 4; k < DFT_SIZE / 2; k++) {
      xk[k] = 0.0;
      for (int n = 0; n < DFT_SIZE; n++) {
        xk[k] = xk[k] + xn[n] * cexp(-I * 2 * M_PI * (k)*n / DFT_SIZE);
      }
    }

  } else if (pid == 0 && pid2 > 0) { // this is the child, parent
    // Discrete Fourier Transform calculation
    for (int k = DFT_SIZE / 2; k < DFT_SIZE * 3 / 4; k++) {
      xk[k] = 0.0;
      for (int n = 0; n < DFT_SIZE; n++) {
        xk[k] = xk[k] + xn[n] * cexp(-I * 2 * M_PI * (k)*n / DFT_SIZE);
      }
    }

  } else if (pid > 0 && pid2 > 0) { // this is the parent, parent
    // Discrete Fourier Transform calculation
    for (int k = DFT_SIZE * 3 / 4; k < DFT_SIZE; k++) {
      xk[k] = 0.0;
      for (int n = 0; n < DFT_SIZE; n++) {
        xk[k] = xk[k] + xn[n] * cexp(-I * 2 * M_PI * (k)*n / DFT_SIZE);
      }
    }
  }

  wait(NULL);
  free(xn);
  free(xk);
  return 0;
}
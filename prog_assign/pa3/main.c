/**
 * @file main.c
 * @brief Runs the main program for testing the complex class
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: PA 3
 * Name: Leigh Goetsch
 *
 */

#include "mycomplex.h"
#include <stdio.h>

int main() {
     // Test complex numbers

  // create test numbers
  double complex x = 3.0 + 4.0 * I;
  double complex y = 1.0 + 2.0 * I;
  // show nubers
  printf("x = %.2f + %.2fi\n", creal(x), cimag(x));
  printf("y = %.2f + %.2fi\n", creal(y), cimag(y));

  // show simple addition and subtraction
  printf("Addition:\nx + y = %.2f + %.2fi\n", creal(add(x, y)),
         cimag(add(x, y)));
  printf("Subtraction:\nx - y = %.2f + %.2fi\n", creal(subtract(x, y)),
         cimag(subtract(x, y)));

  // save magnitude and phase to show then test the inverse functions
  // (fromPolar)
  double mag = magnitude(x);
  double angle = phase(x);
  printf("Magnitude of x:\n|sqrt(real^2 + imag^2)| = %.2f\n", mag);
  printf("Phase of x (radians):\natan2(imag, real) = %.2f\n", angle);

  // show fromPolar
  double complex rect = fromMagPhase(mag, angle);
  printf("Rectangular form from polar:\n"
         "magnitude * (cos(phase) + sin(phase)i) = %.2f + %.2fi\n",
         creal(rect), cimag(rect));

  // show multiplication and division
  printf("Multiplication:\nx * y = %.2f + %.2fi\n", creal(multiply(x, y)),
         cimag(multiply(x, y)));
  printf("Division:\nx / y = %.2f + %.2fi\n", creal(divide(x, y)),
         cimag(divide(x, y)));

  // show parallel impedence
  double complex parallel = parallelImpedance(x, y);
  printf("Parallel Impedance: %.2f + %.2fi\n", creal(parallel),
         cimag(parallel));

  return 0;
}
/**
 * @file mycomplex.c
 * @brief Implements operations on complex numbers.
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: PA 3
 * Name: Leigh Goetsch
 *
 */

#include <complex.h>
#include <math.h> // For atan2, sqrt, and trigonometric functions

// c1 + c2
double complex add(double complex c1, double complex c2) { return c1 + c2; }

// c1 - c2
double complex subtract(double complex c1, double complex c2) {
  return c1 - c2;
}

// | sqrt(a^2 + b^2) |
double magnitude(double complex c) { return cabs(c); }

// arctan(b/a)
double phase(double complex c) { return carg(c); }

// mag * (cos(phase) + sin(phase)i);
double complex fromMagPhase(double magnitude, double phase) {
  return magnitude * (cos(phase) + I * sin(phase));
}

// c1 * c2
double complex multiply(double complex c1, double complex c2) {
  return c1 * c2;
}

// c1 / c2
double complex divide(double complex c1, double complex c2) { return c1 / c2; }

// Zeq = (Z1 * Z2) / (Z1 + Z2)
double complex parallelImpedance(double complex c1, double complex c2) {
  return (c1 * c2) / (c1 + c2);
}
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

#define _USE_MATH_DEFINES

// The program shall add two complex numbers.
double complex add(double complex c1, double complex c2);

// The program shall subtract two complex numbers
double complex subtract(double complex c1, double complex c2);

//  The program shall find the magnitude and phase of a complex number given in
//  rectangular form, a + j b.
double magnitude(double complex c);
double phase(double complex c);

// The program shall find the rectangular form given magnitude and phase of a
// complex number.
double complex fromMagPhase(double magnitude, double phase);

// The program shall find the multiplication of two complex numbers
double complex multiply(double complex c1, double complex c2);

// The program shall find the division of two complex numbers
double complex divide(double complex c1, double complex c2);

// Given two impedances the program shall calculate the impedance of the
// parallel combination.
double complex parallelImpedance(double complex c1, double complex c2);

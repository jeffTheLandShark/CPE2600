/**
 * @file vectmath.c
 * @brief for performing operations on vectors and integers
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 5
 * Name: Leigh Goetsch
 *
 *
 */
#include "vectmath.h"

#include <string.h>

Vect addVect(const char *name, Vect vect1, Vect vect2) {
  Vect vect;
  // copy name
  strcpy(vect.name, name);
  // appy addition to each vector dimension
  vect.x = add(vect1.x, vect2.x);
  vect.y = add(vect1.y, vect2.y);
  vect.z = add(vect1.z, vect2.z);
  return vect;
}

Vect addScalar(const char *name, int x, int y) {
  // create a 1d vect of the results of addition
  Vect vect = {.x = add(x, y), .y = 0, .z = 0};
  strcpy(vect.name, name);
  return vect;
}

int add(int x, int y) { return x + y; }

Vect subtractVect(const char *name, Vect vect1, Vect vect2) {
  Vect vect;
  // copy name
  strcpy(vect.name, name);
  // appy subtraction to each vector dimension
  vect.x = subtract(vect1.x, vect2.x);
  vect.y = subtract(vect1.y, vect2.y);
  vect.z = subtract(vect1.z, vect2.z);
  return vect;
}

Vect subtractScalar(const char *name, int x, int y) {
  // create a 1d vect of the results of subtraction
  Vect vect = {.x = subtract(x, y), .y = 0, .z = 0};
  strcpy(vect.name, name);
  return vect;
}

int subtract(int x, int y) { return x - y; }

int dotProduct(Vect vect1, Vect vect2) {
  // dot product equation returning the result as an int
  return product(vect1.x, vect2.x) + product(vect1.y, vect2.y) +
         product(vect1.z, vect2.z);
}

Vect dotProductVect(const char *name, Vect vect1, Vect vect2) {
  // create a 1d vect of the results of dot product
  Vect vect = {.x = dotProduct(vect1, vect2), .y = 0, .z = 0};
  strcpy(vect.name, name);
  return vect;
}

Vect crossProduct(const char *name, Vect vect1, Vect vect2) {
  // apply cross product following the equation
  Vect vect;
  strcpy(vect.name, name);
  // x = (y1*z2)-(z1*y2)
  vect.x = product(vect1.y, vect2.z) - product(vect1.z, vect2.y);
  // y = (z1*x2) - (x1*z2)
  vect.y = product(vect1.z, vect2.x) - product(vect1.x, vect2.z);
  // z = (x1*y2) - (y1*x2)
  vect.z = product(vect1.x, vect2.y) - product(vect1.y, vect2.x);
  return vect;
}

Vect scalarVectProduct(const char *name, Vect vect1, int scalar) {
  // scale vector by gain amount
  Vect vect;
  strcpy(vect.name, name);
  vect.x = product(vect1.x, scalar);
  vect.y = product(vect1.y, scalar);
  vect.z = product(vect1.z, scalar);
  return vect;
}

Vect scalarProduct(const char *name, int x, int scalar) {
  // The results of multiplication in a 1d vect
  Vect vect = {.x = product(x, scalar), .y = 0, .z = 0};
  strcpy(vect.name, name);
  return vect;
}

int product(int x, int y) { return x * y; }
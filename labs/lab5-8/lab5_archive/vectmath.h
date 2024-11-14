/**
 * @file vectmath.h
 * @brief contains methods for performing vector math
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 5
 * Name: Leigh Goetsch
 *
 *
 */
#include "vectstore.h"

Vect addVect(const char *name, Vect vect1, Vect vect2);

Vect addScalar(const char *name, int x, int y);

int add(int x, int y);

Vect subtractVect(const char *name, Vect vect1, Vect vect2);

Vect subtractScalar(const char *name, int x, int y);

int subtract(int x, int y);

int dotProduct(Vect vect1, Vect vect2);

Vect dotProductVect(const char *name, Vect vect1, Vect vect2);

Vect crossProduct(const char *name, Vect vect1, Vect vect2);

Vect scalarVectProduct(const char *name, Vect vect1, int scalar);

Vect scalarProduct(const char *name, int x, int scalar);

int product(int x, int y);
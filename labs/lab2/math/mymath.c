/**
* @file mymath.c
* @brief contains two functions for math operations related to calculating bit ranges
*
* Course: CPE2600
* Section: 121
* Assignment: Lab 2
* Name: Leigh Goetsch
*
* 
*/
#include "mymath.h"
#include <math.h>

#define BASE_2 2.0

long int maxvalue(int bits){
   return (long int) pow(BASE_2, (double) bits) - 1;
}

int numbits(int value) {
    return ((int) log2((double) value)) + 1;
}
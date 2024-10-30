/**
* @file circle.c
* @brief contains functions for calculating area of a circle
*
* Course: CPE2600
* Section: 121
* Assignment: Quiz 1
* Name: Leigh Goetsch
*
* 
*/
#include "circle.h"
#include <math.h>

double get_rad(double circumference){
    return (circumference) / (2 * M_PI);
}

double get_area(double radius){
    return M_PI * pow(radius, 2);
}
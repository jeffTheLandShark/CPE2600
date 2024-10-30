/**
* @file main.c
* @brief contians the main function.
*
* Course: CPE2600
* Section: 121
* Assignment: Quiz 1
* Name: Leigh Goetsch
* 
* to compile: $ gcc main.c circle.c -lm
* This project has a makefile also
*/

#include "circle.h"
#include <stdio.h>

#define TEST_CIRCLE_SIZE 6.28

int main (int argc, char* argv[]){
    double circumference;
    if (argc > 1){
        scanf("%lf", &circumference);
    } else {
        circumference = TEST_CIRCLE_SIZE;
    }

    double radius = get_rad(circumference);
    double area = get_area(radius);

    printf("The area of a circle with circumference %3lf is %3lf.\n", circumference, area);
}
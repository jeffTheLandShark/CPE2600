/**
* @file main.c
* @brief contians the main function.
*
* Course: CPE2600
* Section: 121
* Assignment: Lab 2
* Name: Leigh Goetsch
* 
* to compile: $ gcc main.c mymath.c -lm
*/

#include "mymath.h"
#include <stdio.h>

#define TEST_ARRAY_SIZE 4

int main (){
    // test arrays
    int bitMax[] = {4, 8, 16, 32};
    int bitsNum[] = {7, 8, 15, 16};

    int i;

    // iterate through maxvalue test values
    for (i = 0; i < TEST_ARRAY_SIZE; i++){
        int bits = bitMax[i];
        printf("The max value that can be represented by %d bits is ", bits);
        printf("%ld\n", maxvalue(bits));
    }

    // iterate through numbits test values
    for (i = 0; i < TEST_ARRAY_SIZE; i++){
        int value = bitsNum[i];
        printf("The min number of bits that can represent %d is ", value);
        printf("%d\n", numbits(value));
    }

    return 0;
}
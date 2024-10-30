/**
* @file filter.c
* @brief contains a function that performs an fir filter on an array of samples
*
* Course: CPE2600
* Section: 121
* Assignment: Problem Assignment 2
* Name: Leigh Goetsch
*
*/

#include <stdio.h>

// Define constants
#define FILTER_SIZE 7
#define DATA_SIZE 512

// FIR filter function
void fir_filter(const double h[], const double x[], double y[]) {
    //iterate through samples
    for (int n = 0; n < DATA_SIZE; n++) {
        // set output sample
        y[n] = 0;
        // iterate though filter coefficients
        for (int k = 0; k < FILTER_SIZE; k++) {
            // find the sample that is k earlier than n
            int index = n - k;
            if (index < 0) {
                // Use first sample for negative index
                y[n] += h[k] * x[0]; 
            } else {
                y[n] += h[k] * x[index]; 
            }
        }
    }
}
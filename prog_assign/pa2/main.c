/**
* @file main.c
* @brief contains the logic for choosing how the program runs
*
* Course: CPE2600
* Section: 121
* Assignment: Problem Assignment 2
* Name: Leigh Goetsch
*
* compile with $ gcc -o filter main.c filter.c test.c -lm
* this project has a make file, so you can just call make
* to run tests by default: $ ./filter -test
* to use test file: $ ./filter -test -f < test.txt
* to use as an fir filter: $ ./filter < file.txt
* for instructions: $ ./filter -h
*/

#include <stdio.h>
#include <string.h>
#include "filter.h"
#include "test.h"

#define FILTER_SIZE 7
#define DATA_SIZE 512

int main (int argc, char* argv[]) {
    // if there is input
    if (argc > 1) {
       // use -test flag to run tests
        if (!strcmp(argv[1],"-test")) {
            // -f to provide custom input file with format:
            // line 1: 7 filter coefficients 
            // line 2: 512 input values
            // line 3: 512 expected output values
            if (argc > 2 && !strcmp(argv[2],"-f")) {
                printf("Running custom test.\n");

                double h[FILTER_SIZE];
                double x[DATA_SIZE];
                double y[DATA_SIZE];
                double out[DATA_SIZE];

                // 7 filter coefficients
                for (int i = 0; i < FILTER_SIZE; i++){
                    scanf("%lf", &h[i]);
                }

                // 512 samples
                for (int i = 0; i < DATA_SIZE; i++) {
                    scanf("%lf", &x[i]);
                }

                // 512 expected values
                for (int i = 0; i < DATA_SIZE; i++) {
                    scanf("%lf", &out[i]);
                }

                // run test
                test(h, x, y, out);

            } else{
                printf("Running default tests.\n");
                // run all pre-written tests
                test_constant_data();
                test_impulse_data();
                test_noisy_data();
            }
        } else if (!strcmp(argv[1],"-h")) {
            printf("Welcome to FIR Filter Program\n\ndefault behaviour:\n\tuse provided file and output filtered values.\n\tThe file should contain 519 values separated by spaces: 7 filter coefficients and 512 input samples\n\n-tests:\n\tdefault: run pre-written tests.\n\t\t1. Constant input data with no shift in output data expected\n\t\t2. Single value of 1 at location 256 in the input data and the filter coefficients are expected as output data values\n\t\t3. Noisy input data with noise reduced output data expected\n\n\t-f: use specified input file in format:\n\t\t7 filter coefficients\n\t\t512 input samples\n\t\t512 expected output values\n");

        }
    } else {
        printf("Running FIR Filter.\n");
        // default behaviour: 
        // line 1: 7 filter coefficients
        // line 2: 512 samples
        double h[FILTER_SIZE];
        double x[DATA_SIZE];
        double y[DATA_SIZE];

        for (int i = 0; i < FILTER_SIZE; i++){
            scanf("%lf", &h[i]);
        }

        for (int i = 0; i < DATA_SIZE; i++) {
            scanf("%lf", &x[i]);
        }

        fir_filter(h, x, y);

        // output filter result
        printf("Output:\n{");
        for (int i = 0; i < DATA_SIZE -1; i++) {
            printf("%.5f, ",y[i]);
        }
        printf("%.5f}", y[DATA_SIZE -1]);

    }
    return 0;
}


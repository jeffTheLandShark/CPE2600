/******************************************************************************
 *  Filename: model.c
 *  Description: A program that takes in the given accel%, break%, and 
 *               previous step actual speed and actual position
 *               and determines the actual speed and and actual position
 *  Authors: John Williams, Connor Albrecht, Andrew Lizak, Anish Kusukuntla
 *  Date: 12/11/24
 *  Note: gcc -o model model.c
 *****************************************************************************/

#include <stdio.h>

// Function to model the cruise controller
void model(double accel, double brake, double prev_speed, double prev_position, double *actual_speed, double *actual_position) {
    // Scale inputs from 0-10V to percentage (0-100)
    double accel_percent = (accel / 10.0) * 100.0;
    double brake_percent = (brake / 10.0) * 100.0;

    // Update speed: Increase due to acceleration, decrease due to braking
    double speed_change = accel_percent - brake_percent;
    *actual_speed = prev_speed + (speed_change * 0.01); // Adjust rate of speed change
    if (*actual_speed < 0) {
        *actual_speed = 0; // Ensure speed is not negative
    } 

    // Update position based on speed
    *actual_position = prev_position + (*actual_speed * 0.1); // Simple proportional update

    // Scale outputs from speed and position to 0-5V range
    *actual_speed = (*actual_speed / 100.0) * 5.0; // Assuming max speed maps to 5V
    *actual_position = (*actual_position / 1000.0) * 5.0; // Assuming max position maps to 5V
}
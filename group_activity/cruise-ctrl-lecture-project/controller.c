/*
 * @file controller.h
 * @brief controller for the cruise control system
 */

#include <math.h>

void controller(int cruise, double speed_setp, double actual_speed, double position_setp,
double actual_position, int manual_accel, int manual_break, int* command_accel, int* command_break) {
    if (cruise && !manual_accel && !manual_break) { //active
        if (actual_position - position_setp < 0) { //car is too close
            *command_accel = 0;
            *command_break = 25 + (int) (100.0 / (position_setp - actual_position));

            if(*command_break > 100) {
                *command_break = 100;
            }
        } else if (abs(actual_speed - speed_setp) > 3) { //cruise control will get within 5 mph
            int percent = (fabs(actual_speed - speed_setp) - 3) * 5;
            if (percent > 100) {
                percent = 100;
            }
            if (actual_speed - speed_setp > 0) { //too fast
                *command_break = percent;
                *command_accel = 0;
            } else { //too slow
                *command_accel = percent;
                *command_break = 0;
            }
        }
    } else {
        *command_accel = manual_accel;
        *command_break = manual_break;
    }
}
/*
 * @file controller.h
 * @brief controller for the cruise control system
 */

void controller(int cruise, double speed_setp, double actual_speed,
                double position_setp, double actual_position, int manual_accel,
                int manual_break, int *command_accel, int *command_break);
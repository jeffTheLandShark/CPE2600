/**
* @file controller.c
* @brief high level state machine for a machine controller
*
* Course: CPE2600
* Section: 121
* Assignment: Problem Assignment 1
* Name: Leigh Goetsch
*
* compile with $ gcc -o controller controller.c
* to run live: $ ./controller
* to use test file: $ ./controller < test.txt
*/

// Define states
#define STOPPED 0
#define STARTUP 1
#define RUNNING 2
#define COASTDOWN 3

#include <stdio.h>
#include <time.h>
#include <unistd.h>

int current_state = STOPPED;
int speed_command = 0;
time_t state_enter_time = 0;


int main (int argc, char* argv[]) {
    int run = 0;

    while(1){
        time_t current_time = time(NULL);
        int time_diff = difftime(current_time, state_enter_time);

        switch(current_state) {
            // Stopped State
            case STOPPED:
                speed_command = 0;
                if (run == 1){
                    state_enter_time = current_time;
                    current_state = STARTUP;
                }
                break;
            // Startup State
            case STARTUP:
                speed_command = 50;
                if (time_diff >= 15 && run == 1){
                    current_state = RUNNING;
                }
                break;
            case RUNNING:
                speed_command = 100;
                if (run == 0){
                    state_enter_time = current_time;
                    current_state = COASTDOWN;
                }
                break;
            case COASTDOWN:
                speed_command = 25;
                if (time_diff >= 30){
                    current_state = STOPPED;
                }
            break;
        }
        // print output
        printf("The current speed command is %d%%\n", speed_command);
        // update run
        scanf("%d", &run);
        // wait 1 sec
        sleep(1);
    }

}

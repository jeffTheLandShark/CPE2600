/******************************************************************************
 *  Filename: cruise_controller.c
 *  Description: 
 *  Authors: Braydon Hanson, Eric Mahn, Alex Toma, Ryan Hilgendorf
 *  Date: 12/11/24
 *  Note: gcc -o cruise_controller cruise_controller.c
 *****************************************************************************/
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "cruise_controller.h"
#include "dataInterface.h"

// User Interface Headers
void user_interface();


// Declare threads, timers, and structure
pthread_t thread1, thread2;
timer_t timer1, timer2;

// Structure to hold all variable parameters for various functions
typedef struct userStruct {

    int cruise;                         // in userInterface
    double speed_setp, position_setp;   // in userInterface
    double manual_accel, manual_break;  // in userInterface
    int *command_accel, *command_break; // determine value in controller

    float positionVoltage;          // actual_speed in model in volts
    float speedVoltage;             // actual_speed in model in volts
    float *adcFeetPosition;         // actual_position in controller + model
    float *adcMPHSpeed;             // actual_speed in controller + model
    float accelerationPercentage;   // command_accel in controller
    float breakPercentage;          // command_break in controller
    float *accelerationVoltage;     // accel in model
    float *breakVoltage;            // break in model


} userStruct;

struct userStruct user = {0};

int main() {
    // Start with random values
    user.speedVoltage = 3;
    user.positionVoltage = 2;
    user.speed_setp = 2;
    user.position_setp = 2;
    user.cruise = 1;
    user.manual_accel = 2;
    user.manual_break = 2;

    //pointers
    /*
    user.command_accel = 2;
    user.command_accel = 2;
    *user.command_break = 2;
    *user.adcFeetPosition = 2;
    *user.adcMPHSpeed = 2;
    *user.accelerationVoltage = 2;
    *user.breakVoltage = 2;
    */

    display();
    // Call cruise method
    cruise_controller();
    // Close timers
    timer_delete(timer1);
    timer_delete(timer2);

    return 0;
}

void cruise_controller()
{

// Create structs
int timerid_datacontrol = 1, timerid_ui = 2;
struct sigevent sev_datacontrol, sev_ui;
struct itimerspec datacontrol, ui, curr_time;

// Assign methods to timer for when occurred
sev_datacontrol.sigev_notify = SIGEV_THREAD;
sev_datacontrol.sigev_value.sival_ptr = &timerid_datacontrol;
sev_datacontrol.sigev_notify_function = timer_handler;
sev_datacontrol.sigev_notify_attributes = NULL;

sev_ui.sigev_notify = SIGEV_THREAD;
sev_ui.sigev_value.sival_ptr = &timerid_ui;
sev_ui.sigev_notify_function = timer_handler;
sev_ui.sigev_notify_attributes = NULL;


// Create timers
if(timer_create(CLOCK_REALTIME, &sev_datacontrol, &timer1) == -1) {
    perror("Timer_create");
    exit(EXIT_FAILURE);
}
if(timer_create(CLOCK_REALTIME, &sev_ui, &timer2) == -1) {
    perror("Timer_create");
    exit(EXIT_FAILURE);
}

// Setting timer delay for data/control and UI threads
datacontrol.it_value.tv_sec = 0;
datacontrol.it_value.tv_nsec = 500000000;
datacontrol.it_interval.tv_sec = 0;
datacontrol.it_interval.tv_nsec = 500000000;

ui.it_value.tv_sec = 0;
ui.it_value.tv_nsec = 300000000;
ui.it_interval.tv_sec = 0;
ui.it_interval.tv_nsec = 300000000;

// Start the timers
if(timer_settime(timer1, 0, &datacontrol, NULL) == -1) {
    perror("Timer_settime");
    exit(EXIT_FAILURE);
}
if(timer_settime(timer2, 0, &ui, NULL) == -1) {
    perror("Timer_settime");
    exit(EXIT_FAILURE);
}

// Infinite loop for cruise control
while(1) {

    if(timer_gettime(timer1, &curr_time) == -1) {
        perror("Timer_gettime");
        exit(EXIT_FAILURE);
    }
    if(timer_gettime(timer2, &curr_time) == -1) {
        perror("Timer_gettime");
        exit(EXIT_FAILURE);
    }
}
// End of cruise_controller function
}

// datacontrol thread method
void* datacontrolMethod(void* arg) {
    printf("Data / Control Method running\n");

    //convertADC(user.positionVoltage, user.speedVoltage, user.adcFeetPosition, user.adcMPHSpeed);
    //convertDAC(user.accelerationPercentage, user.breakPercentage, user.accelerationVoltage, user.breakVoltage);
    

    return NULL;
}

// UI thread method
void* uiMethod(void* arg) {
    printf("UI Method running\n");

    return NULL;
}

// Create the threads and assigns the methods to threads
void timer_handler(union sigval sv) {
    int thread_num = *((int*)sv.sival_ptr); // gets thread number from ptr
    if(thread_num == 1) {
        pthread_create(&thread1, NULL, datacontrolMethod, &thread_num);
        pthread_join(thread1, NULL);
    } else if(thread_num == 2){
        pthread_create(&thread2, NULL, uiMethod, &thread_num);
        pthread_join(thread2, NULL);
    }
}


void display() {
    printf("User values\n----------\n");
    printf("Cruise: %d\n", user.cruise);
    printf("Speed_setp: %f\n", user.speed_setp);
    printf("Position_setp: %f\n", user.position_setp);
    printf("Manual_accel: %f\n", user.manual_accel);
    printf("Manual_break: %f\n", user.manual_break);

    if (user.command_accel != NULL)
        printf("Command_accel: %d\n", *user.command_accel);
    else
        printf("Command_accel: NULL\n");

    if (user.command_break != NULL)
        printf("Command_break: %d\n", *user.command_break);
    else
        printf("Command_break: NULL\n");

    printf("PositionVoltage: %f\n", user.positionVoltage);
    printf("SpeedVoltage: %f\n", user.speedVoltage);

    if (user.adcFeetPosition != NULL)
        printf("adcFeetPosition: %f\n", *user.adcFeetPosition);
    else
        printf("adcFeetPosition: NULL\n");

    if (user.adcMPHSpeed != NULL)
        printf("adcMPHPosition: %f\n", *user.adcMPHSpeed);
    else
        printf("adcMPHPosition: NULL\n");

    printf("accelerationPercentage: %f\n", user.accelerationPercentage);
    printf("breakPercentage: %f\n", user.breakPercentage);

    if (user.accelerationVoltage != NULL)
        printf("accerationVoltage: %f\n", *user.accelerationVoltage);
    else
        printf("accerationVoltage: NULL\n");

    if (user.breakVoltage != NULL)
        printf("breakVoltage: %f\n", *user.breakVoltage);
    else
        printf("breakVoltage: NULL\n");
    printf("\n");
}

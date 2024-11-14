/*
 * Filename: StateMachine.c
 * Description: using switch case to do State Machines
 * Author: Bob Turney
 * Date: 10/27/2024
 * Note: gcc -o StateMachine Stateflachine.c
 *    /StateMachine
 */

#include <stdio.h>
#include <unistd.h>

// declare enumerated states
enum states { Stopped, Running, Diagnostics };
int main(void) {
  // This is testing data for Run and Diag signal Inputs
  int Run[] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int Diag[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0};
  int speed_percent = 0; // this is the output
  enum states States;
  for (int i = 0; i < 30; i++) {
    printf("Run %d, Diag %d\n", Run[i], Diag[i]);
    // this is the switch-case that implements the state machine
    switch (States) {
    case Stopped: // move to Running if input run is 1 and Diag is not 1
      speed_percent = 0;
      printf("In Stopped, Speed percent is %d\n", speed_percent);
      if (Diag[i] == 1) {
        // does not matter what Run signal is if Diagnostic is 1
        States = Diagnostics;
      } else if (Run[i] == 1 && Diag[i] == 0) {
        States = Running;
      }
      break;
    case Running: // stay in running unless input Run signal is e speed percent
                  // 100;
      printf("In Running, Speed precent is %d\n", speed_percent);
      if (Run[i] == 0) {
        States = Stopped;
      }
      break;
    case Diagnostics: // stay in Diagnostics until Diag signal is 0
      speed_percent = 0;
      printf("In Diagnostics, Speed percent is %d\n", speed_percent);
      if (Diag[i] == 0) {
        States = Stopped;
      }
      break;
    default:
      printf("Default case \n");
    }
    sleep(1);
  }

  return 0;
}
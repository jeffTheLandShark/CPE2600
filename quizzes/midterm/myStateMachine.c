#include <stdio.h>
#include <string.h>

// state: stopped = 0, running = 1, diagnostics = 2
int state;
int speed;
// function prototype
int stateMachine(int run, int diag);

// setup initial state and give inputs (not necessary, but helped me with
// design)
int main() {
  // set stopped state to begin
  state = 0;
  speed = 0;

  // list of inputs
  int run[8] = {0, 0, 0, 0, 0, 1, 1, 0};
  int diag[8] = {0, 1, 1, 0, 0, 0, 0, 0};

  // loop through all states & transitions
  for (int i = 0; i < 8; i++) {
    speed = stateMachine(run[i], diag[i]);
    printf("Speed: %d", speed);
  }
  return 0;
}

// state machine code
int stateMachine(int run, int diag) {
  // switch case
  switch (state) {
    // stopped case
  case 0:
    // transition to diagnostics
    if (diag == 1) {
      state = 2;
      return 0;
    }
    // transition to running
    if (run == 1 && diag == 0) {
      state = 1;
      return 100;
    }
    break;

    // running case
  case 1:
    // transition to stopped
    if (run == 0) {
      state = 0;
      return 0;
    }
    break;

    // diagnostics case
  case 2:
    // transition to stopped
    if (diag == 0) {
      state = 0;
      return 0;
    }
    break;
  }

  return speed;
}
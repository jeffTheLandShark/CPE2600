#include <stdio.h>
#include "dataInterface.h"

#define MAXINTVALUE 1023

// Function definitions
int convertADC(float positionVoltage, float speedVoltage,float *adcFeetPosition,float *adcMPHSpeed) {
    int adcpositionValue = (int)((positionVoltage / 5.0) * MAXINTVALUE); // creates a voltage proportion and multiplies that by max int value
    int adcSpeedValue = (int)((speedVoltage / 5.0) * MAXINTVALUE); // creates a voltage proportion and multiplies that by max int value
    *adcFeetPosition = (adcpositionValue/MAXINTVALUE) * 100; // converts the 10 bit int to a range of 0-100 feet
    *adcMPHSpeed = (adcSpeedValue/MAXINTVALUE) * 100; // converts the 10 bit int to a range of 0-100 mph
    return 0;
}

float convertDAC(float accelerationPercentage, float breakPercentage, float *accelerationVoltage,float *breakVoltage) {
    *accelerationVoltage = accelerationPercentage/100.0 * 10.0; // takes the percentage and converts it to a voltage(0-10V)
    *breakVoltage = breakPercentage/100.0 * 10.0; // takes the percentage and converts it to a voltage(0-10V)
    return 0;
}


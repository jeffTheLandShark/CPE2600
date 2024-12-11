#include <stdio.h>

// Function prototypes
int convertADC(float positionVoltage, float speedVoltage,float *adcFeetPosition,float *adcMPHSpeed);
float convertDAC(float accelerationPercentage, float breakPercentage, float *accelerationVoltage,float *breakVoltage);

// Function definitions
int convertADC(float positionVoltage, float speedVoltage,float *adcFeetPosition,float *adcMPHSpeed) {
    int adcpositionValue = (int)((positionVoltage / 5.0) * 1023);
    int adcSpeedValue = (int)((speedVoltage / 5.0) * 1023);
    *adcFeetPosition = (adcpositionValue/1023) * 100;
    *adcMPHSpeed = (adcSpeedValue/1023) * 100;
    return 0;
}

float convertDAC(float accelerationPercentage, float breakPercentage, float *accelerationVoltage,float *breakVoltage) {
    *accelerationVoltage = accelerationPercentage/100.0 * 10.0;
    *breakVoltage = breakPercentage/100.0 * 10.0;
    return 0;
}

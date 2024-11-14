/*
 * Filename : Struct Temperature.c
 * Description : Midterm Exam Problem 6
 * Author : Bob Turney
 * Date : 10 / 27 / 2024
 */

#include <stdio.h>
#include <string.h>

typedef struct Temps {
  float tempF[24];
  float tempC[24];
} Temps;

float FtoC(float degreeF);

int main(void) {
  Temps daily_temps;
  float degF;
  for (int i = 0; i < 24; i++) {
    printf("Please enter temperature value %d in IP units\n", i);
    scanf("%f", &degF);
    daily_temps.tempF[i] = degF;
    daily_temps.tempC[i] = FtoC(daily_temps.tempF[i]); // Convert for SI units
  }
  // Print out the units and temperatures
  for (int i = 0; i < 24; i++)
    printf("The temperatures are %f F and %f C \n", daily_temps.tempF[i],
           daily_temps.tempC[i]);
  return 0;
}
float FtoC(float degreeF) {
  float degreeC = (degreeF - 32.0) * 5.0 / 9.0;
  return degreeC;
}
#include <stdio.h>
#include <string.h>

#define NUM_TEMPS 24

typedef struct TempsBuffer {
  float fahrenheit[NUM_TEMPS];
  float celsius[NUM_TEMPS];
} TempBuffer;
float c_to_f(float c);
float f_to_c(float f);

int main(void) {
  printf("(C)elsius or (F)ahrenheit? (f/c)");
  char userChoice[1];
  scanf("%s", userChoice);

  TempBuffer temps;

  if (!strcasecmp(userChoice, "f")) {

    // get temps in F
    float input;
    for (int i = 0; i < NUM_TEMPS; i++) {
      printf("\nInput temp in Fahrenheit:");
      scanf("%f", &input); // user input
      temps.fahrenheit[i] = input;
      temps.celsius[i] = f_to_c(input); // conversion
    }

    for (int i = 0; i < NUM_TEMPS; i++) {
      printf("\nTemp %d: %3.2f F | %3.2f C", i, temps.fahrenheit[i],
             temps.celsius[i]);
    }

  } else if (!strcasecmp(userChoice, "c")) {

    // get temps in celsius
    float input;
    for (int i = 0; i < NUM_TEMPS; i++) {
      printf("\nInput temp in Celsius:");
      scanf("%f", &input); // user input
      temps.celsius[i] = input;
      temps.fahrenheit[i] = c_to_f(input); // conversion
    }

    for (int i = 0; i < NUM_TEMPS; i++) {
      printf("\nTemp %d: %3.2f F | %3.2f C", i, temps.fahrenheit[i],
             temps.celsius[i]);
    }

  } else {
    printf("Did not chose a viable option.");
  }

  return 0;
}

float c_to_f(float c) { return (float)c * (9.0 / 5.0) + 32.0; }

float f_to_c(float f) { return (float)(f - 32.0) * (5.0 / 9.0); }
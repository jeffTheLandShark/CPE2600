/*
 * Filename : timestamp.c
 * Description : using Enums
 * Author : Bob Turney
 * Date : 3 / 7 / 2024
 */
 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  time_t t = time(NULL); // the number of seconds since Jan 01, 1970
  struct tm datetime = *localtime(&t);
  int32_t t32;
  uint32_t ut32;
  printf("Current time is %ld in seconds\n", t);
  printf("Current datetime is %d-%02d-%02d %02d:%02d:%02d\n",
         datetime.tm_year + 1900, datetime.tm_mon + 1, datetime.tm_mday,
         datetime.tm_hour, datetime.tm_min, datetime.tm_sec);
  // first do a sizeof on t to see what type of variable this is
  // size of 8 so 64 bits on this current machine and version
  printf("the sizeof t is %ld\n", sizeof(t));
  // add to this the number of seconds until Jan 19, 2038, 03:13:07
  printf("add 14 years\n");
  t = t + 441504000; // add 14 years from now
  datetime = *localtime(&t);
  // works in 64 bit but exceeds the 2^31 of 32 bit signed max
  printf("Current time is %ld in seconds\n", t);
  printf("Current datetime is %d-%02d-%02d %02d:%02d:%02d\n",
         datetime.tm_year + 1900, datetime.tm_mon + 1, datetime.tm_mday,
         datetime.tm_hour, datetime.tm_min, datetime.tm_sec);
  // we should see the rollover if this is 32 bit to negative
  t32 = t;
  printf("Current time is %d in seconds for signed 32 bit\n",
         t32); // see the negative value
  // now if we cast to unsigned uint32_t
  // we are not intersted in time before 1970 we get
  // but now if we cast to unsigned value assuming
  ut32 = t32;
  printf("Current time is %u in seconds for unsigned 32 bit\n",
         ut32); // see the positive value
  // now greater than 2^31
  // should probably do a 32 bit compile to make sure this is fixed

  return 0;
}
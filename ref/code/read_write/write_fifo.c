
/**********************************************
 *  Filename: write_fifo.c
 *  Description: using FIFO to connect to programs
 *   do $ mkfifo myfifo in advance of running both programs
 *  Author: Bob Turney
 *  Date: 3/24/2024
 *  Note: gcc -o program1 program1.c
 *  run program1 in a terminal
 *  and run program2 in a terminal
 *  does not matter which program you run first
 ***********************************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(void) {
  int arr[5];
  mkfifo("my_arr",
         0777); // or do $mkfifo fifoname in advance of running the program
  printf("Am I blocked on the open?\n");
  int fd = open("my_arr", O_WRONLY); // should check if opened properly
  printf("Am I blocked after the open?\n");
  if (fd == -1) {
    return 1;
  }
  for (int i = 0; i < 5; i++) {
    arr[i] = i + 10;
    printf("Wrote %d value of %d \n", i, arr[i]);
  }
  printf("Am I blocked before the write FIFO?\n");
  write(fd, arr, sizeof(arr));
  printf("Am I blocked after the write FIFO?\n");
  for (int i = 0; i < 5; i++) {
    arr[i] = i + 20;
    printf("Wrote %d value of %d \n", i, arr[i]);
  }
  write(fd, arr, sizeof(arr));
  for (int i = 0; i < 5; i++) {
    arr[i] = i + 30;
    printf("Wrote %d value of %d \n", i, arr[i]);
  }
  write(fd, arr, sizeof(arr));
  close(fd);
  return 0;
}

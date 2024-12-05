
/**********************************************
 *  Filename: read_fifo.c
 *  Description: using FIFO to connect to programs
 *   do $ mkfifo myfifo in advance of running both programs
 *  Author: Bob Turney
 *  Date: 3/24/2024
 *  Note: gcc -o program1 program1.c
 *  run program1 in a terminal
 *  and run program2 in a terminal
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
  printf("delay before open()\n");
  sleep(10);
  int fd = open("my_arr", O_RDONLY); // should check if opened properly
  printf("after the open now\n");
  if (fd == -1) {
    return 1;
  }
  sleep(10);
  read(fd, arr, sizeof(arr));
  for (int i = 0; i < 5; i++) {
    printf("Received %d value %d\n", i, arr[i]);
  }
  sleep(10);
  read(fd, arr, sizeof(arr));
  for (int i = 0; i < 5; i++) {
    printf("Received %d value %d\n", i, arr[i]);
  }
  sleep(10);
  read(fd, arr, sizeof(arr));
  for (int i = 0; i < 5; i++) {
    printf("Received %d value %d\n", i, arr[i]);
  }
  close(fd);
  return 0;
}

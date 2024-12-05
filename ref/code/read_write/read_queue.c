
/**********************************************
 *  Filename: read_queue.c
 *  Description: using queue to connect to programs
 *  Author: Bob Turney
 *  Date: 3/24/2024
 *  Note: gcc -o read_queue read_queue.c
 *  run ./write_queue in a terminal
 *  and ./read_queue in a second terminal
 *  does not matter which program you run first
 ***********************************************/
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_NAME "/test_queue"
#define MAX_SIZE 1024

int main() {
  mqd_t mq;
  char buffer[MAX_SIZE];

  // Open the message queue
  mq = mq_open(QUEUE_NAME, O_RDONLY);
  if (mq == (mqd_t)-1) {
    perror("mq_open");
    exit(1);
  }
  sleep(30);
  for (int i = 0; i < 10; i++) {
    // Receive the message
    if (mq_receive(mq, buffer, MAX_SIZE, NULL) == -1) {
      perror("mq_receive");
      exit(1);
    }

    printf("Message received: %s\n", buffer);
  }
  // Cleanup
  if (mq_close(mq) == -1) {
    perror("mq_close");
    exit(1);
  }

  if (mq_unlink(QUEUE_NAME) == -1) {
    perror("mq_unlink");
    exit(1);
  }

  return 0;
}

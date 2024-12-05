
/**********************************************
 *  Filename: write_queue.c
 *  Description: using queue to connect to programs
 *  Author: Bob Turney
 *  Date: 3/24/2024
 *  Note: gcc -o write_queue write_queue.c
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

#define QUEUE_NAME "/test_queue"
#define MAX_SIZE 1024

int main() {
  mqd_t mq;
  struct mq_attr attr;
  char buffer[MAX_SIZE];

  // Initialize the queue attributes
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MAX_SIZE;
  attr.mq_curmsgs = 0;

  // Create the message queue
  mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
  if (mq == (mqd_t)-1) {
    perror("mq_open");
    exit(1);
  }
  for (int i = 0; i < 10; i++) {
    printf("Enter a message: ");
    fgets(buffer, MAX_SIZE, stdin);

    // Send the message
    if (mq_send(mq, buffer, MAX_SIZE, 0) == -1) {
      perror("mq_send");
      exit(1);
    }

    printf("Message sent: %s\n", buffer);
  }
  // Cleanup
  if (mq_close(mq) == -1) {
    perror("mq_close");
    exit(1);
  }

  // only the last one needs to unlink
  // in this case it is the read side

  // if (mq_unlink(QUEUE_NAME) == -1) {
  //     perror("mq_unlink");
  //     exit(1);
  // }
  return 0;
}

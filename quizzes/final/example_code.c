#include <time.h>
typedef struct Type {
  int x;
} Type;

#include <stdlib.h>

#define ARRAY_SIZE 10
#define NEW_SIZE 2

int dynamic_mem() {
  Type *array = malloc(sizeof(Type) * ARRAY_SIZE);

  // Reallocate memory for array (increasing size)
  array = realloc(array, sizeof(Type) * (ARRAY_SIZE + NEW_SIZE));

  free(array);
  return 0;
}

// ************************************************************************************

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MESSAGE 5

int pipes() {
  int fd[2];
  int input, output, err;

  if (pipe(fd) == -1) {
    perror("pipe error!!\n");
    return 1;
  }

  int pid = fork();

  if (pid == 0) { // Child process
    input = MESSAGE;
    close(fd[0]);                 // Close read
    printf("Child processing\n"); // Simulate some work
    sleep(10);
    // Send message
    write(fd[1], &input, sizeof(input));
    printf("Child sent message: %d\n", input);
    close(fd[1]);
  } else if (pid > 0) {            // Parent process
    close(fd[1]);                  // Close write
    printf("Parent processing\n"); // Simulate some work
    sleep(5);
    printf("Parent waiting for message\n");
    // Receive message
    err = read(fd[0], &output, sizeof(output));
    if (err == -1) {
      perror("read error!!\n");
      return 1;
    }
    printf("Parent received message: %d\n", output);
    close(fd[0]);
    wait(NULL);
  }
  return 0;
}

// ************************************************************************************

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int named_pipes() {
  const char *fifo_name = "/tmp/myfifo";

  if (mkfifo(fifo_name, 0666) == -1) {
    perror("mkfifo");
    return 1;
  }

  int fd = open(fifo_name, O_WRONLY);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  write(fd, "Hello from writer", 17);
  close(fd);

  return 0;
}

// ************************************************************************************

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define NUM_THREADS 5

sem_t semaphore;

void *thread_function(void *arg) {
  sem_wait(&semaphore);
  printf("Thread %ld is in the critical section\n", (long)arg);
  sleep(1); // Simulate some work
  printf("Thread %ld is leaving the critical section\n", (long)arg);
  sem_post(&semaphore);
  return NULL;
}

int semaphores() {
  pthread_t threads[NUM_THREADS];
  sem_init(&semaphore, 0, 1);

  for (long i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, thread_function, (void *)i);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  sem_destroy(&semaphore);
  return 0;
}

// ************************************************************************************

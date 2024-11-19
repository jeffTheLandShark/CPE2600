/*
 * @file fork_sema.c
 * @brief semaphore use with shared memory
 * @date 2024-11-18
 * @note gcc -o fork_sema fork_sema.c -lpthread -lrt
 */

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 20

int main(void) {
  int shm_fd;
  int *mem;
  sem_t *sem;
  int pid;

  //   share memory file descriptor
  shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666); // check for shd_fd == -1

  //   set the size of shared mem
  ftruncate(shm_fd, sizeof(int) * SIZE);

  // map the shared mem
  mem = mmap(0, sizeof(int) * SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd,
             0); // check if mem == MAP_FAILED

  // create semaphore
//   sem = sem_open("/mysem", O_CREAT, 0666, 1); // check for sem == SEM_FAILED
  sem = sem_open("/mysem", O_CREAT, 0666, 2); // check for sem == SEM_FAILED

  pid = fork(); // check pid == -1

  if (pid == 0) { // child
    sem_wait(sem);
    printf("Child writing...\n");

    for (int i = 0; i < SIZE; i++) {
      mem[i] = i + 23;
      usleep(100);
    }
    printf("Child done writing...\n");
    sem_post(sem);
  } else {        // parent
    usleep(1000); // wait for child to finish
    sem_wait(sem);
    printf("Parent reading\n");

    for (int i = 0; i < SIZE; i++) {
      printf("%d %d\n", i, mem[i]);
    }
    sem_post(sem);
    wait(NULL);
  }

  // unmap
  munmap(mem, sizeof(int) * SIZE); // check == -1

  // unlink mem
  shm_unlink("/myshm"); // == -1

  // close sem
  sem_close(sem); // == -1

  // unlink sem
  sem_unlink("/mysem"); // == -1
}

/**********************************************
 *  Filename: multiproc.c
 *  Description: using fork
 *  Author: Bob Turney
 *  Date: 3/24/2024
 *  Note: gcc -o multiproc multiproc.c
 *
 ***********************************************/
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME "/my_shm"
#define SEM_NAME "/my_sem"
#define SHM_SIZE 1024

int main() {
  int shm_fd;
  char *shm_addr;
  sem_t *sem;
  pid_t pid;

  // Create shared memory
  shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    perror("shm_open");
    exit(1);
  }

  // Set the size of the shared memory
  if (ftruncate(shm_fd, SHM_SIZE) == -1) {
    perror("ftruncate");
    exit(1);
  }

  // Map the shared memory
  shm_addr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (shm_addr == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  // Create semaphore
  sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
  if (sem == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  // Fork a child process
  pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(1);
  }

  if (pid == 0) { // Child process
    sem_wait(sem);
    snprintf(shm_addr, SHM_SIZE, "Hello from child process!");
    sem_post(sem);
    exit(0);
  } else {      // Parent process
    wait(NULL); // Wait for child process to finish
    sem_wait(sem);
    printf("Parent reads: %s\n", shm_addr);
    sem_post(sem);

    // Clean up
    munmap(shm_addr, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);
    sem_close(sem);
    sem_unlink(SEM_NAME);
  }

  return 0;
}

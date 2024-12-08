#include <fcntl.h>
#include <math.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME1 "/my_shm1"
#define SHM_NAME2 "/my_shm2"

#define SEM_NAME1 "/my_sem1"
#define SEM_NAME2 "/my_sem2"
#define SEM_NAME3 "/my_sem3"
#define SEM_NAME4 "/my_sem4"
#define SEM_NAME_PROC2 "/my_sem_proc2"
#define SEM_NAME_PROC3 "/my_sem_proc3"
#define SHM_SIZE 1024
#define NUM_INPUTS 8
#define SLEEPTIME 1

void cleanup() {
  shm_unlink(SHM_NAME1);
  shm_unlink(SHM_NAME2);
  sem_unlink(SEM_NAME1);
  sem_unlink(SEM_NAME2);
  sem_unlink(SEM_NAME3);
  sem_unlink(SEM_NAME4);
}

void sigint_handler(int signum) {
  printf("Caught signal %d (Ctrl+C)\n", signum);
  cleanup(); // Call cleanup function
  exit(0);   // Exit program
}

int main() {
  // Register signal handler for SIGINT
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    perror("signal");
    exit(1);
  }

  int shm_fd1, shm_fd2;
  int *shm_addr1, *shm_addr2;
  sem_t *sem1, *sem2, *sem3, *sem4, *sem_proc2, *sem_proc3;
  pid_t pid1, pid2;

  // Create shared memory
  shm_fd1 = shm_open(SHM_NAME1, O_CREAT | O_RDWR, 0666);
  if (shm_fd1 == -1) {
    perror("shm_open");
    exit(1);
  }

  shm_fd2 = shm_open(SHM_NAME2, O_CREAT | O_RDWR, 0666);
  if (shm_fd2 == -1) {
    perror("shm_open");
    exit(1);
  }

  // Set the size of the shared memory
  if (ftruncate(shm_fd1, SHM_SIZE) == -1 ||
      ftruncate(shm_fd2, SHM_SIZE) == -1) {
    perror("ftruncate");
    exit(1);
  }

  // Map the shared memory
  shm_addr1 = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd1, 0);
  if (shm_addr1 == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  shm_addr2 = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd2, 0);
  if (shm_addr2 == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  // Create semaphores for synchronization
  sem1 = sem_open(SEM_NAME1, O_CREAT, 0666, 1); // semaphore for buffer 1 read
  if (sem1 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  sem2 = sem_open(SEM_NAME2, O_CREAT, 0666, 1); // semaphore for buffer 1 write
  if (sem2 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  sem3 = sem_open(SEM_NAME3, O_CREAT, 0666, 1); // semaphore for buffer 2 read
  if (sem3 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  sem4 = sem_open(SEM_NAME4, O_CREAT, 0666, 1); // semaphore for buffer 2 write
  if (sem4 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  sem_proc2 = sem_open(SEM_NAME_PROC2, O_CREAT, 0666,
                       0); // semaphore to hold back proc 2 at start
  if (sem_proc2 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  sem_proc3 = sem_open(SEM_NAME_PROC3, O_CREAT, 0666,
                       0); // semaphore to hold back proc 3 at start
  if (sem_proc3 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  int ahh;          // Declare a variable to hold the semaphore value
  int *ahh2 = &ahh; // Initialize num to point to num_value
  sem_getvalue(
      sem1, ahh2); // sem_getvalue will store the semaphore value in num_value
  printf("initsem1 %d\n", *ahh2); // Print the value stored in num_value
  sem_getvalue(
      sem2, ahh2); // sem_getvalue will store the semaphore value in num_value
  printf("initsem2 %d\n", *ahh2); // Print the value stored in num_value
  sem_getvalue(
      sem3, ahh2); // sem_getvalue will store the semaphore value in num_value
  printf("initsem3 %d\n", *ahh2); // Print the value stored in num_value
  sem_getvalue(
      sem4, ahh2); // sem_getvalue will store the semaphore value in num_value
  printf("initsem4 %d\n", *ahh2); // Print the value stored in num_value
  sem_getvalue(
      sem_proc2,
      ahh2); // sem_getvalue will store the semaphore value in num_value
  printf("initsem_proc2 %d\n", *ahh2); // Print the value stored in num_value
  sem_getvalue(
      sem_proc3,
      ahh2); // sem_getvalue will store the semaphore value in num_value
  printf("initsem_proc3 %d\n\n", *ahh2); // Print the value stored in num_value

  int nums[NUM_INPUTS] = {2, 3, 4, 5, 6, 7, 8, 9};

  // sem_unlink(SEM_NAME1);
  // sem_unlink(SEM_NAME2);
  // sem_unlink(SEM_NAME3);
  // sem_unlink(SEM_NAME4);
  // sem_unlink(SEM_NAME_PROC2);
  // sem_unlink(SEM_NAME_PROC3);
  // exit(0);

  pid1 = fork(); // Fork first child process
  if (pid1 < 0) {
    perror("fork");
    exit(1);
  }

  if (pid1 > 0) {
    pid2 = fork(); // Fork second child process
    if (pid2 < 0) {
      perror("fork");
      exit(1);
    }
  }

  if (pid1 > 0 && pid2 > 0) { // First process
    // stage 1
    sem_wait(sem1);
    sleep(SLEEPTIME);
    shm_addr1[0] = nums[0] * nums[0];
    printf("STAGE1 Proc 1 Num 1: %d\n", shm_addr1[0]);
    sem_post(sem1);
    // sem_post(sem2);

    // stage 2
    sem_post(sem_proc2); // process 2 can start
    sem_wait(sem3);
    sleep(SLEEPTIME);
    shm_addr2[0] = nums[1] * nums[1];
    printf("STAGE2 Proc 1 Num 2: %d\n", shm_addr2[0]);
    sem_post(sem3);
    sem_post(sem_proc3); // proc 3 can start
    // sem_post(sem4);

    // loops
    for (int i = 0; i < NUM_INPUTS - 2; i++) {
      if (i % 2 == 0) {
        sem_wait(sem4);
        sleep(SLEEPTIME);
        shm_addr2[1] = nums[2 + i] * nums[2 + i];
        printf("STAGE%d Proc 1 Num %d: %d\n", i + 3, 2 + i + 1, shm_addr2[1]);
        sem_post(sem4);
      } else {
        sem_wait(sem3);
        sleep(SLEEPTIME);
        shm_addr2[0] = nums[2 + i] * nums[2 + i];
        printf("STAGE%d Proc 1 Num %d: %d\n", i + 3, 2 + i + 1, shm_addr2[0]);
        sem_post(sem3);
      }
    }
  }

  if (pid1 == 0) {         // Second process
    int num_value;         // Declare a variable to hold the semaphore value
    int *num = &num_value; // Initialize num to point to num_value
    sem_getvalue(
        sem2, num); // sem_getvalue will store the semaphore value in num_value

    sem_wait(sem_proc2);
    sem_wait(sem2);
    sem_wait(sem1);
    sleep(SLEEPTIME);
    shm_addr1[1] = shm_addr1[0] + 10;
    printf("STAGE2 Proc 2 Num 1: %d\n", shm_addr1[1]);
    sem_post(sem1);
    sem_post(sem2);

    for (int i = 0; i < NUM_INPUTS - 1; i++) {
      if (i % 2 == 0) {
        sem_wait(sem3);
        sem_wait(sem1);

        sleep(SLEEPTIME);
        shm_addr1[0] = shm_addr2[0] + 10;
        printf("STAGE%d Proc 2 Num %d %d\n", i + 3, 2 + i, shm_addr1[0]);

        sem_post(sem1);
        sem_post(sem3);
      } else {
        sem_wait(sem4);
        sem_wait(sem2);
        sleep(SLEEPTIME);
        shm_addr1[1] = shm_addr2[1] + 10;
        printf("STAGE%d Proc 2 Num %d %d\n", i + 3, 2 + i, shm_addr1[1]);
        sem_post(sem2);
        sem_post(sem4);
      }
    }

    exit(0);
  }

  // third process
  if (pid2 == 0) {
    sem_wait(sem_proc3);
    for (int i = 0; i < NUM_INPUTS; i++) {
      if (i % 2 == 0) {
        sem_wait(sem2);
        sleep(SLEEPTIME);
        printf("STAGE%d Result %d: %f\n", i + 3, i + 1, sqrt(shm_addr1[1]));
        sem_post(sem2);
      } else {
        sem_wait(sem1);
        sleep(SLEEPTIME);
        printf("STAGE%d Result %d: %f\n", i + 3, i + 1, sqrt(shm_addr1[0]));
        sem_post(sem1);
      }
    }
    exit(0);
  }

  wait(NULL); // Wait for first child
  wait(NULL); // Wait for second child

  // Clean up
  munmap(shm_addr1, SHM_SIZE);
  munmap(shm_addr2, SHM_SIZE);
  close(shm_fd1);
  close(shm_fd2);
  shm_unlink(SHM_NAME1);
  shm_unlink(SHM_NAME2);
  sem_close(sem1);
  sem_close(sem2);
  sem_close(sem3);
  sem_close(sem4);
  sem_unlink(SEM_NAME1);
  sem_unlink(SEM_NAME2);
  sem_unlink(SEM_NAME3);
  sem_unlink(SEM_NAME4);
  sem_unlink(SEM_NAME_PROC2);
  sem_unlink(SEM_NAME_PROC3);

  return 0;
}

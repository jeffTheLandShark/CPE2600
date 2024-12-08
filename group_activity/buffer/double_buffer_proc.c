#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME "/my_shm"
#define SEM_NAME1 "/my_sem1"
#define SEM_NAME2 "/my_sem2"
#define SEM_NAME3 "/my_sem3"
#define SEM_NAME4 "/my_sem4"
#define SHM_SIZE 1024

int main() {
  int shm_fd1, shm_fd2;
  int *shm_addr1, *shm_addr2;
  sem_t *sem1, *sem2, *sem3, *sem4;
  pid_t pid1, pid2;

  // Create shared memory
  shm_fd1 = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  if (shm_fd1 == -1) {
    perror("shm_open");
    exit(1);
  }

  shm_fd2 = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
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

  // Map Both pointers for shm_addr1
  int *shm_addr1_1 = shm_addr1;
  int *shm_addr1_2 = shm_addr1 + (SHM_SIZE / 2);

  shm_addr2 = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd2, 0);
  if (shm_addr2 == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  // Map Both pointers for shm_addr2
  int *shm_addr2_1 = shm_addr2;
  int *shm_addr2_2 = shm_addr2 + (SHM_SIZE / 2);

  // Create semaphores for synchronization
  sem1 = sem_open(SEM_NAME1, O_CREAT, 0666,
                  1); // semaphore for addr1_0 (back buffer)
  if (sem1 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  sem2 = sem_open(SEM_NAME2, O_CREAT, 0666,
                  0); // semaphore for addr1_1 (front buffer)
  if (sem2 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  sem3 = sem_open(SEM_NAME3, O_CREAT, 0666,
                  0); // semaphore for addr2_0 (back buffer)
  if (sem3 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  sem4 = sem_open(SEM_NAME4, O_CREAT, 0666,
                  0); // semaphore for addr2_1 (front buffer)
  if (sem4 == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  int num;

  pid1 = fork(); // fork a second process
  if (pid1 < 0) {
    perror("fork");
    exit(1);
  }

  if (pid1 > 0) { // fork a third process
    pid2 = fork();
  }

  if (pid1 > 0 && pid2 > 0) { // process 1
    num = 1;                  // starting value, increment by 1 every process
    // stage 1
    sem_post(sem1); // shouldn't have to do this, but I do
    sem_wait(sem1); // lock addr1_0 (back half of shm_addr1)

    *shm_addr1_1 = num;
    sleep(1);

    sem_post(sem1); // Unlock addr1_0
    sem_post(sem2); // Signal that addr1_1 is ready to be read
    sem_post(sem3); // Signal that addr2_0 is ready for writing

    // stage 2
    sem_wait(sem2);
    *shm_addr1_2 = num;
    sleep(1);
    sem_post(sem2);

    pid2 = fork(); // create third process
    if (pid2 < 0) {
      perror("fork");
      exit(1);
    }
  } else { // process 2
    // stage 2 - RW
    sem_wait(sem1); // Wait for addr2_1 (front buffer for shm_addr2)
    sem_wait(sem3);
    num = *shm_addr1_1;
    *shm_addr2_1 = num;
    sleep(1);
    sem_post(sem1);
    sem_post(sem3);
    sem_post(sem4);
  }

  // now ready for loop
  for (int i = 0; i < 10; i++) {
    if (pid1 > 0 && pid2 > 0) { // process 1
      printf("here0\n");
      // first - write
      sem_wait(sem4);
      printf("here1\n");
      num++;
      *shm_addr1_1 = num;
      sleep(1);
      sem_post(sem4);

      // second - write
      sem_wait(sem2);
      printf("here2\n");
      num++;
      *shm_addr1_2 = num;
      sleep(1);
      sem_post(sem2);
    } else if (pid1 == 0) { // process 2
      // first - RW
      sem_wait(sem1);
      sem_wait(sem2);
      printf("here3\n");
      num = *shm_addr1_1;
      printf("%d", num);
      *shm_addr2_2 = num;
      sleep(1);
      sem_post(sem1);
      sem_post(sem2);

      // second -RW
      sem_wait(sem3);
      sem_wait(sem4);
      printf("here4\n");
      num = *shm_addr2_2;
      num++;
      *shm_addr2_1 = num;

      sleep(1);

      sem_post(sem3);
      sem_post(sem4);
    } else { // process 3
      // first - read
      sem_wait(sem3);
      printf("here5\n");
      num = *shm_addr2_2;
      printf("%d h\n", num);
      sleep(1);
      sem_post(sem3);

      // second - read
      sem_wait(sem4);
      printf("here6\n");
      num = *shm_addr2_2;
      printf("%d i\n", num);
      sleep(1);
      sem_post(sem4);
    }
  }

  // Clean up
  munmap(shm_addr1, SHM_SIZE);
  munmap(shm_addr2, SHM_SIZE);
  close(shm_fd1);
  close(shm_fd2);
  shm_unlink(SHM_NAME);
  sem_close(sem1);
  sem_close(sem2);
  sem_close(sem3);
  sem_close(sem4);
  sem_unlink(SEM_NAME1);
  sem_unlink(SEM_NAME2);
  sem_unlink(SEM_NAME3);
  sem_unlink(SEM_NAME4);

  return 0;
}
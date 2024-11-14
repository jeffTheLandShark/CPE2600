/*
* File: sysPrintf.c
* @brief Prints using sample system call
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main() {
    int x = 15;

    printf("x value is %d\n", x);

    // syscall version
    const char *message = "Hello, world!\n";
    syscall(SYS_write, STDOUT_FILENO, message, 14);
    syscall(1, 1, message, 14);

    return 0;
}
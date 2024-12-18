// Create a program in C to implement a multi-process environment and print Hello from the parent process and Hi from the child process.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    switch (pid) {
        case -1:
            perror("Fork failed");
            return 1;
        case 0:
            printf("Hi from the child process\n");
            break;
        default:
            wait(NULL);
            printf("Hello from the parent process\n");
            break;
    }

    return 0;
}
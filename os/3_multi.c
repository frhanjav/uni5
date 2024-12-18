// Create a program in C to implement a multi-process environment and print Hello from the parent process and Hi from the child process and before exiting they have to say goodbye. But the parent must wait for the child to complete its execution.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    switch (pid) {
        case -1:
            perror("Fork failed");
            exit(1);
            break;
        case 0:
            printf("Hi from the child process\n");
            printf("Goodbye from the child process\n");
            exit(0);
            break;
        default:
            wait(NULL);
            printf("Hello from the parent process\n");
            printf("Goodbye from the parent process\n");
            break;
        }

    return 0;
    }
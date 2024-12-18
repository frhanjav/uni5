// Create a program in C to implement a multi-process environment and print Hello from all the processes.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int n = 5;

    for (int i = 0; i < n; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            printf("Hello from process %d\n", getpid());
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}
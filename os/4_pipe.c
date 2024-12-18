// Create a program in C to implement a multi-process environment and pass messages among them using pipe(). Print from 1 to 100 by printing alternative numbers by the processes.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];
    int pipe2[2]; 
    int i;
    int num = 1;
    
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe Failure");
        exit(EXIT_FAILURE);
    }

    close(pipe1[1]);    
    close(pipe2[0]); 

    write(pipe1[1], &num, sizeof(num));

    close(pipe1[0]);
    close(pipe2[1]); 

    i = 0;

    while (i <= 100) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {  // Child process
            close(pipe1[1]);
            close(pipe2[0]); 
            int buff;
            read(pipe1[0], &buff, sizeof(buff));
            if(buff%2==0 && buff>0) printf("Child: %d\n", buff);

            i++;
            buff++;
            write(pipe2[1], &buff, sizeof(buff));

            close(pipe1[0]); 
            close(pipe2[1]); 

            exit(0);
        } else {
            wait(NULL);
            close(pipe1[1]);
            close(pipe2[0]);
            int buff;

            read(pipe2[0], &buff, sizeof(buff));
            if(buff%2!=0) printf("Parent: %d\n", buff);

            i++;
            buff++;
            write(pipe1[1], &buff, sizeof(buff));

            close(pipe1[0]);
            close(pipe2[1]);

        }
    }

    close(pipe1[1]);
    close(pipe2[0]);

    return 0;
}
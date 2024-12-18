#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; // Pipe for parent to child (initial value)
    int pipe2[2]; // Pipe for child to parent (incremented value)
    int i;
    int num = 1;
    // Create the pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe Failure");
        exit(EXIT_FAILURE);
    }

    close(pipe1[1]); // Close write end of the first pipe
    close(pipe2[0]); // Close read end of the second pipe

    // Write the incremented value back to the parent
    write(pipe1[1], &num, sizeof(num));

    close(pipe1[0]); // Close read end of the first pipe
    close(pipe2[1]); // Close write end of the second pipe

    // Initialize i with 1
    i = 1;

    while (i <= 100) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {  // Child process
            close(pipe1[1]); // Close write end of the first pipe
            close(pipe2[0]); // Close read end of the second pipe
            int buff;
            // Read the number from the parent
            read(pipe1[0], &buff, sizeof(buff));
            if(buff%2!=0) printf("Child: %d\n", buff);

            // Increment the number
            i++;
            buff++;
            // Write the incremented value back to the parent
            write(pipe2[1], &buff, sizeof(buff));

            close(pipe1[0]); // Close read end of the first pipe
            close(pipe2[1]); // Close write end of the second pipe
            // sleep(1);
            exit(0); // Exit child process
        } else {  // Parent process
            wait(NULL);
            close(pipe1[1]); // Close write end of the first pipe
            close(pipe2[0]); // Close read end of the second pipe
            int buff;
            // Read the number from the parent
            read(pipe2[0], &buff, sizeof(buff));
            if(buff%2==0) printf("Parent: %d\n", buff);

            // Increment the number
            i++;
            buff++;
            // Write the incremented value back to the parent
            write(pipe1[1], &buff, sizeof(buff));

            close(pipe1[0]); // Close read end of the first pipe
            close(pipe2[1]); // Close write end of the second pipe

        }
    }

    // Close remaining pipe ends
    close(pipe1[1]); // Close write end of the first pipe in the parent
    close(pipe2[0]); // Close read end of the second pipe in the parent

    return 0;
}

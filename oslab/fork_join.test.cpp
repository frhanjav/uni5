#include<iostream>
#include<unistd.h>
#include<sys/wait.h>

int main () {
    switch(int child_pid = fork()){
        case -1:
            std::cout << "Child Creation Failure\n";
            break;
        case 0:
            std::cout << "Child: Hello ! \n";
            break;
        default:
            std::cout << "Parent: Hello \n";
    }
}
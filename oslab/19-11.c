#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

// 1 - 100 var decl before loop print after loop

int main(){
    int pid;

    for(int i=1; i<=3;i++){
        switch(pid = fork()){
            case -1:
                printf("Fork Failed\n");
                break;
            case 0:
                printf("Child: %d\n", i);
                break;
            default:
                printf("Parent: %d\n", i);
        }
    }
    
    return 0;
}
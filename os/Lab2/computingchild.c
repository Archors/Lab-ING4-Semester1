#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define KEY 4567
#define PERMS 0660

int main(int argc, char **argv) 
{
    int id;
    int id2;
    int i;
    int *ptr;
    int *ptr2;
    int a=1;
    int b=2;
    int c=3;
    int d=4;
    int total=0;
    ptr = (int *) shmat(id, NULL, 0);
    ptr2 = (int *) shmat(id2, NULL, 0);
    if (fork() == 0) //Creating a child process
    {//Parent
        *ptr = a+b;
        *ptr2 = c+d;
        exit(0);
    }
    else 
    { //Child
        wait(NULL); //Wait until the parent process finish
        total = *ptr - *ptr2;
        printf("%d",total);
        hmctl(id, IPC_RMID, NULL); //Function of control of the memory
    }
}

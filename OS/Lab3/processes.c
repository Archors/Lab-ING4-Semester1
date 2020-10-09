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
    int id, id2, id3;
    int *ptr, *ptr2, *ptr3;
    int total;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;

    id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS); //Create an IPC of 4 bytes (=sizeof int) with shared memory (=allocate shared memory) (id)
    id2 = shmget(KEY+1, sizeof(int), IPC_CREAT | PERMS); //We change the key to avoid having a conflict with ptr
    id3 = shmget(KEY+2, sizeof(int), IPC_CREAT | PERMS);
    


    ptr = (int *) shmat(id, NULL, 0); //Attach an existing shared memory (id) to an adress space (ptr)
    ptr2 = (int *) shmat(id2, NULL, 0);
    ptr3 = (int *) shmat(id2, NULL, 0);
    
    if (fork() == 0) //Creating a child process
    {//Parent
        if (fork() == 0)
        {
            (*ptr) = a + b;
            exit(0);
        }
        else
        {
            (*ptr2) = c - d;
            wait(NULL);
        }
        
        (*ptr3) = e + f;
        exit(0); //Close the parent process
    }
    else 
    { //Child
        wait(NULL); //Wait until the parent process finish
        total = (*ptr) * (*ptr2) - (*ptr3);
        printf("Value of the equation (a + b) * (c - d) + (e + f) = %d\n", total); //Print the value of the total
        exit(0);
    }
}

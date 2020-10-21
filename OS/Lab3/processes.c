#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#define KEY 4567
#define PERMS 0660

int main(int argc, char **argv)
{
    time_t seconds;
    int iterator = 0;
    int id, id2, id3, id4;
    int *ptr, *ptr2, *ptr3, *ptr4;
    int total;
    int a = 1, b = 2, c = 3, d = 4, e = 6, f = 5, g = 7, h = 8;
    seconds = time(NULL);

    id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS); //Create an IPC of 4 bytes (=sizeof int) with shared memory (=allocate shared memory) (id)
    id2 = shmget(KEY+1, sizeof(int), IPC_CREAT | PERMS); //We change the key to avoid having a conflict with ptr
    id3 = shmget(KEY+2, sizeof(int), IPC_CREAT | PERMS);
    id4 = shmget(KEY+3, sizeof(int), IPC_CREAT | PERMS);


    ptr = (int *) shmat(id, NULL, 0); //Attach an existing shared memory (id) to an adress space (ptr)
    ptr2 = (int *) shmat(id2, NULL, 0);
    ptr3 = (int *) shmat(id3, NULL, 0);
    ptr4 = (int *) shmat(id4, NULL, 0);

    for(iterator = 0 ; iterator < 65000 ; iterator++)
    {
    if (fork() == 0) //Creating a child process
    {//Parent
        if (fork() == 0)
        {
            (*ptr) = a + b;
            exit(0);
        }
        else
        {
          wait(NULL);
          (*ptr2) = c * d;
        }

        (*ptr3) = e - f;
        exit(0); //Close the parent process
        wait(NULL); //Wait until the parent process finish

    }
    else
    { //Child
        if (fork() == 0)
        {
            (*ptr4) = g + h;
            exit(0);
        }
        else
        {
            wait(NULL);
            (*ptr2) = (*ptr2) / (*ptr3);
        }
        (*ptr) = (*ptr) - (*ptr2);

    }
    total = (*ptr) + (*ptr3);
    }
    seconds -= time(NULL);
    printf("%ld",seconds);
}

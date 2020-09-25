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
    int *ptr;
    system("ipcs -m"); //Show stats of IPCs
    id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS); //Create an IPC of 4 bytes (=sizeof int) with shared memory (=allocate shared memory) (id)
    system("ipcs -m"); //Show again stats of IPCs because we just created another
    ptr = (int *) shmat(id, NULL, 0); //Attach an existing shared memory (id) to an adress space (ptr)
    *ptr = 54;i = 54;
    if (fork() == 0) //Creating a child process
    {//Parent
        (*ptr)++;i++; //Increment *ptr and i in the parent
        printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i); //Print the value of *ptr and i
        exit(0); //Close the parent process
    }
    else 
    { //Child
        wait(NULL); //Wait until the parent process finish
        printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i); //Print the value of *ptr and i
        shmctl(id, IPC_RMID, NULL); //Function of control of the memory
    }
}

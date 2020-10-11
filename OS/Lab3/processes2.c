//#define __USE_GNU
#include <sys/times.h>
#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define KEY 4567
#define PERMS 0660

clock_t times(struct tms *buf); 

int main(int argc, char **argv) 
{
    struct tms start, end;
    struct rusage rstart, rend;
    int iterator = 0;
    int id, id2, id3, id4;
    int *ptr, *ptr2, *ptr3, *ptr4;
    int total;
    int a = 1, b = 2, c = 3, d = 4, e = 6, f = 5, g = 7, h = 8;

    times(&start);
    getrusage(RUSAGE_SELF, &rstart);
    id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS); //Create an IPC of 4 bytes (=sizeof int) with shared memory (=allocate shared memory) (id)
    id2 = shmget(KEY+1, sizeof(int), IPC_CREAT | PERMS); //We change the key to avoid having a conflict with ptr
    id3 = shmget(KEY+2, sizeof(int), IPC_CREAT | PERMS);
    id4 = shmget(KEY+3, sizeof(int), IPC_CREAT | PERMS);
    

    ptr = (int *) shmat(id, NULL, 0); //Attach an existing shared memory (id) to an adress space (ptr)
    ptr2 = (int *) shmat(id2, NULL, 0);
    ptr3 = (int *) shmat(id3, NULL, 0);
    ptr4 = (int *) shmat(id4, NULL, 0);
    
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
    }
    else 
    { //Child
    getrusage(RUSAGE_CHILDREN, &rend);
        wait(NULL); //Wait until the parent process finish
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
    times(&end);
    printf("%lf usec\n", (end.tms_utime+end.tms_stime-start.tms_utime-start.tms_stime)*1000000.0/sysconf(_SC_CLK_TCK));
  
  printf("%ld usec\n", (rend.ru_utime.tv_sec-rstart.ru_utime.tv_sec)*1000000 +(rend.ru_utime.tv_usec-rstart.ru_utime.tv_usec)+(rend.ru_stime.tv_sec-rstart.ru_stime.tv_sec)*1000000 +(rend.ru_stime.tv_usec-rstart.ru_stime.tv_usec));

    return 0;
}

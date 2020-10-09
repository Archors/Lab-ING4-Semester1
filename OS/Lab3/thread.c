#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int a, b;
} thread_data;


void *calculation1(void *args)
{
    thread_data *data = args;
    //int a = args.a + args.b;
    //pthread_exit(a);
}

int main()
{
    pthread_t thread[4];
    int iret1, iret2, iret3, iret4;
    int *ptr, *ptr2, *ptr3, *ptr4;

    thread_data data[4];
    data[0].a = 1;
    data[0].b = 2;
    data[1].a = 3;
    data[1].b = 4;
    data[2].a = 5;
    data[2].b = 6;
    data[3].a = 7;
    data[3].b = 8;

    //Creation of independant thread
    pthread_create( &thread[0], NULL, calculation1, (void*) data);
    pthread_join(thread[0], (void **) &ptr);

    printf("Resultat du calcul : %d", *ptr);
    return 0;
}
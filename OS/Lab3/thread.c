#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int a, b;
  int res;
} thread_data;


void *add(void *received_struct)
{
  thread_data *data = (thread_data*) received_struct;
  data->res = data->a + data->b;
  pthread_exit(NULL);
}

void *sub(void *received_struct)
{
  thread_data *data = (thread_data*) received_struct;
  data->res = data->a - data->b;
  pthread_exit(NULL);
}

void *mul(void *received_struct)
{
  thread_data *data = (thread_data*) received_struct;
  data->res = data->a * data->b;
  pthread_exit(NULL);
}

void *divi(void *received_struct)
{
  thread_data *data = (thread_data*) received_struct;
  data->res = data->a / data->b;
  pthread_exit(NULL);
}

int main()
{
    pthread_t thread[8]; //Different threads
    thread_data data[8]; //data to calculate in threads
    int res; //results
    int j = 0;
    int iterator = 0;
    time_t seconds;

    for(j=0;j<8;j++)
    {
      data[j].a=0;rk
      data[j].b=0;
      data[j].res=0;

    }
    data[0].a = 1;
    data[0].b = 2;
    data[1].a = 3;
    data[1].b = 4;
    data[2].a = 6;
    data[2].b = 5;
    data[3].a = 7;
    data[3].b = 8;

    seconds = time(NULL);
    //Creation of independant thread
    for(iterator=0 ; iterator < 65000 ; iterator++)
    {
      pthread_create( &(thread[0]), NULL, add, &data[0]);
      pthread_create( &(thread[1]), NULL, mul, &data[1]);
      pthread_create( &(thread[2]), NULL, sub, &data[2]);
      pthread_create( &(thread[3]), NULL, add, &data[3]);
      data[4].a = data[1].res;
      data[4].b = data[2].res;
      pthread_create( &(thread[4]), NULL, divi, &data[4]);
      data[5].a = data[0].res;
      data[5].b = data[4].res;
      pthread_create( &(thread[5]), NULL, sub, &data[5]);


      //Joining threads
      pthread_join(thread[0], NULL);
      pthread_join(thread[1], NULL);
      pthread_join(thread[2], NULL);
      pthread_join(thread[3], NULL);
      pthread_join(thread[4], NULL);
      pthread_join(thread[5], NULL);
      res = data[5].res + data[3].res;
    }

    seconds -= time(NULL);

    printf("Temps %ld", seconds);
    return 0;
}

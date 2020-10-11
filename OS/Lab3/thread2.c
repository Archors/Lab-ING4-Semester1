#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <sys/resource.h>


typedef struct {
  int a, b;
  int res;
} thread_data;

clock_t times(struct tms *buf); 

struct tms start, end;
  struct rusage rstart, rend;

void *add(void *received_struct)
{
    thread_data *data = (thread_data*) received_struct;
    data->res = data->a + data->b;
    getrusage(RUSAGE_THREAD, &rstart);
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
  times(&start);
    pthread_t thread[8]; //Different threads
    thread_data data[8]; //data to calculate in threads
    int res; //results
    int j = 0;
    int iterator = 0;

    for(j=0;j<8;j++)
    {
      data[j].a=0;
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
    
    //Creation of independant thread
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
      times(&end);
  getrusage(RUSAGE_SELF, &rend);

  printf("%lf usec\n", (end.tms_utime+end.tms_stime-start.tms_utime-start.tms_stime)*1000000.0/sysconf(_SC_CLK_TCK));
  
  printf("%ld usec\n", (rend.ru_utime.tv_sec-rstart.ru_utime.tv_sec)*1000000 +(rend.ru_utime.tv_usec-rstart.ru_utime.tv_usec)+(rend.ru_stime.tv_sec-rstart.ru_stime.tv_sec)*1000000 +(rend.ru_stime.tv_usec-rstart.ru_stime.tv_usec));


    return 0;
}
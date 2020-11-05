#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

sem_t first;
sem_t second;
sem_t third;

typedef struct {
  int a, b, c, d, e, f;
  int tab[5];
} thread_data;

void *T1(void *received_struct)
{
  thread_data *data = (thread_data*) received_struct;
  data->tab[0] = data->a + data->b;
  sem_post(&first);
  pthread_exit(EXIT_SUCCESS);
}

void *T2(void *received_struct)
{
  thread_data *data = (thread_data*) received_struct;
  data->tab[1] = data->c + data->d;
  sem_post(&second);
  pthread_exit(EXIT_SUCCESS);
}

void *T3(void *received_struct)
{
  thread_data *data = (thread_data*) received_struct;
  data->tab[2] = data->e + data->f;
  sem_post(&third);
  pthread_exit(EXIT_SUCCESS);
}

void *T4(void *received_struct)
{
  int tmp = 0;
  thread_data *data = (thread_data*) received_struct;
  while(tmp != 1){
    sem_wait(&first);
    
  }
  pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  pthread_t thread[4];
  thread_data data;
  //Creating semaphore
  sem_init(&first,0,0);
  sem_init(&second,0,0);
  sem_init(&third,0,0);
  pthread_create( &(thread[0]), NULL, T1, &data);
  pthread_create( &(thread[1]), NULL, T2, &data);
  pthread_create( &(thread[2]), NULL, T3, &data);

  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);
  pthread_join(thread[2], NULL);
}

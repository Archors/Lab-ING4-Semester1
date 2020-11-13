#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

sem_t finish;
sem_t order;

typedef struct
{
  int a, b, c, d, e, f;
  int order;
  int tab[3];
  int result;
} thread_data;

void *T1(void *received_struct)
{
  thread_data *data = (thread_data *)received_struct;
  int temp = data->a + data->b;
  sem_wait(&order);              //Part of code that can't be accessed  by multiple threads at the same time
  data->tab[data->order] = temp; //The first available spot in the array is filled by the result
  (data->order)++;               //Increase to know the new first available spot
  sem_post(&order);              //Release of this part
  sem_post(&finish);             //Tell others threads that the calculation is complete
  pthread_exit(EXIT_SUCCESS);
}

void *T2(void *received_struct)
{
  thread_data *data = (thread_data *)received_struct;
  int temp = data->c + data->d;
  sem_wait(&order);
  data->tab[data->order] = temp;
  (data->order)++;
  sem_post(&order);
  sem_post(&finish);
  pthread_exit(EXIT_SUCCESS);
}

void *T3(void *received_struct)
{
  thread_data *data = (thread_data *)received_struct;
  int temp = data->e + data->f;
  sem_wait(&order);
  data->tab[data->order] = temp;
  (data->order)++;
  sem_post(&order);
  sem_post(&finish);
  pthread_exit(EXIT_SUCCESS);
}

void *T4(void *received_struct)
{
  thread_data *data = (thread_data *)received_struct;
  int temp;
  sem_wait(&finish);                  //Wait for the first thread to finish
  sem_wait(&finish);                  //wait for the second thread to finish
  temp = data->tab[0] * data->tab[1]; //Calculation
  sem_wait(&finish);                  //Wait for the last thread to finish
  data->result = temp * data->tab[2]; //Complete calculation
  pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
  pthread_t thread[4];
  thread_data data;
  data.order = 0;
  //Creating semaphore
  sem_init(&order, 0, 0);
  sem_init(&finish, 0, 0);
  pthread_create(&(thread[0]), NULL, T1, &data);
  pthread_create(&(thread[1]), NULL, T2, &data);
  pthread_create(&(thread[2]), NULL, T3, &data);
  pthread_create(&(thread[3]), NULL, T4, &data);
  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);
  pthread_join(thread[2], NULL);
  pthread_join(thread[3], NULL);
}

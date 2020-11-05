#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *increment(void *received_data)
{
  int *data = (int*) received_data;
  (*data)++;
  pthread_exit(NULL);
}

void *decrement(void *received_data)
{
  int *data = (int*) received_data;
  (*data)++;
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t thread[2];
  int i = 65;
  pthread_create( &(thread[0]), NULL, increment, &i);
  pthread_create( &(thread[1]), NULL, decrement, &i);

  pthread_join(thread[0], NULL);
  printf("%d\n",i);
  pthread_join(thread[1], NULL);
  printf("%d\n",i);
}

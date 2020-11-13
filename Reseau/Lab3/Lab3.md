# Lab3: Computer Networks

[Subject](os-lab()-subject.pdf)

* Running a file : `gcc -g webserver webserver.c`
* Then use `./execName` to display results.

#### 1-  Objective

1. Socket network programming
2. Review client/server approach.
Each group (composed of 3 students at most) shall submit a report in campus.
The report (PDF format is accepted) shall be uploaded on the campus page before the deadline
November 22 at 23h55.
The source code and the exec files of the server (websrv.c and websrv) as well as the index.html
should be zipped in one file. Please propose a small html file.

#### 2-  Web server

1. Explain why we are using the library `<netinet/in.h >`
`<netinet/in.h >` is an internet protocol family, we are using it to include the `sockaddr` structure or to use `in_` that are defined with `typedef`.

2. Add the following line: `return EXIT_SUCCESS`, compile and execute the server code. What is the required Linux command line and the name of the Compiler.
The command line to compile is `gcc -g webserver webserver.c` and the command line to execute is `./webserver`

##### What if we had more than two processes ? Is there something else to do to enforce mutual exclusion ? Explain and experiment using three processes.

If there are more than two processes we can't be sure which one of the three we can enforce mutual exclusion by adding empty/full.
```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>


sem_t *empty;
sem_t *full;

void *increment(void *received_data)
{
  sem_wait(&empty);
  int *data = (int*) received_data;
  (*data)++;
  sem_post(&full);
  pthread_exit(EXIT_SUCCESS);
}

void *decrement(void *received_data)
{
  sem_wait(&full);
  int *data = (int*) received_data;
  (*data)++;
  sem_post(&full);
  pthread_exit(EXIT_SUCCESS);
}
void *multiple(void *received_data)
{
  sem_wait(&full);
  int *data = (int*) received_data;
  (*data)*2;
  sem_post(&full);
  pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  pthread_t thread[3];
  //Creating semaphore
  sem_init(&empty,0,1);
  sem_init(&full,0,0);  

  int i = 65;
  pthread_create( &(thread[0]), NULL, increment, &i);
  pthread_create( &(thread[1]), NULL, decrement, &i);
  pthread_create( &(thread[2]), NULL, decrement, &i);
  printf("%d\n",i);
  pthread_join(thread[0], NULL);
  printf("%d\n",i);
  pthread_join(thread[1], NULL);
  pthread_join(thread[2], NULL);
}
```

2. A deadlock is a situation in which a process is waiting for some resource held by another
process waiting for it to release another resource, thereby forming a loop of blocked
processes ! Use semaphores to force a deadlock situation using three processes.

```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>

sem_t first;
sem_t second;
sem_t third;

void *increment(void *received_data)
{
  sem_wait(&second);
  int *data = (int*) received_data;
  (*data)++;
  sem_post(&first);
  pthread_exit(EXIT_SUCCESS);
}

void *decrement(void *received_data)
{
  sem_wait(&third);
  int *data = (int*) received_data;
  (*data)++;
  sem_post(&second);
  pthread_exit(EXIT_SUCCESS);
}
void *multiple(void *received_data)
{
  sem_wait(&first);
  int *data = (int*) received_data;
  (*data)*2;
  sem_post(&third);
  pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  pthread_t thread[3];
  //Creating semaphore
  sem_init(&first,0,0);
  sem_init(&second,0,0);
  sem_init(&third,0,0);
  int i = 65;
  pthread_create( &(thread[0]), NULL, increment, &i);
  pthread_create( &(thread[1]), NULL, decrement, &i);
  pthread_create( &(thread[2]), NULL, multiple, &i);
  printf("%d\n",i);
  pthread_join(thread[0], NULL);
  printf("%d\n",i);
  pthread_join(thread[1], NULL);
  pthread_join(thread[2], NULL);
}
```

Here we have a deadlock situation, each thread is waiting for another thread to complete his task (1 waiting for 2 ; 2 waiting for 3 ; 3 waiting for 1).

3. Use semaphores to run 3 different applications (firefox, emacs, vi) in a predefined sequence
no matter in which order they are launched.

```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

sem_t first;
sem_t second;
sem_t third;

void *vim()
{
  system("/usr/bin/vim");
  sem_post(&first);
  pthread_exit(EXIT_SUCCESS);
}

void *firefox()
{
  sem_wait(&first);
  system("/usr/bin/firefox");
  sem_post(&second);
  pthread_exit(EXIT_SUCCESS);
}

void *emacs()
{
  sem_wait(&second);
  system("/usr/bin/emacs");
  pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  pthread_t thread[3];
  //Creating semaphore
  sem_init(&first,0,0);
  sem_init(&second,0,0);
  sem_init(&third,0,0);

  pthread_create( &(thread[0]), NULL, vim, NULL);
  pthread_create( &(thread[1]), NULL, firefox, NULL);
  pthread_create( &(thread[2]), NULL, emacs, NULL);
  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);
  pthread_join(thread[2], NULL);
}
```

4. Use sempahores to implement the following parallelized calculation `(a+b)*(c-d)*(e+f)`
* T1 runs `(a+b)` and stores the result in a shared table (1st available spot)
* T2 runs `(c+d)` and stores the result in a shared table (1st available spot)
* T3 runs `(e+f)` and stores the result in a shared table (1st available spot)
* T4 waits for two tasks to end and does the corresponding calculation
* T4 waits for the remaining task to end and does the final calculation then displays the result

```

```

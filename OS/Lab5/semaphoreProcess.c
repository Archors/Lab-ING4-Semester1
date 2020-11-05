#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  int i = 65;
  if(fork())
  {
    i++;
  }
  else{
    i--;
  }
  printf("%d\n", i);
}

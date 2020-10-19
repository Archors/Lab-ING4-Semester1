#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  unsigned int end = 0;
  while (end != 1) {
    int ftext1 = open("text1", O_APPEND); //We open text1 in read mode
    int ftext2 = open("text2", O_WRONLY); //We open text2 in write mode
    int copy = dup2(ftext2,STDOUT_FILENO); //We redirect the standart output to
    printf("test");
    end = 1;
  }
}

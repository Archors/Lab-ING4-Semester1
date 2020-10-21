#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>


int main() {
  int i;
  char buf[100];
  // ouvrir un le stdin en lecture non bloquante
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); //Set the stdin status flag to 0_NONBLOCK (it can't be stoped)
  for (i = 0; i < 10; i++) {
    int nb;
    nb = read(STDIN_FILENO, buf, 100); //Read the user input
    printf("nwrites = %d\terror = %d\n", nb, errno); //print the number of character and errors
  }
}

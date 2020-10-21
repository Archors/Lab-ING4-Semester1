#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int pipefd[2];
  pid_t cpid;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (cpid == 0) {    /* Child reads from pipe */
    close(pipefd[1]); //close pipe write end
    dup2(STDIN_FILENO,pipefd[0]); //redirect stdin into the pipe
    system("more"); //execute more
    close(pipefd[0]);
    exit(EXIT_SUCCESS);
  } else { //parent
    /* Parent writes argv[1] to pipe */
    close(pipefd[0]); //close pipe read end
    dup2(STDOUT_FILENO,pipefd[1]); //redirect stdin into the pipe
    system("ps aux");
    close(pipefd[1]);
    /* Reader will see EOF */
    wait(NULL);
    /* Wait for child */
    exit(EXIT_SUCCESS);
  }
}

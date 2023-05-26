#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

int pipes[2];

void l_pipe(int pipe_fd[]) {
  close(pipe_fd[0]);                // cerramos lectura
  dup2(pipe_fd[1], STDOUT_FILENO);  // reemplazamos stdout por pipe_write
  execlp("ls", "ls", "-al", NULL);  // ejecutamos
}

void r_pipe(int pipe_fd[]) {
  close(pipe_fd[1]);                // cerramos escritura
  dup2(pipe_fd[0], STDIN_FILENO);   // reemplazamos stdin por pipe_read
  execlp("ls", "ls", "-al", NULL);  // ejecutamos
}

int main(int argc, char const* argv[]) {
  pipe(pipes); // creamos los fd para el pipe
  pid_t lp_pid = fork(); 
  if (lp_pid == 0) {
    l_pipe(pipes);
  }
  pid_t rp_pid = fork();
  if (rp_pid == 0) {
    r_pipe(pipes);
  } 
  exit(EXIT_SUCCESS);
}

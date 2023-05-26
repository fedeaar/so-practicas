#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define SIGHUP 1
#define SIGINT 2

enum {
    READ,
    WRITE
};


int pipe_fd[2];
pid_t padre;
pid_t hijo;


void sighup_handler_h(int signal) {
    char* msg = "Me voy a mirar crecer las flores desde abajo.\n";
    dprintf(STDOUT_FILENO, msg);
    exit(EXIT_SUCCESS);
}

void sigint_handler_h(int signal) {
    char* msg = "Dejame pensarlo...\n";
    dprintf(STDOUT_FILENO, msg);
    sleep(5);
    msg = "Ya sé el significado de la vida.\n";
    dprintf(STDOUT_FILENO, msg);
    int sig = 42;
    write(pipe_fd[WRITE], &sig, sizeof(sig));
    kill(padre, SIGINT);
}

void sigint_handler_p(int signal) {
    int sig;
    read(pipe_fd[READ], &sig, sizeof(sig));
    dprintf(STDOUT_FILENO, "Mirá vos. El significado de la vida es %d.\n", sig);
    char* msg = "¡Bang Bang, estás liquidado!\n";
    dprintf(STDOUT_FILENO, msg);
    kill(hijo, SIGHUP);
    wait(NULL);
    msg = "Te voy a buscar en la oscuridad.\n";
    dprintf(STDOUT_FILENO, msg);
    close(pipe_fd[READ]);
}

int main(int argc, char const *argv[]) 
{   
    pipe(pipe_fd);
    hijo = fork();
    if (hijo == 0) {
        close(pipe_fd[READ]);
        padre = getppid();
        signal(SIGINT, sigint_handler_h);
        signal(SIGHUP, sighup_handler_h);
        while (1);
    } else {
        close(pipe_fd[WRITE]);
        signal(SIGINT, sigint_handler_p);
        sleep(1);
        char* msg = "¿Cuál es el significado de la vida?\n";
        dprintf(STDOUT_FILENO, msg);
        kill(hijo, SIGINT);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}

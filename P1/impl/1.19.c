#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

enum {
    READ,
    WRITE
};

enum {
    PADRE,
    HIJO1,
    HIJO2
};

int pipes[3][2];

void chain(int pipes[][2], int proceso) {
    // cerramos pipes que no usamos
    for (int i = 0; i < 3; ++i) {
        if (i != proceso) {
            close(pipes[i][WRITE]);
            close(pipes[(3 + i-1) % 3][READ]);
        }
    }
    int val;
    while (1) {
        read(pipes[(3 + proceso-1) % 3][READ], &val, sizeof(val));
        ++val;
        if (val > 50) {
            break;
        }
        dprintf(STDOUT_FILENO, "proceso: %d, valor: %d\n", proceso, val);
        write(pipes[proceso][WRITE], &val, sizeof(val));
    }
}

int main() {
    // creamos pipes
    for (int i = 0; i < 3; ++i) {
        pipe(pipes[i]);
    }
    pid_t h1_pid = fork();
    if (h1_pid == 0) { 
        // proceso hijo 1
        chain(pipes, HIJO1);
        exit(EXIT_SUCCESS);
    }
    pid_t h2_pid = fork();
    if (h2_pid == 0) {
        // proceso hijo 2
        chain(pipes, HIJO2);
        exit(EXIT_SUCCESS);
    }
    // proceso padre
    int val = 0;
    dprintf(STDOUT_FILENO, "proceso: %d, valor: %d\n", PADRE, val);
    write(pipes[PADRE][WRITE], &val, sizeof(val));
    chain(pipes, PADRE);
    exit(EXIT_SUCCESS);
}

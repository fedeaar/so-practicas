#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

#define READ  0
#define WRITE 1

#define N 4
#define M 3
#define PROCESADORES 8
#define ARCHIVO "hola.txt"


int pipes_ida[PROCESADORES][2];
int pipes_vta[PROCESADORES][2];
pid_t pid_hijos[PROCESADORES];


void subproceso(int proceso) {
    // cerramos pipes que no usamos
    for (int i = 0; i < PROCESADORES; ++i) {
        if (i != proceso) {
            close(pipes_ida[i][READ]);
            close(pipes_vta[i][WRITE]);
        }
        close(pipes_ida[i][WRITE]);
        close(pipes_vta[i][READ]);
    }
    int fila[M];
    int promedio = 0;
    while (1) {
        read(pipes_ida[proceso][READ], &fila, sizeof(fila));
        promedio = calcular_promedio(&fila);
        write(pipes_vta[proceso][WRITE], &promedio, sizeof(promedio));
    }
}

int main() {
    // creamos pipes
    for (int i = 0; i < PROCESADORES; ++i) {
        pipe(pipes_ida[i]);
        pipe(pipes_vta[i]);
    }
    // creamos hijos
    for (int i = 0; i < PROCESADORES; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            subproceso(i);
        }
        pid_hijos[i] = pid;
    }
    // enviamos data
    int fd = open(ARCHIVO); 
    int fila[M]; 
    int i = 0;
    while (cargar_fila(fd, &fila)) {
        write(pipes_ida[i][WRITE], &fila, sizeof(fila));
        i = (i + 1) % PROCESADORES;    
    }
    // leemos data
    int resultado[N];
    int n = 0;
    for (int i = 0; i < PROCESADORES; ++i) {
        int leer = 0;
        if (read(pipes_vta[i][READ], &leer, sizeof(int)) == -1) {
            exit(EXIT_FAILURE);
        };
        read(pipes_vta[i][READ], (&resultado + n), leer * sizeof(int));
        n += leer;
    }
    // close pipes
    // ...
    // sort(resultado);
    // write resultado a stdout
    // ...
    exit(EXIT_SUCCESS);
}

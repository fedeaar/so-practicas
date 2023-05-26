#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void bart() {
    char mensaje[] = "Soy Bart Simpson\n";
    write(1, mensaje, sizeof(mensaje));
    exit(EXIT_SUCCESS);
}

void lisa() {
    char mensaje[] = "Soy Lisa Simpson\n";
    write(1, mensaje, sizeof(mensaje));
    exit(EXIT_SUCCESS);
}

void maggie() {
    char mensaje[] = "Soy Maggie Simpson\n";
    write(1, mensaje, sizeof(mensaje));
    exit(EXIT_SUCCESS);
}

void homero() {
    pid_t pid = fork();
    if (pid == 0) {
        bart();
    } else {
        wait();
    }
    pid = fork();
    if (pid == 0) {
        lisa();
    } else {
        wait();
    }
    pid = fork();
    if (pid == 0) {
        maggie();
    } else {
        wait();
    }
    char mensaje[] = "Soy Homero, hijo de Abraham\n";
    write(1, mensaje, sizeof(mensaje));
    exit(EXIT_SUCCESS);
}

void abraham() {
    wait();
    char mensaje[] = "Soy el abuelo, Abraham Simpson\n";
    write(1, mensaje, sizeof(mensaje));
    exit(EXIT_SUCCESS);
}


int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if (pid == 0) {
        homero();
    } else {
        abraham();
    }
}

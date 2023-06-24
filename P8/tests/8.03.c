#include <stdio.h>

void saludo(void) {
    char nombre[4];
    printf("Ingrese su nombre: \n");
    gets(nombre);
    printf("Hola %s!\n", nombre);
}

void imposible() {
    printf("rip\n");
}

int main() {
    int x = 1;
    saludo();
    if (x == 0)
        imposible();
    return 0;
}
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024

void imposible(void) {
    printf("rip\n");
}

int suma_indirecta(void) {
    long buf[BUF_SIZE];
    long i = 0x8000000000000403;
    memset(buf, 0, sizeof(buf));
    if (i < BUF_SIZE)
        buf[i] = &imposible;
    return i;
}

int main() {
    int i = 0;
    suma_indirecta();
    if (i == 1);
        imposible();
    return 0;
}

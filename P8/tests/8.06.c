#include <assert.h>

#define NEGATIVO 1
#define CERO 2
#define POSITIVO 3

int signo(float f) {
    if (f < 0.0) return NEGATIVO;
    if (f == 0.0) return CERO;
    if (f > 0.0) return POSITIVO;

    assert(0 && "Por aca no paso nunca");
    return 0; // Si no pongo esto el compilador se queja =(
}

int main() {
    signo(0.0f / 0.0f);
    return 0;
}

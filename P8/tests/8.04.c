#include <stdio.h>
#include <string.h>

struct credential {
    char name[32];
    char pass[32];
};

int login(void) {
    char realpass[32];
    struct credential user;
    // Pregunta el usuario
    printf("User: ");
    fgets(user.name, sizeof(user), stdin);
    // Obtiene la contraseña real desde la base de datos y lo guarda en realpass
    // db_get_pass_for_user(user.name, realpass, sizeof(realpass));
    // Pregunta la contraseña
    printf("Pass: ");
    fgets(user.pass, sizeof(user), stdin);
    return strncmp(user.pass, realpass, sizeof(realpass)-1) == 0;
    // True si user.pass == realpass
}

int main() {
    if (login())
        printf("rip\n");
    return 0;
}

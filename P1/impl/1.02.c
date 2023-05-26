/* defines */

// PCB
typedef struct {
    int STAT;
    int P_ID;
    int PC;
    int R0;
    int R1;
    int R2;
    int R3;
    int R4;
    int R5;
    int R6;
    int R7;
    int R8;
    int R9;
    int R10;
    int R11;
    int R12;
    int R13;
    int R14;
    int R15;
    int CPU_TIME;
} PCB;
enum STAT {
    KE_RUNNING,
    KE_READY,
    KE_BLOCKED,
    KE_NEW
};

// fns
int ke_current_user_time(); 
void ke_reset_current_user_time();
void ret();
void set_current_process(int pid);

// registros
int R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15;




/* ej. 1.2 */
void Ke_context_switch(PCB* pcb_0, PCB* pcb_1) {

    // (2.) actualizar los datos de control
    // (lo hacemos primero para no incluir esta funcion a CPU_TIME)
    pcb_0->CPU_TIME += ke_current_user_time();

    // (3.) asumimos que el nuevo proceso esta en memoria

    // (1.) guardar contexto de pcb_0
    pcb_0->R0 = R0;
    pcb_0->R1 = R1;
    pcb_0->R2 = R2;
    pcb_0->R3 = R3;
    pcb_0->R4 = R4;
    pcb_0->R5 = R5;
    pcb_0->R6 = R6;
    pcb_0->R7 = R7;
    pcb_0->R8 = R8;
    pcb_0->R9 = R9;
    pcb_0->R10 = R10;
    pcb_0->R11 = R11;
    pcb_0->R12 = R12;
    pcb_0->R13 = R13;
    pcb_0->R14 = R14;
    pcb_0->R15 = R15;
    
    // (5.) Se carga el contexto de la nueva tarea
    R0 = pcb_1->R0;
    R1 = pcb_1->R1;
    R2 = pcb_1->R2;
    R3 = pcb_1->R3;
    R4 = pcb_1->R4;
    R5 = pcb_1->R5;
    R6 = pcb_1->R6;
    R7 = pcb_1->R7;
    R8 = pcb_1->R8;
    R9 = pcb_1->R9;
    R10 = pcb_1->R10;
    R11 = pcb_1->R11;
    R12 = pcb_1->R12;
    R13 = pcb_1->R13;
    R14 = pcb_1->R14;
    R15 = pcb_1->R15;

    // (2., 4.) actualizar el estado de los procesos
    // asumo que la funcion ejecuta algo como:
    //  pcb_0->STAT = KE_READY;
    //  pcb_1->STAT = KE_RUNNING;
    set_current_process(pcb_1->P_ID);

    // (4.) nos preparamos para la nueva tarea
    // (lo hacemos al final para que no mida esta funcion (lo mas posible))
    ke_reset_current_user_time();
    
    // (1., 5.) se guarda el PC viejo y carga el nuevo
    // asumo que la funcion ejecuta algo por el estilo de:
    //  pcb_0->PC = PC;
    //  PC = pcb_1->PC;
    ret();
}

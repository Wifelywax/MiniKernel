#include <assert.h> //Deteccion de errores "assert()"
#include <stdio.h>
#include "../include/queue.h"

int main() {

printf("PRUEBA PARA CC\n");

//Inicializar CC
Queue test_queue;
queue_init(&test_queue);

//Empezar desde 0
assert(test_queue.count== 0);

printf("PRUEBA 1: PASADA (CC ESTA VACIA)\n");

//Proceso de prueba

pcb_t test_process;
test_process.pid = 99;
test_process.burst_time = 10;
test_process.state = 0; 

queue_enqueue(&test_queue,test_process);

assert(test_queue.count == 1);

printf("PRUEBA 2: PASADA (ELEMENTO INSERTADO EN CC, CONTADOR=1)\n");

pcb_t dequeue_process = queue_dequeue(&test_queue);

assert(dequeue_process.pid == 99);
assert(test_queue.count == 0);

printf("PRUEBA 3: PASADA (ELEMENTO ELIMINADO DE CC, CONTADOR=0)\n");

printf("PRUEBAS SUPERADAS CON EXITO\n");

return 0;  

}
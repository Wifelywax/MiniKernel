#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "../include/queue.h"

//Cola Compartida 
Queue ready_queue;
int process_count = 0;

void* process_generator(void* arg) {
    while (1) {
        //Duerme un tiempo aleatorio entre 1 y 3 segundos
        int sleep_time = (rand()% 3)+ 1;
        sleep(sleep_time);

        //Crea un nuevo proceso (PCB)
        pcb_t new_process;

        //Aumenta Proccess ID
        new_process.pid = process_count++; 

        //Rafaga entre 1 y 10 segundos
        new_process.burst_time = rand() % 10 + 1; 

        // El tiempo que falta es igual al tiempo total
        new_process.remaining_time = new_process.burst_time;

        
        new_process.priority = 0; 

        //Tiempo aleatorio de llegada
        new_process.arrival_time = (rand() % 10) + 1;

        
        new_process.state = STATE_READY;

        printf("Generated Process: PID=%d, Burst Time=%d, Arrival Time=%ld, Priority=%d\n", 
               new_process.pid, new_process.burst_time, new_process.arrival_time, new_process.priority);

        //Insercion en la cola de listos        
        queue_enqueue(&ready_queue, new_process);

    }
    return NULL;
}

int main() {

    //Inicializar semilla para numeros randoms
    srand(time(NULL)); 

    //Inicializar la cola de listos
    queue_init(&ready_queue);

    //Declarar hilo generador 
    pthread_t generator_thread;

   printf("///Iniciando el MINIKERNEL///\n");

    //Crear y ejecutar el hilo generador
    if(pthread_create(&generator_thread, NULL, process_generator, NULL) != 0) {
        perror("Error al crear hilo generador");
        return 1;
    }

    //Hilo main en espera
    pthread_join(generator_thread, NULL);
    return 0;
}
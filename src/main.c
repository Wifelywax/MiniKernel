#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "../include/queue.h"
#include "../include/metrics.h"

#define NUM_CPUS 2   //CPUs Virtuales


Queue ready_queue; //Cola de listos 
int process_count = 0;

extern void* cpu_scheduler(void* arg); //Declaracion del scheduler


//Cola Compartida 
Queue ready_queue;

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

        printf("Generated Process: PID=%d, Burst Time=%d, Arrival Time=%d, Priority=%d\n", 
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

    metrics_init(); //Inicializar métricas

    pthread_t generator_thread;  //Declarar hilo generador 
    pthread_t cpu_threads[NUM_CPUS]; //Guardar hilos CPU

    pthread_t metrics_thread;

   printf("///Iniciando el MINIKERNE con %d CPUs virtuales///\n", NUM_CPUS);


    //Ejecutar el hilo generador
    if(pthread_create(&generator_thread, NULL, process_generator, NULL) != 0) {
        perror("Error al crear hilo generador");
        return 1;
    }

    //Ejecutar hilos CPU virtuales
    for(int i=0; i<NUM_CPUS; i++){
        int* cpu_id= malloc(sizeof(int));
        *cpu_id = i+1;

        if(pthread_create(&cpu_threads[i], NULL, cpu_scheduler, cpu_id) != 0){
            perror("Error al crear hilo CPU");
            return 1;
        }
    }

    //Ejecutar hilo de métricas
    if(pthread_create(&metrics_thread, NULL, metrics_monitor, NULL) != 0) {
        perror("Error al crear hilo de métricas");
        return 1;
    }

    //Hilo main en espera
    pthread_join(generator_thread, NULL);
    return 0;
}

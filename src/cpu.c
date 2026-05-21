#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "../include/queue.h"

#define Quantum 3   //Quantum RR

extern Queue ready_queue;  

void* cpu_scheduler(void* arg){

    int cpu_id = *((int*)arg);
    free(arg);  //Liberar memoria cpu

    while(1){
       
        pcb_t process = queue_dequeue(&ready_queue); //Sacar proceso, si CC vacia, duerme.

        process.state = 2; // Running
        printf("CPU %d: Running Process PID=%d, Burst Time=%d, Remaining Time=%d, Priority=%d\n",  
            cpu_id, process.pid, process.burst_time, process.remaining_time, process.priority);

            //Tiempo de trabajo (Ver si usa todo el Quantum)
        int time_to_run = (process.remaining_time > Quantum) ? Quantum : process.remaining_time; 
        
        sleep(time_to_run); //Simular tiempo dormido

        process.remaining_time -= time_to_run; //Reducir tiempo restante

        if(process.remaining_time > 0){
            //Si proceso necesita mas CPU
            process.state = 1; // Ready
            printf("CPU %d: Context Switch PID=%d, Remaining Time=%d\n", 
                cpu_id, process.pid, process.remaining_time);
            queue_enqueue(&ready_queue, process); //Retorno al final CC
        } else {
            process.state = 3; // Terminated
            printf("CPU %d: Process PID=%d finalizado.\n", 
                cpu_id, process.pid);
        }
    }
    return NULL;
}


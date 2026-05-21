#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/metrics.h"  


//Variables para métricas(globales)
int total_completed=0;
int total_response_time = 0;
int process_responded = 0;

pthread_mutex_t metrics_mutex; //Evitar condiciones de carrera

void metrics_init() {
    pthread_mutex_init(&metrics_mutex, NULL);
}

void record_first_response_time(int arrival_time) {

    pthread_mutex_lock(&metrics_mutex);
   
    int response_time = time(NULL) - arrival_time; //Tiempo de respuesta
    

    total_response_time += response_time; //Acumular tiempo de respuesta
    process_responded++; //Contar procesos que han respondido

    pthread_mutex_unlock(&metrics_mutex); 
}

void record_completion_time() {
    pthread_mutex_lock(&metrics_mutex);
    total_completed++; 
    pthread_mutex_unlock(&metrics_mutex);
}   

void* metrics_monitor(void* arg){
    int intervalo= 10; //Intervalo de monitoreo
    while(1){
        sleep(intervalo);
        pthread_mutex_lock(&metrics_mutex);


        float throughput = (float)total_completed / intervalo; //Calcular throughput

        //Calcular tiempo promedio de respuesta
        float avg_response_time = (process_responded > 0) ? ((float) total_response_time/process_responded) : 0.0;


        printf("Metricas del Scheduler\n");
        printf("Throughput: %.2f procesos/segundo\n", throughput);
        printf("Tiempo de Respuesta Promedio: %.2f segundos\n", avg_response_time);

        //Reinicio de Contadores(Siguiente inter)
        total_completed = 0; 
        total_response_time = 0; 
        process_responded = 0; 

        
        pthread_mutex_unlock(&metrics_mutex);
    }
    return NULL;
}
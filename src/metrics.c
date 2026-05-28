#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/metrics.h"  



int total_completed=0;
int total_response_time = 0;
int process_responded = 0;

pthread_mutex_t metrics_mutex; //Evitar condiciones de carrera

void metrics_init() {

    pthread_mutex_init(&metrics_mutex, NULL);
}

void record_first_response_time(int arrival_time) {

    pthread_mutex_lock(&metrics_mutex);
   
    //Calculo ligado a anomalias (Reloj Local vs Simulado)
    int response_time = time(NULL) - arrival_time; 
    total_response_time += response_time;
    process_responded++;

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

        //SECCION CRITICA: Extraer contadores sin alterar lecturas
        pthread_mutex_lock(&metrics_mutex);

        float throughput = (float)total_completed / intervalo;

        //Calcular tiempo promedio de respuesta
        float avg_response_time = (process_responded > 0) ? ((float) total_response_time/process_responded) : 0.0;


        printf("Metricas del Scheduler\n");
        printf("Throughput: %.2f procesos/segundo\n", throughput);
        printf("Tiempo de Respuesta Promedio: %.2f segundos\n", avg_response_time);

        //Reinicio de Contadores(Siguiente intervalo)
        total_completed = 0; 
        total_response_time = 0; 
        process_responded = 0; 

        
        pthread_mutex_unlock(&metrics_mutex);
    }
    return NULL;
}
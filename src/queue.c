
#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>

void queue_init(Queue* q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;

    //Inicializar mutex y condiciones
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
}

/*---INSERTAR EN CC---*/

void queue_enqueue(Queue* q, pcb_t process) {
    pthread_mutex_lock(&q->mutex);  //Candado

    // Esperar si la cola está llena
    while (q->count == MAX_QUEUE_SIZE) {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }

    // Agregar el proceso a la cola
    q->buffer[q->tail] = process;
    q->tail = (q->tail + 1) % MAX_QUEUE_SIZE;
    q->count++;

    // Señalar que la cola no está vacía
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
}   

/*---ELIMINAR DE CC---*/

pcb_t queue_dequeue(Queue* q) {
    pthread_mutex_lock(&q->mutex); 

   
    while (q->count == 0) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    // Proceso de la cola
    pcb_t process = q->buffer[q->head];
    q->head = (q->head + 1) % MAX_QUEUE_SIZE;
    q->count--;

    // Señalar que la cola no está llena
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->mutex);

    return process;
}
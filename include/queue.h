#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include "pcb.h"



#define MAX_QUEUE_SIZE 100

typedef struct Queue {
   pcb_t buffer[MAX_QUEUE_SIZE];
   int head;
   int tail;
   int count;

   pthread_mutex_t mutex;
   pthread_cond_t not_empty;
   pthread_cond_t not_full;
} Queue;    

void queue_init(Queue* q);
void queue_enqueue(Queue* q, pcb_t process);
pcb_t queue_dequeue(Queue* q);

#endif 
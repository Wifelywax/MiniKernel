
#ifndef  metrics_h
#define metrics_h


#include <pthread.h>

void metrics_init();
void record_first_response_time(int arrival_time); 
void record_completion_time(); //Datos Throughput
void* metrics_monitor (void* arg);

#endif
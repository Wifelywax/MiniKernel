#ifndef PCB_H
#define PCB_H


#define STATE_NEW 0
#define STATE_READY 1
#define STATE_RUNNING 2
#define STATE_TERMINATED 3

typedef struct {
    int pid;
    int burst_time; 
    int remaining_time; 
    int priority; 
    int arrival_time;
    int state; 
} pcb_t;

#endif 
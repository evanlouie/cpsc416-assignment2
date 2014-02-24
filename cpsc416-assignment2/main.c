//
//  main.c
//  cpsc416-assignment2
//
//  Created by Evan Louie on 2/23/2014.
//  Copyright (c) 2014 Evan Louie. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <getopt.h>

#include "queue.h"



typedef struct queue_operation {
    int operation;
    int value;
} operation_t;

typedef struct generator_state {
    int state[4];
} generator_state_t;

FILE * pFile;
pthread_mutex_t mutex_lock;
pthread_t sniffer_thread;
Queue *queue = NULL;

unsigned long TOTAL_OPERATIONS = 0;

void *thread_handler(void *);

int load_generator(operation_t *op, generator_state_t **s) {
    if (*s == NULL) {
        *s = (generator_state_t *) malloc(sizeof(generator_state_t));
        // initialize state
    }
    // set value for op->operation and op->value
    if (rand()%2) {
        op->operation = 1;
        op->value =rand();
    }
    else {
        op->operation=0;
        op->value = 0;
    }
    return 1;
error:
    return 0;
}

void *thread_handler() {
    operation_t myops;
    generator_state_t *state = NULL;
    while (load_generator(&myops, &state)) {
        pthread_mutex_lock(&mutex_lock);
        TOTAL_OPERATIONS++;
        if (myops.operation == 1) {
            int *i = malloc(sizeof(int));
            *i = myops.value;
            Queue_enqueue(queue, i);
        }
        else if (myops.operation == 0) {
            
            int *i = Queue_dequeue(queue);
            printf("%u\n", (unsigned int) &i);
            printf("Queue size: %d\n", queue->count);
        }
        pthread_mutex_unlock(&mutex_lock);
    }
    return 0;
}





int main(int argc, const char * argv[])
{

    // insert code here...
    // Process parameters
    int PROCESS_COUNT = -1;
    int RUNTIME = -1;
    int option = 0;
    while ((option=getopt(argc, argv, "p:t:"))!= -1) {
        switch(option) {
            case 'p':
                PROCESS_COUNT = atoi(optarg);
                break;
            case 't':
                RUNTIME = atoi(optarg);
                break;
            default:
                break;
        }
    }
    if (PROCESS_COUNT == -1 || PROCESS_COUNT < 1 || PROCESS_COUNT > 100) {
        printf("Number of processes specified not valid\n");
        return -1;
    }
    if (RUNTIME == -1 || RUNTIME < 1 || RUNTIME > 300) {
        printf("Runtime specified not valid\n");
        return -1;
    }
    
    printf("processes: %d\n", PROCESS_COUNT);
    printf("runtime: %d\n", RUNTIME);

    // Seed random number generator
    srand ( (int)time(NULL) );
    if (pthread_mutex_init(&mutex_lock, NULL) != 0) {
        printf("\nWARNING: mutex init failed\n");
        return 1;
    }
    
    pFile = fopen ("result.txt","a");
    
    queue = Queue_create();
    assert(queue != NULL);
    
    
    int CURRENT_PROCESSES = 0;
    
    while (CURRENT_PROCESSES <= PROCESS_COUNT) {
        pthread_mutex_lock(&mutex_lock);
        pthread_create(&sniffer_thread, NULL, thread_handler, (void *) 1);
        CURRENT_PROCESSES++;
        pthread_mutex_unlock(&mutex_lock);
    }
    
    
    // START CLOCK
    clock_t start,now;
    start = clock();
    now = 0;
    while(now <= RUNTIME){
        now = (clock() - start)/CLOCKS_PER_SEC;
//        printf("Time Elapsed: %lu\n", now);
    }
    printf("Total Actions: %lu\n", TOTAL_OPERATIONS);
    
    if (pFile!=NULL)
    {
        char message[1024];
        sprintf(message, "# of threads=%d time (seconds)=%d total number of operations=%lu\n", PROCESS_COUNT, RUNTIME, TOTAL_OPERATIONS);
        fputs (message,pFile);
        fclose (pFile);
    }
    else {
        perror("Could not create/open/write-to result.txt");
        return -1;
    }
    return 0;
}


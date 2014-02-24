//
//  queue.h
//  cpsc416-assignment2
//
//  Created by Evan Louie on 2/23/2014.
//  Copyright (c) 2014 Evan Louie. All rights reserved.
//

#ifndef cpsc416_assignment2_queue_h
#define cpsc416_assignment2_queue_h

#include "list.h"
#include <pthread.h>
pthread_mutex_t mutex_lock;
typedef struct Queue {
    int count;
    ListNode *first;
    ListNode *last;
} Queue;
Queue *Queue_create();

void Queue_enqueue(Queue *queue, void *value);
void *Queue_dequeue(Queue *queue);

void *Queue_remove(Queue *queue, ListNode *node);

#endif

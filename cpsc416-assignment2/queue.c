//
//  queue.c
//  cpsc416-assignment2
//
//  Created by Evan Louie on 2/23/2014.
//  Copyright (c) 2014 Evan Louie. All rights reserved.
//

#include <stdio.h>
#include "queue.h"
#include "dbg.h"

Queue *Queue_create()
{
    return calloc(1, sizeof(Queue));
}

void Queue_enqueue(Queue *queue, void *value) {
    pthread_mutex_lock(&(queue->mutex));
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);
    
    node->value = value;
    
    if (queue->last == NULL) {
        queue->first=node;
        queue->last=node;
    }
    else {
        queue->last->next = node;
        node->prev= queue->last;
        queue->last = node;
    }
    
    queue->count++;
    pthread_mutex_unlock(&(queue->mutex));
error:
    return;
}
void *Queue_dequeue(Queue *queue) {
    pthread_mutex_lock(&(queue->mutex));
    ListNode *node = queue->first;
    if (node != NULL) {
        return Queue_remove(queue, node);
    }
    else {
        pthread_mutex_unlock(&(queue->mutex));
        return NULL;
    }
}

void *Queue_remove(Queue *queue, ListNode *node) {
    
    void *result = NULL;
    check(queue->first && queue->last, "Queue is empty.");
    check(node, "Node can't be NULL");
    
    if (node == queue->first && node == queue->last) {
        queue->first = NULL;
        queue->last = NULL;
    }
    else if (node==queue->first) {
        queue->first = node->next;
        check(queue->first != NULL, "Invalid queue, somehow got a first that is NULL.");
        queue->first->prev = NULL;
    }
    else if (node== queue->last) {
        queue->last = node->prev;
        queue->last = node->prev;
        check(queue->last != NULL, "Invalid queue, somehow got a next that is NULL.");
        queue->last->next = NULL;
    }
    else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }
    
    queue->count--;
    result = node->value;
    free(node);
    pthread_mutex_unlock(&(queue->mutex));
    return result;
error:
    return result;
}
//
// Created by Gabriel Fernandes on 24/12/2020.
//

#include "eventos.h"

EVENT_QUEUE *init_event_queue() {
    EVENT_QUEUE *queue = (EVENT_QUEUE*)malloc(sizeof(EVENT_QUEUE));
    queue->first=NULL;
    queue->last=NULL;
    queue->size=0;
    return queue;
}

void event_list_enqueue(EVENT_QUEUE *queue, EVENT *newEvent) {
    queue->last->next = newEvent;
    queue->last = newEvent;
    queue->size++;
}

void event_list_dequeue(EVENT_QUEUE *queue) {
    queue->first = queue->first->next;
    queue->size--;
}

int event_size(EVENT_QUEUE *queue) {
    return queue->size;
}

int event_isEmpty(EVENT_QUEUE *queue) {
    return queue->size==0;
}

void print_event_queue(EVENT_QUEUE *queue) {
    EVENT *aux;
    while(!event_isEmpty(queue)) {
        aux = queue->first;
        printf("\nID: %d\nTipo: %s\nValor: %d\n", aux->id, aux->tipo, aux->valor);
        event_list_dequeue(queue);
    }
}
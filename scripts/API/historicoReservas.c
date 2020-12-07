//
// Created by Gabriel Fernandes on 06/12/2020.
//

#include "historicoReservas.h"

int hist_size = 0;

HIST_STACK* init_hist_stack() {
    HIST_STACK* stack = (HIST_STACK*)malloc(sizeof(HIST_STACK));
    stack->head = NULL;
    stack->tail = NULL;
    return stack;
}

void hist_list_push(HIST_STACK* stack, HIST* newHead) {
    HIST* oldhead = stack->head;
    newHead->next = oldhead;
    stack->head = newHead;
    hist_size++;
}

void hist_list_pop(HIST_STACK* stack, HIST* currHead) {
    stack->head = currHead->next;
    hist_size--;
}

int hist_list_size() {
    return hist_size;
}

int hist_isEmpty() {
    return hist_size==0;
}

void print_hist_Stack(HIST_STACK* stack) {
    HIST* tmp;
    while(!hist_isEmpty()) {
        tmp = stack->head;
        printf("\nId: %d\nHospede_id: %d\nReserva: %s\n", tmp->id, tmp->hospede_id, tmp->reserva);
        hist_list_pop(stack, tmp);
    }
}
#include "guests_list.h"

int hosp_size=0;

HOSP_STACK* init_guest_stack() {
    HOSP_STACK* stack = (HOSP_STACK*)malloc(sizeof(HOSP_STACK));
    stack->head = NULL;
    stack->tail = NULL;
    return stack;
}

void guests_lists_push(HOSP_STACK* stack, HOSP* newHead) {
    HOSP* oldHead = stack->head;
    newHead->next = oldHead;
    stack->head = newHead;
    hosp_size++;
}

void guests_list_pop(HOSP_STACK* stack, HOSP* currHead) {
    stack->head = currHead->next;
    hosp_size--;
}

int guests_list_size() {
    return hosp_size;
}

int hosp_isEmpty() {
    return hosp_size==0;
}

void print_hosp_Stack(HOSP_STACK* stack) {
    HOSP* tmp;
    while(!hosp_isEmpty()){
        tmp = stack->head;
        printf("\nId: %d\nNome: %s\nEmail: %s\n", tmp->id, tmp->nome, tmp->email);
        guests_list_pop(stack, tmp);
    }
}
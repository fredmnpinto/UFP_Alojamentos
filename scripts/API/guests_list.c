#include "guests_list.h"

HOSP_STACK* init_guest_stack() {
    HOSP_STACK* stack = (HOSP_STACK*)malloc(sizeof(HOSP_STACK));
    stack->head = NULL;
    stack->tail = NULL;
    stack->size=0;
    return stack;
}

void guests_lists_push(HOSP_STACK* stack, HOSP* newHead) {
    HOSP* oldHead = stack->head;
    newHead->next = oldHead;
    stack->head = newHead;
    stack->size++;
}

void guests_list_pop(HOSP_STACK* stack, HOSP* currHead) {
    stack->head = currHead->next;
    stack->size--;
}

int guests_list_size(HOSP_STACK* stack) {
    return stack->size;
}

int hosp_isEmpty(HOSP_STACK* stack) {
    return stack->size==0;
}

void print_hosp_Stack(HOSP_STACK* stack) {
    HOSP* tmp;
    while(!hosp_isEmpty(stack)){
        tmp = stack->head;
        printf("\nId: %d\nNome: %s\nEmail: %s\n", tmp->id, tmp->nome, tmp->email);
        guests_list_pop(stack, tmp);
    }
}
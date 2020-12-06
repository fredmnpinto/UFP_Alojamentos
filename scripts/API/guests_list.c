#include "guests_list.h"

int size=0;

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
    size++;
}

void guests_list_pop(HOSP_STACK* stack, HOSP* currHead) {
    stack->head = currHead->next;
    size--;
}

int guests_list_size() {
    return size;
}

int isEmpty() {
    return size==0;
}

void printStack(HOSP_STACK* stack) {
    HOSP* tmp;
    while(!isEmpty()){
        tmp = stack->head;
        printf("\nId: %d\nNome: %s\nEmail: %s\n", tmp->id, tmp->nome, tmp->email);
        guests_list_pop(stack, tmp);
    }
}
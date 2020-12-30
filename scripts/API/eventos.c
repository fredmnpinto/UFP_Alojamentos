//
// Created by Gabriel Fernandes on 24/12/2020.
//

#include "eventos.h"

EVENT_STACK *init_event_stack() {
    EVENT_STACK *stack = (EVENT_STACK*)malloc(sizeof(EVENT_STACK));
    stack->head=NULL;
    stack->tail=NULL;
    stack->size=0;
    return stack;
}

void event_list_push(EVENT_STACK *stack, EVENT *newEvent) {
    if(stack->head==NULL) {
        stack->head = newEvent;
        stack->tail = newEvent;
    }else{
        newEvent->next = stack->head;
        stack->head = newEvent;
    }
    stack->size++;
}

void event_list_pop(EVENT_STACK *stack) {
    if(!event_isEmpty(stack)) {
        stack->head = stack->head->next;
        stack->size--;
    }
}

int event_size(EVENT_STACK *stack) {
    return stack->size;
}

int event_isEmpty(EVENT_STACK *stack) {
    return stack->size==0;
}

void print_event_stack(EVENT_STACK *stack) {
    EVENT *aux;
    while(!event_isEmpty(stack)) {
        aux = stack->head;
        printf("    %s", aux->descricao);
        event_list_pop(stack);
    }
}

EVENT_STACK* add_data_event(char eventos[], EVENT_STACK* listaEventos) {
    char *savefield = (char*)malloc(sizeof(char)*strlen(eventos));
    strcpy(savefield, eventos);
    char* field = strtok_r(savefield, ",", &savefield);
    do{
        EVENT* evento = (EVENT*)malloc(sizeof(EVENT));
        evento->descricao = (char*)malloc(sizeof(char)*strlen(field));
        strcpy(evento->descricao, field);
        event_list_push(listaEventos, evento);
    }while((field=strtok_r(savefield, ",", &savefield)));

    return listaEventos;
}
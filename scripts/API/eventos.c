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
        EVENT* elementToPop = stack->head;
        stack->head = elementToPop->next;
        stack->size--;
        free(elementToPop->descricao);
        free(elementToPop);
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

int check_event(EVENT_STACK *stack, char eventSearchFor[]) {
    EVENT* start = stack->head;
    for(int i=0; i<stack->size; i++) {
        if(strcmp(start->descricao, eventSearchFor)==0) {
            return 1;
        }
        start = start->next;
    }
    return -1;
}

EVENT_STACK* change_event(EVENT_STACK *listaEventos, char eventSearchFor[], char newChangedEvent[]) {
    EVENT* start = listaEventos->head;
    for(int i=0; i<listaEventos->size; i++) {
        if(strcmp(start->descricao, eventSearchFor)==0) {
            start->descricao = newChangedEvent;
        }
        start = start->next;
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

EVENT_STACK* freeAll(EVENT_STACK* stack) {
    while(!event_isEmpty(stack)) {
        event_list_pop(stack);
    }
}
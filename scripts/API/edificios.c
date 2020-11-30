//
// Created by Frederico on 29/11/2020.
//

#include "edificios.h"

ED_QUEUE * init_ed_queue(){
    ED_QUEUE* queue = (ED_QUEUE*)malloc(sizeof(ED_QUEUE));
    queue->print = _edfs_list_print;
    queue->append = _edfs_list_append;
    queue->remove = _edfs_list_remove;
    queue->free_all = _edfs_list_free_all;
    queue->insert_to_front = _edfs_list_insert_to_front;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void _edfs_list_print(ED_QUEUE *queue){
    ED *tmp = queue->head;
    while(tmp != NULL){
        printf("\nId: %d\nNome: %s\nEndereco: %s\t(lat: %f longi: %f)\n", tmp->id, tmp->nome, tmp->endereco.endereco, tmp->endereco.lat, tmp->endereco.longi);
        tmp = tmp->next;
    }
}

void _edfs_list_append(ED_QUEUE* queue, ED* edificio){
    queue->tail->next = edificio;
    edificio->next = NULL;
    queue->tail = edificio;
}

void _edfs_list_remove(ED_QUEUE* queue, ED* edificio){
    ED* current = queue->head;
    while(current != NULL){
        if(current->next->id == edificio->id){
            ED* to_be_deleted = current->next;
            current->next = current->next->next;
            free(edificio);
            free(to_be_deleted);
            return;
        }
        current = current->next;
    }
    printf("404 - Edificio Not Found withing the list\n");
}

void _edfs_list_free_all(ED_QUEUE* queue){
    ED* current = queue->head;
    ED* _next;
    while(current != NULL){
        _next = current->next;
        free(current);
        current = _next;
    }
    if (queue->head == NULL && queue->tail == NULL) // Checar se tail faz free() ja ou se precisa fazer manualmente
        printf("List has been freed\n");
    else
        printf("Error freeing the list\n");
}

void _edfs_list_insert_to_front(ED_QUEUE* queue, ED* edificio){
//    ED* prior_head = queue->head;
    edificio->next = queue->head;
    queue->head = edificio;
}
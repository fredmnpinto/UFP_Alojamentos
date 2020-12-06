//
// Created by Frederico on 30/11/2020.
//

#include "billing.h"

RP *rp_dyn_arr(RP *static_array, int size ) {
    RP * new_array = malloc(sizeof(RP) * size); // Array dinamico declarado

    for (int i = 0; i < size; ++i) {    // Preenchendo array dinamico com os valores do array estatico
        new_array[i].id = static_array[i].id;
        strcpy(new_array[i].regra, static_array[i].regra);
        new_array[i].taxa = static_array[i].taxa;
    }
    return new_array;
}

void print_rp(RP* rp_array, int array_size){
    for (int i = 0; i < array_size; ++i) {
        printf("ID: %d\n", rp_array[i].id);
        printf("REGRA: %s\n", rp_array[i].regra);
        printf("TAXA: %d\n", rp_array[i].taxa);
    }
}
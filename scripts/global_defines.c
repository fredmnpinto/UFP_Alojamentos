//
// Created by Frederico on 07/11/2020.
//

#include "global_defines.h"

void remove_linebreak_on_the_end(char str[]) {
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

void remove_linebreak(char str[]) {
    int n = strlen(str);
    for (int c = 0; c != n; c = strspn(str, "\n")) {
        for (int i = n; i < n; ++i) {
            str[i] = str[i + 1];
        }
    }
}

void print_alojs(ALOJ* aloj_array, int array_size){
    for (int i = 0; i < array_size; ++i) {
        printf("ID: %lu\n", aloj_array[i].id);
        printf("ESTUDIO ID: %lu\n", aloj_array[i].estudio_id);
        printf("TIPO DE ALOJAMENTO: %s\n", aloj_array[i].tipo);
    }
}

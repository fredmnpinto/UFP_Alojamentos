//
// Created by Frederico on 07/11/2020.
//

#include "utils.h"
#include <time.h>

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
        printf("ID: %d\n", aloj_array[i].id);
        printf("ESTUDIO ID: %lu\n", aloj_array[i].estudio_id);
        printf("TIPO DE ALOJAMENTO: %s\n", aloj_array[i].tipo);
    }
}

int is_upper_c(char c){
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

int is_lower_c(char c){
    if (c >= 'a' && c <= 'z')
        return 0;
    return 1;
}

char get_lower_c(char C){
    if (!is_upper_c(C))
        return C;
    int offset = 'A' - 'a';
    return (char)(C - offset);
}

char get_upper_c(char C){
    if (is_upper_c(C))
        return C;
    int offset = 'A' - 'a';
    return (char)(C + offset);
}

char * get_lower_str(char STR[]){
    unsigned int n = strlen(STR);
    char STR2[n]; strcpy(STR2, STR);
    for (int i = 0; i < n; ++i) {
        if (is_upper_c(STR2[i]))
            STR2[i] = get_lower_c(STR2[i]);
    }
    return STR;
}

char * get_upper_str(char str[]){
    unsigned int n = strlen(str);
    char str2[n];
    strcpy(str2, str);
    for (int i = 0; i < n; ++i) {
        if (!is_upper_c(str2[i]))
            str2[i] = get_lower_c(str2[i]);
    }
    return str;
}

int comp_date(DATA dat1, DATA dat2){
    if(dat1.dia == dat2.dia && dat1.mes == dat2.mes && dat1.ano == dat2.ano)
        return 1;
    return 0;
}

DATA get_today(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return init_data(tm.tm_mday, tm.tm_mon, tm.tm_year);
}

DATA init_data(int dia, int mes, int ano){
    DATA nData;
    nData.dia = dia;
    nData.mes = mes;
    nData.ano = ano;
    return nData;
}
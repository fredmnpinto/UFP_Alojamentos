//
// Created by Frederico on 07/11/2020.
//

#include "utils.h"

void remove_linebreak_on_the_end(char str[]) {
    if(str!=NULL || strcmp(str, " ")==1) {
        if (str[strlen(str) - 1] == '\n') {
            str[strlen(str) - 1] = '\0';
        }
    }
}

void remove_linebreak(char str[]) {
    int n = strlen(str);
    for (int c = 0; c != n; c = strspn(str, "\n")) {
        for (int i = n; i < n; ++i) {
            str[i] = str[i + 1];
        }
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

char toLowerC(char C) {
    if (!is_upper_c(C))
        return C;
    int offset = 'A' - 'a';
    return (char) (C - offset);
}

char toUpperC(char c) {
    if (is_upper_c(c))
        return c;
    int offset = 'A' - 'a';
    return (char) (c + offset);
}

char * get_lower_str(char STR[]){
    unsigned int n = strlen(STR);
    char STR2[n]; strcpy(STR2, STR);
    for (int i = 0; i < n; ++i) {
        if (is_upper_c(STR2[i]))
            STR2[i] = toLowerC(STR2[i]);
    }
    return STR;
}

char * get_upper_str(char str[]){
    unsigned int n = strlen(str);
    char str2[n];
    strcpy(str2, str);
    for (int i = 0; i < n; ++i) {
        if (!is_upper_c(str2[i]))
            str2[i] = toLowerC(str2[i]);
    }
    return str;
}

int isNumStr(char *str) {
    for (int i = 0; i < strlen(str); ++i) {
        if (!isNumC(str[i]))
            return 0;
    }
    return 1;
}

int isNumC(char c) {
    return !(c < '0' || c > '9');
}

int isEstConfig(char *str) {
    // Formato T(x)+(y) ou T(x)
    if (toUpperC(str[0]) != 'T')
        return 0;
    if (!isNumC(str[1]))
        return 0;
    if (strlen(str) == 2)
        return 1;
    return strlen(str) == 4 && isNumC(str[4]);
}

char* toLowerStr(char* str){
    char* cpy = malloc((strlen(str) + 1) * sizeof(char));
    for (int i = 0; i < strlen(str); ++i) {
        cpy[i] = toLowerC(str[i]);
    }
    return cpy;
}
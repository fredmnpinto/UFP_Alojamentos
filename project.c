//
// Created by Frederico on 27/10/2020.
//

#include "project.h"

int main_proj(int argc, char* argv[]){
    main_menu(argc, argv);
    return 0;
}

void main_menu(int argc, char *argv[]){
    char *proj_name = "PortoFlats";
    printf("- - - - Welcome to %s - - - -\n", proj_name);
    printf("[1] - Insert Data\t[2] - Update Data\n[3] - Delete Data\t[4] - Read Data\n");
}

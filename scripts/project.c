//
// Created by Frederico on 27/10/2020.
//

#include "project.h"
#include "data_handler.h"

int main_proj(int argc, char *argv[]) {
    int size;
    ALOJ* a_array = get_aloj_data(&size);
    free(a_array);
}

void main_menu(int argc, char *argv[]) {
    char *proj_name = "PortoFlats";
    printf("- - - - Welcome to %s - - - -\n", proj_name);
    printf("[1] - Insert Data\t[2] - Update Data\n[3] - Delete Data\t[4] - Read Data\n");
}

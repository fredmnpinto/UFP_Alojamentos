//
// Created by Frederico on 27/10/2020.
//

#include "project.h"
#include "data_handler.h"

int main_proj(int argc, char *argv[]) {
<<<<<<< Updated upstream
    int size;
    ALOJ* a_array = get_aloj_data(&size);
    free(a_array);
=======
    int id = 1234;
    char* name = get_filepath_agenda_master(id);
    printf("%s", name);
    return 0;
>>>>>>> Stashed changes
}

void main_menu(int argc, char *argv[]) {
    char *proj_name = "PortoFlats";
    printf("- - - - Welcome to %s - - - -\n", proj_name);
    printf("[1] - Insert Data\t[2] - Update Data\n[3] - Delete Data\t[4] - Read Data\n");
}

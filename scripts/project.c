//
// Created by Frederico on 27/10/2020.
//

#include "project.h"
#include "data_reader.h"

int main_proj(int argc, char *argv[]) {
    int size;
    AGENDA *ag = get_data_agenda_master(1234);
    print_agenda(ag);
    return 0;
}

void main_menu(int argc, char *argv[]) {
    char *proj_name = "PortoFlats";
    char *commands[] = {
            "read",
            "update",
            "delete",
            "insert"
    };

    void (*functions[])(int, char* argv[]) = {   //Array que guarda os pronteiros de funcoes
            get_data_main,              //Por exemplo: functions[0](1, "read"); resulta o mesmo que get_data_main(1, "read");

    };

    printf("- - - - Welcome to %s - - - -\n", proj_name);
    for (int i = 0; i < 4; ++i){
        if (strcmp(argv[0], commands[i]) == 0) {
            return functions[0](argc, argv);
        }
    }
}

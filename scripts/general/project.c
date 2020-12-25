//
// Created by Frederico on 27/10/2020.
//

#include "project.h"
#include "../API/agendas.h"
#include "../API/edificios.h"
#include "../API/estudios.h"
#include "../API/guests_list.h"
#include "../API/historicoReservas.h"
#include "../API/eventos.h"
#include "../billing/billing.h"
#include "../data_handler/data_reader.h"
#include "../data_handler/data_writer.h"
#include "../data_handler/report_generator.h"

int main_proj(int argc, char *argv[]) {
    DATA inicio, final;
    inicio.dia = 1;
    inicio.mes = 1;
    inicio.ano = 2000;

    final.dia = 16;
    final.mes = 11;
    final.ano = 2020;

    EST_HANDLER *array = get_data_estudio();
    ED_LIST *edflist = get_data_edfs();
    EST estudio = array->estArray[0];
    generate_all_billing(array, inicio, final, 0);
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
        if (strcmp(argv[0], commands[i]) == 0)
            return functions[0](argc, argv);
    }
}

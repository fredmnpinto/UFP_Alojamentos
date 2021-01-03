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
#include "commandLineHandler.h"

int main_proj(int argc, char *argv[]) {
/*
    argc = 12;
    argv[1] = "create";
    argv[2] =  "edificio";
//    argv[3] = "est";
    argv[3] =  "10";
    argv[4] =   "adress";
    argv[5] =   "rua";
    argv[6] =   "crescente";
    argv[7] = "lat";
    argv[8] = "23.3";
    argv[9] = "longi";
    argv[10] = "23.3";
    argv[11] = "nome";
    argv[12] = "caralho";
*/
    mainCmd(argc, argv);
    return 0;
}



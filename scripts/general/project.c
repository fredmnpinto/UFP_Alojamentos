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
    argc = 7;
    argv[1] = "create";
    argv[2] =  "report_ocu";
//    argv[3] = "est";
    argv[3] =  "*";
    argv[4] =   "22/10/1900";
    argv[5] =   "03/03/2040";
    argv[6] =   "crescente";
*/
    mainCmd(argc, argv);
    return 0;
}



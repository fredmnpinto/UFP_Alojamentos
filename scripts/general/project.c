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
    mainCmd(argc, argv);
    return 0;
}



//
// Created by Frederico on 31/12/2020.
//

#ifndef UFP_ALOJAMENTOS_COMMANDLINEHANDLER_H
#define UFP_ALOJAMENTOS_COMMANDLINEHANDLER_H

#include "../data_handler/data_reader.h"
#include "../API/estudios.h"
#include "../data_handler/report_generator.h"
#include "utils.h"
#include "../API/agendas.h"
#include "../API/edificios.h"
#include "../API/guests_list.h"
#include "../billing/billing.h"
#include "../data_handler/data_writer.h"

void mainCmd(int argc, char *argv[]);

/// Handlers de CRUD

void readHandler(int argc, char *argv[]);

void createHandler(int argc, char *argv[]);

void deleteHandler(int argc, char *argv[]);

void updateHandler(int argc, char *argv[]);

/// Errors

void errorNumberArguments(int argc);

void errorInvalidInput(int argc, char **argv);

/// Funcoes principais de CRUD

void readEstudios(int argc, char *argv[]);

void readEdificios(int argc, char *argv[]);

void readAgendas(int argc, char *argv[]);

void readMarc(int argc, char *argv[]);

void updateEstudio(int argc, char* argv[]);

void updateEdifcio(int argc, char* argv[]);

void updateAgenda(int argc, char* argv[]);

void createReportOcu(int argc, char *argv[]);

void createReportBill(int argc, char *argv[]);

void __updateEstudioPrecoBase(int argc, char** argv);

void __updateEstudioEdificioId(int argc, char** argv);

void __updateEstudioConfig(int argc, char** argv);


void __updateEdificioNome(int argc, char* argv[], ED_LIST* list);

void __updateEdificioEndereco(int argc, char* argv[], ED_LIST* list);


void marcHandler(int argc, char *argv[]);

void marcAdd(int argc, char* argv[]);

void marcValidate(int argc, char* argv[]);

void createEstudio(int argc, char* argv[]);

void createEdificio(int argc, char* argv[]);

void createGuest(int argc, char *argv[]);

void createAgenda(int argc, char* argv[]);

void readGuests(int argc, char* argv[]);

void updateGuest(int argc, char* argv[]);

void __updateHospedeNome(int argc, char* argv[], HOSP_STACK* stack);

void __updateHospedeEmail(int argc, char* argv[], HOSP_STACK* stack);
#endif //UFP_ALOJAMENTOS_COMMANDLINEHANDLER_H

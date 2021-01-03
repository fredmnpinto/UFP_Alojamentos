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



#endif //UFP_ALOJAMENTOS_COMMANDLINEHANDLER_H

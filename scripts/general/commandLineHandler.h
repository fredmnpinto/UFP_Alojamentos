//
// Created by Frederico on 31/12/2020.
//

#ifndef UFP_ALOJAMENTOS_COMMANDLINEHANDLER_H
#define UFP_ALOJAMENTOS_COMMANDLINEHANDLER_H

#include "../data_handler/data_reader.h"
#include "../API/estudios.h"
#include "utils.h"

void mainCmd(int argc, char *argv[]);

/// Handlers de CRUD

void readHandler(int argc, char *argv[]);

void createHandler(int argc, char *argv[]);

void deleteHandler(int argc, char *argv[]);

void updateHandler(int argc, char *argv[]);

/// Errors

void errorNumberArguments(int argc);

void errorInvalidInput(int argc, char **argv);

/// Outras

void readEstudios(int argc, char *argv[]);

void readEdificios(int argc, char *argv[]);

void readAgendas(int argc, char *argv[]);

void readMarcacao(int argc, char *argv[]);

#endif //UFP_ALOJAMENTOS_COMMANDLINEHANDLER_H

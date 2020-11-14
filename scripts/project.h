//
// Created by Frederico on 27/10/2020.
//

#ifndef UFP_ALOJAMENTOS_PROJECT_H
#define UFP_ALOJAMENTOS_PROJECT_H

#include "data_reader.h"

//Functions
void main_menu(int argc, char *argv[]);

/**
 * Função para fazer o parse da string para a struct DATA
 *
 * @param str_date  Data em forma de string
 * @return          Data em forma de DATA
 */
DATA string_to_date(char str_date[]);

/**
 * Função para checar a disponibilidade em uma data de uma agenda
 *
 * @param agenda_id     Id da agenda a checar a disponibilidade
 * @param data          Data a checar
 * @return              retorna 1 se estiver disponivel e 0 se nao
 */
int checar_disponibilidade(int agenda_id, DATA data);

int main_proj(int argc, char *argv[]);

#endif //UFP_ALOJAMENTOS_PROJECT_H

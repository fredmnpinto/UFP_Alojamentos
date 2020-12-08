//
// Created by Frederico on 07/11/2020.
//

#ifndef UFP_ALOJAMENTOS_UTILS_H
#define UFP_ALOJAMENTOS_UTILS_H

#define ARR_SMALL 10
#define STR_MAX 50
#define CHAR_LIMIT 1024
#define AGENDA_MAX 365
#define ALOJ_HEADER "id,estudio_id,tipo"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

//GLOBAL FUNCTIONS [Usadas ou que podem ser usadas por todos os arquivos]
//BASICAMENTE FUNCOES UTILITARIAS OU HELPER

/**
 * Remove o '\ n' no final da string, caso tenha
 * \warning         Altera o valor da string inicial (remove o \ n)
 * @param str       string com ou sem a quebra de linha no fim
 */
void remove_linebreak_on_the_end(char str[]);

/**
 * Remove o '\ n' de qualquer posicao da string
 * \warning NAO FUNCIONAL, NAO UTILIZAR
 * @param str   String sem qualquer quebra de linha
 */
void remove_linebreak(char str[]);

/**
 * Funcao para printar todos os alojs do array
 * @param aloj_array    Array com todos os alojamentos
 * @param array_size    Tamanho do array
 */
void print_alojs(ALOJ *aloj_array, int array_size);

/**
 * Funcao para retornar a versao em lowercase de um determinado caracter
 * @param C     Caracter em uppercase ou nao
 * @return      Caracter em lowercase
 */
char get_lower_c(char C);

/**
 * Funcao para retornar a versao upppercase de um caracter
 * @param c     Caracter lowercase ou nao
 * @return      Caracter uppercase
 */
char get_upper_c(char c);

/**
 * Funcao para retornar a versao lowercase de uma string
 * @param STR       String em uppercase ou nao
 * @return          String em lowercase
 */
char * get_lower_str(char STR[]);

/**
 * Funcao para retornar a versao uppercase de uma string
 * @param str       String em lowercase ou nao
 * @return          String em uppercase
 */
char * get_upper_str(char str[]);

/**
 * Funcao para determinar se um caracter é uppercase ou nao
 * @param c     Caracter em questao
 * @return      1 para sim, 0 para nao
 */
int is_upper_c(char c);



#endif //UFP_ALOJAMENTOS_UTILS_H
//
// Created by Gabriel Fernandes on 25/12/2020.
//

#ifndef UFP_ALOJAMENTOS_REPORT_GENERATOR_H
#define UFP_ALOJAMENTOS_REPORT_GENERATOR_H

#include "../general/utils.h"

/**
 * Funcao que gera o relatorio de faturacao de um estudio
 * @param estudio           Apontador do estudio selecionado para o relatorio
 * @param inicio            Primeira data do intervalo de datas a pesquisar nas marcacoes
 * @param final             Ultima data do intervalo de datas a pesquisar nas marcacoes
 * @param ordem             Ordem(data) com que as marcacoes aparecem     0 de forma crescente   1 de forma decrescente
 */
void generate_estudio_billing(EST *estudio, DATA inicio, DATA final, int ordem);

/**
 * Funcao que cria um filepath para guardar o relatorio de faturacao do estudio
 * @param estudio           Apontador do estudio selecionado para o relatorio
 * @param hoje              Struct DATA do dia em que o relatorio vai ser criado
 * @return                  path para criar e escrever o relatorio
 */
char* create_filepath_est_report(EST *estudio, DATA hoje);

/**
 * Funcao que cria um filepath para guardar o relatorio de faturacao de um edificio
 * @param edificio          Apontador para o edificio selecionado para o relatorio
 * @param hoje              Struct DATA do dia em que o relatorio vai ser criado
 * @return                  path para criar e escrver o relatorio
 */
char* create_filepath_edf_report(ED *edificio, DATA hoje);

/**
 * Funcao que gera o relatorio de faturacao de um edificio
 * @param arrayEstudios      Apontador para o array dinamico de estudios
 * @param edificio           Apontador para o edificio selecionado para o relatorio
 * @param inicio             Primeira data do intervalo de datas a pesquisar marcacoes
 * @param final              Ultima data do intervalo de datas a pesquisar marcacoes
 * @param ordem              Ordem(data) com que as marcacoes aparecem     0 de forma crescente   1 de forma decrescente
 */
void generate_edificio_billing(EST_HANDLER *arrayEstudios, ED *edificio, DATA inicio, DATA final, int ordem);

/**
 * Funcao que pega num estudio especifico e escreve/imprime todas as suas datas de marcacoes e precos(dentro do intervalo [inicio-final]
 * Ela tambem faz o somatorio dos precos desse estudio e retorna(Total)
 * @param estudio             Apontador para o estudio selecionado
 * @param marcacoes           Apontador para as marcacoes do estudio selecionado
 * @param fw                  Apontador para o Ficheiro onde os dados sao escritos
 * @param inicio              Primeira data do intervalo de datas a pesquisar marcacoes
 * @param final               Ultima data do intervalo de datas a pesquisar marcacoes
 * @param ordem               Ordem(data) com que as marcacoes aparecem     0 de forma crescente    1 de forma decrescente
 * @return                    Preco Total das marcacoes nos dias selecionados do estudio escolhido
 */
int return_estudio_selected_data(EST *estudio, MARC *marcacoes, FILE *fw, DATA inicio, DATA final, int ordem);

/**
 * Funcao que cria um filepath para guardar o relatorio de faturacao de todos os edificios e seus respetivos estudios
 * @param hoje                 Struct DATA do dia em que o relatorio vai ser criado
 * @return                     path para criar e escrever o relatorio
 */
char *create_filepath_all_report(DATA hoje);

/**
 * Funcao que gera o relatorio de faturacao de todos os edificios
 * @param arrayEstudios         Apontador para o array dinamico de estudios
 * @param inicio                Primeira data do intervalo de datas a pesquisar marcacoes
 * @param final                 Ultima data do intervalo de datas a pesquisar marcacoes
 * @param ordem                 Ordem(data) com que as marcacoes aparecem     0 de forma crescente    1 de forma decrescente
 */
void generate_all_billing(EST_HANDLER *arrayEstudios, DATA inicio, DATA final, int ordem);

#endif //UFP_ALOJAMENTOS_REPORT_GENERATOR_H

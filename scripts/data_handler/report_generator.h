//
// Created by Gabriel Fernandes on 25/12/2020.
//

#ifndef UFP_ALOJAMENTOS_REPORT_GENERATOR_H
#define UFP_ALOJAMENTOS_REPORT_GENERATOR_H

#include "../general/utils.h"
#include "../data_handler/data_reader.h"

/**
 * Funcao que gera o relatorio de faturacao de um estudio
 * @param estudio           Apontador do estudio selecionado para o relatorio
 * @param inicio            Primeira data do intervalo de datas a pesquisar nas marcacoes
 * @param final             Ultima data do intervalo de datas a pesquisar nas marcacoes
 * @param ordem             Ordem(data) com que as marcacoes aparecem     0 de forma crescente   1 de forma decrescente
 */
void generate_estudio_billing(EST *estudio, DATA inicio, DATA final, char ordem[]);

/**
 * Funcao que cria um filepath para guardar o relatorio de faturacao do estudio
 * @param estudio           Apontador do estudio selecionado para o relatorio
 * @param hoje              Struct DATA do dia em que o relatorio vai ser criado
 * @return                  path para criar e escrever o relatorio
 */
char* create_filepath_est_report(EST *estudio, DATA hoje, char file_preset2[]);

/**
 * Funcao que cria um filepath para guardar o relatorio de faturacao de um edificio
 * @param edificio          Apontador para o edificio selecionado para o relatorio
 * @param hoje              Struct DATA do dia em que o relatorio vai ser criado
 * @return                  path para criar e escrver o relatorio
 */
char* create_filepath_edf_report(ED *edificio, DATA hoje, char file_preset2[]);

/**
 * Funcao que gera o relatorio de faturacao de um edificio
 * @param arrayEstudios      Apontador para o array dinamico de estudios
 * @param edificio           Apontador para o edificio selecionado para o relatorio
 * @param inicio             Primeira data do intervalo de datas a pesquisar marcacoes
 * @param final              Ultima data do intervalo de datas a pesquisar marcacoes
 * @param ordem              Ordem(data) com que as marcacoes aparecem     0 de forma crescente   1 de forma decrescente
 */
void generate_edificio_billing(EST_HANDLER *arrayEstudios, ED *edificio, DATA inicio, DATA final, char ordem[]);

/**
 * Funcao que pega num estudio especifico e escreve/imprime todas as suas datas de marcacoes e precos(dentro do intervalo [inicio-final]
 * Ela tambem faz o somatorio dos precos desse estudio e retorna(Total)
 * @param estudio             Apontador para o estudio selecionado
 * @param calendario          Apontador para o calendario do estudio selecionado
 * @param fw                  Apontador para o Ficheiro onde os dados sao escritos
 * @param inicio              Primeira data do intervalo de datas a pesquisar marcacoes
 * @param final               Ultima data do intervalo de datas a pesquisar marcacoes
 * @param ordem               Ordem(data) com que as marcacoes aparecem     0 de forma crescente    1 de forma decrescente
 * @return                    Preco Total das marcacoes nos dias selecionados do estudio escolhido
 */
int return_estudiobill_selected_data(EST *estudio, CALEND *calendario, FILE *fw, DATA inicio, DATA final, char ordem[]);

/**
 * Funcao que cria um filepath para guardar o relatorio de faturacao de todos os edificios e seus respetivos estudios
 * @param hoje                 Struct DATA do dia em que o relatorio vai ser criado
 * @return                     path para criar e escrever o relatorio
 */
char *create_filepath_all_report(DATA hoje, char file_preset2[]);

/**
 * Funcao que gera o relatorio de faturacao de todos os edificios
 * @param arrayEstudios         Apontador para o array dinamico de estudios
 * @param inicio                Primeira data do intervalo de datas a pesquisar marcacoes
 * @param final                 Ultima data do intervalo de datas a pesquisar marcacoes
 * @param ordem                 Ordem(data) com que as marcacoes aparecem     0 de forma crescente    1 de forma decrescente
 */
void generate_all_billing(EST_HANDLER *arrayEstudios, DATA inicio, DATA final, char ordem[]);

/**
 * Funcao que pega num estudio especifico e escreve/imprime todas as suas datas de marcacoes e a sua ocupacao(dentro do intervalo [inicio-final]
 * Ela tambem faz o taxa total de ocupacao desse estudio e retorna
 * @param estudio               Apontador para o estudio selecionado
 * @param calendario            Apontador para o calendario do estudio selecionado
 * @param fw                    Apontador para o ficheiro onde os dados sao escritos
 * @param inicio                Primeira DATA do intervalo de datas a pesquisar
 * @param final                 Ultima DATA do intervalo de datas a pesquisar
 * @param ordem                 Ordem(data) com que as marcacoes aparecem     0 de forma crescente    1 de forma decrescente
 * @return                      Taxa total de ocupacao do estudio selecionado
 */
float return_estudioOcu_selected_data(EST *estudio, CALEND *calendario, FILE *fw, DATA inicio, DATA final, char ordem[]);

/**
 * Funcao que gera o relatorio de taxa de ocupacao de um estudio
 * @param estudio           Apontador do estudio selecionado para o relatorio
 * @param inicio            Primeira data do intervalo de datas a pesquisar nas marcacoes
 * @param final             Ultima data do intervalo de datas a pesquisar nas marcacoes
 * @param ordem             Ordem(data) com que as marcacoes aparecem     0 de forma crescente   1 de forma decrescente
 */
void generate_estudio_occupation(EST *estudio, DATA inicio, DATA final, char ordem[]);

/**
 * Funcao que gera o relatorio de taxa de ocupacao de um edificio
 * @param arrayEstudios      Apontador para o array dinamico de estudios
 * @param edificio           Apontador para o edificio selecionado para o relatorio
 * @param inicio             Primeira data do intervalo de datas a pesquisar marcacoes
 * @param final              Ultima data do intervalo de datas a pesquisar marcacoes
 * @param ordem              Ordem(data) com que as marcacoes aparecem     0 de forma crescente   1 de forma decrescente
 */
void generate_edificio_occupation(EST_HANDLER *arrayEstudios, ED *edificio, DATA inicio, DATA final, char ordem[]);

/**
 * Funcao que gera o relatorio de taxa de ocupacao de todos os edificios
 * @param arrayEstudios         Apontador para o array dinamico de estudios
 * @param inicio                Primeira data do intervalo de datas a pesquisar marcacoes
 * @param final                 Ultima data do intervalo de datas a pesquisar marcacoes
 * @param ordem                 Ordem(data) com que as marcacoes aparecem     0 de forma crescente    1 de forma decrescente
 */
void generate_all_occupation(EST_HANDLER *arrayEstudios, DATA inicio, DATA final, char ordem[]);

/**
 * Funcao que retorna a taxa de ocupacao de um estudio num intervalo de data especifico
 * @param estudio               Apontador para o estudio selecionado
 * @param calendario            Apontador para o calendario desse estudio
 * @param inicio                Primeira data do intervalo de datas a pesquisar marcacoes
 * @param final                 Ultima data do intervalo de datas a pesquisar marcacoes
 * @return                      Taxa de ocupacao do estudio para as datas definidas
 */
float return_estudioOcu(EST *estudio, CALEND *calendario, DATA inicio, DATA final);

#endif //UFP_ALOJAMENTOS_REPORT_GENERATOR_H

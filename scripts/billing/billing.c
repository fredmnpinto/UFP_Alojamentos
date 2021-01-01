//
// Created by Frederico on 30/11/2020.
//
#define CHAR_LIMIT 1024
#include "billing.h"
#include "../data_handler/data_reader.h"

RP *get_data_rp() {   /// TEMPLATE PARA GET_DATA EM ARRAYS DINAMICOS
    FILE *fr = fopen("../data/regras_preco.csv", "r");
    char delimiter[] = ",";
    int num_rp = get_number_of_lines(fr);
    //printf("regras_preco.csv has %d lines\n", num_rp);
    RP *rp_array = (RP *) malloc(sizeof(RP) * (num_rp));           // Guarda somente 200 objetos de Regras
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char) getchar();
        if (get_lower_c(answer) == 'y') {
            FILE *fw = fopen(".data/regras_preco.csv", "w");
            fprintf(fw, "id,regra,taxa\n");
            fclose(fw);
        }
    } else {
        char buffer[CHAR_LIMIT];    // Guarda somente os primeiros CHAR_LIMIT caracteres, nesse primeiro momento 1024, por exemplo

        int row_count = 0, field_count;

        while(fgets(buffer, CHAR_LIMIT, fr)){
            field_count = 0;
            row_count++;
            if (row_count == 1)
                continue;

            char *field = strtok(buffer, delimiter);
            while (field_count < 3){
//                printf("%s\t", field);
                switch (field_count){   // id, regra, taxa
                    case 0: {
                        rp_array[row_count - 2].id = atol(field);
                        break;
                    }
                    case 1: {
                        strcpy(rp_array[row_count - 2].regra, field);
                        remove_linebreak_on_the_end(rp_array[row_count-2].regra);
                        break;
                    }
                    case 2: {
                        rp_array[row_count-2].taxa= atol(field);
                        break;
                    }
                    default :{
                        printf("WARNING: Possible unreadable data in 'regras_preco.csv'\n");
                    }

                }
                field = strtok(NULL, delimiter);
                field_count++;
            }
        }

    }
    fclose(fr);

//    RP * dynamic_rp = rp_dyn_arr(rp_array, *num_rp); //Torna-lo em um array dinamico para retornar

    /*printf("Printing all rp that were read\n");
    print_rp(rp_array, num_rp); //Puramente por motivos de debug
*/
    return rp_array;
}

int generate_price_est(MARC* marcacao, EST* estudio, RP* regras, CALEND* estudioCalend) {
    //DATA hoje = get_today();      Nao funciona nao sei porque

    DATA hoje = {.dia=12, .mes=12, .ano=1212};  //APENAS UM EXEMPLO

    int Total = regras[11].taxa + estudio->precoDiario_base;     //Taxa por especificar o estudio + preco base

    if (strcmp(estudio->configuracao, "T2") == 0) {
        Total += regras[0].taxa;
    } else if (strcmp(estudio->configuracao, "T3") == 0) {          //CONFIGURACAO DO ESTUDIO
        Total += regras[1].taxa;
    } else if (strcmp(estudio->configuracao, "T3D") == 0) {
        Total += regras[19].taxa;
    }

    if (marcacao->duracao < 7) {
        Total += regras[13].taxa;
    } else if (marcacao->duracao <= 30) {                           //DURACAO DA ESTADIO
        Total += regras[14].taxa;
    } else if (marcacao->duracao > 30) {
        Total += regras[15].taxa;
    }

    DATA diff = return_data_difference(marcacao->data, hoje);
    if(diff.ano>=1) {
        Total += regras[5].taxa;
    }else if(diff.mes>=6) {
        Total += regras[4].taxa;
    }else if(diff.mes>=3) {                                        //DATA DE ANTECEDENCIA DA MARCACAO
        Total += regras[3].taxa;
    }else if(diff.mes>=1) {
        Total += regras[2].taxa;
    }

    if(marcacao->data.mes > 6 && marcacao->data.mes < 9) {          //EPOCA ALTA VS. EPOCA BAIXA
        Total += regras[7].taxa;
    }else{
        Total += regras[6].taxa;
    }

    if (strcmp(marcacao->plataforma, "A")) {
        Total += regras[8].taxa;
    } else if (strcmp(marcacao->plataforma, "B")) {               //PLATAFORMA EM QUE ESTA A SER MARCADA
        Total += regras[9].taxa;
    } else if (strcmp(marcacao->plataforma, "C")) {
        Total += regras[10].taxa;
    }

    DATA inicio = {.ano = marcacao->data.ano-1, .mes = marcacao->data.mes, .dia= marcacao->data.dia};
    DATA final = {.ano= marcacao->data.ano+1, .mes=marcacao->data.mes, .dia=marcacao->data.dia};
    float ocupacao = return_estudioOcu(estudio, estudioCalend,inicio, final);

    if(ocupacao>0.65) {
        Total+=regras[16].taxa;
    }else if(ocupacao>=0.25) {
        Total+=regras[17].taxa;                                     //TAXA DE OCUPACAO NUM INTERVALO DE UM ANO ANTES E DEPOIS DA DATA MARCADA
    }else if(ocupacao<0.25) {
        Total+=regras[18].taxa;
    }

    return Total;
}

void print_rp(RP* rp_array, int array_size){
    for (int i = 0; i < array_size; ++i) {
        printf("ID: %d\n", rp_array[i].id);
        printf("REGRA: %s\n", rp_array[i].regra);
        printf("TAXA: %d\n", rp_array[i].taxa);
    }
}


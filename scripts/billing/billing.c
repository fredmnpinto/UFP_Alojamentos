//
// Created by Frederico on 30/11/2020.
//

#include "billing.h"

RP *get_data_rp(int *num_rp) {   /// TEMPLATE PARA GET_DATA EM ARRAYS DINAMICOS
    FILE *fr = fopen("./data/regras_preco.csv", "r");
    char delimiter[] = ",";
    *num_rp = get_number_of_lines(fr);
    printf("regras_preco.csv has %d lines\n", *num_rp);
    RP rp_array[200];           // Guarda somente 200 objetos de Regras
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char)getchar();
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

    RP * dynamic_rp = rp_dyn_arr(rp_array, *num_rp); //Torna-lo em um array dinamico para retornar

    printf("Printing all rp that were read\n");
    print_rp(dynamic_rp, *num_rp); //Puramente por motivos de debug

    return dynamic_rp;
}

void print_rp(RP* rp_array, int array_size){
    for (int i = 0; i < array_size; ++i) {
        printf("ID: %d\n", rp_array[i].id);
        printf("REGRA: %s\n", rp_array[i].regra);
        printf("TAXA: %d\n", rp_array[i].taxa);
    }
}
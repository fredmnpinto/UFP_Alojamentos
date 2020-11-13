//
// Created by Frederico on 06/11/2020.
//

#include "data_handler.h"
#define CHAR_LIMIT 1024

ALOJ *get_aloj_data(int *num_alojs) {
    FILE *fr = fopen("./data/aloj.csv", "r");
    char delimiter[] = ",";
     *num_alojs = get_number_of_lines(fr);
    printf("aloj.csv has %d lines\n", *num_alojs);
    ALOJ aloj_array[200];           // Guarda somente 200 objetos de Alojamentos
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        exit(errno);
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
                printf("%s ", field);
                switch (field_count){   // id, estudio_id, tipo
                    case 0: {
                        aloj_array[row_count - 2].id = atol(field);

                        break;
                    }
                    case 1: {
                        aloj_array[row_count - 2].estudio_id = atol(field);
                        break;
                    }
                    case 2: {
                        strcpy(aloj_array[row_count - 2].tipo, field);
                        break;
                    }
                    default :{
                        printf("WARNING: Possible unreadable data in 'aloj.csv'\n");
                    }

                }
                field = strtok(NULL, delimiter);
                field_count++;
            }
        }

    }
    fclose(fr);

    ALOJ * dynamic_aloj = aloj_dyn_arr(aloj_array, *num_alojs);

    printf("Printing all alojs that were read\n");
    print_alojs(dynamic_aloj, *num_alojs);

    return dynamic_aloj;
}

int get_number_of_lines(FILE *fr){
    int result = 0;
    for (char c = getc(fr); c != EOF ; c = getc(fr)) {
        if (c == '\n')
            result++;
    }
    rewind(fr);
    return result - 1;
}

ALOJ *aloj_dyn_arr(ALOJ *static_array, int size){
    ALOJ * new_array = malloc(sizeof(ALOJ) * size); // Array dinamico declarado (Ainda vazio)

    for (int i = 0; i < size; ++i) {    // Preenchendo array dinamico com os valores do array estatico
        new_array[i].id = static_array[i].id;
        new_array[i].estudio_id = static_array[i].estudio_id;
        strcpy(new_array[i].tipo, static_array[i].tipo);
    }
    return new_array;
}

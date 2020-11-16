//
// Created by Frederico on 06/11/2020.
//

#include "data_reader.h"
#define CHAR_LIMIT 1024

void get_data_main(int argc, char* argv[]){
    if (argc <= 1) {
        printf("Invalid number of argument\n");
        return;
    }
    char* types[] = {
      "aloj",
      "edif",
      "estu",
      "agenda",
    };
    void (*read_functions[])(int c, char** v) = {
            get_data_main,
    };
    int i = 0;
    do{
        if (strcmp(argv[1], types[i]) == 0){

        }
        i++;
    }while(i < argc);
}

ALOJ *get_data_aloj(int *num_alojs) {
    FILE *fr = fopen("./data/aloj.csv", "r");
    char delimiter[] = ",";
    *num_alojs = get_number_of_lines(fr);
    printf("aloj.csv has %d lines\n", *num_alojs);
    ALOJ aloj_array[200];           // Guarda somente 200 objetos de Alojamentos
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char)getchar();
        if (get_lower_c(answer) == 'y') {
            FILE *fw = fopen(".data/aloj.csv", "w");
            fprintf(fw, "id,estudio_id,tipo\n");
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
                        remove_linebreak_on_the_end(aloj_array[row_count - 2].tipo);
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

    ALOJ * dynamic_aloj = aloj_dyn_arr(aloj_array, *num_alojs); //Torna-lo em um array dinamico para retornar

    printf("Printing all alojs that were read\n");
    print_alojs(dynamic_aloj, *num_alojs); //Puramente por motivos de debug

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
    ALOJ * new_array = malloc(sizeof(ALOJ) * size); // Array dinamico declarado

    for (int i = 0; i < size; ++i) {    // Preenchendo array dinamico com os valores do array estatico
        new_array[i].id = static_array[i].id;
        new_array[i].estudio_id = static_array[i].estudio_id;
        strcpy(new_array[i].tipo, static_array[i].tipo);
    }
    return new_array;
}

ED* get_data_edfs(){
    FILE *fr = fopen("./data/edfs.psv", "r");
    ED *head = NULL, *aux, *tail;
    ED *tmp = (ED*)malloc(sizeof(ED));
    char delimiter[] = "|";
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char)getchar();
        if (get_lower_c(answer) == 'y') {
            FILE *fw = fopen(".data/edfs.psv", "w");
            fprintf(fw, "id,estudio_id,tipo\n");
            fclose(fw);
        }
    } else {
        printf("edfs.psv has %d lines\n", get_number_of_lines(fr));
        char buffer[CHAR_LIMIT];    // Guarda somente os primeiros CHAR_LIMIT caracteres, nesse primeiro momento 1024, por exemplo
        int row_count = 0, field_count;

        printf("\t");
        while(fgets(buffer, CHAR_LIMIT, fr)){
            tail = tmp;
            field_count = 0;
            row_count++;

            if (row_count == 1) {
                continue;
            }

            char *field = strtok(buffer, delimiter);
            while (field_count < 5){
                switch (field_count){   // id, endereco_str, endereco_lat, endereco_longi, nome
                    case 0: {
                        tmp->id = atol(field);
                        break;
                    }
                    case 1: {
                        strcpy(tmp->endereco.endereco, field);
                        break;
                    }
                    case 2: {
                        tmp->endereco.lat = atof(field);

                        break;
                    }
                    case 3: {
                        tmp->endereco.longi = atof(field);

                        break;
                    }
                    case 4: {
                        remove_linebreak_on_the_end(field);
                        strcpy(tmp->nome, field);
                        break;
                    }
                    default :{
                        printf("WARNING: Possible unreadable data in 'aloj.csv'\n");
                    }

                }

                printf("'%s'\t", field);
                field = strtok(NULL, delimiter);
                field_count++;
            }
            if (head == NULL) {
                head = tmp;
                tmp = (ED*)malloc(sizeof(ED));
                head->next = tmp;
            }
            else{
                aux = (ED*)malloc(sizeof(ED));
                tmp->next = aux;   //Esta a adicionar todos os elementos sempre a frente da lista
                tmp = aux;
            }
        }
        free(aux);
        tail->next = NULL;
    }
    fclose(fr);
    print_edfs_list(head);
    return head;
}

void print_edfs_list(ED *head){
    ED *tmp = head;
    while(tmp != NULL){
        printf("\nId: %d\nNome: %s\nEndereco: %s\t(lat: %f longi: %f)\n", tmp->id, tmp->nome, tmp->endereco.endereco, tmp->endereco.lat, tmp->endereco.longi);
        tmp = tmp->next;
    }
}


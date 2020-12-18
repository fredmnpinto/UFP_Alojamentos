//
// Created by Frederico on 06/11/2020.
//

#include "data_reader.h"
#include "../API/edificios.h"
#include "../API/estudios.h"
#include "../API/agendas.h"
#include "../API/historicoReservas.h"
#include "../API/guests_list.h"
#define CHAR_LIMIT 1024

void get_data_main(int argc, char* argv[]){
    if (argc <= 1) {
        printf("Invalid number of argument\n");
        return;
    }
    char* types[] = {
      "aloj",
      "ed",
      "est",
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

void read_est(){

}

ALOJ *get_data_aloj(int *num_alojs) {   /// TEMPLATE PARA GET_DATA EM ARRAYS DINAMICOS
    FILE *fr = fopen("../data/aloj.csv", "r");
    char delimiter[] = ",";
    *num_alojs = get_number_of_lines(fr);
//    printf("aloj.csv has %d lines\n", *num_alojs);
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
    system("cls");
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

ED_LIST * get_data_edfs(){    ///TEMPLATE PARA GET_DATA EM LISTAS LIGADAS
    FILE *fr = fopen("../data/edfs.psv", "r");
    ED *head = NULL, *aux, *tail;
    ED *tmp = (ED*)malloc(sizeof(ED));
    ED_LIST *edList = initEdList();
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
//        printf("edfs.psv has %d lines\n", get_number_of_lines(fr));
        char buffer[CHAR_LIMIT];    // Guarda somente os primeiros CHAR_LIMIT caracteres, nesse primeiro momento 1024, por exemplo
        int row_count = 0, field_count;

        while(fgets(buffer, CHAR_LIMIT, fr)){
            tail = tmp;
            field_count = 0;
            row_count++;

            if (row_count == 1) {
                edList->fHeader = (char *) malloc(sizeof(char) * strlen(buffer));
                strcpy(edList->fHeader, buffer);
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
                        tmp->endereco.endereco = (char *) malloc(sizeof(char) * (strlen(field) + 1));
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
                        tmp->nome = (char *) malloc(sizeof(char) * (strlen(field) + 1));
                        strcpy(tmp->nome, field);
                        break;
                    }
                    default :{
                        printf("WARNING: Possible unreadable data in 'aloj.csv'\n");
                    }

                }

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
        edList->tail = tail;
    }
    fclose(fr);
    edList->head = head;
//    edList->print(edList);
    system("cls");
    return edList;
}

EST_HANDLER *get_data_estudio() {
    char *file_path = "../data/estudio.psv";
    FILE *fr = fopen(file_path, "r");
    char *header;
    char delimiter[] = "|";
    int size = get_number_of_lines(fr);
    int *agendaMasterIds = (int *) malloc(sizeof(int) * (size));
    int *agendasHandlerIds = (int *) malloc(sizeof(int) * (size));
//    printf("%s has %d lines\n", file_path, *size);
    EST *est_array = (EST *) malloc((size) * sizeof(EST));
    EST_HANDLER *estHandler = initEstHandler(est_array, size);
    if (fr == NULL) {
        perror("get_data_estudio ERROR");
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char) getchar();
        if (get_lower_c(answer) == 'y') {
            FILE *fw = fopen(file_path, "w");
            fprintf(fw, "%s", estHandler->header);
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

            char *field = strtok(buffer, delimiter);    // HEADER: id | edificio_id | nome | agenda_master_id | outras_agendas_id
            while (field_count < 5){
                switch (field_count){   // id, estudio_id, tipo
                    case 0: {
                        est_array[row_count - 2].id = atoi(field);
                        // Lembrando, row_count - 2 chega nesse meio com o valor minimo de 0 (2 - 2)
                        break;
                    }
                    case 1: {
                        est_array[row_count - 2].edificio_id = atoi(field);
                        break;
                    }
                    case 2: {
                        est_array[row_count - 2].nome = (char *) malloc(sizeof(char) * (strlen(field) + 1));
                        strcpy(est_array[row_count - 2].nome, field);
                        break;
                    }
                    case 3: {
                        /*
                         * Cuidado! Tanto a funcao em que estamos quanto a que estamos a ver usam o strtok
                         * Portanto, quando saimos da seguinte funcao, a variavel global que estavamos
                         * usando para guardar o que sobrou de buffer, ja esta comprometida e com NULL
                         */
                        int fieldN = atoi(field);
//                        est_array[row_count - 2].agenda_master = get_data_agenda_master(atoi(field));
                        agendaMasterIds[row_count - 2] = fieldN;
                        break;
                    }
                    case 4: {
                        int fieldN = atoi(field);
                        /*
                         * Cuidado! Tanto a funcao em que estamos quanto a que estamos a ver usam o strtok
                         * Portanto, quando saimos da seguinte funcao, a variavel global que estavamos
                         * usando para guardar o que sobrou de buffer, ja esta comprometida e com NULL
                         */
//                        est_array[row_count - 2].outrasHandler = get_data_agendas_outras(fieldN);
                        agendasHandlerIds[row_count - 2] = fieldN;
                        break;
                    }
                    default : {
                        printf("WARNING: Possible unreadable data in '%s'\n", file_path);
                    }

                }
                field = strtok(NULL, delimiter);
                field_count++;
            }
        }
    }
    fclose(fr);
    for (int i = 0; i < size; ++i) {
        estHandler->estArray[i].agenda_master = get_data_agenda_master(agendaMasterIds[i]);
        estHandler->estArray[i].outrasHandler = get_data_agendas_outras(agendasHandlerIds[i]);
    }
    system("cls");
    return estHandler;
}

AGENDA* get_data_agenda_master(int agenda_id){   //DONE
    char *filepath = get_filepath_agenda_master(agenda_id);
    FILE* data = fopen(filepath, "r");
    char delimiter[] = "|";
    int agenda_size = get_number_of_lines(data);
//    printf("%s has %d lines\n", filepath, agenda_size);
    MARC *datas_array = (MARC*)malloc(sizeof(MARC) * agenda_size);
    if (data == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char)getchar();
        if (get_lower_c(answer) == 'y') {
            FILE *fw = fopen(filepath, "w");
            fprintf(fw, "dia|mes|ano|descricao\n");
            fclose(fw);
        }
        else {
            exit(-1);
        }
    } else {
        char buffer[CHAR_LIMIT];    // Guarda somente os primeiros CHAR_LIMIT caracteres, nesse primeiro momento 1024, por exemplo

        int row_count = 0, field_count;

        while(fgets(buffer, CHAR_LIMIT, data)){
            field_count = 0;
            row_count++;
            if (row_count == 1)
                continue;

            char *field = strtok(buffer, delimiter);
            while (field_count < 4) {
                remove_linebreak_on_the_end(field);
//                printf("%s\t", field);
                switch (field_count){   // dia|mes|ano|descricao
                    case 0: {
                        datas_array[row_count - 2].data.dia = atoi(field);

                        break;
                    }
                    case 1: {
                        datas_array[row_count - 2].data.mes = atoi(field);
                        break;
                    }
                    case 2: {
                        datas_array[row_count - 2].data.ano = atoi(field);
                        break;
                    }
                    case 3: {
                        datas_array[row_count - 2].descricao = (char*)malloc(sizeof(char)*strlen(field) + 1);
                        strcpy(datas_array[row_count - 2].descricao, field);
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
    fclose(data);
    AGENDA *agenda_master = (AGENDA*)malloc(sizeof(AGENDA));
    agenda_master->id = agenda_id;
    agenda_master->size = agenda_size;
    agenda_master->marcacoes = datas_array;
    agenda_master->path = filepath;
    system("cls");
    return agenda_master;
}

char* get_filepath_agenda_master(int id){
    char* file_preset1 = "../data/agendas/masters/";
    char* file_preset2 = "_master.psv";
    char fnum[6];
    itoa(id, fnum, 10);
    char* file_path = (char*)malloc(sizeof(char) * (strlen(file_preset1) + strlen(file_preset2) + strlen(fnum) + 1));
    strcpy(&file_path[0], file_preset1);
    strcpy(&file_path[strlen(file_path)], fnum);
    strcpy(&file_path[strlen(file_path)], file_preset2);
    return file_path;
}

char* get_filepath_agenda_outra(int id){
    char* file_preset1 = "../data/agendas/outras/";
    char* file_preset2 = "_outra.psv";
    char fnum[6];
    itoa(id, fnum, 10);
    char* file_path = (char*)malloc(sizeof(char) * (strlen(file_preset1) + strlen(file_preset2) + strlen(fnum) + 1));
    strcpy(&file_path[0], file_preset1);
    strcpy(&file_path[strlen(file_path)], fnum);
    strcpy(&file_path[strlen(file_path)], file_preset2);
    return file_path;
}

AGENDA* get_data_single_agenda_outra(int id){

    /*
     *                    <#--- Logica ---#>
     * Para esse field especifico sera usada a seguinte logica:
     * No arquivo .psv dos estudios, quanto a isso, somente tera
     * guardado o id do Agendas Handler, que sera usado para
     * chegar ao arquivo .psv do dito cujo. Nesse novo arquivo
     * tera guardado os id's de todas as agendas associadas ao
     * respectivo estudio sendo lido.
    */
    AGENDA* new_agenda;

    char *file_path = get_filepath_agenda_outra(id);// File path configured

    FILE *fr = fopen(file_path, "r");
    const char delimiter[] = "|";
    int n_lines = get_number_of_lines(fr);
//    printf("aloj.csv has %d lines\n", n_lines);
    // Cria o array de marcacoes dessa agenda
    MARC *marc_array;
    printf("Allocated %d marc slots\nsizeof(MARC) = %d\tsizeof(marc_array) = %d\n", n_lines, sizeof(MARC), sizeof(marc_array));
//    n_lines = 10;
    marc_array = (MARC*)malloc((n_lines) * sizeof(MARC));
    // No caso de um erro procurando pelo arquivo
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char)getchar();
        if (get_lower_c(answer) == 'y') {
            FILE *fw = fopen(".data/estudio.csv", "w");
            fprintf(fw, "Dia|Mes|Ano|Descricao\n");
            fclose(fw);
        }
        else {
            exit(-1);
            }
    } else {
        // Guarda somente os primeiros CHAR_LIMIT caracteres, nesse primeiro momento 1024, por exemplo
        char *buffer = (char*)malloc(sizeof(char)*CHAR_LIMIT);
        int row_count = 0, field_count;

        while(fgets(buffer, CHAR_LIMIT, fr)){
            field_count = 0;
            row_count++;
            if (row_count == 1)
                continue;
//            printf("Row_count - 2 = %d\n", row_count - 2);
            char *field = strtok(buffer, delimiter);    // HEADER:  Dia  |   Mes |   Ano |   Descricao
            while (field_count < 4){
//                printf("field_count = %d\n", field_count);
//                printf("field = %s\n", field);
                switch (field_count){
                    case 0: {
                        int field_n = atoi(field);
                        printf(field_n <= 31 || field_n >= 1 ? NULL : "Erro no dia (%d) da marcacao numero %d de %s\n", field_n, id, file_path);
                        marc_array[row_count - 2].data.dia = field_n; // Dia
                        break;
                    }
                    case 1: {
                        int field_n = atoi(field);
                        printf(field_n <= 12 || field_n >= 1 ? NULL : "Erro no mes (%d) da marcacao numero %d de %s\n", field_n, id, file_path);
                        marc_array[row_count - 2].data.mes = atoi(field); // Mes
                        break;
                    }
                    case 2: {
                        int field_n = atoi(field);
                        printf(field_n < 2100 || field_n > 1900 ? NULL : "Erro no ano (%d) da marcacao numero %d de %s\n", field_n, id, file_path);
                        marc_array[row_count - 2].data.ano = field_n; // Ano
                        break;
                    }
                    case 3: {
                        marc_array[row_count - 2].descricao = (char*)malloc(sizeof(char)* (strlen(field) + 1));
                        strcpy(marc_array[row_count - 2].descricao, field);
                        remove_linebreak_on_the_end(marc_array[row_count - 2].descricao);
                        break;
                    }
                    default : {
                        printf("WARNING: Possible unreadable data in line %d of '%s'\n", row_count, file_path);
                    }

                }
                field = strtok(NULL, delimiter);
                field_count++;
            }
        }
//        printf("Got here too\n");
        new_agenda = init_single_agenda(marc_array, n_lines, id, file_path);
        free(buffer);
    }
    fclose(fr);
    system("cls");
    return new_agenda;
}

char* get_filepath_agendas_handler(int handler_id) {
    // data/agendas/outras_handlers/1234_handler.psv
    char *file_preset1 = "../data/agendas/outras_handlers/";
    char *file_preset2 = "_handler.psv";
    char fnum[6];
    itoa(handler_id, fnum, 10);
    char *file_path;
    file_path = (char *) malloc(sizeof(char) * (strlen(file_preset1) + strlen(file_preset2) + strlen(fnum) + 1));
    strcpy(&file_path[0], file_preset1);
    strcpy(&file_path[strlen(file_path)], fnum);
    strcpy(&file_path[strlen(file_path)], file_preset2);
    return file_path;
}

AGENDAS_HANDLER * get_data_agendas_outras(int handler_id){
    char *file_path = get_filepath_agendas_handler(handler_id);// File path configured
    FILE *fr = fopen(file_path, "r");
    const char delimiter[] = "|";
    const int n_lines = get_number_of_lines(fr);
//    printf("%s has %d lines\n", file_path, n_lines);
    // Cria o array de marcacoes dessa agenda
    // inicializando a propria
    AGENDAS_HANDLER* agendasHandler = init_outras_handler(NULL, n_lines, handler_id);
    agendasHandler->agendas = (AGENDA *) malloc((n_lines) * sizeof(AGENDA));
    agendasHandler->filepath = file_path;

    // No caso de um erro procurando pelo arquivo
    if (fr == NULL) {
        perror("get_data_agendas_outras Error oppening file");
        printf("Do you wish to create an empty new file on %s?\n[Y]es --- [N]o\n", file_path);
        char answer = (char)getchar();
        if (get_lower_c(answer) == 'y') {
            FILE *fw = fopen(file_path, "w");
            fprintf(fw, "outra_id|nome\n");
            fclose(fw);
        }
        else {
            exit(-1);
        }
    } else {
        // Guarda somente os primeiros CHAR_LIMIT caracteres, nesse primeiro momento 1024, por exemplo
        char *buffer = (char*)malloc(sizeof(char)*CHAR_LIMIT);
//        printf("n_lines = %d\n", n_lines);
        int row_count = 0, field_count;

        while(fgets(buffer, CHAR_LIMIT, fr)){
            field_count = 0;
            row_count++;
            if (row_count == 1)
                continue;

            char *field = strtok(buffer, delimiter);    // HEADER:  id  |   nome
            while (field_count < 2){
//                printf("%s\t", field);
                switch (field_count){
                    case 0: {
                        int field_n = atoi(field);
                        printf(field_n > 0 ? NULL : "Erro no id (%d) da agenda numero %d de %s\n", field_n, handler_id, file_path);
                        agendasHandler->agendas[row_count - 2].id = field_n; // Id
                        break;
                    }
                    case 1: {
                        agendasHandler->agendas[row_count - 2].nome = (char*)malloc(sizeof(char) * (strlen(field) + 1));
                        strcpy(agendasHandler->agendas[row_count - 2].nome, field);
                        remove_linebreak_on_the_end(agendasHandler->agendas[row_count - 2].nome);
                        break;
                    }
                    default :{
                        printf("WARNING: Possible unreadable data in line %d of '%s'\n", row_count, file_path);
                    }

                }
                field = strtok(NULL, delimiter);
                field_count++;
            }
        }
        // Nesse ponto as agendas foram inicializadas mas nao por inteiro, somente
        // seu id e seu nome ainda precisa-se que pegue os outros parametros dela a partir disso
        // para isso chamamos a funcao get_data_single_agenda(id);
        for (int i = 0; i < n_lines; ++i) {
            // Consegue ler perfeitamente a primeira agenda, mas nem sequer comeca a segunda
            agendasHandler->agendas[i] = *get_data_single_agenda_outra(agendasHandler->agendas[i].id);
        }
        free(buffer);
    }
    fclose(fr);
    system("cls");
    return agendasHandler;
}

HOSP_STACK* get_data_hosp() {
    FILE *fr = fopen("../data/hospedes.csv", "r");
    HOSP *head = (HOSP*)malloc(sizeof(HOSP));
    HOSP_STACK *stack = init_guest_stack();
    char delimiter[] = ",";
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char)getchar();
        if (get_lower_c(answer) == 'y') {
            FILE *fw = fopen("../data/hospedes.csv", "w");
            fprintf(fw, "id,nome,email\n");
            fclose(fw);
        }
    } else {
        char buffer[CHAR_LIMIT];    // Guarda somente os primeiros CHAR_LIMIT caracteres, nesse primeiro momento 1024, por exemplo
        int row_count = 0, field_count;
        while(fgets(buffer, CHAR_LIMIT, fr)) {
            head = (HOSP*)malloc(sizeof(HOSP));
            field_count = 0;
            row_count++;
            if (row_count == 1) {
                continue;
            }
            char *field = strtok(buffer, delimiter);
            while (field_count < 3){
                switch (field_count){   // id, nome, email
                    case 0: {
                        head->id = atol(field);
                        break;
                    }
                    case 1: {
                        strcpy(head->nome, field);
                        break;
                    }
                    case 2: {
                        strcpy(head->email, field);
                        break;
                    }
                    default :{
                        printf("WARNING: Possible unreadable data in 'aloj.csv'\n");
                    }
                }
                field = strtok(NULL, delimiter);
                field_count++;
            }
            guests_lists_push(stack, head);
        }
    }
    fclose(fr);
    stack->head = head;
    return stack;
}

HIST_STACK* get_data_hist() {
    FILE *fr = fopen("../data/historico.csv", "r");
    HIST *head = (HIST*)malloc(sizeof(HIST));
    HIST_STACK *stack = init_hist_stack();
    char delimiter[] = ",";
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char)getchar();
        if (get_lower_c(answer) == 'y') {
            FILE *fw = fopen("..data/historico.csv", "w");
            fprintf(fw, "id,hospede_id,reserva\n");
            fclose(fw);
        }
    } else {
        char buffer[CHAR_LIMIT];    // Guarda somente os primeiros CHAR_LIMIT caracteres, nesse primeiro momento 1024, por exemplo
        int row_count = 0, field_count;
        printf("\t");
        stack->tail = head;
        while(fgets(buffer, CHAR_LIMIT, fr)) {
            head = (HIST*)malloc(sizeof(HIST));
            field_count = 0;
            row_count++;
            if (row_count == 1) {
                continue;
            }
            char *field = strtok(buffer, delimiter);
            while (field_count < 3){
                switch (field_count){   // id, hospede_id, reserva
                    case 0: {
                        head->id = atol(field);
                        break;
                    }
                    case 1: {
                        head->hospede_id = atol(field);
                        break;
                    }
                    case 2: {
                        strcpy(head->reserva, field);
                        break;
                    }
                    default :{
                        printf("WARNING: Possible unreadable data in 'historico.csv'\n");
                    }
                }
                field = strtok(NULL, delimiter);
                field_count++;
            }
            hist_list_push(stack, head);
        }
    }
    fclose(fr);
    stack->head = head;
    return stack;
}

//
// Created by Frederico on 06/11/2020.
//

#include "data_reader.h"
#include "../API/edificios.h"
#include "../API/estudios.h"
#include "../API/agendas.h"
#include "../API/historicoReservas.h"
#include "../API/guests_list.h"
#include "../API/eventos.h"
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

int get_number_of_lines(FILE *fr){
    int result = 0;
    for (char c = getc(fr); c != EOF ; c = getc(fr)) {
        if (c == '\n')
            result++;
    }
    rewind(fr);
    return result - 1;
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
        if (toLowerC(answer) == 'y') {
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
        if (toLowerC(answer) == 'y') {
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

            char *field = strtok(buffer, delimiter);    // HEADER: id | edificio_id | configuracao | precoDiario_base | agenda_master_id | outras_agendas_id
            while (field_count < 6){
                switch (field_count){
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
                        est_array[row_count - 2].configuracao = (char *) malloc(sizeof(char) * (strlen(field) + 1));
                        strcpy(est_array[row_count - 2].configuracao, field);
                        break;
                    }
                    case 3: {
                        est_array[row_count-2].precoDiario_base = atoi(field);
                        break;
                    }
                    case 4: {
                        /*
                         * Cuidado! Tanto a funcao em que estamos quanto a que estamos a ver usam o strtok
                         * Portanto, quando saimos da seguinte funcao, a variavel global que estavamos
                         * usando para guardar o que sobrou de buffer, ja esta comprometida e com NULL
                         */
                        int fieldN = atoi(field);
//                      est_array[row_count - 2].agenda_master = get_data_agenda_master(atoi(field));
                        agendaMasterIds[row_count - 2] = fieldN;
                        break;
                    }
                    case 5: {
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

AGENDA* get_data_agenda_master(int agenda_id) {   //DONE
    char *filepath = get_filepath_agenda_master(agenda_id);
    FILE* data = fopen(filepath, "r");
    char delimiter[] = "|";
    int agenda_size = get_number_of_lines(data);
//    printf("%s has %d lines\n", filepath, agenda_size);
    CALEND *calendario = (CALEND*)malloc(sizeof(CALEND) * agenda_size);
    if (data == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char)getchar();
        if (toLowerC(answer) == 'y') {
            FILE *fw = fopen(filepath, "w");
            fprintf(fw, "dia|mes|ano|plataforma|duracao|preco|hospededID|eventos\n");
            fclose(fw);
        } else {
            exit(-1);
        }
    } else {
        char buffer[CHAR_LIMIT];    // Guarda somente os primeiros CHAR_LIMIT caracteres, nesse primeiro momento 1024, por exemplo

        int row_count = 0, field_count;

        while(fgets(buffer, CHAR_LIMIT, data)){
            field_count = 0;
            row_count++;
            if (row_count == 1) {
                continue;
            }
            calendario[row_count-2].Eventos = init_event_stack();
            calendario[row_count-2].marcacao = (MARC*)malloc(sizeof(MARC));
            char* saveF;
            char *field = strtok_r(buffer, delimiter, &saveF);
            while (field_count<8) {
                remove_linebreak_on_the_end(field);
//                printf("%s\t", field);
                switch (field_count) {   // dia|mes|ano|plataforma|duracao|preco|hospedeID|eventos
                    case 0: {
                        calendario[row_count - 2].data.dia = atoi(field);
                        break;
                    }
                    case 1: {
                        calendario[row_count - 2].data.mes = atoi(field);
                        break;
                    }
                    case 2: {
                        calendario[row_count - 2].data.ano = atoi(field);
                        break;
                    }
                    case 3: {
                        if(strcmp(field, " ")==0) {
                            calendario[row_count-2].marcacao = NULL;
                            free(calendario[row_count-2].marcacao);
                        }else{
                            calendario[row_count-2].marcacao->plataforma = (char*)malloc(sizeof(char)*strlen(field));
                            strcpy(calendario[row_count-2].marcacao->plataforma, field);
                        }
                        break;
                    }
                    case 4: {
                        if(strcmp(field," ")==0) {
                            calendario[row_count-2].marcacao = NULL;
                            free(calendario[row_count-2].marcacao);
                        }else{
                            calendario[row_count-2].marcacao->duracao = atoi(field);
                        }
                        break;
                    }
                    case 5: {
                        if(strcmp(field," ")==0) {
                            calendario[row_count-2].marcacao = NULL;
                            free(calendario[row_count-2].marcacao);
                        }else{
                           calendario[row_count-2].marcacao->preco = atoi(field);
                        }
                        break;
                    }
                    case 6: {
                        if(strcmp(field," ")==0) {
                            calendario[row_count-2].marcacao = NULL;
                            free(calendario[row_count-2].marcacao);
                        }else{
                            calendario[row_count-2].marcacao->hospedeID = atoi(field);
                        }
                        break;
                    }
                    case 7: {
                        if(strcmp(field," ")==0) {
                            calendario[row_count-2].Eventos = NULL;
                            free(calendario[row_count-2].Eventos);
                        }else{
                            calendario[row_count-2].Eventos = add_data_event(field,calendario[row_count-2].Eventos);
                        }
                        break;
                    }
                    default : {
                        printf("WARNING: Possible unreadable data in '%s.psv'\n", filepath);
                    }
                }
                field = strtok_r(saveF, delimiter, &saveF);
                field_count++;
            }
        }
    }
    fclose(data);
    AGENDA *agenda_master = (AGENDA*)malloc(sizeof(AGENDA));
    agenda_master->id = agenda_id;
    agenda_master->size = agenda_size;
    agenda_master->calendario = calendario;
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
    CALEND *calendario;
    printf("Allocated %d CALEND slots\nsizeof(CALEND) = %d\tsizeof(calendario) = %d\n", n_lines, sizeof(CALEND), sizeof(calendario));
//    n_lines = 10;
    calendario = (CALEND*)malloc((n_lines) * sizeof(CALEND));
    // No caso de um erro procurando pelo arquivo
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        printf("Do you wish to create an empty new file?\n[Y]es --- [N]o\n");
        char answer = (char)getchar();
        if (toLowerC(answer) == 'y') {
            FILE *fw = fopen(".data/estudio.csv", "w");
            fprintf(fw, "Dia|Mes|Ano|Descricao\n");
            fclose(fw);
        } else {
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
            calendario[row_count-2].marcacao = (MARC*)malloc(sizeof(MARC));
//            printf("Row_count - 2 = %d\n", row_count - 2);
            char *field = strtok(buffer, delimiter);    // HEADER:  Dia  |   Mes |   Ano |   Descricao
            while (field_count < 4){
//                printf("field_count = %d\n", field_count);
//                printf("field = %s\n", field);
                switch (field_count){
                    case 0: {
                        int field_n = atoi(field);
                        printf(field_n <= 31 || field_n >= 1 ? NULL : "Erro no dia (%d) da marcacao numero %d de %s\n", field_n, id, file_path);
                        calendario[row_count-2].data.dia = field_n; // Dia
                        break;
                    }
                    case 1: {
                        int field_n = atoi(field);
                        printf(field_n <= 12 || field_n >= 1 ? NULL : "Erro no mes (%d) da marcacao numero %d de %s\n", field_n, id, file_path);
                        calendario[row_count - 2].data.mes = atoi(field); // Mes
                        break;
                    }
                    case 2: {
                        int field_n = atoi(field);
                        printf(field_n < 2100 || field_n > 1900 ? NULL : "Erro no ano (%d) da marcacao numero %d de %s\n", field_n, id, file_path);
                        calendario[row_count - 2].data.ano = field_n; // Ano
                        break;
                    }
                    case 3: {
                        if(strcmp(field,"")==0) {
                            calendario[row_count-2].marcacao = NULL;
                            free(calendario[row_count-2].marcacao);
                        }else{
                            calendario[row_count - 2].marcacao->plataforma = (char*)malloc(sizeof(char)* (strlen(field) + 1));
                            strcpy(calendario[row_count - 2].marcacao->plataforma, field);
                            remove_linebreak_on_the_end(calendario[row_count - 2].marcacao->plataforma);
                        }
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
        new_agenda = init_single_agenda(calendario, n_lines, id, file_path);
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
        if (toLowerC(answer) == 'y') {
            FILE *fw = fopen(file_path, "w");
            fprintf(fw, "outra_id|nome\n");
            fclose(fw);
        } else {
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
            while (field_count < 1){
//                printf("%s\t", field);
                switch (field_count){
                    case 0: {
                        int field_n = atoi(field);
                        printf(field_n > 0 ? NULL : "Erro no id (%d) da agenda numero %d de %s\n", field_n, handler_id, file_path);
                        agendasHandler->agendas[row_count - 2].id = field_n; // Id
                        break;
                    }
                    /*case 1: {
                        agendasHandler->agendas[row_count - 2].nome = (char*)malloc(sizeof(char) * (strlen(field) + 1));
                        strcpy(agendasHandler->agendas[row_count - 2].nome, field);
                        remove_linebreak_on_the_end(agendasHandler->agendas[row_count - 2].nome);
                        break;
                    }*/
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
        if (toLowerC(answer) == 'y') {
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
                        head->nome = (char*)malloc(sizeof(char)*strlen(field));
                        strcpy(head->nome, field);
                        break;
                    }
                    case 2: {
                        head->email = (char*)malloc(sizeof(char)*strlen(field));
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
        if (toLowerC(answer) == 'y') {
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

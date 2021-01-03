//
// Created by Frederico on 31/12/2020.
//

#include "commandLineHandler.h"

/*
 * MINHA IDEIA
 * Podemos fazer da seguinte forma
 * Lembrando argv[0] é o path do programa
 * -- argv[1]: O primeiro argumento, ou seja argv[1], será o comando no estilo CRUD [Create Read Update Delete]
 *      Podemos tambem fazer comandos separados, como generate report, ou coisa do genero
 * -- argv[2]: O segundo argumento sera o alvo, ou seja, edificio, estudio, agenda, relatorio, etc
 * -- argv[3]: Os ultimos argumentos serao especificos de cada comando, por exemplo, read estudio 1 availability 3 (Le as proximas 3 datas em que o estudio de id=1 estara disponivel)
 *
 */

void mainCmd(int argc, char *argv[]) {
    if (argc < 3) {
        errorNumberArguments(argc);
        return;
    }
    char *proj_name = "PortoFlats";
    char *commands[] = {
            "read",
            "update",
            "delete",
            "create"
    };


    void (*functions[])(int argc, char *argv[]) = {
            readHandler,
            updateHandler,
            deleteHandler,
            createHandler,
    };
//    system("cls");
    printf("\n\n\n- - - - Welcome to %s - - - -\n", proj_name);
    for (int i = 0; i < 4; ++i) {
//        printf("argv[%d] = '%s'\n", i, argv[i]);
        if (strcmp(commands[i], argv[1]) == 0) {
            functions[i](argc, argv);
            return;
        }
    }
    errorInvalidInput(argc, argv);
}

void readHandler(int argc, char *argv[]) {

    if (argc < 4) {
        errorNumberArguments(argc);
        return;
    }

    char *targets[] = {
            "estudio",
            "edificio",
            "agenda",
            "marcacao"
    };

    void (*functions[])(int, char**) = {
            readEstudios,
            readEdificios,
            readAgendas
    };

    int targetsSize = sizeof(targets) / sizeof(char *);

    for (int i = 0; i < targetsSize; ++i) {
        if (strcmp(targets[i], argv[2]) == 0) {
            functions[i](argc, argv);
            return;
        }
    }
}

void updateHandler(int argc, char *argv[]) {

}

void createHandler(int argc, char *argv[]) {
    if (argc < 4) {
        errorNumberArguments(argc);
    }

    char *targets[] = {
            "report_ocu",
            "report_bill"
    };

    int targetsSize = sizeof(targets) / sizeof(char *);

    for (int i = 0; i < 2; ++i) {
        if (strcmp(targets[0], argv[2]) == 0) {
            createReportOcu(argc, argv);
            return;
        }else if(strcmp(targets[1], argv[2])==0) {
            createReportBill(argc, argv);
        }
    }
}

void deleteHandler(int argc, char *argv[]) {

}

void errorNumberArguments(int argc) {
    printf("Invalid Number of Arguments: %d\n", argc);
}

void errorInvalidInput(int argc, char **argv) {
    printf("Invalid imput: ");
    for (int i = 1; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
}

void readEstudios(int argc, char *argv[]) {

    // Exemplo: UFP_Alojamentos.exe read estudio 37
    // entao procura pelo estudio de id=37
    // Ou: UFP_Alojamentos.exe read estudio *
    // entao le todos os estudios e a data mais proxima deles

    if (argc < 3) {
        errorNumberArguments(argc);
        return;
    }

    if (isNumStr(argv[3])) {
        // Se for um numero vamos procurar pelo ID
        int id = atoi(argv[3]);
        if (argc == 4){
            printf("Reading estdudio with id = %d\n...\n", id);
            EST_HANDLER *handler = get_data_estudio();
            int eIndex = getEstudioArrayIndex(handler, id);
            EST *estudio = getEstudioFromIndex(handler, eIndex);
            if (estudio == NULL) {
                printf("ERROR: Index out of range\n");
                return;
            }
            printEstudio(*estudio);
            DATA dAvailable = getEstudioClosestAvailability(*estudio);
            char *dString = dataToString(dAvailable);
            printf("Vago no dia %s\n", dString);
            return;
        }
        else if (argc >= 5 && strcmp(argv[4], "agenda") == 0){
            if (argc == 5) {
                EST_HANDLER *estHandler = get_data_estudio();
                EST *estudio = getEstudioFromIndex(estHandler, atoi(argv[3]));
                print_agenda(*estudio->agenda_master);
                return;
            }
            else if (argc == 6 && strcmp(argv[5], "outras") == 0){
//                EST_HANDLER *estHandler = get_data_estudio();
//                EST *estudio = getEstudioFromIndex(estHandler, atoi(argv[3]));
                printf("Area nao implementada ainda\n...\nSorry\n");
                return;
            }
        }
    } else if (isEstConfig(argv[3])) {
        // Se for uma configuracao, procuramos pela configuracao
        // retorna o estudio da respectiva configuracao de disponibilidade mais proxima
        EST_HANDLER *handler = get_data_estudio();
        printf("Reading estudio with config = %s\n...\n", argv[3]);
        EST *estudio = getEstudioAvailableFromConfig(*handler, argv[3]);
        if (estudio == NULL) {
            printf("ERROR: Nao foi encontrado qualquer estudio a configuracao [%s]\n", argv[3]);
            return;
        }
        printEstudio(*estudio);
        DATA dAvailable = getEstudioClosestAvailability(*estudio);
        char *dString = dataToString(dAvailable);
        printf("Vago no dia %s\n", dString);
    } else if (strcmp(argv[3], "*") == 0 || strcmp(argv[3], "*\n")) {
        // Faz print a todos os estudios e as suas datas com disponibilidade mais proxima
        printf("Reading all estudios\n...\n");
        EST_HANDLER *handler = get_data_estudio();
        for (int i = 0; i < handler->size; ++i) {
            EST estudio = handler->estArray[i];
            printEstudio(estudio);
            DATA dAvailable = getEstudioClosestAvailability(estudio);
            char *dString = dataToString(dAvailable);
            printf("Vago no dia %s\n", dString);
        }
    }

}

void readEdificios(int argc, char *argv[]){
    if (argc < 3){
        errorNumberArguments(argc);
        printf("Want to print all of them?\nTry: read edificio *\n");
        return;
    }
    if (isNumStr(argv[3])){
        // Procura pelo ID, que supostamente esta no argv[3]
        int id = atoi(argv[3]);
        ED_LIST *list = get_data_edfs();
        ED* edificio = getEdificioFromID(list, id);
        if (edificio == NULL){
            printf("Nao foi encontrado um edificio com o respectivo id de '%d'\n", id);
            return;
        }
        printEdificio(*edificio);
        return;
    }
    if (strcmp(argv[3], "*") == 0 || strcmp(argv[3], "*\n") == 0) {
        // Caso seja um * printamos todos os edificios
        ED_LIST *list = get_data_edfs();
        list->print(list);
        return;
    }
    else{
        // Por fim, caso nao seja nenhum dos outros, so pode ser o nome do edificio
        // Por isso procuramos, com isso em mente
        ED_LIST *list = get_data_edfs();
        ED* edificio = getEdifcioFromName(list, argv[3]);
        if (edificio == NULL){

            printf("Nao foi encontrado um edificio com o nome \"%s\"\n", argv[3]);
            printf("Eis a lista completa:\n");
            list->print(list);
            return;
        }
        printEdificio(*edificio);
        return;
    }
}

void readAgendas(int argc, char *argv[]){
    if (argc < 4){
        errorNumberArguments(argc);
        printf("Para selecionar uma agenda pelo id fazes:\nUFP_Alojamentos.exe read agenda master 5 (sendo o 5 o id desejado)\nOu:\nUFP_Alojamentos.exe read agenda outra 5");
        return;
    }
    if (strcmp("master", argv[3]) == 0){
        // Entao o utilizador quer uma agenda master
        if (isNumStr(argv[4])) {
            // Pelo id
            AGENDA *master = get_data_agenda_master(atoi(argv[4]));
            print_agenda(*master);
            return;
        }
        errorInvalidInput(argc, argv);
        printf("Id Invalido: [%s]", argv[4]);
        return;
    }
    if (strcmp("outra", argv[3]) == 0){
        // Entao o utilizador busca uma agenda outra
        if (isNumStr(argv[4])){
            // Pelo ID
            AGENDA *agenda = get_data_single_agenda_outra(atoi(argv[4]));
            print_agenda(*agenda);
            return;
        }
        else{
            // Entao ele esta buscando pela plataforma
            // Oops um pouco chato, vejo depois
        }
    }
    errorInvalidInput(argc, argv);
    return;
}

void readMarc(int argc, char* argv[]){
    // read marc
}

void createReportOcu(int argc, char *argv[]) {
    // Exemplo: UFP_Alojamentos.exe create report_ocu est 37 10/03/1900 23/04/2030
    // entao gera um report de taxa de ocupacao de um estudio com id 37 no intervalo de datas 10/03/1900 ate 23/04/2030
    // Ou: UFP_Alojamentos.exe create report_ocu * 10/03/1900 23/04/2030
    // entao gera um report de taxa de ocupacao de todos os estudios no intervalo de datas 10/03/1900 ate 23/04/2030

    if (argc < 6) {
        errorNumberArguments(argc);
    }

    if(strcmp(argv[3], "est")==0) {
        int id = atoi(argv[4]);
        printf("Creating report for estudio with id = %d\n...\n", id);
        EST_HANDLER *handler = get_data_estudio();
        int eIndex = getEstudioArrayIndex(handler, id);
        EST *estudio = getEstudioFromIndex(handler, eIndex);
        if (estudio == NULL) {
            printf("ERROR: Index out of range\n");
            return;
        }
        DATA inicio = convertStringDATA(argv[5]);
        DATA final = convertStringDATA(argv[6]);
        generate_estudio_occupation(estudio, inicio, final, argv[7]);
        return;
    }else if(strcmp(argv[3], "ed")==0) {
        int id = atoi(argv[4]);
        printf("Creating report for edificio with id = %d\n...\n", id);
        ED_LIST* queueEdificios = get_data_edfs();
        EST_HANDLER* arrayEstudios = get_data_estudio();
        ED* edificio = getEdificioFromID(queueEdificios, id);
        DATA inicio = convertStringDATA(argv[5]);
        DATA final = convertStringDATA(argv[6]);
        generate_edificio_occupation(arrayEstudios, edificio, inicio, final, argv[7]);
        return;
    }else if(strcmp(argv[3], "all")==0) {
        printf("Creating report for all edificios \n...\n");
        EST_HANDLER* arrayEstudios = get_data_estudio();
        DATA inicio = convertStringDATA(argv[4]);
        DATA final = convertStringDATA(argv[5]);
        generate_all_occupation(arrayEstudios, inicio, final, argv[6]);
    }
}

void createReportBill(int argc, char *argv[]) {
    // Exemplo: UFP_Alojamentos.exe create report_bill est 37 10/03/1900 23/04/2030
    // entao gera um report financeiro de um estudio com id 37 no intervalo de datas 10/03/1900 ate 23/04/2030
    // Ou: UFP_Alojamentos.exe create report_bill * 10/03/1900 23/04/2030
    // entao gera um report financeiro de todos os estudios no intervalo de datas 10/03/1900 ate 23/04/2030

    if (argc < 6) {
        errorNumberArguments(argc);
    }

    if(strcmp(argv[3], "est")==0) {
        int id = atoi(argv[4]);
        printf("Creating report for estudio with id = %d\n...\n", id);
        EST_HANDLER *handler = get_data_estudio();
        int eIndex = getEstudioArrayIndex(handler, id);
        EST *estudio = getEstudioFromIndex(handler, eIndex);
        if (estudio == NULL) {
            printf("ERROR: Index out of range\n");
            return;
        }
        DATA inicio = convertStringDATA(argv[5]);
        DATA final = convertStringDATA(argv[6]);
        generate_estudio_billing(estudio, inicio, final, argv[7]);
        return;
    }else if(strcmp(argv[3], "ed")==0) {
        int id = atoi(argv[4]);
        printf("Creating report for edificio with id = %d\n...\n", id);
        ED_LIST* queueEdificios = get_data_edfs();
        EST_HANDLER* arrayEstudios = get_data_estudio();
        ED* edificio = getEdificioFromID(queueEdificios, id);
        DATA inicio = convertStringDATA(argv[5]);
        DATA final = convertStringDATA(argv[6]);
        generate_edificio_billing(arrayEstudios, edificio, inicio, final, argv[7]);
        return;
    }else if(strcmp(argv[3], "all")==0) {
        printf("Creating report for all edificios \n...\n");
        EST_HANDLER* arrayEstudios = get_data_estudio();
        DATA inicio = convertStringDATA(argv[4]);
        DATA final = convertStringDATA(argv[5]);
        generate_all_billing(arrayEstudios, inicio, final, argv[6]);
    }
}

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

    printf("- - - - Welcome to %s - - - -\n", proj_name);
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
    }

    char *targets[] = {
            "estudio",
            "edificio",
            "agenda",
            "marcacao"
    };

    int targetsSize = sizeof(targets) / sizeof(char *);

    for (int i = 0; i < targetsSize; ++i) {
        if (strcmp(targets[i], argv[2]) == 0) {
            readEstudios(argc, argv);
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
    } else if (strcmp(argv[3], "*") == 0) {
        // Faz print a todos os estudios e as suas datas com disponibilidade mais proxima
        printf("Reading all estudios\n...\n");
    }
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


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
            "create",
            "marc"
    };


    void (*functions[])(int argc, char *argv[]) = {
            readHandler,
            updateHandler,
            deleteHandler,
            createHandler,
            marcHandler
    };

    printf("- - - - Welcome to %s - - - -\n", proj_name);
    for (int i = 0; i < 6; ++i) {
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
    // Exemplo1: update estudio 1 (id) edificio_id 2
    // Exemplo2: update estudio 1 (id) preco_base 28
    // Exemplo3: update estudio 1 (id) config T2+1

    if (argc < 6){
        errorNumberArguments(argc);
        return;
    }

    char* targets[] = {
            "estudio",
            "edificio",
            "agenda",
            "marcacao"
    };

    void (*functions[])(int argc, char* argv[]) = {
            updateEstudio,
            updateEdifcio,
            updateAgenda
    };

    int targetsSize = sizeof(targets) / sizeof(char *);

    for (int i = 0; i < targetsSize; ++i) {
        if (strcmp(targets[i], argv[2]) == 0) {
            functions[i](argc, argv);
            return;
        }
    }

}

void createHandler(int argc, char *argv[]) {
    if (argc < 4) {
        errorNumberArguments(argc);
    }

    char *targets[] = {
            "report_ocu",
            "report_bill",
            "estudio",
            "edificio",
            "guest",
            "agenda"
    };

    int targetsSize = sizeof(targets) / sizeof(char *);

    for (int i = 0; i < targetsSize; ++i) {
        if (strcmp(targets[0], argv[2]) == 0) {
            createReportOcu(argc, argv);
            return;
        }else if(strcmp(targets[1], argv[2])==0) {
            createReportBill(argc, argv);
            return;
        }else if(strcmp(targets[2], argv[2])==0) {
            createEstudio(argc, argv);
            return;
        }else if(strcmp(targets[3], argv[2])==0) {
            createEdificio(argc, argv);
            return;
        }else if(strcmp(targets[4], argv[2])==0) {
            createGuest(argc, argv);
            return;
        }else if(strcmp(targets[5], argv[2])==0) {
            createAgenda(argc, argv);
            return;
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
    // Exemplo1: read edificio 1
    // Exemplo2: read edificio *
    // Exemplo3: read edifico "Dom Afonso Henriques"

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
        return;
    }
}


void updateEstudio(int argc, char* argv[]){
    // Exemplo1: update estudio 1 (id) edificio_id 2
    // Exemplo2: update estudio 1 (id) preco_base 28
    // Exemplo3: update estudio 1 (id) config T2+1

    char* fields[] = {
      "edificio_id",
      "preco_base",
      "config",
      "agenda_handler_id",
      "agenda_master_id"
    };

    void (*functions[])(int, char**) = {
            __updateEstudioEdificioId,
            __updateEstudioPrecoBase,
            __updateEstudioConfig,
            errorInvalidInput,
            errorInvalidInput
    };

    if (isNumStr(argv[3])){
        // Buscando pelo id
        for (int i = 0; i < sizeof(fields)/sizeof(char*); ++i) {
            if (strcmp(fields[i], argv[5]))
            {
                functions[i](argc, argv);
                return;
            }
        }
        errorInvalidInput(argc, argv);
        return;
    }
}

void __updateEstudioPrecoBase(int argc, char** argv){
    EST_HANDLER * handler = get_data_estudio();
    updateEstudioPrecoBase(atoi(argv[5]), atoi(argv[3]), handler);
    printEstudio(*getEstudioFromId(handler, atoi(argv[3])));
}

void __updateEstudioEdificioId(int argc, char** argv){
    EST_HANDLER * handler = get_data_estudio();
    updateEstudioEdificioId(atoi(argv[5]), atoi(argv[3]), handler);
    printEstudio(*getEstudioFromId(handler, atoi(argv[3])));
}

void __updateEstudioConfig(int argc, char** argv){
    EST_HANDLER* handler = get_data_estudio();
    updateEstudioConfig(argv[5], atoi(argv[3]), handler);
    printEstudio(*getEstudioFromId(handler, atoi(argv[3])));
}

void updateEdifcio(int argc, char* argv[]){

}

void updateAgenda(int argc, char* argv[]){

}
void marcHandler(int argc, char *argv[]) {

    if (argc < 4) {
        errorNumberArguments(argc);
    }
    char *targets[] = {
            "add",
            "validate"
    };

    int targetsSize = sizeof(targets) / sizeof(char *);

    for (int i = 0; i < targetsSize; ++i) {
        if (strcmp(targets[0], argv[2]) == 0) {
            marcAdd(argc, argv);
            return;
        }else if(strcmp(targets[1], argv[2])==0) {
            marcValidate(argc, argv);
        }
    }

}

void marcAdd(int argc, char *argv[]) {
    //Exemplo: UFP_alojamentos.exe marc add A 2 23/03/2022 12 4
    //E e criada uma marcacao pela plataforma A registada para o hospede_id 2
    //na data 23/03/2022 com uma duracao de 12 dias no estudio_id 4

    if (argc < 6) {
        errorNumberArguments(argc);
    }

    if (argc == 7) { //com especificacao do estudio
        EST_HANDLER *estudios = get_data_estudio();                     //Carrega o array dinamico de estudios
        int estudio_id = atoi(argv[7]);
        int eIndex = getEstudioArrayIndex(estudios, estudio_id); //Obtem o index do estudio que pretendemos no array dinamico de estudios
        EST *estudio = getEstudioFromIndex(estudios,eIndex);           //Cria um ponteiro para o estudio que pretendemos
        DATA data = convertStringDATA(argv[5]);
        if (_agendas_handler_check_availability(estudio->outrasHandler, data, -1) == 1) {       //Checa se a data que queremos fazer a marcacao no estudio esta disponivel
                for (int i = 0; i < estudio->outrasHandler->size; i++) {                        //Percorre todas as agendas outras do array dinamico de agendas_outras
  /*                 if (strcmp(estudio->outrasHandler->agendas[i].nome, argv[3]) ==0) {           //CHECA SE AQUELA AGENDA OUTRA E DA PLATAFORMA A OU B OU C OU ...(dependendo da que selecionarmos)
                        MARC *marc = (MARC *) malloc(sizeof(MARC));                           //Aloca espaco para uma nova marcacao

                        marc->plataforma = (char *) malloc(sizeof(char) * strlen(argv[3]));        //Preenche a nova marcaaco
                        strcpy(marc->plataforma, argv[3]);
                        marc->hospedeID = atoi(argv[4]);
                        marc->data.dia = data.dia;
                        marc->data.mes = data.mes;
                        marc->data.ano = data.ano;
                        marc->duracao = atoi(argv[6]);

                        RP *rp = get_data_rp();                 //Carrega todas as regras de preco

                        marc->preco = generate_price_est(marc, estudio, rp, estudio->agenda_master->calendario);
                        printf("Preco da marcacao: %d\n", marc->preco);

                        estudio->outrasHandler->agendas[i] = *addMarc(&estudio->outrasHandler->agendas[i], marc, data);

                        saveDataSingleAgenda(&estudio->outrasHandler->agendas[i]);  //NAO FUNCIONA
                        CALEND *cal = estudio->outrasHandler->agendas[i].calendario;
                        printf("Marc: %d-%d-%d\nEstudio_id: %d\nPlataforma:%s\nDuracao:%d\nHospede_ID:%d\nPreco:%d\n",
                               cal->marcacao->data.dia, cal->marcacao->data.mes, cal->marcacao->data.ano, estudio->id,
                               cal->marcacao->plataforma, cal->marcacao->duracao, cal->marcacao->hospedeID,
                               cal->marcacao->preco); //TESTE PARA VER SE ESTA A FAZER A MARCACAO
                        printf("Marcacao efetuada com sucesso. Valide para que esta possa ser definitiva\n");
                        return;
                    }*/
                }
            }
        }else if (argc == 6) { //SEM ESPECIFICACAO DE ESTUDIO
    }
}

void marcValidate(int argc, char* argv[]) {

}

void createEstudio(int argc, char* argv[]) {
    // Exemplo: UFP_Alojamentos.exe create estudio 4 1 T2 30 1234 3213
    // entao cria um estudio T2 com id 4 edificio_id 1 com preco base de 30 e agenda_master_id 1234 e agenda_outras_id 3213

    if(argc<8) {
        errorNumberArguments(argc);
    }

    EST_HANDLER* estHandler = get_data_estudio();

    //FUNCAO QUE VERIFICA SE NAO EXISTE NENHUM ESTUDIO COM O ID DADO

    estHandler->estArray = (EST*)realloc(estHandler->estArray, sizeof(EST)*(estHandler->size+1));
    estHandler->estArray[estHandler->size].id = atoi(argv[3]);
    estHandler->estArray[estHandler->size].edificio_id = atoi(argv[4]);
    estHandler->estArray[estHandler->size].configuracao = (char*)malloc(sizeof(char)*strlen(argv[5]));
    strcpy(estHandler->estArray[estHandler->size].configuracao,argv[5]);
    estHandler->estArray[estHandler->size].precoDiario_base = atoi(argv[6]);
    estHandler->estArray[estHandler->size].agenda_master = (AGENDA*)malloc(sizeof(AGENDA));
    estHandler->estArray[estHandler->size].outrasHandler = (AGENDAS_HANDLER*)malloc(sizeof(AGENDAS_HANDLER));
    estHandler->estArray[estHandler->size].agenda_master->id = atoi(argv[7]);
    estHandler->estArray[estHandler->size].outrasHandler->id = atoi(argv[8]);
    estHandler->estArray[estHandler->size].agenda_master->calendario = NULL;
    estHandler->estArray[estHandler->size].outrasHandler->agendas = NULL;
    estHandler->size++;

    saveDataEstudio(estHandler);

    return;
}

void createEdificio(int argc, char* argv[]) {
    // Exemplo: UFP_Alojamentos.exe create edificio 5 adress Rua nao sei lat 0.2323232 longi 23.323 nome Shakira
    // entao cria um edificio com id 5 com endereco Rua nao sei, lat 0.23232323, longi 23.323 e nome Shakira

    if (argc < 11) {
        errorNumberArguments(argc);
    }

    ED_LIST *edList = get_data_edfs();

    //FUNCAO QUE VERIFICA SE NAO EXISTE NENHUM EDIFICIO COM O ID DADO
    int i;
    ED *novoEdificio = (ED *) malloc(sizeof(ED));
    novoEdificio->id = atoi(argv[3]);
    novoEdificio->endereco.endereco = (char *) malloc(sizeof(char) * (strlen(argv[5]) + 1));
    strcpy(novoEdificio->endereco.endereco, argv[5]);
    int size = strlen(argv[5]);
    for (i = 6; strcmp(argv[i], "lat") != 0; i++) {
        size+= strlen(argv[i]);
        novoEdificio->endereco.endereco = (char *) realloc(novoEdificio->endereco.endereco,sizeof(char)*(size+1));
        strcat(novoEdificio->endereco.endereco, argv[i]);
    }
    novoEdificio->endereco.endereco[strlen(novoEdificio->endereco.endereco)] = '\0';
    printf("Criado edificio com sucesso!\n");
    printf("%s\n", novoEdificio->endereco.endereco);

    novoEdificio->endereco.lat = atoi(argv[i+1]);
    novoEdificio->endereco.longi = atoi(argv[i+3]);
    novoEdificio->nome = (char*)malloc(sizeof(char)*(strlen(argv[argc])+1));
    strcpy(novoEdificio->nome, argv[argc]);
    _edfs_list_append(edList, novoEdificio);
    saveDataEdificios(edList);
}

void createGuest(int argc, char *argv[]) {
    // Exemplo: UFP_Alojamentos.exe create guest 10 Joao Carlos joaocarlos@gmail.com
    // entao cria um hospede com id 10 nome Joao Carlos e email joaocarlos@gmail.com

    if (argc < 6) {
        errorNumberArguments(argc);
    }

    HOSP_STACK* stack = get_data_hosp();

    //FUNCAO QUE VERIFICA SE NAO EXISTE NENHUM HOSPEDE COM O MESMO ID

    HOSP* newHospede = (HOSP*)malloc(sizeof(HOSP));

    newHospede->id=atoi(argv[3]);

    newHospede->nome = (char*)malloc(sizeof(char)*(strlen(argv[4])+strlen(argv[5])+1));
    strcpy(newHospede->nome, argv[4]);
    strcat(newHospede->nome, argv[5]);

    newHospede->email = (char*)malloc(sizeof(char)*(strlen(argv[6])+1));
    strcpy(newHospede->email, argv[6]);

    guests_lists_push(stack, newHospede);

    saveDataHospedes(stack);
}

void createAgenda(int argc, char* argv[]) {
    // Exemplo: UFP_Alojamentos.exe create agenda 1234 3 4
    // entao cria uma agenda_master com id 1234 e outra_agenda com id 1234 e duas agendas com id 3 e 4 para as plataformas A e B, respetivamente

    if (argc < 3) {
        errorNumberArguments(argc);
    }

    int agenda_id = atoi(argv[3]);

    //Funcao que verifica se ja existe uma agenda com esse(s) id(s);

    char* filepath1 = get_filepath_agenda_master(agenda_id);
    char* filepath2 = get_filepath_agendas_handler(agenda_id);
    char* filepathA = get_filepath_agenda_outra(atoi(argv[4]));
    char* filepathB = get_filepath_agenda_outra(atoi(argv[5]));

    FILE* fw = fopen(filepath1, "w");
    fprintf(fw, "dia|mes|ano|plataforma|duracao|preco|hospedeID|eventos\n");
    fclose(fw);

    fw = fopen(filepath2, "w");
    fprintf(fw, "outra_id|nome\n");
    fprintf(fw, "%d|A\n",atoi(argv[4]));
    fprintf(fw, "%d|B\n",atoi(argv[5]));
    fclose(fw);

    fw = fopen(filepathA, "w");
    fprintf(fw, "dia|mes|ano|plataforma|duracao|preco|hospedeID\n");
    fclose(fw);

    fw = fopen(filepathB, "w");
    fprintf(fw, "dia|mes|ano|plataforma|duracao|preco|hospedeID\n");
    fclose(fw);

    printf("Agendas criadas com sucesso!\n");
}


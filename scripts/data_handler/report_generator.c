//
// Created by Gabriel Fernandes on 25/12/2020.
//

#include "report_generator.h"
#include "../API/agendas.h"

int main_report_generator(int argc, char *argv[]) {

}

char* create_filepath_report(EST *estudio, DATA hoje, char file_preset2[]) {
    char* file_preset1= "../data/reports/";
    char i[10], d[10], m[10], a[10];
    itoa(estudio->id,i, 10);
    itoa(hoje.dia, d, 10);
    itoa(hoje.mes, m, 10);
    itoa(hoje.ano, a, 10);
    char* file_path = (char*)malloc(sizeof(char)* (strlen(file_preset1) + strlen(file_preset2) + strlen(i) + strlen(d) + strlen(m) + strlen(a) + 1));
    strcpy(&file_path[0], file_preset1);
    strcpy(&file_path[strlen(file_path)],a);
    strcpy(&file_path[strlen(file_path)],m);
    strcpy(&file_path[strlen(file_path)],d);
    strcpy(&file_path[strlen(file_path)],i);
    strcpy(&file_path[strlen(file_path)],file_preset2);
    return file_path;
}

void generate_estudio_occupation(EST *estudio, DATA inicio, DATA final, int ordem) {
    //DATA hoje = get_today();              //Get_today() nao funciona nao sei porque
    DATA hoje = {2020, 12, 25};

    //CRIACAO DO FICHEIRO COM O RELATORIO

    char *filepath = create_filepath_est_report(estudio, hoje, "_estOcu_report.txt");
    FILE *fw = fopen(filepath, "w");

    //IMPRIMIR RELATORIO NO ECRA

    float Total=0;
    CALEND* calendario = NULL;
    printf("%d-%d-%d\nRelatorio de taxa de ocupacao do estudio: \n\tID: %d      Configuracao: %s\n\n", hoje.ano, hoje.mes, hoje.dia, estudio->id, estudio->configuracao);
    fprintf(fw, "%d-%d-%d\nRelatorio da taxa de ocupacao do estudio: \n\tID: %d      Configuracao: %s\n\n", hoje.ano, hoje.mes, hoje.dia, estudio->id, estudio->configuracao);
    Total+=return_estudioOcu_selected_data(estudio, calendario, fw, inicio, final, ordem);
    printf("-------------------\n");
    printf("Total:  %f\n", Total);
    fprintf(fw, "-------------------\n");
    fprintf(fw, "Total:  %f\n", Total);
}

void generate_estudio_billing(EST *estudio, DATA inicio, DATA final, int ordem) {
    //DATA hoje = get_today();              //Get_today() nao funciona nao sei porque
    DATA hoje = {2020, 12, 25};

    //CRIACAO DO FICHEIRO COM O RELATORIO

    char *filepath = create_filepath_est_report(estudio, hoje, "_estBill_report.txt");
    FILE *fw = fopen(filepath, "w");

    //IMPRIMIR RELATORIO NO ECRA

    int Total=0;
    CALEND* calendario = NULL;
    printf("%d-%d-%d\nRelatorio de faturacao do estudio: \n\tID: %d      Configuracao: %s\n\n", hoje.ano, hoje.mes, hoje.dia, estudio->id, estudio->configuracao);
    fprintf(fw, "%d-%d-%d\nRelatorio de faturacao do estudio: \n\tID: %d      Configuracao: %s\n\n", hoje.ano, hoje.mes, hoje.dia, estudio->id, estudio->configuracao);
    Total+=return_estudiobill_selected_data(estudio, calendario, fw, inicio, final, ordem);
    printf("-------------------\n");
    printf("Total:  %d\n", Total);
    fprintf(fw, "-------------------\n");
    fprintf(fw, "Total:  %d\n", Total);
}


char* create_filepath_est_report(EST *estudio, DATA hoje, char file_preset2[]) {
    char* file_preset1= "../data/reports/";
    char i[10], d[10], m[10], a[10];
    itoa(estudio->id,i, 10);
    itoa(hoje.dia, d, 10);
    itoa(hoje.mes, m, 10);
    itoa(hoje.ano, a, 10);
    char* file_path = (char*)malloc(sizeof(char)* (strlen(file_preset1) + strlen(file_preset2) + strlen(i) + strlen(d) + strlen(m) + strlen(a) + 1));
    strcpy(&file_path[0], file_preset1);
    strcpy(&file_path[strlen(file_path)],a);
    strcpy(&file_path[strlen(file_path)],m);
    strcpy(&file_path[strlen(file_path)],d);
    strcpy(&file_path[strlen(file_path)],i);
    strcpy(&file_path[strlen(file_path)],file_preset2);
    return file_path;
}

char* create_filepath_edf_report(ED *edificio, DATA hoje, char file_preset2[]) {
    char* file_preset1= "../data/reports/";
    char i[10], d[10], m[10], a[10];
    itoa(edificio->id,i, 10);
    itoa(hoje.dia, d, 10);
    itoa(hoje.mes, m, 10);
    itoa(hoje.ano, a, 10);
    char* file_path = (char*)malloc(sizeof(char)* (strlen(file_preset1) + strlen(file_preset2) + strlen(i) + strlen(d) + strlen(m) + strlen(a) + 1));
    strcpy(&file_path[0], file_preset1);
    strcpy(&file_path[strlen(file_path)],a);
    strcpy(&file_path[strlen(file_path)],m);
    strcpy(&file_path[strlen(file_path)],d);
    strcpy(&file_path[strlen(file_path)],i);
    strcpy(&file_path[strlen(file_path)],file_preset2);
    return file_path;
}

void generate_edificio_occupation(EST_HANDLER *arrayEstudios, ED *edificio, DATA inicio, DATA final, int ordem) {
    //DATA hoje = get_today();              //Get_today() nao funciona nao sei porque
    DATA hoje = {2020, 12, 25};

    //CRIACAO DO FICHEIRO COM O RELATORIO

    char *filepath = create_filepath_edf_report(edificio, hoje, "_edfOcu_report.txt");
    FILE *fw = fopen(filepath, "w");

    //IMPRIMIR RELATORIO NO ECRA
    float Total=0, n=0;
    CALEND* calendario = NULL;
    printf("%d-%d-%d\nRelatorio de taxa de faturacao do edificio: \n\tID: %d      Nome: %s\n\n", hoje.ano, hoje.mes, hoje.dia, edificio->id, edificio->nome);
    fprintf(fw, "%d-%d-%d\nRelatorio de taxa de faturacao do edificio: \n\tID: %d      Nome: %s\n\n", hoje.ano, hoje.mes, hoje.dia, edificio->id, edificio->nome);
    for(int i=0; i<arrayEstudios->size; i++) {
        if(arrayEstudios->estArray[i].edificio_id == edificio->id) {
            printf("-------------------\n");
            printf("Estudio_ID: %d\n", arrayEstudios->estArray[i].id);
            fprintf(fw, "-------------------\n");
            fprintf(fw, "Estudio_ID: %d\n", arrayEstudios->estArray[i].id);
            Total+=return_estudioOcu_selected_data(&arrayEstudios->estArray[i], calendario, fw, inicio, final, ordem);
            n++;
        }
    }
    Total = Total / n;
    printf("-------------------\n");
    printf("Total:  %f\n", Total);
    fprintf(fw, "-------------------\n");
    fprintf(fw, "Total:  %f\n", Total);
}

void generate_edificio_billing(EST_HANDLER *arrayEstudios, ED *edificio, DATA inicio, DATA final, int ordem) {
    //DATA hoje = get_today();              //Get_today() nao funciona nao sei porque
    DATA hoje = {2020, 12, 25};

    //CRIACAO DO FICHEIRO COM O RELATORIO

    char *filepath = create_filepath_edf_report(edificio, hoje, "_edfBill_report.txt");
    FILE *fw = fopen(filepath, "w");

    //IMPRIMIR RELATORIO NO ECRA

    int Total=0;
    CALEND* calendario = NULL;
    printf("%d-%d-%d\nRelatorio de faturacao do edificio: \n\tID: %d      Nome: %s\n\n", hoje.ano, hoje.mes, hoje.dia, edificio->id, edificio->nome);
    fprintf(fw, "%d-%d-%d\nRelatorio de faturacao do edificio: \n\tID: %d      Nome: %s\n\n", hoje.ano, hoje.mes, hoje.dia, edificio->id, edificio->nome);
    for(int i=0; i<arrayEstudios->size; i++) {
        if(arrayEstudios->estArray[i].edificio_id == edificio->id) {
            printf("-------------------\n");
            printf("Estudio_ID: %d\n", arrayEstudios->estArray[i].id);
            fprintf(fw, "-------------------\n");
            fprintf(fw, "Estudio_ID: %d\n", arrayEstudios->estArray[i].id);
            Total+=return_estudiobill_selected_data(&arrayEstudios->estArray[i], calendario, fw, inicio, final, ordem);
        }
    }
    printf("-------------------\n");
    printf("Total:  %d\n", Total);
    fprintf(fw, "-------------------\n");
    fprintf(fw, "Total:  %d\n", Total);
}

float return_estudioOcu_selected_data(EST *estudio, CALEND *calendario, FILE *fw, DATA inicio, DATA final, int ordem) {
    float Total=0;
    if(ordem == 0) {
        calendario = sortCalendAsc(estudio->agenda_master->calendario, estudio->agenda_master->size);
    }else if(ordem == 1) {
        calendario = sortCalendDesc(estudio->agenda_master->calendario, estudio->agenda_master->size);
    }else{
        printf("ERROR: Invalid order mode. Please select 0 for increasing and 1 for decreasing.\n");
        exit(-1);
    }
    for(int i=0; i<estudio->agenda_master->size; i++) {
        if(calendario[i].Eventos!=NULL) {
            if(check_event(calendario[i].Eventos, "Ocupado")) {
                int comp1 = compDate(calendario[i].data, inicio);        //Compara a data da marcacao com a data inicio   1 se for depois da inicio  0 se for igual  e -1 se for antes
                int comp2 = compDate(final, calendario[i].data);         //Compara a data final com a data da marcacao    1 se for depois da marcacao   0 se for igual   e -1 se for antes
                if((comp1 == 1 || comp1 == 0) && (comp2 == 1 || comp2 == 0)) {
                    printf("Data: %d-%d-%d\nOcupado\n\n",calendario[i].data.ano, calendario[i].data.mes, calendario[i].data.dia);
                    fprintf(fw, "Data: %d-%d-%d\nOcupado\n\n",calendario[i].data.ano, calendario[i].data.mes, calendario[i].data.dia);
                    Total++;
                    continue;
                }
            }
        }
        printf("Data: %d-%d-%d\nNao ocupado\n\n",calendario[i].data.ano, calendario[i].data.mes, calendario[i].data.dia);
        fprintf(fw, "Data: %d-%d-%d\nNao ocupado\n\n",calendario[i].data.ano, calendario[i].data.mes, calendario[i].data.dia);
    }
    Total = Total / (float)estudio->agenda_master->size;
    return Total;
}

int return_estudiobill_selected_data(EST *estudio, CALEND *calendario, FILE *fw, DATA inicio, DATA final, int ordem) {
    int Total=0;
    if(ordem == 0) {
        calendario = sortCalendAsc(estudio->agenda_master->calendario, estudio->agenda_master->size);
    }else if(ordem == 1) {
        calendario = sortCalendDesc(estudio->agenda_master->calendario, estudio->agenda_master->size);
    }else{
        printf("ERROR: Invalid order mode. Please select 0 for increasing and 1 for decreasing.\n");
        exit(-1);
    }
    for(int i=0; i<estudio->agenda_master->size; i++) {
        if(calendario[i].marcacao != NULL) {
            int comp1 = compDate(calendario[i].data, inicio);        //Compara a data da marcacao com a data inicio   1 se for depois da inicio  0 se for igual  e -1 se for antes
            int comp2 = compDate(final, calendario[i].data);         //Compara a data final com a data da marcacao    1 se for depois da marcacao   0 se for igual   e -1 se for antes
            if((comp1 == 1 || comp1 == 0) && (comp2 == 1 || comp2 == 0)) {
                printf("Data: %d-%d-%d\nPreco: %d\n\n",calendario[i].data.ano, calendario[i].data.mes, calendario[i].data.dia, calendario[i].marcacao->preco);
                fprintf(fw, "Data: %d-%d-%d\nPreco: %d\n\n",calendario[i].data.ano, calendario[i].data.mes, calendario[i].data.dia, calendario[i].marcacao->preco);
                Total+=calendario[i].marcacao->preco;
            }
        }
    }
    return Total;
}

char *create_filepath_all_report(DATA hoje, char file_preset2[]) {
    char* file_preset1= "../data/reports/";
    char d[10], m[10], a[10];
    itoa(hoje.dia, d, 10);
    itoa(hoje.mes, m, 10);
    itoa(hoje.ano, a, 10);
    char* file_path = (char*)malloc(sizeof(char)* (strlen(file_preset1) + strlen(file_preset2) + strlen(d) + strlen(m) + strlen(a) + 1));
    strcpy(&file_path[0], file_preset1);
    strcpy(&file_path[strlen(file_path)],a);
    strcpy(&file_path[strlen(file_path)],m);
    strcpy(&file_path[strlen(file_path)],d);
    strcpy(&file_path[strlen(file_path)],file_preset2);
    return file_path;
}

void generate_all_occupation(EST_HANDLER *arrayEstudios, DATA inicio, DATA final, int ordem) {
    //DATA hoje = get_today();              //Get_today() nao funciona nao sei porque
    DATA hoje = {2020, 12, 25};

    //CRIACAO DO FICHEIRO COM O RELATORIO

    char *filepath = create_filepath_all_report(hoje, "_allOcu_report.txt");
    FILE *fw = fopen(filepath, "w");

    //IMPRIMIR RELATORIO NO ECRA

    float n=0, Total=0;
    CALEND* calendario = NULL;
    printf("%d-%d-%d\nRelatorio de taxa de ocupacao dos parques de edificio: \n\n\n", hoje.ano, hoje.mes, hoje.dia);
    fprintf(fw, "%d-%d-%d\nRelatorio de taxa de ocupacao dos parques de edifcio: \n\n\n", hoje.ano, hoje.mes, hoje.dia);
    for(int i=0; i<arrayEstudios->size; i++) {
        printf("-------------------\n");
        printf("Edificio_ID: %d       Estudio_ID: %d\n", arrayEstudios->estArray[i].edificio_id, arrayEstudios->estArray[i].id);
        fprintf(fw, "-------------------\n");
        fprintf(fw, "Edificio_ID: %d        Estudio_ID: %d\n", arrayEstudios->estArray[i].edificio_id, arrayEstudios->estArray[i].id);
        Total+=return_estudioOcu_selected_data(&arrayEstudios->estArray[i], calendario, fw, inicio, final, ordem);
        n++;
    }
    Total = Total / n;
    printf("-------------------\n");
    printf("Total:  %f\n", Total);
    fprintf(fw, "-------------------\n");
    fprintf(fw, "Total:  %f\n", Total);
}

 void generate_all_billing(EST_HANDLER *arrayEstudios, DATA inicio, DATA final, int ordem) {
    //DATA hoje = get_today();              //Get_today() nao funciona nao sei porque
    DATA hoje = {2020, 12, 25};

    //CRIACAO DO FICHEIRO COM O RELATORIO

    char *filepath = create_filepath_all_report(hoje, "_allBill_report.txt");
    FILE *fw = fopen(filepath, "w");

    //IMPRIMIR RELATORIO NO ECRA

    int Total=0;
    CALEND* calendario = NULL;
    printf("%d-%d-%d\nRelatorio de faturacao dos parques de edificio: \n\n\n", hoje.ano, hoje.mes, hoje.dia);
    fprintf(fw, "%d-%d-%d\nRelatorio de faturacao dos parques de edifcio: \n\n\n", hoje.ano, hoje.mes, hoje.dia);
    for(int i=0; i<arrayEstudios->size; i++) {
            printf("-------------------\n");
            printf("Edificio_ID: %d       Estudio_ID: %d\n", arrayEstudios->estArray[i].edificio_id, arrayEstudios->estArray[i].id);
            fprintf(fw, "-------------------\n");
            fprintf(fw, "Edificio_ID: %d        Estudio_ID: %d\n", arrayEstudios->estArray[i].edificio_id, arrayEstudios->estArray[i].id);
            Total+=return_estudiobill_selected_data(&arrayEstudios->estArray[i], calendario, fw, inicio, final, ordem);
    }
    printf("-------------------\n");
    printf("Total:  %d\n", Total);
    fprintf(fw, "-------------------\n");
    fprintf(fw, "Total:  %d\n", Total);
}
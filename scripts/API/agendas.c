//
// Created by Frederico on 29/11/2020.
//

#include <time.h>
#include "agendas.h"
#include "string.h"

AGENDA* init_single_agenda(CALEND *calendario, int size, int id, char* path){
    AGENDA* new_agenda = (AGENDA*)malloc(sizeof(AGENDA));
    new_agenda->id = id;
    new_agenda->calendario = calendario;
    new_agenda->size = size;
    new_agenda->path = path;
    return new_agenda;
}

AGENDAS_HANDLER* init_outras_handler(AGENDA* agendas, int size, int id){
    AGENDAS_HANDLER *newHandler = (AGENDAS_HANDLER*)malloc(sizeof(AGENDAS_HANDLER));
    newHandler->agendas = agendas;
    newHandler->id = id;
    newHandler->size = size;
    //newHandler->find = _agendas_handler_get_agenda;
    newHandler->free = _agendas_handler_free_all;
    newHandler->print_all = _agendas_handler_print_all;
//    newHandler->check_availability = _agendas_handler_check_availability;
    return newHandler;
}

void _agendas_handler_print_all(AGENDAS_HANDLER* self){
    for (int i = 0; i < self->size; ++i) {
        print_agenda(self->agendas[i]);
    }
}

int _agendas_handler_check_availability(AGENDAS_HANDLER* self, DATA data, int agenda_id){
    if (agenda_id < 0) {
        // Iterates through all agendas
        for (int i = 0; i < self->size; ++i)
            for (int j = 0; j < self->agendas[i].size; ++j)
                if (compDate(data, self->agendas[i].calendario[j].data))
                    return 0;
        return 1;
    }
    else {
        AGENDA agenda = *_agendas_handler_get_agenda(self, agenda_id);
        for (int i = 0; i < agenda.size; ++i) {
            if (compDate(agenda.calendario[i].marcacao->data, data))
                return 0;
        }
        return 1;
    }
}

AGENDA *_agendas_handler_get_agenda(AGENDAS_HANDLER *self, int agenda_id) {
    int hi = self->size;
    int lo = 0;
    int mid;
    while(lo<=hi) {
        mid = (hi + lo) / 2;
        if(self->agendas[mid].id > agenda_id) {
            hi = mid;
        }else if(self->agendas[mid].id < agenda_id) {
            lo = mid;
        }else{
            return &self->agendas[mid];
        }
    }
    printf("Nao foi possivel encontrar a agenda\n");
    return NULL;
}


void print_agenda(AGENDA ag) {
    int n = ag.size;
    for (int i = 0; i < n; ++i) {
        printf("Dia: %d  Mes: %d  Ano: %d\n", ag.calendario[i].data.dia, ag.calendario[i].data.mes, ag.calendario[i].data.ano);
        if(ag.calendario[i].marcacao!=NULL) {
            printf("Plataforma: %s  Duracao: %d  Preco: %d HospedeID: %d\n", ag.calendario[i].marcacao->plataforma, ag.calendario[i].marcacao->duracao, ag.calendario[i].marcacao->preco, ag.calendario[i].marcacao->hospedeID);
        }
        if(ag.calendario[i].Eventos!=NULL) {
            printf("Eventos:\t");
            print_event_stack(ag.calendario[i].Eventos);
        }
        printf("\n\n");
    }
}


int _agendas_handler_free_all(AGENDAS_HANDLER* self) {
    int n = self->size;
    for (int i = 0; i < n; ++i) {
        free(self->agendas[i].path);
        free(self->agendas[i].calendario);
        free(&self->agendas[i]);
        self->size--;
    }
    free(self->agendas);
    int working = self->size == 0;
    free(self);
    return working && !self->agendas && !self;
}

MARC* sortAgenda(AGENDA* agenda){
    int n = agenda->size;


    return NULL;
}

int __comp_date1(const void *p1, const void *p2){
    MARC* _1 = (MARC*)p1, *_2 = (MARC*)p2;
    DATA dat1 = _1->data;
    DATA dat2 = _2->data;
    
    if (dat1.ano < dat2.ano)
        return -1;

    // else if
    if (dat1.ano > dat2.ano)
        return 1;
    // else if (ano == ano)
    if (dat1.mes<dat2.mes)
        return -1;
    else if (dat1.mes>dat2.mes)
        return 1;
    else if (dat1.dia<dat2.dia)
        return -1;
    else if(dat1.dia>dat2.dia)
        return 1;
    else
        return 0;
}

int __comp_date2(const void *p1, const void *p2){
    return (-1 * __comp_date1(p1, p2));
}

int compDate(DATA dat1, DATA dat2) {
    if (dat1.ano > dat2.ano)
        return 1;
    if (dat1.ano < dat2.ano)
        return -1;
    if (dat1.mes > dat2.mes)
        return 1;
    if (dat1.mes < dat2.mes)
        return -1;
    if (dat1.dia > dat2.dia)
        return 1;
    if (dat1.dia < dat2.dia)
        return -1;
    return 0;
}

DATA get_today(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return init_data(tm.tm_mday, tm.tm_mon, tm.tm_year);
}

DATA init_data(int dia, int mes, int ano){
    DATA nData;
    nData.dia = dia;
    nData.mes = mes;
    nData.ano = ano;
    return nData;
}

CALEND* sortCalendAsc(CALEND* calendArray, int size){
    qsort(calendArray, size, sizeof(CALEND), __comp_date1);
    return calendArray;
}

CALEND* sortCalendDesc(CALEND* calendArray, int size){
    qsort(calendArray, size, sizeof(CALEND), __comp_date2);
    return calendArray;
}

CALEND* unifyMarcs(CALEND* a1, CALEND* a2, int size1, int size2, int* newSize){
//    if (a1.id == a2.id)
//        return a1;
    *newSize = size1 + size2;
    printf("newSize = %d\n", *newSize);
    CALEND *uniCalendario = (CALEND *) malloc(sizeof(CALEND) * (*newSize));
    int i;
    for (i = 0; i < size1; ++i) {
//        printf("(%d)\t", i);
        uniCalendario[i].marcacao->data = a1[i].marcacao->data;
        uniCalendario[i].marcacao->plataforma = (char *) malloc((strlen(a1->marcacao->plataforma) + 1) * sizeof(char));
        strcpy(uniCalendario[i].marcacao->plataforma, a1[i].marcacao->plataforma);
//        printf("[%d]: %d/%d/%d\t%s\n", i, uniCalendario[i].data.dia, uniCalendario[i].data.mes, uniCalendario[i].data.ano, uniCalendario[i].descricao);
    }
    for (; i < *newSize; ++i) {
//        printf("(%d)\t", i);
        uniCalendario[i].marcacao->data = a2[i - size1].marcacao->data;

        uniCalendario[i].marcacao->plataforma = (char *) malloc(
                (strlen(a2[i - size1].marcacao->plataforma) + 1) * sizeof(char));
        strcpy(uniCalendario[i].marcacao->plataforma, a2[i - size1].marcacao->plataforma);
//        printf("[%d]: %d/%d/%d\t%s\n", i, uniCalendario[i].data.dia, uniCalendario[i].data.mes, uniCalendario[i].data.ano, uniCalendario[i].descricao);

    }
    return uniCalendario;
}

void print_data(DATA d) {
    printf("%d/%d/%d\n", d.dia, d.mes, d.ano);
}

char *dataToString(DATA d) {
    char *str = (char *) malloc(sizeof(char) * 10);
    sprintf(str, "%d/%d/%d", d.dia, d.mes, d.ano);
    return str;
}

void freeAgendaByPtr(AGENDA *a) {
    if (a == NULL)
        return (void) printf("ERROR IN freeAgedendaByPtr(a = NULL)");
    free(a->path);
    for (int i = 0, size = a->size; i < size; ++i) {
        free(a->calendario[i].marcacao->plataforma);
        free(a->calendario[i].marcacao);
        freeAll(a->calendario[i].Eventos);
        free(a->calendario[i].Eventos);
    }
    free(a->calendario);
    free(a->path);
    free(a);
}

AGENDA* addMarc(AGENDA* agenda, MARC *marc, DATA data) {
    if(agenda->calendario !=NULL) {
        int index = getMarcIndex(agenda, data);
        if(index <0) {
            printf("DATA NAO EXISTE NO CALENDARIO");
        }else{
            agenda->calendario[index].marcacao = marc;
            agenda->size++;
        }
    }else{
        agenda->calendario = (CALEND*)malloc(sizeof(CALEND));
        agenda->calendario->data.dia = marc->data.dia;
        agenda->calendario->data.mes = marc->data.mes;
        agenda->calendario->data.ano = marc->data.ano;
        agenda->calendario->Eventos = NULL;
        agenda->calendario->marcacao = marc;
        agenda->size++;
    }
    return agenda;
}

void remMarc(AGENDA *agenda, DATA data) {
    int index = getMarcIndex(agenda, data);
    free(agenda->calendario[index].marcacao->plataforma);
    free(agenda->calendario[index].marcacao);
    freeAll(agenda->calendario[index].Eventos);
    free(agenda->calendario[index].Eventos);
    for(int i=index; i<agenda->size-1; i++) {
        agenda->calendario[i] = agenda->calendario[i++];
    }
}

/**
 * \warning TEM QUE SER REFEITA PARA FUNCIONAR
 */
 /*
void updateMarcFromPos(AGENDA *agenda, int index, DATA *newData, char *newDesc) {
    if (newDesc != NULL)
        strcpy(agenda->marcacoes[index].descricao, newDesc);
    if (newData != NULL)
        agenda->marcacoes[index].data = *newData;
}*/

int getMarcIndex(AGENDA *agenda, DATA data) {
    int size = agenda->size;
    int hi = size, lo = 0;
    if (compDate(agenda->calendario[agenda->size].data, data) < 0 || compDate(data, agenda->calendario[0].data) < 0)
        return -1;
    while (1) {
        int mid = (hi + lo) / 2;
        if (compDate(agenda->calendario[mid].data, data) > 0)
            lo = mid;
        else if (compDate(agenda->calendario[mid].data, data) < 0)
            hi = mid;
        else
            return mid;
    }
 }

MARC getMarc(AGENDA *agenda, DATA data) {
    int index = getMarcIndex(agenda, data);
    return *agenda->calendario[index].marcacao;
}

DATA return_data_difference(DATA data1, DATA data2) {
    DATA diff;
    if(data1.dia>=data2.dia)
        diff.dia = data1.dia-data2.dia;
    else
    {
        data1.dia+=30;
        data1.mes-=1;
        diff.dia = data1.dia-data2.dia;
    }

    if(data1.mes>=data2.mes)
        diff.mes = data1.mes-data2.mes;
    else
    {
        data1.mes+=12;
        data1.ano-=1;
        diff.mes = data1.mes-data2.mes;
    }

    if(data1.ano>=data2.ano) {
        diff.ano = data1.ano-data2.ano;
    }else{
        diff.ano = data2.ano-data1.ano;
    }

    return diff;
}

int dataInDays(DATA data) {
    int days = data.dia;
    if (data.mes == 2) {
        int diasMes = isLeapYear(data.ano) ? 29 : 28;
        days += diasMes;
    } else {
        days += daysInMonth(data.mes);
    }
    days += daysInYear(data.ano);
    return days;
}

int daysInMonth(int mes) {
    if (mes < 1 || mes > 12) {
//        perror("Mes Invalido");
        return -1;
    }
    if (mes == 2)
        return 28;
    switch (mes) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        default:
            return 30;
    }
}

int daysInYear(int ano) {
    return (ano - 1) * 365;
}

int isLeapYear(int ano) {
    if (ano % 400 == 0) {
        return 1;
    } else if (ano % 100 == 0) {
        return 0;
    } else if (ano % 4 == 0) {
        return 1;
    }
    return 0;
}

int howCloseToData(DATA data1, DATA data2) {
    return dataInDays(data1) - dataInDays(data2);
}

DATA convertStringDATA(char str[]) {
    DATA data;
    char* str2 = (char*)malloc(sizeof(char)*2);
    sprintf(str2, "%c%c", str[0], str[1]);
    data.dia = atoi(str2);
    sprintf(str2, "%c%c", str[3], str[4]);
    data.mes = atoi(str2);
    sprintf(str2, "%c%c%c%c", str[6], str[7], str[8], str[9]);
    data.ano = atoi(str2);

//    free(str2);  //Por algum motivo nao funciona
    return data;
}

AGENDA* find(AGENDAS_HANDLER* agendasOutras, int id, char plat[]) {

}


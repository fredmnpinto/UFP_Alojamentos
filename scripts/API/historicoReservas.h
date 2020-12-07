//
// Created by Gabriel Fernandes on 06/12/2020.
//

#ifndef UFP_ALOJAMENTOS_HISTORICORESERVAS_H
#define UFP_ALOJAMENTOS_HISTORICORESERVAS_H

#include "../general/utils.h"

HIST_STACK* init_hist_stack();

void hist_list_push(HIST_STACK* stack, HIST* newHead);

void hist_list_pop(HIST_STACK* stack, HIST* currHead);

int hist_list_size();

int hist_isEmpty();

void print_hist_Stack(HIST_STACK* stack);

#endif //UFP_ALOJAMENTOS_HISTORICORESERVAS_H

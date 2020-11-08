//
// Created by Frederico on 06/11/2020.
//

#include "data_handler.h"


ALOJ *get_aloj_data(int *num_alojs) {
    FILE *fr = fopen("data\\aloj.csv", "r");
    char delimiter[] = ",";
    ALOJ *aloj_array;
    if (fr == NULL) {
        printf("ERROR: ");
        printf("%s\n", strerror(errno));
        exit(errno);
    } else {
        for (int c = getc(fr); c != EOF; c = getc(fr)) {
            if (c == '\n')
                *(num_alojs) += 1;
        }
        aloj_array = malloc(sizeof(ALOJ) * (*num_alojs));
        char file_data[500], header[20];
        int i = 0;
        fscanf(fr, "%s", header);
        remove_linebreak_on_the_end(header);
        printf("%s", header); // id,estudio_id,tipo
        while (fgets(file_data, sizeof(file_data), fr)) {
            aloj_array[i].id = atoi(strtok(NULL, delimiter));
            aloj_array[i].estudio_id = atoi(strtok(NULL, delimiter));
            strcpy(aloj_array[i].tipo, strtok(NULL, delimiter));
        }
    }
    fclose(fr);
    return aloj_array;
}



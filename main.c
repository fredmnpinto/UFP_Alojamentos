#include <stdio.h>
#include "scripts/general/project.h"
int main(int argc, char *argv[]) {
    printf("Root path: %s\n", argv[0]);
    main_proj(argc, argv);
    return 0;
}
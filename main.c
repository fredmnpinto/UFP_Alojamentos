#include <stdio.h>
#include "scripts/general/project.h"
int main(int argc, char *argv[]) {
    remove_linebreak_on_the_end(argv[argc - 1]);
    printf("Root path: %s\n", argv[0]);
    main_proj(argc, argv);
    return 0;
}
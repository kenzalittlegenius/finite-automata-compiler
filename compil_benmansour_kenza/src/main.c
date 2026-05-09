#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char **argv) {
    char *regex;
    regex = read_first_line(argv[1]);
    trim_newline(regex);
    free(regex);

    if (argc != 2) {
        printf("Add the regex file to %s\n", argv[0]);
        return 1;
    }

    if (regex == NULL) {
        printf("Error : can't read the regex\n");
        return 1;
    }
    printf("Regex : %s\n", regex);
    return 0;
}
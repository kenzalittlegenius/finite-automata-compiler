#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *read_first_line(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Erreur ouverture fichier");
        return NULL;
    }

    char *line = malloc(1024 * sizeof(char));

    if (line == NULL) {
        fclose(file);
        return NULL;
    }

    if (fgets(line, 1024, file) == NULL) {
        fclose(file);
        free(line);
        return NULL;
    }

    fclose(file);
    return line;
}

void trim_newline(char *s) {
    if (s == NULL) {
        return;
    }

    s[strcspn(s, "\n")] = '\0';
}
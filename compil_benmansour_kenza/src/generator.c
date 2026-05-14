#include <stdio.h>

#include "generator.h"
#include "dfa.h"

/*
Génère un fichier C qui reconnaît
les mots acceptés par le DFA donné.

En pratique, on lui passera le DFA minimal D'.
*/
void generate_lexer_c(
    const DFA *dfa,
    const char *filename
) {
    FILE *file;
    int i;
    int j;

    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error: cannot create generated lexer file\n");
        return;
    }

    fprintf(file, "#include <stdio.h>\n");
    fprintf(file, "#include <string.h>\n\n");

    fprintf(file, "int main(int argc, char **argv) {\n");
    fprintf(file, "    int state = %d;\n", dfa->start_state);
    fprintf(file, "    int i;\n");
    fprintf(file, "    char *word;\n\n");

    fprintf(file, "    if (argc != 2) {\n");
    fprintf(file, "        printf(\"Usage: %%s <word>\\n\", argv[0]);\n");
    fprintf(file, "        return 1;\n");
    fprintf(file, "    }\n\n");

    fprintf(file, "    word = argv[1];\n\n");

    fprintf(file, "    for (i = 0; word[i] != '\\0'; i++) {\n");
    fprintf(file, "        char c = word[i];\n\n");

    fprintf(file, "        switch (state) {\n");

    for (i = 0; i < dfa->state_count; i++) {
        fprintf(file, "            case %d:\n", i);

        for (j = 0; j < dfa->alphabet_size; j++) {
            int target = dfa->transitions[i][j];

            if (target != -1) {
                fprintf(
                    file,
                    "                if (c == '%c') { state = %d; break; }\n",
                    dfa->alphabet[j],
                    target
                );
            }
        }

        fprintf(file, "                state = -1;\n");
        fprintf(file, "                break;\n");
    }

    fprintf(file, "            default:\n");
    fprintf(file, "                state = -1;\n");
    fprintf(file, "                break;\n");

    fprintf(file, "        }\n\n");

    fprintf(file, "        if (state == -1) {\n");
    fprintf(file, "            break;\n");
    fprintf(file, "        }\n");
    fprintf(file, "    }\n\n");

    fprintf(file, "    if (");

    for (i = 0; i < dfa->state_count; i++) {
        if (dfa->states[i].is_accepting) {
            fprintf(file, "state == %d || ", i);
        }
    }

    fprintf(file, "0) {\n");
    fprintf(file, "        printf(\"%%s appartient au langage rationnel defini par e.\\n\", word);\n");
    fprintf(file, "    } else {\n");
    fprintf(file, "        printf(\"%%s n'appartient pas au langage rationnel defini par e.\\n\", word);\n");
    fprintf(file, "    }\n\n");

    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");

    fclose(file);
}
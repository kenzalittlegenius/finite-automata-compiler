#include <stdio.h>
#include <stdlib.h>

#include "graphviz.h"
#include "nfa.h"

/*
Exporte le NFA
dans un fichier Graphviz .dot
*/
void export_nfa_to_dot(
    const NFA *nfa,
    const char *filename
) {

    FILE *file;

    int i;

    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error: cannot create dot file\n");
        return;
    }

    fprintf(file, "digraph NFA {\n");

    fprintf(file, "    rankdir=LR;\n");

    /*
    état acceptant en double cercle
    */
    fprintf(
        file,
        "    node [shape = doublecircle]; %d;\n",
        nfa->accept_state
    );

    /*
    autres états en cercle simple
    */
    fprintf(file, "    node [shape = circle];\n");

    /*
    transitions
    */
    for (i = 0; i < nfa->transition_count; i++) {

        Transition t = nfa->transitions[i];

        if (t.symbol == '\0') {

            fprintf(
                file,
                "    %d -> %d [label=\"ε\"];\n",
                t.from,
                t.to
            );

        } else {

            fprintf(
                file,
                "    %d -> %d [label=\"%c\"];\n",
                t.from,
                t.to,
                t.symbol
            );
        }
    }

    fprintf(file, "}\n");

    fclose(file);
}
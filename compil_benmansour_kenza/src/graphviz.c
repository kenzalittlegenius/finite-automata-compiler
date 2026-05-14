#include <stdio.h>
#include <stdlib.h>

#include "graphviz.h"
#include "nfa.h"
#include "ast.h"

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

/*
Exporte le DFA
dans un fichier Graphviz .dot
*/
void export_dfa_to_dot(
    const DFA *dfa,
    const char *filename
) {
    FILE *file;
    int i;
    int j;

    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error: cannot create dot file\n");
        return;
    }

    fprintf(file, "digraph DFA {\n");
    fprintf(file, "    rankdir=LR;\n");

    fprintf(file, "    node [shape = doublecircle];");
    for (i = 0; i < dfa->state_count; i++) {
        if (dfa->states[i].is_accepting) {
            fprintf(file, " %d", i);
        }
    }
    fprintf(file, ";\n");

    fprintf(file, "    node [shape = circle];\n");

    for (i = 0; i < dfa->state_count; i++) {
        for (j = 0; j < dfa->alphabet_size; j++) {
            if (dfa->transitions[i][j] != -1) {
                fprintf(
                    file,
                    "    %d -> %d [label=\"%c\"];\n",
                    i,
                    dfa->transitions[i][j],
                    dfa->alphabet[j]
                );
            }
        }
    }

    fprintf(file, "}\n");

    fclose(file);
}



/*
Fonction récursive interne :
écrit un noeud de l'AST et ses arêtes.
*/
static int export_ast_node(
    FILE *file,
    ASTNode *node,
    int *next_id
) {
    int current_id;
    int left_id;
    int right_id;

    if (node == NULL) {
        return -1;
    }

    current_id = *next_id;
    (*next_id)++;

    if (node->Type == AST_SYMBOL) {
        fprintf(file, "    node%d [label=\"%c\"];\n", current_id, node->symbol);
    } else if (node->Type == AST_UNION) {
        fprintf(file, "    node%d [label=\"|\"];\n", current_id);
    } else if (node->Type == AST_CONCAT) {
        fprintf(file, "    node%d [label=\".\"];\n", current_id);
    } else if (node->Type == AST_STAR) {
        fprintf(file, "    node%d [label=\"*\"];\n", current_id);
    }

    left_id = export_ast_node(file, node->left, next_id);

    if (left_id != -1) {
        fprintf(file, "    node%d -> node%d;\n", current_id, left_id);
    }

    right_id = export_ast_node(file, node->right, next_id);

    if (right_id != -1) {
        fprintf(file, "    node%d -> node%d;\n", current_id, right_id);
    }

    return current_id;
}





/*
Exporte l'AST dans un fichier Graphviz .dot
*/
void export_ast_to_dot(
    ASTNode *tree,
    const char *filename
) {
    FILE *file;
    int next_id;

    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error: cannot create dot file\n");
        return;
    }

    next_id = 0;

    fprintf(file, "digraph AST {\n");
    fprintf(file, "    node [shape = circle];\n");

    export_ast_node(file, tree, &next_id);

    fprintf(file, "}\n");

    fclose(file);
}


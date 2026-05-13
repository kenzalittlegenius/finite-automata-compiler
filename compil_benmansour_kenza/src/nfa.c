#include <stdio.h>
#include <stdlib.h>

#include "nfa.h"
#include "ast.h"

/*
prépare un automate vide avant construction
*/
void nfa_init(NFA *nfa) {

    nfa->start_state = -1;
    nfa->accept_state = -1;

    nfa->state_count = 0;

    nfa->transition_count = 0;
}

/*
Crée un nouvel état et renvoie son numéro.
*/
int nfa_new_state(NFA *nfa) {
    int id = nfa->state_count;

    nfa->state_count++;

    return id;
}

/*
Ajoute une transition 
*/
void nfa_add_transition(
    NFA *nfa,
    int from,
    int to,
    char symbol
) {

    Transition *t;

    t = &nfa->transitions[nfa->transition_count];

    t->from = from;
    t->to = to;
    t->symbol = symbol;

    nfa->transition_count++;
}

NFAFragment nfa_build_from_ast(
    NFA *nfa,
    ASTNode *node
) {

    NFAFragment frag;

    if (node->Type == AST_SYMBOL) {

        int start = nfa_new_state(nfa);
        int end = nfa_new_state(nfa);

        nfa_add_transition(
            nfa,
            start,
            end,
            node->symbol
        );

        frag.start = start;
        frag.end = end;

        return frag;
    }


    if (node->Type == AST_CONCAT) {
    NFAFragment left = nfa_build_from_ast(nfa, node->left);
    NFAFragment right = nfa_build_from_ast(nfa, node->right);

    nfa_add_transition(nfa, left.end, right.start, '\0');

    frag.start = left.start;
    frag.end = right.end;

    return frag;
}

if (node->Type == AST_UNION) {
    NFAFragment left = nfa_build_from_ast(nfa, node->left);
    NFAFragment right = nfa_build_from_ast(nfa, node->right);

    int start = nfa_new_state(nfa);
    int end = nfa_new_state(nfa);

    nfa_add_transition(nfa, start, left.start, '\0');
    nfa_add_transition(nfa, start, right.start, '\0');

    nfa_add_transition(nfa, left.end, end, '\0');
    nfa_add_transition(nfa, right.end, end, '\0');

    frag.start = start;
    frag.end = end;

    return frag;
}

if (node->Type == AST_STAR) {
    NFAFragment sub = nfa_build_from_ast(nfa, node->left);

    int start = nfa_new_state(nfa);
    int end = nfa_new_state(nfa);

    nfa_add_transition(nfa, start, sub.start, '\0');
    nfa_add_transition(nfa, start, end, '\0');

    nfa_add_transition(nfa, sub.end, sub.start, '\0');
    nfa_add_transition(nfa, sub.end, end, '\0');

    frag.start = start;
    frag.end = end;

    return frag;
}

    frag.start = -1;
    frag.end = -1;

    return frag;
}

/*
fonction d'affichage pour tester
*/
void nfa_print(const NFA *nfa) {

    int i;

    printf("NFA transitions:\n");

    for (i = 0; i < nfa->transition_count; i++) {

        Transition t = nfa->transitions[i];

        if (t.symbol == '\0') {

            printf(
                "%d -- epsilon --> %d\n",
                t.from,
                t.to
            );

        } else {

            printf(
                "%d -- %c --> %d\n",
                t.from,
                t.symbol,
                t.to
            );
        }
    }
}
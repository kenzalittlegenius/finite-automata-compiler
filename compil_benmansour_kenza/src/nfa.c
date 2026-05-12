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
#ifndef GRAPHVIZ_H_INCLUDED
#define GRAPHVIZ_H_INCLUDED

#include "nfa.h"
#include "dfa.h"

/*
Génère un fichier .dot
pour visualiser le NFA
*/
void export_nfa_to_dot(
    const NFA *nfa,
    const char *filename
);

/*
Génère un fichier .dot
pour visualiser le DFA
*/
void export_dfa_to_dot(
    const DFA *dfa,
    const char *filename
);

#endif
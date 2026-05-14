#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "dfa.h"

/*
Génère automatiquement le fichier C
de l'analyseur lexical associé au DFA minimal D'.
*/
void generate_lexer_c(
    const DFA *dfa,
    const char *filename
);

#endif
#ifndef MINIMIZE_H_INCLUDED
#define MINIMIZE_H_INCLUDED

/*
Construit D',
c'est-à-dire le DFA minimal
obtenu à partir du DFA D.
*/

#include "dfa.h"

/*
Minimise un automate fini déterministe : DFA
*/
void minimize_dfa(const DFA *dfa, DFA *minimized);

#endif
#ifndef DFA_H_INCLUDED
#define DFA_H_INCLUDED

#include "nfa.h"

/*
Nombre maximal d'états dans le DFA.
Chaque état du DFA correspond à un ensemble d'états du NFA.
*/
#define MAX_DFA_STATES 1024

/*
Taille maximale de l'alphabet.
Pour l'instant, on reste simple.
*/
#define MAX_ALPHABET 128

/*
Un état du DFA est représenté par un ensemble d'états du NFA.

Exemple :
l'état DFA 0 peut correspondre à l'ensemble {0, 1, 4}
*/
typedef struct {

    /*
    states[i] vaut 1 si l'état i du NFA appartient à cet ensemble.
    Sinon, states[i] vaut 0.
    */
    int states[1024];

    /*
    Indique si cet état DFA est acceptant.
    */
    int is_accepting;

} DFAState;

/*
Structure représentant un automate fini déterministe.
*/
typedef struct {

    /*
    Liste des états du DFA.
    */
    DFAState states[MAX_DFA_STATES];

    /*
    Nombre réel d'états dans le DFA.
    */
    int state_count;

    /*
    État initial du DFA.
    */
    int start_state;

    /*
    Alphabet utilisé par le DFA.
    */
    char alphabet[MAX_ALPHABET];

    /*
    Nombre de symboles dans l'alphabet.
    */
    int alphabet_size;

    /*
    Table de transition du DFA.

    transitions[i][j] donne l'état atteint
    depuis l'état DFA i
    en lisant alphabet[j].

    -1 signifie : aucune transition.
    */
    int transitions[MAX_DFA_STATES][MAX_ALPHABET];

} DFA;

/*
Initialise un DFA vide.
*/
void dfa_init(DFA *dfa);

/*
Construit le DFA correspondant au NFA donné.
*/
void dfa_from_nfa(DFA *dfa, const NFA *nfa);

/*
Affiche le DFA dans le terminal.
*/
void dfa_print(const DFA *dfa);

#endif
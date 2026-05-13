#ifndef NFA_H_INCLUDED
#define NFA_H_INCLUDED

#include "ast.h" 

/* 
Nombre maximal de transitions
dans l'automate.
*/

#define MAX_TRANSITIONS 1024

/*
Structure représentant une transition
*/

typedef struct{
    int from;
    int to;
    char symbol;
} Transition; 


/*
Structure représentant un automate fini non déterministe (NFA)
*/

typedef struct{
    /* état initial */
    int start_state;
    
    /* état acceptant */
    int accept_state;

    /* nombre total d'états */
    int state_count;

   /* tableau des transitions du NFA*/
    Transition transitions[MAX_TRANSITIONS];

    /*compteur de transitions*/
    int transition_count;
}NFA;

/*
Fragment utilisé par
l'algorithme de Thompson
*/
typedef struct {

    /* début du fragment */
    int start;

    /* fin du fragment */
    int end;

} NFAFragment;

/*
Initialise un NFA vide
*/
void nfa_init(NFA *nfa);

/*
Crée un nouvel état
et renvoie son numéro
*/
int nfa_new_state(NFA *nfa);

/*
Ajoute une transition
dans le NFA.
*/
void nfa_add_transition(
    NFA *nfa,
    int from,
    int to,
    char symbol
);

void nfa_init(NFA *nfa);

int nfa_new_state(NFA *nfa);

void nfa_add_transition(
    NFA *nfa,
    int from,
    int to,
    char symbol
);

NFAFragment nfa_build_from_ast(
    NFA *nfa,
    ASTNode *node
);

void nfa_print(const NFA *nfa);

#endif
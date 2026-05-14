#include <stdio.h>
#include <string.h>

#include "dfa.h"
#include "nfa.h"

/*
Initialise un DFA vide
*/
void dfa_init(DFA *dfa) {
    int i;
    int j;

    dfa->state_count = 0;
    dfa->start_state = 0;
    dfa->alphabet_size = 0;

    for (i = 0; i < MAX_DFA_STATES; i++) {
        dfa->states[i].is_accepting = 0;

        for (j = 0; j < MAX_NFA_STATES; j++) {
            dfa->states[i].states[j] = 0;
        }

        for (j = 0; j < MAX_ALPHABET; j++) {
            dfa->transitions[i][j] = -1;
        }
    }
}

/*
Ajoute un symbole à l'alphabet du DFA
s'il n'est pas déjà présent
*/
static void add_symbol_to_alphabet(DFA *dfa, char symbol) {
    int i;

    if (symbol == '\0') {
        return;
    }

    for (i = 0; i < dfa->alphabet_size; i++) {
        if (dfa->alphabet[i] == symbol) {
            return;
        }
    }

    dfa->alphabet[dfa->alphabet_size] = symbol;
    dfa->alphabet_size++;
}

/*
Construit l'alphabet à partir des transitions du NFA
On ignore les transitions epsilon
*/
static void build_alphabet(DFA *dfa, const NFA *nfa) {
    int i;

    for (i = 0; i < nfa->transition_count; i++) {
        add_symbol_to_alphabet(dfa, nfa->transitions[i].symbol);
    }
}

/*
Calcule l'epsilon-fermeture d'un ensemble d'états.

Cela signifie :
à partir d'un ensemble d'états,
on ajoute tous les états accessibles
uniquement avec des transitions epsilon.
*/
static void epsilon_closure(
    const NFA *nfa,
    int input_set[],
    int output_set[]
) {
    int changed;
    int i;

    for (i = 0; i < MAX_NFA_STATES; i++) {
        output_set[i] = input_set[i];
    }

    do {
        changed = 0;

        for (i = 0; i < nfa->transition_count; i++) {
            Transition t = nfa->transitions[i];

            if (t.symbol == '\0' && output_set[t.from]) {
                if (!output_set[t.to]) {
                    output_set[t.to] = 1;
                    changed = 1;
                }
            }
        }

    } while (changed);
}

/*
Calcule move(S, symbol).

Cela signifie :
depuis un ensemble d'états S,
où peut-on aller en lisant symbol ?
*/
static void move_set(
    const NFA *nfa,
    int input_set[],
    char symbol,
    int output_set[]
) {
    int i;

    for (i = 0; i < MAX_NFA_STATES; i++) {
        output_set[i] = 0;
    }

    for (i = 0; i < nfa->transition_count; i++) {
        Transition t = nfa->transitions[i];

        if (t.symbol == symbol && input_set[t.from]) {
            output_set[t.to] = 1;
        }
    }
}

/*
Compare deux ensembles d'états.
Renvoie 1 s'ils sont identiques, 0 sinon.
*/
static int same_set(int a[], int b[]) {
    int i;

    for (i = 0; i < MAX_NFA_STATES; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}

/*
Cherche si un ensemble d'états existe déjà comme état du DFA.

Renvoie son indice si oui.
Renvoie -1 sinon.
*/
static int find_dfa_state(DFA *dfa, int set[]) {
    int i;

    for (i = 0; i < dfa->state_count; i++) {
        if (same_set(dfa->states[i].states, set)) {
            return i;
        }
    }

    return -1;
}

/*
Ajoute un nouvel état au DFA à partir d'un ensemble d'états NFA
*/
static int add_dfa_state(DFA *dfa, const NFA *nfa, int set[]) {
    int i;
    int id = dfa->state_count;

    for (i = 0; i < MAX_NFA_STATES; i++) {
        dfa->states[id].states[i] = set[i];
    }

    /*
    Un état DFA est acceptant si l'ensemble qu'il représente
    contient l'état acceptant du NFA.
    */
    if (set[nfa->accept_state]) {
        dfa->states[id].is_accepting = 1;
    } else {
        dfa->states[id].is_accepting = 0;
    }

    dfa->state_count++;

    return id;
}

/*
Construit le DFA à partir du NFA
*/
void dfa_from_nfa(DFA *dfa, const NFA *nfa) {
    int initial_set[MAX_NFA_STATES] = {0};
    int initial_closure[MAX_NFA_STATES] = {0};

    int current_index;
    int symbol_index;

    dfa_init(dfa);

    build_alphabet(dfa, nfa);

    initial_set[nfa->start_state] = 1;

    epsilon_closure(nfa, initial_set, initial_closure);

    add_dfa_state(dfa, nfa, initial_closure);

    dfa->start_state = 0;

    current_index = 0;

    while (current_index < dfa->state_count) {

        for (symbol_index = 0; symbol_index < dfa->alphabet_size; symbol_index++) {
            char symbol = dfa->alphabet[symbol_index];

            int moved[MAX_NFA_STATES] = {0};
            int closure[MAX_NFA_STATES] = {0};

            int existing_state;

            move_set(
                nfa,
                dfa->states[current_index].states,
                symbol,
                moved
            );

            epsilon_closure(nfa, moved, closure);

            existing_state = find_dfa_state(dfa, closure);

            if (existing_state == -1) {
                existing_state = add_dfa_state(dfa, nfa, closure);
            }

            dfa->transitions[current_index][symbol_index] = existing_state;
        }

        current_index++;
    }
}

/*
Affiche le DFA
*/
void dfa_print(const DFA *dfa) {
    int i;
    int j;

    printf("DFA states: %d\n", dfa->state_count);

    printf("Alphabet: ");
    for (i = 0; i < dfa->alphabet_size; i++) {
        printf("%c ", dfa->alphabet[i]);
    }
    printf("\n");

    printf("DFA transitions:\n");

    for (i = 0; i < dfa->state_count; i++) {
        for (j = 0; j < dfa->alphabet_size; j++) {
            printf(
                "%d -- %c --> %d\n",
                i,
                dfa->alphabet[j],
                dfa->transitions[i][j]
            );
        }

        if (dfa->states[i].is_accepting) {
            printf("State %d is accepting\n", i);
        }
    }
}
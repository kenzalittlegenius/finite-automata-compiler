#include <stdio.h>
#include <string.h>

#include "minimize.h"
#include "dfa.h"


/*
Construit D',
c'est-à-dire le DFA minimal
obtenu à partir du DFA D.
*/


/*
Renvoie 1 si les états p et q sont distinguables,
0 sinon.
*/
static int are_distinguishable(
    const DFA *dfa,
    int p,
    int q,
    int class[]
) {
    int i;

    for (i = 0; i < dfa->alphabet_size; i++) {
        int next_p = dfa->transitions[p][i];
        int next_q = dfa->transitions[q][i];

        if (next_p == -1 && next_q == -1) {
            continue;
        }

        if (next_p == -1 || next_q == -1) {
            return 1;
        }

        if (class[next_p] != class[next_q]) {
            return 1;
        }
    }

    return 0;
}

/*
Minimise le DFA par raffinements successifs de classes.
*/
void minimize_dfa(const DFA *dfa, DFA *minimized) {
    int class[MAX_DFA_STATES];
    int new_class[MAX_DFA_STATES];

    int changed;
    int i;
    int j;
    int c;
    int class_count;

    dfa_init(minimized);

    /*
    On copie l'alphabet.
    */
    minimized->alphabet_size = dfa->alphabet_size;

    for (i = 0; i < dfa->alphabet_size; i++) {
        minimized->alphabet[i] = dfa->alphabet[i];
    }

    for (i = 0; i < dfa->state_count; i++) {
        if (dfa->states[i].is_accepting) {
            class[i] = 1;
        } else {
            class[i] = 0;
        }
    }

    class_count = 2;

    /*
    Raffinement des classes jusqu'à stabilisation.
    */
    do {
        changed = 0;

        for (i = 0; i < dfa->state_count; i++) {
            new_class[i] = -1;
        }

        class_count = 0;

        for (i = 0; i < dfa->state_count; i++) {
            if (new_class[i] != -1) {
                continue;
            }

            new_class[i] = class_count;

            for (j = i + 1; j < dfa->state_count; j++) {
                if (class[i] == class[j]
                    && !are_distinguishable(dfa, i, j, class)) {
                    new_class[j] = class_count;
                }
            }

            class_count++;
        }

        for (i = 0; i < dfa->state_count; i++) {
            if (class[i] != new_class[i]) {
                changed = 1;
            }

            class[i] = new_class[i];
        }

    } while (changed);

    /*
    Chaque classe devient un état du DFA minimal.
    */
    minimized->state_count = class_count;
    minimized->start_state = class[dfa->start_state];

    /*
    Initialisation des transitions du DFA minimal.
    */
    for (i = 0; i < MAX_DFA_STATES; i++) {
        for (j = 0; j < MAX_ALPHABET; j++) {
            minimized->transitions[i][j] = -1;
        }
    }

    /*
    Définition des états acceptants du DFA minimal.
    */
    for (i = 0; i < dfa->state_count; i++) {
        c = class[i];

        if (dfa->states[i].is_accepting) {
            minimized->states[c].is_accepting = 1;
        }
    }

    /*
    Construction des transitions du DFA minimal.
    */
    for (i = 0; i < dfa->state_count; i++) {
        int from_class = class[i];

        for (j = 0; j < dfa->alphabet_size; j++) {
            int target = dfa->transitions[i][j];

            if (target != -1) {
                int to_class = class[target];

                minimized->transitions[from_class][j] = to_class;
            }
        }
    }
}
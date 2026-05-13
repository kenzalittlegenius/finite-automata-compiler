#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "ast.h"
#include "parser_regex.h"
#include "nfa.h"

int main(int argc, char **argv) {

    char *regex;

    ASTNode *tree;

    NFA nfa;
    NFAFragment frag;

    if (argc != 2) {
        printf("Usage: %s <regex_file>\n", argv[0]);
        return 1;
    }

    regex = read_first_line(argv[1]);

    if (regex == NULL) {
        printf("Error: can't read regex file\n");
        return 1;
    }

    trim_newline(regex);

    printf("Regex: %s\n", regex);

    /*
    Construction de l'AST
    */
    tree = parse_regex(regex);

    if (tree == NULL) {
        printf("Parsing failed\n");

        free(regex);

        return 1;
    }

    printf("AST: ");

    ast_print(tree);

    printf("\n");

    /*
    Construction du NFA
    */
    nfa_init(&nfa);

    frag = nfa_build_from_ast(&nfa, tree);

    nfa.start_state = frag.start;
    nfa.accept_state = frag.end;

    printf("\n");

    nfa_print(&nfa);

    /*
    Libération mémoire
    */
    ast_free(tree);

    free(regex);

    return 0;
}
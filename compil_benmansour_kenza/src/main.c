#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "ast.h"
#include "parser_regex.h"
#include "nfa.h"
#include "dfa.h"
#include "minimize.h"
#include "graphviz.h"
#include "generator.h"

int main(int argc, char **argv) {
    char *regex;
    ASTNode *tree;

    NFA nfa;
    NFAFragment frag;

    DFA dfa;
    DFA minimized;

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

    tree = parse_regex(regex);

    if (tree == NULL) {
        printf("Parsing failed\n");
        free(regex);
        return 1;
    }

    printf("\nAST:\n");
    ast_print(tree);
    printf("\n");

    export_ast_to_dot(tree, "ast.dot");

    nfa_init(&nfa);
    frag = nfa_build_from_ast(&nfa, tree);

    nfa.start_state = frag.start;
    nfa.accept_state = frag.end;

    printf("\nNFA:\n");
    nfa_print(&nfa);
    export_nfa_to_dot(&nfa, "nfa.dot");

    dfa_from_nfa(&dfa, &nfa);

    printf("\nDFA:\n");
    dfa_print(&dfa);
    export_dfa_to_dot(&dfa, "dfa.dot");

    minimize_dfa(&dfa, &minimized);

    printf("\nDFA minimal D':\n");
    dfa_print(&minimized);
    export_dfa_to_dot(&minimized, "min_dfa.dot");

    generate_lexer_c(&minimized, "generated_lexer.c");

    ast_free(tree);
    free(regex);


    generate_lexer_c(&minimized, "generated_lexer.c");
    printf("\nCompiling generated lexer...\n");
    int result = system(
        "gcc -Wall -Wextra -std=c11 generated_lexer.c -o lexer_generated"
    );
    printf("Compilation return code = %d\n", result);

    return 0;
}
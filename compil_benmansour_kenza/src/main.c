#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "ast.h"

int main(int argc, char **argv) {
    char *regex;

    if (argc != 2) {
        printf("Add the regex file to %s\n", argv[0]);
        return 1;
    }

    regex = read_first_line(argv[1]);

    if (regex == NULL) {
        printf("Error: can't read the regex\n");
        return 1;
    }

    trim_newline(regex);

    printf("Regex: %s\n", regex);

    ASTNode *a = ast_create_symbol('a');
    ASTNode *b = ast_create_symbol('b');

    ASTNode *union_node = ast_create_binary(AST_UNION, a, b);
    ASTNode *star_node = ast_create_unary(AST_STAR, union_node);

    printf("AST: ");
    ast_print(star_node);
    printf("\n");

    ast_free(star_node);
    free(regex);

    return 0;
}
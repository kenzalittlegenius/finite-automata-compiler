//le parser_regex permet de construire les arbres syntaxiques ast
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser_regex.h"
#include "ast.h"

static const char *current;

/* Déclarations internes */
static ASTNode *parse_expr(void);
static ASTNode *parse_concat(void);
static ASTNode *parse_base(void);
static ASTNode *parse_factor(void);



ASTNode *parse_regex(const char *regex){
    ASTNode *tree; 

    current = regex;
    tree = parse_expr();

    if(*current != '\0'){
        printf("Syntax Error : %c \n", *current);
        ast_free(tree);
        return NULL;
    }

    return tree;
}

static ASTNode *parse_expr(void) {
    ASTNode *left = parse_concat();

    while (*current == '|') {
        current++;

        ASTNode *right = parse_concat();
        left = ast_create_binary(AST_UNION, left, right);
    }

    return left;
}

static ASTNode *parse_concat(void) {
    ASTNode *left = parse_factor();

    while (*current != '\0'
        && *current != ')'
        && *current != '|') {

        ASTNode *right = parse_factor();
        left = ast_create_binary(AST_CONCAT, left, right);
    }

    return left;
}

static ASTNode *parse_base(void) {
    ASTNode *node;

    if (*current == '(') {
        current++;

        node = parse_expr();

        if (*current != ')') {
            printf("Erreur : parenthèse fermante manquante\n");
            ast_free(node);
            return NULL;
        }

        current++;
        return node;
    }

    if (isalnum((unsigned char)*current)) {
        char symbol = *current;
        current++;
        return ast_create_symbol(symbol);
    }

    printf("Erreur : symbole inattendu '%c'\n", *current);
    return NULL;
}

static ASTNode *parse_factor(void) {
    
    ASTNode *node = parse_base();

    while (*current == '*') {
        current++;
        node = ast_create_unary(AST_STAR, node);
    }

    return node;
}
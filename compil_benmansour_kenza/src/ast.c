#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

//noeud symbole = caractère de l'expression régulière
ASTNode *ast_create_symbol(char symbol) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (node == NULL) return NULL;

    node->Type = AST_SYMBOL;
    node->symbol = symbol;
    node->left = NULL;
    node->right = NULL;

    return node;
}
//noeud unaire = opération agissant un élément 
ASTNode *ast_create_unary(ASTType type, ASTNode *child) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (node == NULL) return NULL;

    node->Type = type;
    node->symbol = '\0';
    node->left = child;
    node->right = NULL;

    return node;
}
//noeud binaire = opération entre deux éléments (concaténation et union)
ASTNode *ast_create_binary(ASTType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (node == NULL) return NULL;

    node->Type = type;
    node->symbol = '\0';
    node->left = left;
    node->right = right;

    return node;
}
//fonction de l'affichage de l'ast 
void ast_print(ASTNode *node) {
    if (node == NULL) return;

    switch (node->Type) {
        case AST_SYMBOL:
            printf("%c", node->symbol);
            break;

        case AST_STAR:
            printf("STAR(");
            ast_print(node->left);
            printf(")");
            break;

        case AST_UNION:
            printf("UNION(");
            ast_print(node->left);
            printf(",");
            ast_print(node->right);
            printf(")");
            break;

        case AST_CONCAT:
            printf("CONCAT(");
            ast_print(node->left);
            printf(",");
            ast_print(node->right);
            printf(")");
            break;
    }
}
//fonction pour libérer le sous-arbre droit ou le sous-arbre gauche
void ast_free(ASTNode *node) {
    if (node == NULL) return;

    ast_free(node->left);
    ast_free(node->right);
    free(node);
}
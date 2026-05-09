//garde d'inclusion 
#ifndef AST_H
#define AST_H


//définission des noeuds de l'arbre syntaxique

//les types de noeuds possibles : symbole, union concaténation et étoile de Keene
typedef enum {
    AST_SYMBOL,
    AST_UNION, 
    AST_CONCAT,
    AST_STAR,
}ASTType;

// Structure d'un noeud : noeud gauche et noeud droit
typedef struct ASTNode {
    ASTType Type; 
    char symbol;
    struct ASTNode *left;
    struct ASTNode *right; 
} ASTNode;

//Déclaration des fonctions utilitaires pour l'AST que l'on implémente dans ast.c 
ASTNode *ast_create_symbol(char symbol);
ASTNode *ast_create_unary(ASTType type, ASTNode *child);
ASTNode *ast_create_binary(ASTType type, ASTNode *left, ASTNode *right);

void ast_print(ASTNode *node);
void ast_free(ASTNode *node);

#endif
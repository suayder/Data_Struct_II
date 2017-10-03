#ifndef TREE_H
#define TREE_H

typedef struct no{
    int info;
    struct no *right;
    struct no *left;
    char collor;
}Tree;

void colour(Tree **root);

void insert_tree(Tree **root, int info);

Tree *insert(Tree *root, int info);

char returnCollor(Tree *tree);

void swapCollor(Tree **tree);

Tree *left_rotation(Tree *root);

Tree *right_rotation(Tree *root);

Tree *move_redToRight(Tree *root);

Tree *move_redToleft(Tree *root);

Tree *balance(Tree *root);

void print_out(Tree *root);

Tree *removal(Tree *root, int info);

int remove_tree(Tree *root, int info);

Tree *search_minor(Tree *root);

Tree *remove_minor(Tree *root);

#endif

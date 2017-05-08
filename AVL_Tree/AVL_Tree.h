/*
 * AVL_Tree.h
 *
 *  Created on: 5 de mai de 2017
 *      Author: Suayder
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <stdio.h>
#include <stdlib.h>

/*typedef struct no{
    int key;
    struct no *right;
    struct no *left;
}Tno;*/

typedef struct no{
    int key;
    int FB;
    struct no *left;
    struct no *right;
}Tno;

void startTree(Tno **aux);
int height(Tno *source);
int balanceFactor(Tno *source);
void delete_tree(Tno **root);
Tno *rightRotation(Tno *source);
Tno* leftRotation(Tno *source);
Tno *duo_rotation_r (Tno *source);
Tno *duo_rotation_l(Tno *source);
Tno *balance_AVL(Tno *source);
void insert_avl(Tno **source, int info);
void RemoveAVL(Tno **source, int key);
void R_print_in_order(Tno *source);
void R_print_pre_order(Tno *source);
Tno *search(Tno *source, int key);
Tno *find_father(Tno *source, Tno *son);
void show_fathers_and_child(Tno *root);
int isbalanced(Tno *root);
void updateFB(Tno **root);
int contNodes(Tno *root); //Will count number of nodes into each subtree

void order_A(Tno *root); //print Order A and B
void order_B(Tno *root);


#endif /* AVL_TREE_H_ */

#include <stdio.h>
#include <stdlib.h>
#include "Functions_Red-Black_Tree.h"

char returnCollor(Tree *tree){
  return(tree==NULL)?'b':tree->collor;
}

void swapCollor(Tree **tree){
  (*tree)->collor=(returnCollor(*tree)=='b')?'r':'b';
  (*tree)->left->collor=((*tree)->left && returnCollor((*tree)->left)=='b')?'r':'b';
  (*tree)->right->collor=((*tree)->right && returnCollor((*tree)->right)=='b')?'r':'b';
}

Tree *move_redToleft(Tree *root){
  swapCollor(&root);
  //Ao mudar a cor caso apareça dois vermelhos seguidos
  if(root->right && root->right->left && returnCollor(root->right->left)=='r'){
    root->right=right_rotation(root->right);
    root=left_rotation(root);
    swapCollor(&root);
  }
  return root;
}

Tree *move_redToRight(Tree *root){
  swapCollor(&root);
  //Mesmo que o caso passado, ao mudar a cor caso apareça dois vermelhos seguidos
  if(root->left && root->left->left && returnCollor(root->left->left)=='r'){
    root=right_rotation(root->right);
    swapCollor(&root);
  }
  return root;
}

Tree *left_rotation(Tree *root){
    Tree *tree=root->right;
    root->right=tree->left;
    tree->left=root;
    tree->collor=root->collor; // aqui a cor da nova raiz será a cor da raiz
    root->collor='r';//Agora a raiz(que é filho esquerdo) recebe a cor vermelha
    return tree;
}

Tree *right_rotation(Tree *root){
  Tree *tree=root->left;
  root->left=tree->right;
  tree->right=root;
  tree->collor=root->collor;// aqui a cor da nova raiz será a cor da raiz
  root->collor='r';//Agora a raiz(que é filho direito) recebe a cor vermelha
  return tree;
}

Tree *balance(Tree *root){
  //Condição garante que um nó vermelho nunca seja filho esquerdo
  if(returnCollor(root->right)=='r'){
    root=left_rotation(root);
  }
  //Se  o filho da direita e neto da esquerda são vermelhos
  if(root->left && returnCollor(root->right)=='r' && returnCollor(root->left->left)=='r'){
    root=right_rotation(root);
  }
  //Se os dois filhos forem vermelhos a cor será trocada
  if(returnCollor((root)->left)=='r' && returnCollor(root->right)=='r'){
    swapCollor(&root);
  }
  return root;
}

void insert_tree(Tree **root, int info){
    (*root)=insert((*root), info);
    printf("info %d\n", (*root)->left->info);
    if((*root)!= NULL)
      (*root)->collor='b';
}

Tree *insert(Tree *root, int info){
  if(root==NULL){
    Tree *tree=(Tree*) malloc(sizeof(Tree));
    tree->left=NULL;
    tree->right=NULL;
    tree->info=info;
    tree->collor='r';
    root=tree;
    return (root);
  }
  else{
    if(root->info>info){ //move to left
        root->left=insert(root->left,info);
    }
    else//move to right
        root->right=insert(root->right,info);

  }
  //Não posso ter filho a direita vermelho
  if(returnCollor(root->right)=='r' && returnCollor(root->left)=='b')
    root=left_rotation(root);
  //Não posso ter dois filhos vermelho seguidos
  if(returnCollor(root->left)=='r' && returnCollor(root->left->left)=='r')
    root=right_rotation(root);
  if(returnCollor(root->left)=='r' && returnCollor(root->right)=='r')
    swapCollor(&root);
  return root;
}

Tree *search(Tree *root, int info){
  while (root!=NULL) {
    if(root->info>info)
      root=root->left;
    else if(root->info<info)
      root=root->right;
    else
      return root;
  }
  return NULL;
}

void print_out(Tree *root){
    if(root->left!=NULL) print_out(root->left);
    printf("%d\n", root->info);
    if(root->right!=NULL) print_out(root->right);
}
Tree *search_minor(Tree *root){
  Tree *aux1=root;
  Tree *aux2=root->right;
  while (aux2!=NULL) {
    aux1=aux2;
    aux2=aux2->left;
  }
  return aux1;
}
Tree *remove_minor(Tree *root){
  if(root->left == NULL){
    free(root);
    return NULL;
  }
  if(returnCollor(root->left)=='b' && returnCollor(root->left->left)=='b')
    root=move_redToleft(root);
  root->left=remove_minor(root->left);
  return balance(root);
}
int remove_tree(Tree *root, int info){
      if(search(root, info)){
        Tree *tree=root;
        root=removal(tree, info);
        if(root!=NULL)
          root->collor='b';
        return 1;
      }
      return 0;
}

Tree *removal(Tree *root, int info){
  if(info<root->info){
    if(returnCollor(root->left)=='b' && returnCollor(root->left->left)=='b')
      root=move_redToleft(root);

    root->left=removal(root->left, info);
  }
  else{
    if(returnCollor(root->left)=='r')
      root=right_rotation(root);
    if(info==root->info && root->right==NULL){
      free(root);
      return NULL;
    }
    if(returnCollor(root->right)=='b' && returnCollor(root->right->left)=='b')
      root=move_redToRight(root);
    if(info == root->info){
      Tree *aux= search_minor(root->right);
      root->info=aux->info;
      root->right=remove_minor(root->right);
    }
    else
      root->right=removal(root->right, info);
  }
  return balance(root);
}

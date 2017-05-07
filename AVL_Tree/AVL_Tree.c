/*
 ============================================================================
 Name        : AVL_Tree.c
 Author      : COSTA, S.M.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include"AVL_Tree.h"


void startTree(Tno **aux){
  (*aux)->FB = 0;
  (*aux)->left=NULL;
  (*aux)->right=NULL;
}

int height (Tno* root){ // calculate height
	int left_height, right_height;
	if (root == NULL) return 0;
	else{
		left_height = height (root->left); //Walks over the tree
		right_height = height (root->right);
		if (left_height < right_height)// if the height increased
			return (right_height+1);     //return key
		else
			return (left_height+1);
	}
}

int balanceFactor(Tno *root){
    if(root == NULL) return 0;
    return (height(root->right) - height(root->left));
}

Tno *rightRotation(Tno *root){

	Tno *aux= root->left;
	Tno *temp = aux->right;
	aux->right = root;
	root->left= temp;
	return aux;
}

Tno* leftRotation(Tno *root){

	Tno *aux= root->right;
	Tno *temp = aux->left;
	aux->left = root;
	root->right= temp;

	return aux;
}

Tno *duo_rotation_r (Tno *root){
	root->left = leftRotation(root->left);
	return rightRotation(root);
}

Tno *duo_rotation_l(Tno *root){
	root->right = rightRotation(root->right);
	return leftRotation(root);
}

Tno *balance_AVL(Tno *root){
	if(root != NULL){
		root->FB = balanceFactor(root);
		if(root->FB == -2){
			root->left->FB=balanceFactor(root->left);
			if(root->left->FB < 0){
				root = rightRotation(root);
				}
			else{
				root =  duo_rotation_r(root);
			}
		}
		else if(root->FB == 2){
			root->right->FB = balanceFactor(root->right);
			if(root->right->FB > 0){
				root = leftRotation(root);
			}
			else{
				root =  duo_rotation_l(root);
			}
		}
		root->left = balance_AVL(root->left);
		root->right = balance_AVL(root->right);

		updateFB(&root);
		while(isbalanced(root)==-1){
			root = balance_AVL(root);
		}
	}
    return root;
}

void updateFB(Tno **root){
	if(*root == NULL) return;
	(*root)->FB = balanceFactor(*root);
	if((*root)->left) updateFB(&(*root)->left);
	if((*root)->right) updateFB(&(*root)->right);
}

int isbalanced(Tno *root){

	if(root==NULL) return 0;
	if (root->FB>1 || root->FB<(-1)) return -1;
	else
		return (isbalanced(root->left) + isbalanced(root->right));
}

Tno *search(Tno *root, int key){

	if(root == NULL) return NULL;

	if(root->key == key) return root;

	else {
		if(key < root->key) return search(root->left,key);

		else  return search(root->right,key);
	}
}

void insert_avl(Tno **root, int key){
  if((*root)==NULL){
    Tno *aux=(Tno*) malloc(sizeof(Tno));
    if(aux==NULL) exit(1);
    startTree(&aux);
    aux->key=key;
    (*root)=aux;
  }
  else{
    if(key < (*root)->key){
			insert_avl(&((*root)->left),key);
		}
		else{
			insert_avl(&((*root)->right),key);
		}
  }
  *root = balance_AVL(*root);
}

void R_print_in_order(Tno *root){
  if(root->left!=NULL) R_print_in_order(root->left);
  printf("%d\n", root->key);
  if(root->right!=NULL) R_print_in_order(root->right);
}

void R_print_pre_order(Tno *root){
	printf("%d\n", root->key);
	if(root->left!=NULL) R_print_pre_order(root->left);
	if(root->right!=NULL) R_print_pre_order(root->right);
}

Tno *find_father(Tno *root, Tno *son){

	if(root == NULL) return NULL;

	if(root == son) return root;

	else if(root->left == son || root->right == son) return root;

	else {
		if(son->key < root->key) return find_father(root->left,son);

		else  return find_father(root->right, son);
	}
}

void RemoveAVL(Tno **root, int key){

	if((*root) == NULL){
		printf("Empty Tree");
		return;
	}
	Tno *aux = search((*root), key);
	Tno *father = find_father((*root), aux);

	if(aux == NULL){
		printf("Key Not Found");
		return;
	}

	//Case there is only the root
	else if(((*root)->key == key) && ((*root)->left == NULL) && ((*root)->right == NULL)){
		free((*root));
		(*root) = NULL;
		return;
	}
	// Case there isn't sons
	else if(aux->left==NULL && aux->right == NULL){

		if(father->left == aux) father->left = NULL;
		else father->right = NULL;

		free(aux);
		(*root) = balance_AVL((*root));
	}

	//Case there is only the right son
	else if((aux->left == NULL) && (aux->right != NULL)){

		if(father->left == aux) father->left = aux->right;
		else father->right = aux->right;

        free(aux);
    	(*root) = balance_AVL((*root));
	}

	//Case there is only the left son
	else if((aux->left != NULL) && (aux->right == NULL)){

		if(father->left == aux) father->left = aux->left;
		else father->right = aux->left;

		free(aux);
		(*root) = balance_AVL((*root));
	}
	// Two sons
	else
	{
		//Get son to the left of the sub tree to the right
		Tno *aux2, *father2 = aux;
		aux2=aux->right;

		while (1){
			if(aux2->left == NULL) break;
			father2=aux2;
			aux2=aux2->left;
		}
		// Turn of son's points
		if(father2 == aux){
			if(aux2->right!=NULL)
				father2->right = aux2->right;
			else
				father2->right = NULL;
		}
		else if(aux2->right != NULL)
			father2->left = aux2->right;
		else
			father2->left = NULL;

		//linking father with aux2
		aux2->left=aux->left;
		aux2->right=aux->right;

		if(father == (*root))
			(*root) = aux2;
		else if(father->left==aux)
			father->left = aux2;
		else if(father->right == aux)
			father->right = aux2;

		aux->left = NULL;
		aux->right = NULL;

		free(aux);

		(*root) = balance_AVL((*root));

	  }

}

void show_fathers_and_sons(Tno *root){
	if(root->left && (root->left->left!=NULL || root->left->right!=NULL)) show_fathers_and_sons(root->left);

	printf("\nFather key: %d", root->key);
	if(root->left != NULL) printf(" - Left son key: %d", root->left->key);
	if(root->right) printf(" - Right son key: %d",root->right->key);
	puts("");

	if(root->right && (root->right->right!=NULL || root->right->left!=NULL)) show_fathers_and_sons(root->right);
}


int main(void) {

	  Tno *root=NULL;
	  insert_avl(&root, 20);
	  insert_avl(&root, 10);
	  insert_avl(&root, 30);
	  insert_avl(&root, 25);
	  insert_avl(&root, 35);
	  insert_avl(&root, 23);
	  insert_avl(&root, 8);
	  insert_avl(&root, 9);
	  insert_avl(&root, 4);
	  insert_avl(&root, 2);
	  insert_avl(&root, 17);
	  insert_avl(&root, 13);
	  insert_avl(&root, 1);

	  R_print_pre_order(root);
	  puts("---------");
	  RemoveAVL(&root, 20);
	  R_print_pre_order(root);


	  show_fathers_and_sons(root);



	return EXIT_SUCCESS;
}

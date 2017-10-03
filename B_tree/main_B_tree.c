#include<stdio.h>
#include<stdlib.h>
#include "B_tree.c"


int main(){
	T_tree *root = NULL;
	int i, aux;
	for(i=0;i<20;i++){
		insert(&root, aux=rand()%50);
		printf("ins: %d\n",aux);
	}
	deletion(42, &root);
	deletion(12, &root);
	traversal(root);
}

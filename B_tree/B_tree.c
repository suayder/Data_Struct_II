#include<stdio.h>
#include<stdlib.h>
#include "B_tree.h"

#define MAX 5
#define MIN 2


/* criação de um nó*/
T_tree *createNo(int key, T_tree *search, T_tree *filho){
	T_tree *No;
	No = (T_tree*)malloc(sizeof(T_tree));
	No->key[1] = key;
    No->count = 1;
    No->pointer[0] = search;
    No->pointer[1] = filho;
    return No;
}

/* Adiciona o valor na posição apropriada */
void addkeyToNo(int key, int pos, T_tree *No,T_tree *filho){
    int i = No->count;
    while (i > pos){
        No->key[i+1] = No->key[i];
        No->pointer[i+1] = No->pointer[i];
        i--;
    }
    No->key[i+1] = key;
    No->pointer[i+1] = filho;
    No->count++;
}

/* Separa o Nó */
void spliT_treede (int key, int *pval, int pos, T_tree *no,T_tree *filho, T_tree **newNo){
    int mediana, i;

    if(pos > MIN)
        mediana = MIN + 1;
    else
        mediana = MIN;

    *newNo = (T_tree *)malloc(sizeof(T_tree));
    i = mediana + 1;
    while (i <= MAX){
        (*newNo)->key[i - mediana] = no->key[i];
        (*newNo)->pointer[i - mediana] = no->pointer[i];
        i++;
    }
    no->count = mediana;
    (*newNo)->count = MAX - mediana;

    if(pos <= MIN){
        addkeyToNo(key, pos, no, filho);
    }
	else{
        addkeyToNo(key, pos - mediana, *newNo, filho);
    }
    *pval = no->key[no->count];
    (*newNo)->pointer[0] = no->pointer[no->count];
    no->count--;
}

/* Coloca o valor solicitado dentro do nó */
int setValueInNode(int key, int *pval,T_tree *root, T_tree **filho){
    int pos;
    if(!root){
        *pval = key;
        *filho = NULL;
        return 1;
    }

    if(key < root->key[1]){
       pos = 0;
    }
	else{
        for(pos = root->count;(key < root->key[pos] && pos > 1); pos--);
        if(key == root->key[pos]){
            printf("Duplicacoes nao sao permitidas\n");
            return 0;
        }
    }
    if(setValueInNode(key, pval, root->pointer[pos], filho)){
        if(root->count < MAX){
            addkeyToNo(*pval, pos, root, *filho);
        } else{
            spliT_treede(*pval, pval, pos, root, *filho, filho);
            return 1;
        }
    }
    return 0;
}

/* Insere um valor na árvore */
void insert(T_tree **root, int key){
    int flag, i;
    T_tree *filho;

    flag = setValueInNode(key, &i, *root, &filho);
    if(flag)
        *root = createNo(i, *root, filho);
}

/* Faz a cópia do sucessor do valor a ser deletado */
void copySuccessor(T_tree *root, int pos){
    T_tree *aux;
    aux = root->pointer[pos];

    while(aux->pointer[0] != NULL)
        aux = aux->pointer[0];
    root->key[pos] = aux->key[1];
}

/* remove o valor de um nó e reorganiza os valores */
void removeKey(T_tree *root, int pos){
    int i = pos + 1;
    while (i <= root->count){
        root->key[i-1] = root->key[i];
        root->pointer[i-1] = root->pointer[i];
        i++;
    }
    root->count--;
}

/* Troca o valor do pai com o do filho da direita */
void doRightShift(T_tree *root, int pos){
    T_tree *aux = root->pointer[pos];
    int i = aux->count;

    while (i > 0){
        aux->key[i+1] = aux->key[i];
        aux->pointer[i+1] = aux->pointer[i];
    }
    aux->key[1] = root->key[pos];
    aux->pointer[1] = aux->pointer[0];
    aux->count++;

    aux = root->pointer[pos-1];
    root->key[pos] = aux->key[aux->count];
    //root->pointer[pos] = x->pointer[x->count];
    aux->count--;
    return;
}

/* Troca o valor do pai para com o do filho da esquerda */
void doLeftShift(T_tree *root, int pos){
    int i = 1;
    T_tree *aux = root->pointer[pos - 1];

    aux->count++;
    aux->key[aux->count] = root->key[pos];
    aux->pointer[aux->count] = root->pointer[pos]->pointer[0];

    aux = root->pointer[pos];
    root->key[pos] = aux->key[1];
    aux->pointer[0] = aux->pointer[1];
    aux->count--;

    while (i <= aux->count){
        aux->key[i] = aux->key[i + 1];
        aux->pointer[i] = aux->pointer[i + 1];
        i++;
    }
    return;
}

/* Junção de nós, para quando há um nó vazio após o processo de remoção, faz-se a junção entre o valor no nó pai
mais próximo do valor removido com o valor mais próximo de um nó irmão do valor removido. */
void mergeNodes(T_tree *root, int pos){
    int i = 1;
    T_tree *aux1 = root->pointer[pos], *aux2 = root->pointer[pos - 1];

    aux2->count++;
    aux2->key[aux2->count] = root->key[pos];
    aux2->pointer[aux2->count] = aux1->pointer[0];

    while (i <= aux1->count){
        aux2->count++;
        aux2->key[aux2->count] = aux1->key[i];
        aux2->pointer[aux2->count] = aux1->pointer[i];
        i++;
    }

    i = pos;
    while (i < root->count){
        root->key[i] = root->key[i + 1];
        root->pointer[i] = root->pointer[i + 1];
        i++;
    }
    root->count--;
    free(aux1);
}

/* Função para os ajustes necessários após a remoção de um valor.
faremos a função necessária de ajuste dependendo da posição do filho que teve um de seus valores
removidos */
void adjusT_treede(T_tree *root, int pos){
    if(!pos){
        if(root->pointer[1]->count > MIN){
            doLeftShift(root, 1);
        }
		else{
            mergeNodes(root, 1);
        }
    }
	else{
        if(root->count != pos){
            if(root->pointer[pos - 1]->count > MIN){
                doRightShift(root, pos);
            }
			else{
                if(root->pointer[pos + 1]->count > MIN){
                    doLeftShift(root, pos + 1);
                } else{
                    mergeNodes(root, pos);
                }
            }
        }
		else{
            if(root->pointer[pos - 1]->count > MIN)
                doRightShift(root, pos);
            else
                mergeNodes(root, pos);
        }
    }
}

/* Função usada para descer a árvore recursivamente e encontrar o valor a ser removido
e especificar o processo de remoção a ser utilizado dependendo da quantidade de filhos que o nó
tem e de onde se encontra o valor a ser removido*/
int delKeyFromNo(int key, T_tree *root){
    int pos, flag = 0;
    if(root){
        if(key < root->key[1]){
            pos = 0;
        }
		else{
            for(pos = root->count;(key <= root->key[pos] && pos > 0); pos--){
	            if(key == root->key[pos]){
	            	//flag indica que o valor a ser removido foi encontrado
	                flag = 1;
	                break;
	            }
				else{
	                flag = 0;
	            }
	        }
        }
        if(flag){
        	/* caso valor a ser removido não seja de um nó folha */
           if(root->pointer[pos-1]){
	            copySuccessor(root, pos);
	            /* remoção recursiva do valor no nó sucessor (troca-se o valor a ser removido
	            pelo valor do nó sucessor, logo o programa busca o valor a ser removido no nó sucessor)*/
	            flag = delKeyFromNo(root->key[pos], root->pointer[pos]);
        	}
			else{
            	removeKey(root, pos);
        	}
        }
		else{
			/* continua a busca na árvore pelo valor dado*/
            flag = delKeyFromNo(key, root->pointer[pos]);
        }
        /* caso o nó onde o valor foi removido tenha um ponteiro a direita do valor removido é necessário checar
        se não há ajustes a serem feitos.*/
        if(root->pointer[pos]){
            if(root->pointer[pos]->count < MIN)
                adjusT_treede(root, pos);
        }
    }
    return flag;
}

/* Função inicial de remoção de valor da árvore B */
void deletion(int key,T_tree **search){
    T_tree *temp;
    if(!delKeyFromNo(key, *search)){
        printf("Valor nao esta presente na arvore\n");
        return;
    }
	else{
        if((*search)->count == 0){
            temp = *search;
            *search = (*search)->pointer[0];
            free(temp);
        }
    }
    return;
}

/* Procura por valor na árvore B */
void search(int info, int *pos, T_tree *root){
    if(!root){
        return;
    }

    if(info < root->key[1]){
        *pos = 0;
    }
	else{
        for(*pos = root->count;(key < root->key[*pos] && *pos > 1); (*pos)--);
        if(info == root->key[*pos]){
            printf("value: %d \n", info);
            return;
        }
    }
    search(info, pos, root->pointer[*pos]);
    return;
}

/* Travessia da árvore B */
void traversal(T_tree *root){
    int i;
    if(root){
        for(i = 0; i < root->count; i++){
            traversal(root->pointer[i]);
            printf("%d ", root->key[i + 1]);
        }
        traversal(root->pointer[i]);
    }
}

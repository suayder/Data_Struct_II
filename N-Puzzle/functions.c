#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MODULO(x)(x>=0?(x):(x*(-1)))
#include<functions.h>

typedef struct tree{
  int **mat;
  char text[5];
  struct tree *lr_point; //left to right
  struct tree *rl_point; //right to left
  struct tree *lh_point; //bottom up (low - high)
  struct tree *hl_point; //top to bottom (high - low)
}T_tree;

typedef struct stk{
  int heuristc;
  T_tree *type_tree;
  struct stk *prox;
}stack;

typedef struct queue{
  T_tree *type_tree;
  stack *type_stack;
  struct queue *prox;
}T_queue;

T_queue *first=NULL;
T_queue *last=NULL;
unsigned int cont=0, iter=0;

void insert_queue(T_tree *T, stack *h){
  cont++;
  T_queue *aux=(T_queue*) malloc(sizeof(T_queue));
  if(aux==NULL) printf("MEMORIA CHEIA\n");
  aux->prox=NULL;
  aux->type_tree=T;
  aux->type_stack=h;
  if(first==NULL){
      first=aux;
      last=aux;
  }
  else{
    last->prox=aux;
    last=aux;
  }
}

void remove_queue(){
  cont--;
  //if(first==NULL && last==NULL) printf("VAZIO\n");
  if(first==last){
    free(first);
    first=NULL;
    last=NULL;
  }
  else{
    T_queue *aux=first;
    T_tree *aux_T, *aux_T2;
    while (aux->prox!=last)
      aux=aux->prox;
    last=aux;
    aux_T2=aux->type_tree;
    if (aux_T2->rl_point==last->prox->type_tree){
      aux_T=aux_T2->rl_point;
      aux_T2->rl_point=NULL;
      //printf("%s\n","OK1");
    }
    else if(aux_T2->lr_point==last->prox->type_tree){
      //printf("%s\n","OK2");
      aux_T=aux_T2->lr_point;
      aux_T2->lr_point=NULL;
    }
    else if(aux_T2->lh_point==last->prox->type_tree){
      //printf("%s\n","OK3");
      aux_T=aux_T2->lh_point;
      aux_T2->hl_point=NULL;
    }
    else if(aux_T2->hl_point==last->prox->type_tree){
      aux_T=aux_T2->hl_point;
      aux_T2->hl_point=NULL;
    }
    free(aux_T);
    free(aux->prox);
    last->prox=NULL;
  }
}
void print_queue(){
  T_queue *aux=first;
  while (aux!=NULL) {
    printf("\nAction: %s", aux->type_tree->text);
    aux=aux->prox;
  }
  //printf("\n");
  //printf("%s\n", "FIM");
}

void push(stack **h, int value, T_tree *tree){
  stack *aux=(stack*) malloc(sizeof(stack));
  if(aux==NULL) printf("MEMORY FULL\n");
  aux->heuristc=value;
  aux->type_tree=tree;
  aux->prox=NULL;
  if((*h)==NULL) (*h)=aux;
  else if(aux->heuristc<=(*h)->heuristc){
    aux->prox=(*h);
    (*h)=aux;
  }
  else{
    stack *aux2=(*h);
    while (aux2->prox!=NULL && aux2->prox->heuristc<=value)
      aux2=aux2->prox;
    if(aux2->prox!=NULL){
      aux->prox=aux2->prox;
      aux2->prox=aux;
    }
    else
      aux2->prox=aux;
  }
}
void pop(stack **h){
  if((*h)->prox==NULL){
    free(*h);
    (*h)=NULL;
  }
  else{
    stack *aux=(*h);
    (*h)=(*h)->prox;
    free(aux);
  }
}
void print_stack(stack *h){
  while (h!=NULL) {
    printf("HH: %d\n", h->heuristc);
    h=h->prox;
  }
}


void start(T_tree **tree){  T_queue *aux=(T_queue*) malloc(sizeof(T_queue));

  (*tree)->lr_point=NULL;
  (*tree)->rl_point=NULL;
  (*tree)->lh_point=NULL;
  (*tree)->hl_point=NULL;
}

int compare_array(int **array1, int **array2, int size){
  int i, j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      if(array1[i][j]!=array2[i][j]) return -1;
    }
  }
  return 1;//if equal
}

int search(int **array, int size){
  T_queue *aux=first;
  while (aux!=NULL) {
    if(compare_array(aux->type_tree->mat, array, size)==1) return 1;//if equal
    aux=aux->prox;
  }
  return 0;
}

void copy_array(int ***array1, int **array2, int size){
  int i, j;
  for (i=0;i < size;i++){
    for (j = 0; j < size; j++)
      (*array1)[i][j]=array2[i][j];
  }
}

void find_out_zero(int **root, int *i, int *j, int size){
  for((*i)=0;(*i)<size;(*i)++){
    for((*j)=0;(*j)<size;(*j)++){
      if(root[(*i)][(*j)]==0)
        goto A;
    }
    //if(last->type_tree->mat[(*i)][(*j)]==0)
      //break;
  }
  A:
  printf(" ");
}

void swap (int *a, int *b){
  int aux;
  aux=*a;
  *a=*b;
  *b=aux;
}

void move_up(T_tree **aux, int size, int i, int j){
  int k, l;
  T_tree *aux1=(T_tree*) malloc(sizeof(T_tree));
  start(&aux1);
  aux1->mat=(int**) malloc(size*sizeof(int*));
  for(k=0; k<size;k++)
    aux1->mat[k]=(int*) malloc(size*sizeof(int));

  copy_array(&(aux1->mat),((*aux)->mat), size);

  strcpy((aux1)->text,"up");
  swap(&(aux1->mat[i][j]),&((aux1)->mat[(i+1)][j]));
  (*aux)->lh_point=aux1;
}

void move_down(T_tree **aux, int size, int i, int j){
  int k;
  T_tree *aux1=(T_tree*) malloc(sizeof(T_tree));
  start(&aux1);
  aux1->mat=(int**) malloc(size*sizeof(int*));
  for(k=0;k<size;k++)
    aux1->mat[k]=(int*) malloc(size*sizeof(int));
  copy_array(&(aux1->mat),((*aux)->mat), size);
  strcpy(aux1->text,"down");
  swap(&((aux1->mat)[(i-1)][j]),&(aux1->mat[i][j]));
  (*aux)->hl_point=aux1;
}

void move_right(T_tree **aux, int size, int i, int j){
  int k;
  T_tree *aux1=(T_tree*) malloc(sizeof(T_tree));
  start(&aux1);
  aux1->mat=(int**) malloc(size*sizeof(int*));
  for(k=0; k<size;k++)
    aux1->mat[k]=(int*) malloc(size*sizeof(int));

  copy_array(&(aux1->mat),((*aux)->mat), size);

  strcpy((aux1->text), "right");
  swap(&(aux1->mat[i][(j-1)]),&(aux1->mat[i][j]));
  (*aux)->lr_point=(aux1);
}

void move_left(T_tree **aux, int size, int i, int j){
  int k;
  T_tree *aux1=(T_tree*) malloc(sizeof(T_tree));
  start(&aux1);
  aux1->mat=(int**) malloc(size*sizeof(int*));
  for(k=0; k<size;k++)
    aux1->mat[k]=(int*) malloc(size*sizeof(int));

  copy_array(&(aux1->mat),((*aux)->mat), size);

  strcpy((aux1->text),"left");
  swap(&(aux1->mat[i][j]),&(aux1->mat[i][(j+1)]));
  (*aux)->rl_point=(aux1);
}

int calculation_distance_Manhattan(int **array, int **array_resul, int size){
  int i,j, k, l, h=0;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      if(array[i][j]!=0){
        for(k=0;k<size;k++){
          for(l=0;l<size;l++){

            if(array[i][j]==array_resul[k][l])
              goto p;
            }
          }
p:
          h+=(MODULO((i-k))+MODULO((j-l)));
        }
    }
  }
  return h;
}

void fill_tree(T_tree *root, int **array_resul, int size, int i, int j){ //i and j are posiction where zero's
  int k, l;
  stack *h=NULL;
  iter++;

  if(compare_array(root->mat,array_resul, size)==-1){//if result isn't root

    if(j+1<size){ // move to left
      move_left(&root, size, i, j);
      push(&h, calculation_distance_Manhattan((root->rl_point->mat), array_resul,size), root->rl_point);
      //printf("left %d\n",calculation_distance_Manhattan((root->rl_point->mat), array_resul,size));
    }
    if((j-1)>=0){ // move to right
      move_right(&root, size, i, j);
      push(&h, calculation_distance_Manhattan((root->lr_point->mat), array_resul,size), root->lr_point);
      //printf("right: %d\n",calculation_distance_Manhattan((root->lr_point->mat), array_resul,size));
    }
    if((i+1)<size){ //move up
      move_up(&root, size, i, j);
      push(&h, calculation_distance_Manhattan((root->lh_point->mat), array_resul,size), root->lh_point);
      //printf("up: %d\n", calculation_distance_Manhattan((root->lh_point->mat), array_resul,size));
    }
    if((i-1)>=0){ //move down
      move_down(&root, size, i, j);
      push(&h, calculation_distance_Manhattan((root->hl_point->mat), array_resul,size), root->hl_point);
      //printf("down: %d\n", calculation_distance_Manhattan((root->hl_point->mat), array_resul,size));
    }
    // faz todos os movimentos inserindo a prioridade do proximo movitento em uma pilha
    insert_queue(root, h); //insere o moviento em uma fila a raiz, que sempre será o movimeto feito
    while(search(last->type_stack->type_tree->mat, size)==1){ //verifica se não há nenhum moviento anteriormente igual a esse já feito
      pop(&(last->type_stack));
      //remove_queue();
      //printf("\n\n\nENTROUUUU\n\n\n");
      if(last->type_stack==NULL){
        remove_queue();
        pop(&(last->type_stack));
        root=last->type_tree;
        find_out_zero(last->type_tree->mat, &i, &j, size);
        break;
      }
    }
    if(last->type_stack->type_tree==root->rl_point){
        j++;
        //printf("\nGo to left\n");
        fill_tree(root->rl_point, array_resul, size, i, j);
      }
      else if(last->type_stack->type_tree==root->lr_point){
        j--;
        //printf("\nGo to right\n");
        fill_tree(root->lr_point, array_resul, size, i, j);
      }
      else if(last->type_stack->type_tree==root->lh_point){
        i++;
        //printf("\nGo to up\n");
        fill_tree(root->lh_point, array_resul, size, i, j);
      }
      else if(last->type_stack->type_tree==root->hl_point){
        i--;
        //printf("\nGo to down\n");
        fill_tree(root->hl_point, array_resul, size, i, j);
      }
  }
  else{//if is result
    printf("MOVIMENTS\n");
    print_queue();
    int p,m;
    printf("\n\nRESULT FOUND:\n");
    for (p=0;p < size;p++){
        printf("\n");
        for (m = 0;  m< size; m++)
          printf("%d\t", root->mat[p][m]);
    }
    printf("\n\n\n");
  }
}

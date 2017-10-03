#include<stdio.h>
#include<stdlib.h>
#include "functions.h"
#include <time.h>

int *randon(int size, int *root){
  srand((unsigned)time(NULL));

  int i=-1,value, j=-1;
  while (i<(size*size-1)) {
    value=(rand()%(size*size));
    for(j=0;j<=i;j++){
      if(value==root[j]){
        j=-1;
        break;
      }
    }
    if(j!=-1){
      root[++i]=value;
    }
  }
  return root;
}

int ammount_motion(int **array, int size) {
  int i, j, k, l, cont=0;
  for(i=0; i<size; i++){
    for(j=0;j<size; j++){
      if(array[i][j]!=0){
        l=j;
        for(k=i; k<size; k++){
          for(l;l<size; l++){
            if(array[k][l]!=0 && array[i][j]>array[k][l]){
              cont++;
            }
          }
          l=0;
        }
      }

    }
  }
  return cont;
}

void inicial_state_and_Goal(int *(**goal_array), int *(**initial_array), int **vector_aux, int size, int *i, int *j){

  (*vector_aux)=randon(size, (*vector_aux));
  for((*i)=0;(*i)<size;(*i)++){
    for ((*j)=0;(*j)<size;(*j)++){
      (*initial_array)[*i][*j]=(**vector_aux);
      (*vector_aux)++;
    }
  }
  find_out_zero((*initial_array), i, j, size);
  if(size%2==0){
    if(((ammount_motion((*initial_array), size)+(*i)+1)%2)!=0){
      int b;
      for(b=0;b<1000000;b++);
      inicial_state_and_Goal(goal_array, initial_array, vector_aux, size, i, j);
    }
    else{
      int m, n, val=1;
      for(m=0;m<size;m++){
        for(n=0;n<size;n++){
          if(m==(size-1) & n==(size-1)) {
            (*goal_array)[m][n]=0;
            break;
          }
          (*goal_array)[m][n]=val;
          val++;
        }
      }
    }
  }
  else{
    if(ammount_motion((*initial_array), size)%2==0){
      int m, n, val=1;
        for(m=0;m<size;m++){
          for(n=0;n<size;n++){
            if(m==(size-1) & n==(size-1)) {
              (*goal_array)[m][n]=0;
              break;
            }
            (*goal_array)[m][n]=val;
            val++;
          }
        }
    }
    else if(size==3){
        (*goal_array)[0][0]=1;
        (*goal_array)[0][1]=2;
        (*goal_array)[0][2]=3;
        (*goal_array)[1][0]=8;
        (*goal_array)[1][1]=0;
        (*goal_array)[1][2]=4;
        (*goal_array)[2][0]=7;
        (*goal_array)[2][1]=6;
        (*goal_array)[2][2]=5;
      }
    else{
      int b;
      for(b=0;b<1000000;b++);
      inicial_state_and_Goal(goal_array, initial_array, vector_aux, size, i, j);
    }
  }
}

int main(){

  T_tree root;
  int size, i, j;
  int **goal_array;
  printf("type the size matrix: ");
  scanf("%d", &size);

  root.lh_point=NULL;
  root.hl_point=NULL;
  root.rl_point=NULL;
  root.lr_point=NULL;

  goal_array=(int**) malloc(size*sizeof(int*));
  root.mat=(int**) malloc(size*sizeof(int*));
  for(i=0; i<size;i++){
    root.mat[i]=(int*) malloc(size*sizeof(int));
    goal_array[i]=(int*) malloc(size*sizeof(int));
  }

 int *aux=(int*) malloc((size*size)*sizeof(int));
 inicial_state_and_Goal(&goal_array, &root.mat, &aux, size, &i, &j);

  strcpy(root.text,"begin");
  fill_tree(&root, goal_array, size, i, j);

  printf("\nINITIAL MATRIX:\n\n");
  for (i=0;i < size;i++){
      printf("\n");
      for (j = 0; j < size; j++) {
        printf("%d\t", root.mat[i][j]);
      }
  }
  printf("\n\n\n");
  printf("Quantidade de Movimetos: %d\n", cont);
  //printf("iter %d\n\n", iter);

return 0;
}

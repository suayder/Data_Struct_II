#ifndef N_PUZZLE
#define n_PUZZLE

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

void insert_queue(T_tree *T, stack *h);

void remove_queue();

void print_queue();

void push(stack **h, int value, T_tree *tree);

void pop(stack **h);

void start(T_tree **tree);

int compare_array(int **array1, int **array2, int size);

int search(int **array, int size);

void copy_array(int ***array1, int **array2, int size);

void find_out_zero(int **root, int *i, int *j, int size);

void swap (int *a, int *b);

void move_up(T_tree **aux, int size, int i, int j);

void move_down(T_tree **aux, int size, int i, int j);

void move_right(T_tree **aux, int size, int i, int j);

void move_left(T_tree **aux, int size, int i, int j);

int calculation_distance_Manhattan(int **array, int **array_resul, int size);

void fill_tree(T_tree *root, int **array_resul, int size, int i, int j);

#endif

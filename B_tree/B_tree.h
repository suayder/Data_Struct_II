#ifndef B_TREE
#define B_TREE

typedef struct No{
	int key[MAX+1], count;
	struct No *pointer[MAX+1];
}T_tree;

T_tree *createNo(int key, T_tree *search, T_tree *filho);

void addkeyToNo(int key, int pos, T_tree *No,T_tree *filho);

void spliT_treede (int key, int *pval, int pos, T_tree *no,T_tree *filho, T_tree **newNo);

int setValueInNode(int key, int *pval,T_tree *root, T_tree **filho);

void insert(T_tree **root, int key);

void copySuccessor(T_tree *root, int pos);

void removeKey(T_tree *root, int pos);

void doRightShift(T_tree *root, int pos);

void doLeftShift(T_tree *root, int pos);

void mergeNodes(T_tree *root, int pos);

void adjusT_treede(T_tree *root, int pos);

int delKeyFromNo(int key, T_tree *root);

void deletion(int key,T_tree **search);

void search(int info, int *pos, T_tree *root);

void traversal(T_tree *root);

#endif

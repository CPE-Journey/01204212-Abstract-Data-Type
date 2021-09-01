#include <stdio.h>
#include <stdlib.h>
#include "week8.h"

#ifndef __bin_tree__
typedef struct node {
  int    data;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t tree_t;
#endif

// Write your code here
// ** Note that the attach() function has
// been implemented already and included
// in the week8.h header
// ...

void print_preorderRec(tree_t *t){
  if(t==NULL){return;}
  printf("%d ",t->data);
  print_preorderRec(t->left);
  print_preorderRec(t->right);
}

void print_preorder(tree_t *t){
  print_preorderRec(t);
  printf("\n");
}

void print_postorderRec(tree_t *t){
  if(t==NULL){return;}
  print_postorderRec(t->left);
  print_postorderRec(t->right);
  printf("%d ",t->data);
}

void print_postorder(tree_t *t){
  print_postorderRec(t);
  printf("\n");
}

void print_inorderRec(tree_t *t){
  if(t==NULL){return;}
  print_inorderRec(t->left);
  printf("%d ",t->data);
  print_inorderRec(t->right);
}

void print_inorder(tree_t *t){
  print_inorderRec(t);
  printf("\n");
}

int main(void) {
  tree_t *t = NULL;
  int n, i;
  int parent, child;
  int branch; // 0 root, 1 left, 2 right

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d %d %d", &parent, &child, &branch);
    t = attach(t, parent, child, branch);
  }

  print_preorder(t);
  print_postorder(t);
  print_inorder(t);

  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <week8.h>

#ifndef __bin_tree__
typedef struct node {
  int    data;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t tree_t;
#endif


typedef struct q_node {
  tree_t *data;
  struct q_node *next;
} Queue;

Queue *enqueue(Queue *q,tree_t *value){
    Queue *tmp = q;
    Queue *node = malloc(sizeof(Queue));
    node->data = value;
    node->next = NULL;
    
    if(q == NULL){
        return node;
    }
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = node;
    return q;
}

tree_t *dequeue(Queue **q){
    tree_t *rtn = (**q).data;
    *q = (**q).next;
    return rtn;
}

int isQEmpty(Queue *q){
    if(q==NULL){
        return 1;
    }
    return 0;
}



int is_full(tree_t *t){
  if(t->left != NULL && t->right != NULL){
    if(is_full(t->left)){
      return is_full(t->right);
    }
  }
  else if(t->left == NULL && t->right == NULL){
    return 1;
  }
  return 0;
}

int depth(tree_t *t){
  int d = 0;
  while(t->left != NULL){
    d++;
    t = t->left;
  }
  return d;
}

int is_perfectRec(tree_t *t,int depth,int current_depth){
  if(t->left != NULL && t->right != NULL){
    if(is_perfectRec(t->left,depth,current_depth+1)){
      return is_perfectRec(t->right,depth,current_depth+1);
    }
  }
  else if(t->left == NULL && t->right == NULL && depth==current_depth){
    return 1;
  }
  return 0;
}

int is_perfect(tree_t *t){
  return is_perfectRec(t,depth(t),0);
}

int is_complete(tree_t *t){
  Queue *q = NULL;
  q = enqueue(q,t);
  int no_more = 0;
  while(!isQEmpty(q)){
    int not_left = 1;
    tree_t *t = dequeue(&q);
    if(t->left != NULL){
      if(no_more){
        return 0;
      }
      not_left = 0;
      q = enqueue(q,t->left);
    }
    if(t->right != NULL){
      if(not_left){return 0;}
      q = enqueue(q,t->right);
    }
    else{no_more = 1;}
  }
  return 1;
}

int is_degenerate(tree_t *t){
  if(t==NULL || (t->left == NULL && t->right == NULL)){
    return 1;
  }
  if(t->left != NULL && t->right == NULL){
    return is_degenerate(t->left);
  }
  else if(t->left == NULL && t->right != NULL){
    return is_degenerate(t->right);
  }
  return 0;
}

int is_skewedRec(tree_t *t,int dir){ // 0 = Left | 1 = Right
  if(t->left == NULL || t->right == NULL){
    if((dir && t->left != NULL) || (!dir && t->right != NULL)){
      return 0;
    }
    return 1;
  }
  if(dir){
    return is_skewedRec(t->right,dir);
  }
  return is_skewedRec(t->left,dir);

}

int is_skewed(tree_t *t){
  if(t->left != NULL){
    while(t!=NULL){
      if(t->right != NULL){return 0;}
      t = t->left;
    }
  }
  else{
    while(t!=NULL){
      if(t->left != NULL){return 0;}
      t = t->right;
    }
  }
  return 1;
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
  printf("%d %d %d %d %d\n", is_full(t), is_perfect(t), is_complete(t), is_degenerate(t), is_skewed(t));
  // printf("%d %d %d %d %d\n", is_full(t), is_perfect(t), is_complete(t), is_degenerate(t), is_skewed(t));

  return 0;
}

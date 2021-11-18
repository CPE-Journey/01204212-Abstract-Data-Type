#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int    data;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t bst_t;

// Write your code here
// ...

bst_t *createNode(int value){
    bst_t *node = malloc(sizeof(bst_t));
    node->data = value;
    node->right = NULL;
    node->left = NULL;
}

bst_t *insert(bst_t *t,int value){
    if(t==NULL){
        return createNode(value);
    }
    else if(t->data > value){
        t->left = insert(t->left,value);
    }
    else{
        t->right = insert(t->right,value);
    }
    return t;
}

bst_t *delete(bst_t *t,int value){
    if(t==NULL){
        return t;
    }
    else if(t->data > value){
        t->left = delete(t->left,value);
    }
    else if(t->data < value){
        t->right = delete(t->right,value);
    }
    else{
        // 2 Children
        if(t->left != NULL && t->right != NULL){
            int new_head = find_min(t->right);
            t->data = new_head;
            t->right = delete(t->right,new_head);
            return t;
        }
        // 0-1 Child
        else{
            bst_t *child = NULL;
            if(t->left != NULL){
                child = t->left;
            }
            else if(t->right != NULL){
                child = t->right;
            }
            return child;
        }
    }
    return t;
}

int find(bst_t *t,int value){
    if(t==NULL){
        return 0;
    }
    else if(t->data == value){
        return 1;
    }
    return find(t->left,value) || find(t->right,value) ? 1:0;
}

int find_min(bst_t *t){
    bst_t *tmp = t;
    while(tmp->left != NULL){
        tmp = tmp->left;
    }
    return tmp->data;
}

int find_max(bst_t *t){
    bst_t *tmp = t;
    while(tmp->right != NULL){
        tmp = tmp->right;
    }
    return tmp->data;
}

int main(void) {
  bst_t *t = NULL;
  int   n, i;
  int   command, data;

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch (command) {
      case 1:
        scanf("%d", &data);
        t = insert(t, data);
        break;
      case 2:
        scanf("%d", &data);
        t = delete(t, data);
        break;
      case 3:
        scanf("%d", &data);
        printf("%d\n", find(t, data));
        break;
      case 4:
        printf("%d\n", find_min(t));
        break;
      case 5:
        printf("%d\n", find_max(t));
        break;
    }
  }
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "week9.h"

#ifndef __avl_tree__
typedef struct node {
  int    data;
  int    height;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t avl_t;
#endif

// Write your code here
// ** Note that the print_tree() function
// has been implemented already and
// included in the week9.h header
// ...

avl_t *createNode(int value){
    avl_t *node = malloc(sizeof(avl_t));
    node->data = value;
    node->height = 1;
    node->right = NULL;
    node->left = NULL;
    return node;
}

int find_min(avl_t *t){
    avl_t *tmp = t;
    while(tmp->left != NULL){
        tmp = tmp->left;
    }
    return tmp->data;
}

int balance(avl_t *t){
  if(t==NULL){
    return 0;
  }
  return getHeight(t->left) - getHeight(t->right);
}

avl_t* leftRotation(avl_t* t){
    avl_t *rotate = t;
    avl_t *rhs = t->right;

    rotate->right = rhs->left;
    rhs->left = rotate;

    updateHeight(rotate);
    updateHeight(rhs);
    return rhs;
}
avl_t* rightRotation(avl_t* t){
    avl_t *rotate = t;
    avl_t *lhs = t->left;

    rotate->left = lhs->right;
    lhs->right = rotate;

    updateHeight(rotate);
    updateHeight(lhs);
    return lhs;
}

avl_t *leftRightRotation(avl_t *t){
  t->left = leftRotation(t->left);
  return rightRotation(t);
}

avl_t *rightLeftRotation(avl_t *t){
  t->right = rightRotation(t->right);
  return leftRotation(t);
}

int getHeight(avl_t *t){
  if(t==NULL){
    return 0;
  }
  return t->height;
}

void updateHeight(avl_t *t){
  int lh = getHeight(t->left), rh = getHeight(t->right);
  if(lh > rh){
    t->height = lh + 1;
  }
  else{
    t->height = rh + 1;
  }
}

avl_t *insert(avl_t *t,int value){
    if(t==NULL){
        return createNode(value);
    }
    else if(t->data > value){
        t->left = insert(t->left,value);
    }
    else{
        t->right = insert(t->right,value);
    }

    updateHeight(t);

    int bal = balance(t);
    
    if(bal > 1 && value < t->left->data){
    return rightRotation(t);
    }
    else if(bal < -1 && value > t->right->data){
      return leftRotation(t);
    }
    else if(bal > 1 && value > t->left->data){
      return leftRightRotation(t);
    }
    else if(bal < -1 && value < t->right->data){
      return rightLeftRotation(t);
    }
    return t;
}

avl_t *delete(avl_t *t,int value){
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
            avl_t *child = NULL;
            if(t->left != NULL){
                child = t->left;
            }
            else if(t->right != NULL){
                child = t->right;
            }
            return child;
        }
    }

    if(t==NULL){return t;}

    updateHeight(t);

    int bal = balance(t);
    if(bal > 1 && balance(t->left) >= 0){
    return rightRotation(t);
    }
    else if(bal < -1 && balance(t->right) <= 0){
      return leftRotation(t);
    }
    else if(bal > 1 && balance(t->left) < 0){
      return leftRightRotation(t);
    }
    else if(bal < -1 && balance(t->left) > 0){
      return rightLeftRotation(t);
    }
    return t;
}

void BFS(avl_t *t,int depth){
    if(t==NULL){return;}
    for(int i=0;i<depth;i++){
        printf("    ");
    }
    printf("%d(%d)\n",t->data,t->height);
    BFS(t->left,depth+1);
    BFS(t->right,depth+1);
}

int main(void) {
  avl_t *t = NULL;
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
        print_tree(t);
        break;
    }
  }
  return 0;
}
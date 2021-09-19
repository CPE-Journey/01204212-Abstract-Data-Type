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

int max(int a, int b)
{
    return (a > b)? a : b;
}

avl_t* newNode(int x){
    avl_t* node = (avl_t*)malloc(sizeof(avl_t));
    node->data = x;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}
int height(avl_t* node){
    if (node == NULL) return -1;
    return node->height;
}
avl_t* leftRotate(avl_t* l){
    avl_t*r = l->right;
    avl_t* t2 = r->left;
    r->left = l;
    l->right = t2;
    l->height = max(height(l->left),height(l->right))+1;
    r->height = max(height(r->left),height(r->right))+1;
    return r;
}
avl_t* rightRotate(avl_t* r){
    avl_t*l = r->left;
    avl_t* t2 = l->right;
    l->right = r;
    r->left = t2;
    r->height = max(height(r->left),height(r->right))+1;
    l->height = max(height(l->left),height(l->right))+1;
    return l;
}

int getBalance(avl_t* node){
    if(node == NULL) return 0;
    return height(node->left) - height(node->right);
}

avl_t *minValueNode(avl_t *node)
{
    avl_t *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

avl_t* insert(avl_t* node,int x){
    if(node == NULL) 
        return newNode(x);
    if (x < node->data)
        node->left = insert(node->left,x);
    else if (x > node->data)
        node->right = insert(node->right,x);
    else   
        return node; // equal x (not necsessary)
    // we will rebalance
    node->height = 1 + max(height(node->left),height(node->right));

    int balance = getBalance(node);
    // printf("Balance Insert: %d\n",balance);
    // balance == 1 is balance 

    
    if (balance > 1 && x < (node->left->data)) // left-left
        return rightRotate(node);
    if (balance < -1 && x > (node->right->data)) // right-right
        return leftRotate(node);
    if (balance > 1 && x > (node->left->data)){ // left-right
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && x < (node->right->data)){ // right-left
        node->right = rightRotate(node->right);
        return leftRotate(node);   
    }
    return node;
}

avl_t* delete(avl_t* node,int x){
    if(node == NULL) 
        return node;
    if (x < node->data)
        node->left = delete(node->left,x);
    else if (x > node->data)
        node->right = delete(node->right,x);
    else{
        if(node->left==NULL || node->right==NULL){
            avl_t* temp = node->left ? node->left : node->right;
            if(temp == NULL){
                temp = node;
                node = NULL;
            }
            else{
                *node = *temp;
            }
            free(temp);
        }
        else{
            avl_t* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = delete(node->right,temp->data);
        }
    }

    if(node == NULL) 
        return node;
    // we will rebalance
    node->height = 1 + max(height(node->left),height(node->right));

    int balance = getBalance(node);
    // printf("Balance Delete: %d\n",balance);
    // balance == 1 is balance 

    
    if (balance > 1 && getBalance(node->left) >= 0) // left-left
        return rightRotate(node);
    if (balance < -1 && getBalance(node->right) <= 0) // right-right
        return leftRotate(node);
    if (balance > 1 && getBalance(node->left) < 0){ // left-right
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) > 0){ // right-left
        node->right = rightRotate(node->right);
        return leftRotate(node);   
    }
    return node;
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
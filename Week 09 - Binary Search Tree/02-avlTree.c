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

avl_t *rightRoataion(avl_t *t){
  avl_t *rotation = t->left;
  avl_t *rhs = t;
  rhs->left = rotation->right;
  rotation->right = rhs;

  updateHeight(rhs);
  updateHeight(rotation);

  return rotation;
}

avl_t *leftRoataion(avl_t *t){
  avl_t *rotation = t->right;
  avl_t *lhs = t;
  lhs->right = rotation->left;
  rotation->left = lhs;

  updateHeight(lhs);
  updateHeight(rotation);

  return rotation;
}

avl_t *leftRightRotation(avl_t *t){
  t->left = leftRoataion(t->left);
  return rightRoataion(t);
}

avl_t *rightLeftRotation(avl_t *t){
  t->right = rightRoataion(t->right);
  return leftRoataion(t);
}

int getHeight(avl_t *t){
  if(t==NULL) return 0;
  return t->height;
}

void updateHeight(avl_t *t){
  int lh = -1,rh = -1;
  if(t->left != NULL){lh = t->left->height;}
  if(t->right != NULL){rh = t->right->height;}
  if(t->left == NULL && t->right == NULL){
    t->height = 0;
  }
  else if(lh>rh){
    t->height = lh+1;
  }
  else{
    t->height = rh+1;
  }
}

avl_t *createNode(int value){
  avl_t *node = malloc(sizeof(avl_t));
  node->data = value;
  node->height = 0;
  node->left = NULL;
  node->right = NULL;
  return node;
}

avl_t *insert(avl_t *t,int value){
  //INSERT RECURSION
  if(t==NULL){
    return createNode(value);
  }
  else if(t->data > value){
    t->left = insert(t->left,value);
  }
  else if(t->data < value){
    t->right = insert(t->right,value);
  }
  else{
    return t;
  }
  
  // UPDATE HEIGHT
  updateHeight(t);
  
  // TREE ROTATION
  int lh = -1,rh = -1;
  if(t->left != NULL){lh = t->left->height;}
  if(t->right != NULL){rh = t->right->height;}
  printf("%d %d\n",lh,rh);

  if(lh-rh > 1 && value < t->left->data){
    printf("Doing 1 at %d",t->data);
    return rightRoataion(t);
  }
  else if(rh-lh > 1 && value > t->right->data){
    printf("Doing 1 at %d",t->data);
    return leftRoataion(t);
  }
  else if(lh-rh > 1 && value > t->left->data){
    printf("Doing 2 at %d",t->data);
    return leftRightRotation(t);
  }
  else if(rh-lh > 1 && value < t->right->data){
    printf("Doing 3 at %d",t->data);
    return rightLeftRotation(t);
  }
  return t;
}

int find_min(avl_t *t){
  avl_t *tmp = t;
  while(tmp->left != NULL){
    tmp = tmp->left;
  }
  return tmp->data;
}

void deleteNode(avl_t *select,int value,avl_t *parent){
  if(select==NULL){
    return;
  }
  else if(select->data == value){
    // printf("Delete at %d %d\n",select->data,parent->data);
    // printf("Par = %d Current = %d\n",parent->data,select->data);
    
    // Delete at Leaf Node
    if(select->left == NULL && select->right == NULL){
      if(parent->left != NULL && parent->left->data == value){
        parent->left = NULL;
      }
      else{
        parent->right = NULL;
      }
    }

    // Delete 2 Chilldren Node
    else if(select->left != NULL && select->right != NULL){
      select->data = find_min(select->right);
      avl_t *rhs = select->right,*prev = select;
      while(rhs->left != NULL){
        prev = rhs;
        rhs = rhs->left;
      }
      if(rhs->right == NULL){
        if(prev->left == rhs){
          prev->left = NULL;
        }
        else{
          prev->right = NULL;
        }
      }
      else{
        rhs->data = rhs->right->data;
        rhs->right = NULL;
      }
    }

    // Delete 1 Child Node
    else{
      if(parent == NULL){
        if(select->left != NULL){
          return select->left;
        }
        return select->right;
      }
      else if(parent->left != NULL && parent->left->data == value){
        if(select->left != NULL){
          parent->left = parent->left->left;
        }
        else{
          parent->left = parent->left->right;
        }
      }
      else if(parent->right != NULL && parent->right->data == value){
        if(select->left != NULL){
          parent->right = parent->right->left;
        }
        else{
          parent->right = parent->right->right;
        }
      }
    }
    if(parent!=NULL && parent->right == NULL && parent->left==NULL){
      parent->height -= 1;
    }
    
    return select;
  }
  else if(select->data > value){
    /* select->left = */ deleteNode(select->left,value,select);
  }
  else{
    /* select->right = */ deleteNode(select->right,value,select);
  }
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
  
  // UPDATE HEIGHT
  updateHeight(t);
  
  // TREE ROTATION
  int lh = -1,rh = -1;
  if(t->left != NULL){lh = t->left->height;}else{lh = -1;}
  if(t->right != NULL){rh = t->right->height;}else{rh = -1;}
  printf("%d %d\n",lh,rh);
  if(lh-rh > 1 && value < t->left->data){
    printf("Doing 1 at %d",t->data);
    return rightRoataion(t);
  }
  else if(rh-lh > 1 && value > t->right->data){
    printf("Doing 1 at %d",t->data);
    return leftRoataion(t);
  }
  else if(lh-rh > 1 && value > t->left->data){
    printf("Doing 2 at %d",t->data);
    return leftRightRotation(t);
  }
  else if(rh-lh > 1 && value < t->right->data){
    printf("Doing 3 at %d",t->data);
    return rightLeftRotation(t);
  }
  return t;
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
        BFS(t,0);
        print_tree(t);
        break;
    }
  }
  return 0;
}
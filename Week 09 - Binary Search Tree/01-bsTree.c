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

bst_t *search(bst_t *t,int num){
    if(t==NULL || t->data == num){
        return t;
    }
    else if(t->data > num){
        return search(t->left,num);
    }
    return search(t->right,num);
}

void insertParent(bst_t *t,int num,bst_t **parent,int *is_left){
    if(t==NULL){
        return;
    }
    if(t->data > num){
        if(t->left == NULL){
            *parent = t;
            *is_left = 1;
            return;
        }
        insertParent(t->left,num,parent,is_left);
    }
    else{
        if(t->right == NULL){
            *parent = t;
            *is_left = 0;
            return;
        }
        insertParent(t->right,num,parent,is_left);
    }
}

void findParent(bst_t *t,int num,bst_t *par,bst_t **rtn){
  if(t == NULL || *rtn != NULL){
    return;
  }
  else if((t->left != NULL && t->left->data == num) || (t->right != NULL && t->right->data == num)){
    *rtn = t;
    return;
  }
  findParent(t->left,num,NULL,rtn);
  findParent(t->right,num,NULL,rtn);
}

bst_t *insert(bst_t *t,int num){
    bst_t *node = malloc(sizeof(bst_t));
    node->data = num;
    node->right = NULL;
    node->left = NULL;
    
    if(t==NULL){
        return node;
    }

    int is_left;
    bst_t *select = NULL;
    insertParent(t,num,&select,&is_left);
    if(is_left){
        select->left = node;
    }
    else{
        select->right = node;
    }
    return t;
}

bst_t *delete(bst_t *t,int num){
  bst_t *select = search(t,num);
  bst_t *parent = NULL;
  if(t->data != num){
    findParent(t,num,NULL,&parent);
  }

  // Only Root Left
  if(t->data == num && t->left == NULL && t->right == NULL){
    return NULL;
  }

  // Delete at Leaf Node
  else if(select->left == NULL && select->right == NULL){
    if(parent->left != NULL && parent->left->data == num){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
  }

  // Delete 2 Chilldren Node
  else if(select->left != NULL && select->right != NULL){
      select->data = find_min(select->right);
      bst_t *rhs = select->right,*prev = select;
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
    else if(parent->left != NULL && parent->left->data == num){
      if(select->left != NULL){
        parent->left = parent->left->left;
      }
      else{
        parent->left = parent->left->right;
      }
    }
    else if(parent->right != NULL && parent->right->data == num){
      if(select->left != NULL){
        parent->right = parent->right->left;
      }
      else{
        parent->right = parent->right->right;
      }
    }
  }
  
  return t;
}

int find(bst_t *t,int num){
    if(t==NULL){
        return 0;
    }
    if(t->data == num){
        return 1;
    }
    else if(t->data > num){
        return find(t->left,num);
    }
    return find(t->right,num);
}

void find_minRec(bst_t *t,int *min){
  if(t==NULL){
    return;
  }
  if(t->data < *min){
    *min = t->data;
  }
  find_minRec(t->left,min);
  find_minRec(t->right,min);
}

int find_min(bst_t *t){
  int min = t->data;
  find_minRec(t,&min);
  return min;
}

void find_maxRec(bst_t *t,int *max){
  if(t==NULL){
    return;
  }
  if(t->data > *max){
    *max = t->data;
  }
  find_maxRec(t->left,max);
  find_maxRec(t->right,max);
}

int find_max(bst_t *t){
  int max = t->data;
  find_maxRec(t,&max);
  return max;
}

void BFS(bst_t *t,int depth){
    if(t==NULL){return;}
    for(int i=0;i<depth;i++){
        printf("    ");
    }
    printf("%d\n",t->data);
    BFS(t->left,depth+1);
    BFS(t->right,depth+1);
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
      case 6:
        BFS(t,0);
        break;
    }
  }
  return 0;
}
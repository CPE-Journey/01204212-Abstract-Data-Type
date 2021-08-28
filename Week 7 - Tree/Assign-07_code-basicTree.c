#include <stdio.h>
#include <stdlib.h>

// TREE ADT

typedef struct node{
  int data;
  struct node* f_child;
  struct node* nxt_sib;
}tree_t;

// STACK ADT

typedef struct stack {
  int data;
  struct stack *next;
}Stack;

Stack *push(Stack *s,char value){
  Stack *node = malloc(sizeof(Stack));
  node->data = value;
  node->next = NULL;

  if(s != NULL){
      node->next = s;
  }
  return node;
}

int pop(Stack **s){
  if(*s==NULL){
    return 'X';
  }
  int rtrn = (**s).data;
  *s = (**s).next;
  return rtrn;
}

int isSEmpty(Stack *s){
    if(s==NULL){
        return 1;
    }
    return 0;
}

// QUEUE ADT

typedef struct q_node {
  tree_t *data;
  struct q_node *next;
} Queue;

Queue *enqueue(Queue *q,int value){
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
    if(q==NULL){
        return -1;
    }
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



// CUSTOM TOOL

tree_t *quickSearch(tree_t *t,int value){
  if(t == NULL || t->data == value){
    return t;
  }
  tree_t *pos = quickSearch(t->f_child,value);
  if(pos!=NULL){
    return pos;
  }
  return quickSearch(t->nxt_sib,value);
}

void *findParent(tree_t *t,int value,tree_t *parent,tree_t **rtn){
  if(t == NULL){
    return;
  }
  tree_t *child = t;
  if(child==NULL){return;}
  while(child->nxt_sib!=NULL){
    if(child->data==value){
      *rtn = parent;
      return;
    }
    child = child->nxt_sib;
  }
  if(child->data==value){
      *rtn = parent;
      return;
  }
  findParent(t->f_child,value,t,rtn);
  findParent(t->nxt_sib,value,t,rtn);
}

// COMMAND

tree_t *attach(tree_t *t,int parent,int value){
  tree_t *new_child = malloc(sizeof(tree_t));
  new_child->data = value;
  new_child->f_child = NULL;
  new_child->nxt_sib = NULL;

  if(t==NULL){
    return new_child;
  }
  tree_t *select = quickSearch(t,parent);
  if(select->f_child == NULL){
    select->f_child = new_child;
  }
  else{
    select = select->f_child;
    while(select->nxt_sib != NULL){
      select = select->nxt_sib;
    }
    select->nxt_sib = new_child;
  }
  return t;
}

tree_t *detach(tree_t *t,int value){
  if(t->data == value){
    return NULL;
  }
  tree_t *select_parent = NULL;
  findParent(t,value,NULL,&select_parent);
  
  tree_t *child = select_parent->f_child;
  tree_t *prev = NULL;

  if(child->data==value){
    select_parent->f_child = select_parent->f_child->nxt_sib;
  }
  else{
    while(child->nxt_sib != NULL){
      if(child->data == value){
        prev->nxt_sib = prev->nxt_sib->nxt_sib;
      }
      prev = child;
      child = child->nxt_sib;
    }
    if(child->data == value){
        prev->nxt_sib = prev->nxt_sib->nxt_sib;
    }
  }
  return t;
}

int search(tree_t *t,int value){
  tree_t *select = quickSearch(t,value);
  if(select==NULL){
    return 0;
  }
  return 1;
}

int degree(tree_t *t,int value){
  tree_t *select = quickSearch(t,value);
  select = select->f_child;
  if(select==NULL){
    return 0;
  }
  int i = 1;
  while(select->nxt_sib != NULL){
    i++;
    select = select->nxt_sib;
  }
  return i;
}

int is_root(tree_t *t,int root){
  if(t->data==root){
    return 1;
  }
  return 0;
}

int is_leaf(tree_t *t,int leaf){
  tree_t *select = quickSearch(t,leaf);
  if(select->f_child==NULL){
    return 1;
  }
  return 0;
}

void siblings(tree_t *t,int child){
  if(t->data==child){
    printf("\n");
    return;
  }
  tree_t *parent = NULL;
  findParent(t,child,NULL,&parent);
  parent = parent->f_child;
  if(parent->nxt_sib==NULL){
    printf("\n");
    return;
  }
  while(parent->nxt_sib != NULL){
    if(parent->data != child){
      printf("%d ",parent->data);
    }
    parent = parent->nxt_sib;
  }
  if(parent->data != child){
      printf("%d",parent->data);
  }
  printf("\n");
}

void depthRec(tree_t *t,int value,int depth,int *rtn){
  if(t==NULL){
    return;
  }
  if(t->data == value){
    *rtn = depth;
    return;
  }
  else{
    depthRec(t->f_child,value,depth+1,rtn);
    depthRec(t->nxt_sib,value,depth,rtn);
  }
}

int depth(tree_t *t,int value){
  int x;
  depthRec(t,value,0,&x);
  return x;
}

void print_path(tree_t *t,int start,int end){
  Stack *s = NULL;
  tree_t *a = quickSearch(t,end);
  s = push(s,a->data);
  while(a->data != start){
    findParent(t,a->data,NULL,&a);
    s = push(s,a->data);
  }
  while(!isSEmpty(s)){
    int x = pop(&s);
    printf("%d ",x);
  }
  printf("\n");
}

int path_length(tree_t *t,int start,int end){
  Stack *s = NULL;
  tree_t *a = quickSearch(t,end);
  int l = 1;
  while(a->data != start){
    findParent(t,a->data,NULL,&a);
    l++;
  }
  return l;
}

void ancestor(tree_t *t,int value){
  print_path(t,t->data,value);
}

void descendant(tree_t *t,int value){
  tree_t *subtree = quickSearch(t,value);
  bfs(subtree);
}

void bfs(tree_t *t){
  Queue *q = NULL;
  tree_t *current = NULL;
  int x;
  q = enqueue(q,t);
  while(!isQEmpty(q)){
    current = dequeue(&q);
    printf("%d ",current->data);
    current = current->f_child;
    if(current == NULL){continue;}
    while(current->nxt_sib != NULL){
      q = enqueue(q,current);
      current = current->nxt_sib;
    }
    q = enqueue(q,current);
  }
  printf("\n");
}

void dfsRec(tree_t *t){
  if(t==NULL){
    return;
  }
  printf("%d ",t->data);
  dfsRec(t->f_child);
  dfsRec(t->nxt_sib);
}

void dfs(tree_t *t){
  dfsRec(t);
  printf("\n");
}

void print_treeRec(tree_t *t,int depth){
  if(t==NULL){
    return;
  }
  int i=0;
  for(i=0;i<depth;i++){
    printf("    ");
  }
  printf("%d\n",t->data);
  print_treeRec(t->f_child,depth+1);
  print_treeRec(t->nxt_sib,depth);
}

void print_tree(tree_t *t){
  print_treeRec(t,0);
}

int main(void) {
  tree_t *t = NULL;
  int n, i, command;
  int parent, child, node, start, end;

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch(command) {
      case 1:
        scanf("%d %d", &parent, &child);
        t = attach(t, parent, child);
        break;
      case 2:
        scanf("%d", &node);
        t = detach(t, node);
        break;
      case 3:
        scanf("%d", &node);
        printf("%d\n", search(t, node));
        break;
      case 4:
        scanf("%d", &node);
        printf("%d\n", degree(t, node));
        break;
      case 5:
        scanf("%d", &node);
        printf("%d\n", is_root(t, node));
        break;
      case 6:
        scanf("%d", &node);
        printf("%d\n", is_leaf(t, node));
        break;
      case 7:
        scanf("%d", &node);
        siblings(t, node);
        break;
      case 8:
        scanf("%d", &node);
        printf("%d\n", depth(t, node));
        break;
      case 9:
        scanf("%d %d", &start, &end);
        print_path(t, start, end);
        break;
      case 10:
        scanf("%d %d", &start, &end);
        printf("%d\n", path_length(t, start, end));
        break;
      case 11:
        scanf("%d", &node);
        ancestor(t, node);
        break;
      case 12:
        scanf("%d", &node);
        descendant(t, node);
        break;
      case 13:
        bfs(t);
        break;
      case 14:
        dfs(t);
        break;
      case 15:
        print_tree(t);
        break;
    }
  }
  return 0;
}
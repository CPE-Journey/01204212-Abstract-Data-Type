#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int          data;
  struct node *next;
} node_t;

typedef node_t stack_t;

stack_t *push(stack_t *s,int value){
  stack_t *node = malloc(sizeof(stack_t));
  node->data = value;
  node->next = NULL;

  if(s != NULL){
      node->next = s;
  }
  return node;
}

void top(stack_t *s){
  if(s == NULL){
    printf("Stack is empty.\n");
    return;
  }
  printf("%d\n",s->data);
}

stack_t *pop(stack_t *s){
  if(s==NULL){
    return NULL;
  }
  stack_t *go_next = s->next;
  free(s);
  return go_next;
}

void empty(stack_t *s){
  if(s==NULL){
    printf("Stack is empty.\n");
    return;
  }
  printf("Stack is not empty.\n");
}

void size(stack_t *s){
  int size = 1;
  if(s==NULL){
    printf("0\n");
    return;
  }
  while(s->next != NULL){
    size++;
    s = s->next;
  }
  printf("%d\n",size);
}

int main(void) {
  stack_t *s = NULL;
  int      n, i, command, value;

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch(command) {
      case 1:
        scanf("%d", &value);
        s = push(s, value);
        break;
      case 2:
        top(s);
        break;
      case 3:
        s = pop(s);
        break;
      case 4:
        empty(s);
        break;
      case 5:
        size(s);
        break;
      }
  }
  return 0;
}
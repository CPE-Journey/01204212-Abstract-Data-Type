#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int          data;
  struct node *next;
} node_t;

typedef node_t queue_t;

queue_t *enqueue(queue_t *q,int value){
    queue_t *tmp = q;
    queue_t *node = malloc(sizeof(queue_t));
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

queue_t *dequeue(queue_t *q){
    if(q==NULL){
        printf("Queue is empty.\n");
        return NULL;
    }
    printf("%d\n",q->data);
    return q->next;
}

void show(queue_t *q){
    if(q==NULL){
        printf("Queue is empty.\n");
        return;
    }
    while(q->next != NULL){
        printf("%d ",q->data);
        q = q->next;
    }
    printf("%d ",q->data);
    printf("\n");
}

void empty(queue_t *q){
    if(q==NULL){
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue is not empty.\n");
}

void size(queue_t *q){
    int size = 1;
    if(q==NULL){
        printf("0\n");
        return;
    }
    while(q->next != NULL){
        size++;
        q = q->next;
    }
    printf("%d\n",size);
}

int main(void) {
  queue_t *q = NULL;
  int      n, i, command, value;

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch(command) {
      case 1:
        scanf("%d", &value);
        q = enqueue(q, value);
        break;
      case 2:
        q = dequeue(q);
        break;
      case 3:
        show(q);
        break;
      case 4:
        empty(q);
        break;
      case 5:
        size(q);
        break;
    }
  }
  return 0;
}
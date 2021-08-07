#include <stdio.h>
#include <stdlib.h>

typedef struct Queue{
    int value;
    struct Queue *next;
}Queue;

typedef struct{
    Queue *first;
    Queue *last;
}QueuePosition;

void enqueue(QueuePosition *q,int v){
    Queue *new_q = malloc(sizeof(Queue));
    new_q->value = v;
    new_q->next = NULL;

    if(q->first == NULL){
        q->first = new_q;
        q->last = new_q;
        return;
    }
    q->last->next = new_q;
    q->last = new_q;
}

int dequeue(QueuePosition *q){
    if(q->first == NULL){
        printf("ERROR!\n");
        return 0;
    }
    int rtrn = q->first->value;
    q->first = q->first->next;
    if(q->first == q->last){
        q->first = NULL;
        q->last = NULL;
    }
    return rtrn;
}

void show(QueuePosition *q){
    if(q->first == NULL){
        printf("\n");
        return;
    }
    Queue *p = q->first;
    printf("<<< ");
    while(p->next != NULL){
        printf("%d ",p->value);
        p = p->next;
    }
    printf("%d ",p->value);
    printf("<<<\n");
}

int main(){
    QueuePosition pos = {NULL,NULL};
    char command;
    int arg;
    while(1){
        scanf(" %c",&command);
        switch(command){
            case 'E':
                scanf("%d",&arg);
                enqueue(&pos,arg);
                break;
            
            case 'D':
                dequeue(&pos);
                break;

            default:
                return 0;
        }
        show(&pos);
    }
}
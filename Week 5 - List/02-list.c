#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node_t;

node_t *append(node_t *start){
    int value;
    scanf("%d",&value);

    node_t *p = start;
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->data = value;
    node->next = NULL;

    if(start == NULL){
        start = node;
    }
    else{
        while(p->next != NULL){
            p = p->next;
        }
        p->next = node;
    }
    return start;
}

void get(node_t *start){
    int index;
    scanf("%d",&index);
    while(index != 0){
        start = start->next;
        index--;
    }
    printf("%d\n",start->data);
}

void show(node_t *start){
    node_t *p = start;
    if(p==NULL){
        printf("\n");
        return ;
    }
    
    while(p->next != NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("%d\n",p->data);
    
}

node_t *reverse(node_t *start){
    node_t *current = start;
    node_t *prev = NULL;
    node_t *nxt = current->next;

    while(current->next != NULL){
        current->next = prev;
        prev = current;
        current = nxt;
        nxt = nxt->next;
    }
    current->next = prev;
    prev = current;

    start = prev;
    return start;
}

node_t *cut(node_t *start){
    node_t *current = start;
    node_t *prev = NULL;
    node_t *head;

    int i,f,opening=1;
    scanf("%d %d",&i,&f);
    int final_o = f;

    do{
        if(i==0 && opening){
            opening = 0;
            head = current;
            if(final_o != f){
                prev->next = NULL;
            }
        }
        prev = current;
        current = current->next;
        f--;
        i--;
    }while(f >= 0);
    prev->next = NULL;
    start = head;
    return start;
}

int main(void){
    node_t *startNode;
    int n,i;
    char command;

    startNode = NULL;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf(" %c",&command);
        switch(command){
            case 'A':
                startNode = append(startNode);
                break;

            case 'G':
                get(startNode);
                break;

            case 'S':
                show(startNode);
                break;

            case 'R':
                startNode = reverse(startNode);
                break;

            case 'C':
                startNode = cut(startNode);

            default:
                break;
        }
    }
    return 0;
}
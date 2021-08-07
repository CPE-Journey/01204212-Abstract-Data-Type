#include <stdio.h>
#include <stdlib.h>

typedef struct dList{
    int data;
    struct dList *prev;
    struct dList *next;
}dList;

dList *append(dList *start,int value){
    dList *p = start;

    dList *new_node = malloc(sizeof(dList));
    new_node->data = value;
    new_node->next = NULL;

    // First Element
    if(p == NULL){
        return new_node;
    }
    // 2nd+ Element
    else{
        while(p->next != NULL){
            p = p->next;
        }
        new_node->prev = p;
        p->next = new_node;
    }
    return start;
}

void show(dList *start){
    dList *p = start;
    while(p->next != NULL){
        // printf("%d << %d >> %d\n",p->prev,p,p->next);
        printf("%d ",p->data);
        p = p->next;
    }
    // printf("%d << %d >> %d\n",p->prev,p,p->next);
    printf("%d ",p->data);
}

int main(){
    dList *start = NULL;
    start = append(start,5);
    start = append(start,6);
    start = append(start,7);
    start = append(start,12);
    start = append(start,4);
    start = append(start,8);
    show(start);
}
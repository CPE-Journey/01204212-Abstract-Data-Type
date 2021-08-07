#include <stdio.h>
#include <stdlib.h>

typedef struct lList{
    int num;
    double flt;
    char txt[10];

    char type;
    struct lList *next;

}lList;

lList *append(lList *start){
    lList *p = start;
    lList *node = malloc(sizeof(lList));

    int type,d;
    double f;
    scanf("%d",&type);
    switch(type){
        case 0:
            scanf("%d",&d);
            node->num = d;
            node->type = 'N';
            break;

        case 1:
            scanf("%lf",&f);
            node->flt = f;
            node->type = 'F';
            break;

        case 2:
            scanf("%s",node->txt);
            node->type = 'T';
            break;
    }

    // printf("%s %f %d",node->txt,node->flt,node->num);
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

void get(lList *start){
    lList *p = start;

    int order;
    scanf("%d",&order);

    while(order != 0){
        p = p->next;
        order--;
    }
    
    switch(p->type){
        case 'N':
            printf("%d\n",p->num);
            break;

        case 'F':
            printf("%f\n",p->flt);
            break;

        case 'T':
            printf("%s\n",p->txt);
            break;
    }
}

void show(lList *start){
    lList *p = start;

    if(p==NULL){
        printf("\n");
        return ;
    }

    while(p!=NULL){
        switch(p->type){
        case 'N':
            printf("%d ",p->num);
            break;

        case 'F':
            printf("%f ",p->flt);
            break;

        case 'T':
            printf("%s ",p->txt);
            break;
    }
        p = p->next;
    }
    printf("\n");
}

void show_reverse(lList *start,int first){
    lList *crnt = start;
    lList *prev = NULL;
    lList *nxt = crnt->next;

    while(crnt->next!=NULL){
        crnt->next = prev;
        prev = crnt;
        crnt = nxt;
        nxt = nxt->next;
    }
    crnt->next = prev;
    
    if(first){
        show(crnt);
        show_reverse(crnt,0);
    }
}

void insert(lList *start,int ind){
    lList *p = start;

    int order;
    if(ind>=0){
        order = ind;
    }
    else{
        scanf("%d",&order);
    }

    while(order > 0){
        p = p->next;
        order--;
    }
    
    lList *insNode = NULL;
    insNode = append(insNode);
    
    lList *nxtNode;

    nxtNode = p->next;
    p->next = insNode;
    insNode->next = nxtNode;
}

lList *delete(lList *start){
    lList *p = start;
    lList *prev = NULL;

    int order;
    scanf("%d",&order);

    while(order > 1){
        prev = p;
        p = p->next;
        order--;
    }

    if(order==0){
        return p->next;
    }

    else{
        lList *revNode = p->next;
        p->next = p->next->next;
        free(revNode);
    }
    
    return start;
}

lList *change(lList *start){
    lList *p = start;
    lList *prev;
    
    int order,first_order;
    scanf("%d",&order);
    first_order = order;

    while(order > 0){
        prev = p;
        p = p->next;
        order--;
    }

    lList *changeNode = NULL;
    changeNode = append(changeNode);
    printf("%d",changeNode->num);

    if(first_order==0){
        changeNode->next = p->next;
        return changeNode;
    }
    else{
        prev->next = changeNode;
        changeNode->next = p->next;
        return start;
    }


}

void is_empty(lList *start){
    if(start==NULL){
        printf("Empty\n");
    }
    else{
        printf("Not Empty\n");
    }
}

void length(lList *start){
    lList *p = start;
    
    int l = 0;
    while(p != NULL){
        l++;
        p = p->next;
    }
    printf("%d\n",l);
}

int main(){
    lList *start = NULL;

    int n,i;
    scanf("%d",&n);
    char command;
    for(i=0;i<n;i++){
        scanf(" %c",&command);
        switch(command){
            case 'A':
                start = append(start);
                break;

            case 'G':
                get(start);
                break;

            case 'S':
                show(start);
                break;

            case 'R':
                show_reverse(start,1);
                break;

            case 'I':
                insert(start,-1);
                break;

            case 'D':
                start = delete(start);
                break;

            case 'C':
                start = change(start);
                break;

            case 'E':
                is_empty(start);
                break;

            case 'L':
                length(start);
                break;
            
            default:
                break;
        }
    }
}
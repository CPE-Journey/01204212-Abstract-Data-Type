#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
    int data;
    struct Stack *below;
}Stack;

Stack *push(Stack *jar,int c){
    Stack *cookie = malloc(sizeof(Stack));
    cookie->data = c;
    cookie->below = NULL;
    if(jar != NULL){
        cookie->below = jar;
    }
    return cookie;
}

Stack *pop(Stack *jar,int *n){
    Stack *p = jar;
    *n = p->data;
    jar = jar->below;
    free(p);
    return jar;
}

int top(Stack *jar){
    return jar->data;
}

void show(Stack *jar){
    Stack *p = jar;
    
    if(p == NULL){
        printf("\n");
        return ;
    }
    while(p->below != NULL){
        printf("%d\n",p->data);
        p = p->below;
    }
    printf("%d\n",p->data);
}

void is_empty(Stack *jar){
    if(jar == NULL){
        printf("Empty\n");
        return;
    }
    printf("Not Empty\n");
}

Stack *make_empty(Stack *jar){
    return NULL; // Beware: There's a trash in Heap Memory
                 // or free() it
}

int main(){
    Stack *jar = NULL;
    int arg,n;
    char command;

    while(1){
        scanf(" %c",&command);

        switch(command){
            case 'A':
                scanf("%d",&arg);
                jar = push(jar,arg);
                break;

            case 'D':
                jar = pop(jar,&n);
                printf("%d\n",n);
                break;

            case 'T':
                printf("%d",top(jar));
                break;

            case 'S':
                show(jar);
                break;

            case 'E':
                is_empty(jar);
                break;

            case 'M':
                jar = make_empty(jar);
                break;

            default:
                return 0;
        }
    }
}
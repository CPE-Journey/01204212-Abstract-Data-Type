#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char num;
    struct node *next;
}Stack;

Stack *push(Stack *s,char value){
    Stack *node = malloc(sizeof(Stack));
    node->num = value;
    node->next = NULL;

    if(s == NULL){
        return node;
    }
    node->next = s;
    return node;
}

char pop(Stack **s){
    if(*s==NULL){
        return '\0';
    }
    char rtn = (**s).num;
    *s = (**s).next;
    return rtn;
}

int isEmpty(Stack *s){
    if(s==NULL){
        return 1;
    }
    return 0;
}

int main(){
    char password[1000000];
    int i = 0;
    Stack *s = NULL;
    scanf("%s",password);

    while(password[i] != 'x'){
        s = push(s,password[i]);
        i++;
    }
    i++;
    while(password[i] != 'y'){
        if(pop(&s) != password[i]){
            printf("0\n");
            return 0;
        }
        i++;
    }
    if(!isEmpty(s)){
        printf("0\n");
        return 0;
    }
    printf("1\n");
}
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    double num;
    struct node *next;
}Stack;

Stack *push(Stack *s,double value){
    Stack *node = malloc(sizeof(Stack));
    node->num = value;
    node->next = NULL;

    if(s == NULL){
        return node;
    }
    node->next = s;
    return node;
}

double pop(Stack **s){
    double rtn = (**s).num;
    *s = (**s).next;
    return rtn;
}

int isIn(char x,char *str){
    while(*str){
        if(*str == x){
            return 1;
        }
        str++;
    }
    return 0;
}

int main(){
    int t_len,i;
    char text[1000000];
    char opr[] = "+-*/";

    scanf("%d",&t_len);
    scanf("%s",text);

    Stack *s = NULL;
    double sum = 0;
    for(i=0;i<t_len;i++){
        // OPERATOR
        if(isIn(text[i],opr)){
            double op2 = pop(&s),op1 = pop(&s);
            switch(text[i]){
                case '+':
                    sum = (op1+op2);
                    break;

                case '-':
                    sum = (op1-op2);
                    break;

                case '*':
                    sum = (op1*op2);
                    break;

                case '/':
                    sum = (op1/op2);
                    break;
            }
            s = push(s,sum);
        }
        // NUMBER
        else{
            s = push(s,(double)((int)text[i]-48));
        }
    }
    printf("%.2f\n",sum);
}
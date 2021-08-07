#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  char data;
  struct node *next;
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

char pop(Stack **s){
  if(*s==NULL){
    return 'X';
  }
  char rtrn = (**s).data;
  *s = (**s).next;
  return rtrn;
}

int isEmpty(Stack *s){
    if(s==NULL){
        return 1;
    }
    return 0;
}

int indexOf(char *str,char sym){
    int ind = 0;
    while(*str){
        if(*str==sym){
            return ind;
        }
        ind++;
        str++;
    }
    return -1;
}

int main(){
    int t_len,i;
    scanf("%d",&t_len);
    char text[1000000];
    scanf("%s",text);
    char open[] = "([{";
    char close[] = ")]}";

    Stack *s = NULL;
    for(i=0;i<t_len;i++){
        // Open Paren
        if(indexOf(open,text[i]) >= 0){
            s = push(s,text[i]);
        }
        // Close Paren
        else{
            if(indexOf(close,text[i]) != indexOf(open,pop(&s))){
              printf("0\n");
              return 0;
            }
        }
    }
    if(!isEmpty(s)){
      printf("0\n");
      return 0;
    }
    printf("1\n");
}
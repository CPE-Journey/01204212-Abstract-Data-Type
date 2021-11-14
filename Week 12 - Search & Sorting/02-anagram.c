#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char word[50];
    char sort_word[50];
    struct node *next;
}WordList;

void insertionSort(char arr[]){
    int i,j;
    for(i=1;i<strlen(arr);i++){
        int insert_index = i;
        int insert_value = arr[i];
        for(j=0;j<i+1;j++){
            if(arr[j] > arr[i]){
                insert_index = j;
                break;
            }
        }
        for(j=i;j>insert_index;j--){
            arr[j] = arr[j-1];
        }
        arr[insert_index] = insert_value;
    }
}

WordList *append(WordList *w,char *text){
    WordList *node = malloc(sizeof(WordList));
    strcpy(node->word,text);
    insertionSort(text);
    strcpy(node->sort_word,text);
    node->next = NULL;

    if(w==NULL)
        return node;
    WordList *tmp = w;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
    return w;
}

void anagram(WordList *w,char *text){
    insertionSort(text);
    while(w != NULL){
        if(strcmp((w->sort_word),text) == 0)
            printf("%s ",w->word);
        w = w->next;
    }
    printf("\n");
}

int main(){
    WordList *wl = NULL;
    int i,m,n;
    char text[50];
    scanf("%d %d",&m,&n);
    for(i=0;i<m;i++){
        scanf("%s",text);
        wl = append(wl,text);
    }
    for(i=0;i<n;i++){
        scanf("%s",text);
        anagram(wl,text);
    }
    return 0;
}
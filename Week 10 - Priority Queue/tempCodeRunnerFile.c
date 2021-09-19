#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    int head;
    int status;
    char string[15];
    struct tree*left;
    struct tree*right;
}tree_t;

typedef struct heap
{
    tree_t**array; // collect the pointer of tree
    int last_index;
}heap_t;

heap_t*reserve(heap_t*min_heap,int n){
    min_heap = malloc(sizeof(heap_t));
    min_heap->last_index=0;
    // tree_t**node=(tree_t**)malloc(sizeof(tree_t*)*(n+1));
    min_heap->array=malloc(sizeof(tree_t)*n);
    return min_heap;
}


void main(void){
    int n;
    char test[15];
    int x;
    scanf("%d",&n);
    heap_t*min_heap=NULL;
    min_heap=reserve(min_heap,n);
    for(int i=1;i<=n;i++){
        printf("i=%d\n",i);
        // printf("size of (tree_t*)=%ld address of array[i] = %p \n",sizeof (min_heap->array[i]->head),min_heap->array[i]);
        // scanf("%s %d",min_heap->array[i]->string,&(min_heap->array[i]->head));
        scanf("%s %d",min_heap->array[i]->string,&(min_heap->array[i]->head));
        // printf("string=%s freq=%d\n",min_heap->array[i]->string,min_heap->array[i]->head);
        min_heap->array[i]->left=NULL;
        min_heap->array[i]->right=NULL;
        min_heap->array[i]->status=0;
        // break;
    }

    printf("printing");
    for(int j=1;j<=n;j++){
        printf("string=%s freq=%d\n",min_heap->array[j]->string,min_heap->array[j]->head);
    }
}
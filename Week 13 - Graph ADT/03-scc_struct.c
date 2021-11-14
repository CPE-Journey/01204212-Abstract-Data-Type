#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int data;
    int enter;
    int leave;
}Vertex;

int swp(int *a,int *b){
    int *tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){
    Vertex *arr = malloc(sizeof(Vertex)*10);
    int x,y;
    arr[0].data = 1;
    arr[0].enter = 10;
    arr[0].leave = 100;

    arr[1].data = 2;
    arr[1].enter = 20;
    arr[1].leave = 200;
    swap(&arr[0],&arr[1]);
    printf("%d %d",arr[0].data,arr[1].data);
}
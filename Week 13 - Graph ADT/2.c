#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}Node;

typedef struct{
    Node **arr;
    int *visit;
    int index;
}Graph;

typedef struct{
    int *arr;
    int index;
}ArrayList;

ArrayList *createArrayList(int size){
    ArrayList *al = malloc(sizeof(ArrayList));
    al->arr = malloc(sizeof(int)*size);
    al->index = 0;
    return al;
}

void append(ArrayList *al,int num){
    al->arr[al->index] = num;
    al->index++;
}

Graph *createGraph(int s){
    Graph *g = malloc(sizeof(Graph));
    g->arr = malloc(sizeof(Node)*s);
    g->visit = malloc(sizeof(int)*s);
    g->index = 0;
    return g;
}

Node *createNode(int value){
    Node *new = malloc(sizeof(Node));
    new->data = value;
    new->next = NULL;
    return new;
}

void insert(Graph *g,int v1,int v2){
    int i,isFound1 = 0,isFound2 = 0;
    for(i=0;i<g->index;i++){
        if(g->arr[i]->data == v1){
            Node *tmp = g->arr[i];
            while(tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = createNode(v2);
            isFound1 = 1;
            break;
        }
    }
    for(i=0;i<g->index;i++){
        if(g->arr[i]->data == v2){
            Node *tmp = g->arr[i];
            while(tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = createNode(v1);
            isFound2 = 1;
            break;
        }
    }
    if(!isFound1){
        g->arr[g->index] = createNode(v1);
        g->arr[g->index]->next = createNode(v2);
        g->visit[g->index] = 0;
        g->index++;
    }
    if(!isFound2){
        g->arr[g->index] = createNode(v2);
        g->arr[g->index]->next = createNode(v1);
        g->visit[g->index] = 0;
        g->index++;
    }
}

int indexOf(Graph *g,int value){
    int i;
    for(i=0;i<g->index;i++){
        if(g->arr[i]->data == value)
            return i;
    }
    return -1;
}

void show(Graph *g){
    int i;
    for(i=0;i<g->index;i++){
        printf("%d[%d] -> ",g->arr[i]->data,g->visit[i]);
        Node *tmp = g->arr[i]->next;
        while(tmp != NULL){
            printf("%d -> ",tmp->data);
            tmp = tmp->next;
        }
        printf("NULL\n");
    }
    printf("\n");
}

int isIn(int num,int *arr,int len){
    int i;
    for(i=0;i<len;i++){
        if(num == arr[i])
            return 1;
    }
    return 0;
}

int intersect(int *arr1,int len1,int *arr2,int len2){
    int i,count = 0;
    for(i=0;i<len1;i++){
        if(isIn(arr1[i],arr2,len2))
            count++;
    }
    return count;
}

int maxClique(Graph *g){
    int i,j,maxC = 0;
    for(int i=0;i<g->index;i++){
        // Create Sample Array
        ArrayList *select = createArrayList(g->index);
        Node *tmp = g->arr[i];
        while(tmp != NULL){
            append(select,tmp->data);
            tmp = tmp->next;
        }
        // printf("%d: ",g->arr[i]->data);
        // Test with any other
        ArrayList *inter = createArrayList(g->index);
        for(int j=0;j<g->index;j++){
            if(i == j)
                continue;
            ArrayList *sample = createArrayList(g->index);
            Node *tmp = g->arr[j];
            while(tmp != NULL){
                append(sample,tmp->data);
                tmp = tmp->next;
            }
            append(inter,intersect(select->arr,select->index,sample->arr,sample->index));
            // printf("%d(%d) ",g->arr[j]->data,intersect(select->arr,select->index,sample->arr,sample->index));
            free(sample);
        }
        // Count For Max
        ArrayList *record = createArrayList(g->index);
        for(j=0;j<inter->index;j++){
            if(isIn(inter->arr[j],record->arr,record->index))
                continue;
            int crnt = inter->arr[j],counter = 0,k;
            for(k=j;k<inter->index;k++){
                if(inter->arr[j] == inter->arr[k])
                    counter++;
            }
            append(record,inter->arr[j]);
            if(counter+1 == inter->arr[j] && counter+1 > maxC){
                maxC = counter+1;
                // printf(" (%d %d) Max: %d ",counter+1,inter->arr[j],maxC);
            }
            // printf("%d",counter);
            // printf("(%d %d) ",counter+1,inter->arr[j]);
        }
        // printf("\n");
        free(select);
    }
    // printf("\n%d\n",maxC);
    return maxC;
}

int main(){
    int i,n,m,n1,n2,w,sp;
    scanf("%d %d",&n,&m);
    Graph *graph = createGraph(n);
    for(i=0;i<m;i++){
        scanf("%d %d",&n1,&n2);
        insert(graph,n1,n2);
    }
    // show(graph);

    printf("%d",maxClique(graph));
}
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    int weight;
    struct node *next;
}Node;

typedef struct{
    Node **arr;
    int *visit;
    int index;
}Graph;

Graph *createGraph(int s){
    Graph *g = malloc(sizeof(Graph));
    g->arr = malloc(sizeof(Node)*s);
    g->visit = malloc(sizeof(int)*s);
    g->index = 0;
    return g;
}

Node *createNode(int value,int cost){
    Node *new = malloc(sizeof(Node));
    new->data = value;
    new->weight = cost;
    new->next = NULL;
    return new;
}

void insert(Graph *g,int v1,int v2,int weight){
    int i,isFound1 = 0,isFound2 = 0;
    for(i=0;i<g->index;i++){
        if(g->arr[i]->data == v1){
            Node *tmp = g->arr[i];
            while(tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = createNode(v2,weight);
            isFound1 = 1;
            break;
        }
    }
    for(i=0;i<g->index;i++){
        if(g->arr[i]->data == v2){
            Node *tmp = g->arr[i];
            while(tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = createNode(v1,weight);
            isFound2 = 1;
            break;
        }
    }
    if(!isFound1){
        g->arr[g->index] = createNode(v1,weight);
        g->arr[g->index]->next = createNode(v2,weight);
        g->visit[g->index] = 0;
        g->index++;
    }
    if(!isFound2){
        g->arr[g->index] = createNode(v2,weight);
        g->arr[g->index]->next = createNode(v1,weight);
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

void shortestPathRecursion(Graph *g,int begin,int dest,int cost,int *low){
    Node *start = g->arr[indexOf(g,begin)]->next;
    g->visit[indexOf(g,begin)] = 1;
    while(start != NULL){
        if(g->visit[indexOf(g,start->data)]){
            start = start->next;
            continue;
        }
        cost += start->weight;
        if(start->data == dest){
            if(*low == -1 || cost < *low){
                *low = cost;
                break;
            }
        }
        shortestPathRecursion(g,start->data,dest,cost,low);
        cost -= start->weight;
        start = start->next;
    }
    g->visit[indexOf(g,begin)] = 0;
}

int shortestPath(Graph *g,int begin,int dest){
    if(begin == dest)
        return 0;
    int low = -1;
    shortestPathRecursion(g,begin,dest,0,&low);
    return low;
}

int main(){
    int i,n,m,p,n1,n2,w;
    scanf("%d %d %d",&n,&m,&p);
    Graph *graph = createGraph(m);
    for(i=0;i<m;i++){
        scanf("%d %d %d",&n1,&n2,&w);
        insert(graph,n1,n2,w);
    }
    for(i=0;i<p;i++){
        scanf("%d %d",&n1,&n2);
        printf("%d\n",shortestPath(graph,n1,n2));
    }
}
#include <stdio.h>
#include <stdlib.h>
int *visit,*enter,*leave;
int time = 1;

int maxIndex(int *arr,int len){
    int i,max=arr[0],ind = 0;
    for(i=0;i<len;i++){
        if(arr[i]>max){
            max = arr[i];
            ind = i;
        }
    }
    return ind;
}

int **createArray(int size){
    int i,j;
    int **mat = malloc(sizeof(int*)*size);
    for(i=0;i<size;i++){
        mat[i] = malloc(sizeof(int)*size);
        for(j=0;j<size;j++){
            mat[i][j] = 0;
        }
    }
    return mat;
}

int **createTranspose(int **arr,int size){
    int **mat = createArray(size);
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++)
            mat[j][i] = arr[i][j];
    }
    return mat;
}

int *createLinear(int size){
    int i;
    int *mat = malloc(sizeof(int)*size);
    for(i=0;i<size;i++)
        mat[i] = 0;
    return mat;
}

void traversal(int **arr,int len,int vertex){
    int i;
    enter[vertex] = time;
    time++;
    for(i=0;i<len;i++){
        if(arr[vertex][i] && !visit[i]){
            visit[vertex] = 1;
            traversal(arr,len,i);
            visit[vertex] = 0;
        }
    }
    visit[vertex] = 1;
    leave[vertex] = time;
    time++;
}

int visitAll(int len){
    int i;
    for(i=0;i<len;i++){
        if(!visit[i])
            return 0;
    }
    return 1;
}

int sum(int *arr,int len){
    int i,res = 0;
    for(i=0;i<len;i++){
        if(arr[i]==1)
            res += arr[i];
    }
    return res;
}


void replace(int *rtn,int *arr,int len){
    int i;
    for(i=0;i<len;i++)
        rtn[i] = arr[i];
}

int main(){
    int i,j,k,n,e,v1,v2,crnt_sum = 0,prev_sum = 0;
    scanf("%d %d",&n,&e);
    int **adj = createArray(n);
    int *scc = createLinear(n);
    visit = createLinear(n);
    enter = createLinear(n);
    leave = createLinear(n);
    for(i=0;i<e;i++){
        scanf("%d %d",&v1,&v2);
        adj[v1][v2] = 1;
    }
    int **trs = createTranspose(adj,n);
    i = 0;
    while(!visitAll(n)){
        traversal(adj,n,i);
        i++;
    }
    for(i=0;i<n;i++){
        visit[i] = 0;
    }
    int *total_visit = createLinear(n);
    while(!visitAll(n)){
        int max_index = maxIndex(leave,n);
        traversal(trs,n,max_index);
        crnt_sum = sum(visit,n);
        if(crnt_sum-prev_sum > sum(scc,n)){
            for(i=0;i<n;i++){
                if(scc[i] == 1)
                    scc[i] = -1;
            }
            for(i=0;i<n;i++){
                if(scc[i] == 0 && visit[i] == 1)
                    scc[i] = 1;
            }
        }
        else{
            for(i=0;i<n;i++){
                if(visit[i] && !scc[i])
                    scc[i] = -1;
            }
        }
        prev_sum = crnt_sum;
        leave[max_index] = 0;
    }
    for(int i=0;i<n;i++){
        if(scc[i]==1)
            printf("%d ",i);
    }
    printf("\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
int *current;

int **createMatrix(int size){
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

int max(int a,int b){
    return a > b ? a : b;
}

int isClique(int **arr,int re_size){
    int i,j;
    for(i=1;i<re_size;i++){
        for(j=i+1;j<re_size;j++){
            if(!arr[current[i]][current[j]])
                return 0;
        }
    }
    return 1;
}

int maxClique(int **arr,int start,int size,int re_size){
    int i,max_c = 0;
    for(i=start;i<size;i++){
        current[re_size] = i;
        if(isClique(arr,re_size+1)){
            max_c = max(max_c,re_size);
            max_c = max(max_c,maxClique(arr,i,size,re_size+1));
        }
    }
    return max_c;
}

int main(){
    int i,j,n,m,n1,n2;
    scanf("%d %d",&n,&m);
    int **adj = createMatrix(n);
    current = malloc(sizeof(int)*n);
    for(i=0;i<m;i++){
        scanf("%d %d",&n1,&n2);
        adj[n1][n2] = 1;
        adj[n2][n1] = 1;
    }
    printf("%d\n",maxClique(adj,0,n,1));
}
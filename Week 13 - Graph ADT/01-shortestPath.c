#include <stdio.h>
#include <stdlib.h>

int **createMatrix(int size){
    int i,j;
    int **mat = malloc(sizeof(int*)*size);
    for(i=0;i<size;i++){
        mat[i] = malloc(sizeof(int)*size);
        for(j=0;j<size;j++){
            if(i==j)
                mat[i][j] = 0;
            else
                mat[i][j] = 999;
        }
    }
    return mat;
}

int min(int a,int b){
    return a < b ? a : b;
}

int main(){
    int i,j,k,n,m,p,n1,n2,w;
    scanf("%d %d %d",&n,&m,&p);
    int **adj = createMatrix(n);
    for(i=0;i<m;i++){
        scanf("%d %d %d",&n1,&n2,&w);
        adj[n1][n2] = w;
        adj[n2][n1] = w;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(k=0;k<n;k++)
                adj[i][k] = min(adj[i][k],adj[i][j]+adj[j][k]);
        }
    }
    for(i=0;i<p;i++){
        scanf("%d %d",&n1,&n2);
        printf("%d\n",adj[n1][n2] <= 100 ? adj[n1][n2] : -1);
    }
}
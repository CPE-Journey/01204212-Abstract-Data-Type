#include<stdio.h>
#include<string.h>

int size;
char maze[100][100];
char visit[100][100];
int walkrow[]={1,0,-1,0};
int walkcol[]={0,1,0,-1};
int succeed=0;
void fun(int i,int j);

void main(){
    int i,j,s=0;
    // printf("enter size ");
    scanf("%d\n",&size);
    for (s; s<size ;s++)
    {   
        // printf("enter maze");
        fgets(maze[s], 100, stdin);
        // printf("i=%d\n",i);
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            if (maze[i][j]=='S')
            {
                printf("i=%d j=%d\n",i,j);
                fun(i,j);
            }
        }
    }

    for (i=0;i<size;i++){
        printf("%s",maze[i]);
    }
}

void fun(int i,int j){
    // printf("%d %d\n",i,j);
    // printf("here\n");
    if (i<0||i>=size||j<0||j>=size)
    {   
        printf("border\n");
        return;
    }
    if (maze[i][j]=='#')
    {
        printf("bomb\n");
        return;
    }
    if (visit[i][j]==1)
    {
        printf("visit\n");
        return;
    }
    if (maze[i][j]=='G')
    {   
        printf("G\n");
        succeed=1;
        return;
    }
    visit[i][j]=1;
    for(int a=0;a<4;a++){
        // printf("loop i=%d,j=%d\n",i,j);
        fun(i+walkrow[a],j+walkcol[a]);
        if (succeed)
        {
            maze[i][j]='.';
            return ;
        }
    }

}


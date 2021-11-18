#include <stdio.h>

int size = 12;
char maze[100][100] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
    {'S',' ','#',' ','#',' ','#','#','#','#',' ','#'},
    {'#','#','#',' ','#',' ',' ',' ',' ','#',' ','#'},
    {'#',' ',' ',' ',' ','#','#','#',' ','#',' ','G'},
    {'#','#','#','#',' ','#',' ','#',' ','#',' ','#'},
    {'#',' ',' ','#',' ','#',' ','#',' ','#',' ','#'},
    {'#','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#'},
    {'#','#','#','#','#','#',' ','#','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#'}
};

int walked[100][100];
int isFound = 0;

void printMaze(){
    for(int i=0;i<size;i++){
        for(int j=0;i<size;j++){
            printf("%c ",maze[i][j]);
        }
        printf("\n");
    }
}

void traverseMaze(int r,int c){
    if(r < 0 || c < 0 || r >= size || c >= size){
        return ;
    }
    if(maze[r][c] == '#'){
        return ;
    }
    if(walked[r][c]==1){
        return ;
    }
    walked[r][c] = 1;
    int pi[] = {0,1,0,-1};
    int pj[] = {1,0,-1,0};
    if(maze[r][c] == 'G'){
        isFound = 1;
    }
    if(isFound){
        maze[r][c] == '.';
        return ;
    }
    for(int i=0;i<3;i++){
        traverseMaze(r+pi[i],c+pj[i]);
    }
}

int main(void){
    traverseMaze(2,0);
    // for(int i=0;i<size;i++){
    //     printf("%s\n",maze[i]);
    // }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            printf("%d ",walked[i][j]);
        }
        printf("\n");
    }
}
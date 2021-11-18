#include <stdio.h>
#include <stdlib.h>

int size,i_start,j_start,i,j;
char maze[110][110];

void printMaze(){
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(i==i_start && j==j_start){
                printf("S");
            }
            else if(maze[i][j] == 'X'){
                printf(" ");
            }
            else{
                printf("%c",maze[i][j]);
            }
        }
        printf("\n");
    }
}

int walkable(int a,int b){
    if(((maze[a][b] == ' ') || (maze[a][b] == 'G')) && ((maze[a][b] != '#') && (maze[a][b] != '.'))){
        return 1;
    }
    return 0;
}

int pathfinding(int i,int j){
    if(i < 0 || j < 0 || i >= size || j >= size){
        return 0;
    }
    if(walkable(i,j)){
        
    }
}

int traverseMaze(){
    int pi = i_start;
    int pj = j_start;
    while(1){
        if((pi-1 >= 0) && walkable(pi-1,pj)){
            maze[pi][pj] = '.';
            if(maze[pi-1][pj] == 'G'){
                printMaze();
                return 0;
            }
            pi -= 1;
        }
        else if((pj+1 < size) && walkable(pi,pj+1)){
            maze[pi][pj] = '.';
            if(maze[pi][pj+1] == 'G'){
                printMaze();
                return 0;
            }
            pj += 1;
        }
        else if((pi+1 < size) && walkable(pi+1,pj)){
            maze[pi][pj] = '.';
            if(maze[pi+1][pj] == 'G'){
                printMaze();
                return 0;
            }
            pi += 1;
        }
        else if((pj-1 >= 0) && walkable(pi,pj-1)){
            maze[pi][pj] = '.';
            if(maze[pi][pj+1] == 'G'){
                printMaze();
                return 0;
            }
            pj -= 1;
        }
        else{
            maze[pi][pj] = 'X';
            break;
        }
    }
    // printMaze();
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(maze[i][j] == '.'){
                maze[i][j] = ' ';
            }
        }
    }
    
    return traverseMaze();
}

int main(){
    scanf("%d\n",&size);
    for(i=0;i<size;i++){
        char *tmp = malloc(size*sizeof(char));
        for(j=0;j<size;j++){
            scanf("%c",&tmp[j]);
        }
        getchar();
        for(j=0;j<size;j++){
            maze[i][j] = tmp[j];
        }
        free(tmp);
    }

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(maze[i][j] == 'S'){
                i_start = i;
                j_start = j;
                break;
            }
        }
    }
    traverseMaze();
    return 0;
}
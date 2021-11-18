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

int traverseMaze(){
    int pi = i_start;
    int pj = j_start;
    while(1){
        if((pj-1 >= 0) && ((maze[pi][pj-1] == ' ') || (maze[pi][pj-1] == 'G') )){
            maze[pi][pj] = '.';
            if(maze[pi][pj-1] == 'G'){
                printMaze();
                return 0;
            }
            pj -= 1;
        }
        else if((pi+1 < size) && ((maze[pi+1][pj] == ' ') || (maze[pi+1][pj] == 'G'))){
            maze[pi][pj] = '.';
            if(maze[pi+1][pj] == 'G'){
                printMaze();
                return 0;
            }
            pi += 1;
        }
        else if((pj+1 < size) && ((maze[pi][pj+1] == ' ') || (maze[pi][pj+1] == 'G') )){
            maze[pi][pj] = '.';
            if(maze[pi][pj+1] == 'G'){
                printMaze();
                return 0;
            }
            pj += 1;
        }
        else if((pi-1 >= 0) && ((maze[pi-1][pj] == ' ') || (maze[pi-1][pj] == 'G'))){
            maze[pi][pj] = '.';
            if(maze[pi-1][pj] == 'G'){
                printMaze();
                return 0;
            }
            pi -= 1;
        }
        else{
            maze[pi][pj] = 'X';
            break;
        }
    }
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
        char *tmp = malloc(size+1);
        for(j=0;j<size;j++){
            scanf("%c",&tmp[j]);
        }
        getchar();
        for(j=0;j<size;j++){
            maze[i][j] = tmp[j];
        }
        free(tmp);
    }

    // scanf("%d",&size);
    // char temp[110];
    // fgets(temp, 110, stdin);
    // for (i = 0; i < size; i++){
    //     char temp[110];
    //     fgets(temp, 110, stdin);
    //     if (i < size){
    //         for (j = 0; j < size; j++)
    //             maze[i][j] = temp[j];
    //     }
    // }

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
}
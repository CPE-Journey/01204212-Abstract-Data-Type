#include <stdio.h>
#include <stdlib.h>

void printMaze(char *maze,int size,int is,int js){
    int i;
    for(i=0;i<size;i++){
        int j;
        for(j=0;j<size;j++){
            if(i==is && j==js){
                printf("S ");
            }
            else if(*(maze+(i*size)+j) == 'X'){
                printf("  ");
            }
            else{
                printf("%c ",*(maze+(i*size)+j));
            }
        }
        printf("\n");
    }
}

void traverseMaze(char *maze,int size,int is,int js){
    int pi = is;
    int pj = js;
    while(1){
        if((pj-1 >= 0) && (*(maze+(pi*size)+pj-1) == ' ' || *(maze+(pi*size)+pj-1) == 'G' )){
            *(maze+(pi*size)+pj) = '.';
            if(*(maze+(pi*size)+pj-1) == 'G'){
                printMaze(maze,size,is,js);
                return 0;
            }
            pj -= 1;
        }
        else if((pi+1 < size) && (*(maze+((pi+1)*size)+pj) == ' ' || *(maze+((pi+1)*size)+pj) == 'G')){
            *(maze+(pi*size)+pj) = '.';
            if(*(maze+((pi+1)*size)+pj) == 'G'){
                printMaze(maze,size,is,js);
                return 0;
            }
            pi += 1;
        }
        else if((pj+1 < size) && (*(maze+(pi*size)+pj+1) == ' ' || *(maze+(pi*size)+pj+1) == 'G' )){
            *(maze+(pi*size)+pj) = '.';
            if(*(maze+(pi*size)+pj+1) == 'G'){
                printMaze(maze,size,is,js);
                return 0;
            }
            pj += 1;
        }
        else if((pi-1 >= 0) && (*(maze+((pi-1)*size)+pj) == ' ' || *(maze+((pi-1)*size)+pj) == 'G')){
            *(maze+(pi*size)+pj) = '.';
            if(*(maze+((pi-1)*size)+pj) == 'G'){
                printMaze(maze,size,is,js);
                return 0;
            }
            pi -= 1;
        }
        else{
            *(maze+(pi*size)+pj) = 'X';
            break;
        }
    }
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(*(maze+(i*size)+j) == '.'){
                *(maze+(i*size)+j) = ' ';
            }
        }
    }
    return traverseMaze(maze,size,is,js);
}

int main(){

    int size=12,i_start,j_start,i_end,j_end;
    char maze[101][101];

    printMaze(maze,size,0,0);

    // printf("%c",maze[2][0]);

    // char maze[12][12] = {
    //     {'#','#','#','#','#','#','#','#','#','#','#','#'},
    //     {'#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
    //     {'S',' ','#',' ','#',' ','#','#','#','#',' ','G'},
    //     {'#','#','#',' ','#',' ',' ',' ',' ','#',' ','#'},
    //     {'#',' ',' ',' ',' ','#','#','#',' ','#',' ','#'},
    //     {'#','#','#','#',' ','#',' ','#',' ','#',' ','#'},
    //     {'#',' ',' ','#',' ','#',' ','#',' ','#',' ','#'},
    //     {'#','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
    //     {'#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#'},
    //     {'#','#','#','#','#','#',' ','#','#','#',' ','#'},
    //     {'#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
    //     {'#','#','#','#','#','#','#','#','#','#','#','#'}
    // };

    // for(i=0;i<size;i++){
    //     printf("1\n");
    //     for(j=0;j<size;j++){
    //         if(maze[i][j] == 'S'){
    //             i_start = i;
    //             j_start = j;
    //         }
    //         if(maze[i][j] == 'G'){
    //             i_end = i;
    //             j_end = j;
    //         }
    //     }
    // }
    // traverseMaze(maze,size,i_start,j_start);
    // return 0;
}
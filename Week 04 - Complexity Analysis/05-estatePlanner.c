#include <stdio.h>
int i,j,row,col;
int board[10000][10000];

void printBoard(){
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf("%d  ",board[i][j]);
        }
        printf("\n");
    }
}

int twoPower(int p){
    int sum = 1,x;
    for(x=1;x<=p;x++){
        sum *= 2;
    }
    return sum;
}

int main(){
    scanf("%d %d",&row,&col);
    int isDiv = 1,count=0;
    while(isDiv){
        isDiv = 0;
        for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                // Pinned Point
               
                if(board[i][j]==0){
                    count += 1;
                    
                    isDiv = 1;
                    int powerC=0,k,l;

                    while(twoPower(powerC) <= col-j && twoPower(powerC) <= row-i){
                        powerC++;
                    }
                    powerC--;
                    
                    for(k=i;k<i+twoPower(powerC);k++){
                        for(l=j;l<j+twoPower(powerC);l++){
                            board[k][l] = 1;
                        }
                    }
                }
            }
        }
    }
    printf("%d",count);
}

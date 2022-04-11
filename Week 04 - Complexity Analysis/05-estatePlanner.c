#include <stdio.h>

int row,col,count = 0;

int twoPower(int p){
    int sum = 1,x;
    for(x=1;x<=p;x++){
        sum *= 2;
    }
    return sum;
}

void estatePlanner(int row,int col){
    if(row==0 || col==0){
        return ;
    }
    int p = 0,length;
    while(twoPower(p) <= col&& twoPower(p) <= row){
        p++;
    }
    p--;
    length = twoPower(p);
    count++;
    estatePlanner(row-length,col);
    estatePlanner(col-length,length);
}

int main(){
    scanf("%d %d",&row,&col);
    estatePlanner(row,col);
    printf("%d",count);
}

// O(n)
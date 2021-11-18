#include <stdio.h>
#include <math.h>

int isPrime(int n){
    int i;
    if(n==2){
        return 1;
    }
    for(i=2;i<=ceil(sqrt(n));i++){
        if(n%i==0){
            return 0;
        }
    }
    return 1;
}

int main(){
    int n;
    scanf("%d",&n);
    printf("%d",isPrime(n));
}

// O(sqrt(n))
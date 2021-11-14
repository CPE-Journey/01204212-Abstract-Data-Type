#include <stdio.h>

void printArray(int arr[],int len){
    int i;
    for(i=0;i<len;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void insertionSort(int arr[],int len){
    int i,j;
    for(i=1;i<len;i++){
        int insert_index = i;
        int insert_value = arr[i];
        for(j=0;j<i+1;j++){
            if(arr[j] > arr[i]){
                insert_index = j;
                break;
            }
        }
        for(j=i;j>insert_index;j--){
            arr[j] = arr[j-1];
        }
        arr[insert_index] = insert_value;
        printArray(arr,len);
    }
}

int main(){
    int size,i;
    scanf("%d",&size);
    int data[size];
    for(i=0;i<size;i++){
        scanf("%d",&data[i]);
    }
    insertionSort(data,size);
    return 0;
}
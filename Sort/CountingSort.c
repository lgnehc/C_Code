#include <stdio.h>

//计数排序适用于集中在小范围内的数据排序

//打印函数
void printArray(int arr[],int length){
    for (int i=0; i<length; i++)  { printf("%d ",arr[i]); }
    printf("\n");
}

//找出数组中的最大值
int findMax(int arr[],int length){
    int max = arr[0];
    for(int i=0; i<length; i++){
        // max = arr[i] > max ? arr[i] :max;
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

//length是数组长度，
void countingSort(int arr[],int length){
    //确定出计数数组的长度
    int max = findMax(arr,length)+1;
    int count[max];
    //初始化数组
    for(int i=0; i < max; i++){
        count[i] =0 ;
    }
    printf("arr:");
    printArray(arr,length);
    //计数
    for(int i = 0; i < length; i++){
        count[arr[i]]++;
    }

    printf("count:");
    printArray(count,max);
    

    //输出打印
    for(int i = 0; i < max; i++){
        //count[i]的计数值多大，那么就打印下标多少次
        if(count[i] != 0){
            for(int j = 0 ;j < count[i]; j++){
                printf("%d ",i);
            }
        }  
    }    
}

int main(){
    int arr[8] ={1,2,5,9,2,6,7,4};
    int length = sizeof(arr)/sizeof(int);
    
    countingSort(arr,length);

    return 0;
}
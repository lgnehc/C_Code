#include <stdio.h>

void printArray(int array[],int length){
    for (int i=0; i<length; i++)  { printf("%d ",array[i]); }
    printf("\n");
}

void bubbleSort(int array[],int length){
    for(int i = 0; i < length-1; i++){    //int i = length-1; i > 0; i--  都是 执行n-1次判断
        int swapCount = 0;
        for(int j = 0;j<length-1; j++){   //判断是否交换
            if(array[j] > array[j+1]){
                int tem =array[j+1];
                array[j+1] = array[j];
                array[j] = tem;
                swapCount ++;  
            }   
        }
        if(swapCount == 0)  {break;}
        printArray(array,length);
    }
}

int main(){
    int array[8] = {49,38,65,97,76,13,27,49};
    bubbleSort(array,8);
    // printArray(array,8);

    return 0;
}
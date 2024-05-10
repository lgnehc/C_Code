#include <stdio.h>
#include <stdlib.h>

//打印函数
void printArray(int arr[],int length){
    for (int i=0; i<length; i++){ 
        printf("%d ",arr[i]); 
    }
    printf("\n");
}

//找出数组中的最大值
int get_Max(int arr[],int length){
    int max = arr[0];
    for(int i=0; i<length; i++){
        // max = arr[i] > max ? arr[i] :max;
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

//按个/十/百位数排序
//参数说明：exp=1,10,100是用来取余数的；length是需要排序的数组长度
void countSort(int arr[],int length,int exp){
    int output[length];     //定义输出数组
    int count[10] = {0};    //定义桶数组
    
    //统计count[]里面记了多少个数
    for(int i = 0; i < length; i++){
        int n = (arr[i]/exp)%10;     //确定个/十/...位数
        count[n]++;
   }
    //把统计个数累加起来
    for(int i = 1; i < 10;i++){
        count[i] = count[i-1] + count[i];
    }
    
    //根据累加数值定位到原始数据arr
    for(int i = length-1; i>=0; i--){
        int n =(arr[i]/exp) % 10 ;    //确定arr[i]的个/十/百位数
        output[count[n]-1] = arr[i];  //为啥对应关系是这个
        count[n]--;
    } 
    //重新赋值给回arr[]
    for(int i = 0; i < length; i++){
        arr[i] = output[i];
    }
}


void radixSort(int arr[], int length){
    int max = get_Max(arr,length);
    for(int exp = 1;max/exp > 0; exp = exp*10){
        countSort(arr,length,exp);
    }
}

int main(){
   int arr[6] = {12,246,347,65,89,8};
   int length = sizeof(arr)/sizeof(arr[0]);
   //printArray(arr,length);

   radixSort(arr,length);
   printArray(arr,length);
   
    return 0;
}
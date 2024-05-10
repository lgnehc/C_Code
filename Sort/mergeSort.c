#include <stdio.h>

//学习资料：B站up:正月点灯笼
//先细分，在归并

//打印函数
void printArray(int arr[],int length){
    for (int i=0; i<length; i++)  { printf("%d ",arr[i]); }
    printf("\n");
}

//归并函数：针对两边有序的，L/R是开始/结束下标，M是中间分隔index
void merge(int arr[],int L, int M,int R){
    //定义分隔后的2个数组
    int Left_Size = M-L;
    int Right_Size = (R-M)+1;
    int left[Left_Size] ;
    int right[Right_Size];
    //细分数组，直接赋值到left/right[]数组
    for(int i = M; i <= R; i++){
        right[i- M] =arr[i];
    }
    //printArray(right,R-M+1);
    for(int i = L; i < M; i++){
        left[i-L] = arr[i];           //这里为什么是i-L;
    }
    //printArray(left,M-L);
    
    //合并
    int i = 0;   //指向left的index
    int j = 0;   //指向right的index
    int k = L;   //指向合并后存放数据的数组的index
    //情形1：两个都还没到顶点
    while( i<Left_Size && j<Right_Size){  
        if(left[i] < right[j]){
            arr[k] = left[i];   //小到大排序
            i++;
            k++;
        }else if (left[i] >= right[j]){
            arr[k] = right[j];
            j++;
            k++;
        }
    }
    //情形2：有一个已经到顶,直接赋值
    while(i<Left_Size && j==Right_Size){
        arr[k] = left[i];    // arr[k++] = left[i++];
        i++;
        k++;
    }
    while(i==Left_Size && j<Right_Size){
        arr[k] = right[j];
        j++;
        k++;
    }  
}


void mergeSort(int arr[],int L,int R){
    if (L == R){   //分到只有一个数的时候
        return;
    }
    else{
        int M = (L+R)/2;
        mergeSort(arr,L,M);
        mergeSort(arr,M+1,R);
        merge(arr,L,M+1,R);
    }   
}

int main(){
    int arr[]={2,8,9,10,4,5,6,7};
    int L = 0;
    int R = 7;
    /* int M = 4;
    merge(arr,L,M,R);
    printArray(arr,R+1);*/

    mergeSort(arr,L,R);
    printArray(arr,R+1);

    return 0;
}
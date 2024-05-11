#include <stdio.h>

//学习资料：https://www.cnblogs.com/shih/p/6613954.html

//打印函数
void printArray(int arr[],int length){
    for (int i=0; i<length; i++)  { printf("%d ",arr[i]); }
    printf("\n");
}

void binaryInsertSort(int arr[], int len) {
    //对每个数据都要进行排序
    for(int i = 1; i < len; i++){
        int key = arr[i];
        int left =0;
        int right = i-1;
        //开始二分查找插入位置
        while(left <= right){
            int mid = (left + right)/2;
            if(arr[mid] > key)        //这个是小到大排序 ，往左边查找    
            //if(arr[mid] < key)      //这个是大到小排序
                right = mid - 1;
            else                      //往右边查找
                left = mid + 1;
        }
        //while循环结束后，找到插入位置left = right
        //把数据往后移动一位，空出插入位置
        for(int j = i-1; j >= left; j--){
            arr[j+1] = arr[j];
        }
        arr[left] = key;
    }
}


int main(){ 
  int i;
  int arr[]={1,5,9,7,8,6,4,11,16,3};
  int len=sizeof(arr)/sizeof(arr[0]);
  printArray(arr,len); 
  
  binaryInsertSort(arr,len);
  printArray(arr,len);
  
  return 0; 	
} 
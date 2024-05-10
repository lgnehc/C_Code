#include <stdio.h>

/*
//这个n是需要插入的第n个数
void insert(int arr[],int n){    
	  int key = arr[n];         
    while(arr[n-1]>key) {
    	arr[n]=arr[n-1];
		  n--;
		  if(n==0)  { break; }		
      } 
	  arr[n]=key;
  }
*/

//小到大排序
void insertionSort(int arr[],int n){
	  for(int i=1; i<n; i++){   //arr[0]不用排序
          //可用insert(arr,i);直接封装
		      int key = arr[i];
          //判断插入位置，从右往左判断插入位置
          while(arr[i-1] > key){
            arr[i] = arr[i-1];
            i--;
            if(i==0)  { break; }
          }
          //循环结束后找到插入的位置
          arr[i] = key;
      }
	}  



int main(){ 
  int i;
  int arr[]={1,5,9,7,8,6,4,11,16,3};
  int num=sizeof(arr)/sizeof(arr[0]); 
  
  insertionSort(arr,num);
  
  for(i=0;i<num;i++){
  	printf("%d  ",arr[i]);
  }
  printf("\n");
  
  return 0; 	
} 
#include <stdio.h>

void insert(int arr[],int n)  //这个n是需要插入的第n个数 
{	                          //判断第n个数的插入 
	int key=arr[n];         
    while(arr[n-1]>key) {
    	arr[n]=arr[n-1];
		n--;
		if(n==0){
		break;
		}		
      } 
	arr[n]=key;
}


void insertionSort(int arr[],int n)   
{
    int i;
	for(i=1;i<n;i++){
		insert(arr,i);
	}  
 } 


int main()

{ 
  
  int i;
  int arr[]={1,5,9,7,8,6,4,11,16,3};
  int num=sizeof(arr)/sizeof(arr[0]); 
  
  insertionSort(arr,num);
  
  for(i=0;i<num;i++)
  {
  	printf("%d\n",arr[i]);
  }
  
  
  return 0; 
	
 } 

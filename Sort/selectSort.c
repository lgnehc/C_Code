#include <stdio.h>

int findMaxPos(int arr[],int n) 
{	
	int i;
	int pos=0;
	int max=arr[0];
	for (i=0;i<n;i++){   
		if(arr[i]>max){
			max=arr[i];
			pos=i;
		}
	}
	return pos;
}

void sellectionSort(int arr[],int n)
{  
    while(n>1){
	  int pos=findMaxPos(arr,n);
	  int tem;
	  tem=arr[pos];
	  arr[pos]=arr[n-1];
	  arr[n-1]=tem;
	  n--;
	}
 } 

int main(){ 
  int i;
  int arr[]={1,5,9,7,8,6,4,11,15,3};
  int num=sizeof(arr)/sizeof(arr[0]); 
  
  sellectionSort(arr,num);
  
  for(i=0;i<num;i++){
  	printf("%d  ",arr[i]);
  }
  printf("\n");
  
  return 0; 	
 } 
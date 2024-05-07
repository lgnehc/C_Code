#include <stdio.h>

void bubble(int arr[],int n) 
{	
	int i;
	int tem;
	for (i=0;i<n-1;i++){   //½»»» 
		if(arr[i]>arr[i+1]){
			tem=arr[i];
			arr[i]=arr[i+1];
			arr[i+1]=tem;
		}
	}
}

void bubblesort(int arr[],int n)
{
	int i;
	for(i=n;i>=1;i--){
		bubble(arr,i);
	}
 } 


int main()

{ 
  
    int i;
	int arr[]={1,5,3,7,6,4,11,22,34} ;
	int num=sizeof(arr)/sizeof(arr[0]);
	bubblesort(arr,num);
	for(i=0; i<num; i++){
	printf("%d\n",arr[i]);}
  
  
  return 0; 
	
 } 

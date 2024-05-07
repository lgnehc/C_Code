#include <stdio.h>

int findmaxpos(int arr[],int num){
	int i;
	int pos=0;
	int max=arr[0];
	for(i=0;i<num;i++){
		if(arr[i]>max){
			max=arr[i];
			pos=i;
		} 
	}
	return pos;
}
 
void sellectionSort(int arr[],int num)
{
	while(num>1){
		int pos=findmaxpos(arr,num);
		int tem;
		tem=arr[num-1];
		arr[num-1]=arr[pos];
		arr[pos]=tem;
		num--;
	
	}
}



int main()

{ 
  
  int i;
  int arr[]={1,5,9,7,8,6,4,11,15,3};
  int num=sizeof(arr)/sizeof(arr[0]); 
  
  sellectionSort(arr,num);
  
  for(i=0;i<num;i++)
  {
  	printf("%d\n",arr[i]);
  }
  
  
  return 0; 
	
 } 

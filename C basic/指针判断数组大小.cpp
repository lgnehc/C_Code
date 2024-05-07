#include <stdio.h>
#include <stdbool.h>

void minmax(int a,int length ,int *pmin,int *pmax);

int main()
{
   int a[]={1,2,3,4,5,6,7,8,9,11,13,16,18,20,25};
   int min,max;
   int length=sizeof(a)/sizeof(a[0]);
   printf("%d\n",length);
  
  //  minmax(a,length,&min,&max);
    printf("min=%d max=%d\n",min,max);
    
	return 0;	
	
 } 
 
 void minmax(int a[],int length,int *pmin,int *pmax)
 {  
    int i=0;
 	*pmin=*pmax=a[0];
 	for(i=0;i<length;i++)
 	{
 		if(a[i]<*pmin)
		 {
 			*pmin=a[i];
		 } else if(a[i]>*pmax)
		   {*pmax=a[i];
		   }
	 }
 
 	
 }

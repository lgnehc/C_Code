#include <stdio.h>

 int search(int key,int a[],int length); 
int main()


{
  int a[]={1,2,3,4,5,6,7,8};
  printf("sizeof(a)=%lu\n",sizeof(a));
  printf("sizeof(a[0])=%lu\n",sizeof(a[0]));
  int length=sizeof(a)/sizeof(a[0]);   //确认数组长度
   
  {                                    //遍历输出数组 
  	int i;
  	for(i=0;i<length;i++)
	  {
	  printf("%d ",a[i]);
	  }
	  printf("\n");
  }
  
  int x;
  int loc;
  
  printf("input a number:");
  scanf("%d",&x) ;
  loc=search(x,a,length);
 
  if(loc!=-1)
  { printf("输入的数字在第%d个位置",loc); }
   else {printf("不在数组中");}
 

	return 0;	
	
 } 
 
 int search(int key,int a[],int length)
 {
 	int ret=-1;
 	int i;
 	for (i=0;i<length;i++){
 		if(key==a[i]){
 			ret=i;
 			break;
		 }
	 }
	 return ret;	
 }

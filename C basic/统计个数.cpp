#include <stdio.h>
#include <stdbool.h>
int main()
{
   const int num=10;
   int i,x;
   int count[num];
   
   for(i=0;i<num;i++){   //数组每个数初始化为0 ，后面有其他赋值方式 
   	count[i]=0;
   }
   
   
   	printf("输入需要统计的数据(-1结束)：");  //统计个数 
    scanf("%d",&x); 
    while(x!=-1) 
	{
		if(x>=0 && x<=9){
		count[x]++ ;	   //数组统计的关键 
		}
     scanf("%d",&x); 
	}
 
   for(i=0;i<num;i++)       //遍历数组输出个数 
   {
   printf("%d:%d\n",i,count[i]);
	} 

    
    
	return 0;	
	
 } 

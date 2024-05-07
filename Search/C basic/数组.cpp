#include <stdio.h>
#include <stdbool.h>


int main()

{
	int x=0;
	int index; 
	double sum=0;
	int cnt=0;
	 printf("输入要求的平均数的个数：") ;
	 scanf("%d",&index);
	 int num[index]; 
	 
	printf("输入%d个数据（输入-1结束）：",index) ;
	scanf("%d",&x);
	
	while(x!=-1){    //输入数据 
	num[cnt]=x;
	sum+=num[cnt];
	cnt++;	
	scanf("%d",&x);	

	}
	
	if(cnt>0){        //计算平均值 
		int i; 
		double average=sum/cnt;
		printf("average=%lf\n",average);
		
		for(i=0;i<cnt;i++)  //判断是否输出 ，因为不能破坏cnt,所以从新定义下标 
		{
		  if(num[i]>average){
		  	printf("大于平均数的有：%d\n",num[i]);
		  }
		
		}
		 
	}
	
    
    
	return 0;	
	
 } 
 


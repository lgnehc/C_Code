#include <stdio.h>
 
 
int main(){
	int num;
	
	
	printf("%9d end\n",12345);    //+强制的意思 
	printf("%09d end\n",12345);   //加0是空位的输出0 
	printf("%+9d end\n",12345);
	printf("%-9d end\n",12345);
	printf("%+-9d end\n",12345);
	printf("%-+9d end\n",12345);
	printf("%e end\n",12345);   //指数输出 ？？？ 
	
	printf("%*d end\n",10,12345); 
	printf("%*.2f end\n",9,123.0);   //包括小数点和后面的小数一共9位 
	
//	printf("%d %n end\n",12345,&num);   //%n是看前面输出了多少个字符 
//	printf("num=%d\n",num);       //这里没有正确输出num值 
	
	{
		int n1,n2; 
		int p1=scanf("%d %d",&n1,&n2);
		//int p2=scanf("%d %d",&n1,&n2);
		int p2=printf("%d\n",n1);  // 空格也算 
		printf("%d %d",p1,p2);   
	}
	
	return 0;
} 

#include <stdio.h>
int main()
{
    char *month[]={"January","February","March","April","May","June",\
	                "July","August","September","October","November","December"};
	                //初始化多个字符串数组 
	int i; 
	char a[][12]={"January","February","March","April","May","June",\
	                "July","August","September","October","November","December",}; 
	              //这个表示每个字符串的长度是12，如果初始化字符超过12会编译失败 
//	char b[][12]={"qwaszxqwaszx"};   //编译失败 
	
	
	printf("输入月份:");
	scanf("%d",&i); 
    printf("%s",month[i-1]); 








  return 0; 
}

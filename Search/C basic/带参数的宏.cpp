#include <stdio.h>

#define  cube(x) ((x)*(x)*(x))             //带参数的宏定义 
#define  MIN(a,b) ((a)>(b) ? (b) : (a))   //带多个参数的宏定义 

int main()
{

	printf("%d \n",cube(5+1));
	printf("%d\n",MIN(3,2));
	return 0;
}  



#include <stdio.h>

#define  cube(x) ((x)*(x)*(x))             //�������ĺ궨�� 
#define  MIN(a,b) ((a)>(b) ? (b) : (a))   //����������ĺ궨�� 

int main()
{

	printf("%d \n",cube(5+1));
	printf("%d\n",MIN(3,2));
	return 0;
}  



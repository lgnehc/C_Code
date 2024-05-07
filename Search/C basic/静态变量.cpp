#include <stdio.h>

void f(void){
 static	int i=2;
	printf("%d\n",i);
	i=i+2;
	
}

int main()
{
	f();
	f();
	f();
	
	return 0;
} 



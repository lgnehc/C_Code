#include <stdio.h>
#include <stdbool.h>
int main()


{
   int a[10]; 
   int i=sizeof(a)/sizeof(a[0]); 
   printf("%d\n",i);
   printf("%p\n",&a);
	printf("%p\n",a);
	printf("%p\n",&a[0]);
	printf("%p\n",&a[1]);
    
    
	return 0;	
	
 } 

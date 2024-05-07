#include <stdio.h>
#include <stdbool.h>
int main()


{
    int count; 
    printf("input a number:");
    scanf("%d",&count) ;
    
	count=(count>20)?count-10:count+10;
	printf("%d",count);
    
    
	return 0;	
	
 } 

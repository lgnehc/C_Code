#include <stdio.h>
#include <math.h>
int main()
/*九九口诀   9*9输出 
{
  int i,j;
  
  for(i=1;i<10;i++){
  	int count=0;
  	
  	for(j=1;j<10;j++){
  	printf("%d*%d=%d",i,j,i*j);
  	if((i*j)<10){
	  printf("   ");
	  }else {printf("  ");
	  }
  	count++;
  	if(count==9) printf("\n");	
  		
	  }
  	
  }
	return 0;	
 }     */
 
 //三角输出 
 {
  int i,j,ji;
  
  for(i=1;i<10;i++){
    j=1;
  	for(j=1;j<=i;j++){	
  	printf("%d*%d=%d",j,i,i*j);
  	if(i*j<10){
	  printf("   ");
	  }else {printf("  ");
	  }	
	  }
  	printf("\n");	
  }
	return 0;	
 } 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()


{
   int num;
   int *a;
   int i;
   
    printf(" ‰»Î ˝¡ø£∫");
    scanf("%d",&num) ;
    a=(int*)malloc(num*sizeof(int));
   for(i=0;i<num;i++){
   	scanf("%d ",&a[i]);
   }
   
   for(i=num-1;i>=0;i--){
   	printf("%d ",a[i]);
   }
   
   free(a);
   

    

	return 0;	
	
 } 
 

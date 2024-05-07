#include <stdio.h>
#include <stdbool.h>

void swap(int *pa,int *pb);
int main()
{
   int a=5;
   int b=6; 
  
   swap(&a,&b);
    printf("a=%d b=%d\n",a,b);
    
    { int c=7;
      int *p;
      p=&c;
      printf("c=%d p=%p\n",c,p);
	}
   
    
	return 0;	
	
 } 
 
 void swap( int *pa,int *pb )
 {
 	int t;
 	t=*pb;
 	*pb=*pa;
 	*pa=t;
 	
 }

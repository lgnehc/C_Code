#include <stdio.h>

 struct point getstruct(void); 
 void output(struct point a);

struct point {
	int x;
	int y;
};
	

int main()
{
    struct point y={0,0};
    y=getstruct();
     //printf("%d %d",y.x,y.y);
   output(y);
	
	return 0;
	
 } 
 
struct point getstruct(void){
 	struct point p;
 	scanf("%d",&p.x);
 	scanf("%d",&p.y);
 	return p;
 }
 
 void output(struct point a)
 {
 printf("%d %d",a.x,a.y);
 
 }

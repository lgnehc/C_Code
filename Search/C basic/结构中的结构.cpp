#include <stdio.h>

struct point{
	int x;
	int y; 
};

struct rectangle
{
struct point point1;
struct point point2;
};

void printRect(struct rectangle r){
 printf("<%d %d> to <%d %d>\n",r.point1.x,r.point1.y,r.point2.x,r.point2.y);
}

int main ()
{
    struct rectangle rects[]={
    	{ {1,1},{3,3} },  //rects[0] 
    	{ {5,5},{7,7} }  //rects[1]
	};
	
	int i;
	for(i=0;i<2;i++){	
	printRect(rects[i]); //printRect(struct rectangle rects[i])---error
}
	
	return 0;

}



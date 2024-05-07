#include <stdio.h>

typedef struct date {
	int year;
	int month;
	int day;
}  aa  ;




int main ()
{
    aa today={2024,3,23};   //µÈÓÚÊÇstruct date today 
	printf("the date is %i-%i-%i\n",today.year,today.month,today.day);	
	return 0;

}



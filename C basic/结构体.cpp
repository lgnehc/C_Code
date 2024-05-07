#include <stdio.h>

struct date {
	int month;
	int day;
	int  year;
};


int main()
{
	struct date today={.month=03, .day=21};
	struct date day={03,21,2024};
	
	struct date day1 ;
	day1=(struct date){03,21,2024};
 //	struct date yestoday;
	//yestoday=(struct date){3,15,2024};
	//yestoday=day;
	//yestoday.year=2015; 

    struct date* p=&day;
	
	printf("today:%i-%i-%i\n",today.month,today.day,today.year);
	printf("day:%d-%d-%d\n",day.month,day.day,day.year);
	//printf("day:%d-%d-%d\n",yestoday.month,yestoday.day,yestoday.year);
	
	printf("adress of day=%p\n",p);
	printf("adress of day=%d\n",*p);
	
	return 0;
	
 } 

#include <stdio.h>

struct date nextmonth(struct date nextmonth);
struct date {
	int year;
	int month;
	int day;
};

struct date dates[]=
{
  {2024,01,01},{2024,01,02},{2024,01,03},{2024,01,04},{2024,01,05}
};




int main ()
{
	int i;
	for(i=0;i<5;i++){
		printf("the date is %i-%i-%i\n",dates[i].year,dates[i].month,dates[i].day);
		dates[i]=nextmonth(dates[i]); 
		printf("the nextmonth is %i-%i-%i\n",dates[i].year,dates[i].month,dates[i].day);
	}
	
	return 0;

}

struct date nextmonth(struct date nextmonth)
{
	nextmonth.month+=1;
	return nextmonth;
}

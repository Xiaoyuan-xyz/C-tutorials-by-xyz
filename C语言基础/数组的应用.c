#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int day_in_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

int get_day_in_year(int year,int month,int day)
{
	int days = 0;
	for (int i = 0; i < month - 1; i++)
	{
		days += day_in_month[i];
	}
	days += month > 2 && (!(year % 400) || (!(year % 4) && (year % 100)));
	days += day;
	return days;
}

int is_leap_year(int year)
{
	return !(year % 400) || (!(year % 4) && (year % 100));
}

int main_szdyy()
{
	int year = 2018;
	int month = 12;
	
	int dy = year - 2019;
	int days = get_day_in_year(year, month, 1);


	int whole_days = dy * 365;

	for (int i = 2019; i < year; i++)
	{
		whole_days += is_leap_year(i);
	}

	for (int i = year; i < 2019; i++)
	{
		whole_days += is_leap_year(i);
	}

	days += whole_days;
	//2019,1,1 是星期二
	days %= 7;
	if (days <= 0)days += 7;
	

	printf("一\t二\t三\t四\t五\t六\t日\n");
	int count = 0;
	for (int i = 0; i < days; i++)
	{
		printf("\t");
		count++;
	}
	int need_day = day_in_month[month - 1];
	for (int i = 1; i <= need_day; i++)
	{
		printf("%d\t",i);
		count++;
		if (!(count % 7))printf("\n");
	}

	return 0;
}
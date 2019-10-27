#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>

int main_zz1()
{
	int a = 97;

	int* p = &a;

	int** pp = &p;

	printf("%p\n", p);

	printf("%p\n", &p);

	printf("%p\n", &pp);

	int***** p5;
	int****** p6 = &p5;


	return 0;
}


int main_zz2()
{
	/*
	int a = 50;

	int* p = &a;

	int** pp = &p;
	*/

	int a = 50, *p = &a, **pp = &p;

	printf("%d\n", a);
	printf("%d\n", *p);
	printf("%d\n", **pp);

	//printf("%p\n", &(a+1));
	//printf("%p\n", &&a));

	return 0;
}

int main_zz3()
{
	int a = 50;
	int* p = &a;
	
	*p = 40;
	printf("%d", a);

	return 0;
}
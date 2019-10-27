#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int main_zzz2()
{
	/*
	int x = 5, y = 10;
	swap(&x, &y);
	printf("x=%d y=%d\n", x, y);

	
	int* p;
	//p = 12345;
	p = NULL;
	if (p != NULL)
	{
		printf("%d", *p);
	}
	int a = 10;
	int b = 20;

	int* p = &a;
	*p = 30;
	p = &b;
	*p = 40;
	printf("a=%d b=%d\n", a, b);


	const int x = 30;

	//x = 40;

	int* p = &x;
	*p = 40;
	printf("%d", x);


	int a = 30;
	int b = 50;
	const int* p = &a;

	a = 40;
	//*p = 50;

	p = &b;
	*p = 60;

	int a = 10, b = 20;

	int * const p = &a;

	a = 30;
	*p = 40;
	//p = &b;

	*/
	const int a = 10;
	//a = 20;
	int const* const p = &a;

	//p = NULL;
	//*p = 20;

	int** pp = &p;
	*pp = NULL;


	return 0;
}

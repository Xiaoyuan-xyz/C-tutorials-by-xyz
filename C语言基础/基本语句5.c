#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define HELLO printf("hello world");

#define SQR(x) ((x)*(x))

int main_define()
{
	/*
	if (1)
		HELLO;
	else 
	{
	
	}
	*/
	
	//printf("%d", 2000/SQR(10));
	//printf("%d", 2000/10*10);
	//printf("%d", 10+1*10+1);
	//printf("%d", 10 * 10);;

	//printf("%d", max(3, 5));

	int x, y;
	scanf("%d%d", &x, &y);
	int m = max(x,y);

	if (x > y)m = x;
	else m = y;
	printf("\n%d", m);

	int this_is_a_int;
	int thisIsAInt;
	int int1;
	int int2;
	int _a;
	//int if;

	return 0;
}


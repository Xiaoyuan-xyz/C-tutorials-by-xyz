#include <stdio.h>
#include <stdlib.h>

int main_dygcx()
{
	/*
	printf("Hello World!");
	system("pause");
	return 0;
	printf("Hello World!2");
	*/
	int a = 0;
	int b = 0;
	while (a < 5)
	{
		a = a + 1;
		b = b + a;
	}
	printf("%d", b);
	return 0;
}
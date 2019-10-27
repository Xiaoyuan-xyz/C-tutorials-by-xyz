#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main_skdyx()
{
	/*
	int a;
	int b;
begin:
	scanf("%d", &a);
	if (a < 0)
	{
		goto ltzero;
	}
print:
	printf("%d", a);
	goto begin;
ltzero:
	b = a;
	a = a - b;
	a = a - b;
	goto print;

	return 0;
	*/

	while (1)
	{
		int a;
		scanf("%d", &a);
		if (a < 0)
		{
			a = -a;
		}
		printf("%d", a);
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main_jbyjfx()
{
	int x;
	while (1)
	{
	begin:
		scanf("%d", &x);
		if (x % 6 != 1 && x % 6 != 5)
		{
			printf("%d�Ǻ���", x);
			continue;
		}
		if (x == 2 || x == 3)
		{
			printf("%d������", x);
			continue;
		}
		int tmp = (int)sqrt(x);
		for (int i = 5; i <= tmp; i += 6)
			if (x % i == 0 || x % (i + 2) == 0)
			{
				printf("%d�Ǻ���", x);
				goto begin;
			}
		printf("%d������", x);	
	}
	return 0;
}
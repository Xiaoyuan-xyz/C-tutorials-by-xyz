#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main_kfcs1()
{
	int x;
	int times = 0;
	scanf("%d", &x);
	times++;
	while (x < 0)
	{
		scanf("%d", &x);
		times++;
	}
	printf("������������%d����������%d��������������һ���ܿ�������", x, times);
	return 0;
}

int main_dhbdsdyy()
{
	int x;
	int times = 0;
	while (scanf("%d", &x), times++, x < 0)
		;
	printf("������������%d����������%d��������������һ���ܿ�������", x, times);
	return 0;
}

int main_dhbds()
{
	//int x = (3 + 1, 4 + 5, 10 + 10);

	int x, y, z;
	x = 1;
	y = 1;
	z = x++, y++, ++y;
	printf("%d,%d,%d\n", x, y, z);

	return 0;
}

int main_ctn()
{
	int x;
	int times = 0;
	while (1)
	{
		scanf("%d", &x);
		times++;
		if (x < 0)
			continue;
		break;
	}
	printf("������������%d����������%d��������������һ���ܿ�������", x, times);
	return 0;
}

int main_sxhx()
{
	int i = 100;
	for (int i = 100; i < 1000; i++)
	{
		int b = i / 100;
		int g = i % 10;
		int s = (i / 10) % 10;

		if (i == b * b * b + g * g * g + s * s * s)
		{
			break;
		}
	}
	printf("%d\t", i);
	return 0;
}


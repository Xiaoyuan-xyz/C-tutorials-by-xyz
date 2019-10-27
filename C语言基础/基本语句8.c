#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>

int x;

int jiaogu(int x)
{
	if (x % 2)
	{
		x *= 3;
		x++;
	}
	else
	{
		x /= 2;
	}
	return x;
}

int main_hs()
{
	int x;
	scanf("%d", &x);
	while (x != 1)
	{
		x = jiaogu(x);
		printf("%d\t", x);
	}
	return 0;
}

int jc(int x)
{
	if (x == 1) return 1;
	return x * jc(x - 1);
}

int main_jc()
{
	int x, p = 1;
	scanf("%d", &x);
	printf("%d\t", jc(x));
	return 0;
}

void hs_10to2(int);



int main_10to2()
{
	int x;
	scanf("%d", &x);

	hs_10to2(x);
	return 0;
}

void hs_10to2(int x)
{
	if (x > 1) hs_10to2(x >> 1);
	printf("%d", x % 2);
}

void count(void)
{
	static int i = 0;
	printf("%d", i++);
}

int main_static()
{
	int x;
	scanf("%d", &x);
	while (x)
	{
		count();
		x--;
	}
}

void swap_8(int x, int y)
{
	int t;
	t = x;
	x = y;
	y = t;
}


int main_jh()
{
	int a = 10, b = 20;
	swap_8(a, b);
	printf("%d %d", a, b);
	return 0;
}
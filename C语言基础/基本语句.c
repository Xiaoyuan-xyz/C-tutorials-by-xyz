#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main_jbyj()
{
	printf("Hello world!\\n\n");

	//printf("x的十进制是 %d，x的八进制是 %o", x, x);
	/*
	int x = -5;
	int y = -3;

	printf("5+3=%d,5-3=%d,5*3=%d,5/3=%d,-5%%-3=%d"
		, x + y, x - y, x * y, x / y, x % y);
	*/

	/*
	int x;
	int y;
	printf("请输入x：");
	scanf("%d", &x);
	printf("请输入y：");
	scanf("%d", &y);
	printf("x+y=%d", x+y);

	scanf("请输入x：%d", &x);
	printf("x=%d", x);
	*/

	/*
	int x;
	int y;

	scanf("%d%d", &x, &y);
	printf("x=%d,y=%d", x, y);
	*/

	int x;
	int y = 0;
	scanf("%d", &x);

	if (x < 0)
	{
		printf("-");
		x = -x;
	}
	else if (x == 0)
	{
		printf("%d", 0);
	}

	while (x != 0)
	{
		y = x % 10;
		printf("%d", y);
		x = x / 10;
	}

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main_gth()
{
	int x = 10;
	int s;
	//scanf("%d", &x);
	//printf("%d", (int)3.5);
	//printf("%d", sizeof(x));
	printf("%d", x << 2);
	//0是假  除0以外所有数 都是真 默认是1
	if (!(10%5))
	{

	}
	//!10%5 = 0%5 = 0
	//!(10%5) = !0 1

	return 0;
}

int main_yhf()
{
	int x;
	scanf("%d", &x);
	int flag = 0;
	/*
	if (!(x % 4))
		flag = 1;
	if (!(x % 100))
		flag = 0;
	if (!(x % 400))
		flag = 1;
*/
	flag = !(x % 400) || !(x % 4) && x % 100;

	1||1 / 0;//短路
	0 && 1 / 0;

	printf("%d 是闰年吗：%d", x, flag);

	return 0;
}

int main_fzd()
{
	int x = 10;
	x = x * 3;
	x *= 3;

	x = x << 1;
	x <<= 1;
	return 0;
}

int main_yhfw()
{
	//4 100 
	//5 101
	4 & 5; //100

	//0&0=0
	//0&1=0
	//1&0=0
	//1&1=1

	//0|0=0
	//0|1=1
	//1|0=1
	//1|1=1

	//0^0=0
	//0^1=1
	//1^0=1
	//1^1=0

	printf("%u", ~5);
	unsigned int x;
	unsigned char c;

	return 0;
}
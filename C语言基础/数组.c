#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#if 0
int main_sz1()
{
	int x[50];//À¬»ø
	int y[4] = { 1,2,3,4 };
	int z[5] = { 1,2,3,4 };//1,2,3,4,0
	int w[5] = { 0 };
	//int u[3] = { 1,2,3,4 };
	int v[] = { 1,2,3,4 };//int v[4] = {1,2,3,4};

	//printf("%d", z[4]);

	for (int i = 0; i < sizeof(z) / sizeof(z[0]); i++)
	{
		printf("%d\t", z[i]);
	}

	int num;

	return 0;
}

int main_sz2()
{
	int x[10] = { 0 };

	printf("sizeof(x)=%d\n", sizeof(x));
	printf("sizeof(x[0])=%d\n", sizeof(x[0]));

	return 0;
}

int main_sz3()
{
	int fbnq[10] = { 0 };
	fbnq[1] = fbnq[0] = 1;
	for (int i = 2; i < 10; i++)
	{
		fbnq[i] = fbnq[i - 1] + fbnq[i - 2];
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d\t", fbnq[i]);
	}


	return 0;
}
#endif
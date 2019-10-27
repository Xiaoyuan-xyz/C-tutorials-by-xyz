#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main_sz3()
{
#if 1
	int x[2][3];
	int y[2][3] = { 1,2,3,4,5,6 };//1,2,3  ,4,5,6
	int z[2][4] = { 1,2,3,4,5,6 };//1,2,3,4,  5,6,0,0,
	int w[][4] = { 1,2,3,4,5,6 };//1,2,3,4,  5,6,0,0
	//int u[2][] = { 1,2,3,4,5,6 };
	//int v[][] = { 1,2,3,4,5,6 };
	int u[][4] =
	{
		{1,2},
		{3,4,5},
		{6}
	};//1,2,0,0   3,4,5,0  6,0,0,0

	for (int i = 0; i < sizeof(z)/ sizeof(z[0]); i++)
	{
		for (int j = 0; j < sizeof(z[0])/ sizeof(z[0][0]); j++)
		{
			printf("%d\t", *(*(z+i)+j));
		}
		printf("\n");
	}
#endif
	return 0;
}

int main_sz33()
{
	int z[2][4] = { 1,2,3,4,5,6 };//1,2,3,4,  5,6,0,0,
	//printf("%d\n", sizeof(z));
	//printf("%d\n", sizeof(z[0]));
	//printf("%d\n", sizeof(z[0][0]));

	//int* p = z;
	//printf("%p\n", z);
	//printf("%p\n", p);
	//printf("%p\n", z+1);
	//printf("%p\n", p+1);
	//printf("%p\n", &z);
	//printf("%p\n", &z+1);
	//printf("%p\n", *z);
	//printf("%p\n", *z+1);

	//x[1] (*x+1)

	//y[1][2] (*y+1)[2] (*(*y+1)+2)

	int (*p)[4] = z;

	//int a[] int* p
	//int a[][10] int[]* p 

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void show(int* array,int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d\t", array[i]);
		//printf("%d\t", *array);
	}
}

int main1_sz2()
{
	int x[4] = { 1,2,3,4 };
	show(x,4);
	
	int* p = &x[1];
	//printf("%p\n", p);
	//printf("%p\n", x);
	//printf("%p\n", &x);
	//printf("%p\n", &x[1]);
	//printf("%p\n", &x[2]);
	//printf("%p\n", p+1);
	//printf("%p\n", x+1);
	//printf("%p\n", &x+1);
	//printf("%p\n", p+1);


	printf("%d\n", p[1]);
	printf("%d\n", p[-1]);
	printf("%d\n", 1[p]);

	//p[i] *(p+i) 
	//i[p] *(i+p)
	

	return 0;
}
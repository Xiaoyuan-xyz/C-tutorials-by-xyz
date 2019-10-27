#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include <limits.h>
#include <float.h>

enum Direction
{
	NORTH,WEST,SOUTH,EAST
};

int main_double()
{

	enum Direction dir = NORTH;

	if (dir == NORTH)
	{
		printf("north");
	}

	switch (dir)
	{
	case NORTH:
		printf("north");
		break;
	case WEST:
		printf("west");
		break;
	case SOUTH:
		printf("south");
		break;
	case EAST:
		printf("east");
		break;
	}




	float d = (double)3;
	//short x;
	long y = 3;
	//long long z;

	printf("%3.3f", d);


	return 0;
}

int main_switch()
{
	int x;
	scanf("%d", &x);

	switch (x)
	{
	case 2:
	case 3:
	case 5:
	case 7:
		printf("是质数");
		break;
	case 4:
	case 6:
	case 8:
	case 9:
		printf("是合数");
		break;
	default:
		printf("我不知道");
	}

	return 0;
}
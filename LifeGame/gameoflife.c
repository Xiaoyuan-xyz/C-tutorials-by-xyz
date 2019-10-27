#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define WIDTH 40 //wide x j
#define HIGTH 30 //high y i
//map[HIGTH][WIDTH] map[i][j] map[y][x]

//声明地图
char map[HIGTH][WIDTH] = {
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	1,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,
0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	0,	0,	0,	0,
0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	1,	1,	1,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
};
int loop;

int count_cell(int x, int y)
{
	int cell = 0;

	if (x == 0)
	{
		cell += map[y][x + 1];
		if (y > 0)cell += map[y - 1][x] + map[y - 1][x + 1];
		if (y < HIGTH-1)cell += map[y + 1][x] + map[y + 1][x + 1];
	}
	else if (x == WIDTH - 1)
	{
		cell += map[y][x - 1];
		if (y > 0)cell += map[y - 1][x] + map[y - 1][x - 1];
		if (y < HIGTH - 1)cell += map[y + 1][x] + map[y + 1][x - 1];
		
	}
	else
	{
		cell += map[y][x - 1];
		cell += map[y][x + 1];
		if (y > 0)cell += map[y - 1][x] + map[y - 1][x + 1] + map[y - 1][x - 1];
		if (y < HIGTH - 1)cell += map[y + 1][x] + map[y + 1][x + 1] + map[y + 1][x - 1];
	}
	return cell;
}

void init_map()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < HIGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			map[i][j] = rand() % 2;
		}
	}
}

void update_map()
{
	char map2[HIGTH][WIDTH] = { 0 };
	int cell;
	for (int i = 0; i < HIGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cell = count_cell(j,i);
			map2[i][j] = cell == 3 || cell == 2 && map[i][j];
		}
	}
	memcpy(map, map2, HIGTH * WIDTH * sizeof(char));
}

void print_map()
{
	//system("CLS");
	for (int i = 0; i < HIGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j])printf("■");
			else printf("  ");
		}
		puts("");
	}
	printf("loop:%d", loop++);
}

int main()
{
	//获取句柄等操作
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD zero = { 0,0 };
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &cci);

	//初始化地图
	//init_map();

	while (1)
	{
		//让光标到最开始的地方
		SetConsoleCursorPosition(handle, zero);
		//绘制地图
		print_map();
		//计算地图
		update_map();
		//getchar();
		//Sleep(1000);
	}

	return 0;
}
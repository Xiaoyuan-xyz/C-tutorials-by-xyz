#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define HIGTH 30 //high y 10 i
#define WIDTH 40 //wide x 20 j
#define CHANCE 10

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
int loop = 0;

void show()
{
	//system("CLS");
	for (int i = 0; i < HIGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j]) printf("¡ö");
			else printf("  ");
		}
		puts("");
	}
	printf("loop:%d", loop++);
}

int get_cell(int x,int y)
{
	int cell = 0;
	if (x == 0)
	{
		cell += map[y][1];
		if (y > 0)cell += map[y - 1][0]+map[y-1][1];
		if (y < HIGTH - 1)cell += map[y + 1][0]+map[y+1][1];
	}
	else if (x == WIDTH - 1)
	{
		cell += map[y][x - 1];
		if (y > 0)cell += map[y - 1][x]+ map[y - 1][x-1];
		if (y < HIGTH - 1)cell += map[y + 1][x]+ map[y + 1][x-1];
	}
	else 
	{
		cell += map[y][x + 1];
		cell += map[y][x - 1];
		if (y > 0)cell += map[y - 1][x]+ map[y - 1][x - 1]+ map[y - 1][x + 1];
		if (y < HIGTH - 1)cell += map[y + 1][x]+ map[y + 1][x-1]+ map[y + 1][x+1];
	}
	return cell;
}

void flush_map()
{
	char map2[HIGTH][WIDTH] = { 0 };
	int cell = 0;
	for (int i = 0; i < HIGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cell = get_cell(j, i);
			map2[i][j] = cell == 3 || cell == 2 && map[i][j];
		}
	}
	memcpy(map, map2, HIGTH * WIDTH * sizeof(char));
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

int main_ready()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD zero = { 0,0 };
start:
	loop = 0;
	system("CLS");
	//init_map();
	while (1)
	{
		SetConsoleCursorPosition(handle, zero);
		show();
		flush_map();
		//Sleep(1000);
		//getchar();
		//while (_kbhit())
		//{	
		//	goto start;
		//}
	}
	return 0;
}
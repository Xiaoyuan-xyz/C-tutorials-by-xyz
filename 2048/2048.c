#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

int map[4][4] = { 0 };
char key;
HANDLE hdl;

void init();
int move_up();
int move_down();
int move_left();
int move_right();
void update_screen();
void generate();
int fail_check();

int main()
{
	init();
	while (1)
	{
		key = _getch();
		int flag = 0;
		switch (key)
		{
		case 'W':case 'w':
			flag = move_up();
			break;
		case 'A':case 'a':
			flag = move_left();
			break;
		case 'S':case 's':
			flag = move_down();
			break;
		case 'D':case 'd':
			flag = move_right();
			break;
		case -32:
			key = _getch();
			switch (key)
			{
			case 72:
				flag = move_up();
				break;
			case 80:
				flag = move_down();
				break;
			case 75:
				flag = move_left();
				break;
			case 77:
				flag = move_right();
				break;
			}
		}
		if (flag == 0)continue;
		generate();
		update_screen();
		if (fail_check())break;
	}
	return 0;
}

void update_screen()
{
	COORD zeros = { 0,0 };
	SetConsoleCursorPosition(hdl,  zeros);
	printf("©°©¤©¤©¤©¤©¤©¤©¤©Ð©¤©¤©¤©¤©¤©¤©¤©Ð©¤©¤©¤©¤©¤©¤©¤©Ð©¤©¤©¤©¤©¤©¤©¤©´\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)printf("©¦       ");
			else if (map[i][j] < 100)printf("©¦   %2d  ", map[i][j]);
			else if (map[i][j] < 10000)printf("©¦  %4d ", map[i][j]);
			else if (map[i][j] < 1000000)printf("©¦ %6d", map[i][j]);
			else  printf("©¦%7d", map[i][j]);
		}
		printf("©¦\n");
		if(i<3) printf("©À©¤©¤©¤©¤©¤©¤©¤©à©¤©¤©¤©¤©¤©¤©¤©à©¤©¤©¤©¤©¤©¤©¤©à©¤©¤©¤©¤©¤©¤©¤©È\n");
		else printf("©¸©¤©¤©¤©¤©¤©¤©¤©Ø©¤©¤©¤©¤©¤©¤©¤©Ø©¤©¤©¤©¤©¤©¤©¤©Ø©¤©¤©¤©¤©¤©¤©¤©¼\n");
	}
}

void init()
{
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci = { 1,0 };
	SetConsoleCursorInfo(hdl, &cci);
	SetConsoleTitle("2048!!!");
	srand((unsigned)time(NULL));
	map[rand() % 4][rand() % 4] = 2;
	generate();
	update_screen();
}

void generate()
{
	int empty[16] = { 0 };
	int empty_num = 0;
	int count = 0;
	for (int* p = map; p < map + 16; p++)
	{
		if (*p == 0)empty[count++] = p - map;
	}
	*map[empty[rand() % count]] = rand() % 10 == 0 ? 4 : 2;
}

int move_right()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j >= 0; j--)
		{


		}
	}
}

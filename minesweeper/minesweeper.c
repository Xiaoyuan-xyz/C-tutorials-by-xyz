#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define WIDTH 20//x j
#define HIGTH 16//y i
//[HIGTH][WIDTH] [y][x] [i][j] [16][20]
#define MINE_NUM 32

typedef enum Block
{
	AIR, MINE, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, FLAG, FLAG_AND_MINE
}BLOCK;

char* element[] = { "□", "□", "  ", "①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "☆", "★" };

typedef enum Action
{
	MOVE,LEFT,MIDDLE,RIGHT
}ACTION;

BLOCK map[HIGTH + 2][WIDTH + 2] = { 0 };//[1][1] 到[HIGTH][WIDTH]
HANDLE hdl;
COORD guy = { 1,1 };
COORD guy_old = { 1,1 };

void print_map();
void draw_player();
void generate();
ACTION get_action();
void update(COORD);
int left_event(int y,int x);
void middle_event(int y,int x);
void right_event(int y,int x);
int caculate(int y, int x);
int is_legal(int y, int x);
int caculate_flag(int y, int x);

int main()
{
	//游戏初始化
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci = { 1,0 };
	SetConsoleCursorInfo(hdl, &cci);
	SetConsoleTitle("MINESWEEPR!!!");

	//生成地图
	generate();

	//打印地图
	print_map();
	draw_player();

	while (1)
	{
		//获取按键
		//get_action()包含对guy的移动 返回Action
		switch (get_action())
		{
		case MOVE:
			update(guy_old);
			draw_player();
			break;
		case LEFT:
			left_event(guy.Y,guy.X);
			if (map[guy.Y][guy.X] == ZERO)draw_player();
			break;
		case MIDDLE:
			middle_event(guy.Y, guy.X);
			break;
		case RIGHT:
			right_event(guy.Y, guy.X);
			break;
		}
	}

	return 0;
}

void print_map()
{
	for (int i = 1; i <= HIGTH; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			printf("□");
		}
		puts("");
	}
}

void draw_player()
{
	COORD pos;
	pos.X = (guy.X - 1) * 2;
	pos.Y = guy.Y - 1;
	SetConsoleCursorPosition(hdl, pos);
	printf("♀");
}

void generate()
{
	srand((unsigned)time(NULL));
	int x, y;
	for (int i = 0; i < MINE_NUM; i++)
	{
		x = rand() % WIDTH;
		y = rand() % HIGTH;
		if (map[y + 1][x + 1] == AIR)
		{
			map[y + 1][x + 1] = MINE;
		}
	}
}

ACTION get_action()
{
	guy_old = guy;
	char key = _getch();
	switch (key)
	{
	case 'W':case 'w':
		if (guy.Y > 1)guy.Y--;
		break;
	case 'A':case 'a':
		if (guy.X > 1)guy.X--;
		break;
	case 'S':case 's':
		if (guy.Y < HIGTH)guy.Y++;
		break;
	case 'D':case 'd':
		if (guy.X < WIDTH)guy.X++;
		break;
	case 'Z':case 'z':
		return LEFT;
	case 'X':case 'x':
		return MIDDLE;
	case 'C':case 'c':
		return RIGHT;
	case -32:
		key = _getch();
		switch (key)
		{
		case 72:
			if (guy.Y > 1)guy.Y--;
			break;
		case 80:
			if (guy.Y < HIGTH)guy.Y++;
			break;
		case 75:
			if (guy.X > 1)guy.X--;
			break;
		case 77:
			if (guy.X < WIDTH)guy.X++;
			break;
		}
	}
	return MOVE;
}

void update(COORD pos)
{
	COORD pos_on_screen = { (pos.X - 1) * 2 ,pos.Y - 1 };
	SetConsoleCursorPosition(hdl, pos_on_screen);
	printf("%s", element[map[pos.Y][pos.X]]);
}

int left_event(int y, int x)
{
	int count;
	COORD pos = { x,y };
	switch (map[y][x])
	{
	case AIR:
		count = caculate(y, x);
		map[y][x] = count + ZERO;
		update(pos);
		if (count == 0)
		{
			if (is_legal(y - 1, x - 1))left_event(y - 1, x - 1);
			if (is_legal(y + 1, x - 1))left_event(y + 1, x - 1);
			if (is_legal(y - 1, x + 1))left_event(y - 1, x + 1);
			if (is_legal(y + 1, x + 1))left_event(y + 1, x + 1);
			if (is_legal(y - 1, x))left_event(y - 1, x);
			if (is_legal(y + 1, x))left_event(y + 1, x);
			if (is_legal(y, x - 1))left_event(y, x - 1);
			if (is_legal(y, x + 1))left_event(y, x + 1);
		}
		break;
	case MINE:
		return -1;
	}
	return 0;
}

void middle_event(int y, int x)
{
	if (map[y][x] >= ZERO && map[y][x] <= EIGHT)
	{
		int should = map[y][x] - ZERO;
		int count = caculate_flag(y, x);
		if (should == count)
		{
			if (is_legal(y - 1, x - 1))left_event(y - 1, x - 1);
			if (is_legal(y + 1, x - 1))left_event(y + 1, x - 1);
			if (is_legal(y - 1, x + 1))left_event(y - 1, x + 1);
			if (is_legal(y + 1, x + 1))left_event(y + 1, x + 1);
			if (is_legal(y - 1, x))left_event(y - 1, x);
			if (is_legal(y + 1, x))left_event(y + 1, x);
			if (is_legal(y, x - 1))left_event(y, x - 1);
			if (is_legal(y, x + 1))left_event(y, x + 1);
		}
	}
}

void right_event(int y, int x)
{
	COORD pos = { x,y };
	if (map[y][x] >= FLAG)
	{
		map[y][x] -= FLAG;
		update(pos);
	}
	else if (map[y][x] <= MINE)
	{
		map[y][x] += FLAG;
		update(pos);
	}
}

int caculate(int y, int x)
{
	int count = 0;
	if (map[y - 1][x - 1] == MINE || map[y - 1][x - 1] == FLAG_AND_MINE)count++;
	if (map[y - 1][x + 1] == MINE || map[y - 1][x + 1] == FLAG_AND_MINE)count++;
	if (map[y + 1][x - 1] == MINE || map[y + 1][x - 1] == FLAG_AND_MINE)count++;
	if (map[y + 1][x + 1] == MINE || map[y + 1][x + 1] == FLAG_AND_MINE)count++;
	if (map[y - 1][x] == MINE || map[y - 1][x] == FLAG_AND_MINE)count++;
	if (map[y + 1][x] == MINE || map[y + 1][x] == FLAG_AND_MINE)count++;
	if (map[y][x - 1] == MINE || map[y][x - 1] == FLAG_AND_MINE)count++;
	if (map[y][x + 1] == MINE || map[y][x + 1] == FLAG_AND_MINE)count++;
	return count;
}

int is_legal(int y, int x)
{
	return x >= 1 && x <= WIDTH && y >= 1 && y <= HIGTH && map[y][x] <= MINE;
}

int caculate_flag(int y, int x)
{
	int count = 0;
	if (map[y - 1][x - 1] >= FLAG)count++;
	if (map[y - 1][x + 1] >= FLAG)count++;
	if (map[y + 1][x - 1] >= FLAG)count++;
	if (map[y + 1][x + 1] >= FLAG)count++;
	if (map[y - 1][x] >= FLAG)count++;
	if (map[y + 1][x] >= FLAG)count++;
	if (map[y][x - 1] >= FLAG)count++;
	if (map[y][x + 1] >= FLAG)count++;
	return count;
}
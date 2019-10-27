#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define WIDTH 20//x j
#define HIGTH 16//y i
//[y][x]  [HIGTH][WIDTH]  [i][j]  [20][16]
#define RATE 0.2

typedef enum Block
{
	AIR, MINE, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, FLAG, FLAG_AND_MINE
}Block;
char* element[] = { "□","□","  ","①","②","③","④","⑤","⑥","⑦","⑧","☆","★" };
typedef enum Action
{
	MOVE, LEFT, RIGHT, MIDDLE
}Action;

//初始化全局变量
Block map[HIGTH+2][WIDTH+2] = { 0 };//真正含雷的范围是1,1到HIGTH,WIDTH
COORD guy = { 1,1 };
COORD guyOld = { 1,1 };
HANDLE hdl;

void generate(void)
{
	//随机数种子初始化
	srand((unsigned)time(NULL));
	int mineTotal = (int)(WIDTH * HIGTH * RATE);//32
	int tmpY, tmpX;
	for (int i = 0; i < mineTotal; )
	{
		tmpY = rand() % HIGTH;//0,HIGTH-1
		tmpX = rand() % WIDTH;//0,WIDTH-1
		if (map[tmpY+1][tmpX+1] == MINE)//1,HIGTH
		{
			continue;
		}
		map[tmpY+1][tmpX+1] = MINE;
		i++;
	}
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

void draw_player(COORD pos)
{
	pos.X--;
	pos.Y--;
	pos.X <<= 1;
	SetConsoleCursorPosition(hdl, pos);
	printf("♀");
}

Action get_action()
{
	guyOld = guy;
	char keyPress = _getch();
	switch (keyPress)
	{
	case 'W':
	case 'w':
		if (guy.Y > 1)
		{
			guy.Y--;
		}
		break;
	case 'A':
	case 'a':
		if (guy.X > 1)
		{
			guy.X--;
		}
		break;
	case 'S':
	case 's':
		if (guy.Y < HIGTH)
		{
			guy.Y++;
		}
		break;
	case 'D':
	case 'd':
		if (guy.X < WIDTH)
		{
			guy.X++;
		}
		break;
	case -32:
		keyPress = _getch();
		switch (keyPress)
		{
		case 77:
			if (guy.X < WIDTH)
			{
				guy.X++;
			}
			break;
		case 75:
			if (guy.X > 1)
			{
				guy.X--;
			}
			break;
		case 72:
			if (guy.Y > 1)
			{
				guy.Y--;
			}
			break;
		case 80:
			if (guy.Y < HIGTH)
			{
				guy.Y++;
			}
			break;
		}
		break;
	case 'Z':
	case 'z':
		return LEFT;
	case 'X':
	case 'x':
		return MIDDLE;
	case 'C':
	case 'c':
		return RIGHT;
	}
	return MOVE;
}

void update(COORD pos)
{
	COORD pos_on_screen = { (pos.X - 1) << 1,pos.Y - 1 };
	SetConsoleCursorPosition(hdl, pos_on_screen);
	printf("%s", element[map[pos.Y][pos.X]]);
}

int sub_calculate(int y, int x)
{
	int count = 0;
	if (map[y - 1][x] == MINE || map[y - 1][x] == FLAG_AND_MINE)count++;
	if (map[y + 1][x] == MINE || map[y + 1][x] == FLAG_AND_MINE)count++;
	if (map[y][x] == MINE || map[y][x] == FLAG_AND_MINE)count++;
	return count;
}

int calculate(int y, int x)
{
	int count = 0;
	count += sub_calculate(y, x);
	count += sub_calculate(y, x - 1);
	count += sub_calculate(y, x + 1);
	return count;
}

int is_legal(int y, int x)
{
	return x > 0 && x <= WIDTH && y > 0 && y <= HIGTH;
}

int left_event(int y, int x)
{
	int count = 0;
	COORD pos = { x,y };
	switch (map[y][x])
	{
	case AIR:
		//计算周围雷数
		count = calculate(y, x);
		map[y][x] = count + ZERO;
		update(pos);
		//如果雷数==0 递归调用本函数
		if (count == 0)
		{
			if (is_legal(y - 1, x - 1))left_event(y - 1, x - 1);
			if (is_legal(y - 1, x))left_event(y - 1, x);
			if (is_legal(y - 1, x + 1))left_event(y - 1, x + 1);
			if (is_legal(y, x + 1))left_event(y, x + 1);
			if (is_legal(y + 1, x + 1))left_event(y + 1, x + 1);
			if (is_legal(y + 1, x))left_event(y + 1, x);
			if (is_legal(y + 1, x - 1))left_event(y + 1, x - 1);
			if (is_legal(y, x - 1))left_event(y, x - 1);
		}

		//调用结束后 将计算结果显示

		return 1;
	case MINE:
		//游戏结束
		return -1;
	}
	return 0;

}

int sub_calculate_flag(int y, int x)
{
	int count = 0;
	if (map[y - 1][x] >= FLAG)count++;
	if (map[y + 1][x] >= FLAG)count++;
	if (map[y][x] >= FLAG)count++;
	return count;
}

int calculate_flag(int y, int x)
{
	int count = 0;
	count += sub_calculate_flag(y, x);
	count += sub_calculate_flag(y, x - 1);
	count += sub_calculate_flag(y, x + 1);
	return count;
}

int is_flag_legal(int y, int x)
{
	return is_legal(y, x) && map[y][x] <= MINE;
}

void area_clear(int y, int x)
{
	if (map[y][x] >= ONE && map[y][x] <= EIGHT)
	{
		int should = map[y][x] - ZERO;
		int count = calculate_flag(y, x);
		if (should == count)
		{
			if (is_flag_legal(y - 1, x - 1))left_event(y - 1, x - 1);
			if (is_flag_legal(y - 1, x))left_event(y - 1, x);
			if (is_flag_legal(y - 1, x + 1))left_event(y - 1, x + 1);
			if (is_flag_legal(y, x + 1))left_event(y, x + 1);
			if (is_flag_legal(y + 1, x + 1))left_event(y + 1, x + 1);
			if (is_flag_legal(y + 1, x))left_event(y + 1, x);
			if (is_flag_legal(y + 1, x - 1))left_event(y + 1, x - 1);
			if (is_flag_legal(y, x - 1))left_event(y, x - 1);
		}
	}
}

int main()
{
	//游戏初始化
	SetConsoleTitle("MINE SWEEPER!");
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info = { 1,0 };
	SetConsoleCursorInfo(hdl, &info);

	//生成地图
	generate();

	//初始化地图
	print_map();
	draw_player(guy);
	while (1)
	{
		//get_action包含了返回按键和移动guy的位置
		Action act = get_action();
		//按键选择
		switch (act)
		{
		case MOVE:
			update(guyOld);
			draw_player(guy);
			break;
		case LEFT:
			left_event(guy.Y, guy.X);
			if (map[guy.Y][guy.X] == ZERO)
			{
				draw_player(guy);
			}
			break;
		case MIDDLE:
			area_clear(guy.Y, guy.X);
			break;
		case RIGHT:
			if (map[guy.Y][guy.X] <= MINE)
			{
				map[guy.Y][guy.X] += FLAG;
				update(guyOld);
			}
			else if (map[guy.Y][guy.X] >= FLAG)
			{
				map[guy.Y][guy.X] -= FLAG;
				update(guyOld);
			}
			break;
		}
	}
}
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define WIDTH 10//x j
#define HIGTH 25//y i
//[y][x]  [HIGTH][WIDTH]  [i][j]  [20][10]
#define TICK 1000
#define COOLDOWN 200

typedef enum ELEMENT
{
	AIR, BLOCK, MOVING
}ELEMENT;

typedef enum SHAPE_TYPE
{
	O_SHAPE, J_SHAPE, L_SHAPE, T_SHAPE, I_SHAPE, S_SHAPE, Z_SHAPE
}SHAPE_TYPE;

short shapes[7][8] = 
{
	{ 4,3,5,3,4,4,5,4 },
	{ 4,4,5,4,6,4,4,3 },
	{ 5,4,4,4,3,4,5,3 },
	{ 5,4,4,4,6,4,5,3 },
	{ 4,4,5,4,3,4,6,4 },
	{ 4,3,5,3,4,2,5,4 },
	{ 4,3,5,3,5,2,4,4 },
};

char map[HIGTH][WIDTH];//显示区域为0,5到10,25 0为空 1为已下落的方块 2为正在移动的方块
HANDLE hdl;
ULONGLONG now, last;
char key;
COORD faller[4];
COORD next_faller[4];
SHAPE_TYPE now_shape;
int keyboard_flag;

void generate();
void update_screen();
void clear_row();
int try_move_down();
int try_rotate(int);//顺时针旋转输入1,逆时针-1
int try_fall();
int try_move(int);//向右移动输入1,向左-1
int is_legal(COORD[4]);
int t_spin(int);

int main()
{
	//清除光标
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci = { 1,0 };
	SetConsoleCursorInfo(hdl, &cci);
	SetConsoleTitle("TETRIS!!!");

	//随机数种子
	srand((unsigned)time(NULL));

	//地图初始化
	memset(map, 0, WIDTH * HIGTH * sizeof(char));

	//计时开始
	last = GetTickCount64();
	keyboard_flag = 0;

	//生成第一个方块
	generate();
	update_screen();

	while (1)
	{
		//按键成功后的冷却
		if (keyboard_flag)
		{
			keyboard_flag = 0;
			last = GetTickCount64() + COOLDOWN;
		}

		//自然下落
		now = GetTickCount64();
		if (now > last)
		{
			last += TICK;
			if (try_move_down() == 0)
			{
				for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = BLOCK;
				clear_row();
				generate();
			}
			update_screen();
		}

		//按键检测
		while (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 'E':case 'e':
				if (try_rotate(1)==1)keyboard_flag = 1;
				break;
			case 'Q':case 'q':
				if (try_rotate(-1) == 1)keyboard_flag = 1;
				break;
			case 'S':case 's':
				if (try_move_down() == 1)keyboard_flag = 1;
				break;
			case 'W':case 'w':
				if (try_fall() == 1)keyboard_flag = 1;
				break;
			case 'D':case 'd':
				if (try_move(1) == 1)keyboard_flag = 1;
				break;
			case 'A':case 'a':
				if (try_move(-1) == 1)keyboard_flag = 1;
				break;

			}
		}
		update_screen();
	}
	return 0;
}

void generate()
{
	//static test = 0;
	//SHAPE_TYPE temp_shape[] = { T_SHAPE,J_SHAPE,I_SHAPE,Z_SHAPE,T_SHAPE };
	//now_shape = temp_shape[test++];
	now_shape = rand() % 7;
	memcpy(faller, shapes + now_shape, sizeof(faller));
	for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = MOVING;
}

void update_screen()
{
	COORD zero = { 0,0 };
	SetConsoleCursorPosition(hdl, zero);
	for (int i = 0; i < HIGTH; i++)
	{
		printf("<|");
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == AIR)printf(". ");
			else printf("■");
		}
		puts("|>");
	}
	printf("<---------------------->");
}
void clear_row()
{
	int flag;
	for (int i = HIGTH - 1; i >= 5; i--)
	{
		flag = 1;
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j] != BLOCK)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			for (int j = i; j > 5; j--)
			{
				memcpy(map[i], map[i - 1], WIDTH * sizeof(char));
			}
		}
	}
}
int try_move_down()
{
	memcpy(next_faller, faller, sizeof(faller));
	for (int i = 0; i < 4; i++)
	{
		next_faller[i].Y++;
		if (is_legal(next_faller)==0)return 0;
	}
	for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = AIR;
	memcpy(faller, next_faller, sizeof(faller));
	for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = MOVING;
	return 1;
}
int try_rotate(int direction)
{
	if (now_shape == O_SHAPE)return 0;
	if (now_shape == T_SHAPE)return t_spin(direction);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			next_faller[j].X = faller[i].X + direction * (faller[i].Y - faller[j].Y);
			next_faller[j].Y = faller[i].Y + direction * (faller[j].X - faller[i].X);
		}
		if (is_legal(next_faller))
		{
			for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = AIR;
			memcpy(faller, next_faller, sizeof(faller));
			for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = MOVING;
			return 1;
		}
	}
	return 0;
}
int try_fall()
{
	int result = 0;
	while (try_move_down() == 1)result = 1;
	return result;
}
int try_move(int direction)
{
	memcpy(next_faller, faller, sizeof(faller));
	for (int i = 0; i < 4; i++)
	{
		next_faller[i].X += direction;
		if (is_legal(next_faller)==0)return 0;
	}
	for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = AIR;
	memcpy(faller, next_faller, sizeof(faller));
	for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = MOVING;
	return 1;
}

int is_legal(COORD test[4])
{
	for (int i = 0; i < 4; i++)
	{
		if (test[i].Y >= HIGTH)return 0;
		if (test[i].X >= WIDTH || test[i].X < 0)return 0;
		if (map[next_faller[i].Y][next_faller[i].X] == BLOCK)return 0;
	}
	return 1;
}
int t_spin(int direction)
{
	for (int j = 0; j < 4; j++)
	{
		next_faller[j].X = faller[0].X + direction * (faller[0].Y - faller[j].Y);
		next_faller[j].Y = faller[0].Y + direction * (faller[j].X - faller[0].X);
	}
	if (is_legal(next_faller))
	{
		for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = AIR;
		memcpy(faller, next_faller, sizeof(faller));
		for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = MOVING;
		return 1;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			next_faller[j].X = faller[i].X + direction * (faller[i].Y - faller[j].Y);
			next_faller[j].Y = faller[i].Y + direction * (faller[j].X - faller[i].X) + 1;
		}
		if (is_legal(next_faller))
		{
			for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = AIR;
			memcpy(faller, next_faller, sizeof(faller));
			for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = MOVING;
			return 1;
		}
	}
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			next_faller[j].X = faller[i].X + direction * (faller[i].Y - faller[j].Y);
			next_faller[j].Y = faller[i].Y + direction * (faller[j].X - faller[i].X);
		}
		if (is_legal(next_faller))
		{
			for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = AIR;
			memcpy(faller, next_faller, sizeof(faller));
			for (int i = 0; i < 4; i++)map[faller[i].Y][faller[i].X] = MOVING;
			return 1;
		}
	}
	return 0;
}
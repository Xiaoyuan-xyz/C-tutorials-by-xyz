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

typedef enum FUNCTION_RESULT
{
	FUNCTION_SUSSESS, FUNCTION_FAIL
}FUNCTION_RESULT;

typedef enum SHAPE_TYPE
{
	O_SHAPE, J_SHAPE, L_SHAPE, T_SHAPE, I_SHAPE, S_SHAPE, Z_SHAPE
}SHAPE_TYPE;

char map[HIGTH][WIDTH];//显示区域为0,5到10,25 0为空 1为已下落的方块 2为正在移动的方块
COORD faller[4];
COORD next_faller[4];
ULONGLONG last;
ULONGLONG now;
int key;
SHAPE_TYPE now_shape;
int keyboard_flag;
HANDLE hdl;

//形状的初始位置，分别表示xy坐标，顺序是ojltisz
short o_shape[8] = { 4,3,5,3,4,4,5,4 };
short j_shape[8] = { 4,4,5,4,6,4,4,3 };
short l_shape[8] = { 5,4,4,4,3,4,5,3 };
short t_shape[8] = { 5,4,4,4,6,4,5,3 };
short i_shape[8] = { 4,4,5,4,3,4,6,4 };
short s_shape[8] = { 4,3,5,3,4,2,5,4 };
short z_shape[8] = { 4,3,5,3,5,2,4,4 };

short shape[7][8] =
{
	{ 4,3,5,3,4,4,5,4 },
	{ 4,4,5,4,6,4,4,3 },
	{ 5,4,4,4,3,4,5,3 },
	{ 5,4,4,4,6,4,5,3 },
	{ 4,4,5,4,3,4,6,4 },
	{ 4,3,5,3,4,2,5,4 },
	{ 4,3,5,3,5,2,4,4 },
};

int is_legal(COORD test[4])//1为合法 0为不合法
{
	for (int i = 0; i < 4; i++)
	{
		if (test[i].X < 0 || test[i].X >= WIDTH)return 0;
		if (test[i].Y >= HIGTH)return 0;
	}
	for (int i = 0; i < 4; i++)
	{
		if (map[test[i].Y][test[i].X] == BLOCK)return 0;
	}
	return 1;
}

void update_screen()
{
	//system("CLS");
	COORD pos_start= { 0,0 };
	SetConsoleCursorPosition(hdl, pos_start);
	for (int i = 5; i < HIGTH; i++)
	{
		printf("<|");
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == AIR) printf(". ");
			else printf("■");
		}
		printf("|>\n");
	}
	printf("<---------------------->");
}

void generate()
{
	now_shape = rand() % 7;
	memcpy(&faller, shape[now_shape], 4 * sizeof(COORD));
	for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = MOVING;
}

FUNCTION_RESULT try_move_down()
{
	memcpy(next_faller, faller, sizeof(faller));
	for (int i = 0; i < 4; i++)
	{
		next_faller[i].Y++;
		if (next_faller[i].Y >= HIGTH)return FUNCTION_FAIL;
		if (map[next_faller[i].Y][next_faller[i].X] == BLOCK)return FUNCTION_FAIL;
	}
	for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = AIR;
	memcpy(faller, next_faller, sizeof(faller));
	for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = MOVING;
	return FUNCTION_SUSSESS;
}

void clear_row()
{
	COORD temp_map[HIGTH][WIDTH];
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
			memcpy(temp_map, map, i * sizeof(map[0]));
			memcpy(map + 1, temp_map, i * sizeof(map[0]));
			continue;
		}
	}
}

//向右输入1，向左输入-1
FUNCTION_RESULT try_move_horizontal(int direction)
{
	memcpy(next_faller, faller, sizeof(faller));
	for (int i = 0; i < 4; i++)
	{
		next_faller[i].X+=direction;
		if (next_faller[i].X >= WIDTH || next_faller[i].X < 0) return FUNCTION_FAIL;
		if (map[next_faller[i].Y][next_faller[i].X] == BLOCK)return FUNCTION_FAIL;
	}
	keyboard_flag = 1;
	for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = AIR;
	memcpy(faller, next_faller, sizeof(faller));
	for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = MOVING;
	return FUNCTION_SUSSESS;
}

FUNCTION_RESULT try_fall()
{
	FUNCTION_RESULT result = FUNCTION_FAIL;
	while (try_move_down() == FUNCTION_SUSSESS)result = FUNCTION_SUSSESS;
	return result;
}

//以中心点旋转
//以所有点旋转后向下
//以其他点旋转
FUNCTION_RESULT t_spin(int direction)
{
	for (int j = 0; j < 4; j++)
	{
		next_faller[j].X = faller[0].X + direction * (faller[0].Y - faller[j].Y);
		next_faller[j].Y = faller[0].Y + direction * (faller[j].X - faller[0].X);
	}
	if (is_legal(next_faller))
	{
		for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = AIR;
		memcpy(faller, next_faller, sizeof(faller));
		for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = MOVING;
		return FUNCTION_SUSSESS;
	}

	for (int round = 1; round >= 0; round--)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				next_faller[j].X = faller[i].X + direction * (faller[i].Y - faller[j].Y);
				next_faller[j].Y = faller[i].Y + direction * (faller[j].X - faller[i].X) + round;
			}
			if (is_legal(next_faller))
			{
				for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = AIR;
				memcpy(faller, next_faller, sizeof(faller));
				for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = MOVING;
				return FUNCTION_SUSSESS;
			}
		}
	}
	return FUNCTION_FAIL;
}

//以中心点旋转
//以其他点旋转
//检查以中心点旋转后能否向下移动一格
//检查以其他点旋转后能否向下移动一格
FUNCTION_RESULT try_rotate(int direction)
{
	if (now_shape == O_SHAPE)return FUNCTION_FAIL;
	if (now_shape == T_SHAPE)return t_spin(direction);
	for (int round = 0; round <= 1; round++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				next_faller[j].X = faller[i].X + direction * (faller[i].Y - faller[j].Y);
				next_faller[j].Y = faller[i].Y + direction * (faller[j].X - faller[i].X) + round;
			}
			if (is_legal(next_faller))
			{
				for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = AIR;
				memcpy(faller, next_faller, sizeof(faller));
				for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = MOVING;
				return FUNCTION_SUSSESS;
			}
		}
	}
	return FUNCTION_FAIL;
}


int main_()
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

	while (1)//主循环
	{
		now = GetTickCount64();
		//说明该向下移动了
		if (keyboard_flag)
		{
			keyboard_flag = 0;
			last = GetTickCount64() + COOLDOWN;
			update_screen();
		}
		if (now > last)
		{
			last += TICK;
			if (try_move_down() == FUNCTION_FAIL)//向下移动失败，创建一个新的形状
			{
				for (int i = 0; i < 4; i++) map[faller[i].Y][faller[i].X] = BLOCK;
				clear_row();
				generate();
			}
			update_screen();
		}

		while (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 'E':case 'e':
				if (try_rotate(1) == FUNCTION_SUSSESS)keyboard_flag = 1;
				break;
			case 'Q':case 'q':
				if (try_rotate(-1) == FUNCTION_SUSSESS)keyboard_flag = 1;
				break;
			case 'S':case 's':
				if (try_move_down() == FUNCTION_SUSSESS)keyboard_flag = 1;
				break;
			case 'W':case 'w':
				if (try_fall() == FUNCTION_SUSSESS)keyboard_flag = 1;
				break;
			case 'D':case 'd':
				if (try_move_horizontal(1) == FUNCTION_SUSSESS)keyboard_flag = 1;
				break;
			case 'A':case 'a':
				if (try_move_horizontal(-1) == FUNCTION_SUSSESS)keyboard_flag = 1;
				break;
			}
		}
	}
	return 0;
}
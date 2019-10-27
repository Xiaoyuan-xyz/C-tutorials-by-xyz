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

char map[HIGTH][WIDTH];//��ʾ����Ϊ0,5��10,25 0Ϊ�� 1Ϊ������ķ��� 2Ϊ�����ƶ��ķ���
COORD faller[4];
COORD next_faller[4];
ULONGLONG last;
ULONGLONG now;
int key;
SHAPE_TYPE now_shape;
int keyboard_flag;
HANDLE hdl;

//��״�ĳ�ʼλ�ã��ֱ��ʾxy���꣬˳����ojltisz
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

int is_legal(COORD test[4])//1Ϊ�Ϸ� 0Ϊ���Ϸ�
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
			else printf("��");
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

//��������1����������-1
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

//�����ĵ���ת
//�����е���ת������
//����������ת
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

//�����ĵ���ת
//����������ת
//��������ĵ���ת���ܷ������ƶ�һ��
//�������������ת���ܷ������ƶ�һ��
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
	//������
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci = { 1,0 };
	SetConsoleCursorInfo(hdl, &cci);
	SetConsoleTitle("TETRIS!!!");

	//���������
	srand((unsigned)time(NULL));
	
	//��ͼ��ʼ��
	memset(map, 0, WIDTH * HIGTH * sizeof(char));

	//��ʱ��ʼ
	last = GetTickCount64();
	keyboard_flag = 0;

	//���ɵ�һ������
	generate();
	update_screen();

	while (1)//��ѭ��
	{
		now = GetTickCount64();
		//˵���������ƶ���
		if (keyboard_flag)
		{
			keyboard_flag = 0;
			last = GetTickCount64() + COOLDOWN;
			update_screen();
		}
		if (now > last)
		{
			last += TICK;
			if (try_move_down() == FUNCTION_FAIL)//�����ƶ�ʧ�ܣ�����һ���µ���״
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
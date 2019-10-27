#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 90 //x i
#define HIGTH 25 //y j
#define TICK 80
#define APPLE_DELAY 5000

typedef enum {
	NORTH,SOUTH,WEST,EAST
}Direction;

int size;
COORD* body;
Direction direction;
COORD apple, tail;
char key;
HANDLE hdl;
ULONGLONG start, tick_event, apple_event, now;
boolean is_death;
int dx, dy;

void draw_wall();
void draw_score();
void init_apple();
void init_snake();
void tick();
void remove_obj(COORD obj);
void update_screen();
void get_direction();

int main()
{
	//��ʼ������갡֮���
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci = { 1,0 };
	SetConsoleCursorInfo(hdl, &cci);
	SetConsoleTitle("SNAKE!!!");
	srand((unsigned)time(NULL));
	//���߽��г�ʼ�����ڶ��������ߵ�����
	body = (COORD*)malloc(sizeof(COORD) * HIGTH * WIDTH);
	
	
	//������Ϸ����
	draw_wall();
	draw_score();//score:XXX

	//���߽��л��ƣ�ƻ��
	init_snake();
	init_apple();

	//��ʱ����г�ʼ��
	start = GetTickCount64();
	tick_event = start + TICK;
	apple_event = start + APPLE_DELAY;

	while (1)
	{
		//��ȡ��ǰ��ʱ�䣬����ﵽһ��ʱ�䣬���ƶ���
			//���߱��������ģ�ɾ��β�ͣ���ǰ�ƶ�һ��
			//ʤ���ж�����ƻ���ж�
			//�������
		now = GetTickCount64();
		if (now > tick_event)
		{
			tick();
			if (is_death == TRUE)break;
			tick_event += TICK;
		}
		if (now > apple_event)
		{
			remove_obj(apple);
			init_apple();
			apple_event += APPLE_DELAY;
		}

		//ÿ��һ��ʱ�� ����ƻ����λ��

	}
	free(body);
	return 0;
}

void draw_wall()
{
	for (int i = 0; i <= HIGTH; i++)
	{
		for (int j = 0; j <= WIDTH; j++)
		{
			if (i == HIGTH)putchar('=');
			else if (j == WIDTH)putchar('=');
			else putchar(' ');
		}
		puts("");
	}
}
void draw_score()
{
	COORD pos = { WIDTH + 5,HIGTH / 2 };
	SetConsoleCursorPosition(hdl, pos);
	printf("SCORE:");
}
void init_apple()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		apple.X = rand() % WIDTH;
		apple.Y = rand() % HIGTH;
		for (int i = 0; i < size; i++)
		{
			if (body[i].X == apple.X && body[i].Y == apple.Y)
			{
				flag = 1;
			}
		}
	}
}
void init_snake()
{
	is_death = FALSE;
	size = 2;
	body[0].X = WIDTH / 2;
	body[0].Y = HIGTH / 2;
	body[1].X = WIDTH / 2 - 1;
	body[1].Y = HIGTH / 2;
	direction = EAST;
	key = 'D';
	dx = 1;
	dy = 0;
}
void tick()
{
	//�ж��Ƿ�ײǽ
	if (body[0].X < 0 || body[0].X >= WIDTH || body[0].Y < 0 || body[0].Y >= HIGTH)
	{
		is_death = TRUE;
		return;
	}

	//��ƻ������
	update_screen();

	//�������
	get_direction();

	//�ж��Ƿ�ײ���Լ�
	for (int i = 1; i < size; i++)
	{
		if (body[i].X == body[0].X && body[i].Y == body[0].Y)
		{
			is_death = TRUE;
			return;
		}
	}

	//�ж��Ƿ�Ե�ƻ��
	if (apple.X == body[0].X && apple.Y == body[0].Y)
	{
		init_apple();
		size++;
	}

	//�����ߵ�λ�� 
	tail = body[size - 1];
	for (int i = size - 1; i > 0; i--)
	{
		body[i] = body[i - 1];
	}
	body[0].X += dx;
	body[0].Y += dy;

}
void remove_obj(COORD obj)
{
	SetConsoleCursorPosition(hdl, obj);
	putchar(' ');
}

void update_screen()
{
	remove_obj(tail);
	for (int i = 0; i < size; i++)
	{
		SetConsoleCursorPosition(hdl, body[i]);
		if (i == 0)putchar('@');
		else putchar('*');
	}
	SetConsoleCursorPosition(hdl, apple);
	putchar('#');
	COORD pos = { WIDTH + 11,HIGTH / 2 };
	SetConsoleCursorPosition(hdl, pos);
	printf("%d", size);
}

void get_direction()
{
	while (_kbhit())
	{
		key = _getch();
		switch (key)
		{
		case 'W':case 'w':
			if (direction == SOUTH)break;
			direction = NORTH;
			dx = 0;
			dy = -1;
			break;
		case 'A':case 'a':
			if (direction == EAST)break;
			direction = WEST;
			dx = -1;
			dy = 0;
			break;
		case 'S':case 's':
			if (direction == NORTH)break;
			direction = SOUTH;
			dx = 0;
			dy = 1;
			break;
		case 'D':case 'd':
			if (direction == WEST)break;
			direction = EAST;
			dx = 1;
			dy = 0;
			break;
		case -32:
			key = _getch();
			switch (key)
			{
			case 72:
				if (direction == SOUTH)break;
				direction = NORTH;
				dx = 0;
				dy = -1;
				break;
			case 80:
				if (direction == NORTH)break;
				direction = SOUTH;
				dx = 0;
				dy = 1;
				break;
			case 75:
				if (direction == EAST)break;
				direction = WEST;
				dx = -1;
				dy = 0;
				break;
			case 77:
				if (direction == WEST)break;
				direction = EAST;
				dx = 1;
				dy = 0;
				break;
			}
		}
	}
}
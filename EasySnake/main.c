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
	//初始化：光标啊之类的
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci = { 1,0 };
	SetConsoleCursorInfo(hdl, &cci);
	SetConsoleTitle("SNAKE!!!");
	srand((unsigned)time(NULL));
	//对蛇进行初始化：在堆区创建蛇的数组
	body = (COORD*)malloc(sizeof(COORD) * HIGTH * WIDTH);
	
	
	//绘制游戏界面
	draw_wall();
	draw_score();//score:XXX

	//对蛇进行绘制，苹果
	init_snake();
	init_apple();

	//对时间进行初始化
	start = GetTickCount64();
	tick_event = start + TICK;
	apple_event = start + APPLE_DELAY;

	while (1)
	{
		//获取当前的时间，如果达到一定时间，就移动蛇
			//对蛇本身做更改：删除尾巴，向前移动一格
			//胜负判定、吃苹果判定
			//按键检测
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

		//每隔一段时间 更改苹果的位置

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
	//判断是否撞墙
	if (body[0].X < 0 || body[0].X >= WIDTH || body[0].Y < 0 || body[0].Y >= HIGTH)
	{
		is_death = TRUE;
		return;
	}

	//画苹果画蛇
	update_screen();

	//按键检测
	get_direction();

	//判断是否撞到自己
	for (int i = 1; i < size; i++)
	{
		if (body[i].X == body[0].X && body[i].Y == body[0].Y)
		{
			is_death = TRUE;
			return;
		}
	}

	//判断是否吃到苹果
	if (apple.X == body[0].X && apple.Y == body[0].Y)
	{
		init_apple();
		size++;
	}

	//更改蛇的位置 
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
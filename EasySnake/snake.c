#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define WIDE 90 //x j
#define HIGH 25 //y i
#define DELAY 80
#define APPLE_DELAY 5000

typedef enum {
	EAST, WEST, NORTH, SOUTH
}Direction;


int size;
COORD* body;
Direction direction;

COORD coord, apple, tail;
int score;
int dx, dy;
char key;
boolean isDeath;

ULONGLONG start, tickEvent, now, appleEvent;

void DrawWall()
{
	for (int i = 0; i <= HIGH; i++)
	{
		for (int j = 0; j <= WIDE; j++)
		{
			if (i == HIGH)
				putchar('=');
			else if (j == WIDE)
				putchar('=');
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

void DrawScore()
{
	COORD coord;
	coord.X = WIDE + (WIDE >> 3);
	coord.Y = HIGH >> 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("SCORE:");
}

void InitApple()
{
	boolean flag = TRUE;
	while (flag)
	{
		flag = FALSE;
		apple.X = rand() % WIDE;
		apple.Y = rand() % HIGH;
		for (int i = 0; i < size; i++)
			if (body[i].X == apple.X &&
				body[i].Y == apple.Y)flag = TRUE;
	}
	appleEvent += APPLE_DELAY;
}

void InitSnake()
{
	score = 0;
	size = 2;
	body[0].X = WIDE / 2;
	body[0].Y = HIGH / 2;
	body[1].X = WIDE / 2 - 1;
	body[1].Y = HIGH / 2;
	key = 'D';
	direction = EAST;
}

void RemoveObject(COORD object)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), object);
	putchar(' ');
}

void GameUI()
{
	//delete tail
	RemoveObject(tail);
	//move snake
	for (int i = 0; i < size; i++)
	{
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE), body[i]);
		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}
	//show apple
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), apple);
	putchar('#');
	//show score
	coord.X = WIDE + (WIDE >> 3) + 6;
	coord.Y = HIGH >> 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("%3d", score);
}

void Tick_SnakeControl()
{
	while (_kbhit())
	{
		key = _getch();
	}
	switch (key)
	{
	case 'D':case 'd':case 77:
		if (direction == WEST)break;
		direction = EAST;
		dx = 1; dy = 0; break;
	case 'A':case 'a':case 75:
		if (direction == EAST)break;
		direction = WEST;
		dx = -1; dy = 0; break;
	case 'W':case 'w':case 72:
		if (direction == SOUTH)break;
		direction = NORTH;
		dx = 0; dy = -1; break;
	case 'S':case 's':case 80:
		if (direction == NORTH)break;
		direction = SOUTH;
		dx = 0; dy = 1; break;
	case 224:
		key = _getch();
		switch (key)
		{
		case 77:
			if (direction == WEST)break;
			direction = EAST;
			dx = 1; dy = 0; break;
		case 75:
			if (direction == EAST)break;
			direction = WEST;
			dx = -1; dy = 0; break;
		case 72:
			if (direction == SOUTH)break;
			direction = NORTH;
			dx = 0; dy = -1; break;
		case 80:
			if (direction == NORTH)break;
			direction = SOUTH;
			dx = 0; dy = 1; break;
		}
	}
}

void Tick()
{
	//bond_test
	if (body[0].X < 0 || body[0].X >= WIDE
		|| body[0].Y < 0 || body[0].Y >= HIGH)
		isDeath = TRUE;
	if (isDeath)return;
	
	//showUI
	GameUI();
	//react if key pressed
	Tick_SnakeControl();
	//if hit body
	for (int i = 1; i < size; i++)
		if (body[i].X == body[0].X
			&& body[i].Y == body[0].Y)
		{
			isDeath = TRUE;
			return;
		}
	

	//if hit apple
	if (apple.X == body[0].X
		&& apple.Y == body[0].Y)
	{
		InitApple();
		size++;
		score += 1;
	}
	//get tail for delete
	tail = body[size - 1];
	//move body
	for (int i = size - 1; i > 0; i--)
		body[i] = body[i - 1];
	//move head
	body[0].X += dx;
	body[0].Y += dy;
}

int main_()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	srand((size_t)time(NULL));
	body = (COORD*)(malloc(sizeof(COORD) * HIGH * WIDE));

	DrawWall();
	DrawScore();
	InitApple();
	InitSnake();

	isDeath = FALSE;
	//time when one game start
	start = GetTickCount64();
	//init tick clock
	appleEvent = start + APPLE_DELAY;
	tickEvent = start + DELAY;


	while (TRUE)
	{
		now = GetTickCount64();
		//apple reflesh
		if (now > appleEvent)
		{
			RemoveObject(apple);
			//init apple and reset clock
			InitApple();
		}
		//snake tick event
		if (now > tickEvent)
		{
			Tick();
			if (isDeath)break;
			tickEvent += DELAY;
		}
	}

	//game over
}
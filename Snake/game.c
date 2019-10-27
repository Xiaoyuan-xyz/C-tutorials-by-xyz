#include "snake.h"
#include "extern.h"

void Tick()
{
	//return if out of bound in HARD or LUNATIC
	if (difficult > NORMAL)
	{
		Tick_BoundTest();
		if (isDeath)return;
	}
	//showUI
	GameUI();
	//react if key pressed
	Tick_SnakeControl();
	//if hit body
	if(difficult>NORMAL)
	{
		for (int i = 1; i < snake.size; i++)
			if (snake.body[i].X == snake.body[0].X
				&&snake.body[i].Y == snake.body[0].Y)
			{
				isDeath = TRUE;
				return;
			}
	}
	//if hit apple
	if (apple.X == snake.body[0].X
		&&apple.Y == snake.body[0].Y)
	{
		InitApple();
		snake.size++;
		score += 1;
	}
	//get tail for delete
	tail = snake.body[snake.size - 1];
	//move body
	for (int i = snake.size - 1; i > 0; i--)
		snake.body[i] = snake.body[i - 1];
	//move head
	snake.body[0].X += dx;
	snake.body[0].Y += dy;
	//won't hit the wall in EASY and NORMAL
	if (difficult <= NORMAL)
	{
		if (snake.body[0].X < 0)snake.body[0].X += WIDE;
		if (snake.body[0].X >= WIDE)snake.body[0].X -= WIDE;
		if (snake.body[0].Y < 0)snake.body[0].Y += HIGH;
		if (snake.body[0].Y >= HIGH)snake.body[0].Y -= HIGH;
	}
	CalculateDelay();
}

void RunGame()
{
	system("CLS");
	Init();
	isDeath = FALSE;

	//time when one game start
	start = GetTickCount64();
	//init tick clock
	appleEvent = start + resetAppleDelay;
	tickEvent = start + delay;
	//start main loop
	while (TRUE)
	{
		Sleep(1);
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
			tickEvent += delay;
		}
	}

	//game over
	SaveHighScore();
	OverUI();
}

void Tick_BoundTest()
{
	if (snake.body[0].X < 0 || snake.body[0].X >= WIDE
		|| snake.body[0].Y < 0 || snake.body[0].Y >= HIGH)
		isDeath = TRUE;
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
		if (snake.direction == WEST)break;
		snake.direction = EAST;
		dx = 1; dy = 0; break;
	case 'A':case 'a':case 75:
		if (snake.direction == EAST)break;
		snake.direction = WEST;
		dx = -1; dy = 0; break;
	case 'W':case 'w':case 72:
		if (snake.direction == SOUTH)break;
		snake.direction = NORTH;
		dx = 0; dy = -1; break;
	case 'S':case 's':case 80:
		if (snake.direction == NORTH)break;
		snake.direction = SOUTH;
		dx = 0; dy = 1; break;
	case 224:
		key = _getch();
		switch (key)
		{
		case 77:
			if (snake.direction == WEST)break;
			snake.direction = EAST;
			dx = 1; dy = 0; break;
		case 75:
			if (snake.direction == EAST)break;
			snake.direction = WEST;
			dx = -1; dy = 0; break;
		case 72:
			if (snake.direction == SOUTH)break;
			snake.direction = NORTH;
			dx = 0; dy = -1; break;
		case 80:
			if (snake.direction == NORTH)break;
			snake.direction = SOUTH;
			dx = 0; dy = 1; break;
		}
	}
}
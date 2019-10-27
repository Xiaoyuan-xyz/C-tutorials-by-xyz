#include "snake.h"
#include "extern.h"

void BeforeAll()
{
	SetVars();
	GetHighScore();
	SetNoCursor();
}

void SetVars()
{
	srand((size_t)time(NULL));
	resetAppleDelay = 5000;
	snake.body = (COORD*)(malloc(sizeof(COORD)*HIGH*WIDE));
}

void GetHighScore()
{
	fp = fopen("newscore.xyz", "rb");
	if (fp == NULL)
	{
		//create scores file if don't exists
		fp = fopen("newscore.xyz", "wb");
		fwrite(highscore, sizeof(int), 40, fp);
		fclose(fp);
	}
	else
	{
		//read scores
		fread(highscore, sizeof(int), 40, fp);
		fclose(fp);
	}
}

void SetNoCursor()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Init()
{
	DrawWall();
	DrawScore();
	InitApple();
	InitSnake();
	CalculateDelay();
}

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
		for (int i = 0; i < snake.size; i++)
			if (snake.body[i].X == apple.X&&
				snake.body[i].Y == apple.Y)flag = TRUE;
	}
	appleEvent += resetAppleDelay;
}

void InitSnake()
{
	score = 0;
	snake.size = 2;
	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;
	snake.body[1].X = WIDE / 2 - 1;
	snake.body[1].Y = HIGH / 2;
	key = 'D';
	snake.direction = EAST;
}

void CalculateDelay()
{
	if (difficult % 2)delay = 40;
	else delay = max(50, 120 - (score << 2));
	if (snake.direction == NORTH || snake.direction == SOUTH)delay = (int)(delay*1.5);
}

void RemoveObject(COORD object)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), object);
	putchar(' ');
}

void SaveHighScore()
{
	for (int i = 0; i < 10; i++)
	{
		if (highscore[difficult][i] < score)
		{
			memcpy(&highscore[difficult][i + 1], &highscore[difficult][i], sizeof(int)*(9 - i));
			highscore[difficult][i] = score;
			break;
		}
	}
	fp = fopen("newscore.xyz", "wb");
	fwrite(highscore, sizeof(int), 40, fp);
	fclose(fp);
}
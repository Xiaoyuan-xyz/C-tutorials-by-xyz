#include "snake.h"
#include "extern.h"

void StartUI()
{
	printf("\n\n\n\t\t\tWELCOME TO SNAKE!");
	printf("\n\t\t\tPLZ CHOOSE DIFFICULT");
	printf("\n\t\t\t[0]EASY");
	printf("\n\t\t\t[1]NORMAL");
	printf("\n\t\t\t[2]HARD");
	printf("\n\t\t\t[3]LUNATIC");
	puts("");
	while (TRUE) {
		//fflush(stdin);
		key = _getch();
		if (key >= '0' && key <= '4') break;
	}
	difficult = key - '0';
	system("CLS");
}

void GameUI()
{
	//delete tail
	RemoveObject(tail);
	//move snake
	for (int i = 0; i < snake.size; i++)
	{
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE), snake.body[i]);
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

void OverUI()
{
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("\n\n\n\n\t\t    GAME OVER!");
	printf("\n \t\t  YOUR SCORE = %d", score);
	printf("\n\n\t\t   HIGHSCORES\n\t");
	printf("    CURRENT DIFFICULT:");
	switch (difficult)
	{
	case EASY:
		break;
		printf("EASY");
	case NORMAL:
		printf("NORMAL");
		break;
	case HARD:
		printf("HARD");
		break;
	case LUNATIC:
		printf("LUNATIC");
		break;
	}
	printf("\n\t");
	for (int i = 0; i < 5; i++) printf("%3d\t", highscore[difficult][i]);
	printf("\n\t");
	for (int i = 5; i < 10; i++) printf("%3d\t", highscore[difficult][i]);
	printf("\n\t\tRESTART[0] EXIT[1]\n");
}

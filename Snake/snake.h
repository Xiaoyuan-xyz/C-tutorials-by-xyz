#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define WIDE 90
#define HIGH 25

typedef enum {
	EAST, WEST, NORTH, SOUTH
}Direction;

typedef enum {
	EASY,NORMAL,HARD,LUNATIC
}Difficult;

struct Snake
{
	int size;
	COORD* body;
	Direction direction;
}snake;

COORD coord, apple, tail;
Difficult difficult;
int score;
int dx, dy;
char key;
boolean isDeath;

int highscore[4][10];
FILE *fp;

long long int start, tickEvent, now, appleEvent;
unsigned long delay;
int resetAppleDelay;

void BeforeAll();
void SetVars();
void SetNoCursor();
void GetHighScore();

void Init();
void InitApple();
void InitSnake();
void DrawWall();
void DrawScore();
void CalculateDelay();

void RemoveObject(COORD);
void SaveHighScore();

void RunGame();
//true if death
void Tick();
void Tick_BoundTest();
void Tick_SnakeControl();


void StartUI();
void GameUI();
void OverUI();




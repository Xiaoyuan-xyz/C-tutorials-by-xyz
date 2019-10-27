#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<ctime>
#define H 25
#define L 14
//这个里要判断它下一步是否会重叠，如果会则表示已经到底
using namespace std;

int array[H][L];    //进行方块组合的地方
//28中变形
int to_change[7][4][4][2] = { {{{0,0},{0,0},{0,0},{0,0}},{{0,0},{0,0},{0,0},{0,0}},{{0,0},{0,0},{0,0},{0,0}},{{0,0},{0,0},{0,0},{0,0}}},
			  {{{2,1},{1,0},{0,1},{-1,0}},{{-2,-1},{-1,0},{0,-1},{1,0}},{{2,1},{1,0},{0,1},{-1,0}},{{-2,-1},{-1,0},{0,-1},{1,0}}},
			  {{{1,2},{0,1},{1,0},{0,-1}},{{-1,-2},{0,-1},{-1,0},{0,1}},{{1,2},{0,1},{1,0},{0,-1}},{{-1,-2},{0,-1},{-1,0},{0,1}}},
			  {{{-1,2},{-2,1},{-1,0},{0,-1}},{{2,0},{1,1},{0,0},{-1,-1}},{{0,-1},{1,0},{0,1},{-1,2}},{{-1,-1},{0,-2},{1,-1},{2,0}}},
			  {{{1,0},{0,-1},{-1,0},{-2,1}},{{0,-2},{-1,-1},{0,0},{1,1}},{{-2,1},{-1,2},{0,1},{1,0}},{{1,1},{2,0},{1,-1},{0,-2}}},
			  {{{-3,2},{-2,-1},{-1,0},{0,1}},{{3,-2},{2,1},{1,0},{0,-1}},{{-3,2},{-2,-1},{-1,0},{0,1}},{{3,-2},{2,1},{1,0},{0,-1}}},
			  {{{0,1},{-2,1},{-1,0},{0,-1}},{{1,-1},{1,1},{0,0},{-1,-1}},{{-1,0},{1,0},{0,1},{-1,2}},{{0,0},{0,-2},{1,-1},{2,0}}} };
//7个图形
int block[7][4][2] = { {{2,6},{2,7},{3,6},{3,7}},
					{{1,7},{2,7},{2,6},{3,6}},
					{{1,6},{2,6},{2,7},{3,7}},
					{{2,6},{3,6},{3,7},{3,8}},
					{{2,8},{3,8},{3,7},{3,6}},
					{{3,5},{3,8},{3,7},{3,6}},
					{{2,7},{3,6},{3,7},{3,8}} };
int picture;//图形的序号
int now;  //当前图形的变化号
int graph[4][2];//图形的坐标
char control;
int start;

void Change();
void Move(char M);  //根据输入的AD判断左右移动
int See();         //判断是否到底
void New();         //开新
void Go();          //向下走一格
void Begin();       //一切值初始化
int Elimination(); //把完整行的消去
void Cout();        //输出矩阵
int main_wow()
{

	Begin();
	Cout();
	while (1) {

		if (GetTickCount() - start >= 500) {

			start = GetTickCount();
			if (!See())Go();
			else {
				if (Elimination())break;
				New();
			}
			system("cls");
			Cout();
		}
		if (kbhit()) {
			control = getch();
			if (control == 'W' || control == 'w')Change();
			else Move(control);
			system("cls");
			Cout();
		}
	}
	//虽然背景板的高度为25，但显示时只显示后20格
}

void Change()
{
	for (int i = 0; i < 4; i++)
		array[graph[i][0]][graph[i][1]] = 0;
	now = (now + 1) % 4;
	for (int i = 0; i < 4; i++) {
		graph[i][0] += to_change[picture][now][i][0];
		graph[i][1] += to_change[picture][now][i][1];
	}
	for (int i = 0; i < 4; i++) {
		if (graph[i][1] < 0) {
			int temp = 0 - graph[i][1];
			for (int j = 0; j < 4; j++)graph[j][1] += temp;
		}
		if (graph[i][1] > L - 1) {
			int temp = graph[i][1] - (L - 1);
			for (int j = 0; j < 4; j++)graph[j][1] -= temp;
		}
	}
	for (int i = 0; i < 4; i++)
		array[graph[i][0]][graph[i][1]] = 2;
}
void Move(char M)
{
	for (int i = 0; i < 4; i++)
		array[graph[i][0]][graph[i][1]] = 0;

	if ((M == 'a' || M == 'A') && graph[0][1] && graph[1][1] && graph[2][1] && graph[3][1])
		if (array[graph[0][0]][graph[0][1] - 1] != 1 && array[graph[1][0]][graph[1][1] - 1] != 1 && array[graph[2][0]][graph[2][1] - 1] != 1 && array[graph[3][0]][graph[3][1] - 1] != 1) {
			graph[0][1]--;
			graph[1][1]--;
			graph[2][1]--;
			graph[3][1]--;
		}
	if ((M == 'd' || M == 'D') && graph[0][1] < L - 1 && graph[1][1] < L - 1 && graph[2][1] < L - 1 && graph[3][1] < L - 1)
		if (array[graph[0][0]][graph[0][1] + 1] != 1 && array[graph[1][0]][graph[1][1] + 1] != 1 && array[graph[2][0]][graph[2][1] + 1] != 1 && array[graph[3][0]][graph[3][1] + 1] != 1) {
			graph[0][1]++;
			graph[1][1]++;
			graph[2][1]++;
			graph[3][1]++;
		}
	for (int i = 0; i < 4; i++)
		array[graph[i][0]][graph[i][1]] = 2;
}
int See()
{
	for (int i = 0; i < 4; i++)
		if (graph[i][0] + 1 == H)return 1;
	for (int i = 0; i < 4; i++)
		if (array[graph[i][0] + 1][graph[i][1]] == 1)return 1;
	return 0;
}
void New()
{
	picture = rand() % 7;
	now = -1;
	for (int i = 0; i < 4; i++) {
		graph[i][0] = block[picture][i][0];
		graph[i][1] = block[picture][i][1];
		array[graph[i][0]][graph[i][1]] = 2;
	}
}
void Go()
{
	for (int i = 0; i < 4; i++) {
		array[graph[i][0]][graph[i][1]] = 0;
		graph[i][0]++;
	}
	for (int i = 0; i < 4; i++)
		array[graph[i][0]][graph[i][1]] = 2;
}
void Begin()
{
	srand(time(NULL));
	start = GetTickCount();//开始的时间
	for (int i = 0; i < H; i++)
		for (int j = 0; j < L; j++)
			array[i][j] = 0;
	picture = rand() % 7;
	now = -1;
	for (int i = 0; i < 4; i++) {
		graph[i][0] = block[picture][i][0];
		graph[i][1] = block[picture][i][1];
		array[graph[i][0]][graph[i][1]] = 2;
	}
}
int Elimination()
{
	for (int i = 0; i < 4; i++) {
		array[graph[i][0]][graph[i][1]] = 1;
		if (graph[i][0] < 4)return 1;
	}
	for (int i = H - 1; i >= 0; ) {
		int j;
		for (j = 0; j < L; j++)
			if (array[i][j] != 1)break;
		if (j == L) {
			for (int k = i; k > 0; k--)
				for (int l = 0; l < L; l++)
					array[k][l] = array[k - 1][l];
		}
		else i--;
	}
	return 0;
}
void Cout()
{
	for (int i = 5; i < H; i++) {
		for (int j = 0; j < L; j++) {
			if (array[i][j] == 0)printf(".");
			else if (array[i][j] == 1) {
				printf("#");

			}
			else printf("o");
		}
		printf("\n");
	}
}

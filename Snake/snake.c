#include "snake.h"

int main()
{
	BeforeAll();
	StartUI();
	//game loop
	while (TRUE)
	{
		RunGame();
		while (TRUE) {
			key = _getch();
			//restart
			if (key == '0')break;
			//exit
			if (key == '1')return 0;
		}
	}
}



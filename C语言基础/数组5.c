#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main()
{
	char *p1 = "hello";
	char *p2 = "world";
	char *p3 = "goodbye";

	char x[][8] = {
		"hello", //hello000world000goodbye0
		"world",
		"goodbye",
	};

	char(*p2)[8] = x;

	char* y[] = {
		"hello", 
		"world",
		"goodbye",
		NULL,
	};

	char** p = y;

	while (*p != NULL)
	{
		printf("%s\n", *p);
		p++;
	}


	//for (int i = 0; i < 3; i++)
	//{
	//	printf("%s\n", y[i]);
	//}


	return 0;
}
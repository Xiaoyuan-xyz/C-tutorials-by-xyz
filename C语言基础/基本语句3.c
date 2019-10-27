#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main_zmb()
{
#if 0
	int x = 120;
	char c = 'x';

	printf("120:%o\n120:%c", 120, 120);
#endif

	char c = 'A';

	while (c <= 'Z')
	{
		putchar(c);
		putchar(c + 'a' - 'A');
		putchar(' ');
		c++;
	}
	return 0;
}

int main_getchar()
{
	char c;
	while (1)
	{
		c = getchar();
		putchar(c);
	}

	return 0;
}

int main_scanf_c()
{
	char c;
	scanf("%c", &c);
	printf("%c", c);

	return 0;
}

int main_cdcd()
{
	int x, y;
	char a, b;
	scanf("%d%c%d%c", &x, &a, &y, &b);
	printf("%d %c %d %c", x, a, y, b);
	return 0;
}

int main_zyzf()
{
	//putchar(''');
	putchar('\'');
	printf("\"");
	putchar('0');
	putchar('\0');
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void showw(char* str)
{
	while (*str)
	{
		putchar(*str);
		str++;
	}
}

int main_sz4()
{
	char x[50];//À¬»ø
	char y[4] = { 'a','b','c','d' };
	char z[5] = { 'a','\0','c','d' };// a b c d \0
	char w[5] = { 0 };// \0 \0 \0 \0 \0
	char u[] = { 'a','b','c','d' };
	char s[] = "hello";// h e l l o \0



	//for (int i = 0; i < 4; i++)
	//{
	//	putchar(y[i]);
	//}

	//printf("%s", s);
	//showw(x);

	return 0;
}

int main_sz1()
{
	char s[] = "hello";// h e l l o \0
	s[0] = 'm';

	char* p = "hello";
	char* p2 = s;

	printf("%p\n", p);
	printf("%p\n", p2);

	//p[0] = 'm';
	p2[0] = 'n';

	showw(p);
	showw(p2);

}

void to_upper(char* str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
		{
			*str -= 32;
		}
		str++;
	}
}

void string_copy(char* dest,const char* src)
{
	while (*dest++ = *src++);
}

int main_sz42()
{
	char str[100] = "hello world";
	//scanf("%s", str);
	char dest[100];

	//string_copy(dest, str);

	strcpy(dest, str);

	showw(dest);

	//to_upper(str);
	//showw(str);
	//Ð¡Ð´×ÖÄ¸×ª´óÐ´

	return 0;
}
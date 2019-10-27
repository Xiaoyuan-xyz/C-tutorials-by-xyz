#include <stdio.h>
#include <math.h>

#define N 1000


/*
s=1+(++i);
i = i + 1;
s=1 + i;
*/
#if 0
int main_zs()
{
	int i = 2;
	int j = 2;
	int s = 0;
	int flag = 0;
	while (i<=N)
	{
		s = sqrt(i);
		flag = 0;
		j = 2;
		while (j<=s)
		{
			if (i % j == 0)
			{
				flag = 1;
				break;
			}
			++j;
		}
		if (flag != 1)
		{
			printf("%d\t", i);
		}
		++i;
	}
	return 0;
}

int main_for()
{
	int s = 0;
	int flag = 0;
	for (int i = 2; i <= N; i++)
	{
		s = sqrt(i);
		flag = 0;
		for (int j = 2; j <= s; j++)
		{
			if (i % j == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag != 1)
		{
			printf("%d\t", i);
		}
	}
	return 0;
}

int main_do()
{
	int i = 2;
	int s = 0;
	int flag = 0;
	do
	{
		s = sqrt(i);
		flag = 0;
		for (int j = 2; j <= s; j++)
		{
			if (i % j == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag != 1)
		{
			printf("%d\t", i);
		}
		i++;
	} while (i <= N);
	return 0;
}
#endif
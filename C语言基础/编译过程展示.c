//�˴�����ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>

//����궨��N=10
#define N 10

//������
int main_bygczs()
{
	int i = 0;
	int s = 0;
	while (i < N)
	{
		i = i + 1;
		s = s + i;
	}
	printf("%d", s);
	system("pause");
	return 0;
}

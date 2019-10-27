#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main_rpn()
{
	char	str[100] = { 0 };
	char*	p = str;
	
	int		num[100] = { 0 };//��׺���ʽ
	char	operator[100] = { 0 };
	int		index = 0;

	char	stack[100] = { 0 };//����ջ
	int		stacki[100] = { 0 };//����ջ
	int		top = -1;//ջ�����

	int		temp = 0, temp1 = 0, temp2 = 0;
	int		flag = 0;//��ǰ�Ƿ���ƴдһ������

	scanf("%s", str);
	while (1)//��׺���ʽת��׺���ʽ
	{
		if (*p >= '0' && *p <= '9')//�������һ�������ַ�
		{
			flag = 1;//������ƴд����
			temp *= 10;
			temp += *p - '0';
		}
		else//�����˷��Ż����ַ����Ѿ�������
		{
			if (flag)//�������ƴд���֣��ͽ����ָ���num
			{
				operator[index] = '!';
				num[index++] = temp;
				flag = temp = 0;//���ڲ�ƴд������
			}
			if (!*p)//����ַ���������
			{
				while (top>=0) operator[index++] = stack[top--];//ʣ����ų�ջ
				break;
			}
			else//�����һ������
			{
				if (top < 0 || *p == '(') stack[++top] = *p;//ջΪ�ջ���������������ջ
				else if (*p == ')')//���������ţ���ջ��������
				{
					while (top >= 0 && stack[top] != '(')//��ջ��������
					{
						operator[index++] = stack[top--];
					}
					top--;//�����ų�ջ
				}
				else if (*p == '*' || *p == '/')//�����˳����˳���ջ
				{
					while (top >= 0 && (stack[top] == '*' || stack[top] == '/'))
					{
						operator[index++] = stack[top--];
					}
					stack[++top] = *p;//�˳��Ž�ջ
				}
				else //�Ӻźͼ���
				{
					while (top >= 0&& stack[top] != '(')//�����Ӽ��������������������ջ
					{
						operator[index++] = stack[top--];
					}
					stack[++top] = *p;//�Ӽ��Ž�ջ
				}
			}
		}
		p++;
	}

	top = -1;//�����׺���ʽ
	for (int i = 0; i < index;i++)
	{
		if (operator[i] == '!')
		{
			stacki[++top] = num[i];
		}
		else
		{
			temp1 = stacki[top--];
			temp2 = stacki[top--];
			switch (operator[i])
			{
			case '+':
				stacki[++top] = temp2 + temp1;
				break;
			case '-':
				stacki[++top] = temp2 - temp1;
				break;
			case '*':
				stacki[++top] = temp2 * temp1;
				break;
			case '/':
				stacki[++top] = temp2 / temp1;
				break;
			}
		}
	}
	int result = stacki[0];
	printf("%s=%d\n", str, result);
	return 0;
}
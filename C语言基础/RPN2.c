#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main_rpn2()
{
	char	str[100] = { 0 };
	char*	p = str;

	int		num[100] = { 0 };
	char	operator[100] ={ 0 };
	int		index = 0;

	char	stack[100] = { 0 };
	int		stacki[100] = { 0 };
	int		top = -1;
	
	int		temp = 0;//����ƴд������
	int		flag = 0;//��ʾ��ǰ�Ƿ�����ƴд����

	scanf("%s", str);

	//��׺���ʽת��׺���ʽ
	while (1)
	{
		if (*p >= '0' && *p <= '9')//������һ������
		{
			flag = 1;
			temp *= 10;
			temp += *p - '0';
		}
		else//������һ�����ţ����ַ����Ѿ�������
		{
			if (flag)//�����ƴдһ�����֣����Ƚ��������
			{
				num[index] = temp;
				operator[index] = '!';
				index++;
				flag = temp = 0;
			}
			if (!*p)//����ַ����Ѿ�����
			{
				//���գ���ջԪ��ȫ����ջ
				while (top >= 0) operator[index++] = stack[top--];
				break;
			}
			else//����һ������
			{
				//���ջ��ʱ�������Ϊ�����ţ���ջ
				if (top == -1 || *p == '(')stack[++top] = *p;
				else if (*p == ')')//����������ţ���ջ��������
				{
					while (top >= 0 && stack[top] != '(')
					{
						operator[index++] = stack[top--];
					}
					--top;
				}
				else if (*p == '*' || *p == '/')//����ǳ˳�����˳���ջ���·�����ջ
				{
					while (top >= 0 && (stack[top] == '*'||stack[top]=='/'))
					{
						operator[index++] = stack[top--];
					}
					stack[++top] = *p;
				}
				else //����ǼӼ��������������ջ���·�����ջ
				{
					while (top >= 0 && stack[top] != '(')
					{
						operator[index++] = stack[top--];
					}
					stack[++top] = *p;
				}
			}
		}
		p++;
	}

	//��׺���ʽ��ֵ
	top = -1;
	int temp1 = 0;
	int temp2 = 0;
	for (int i = 0; i < index; i++)
	{
		if (operator[i] == '!')//������ջstacki
		{
			stacki[++top] = num[i];
		}
		else//��������
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
	//���ս����stacki[0]
	int result = stacki[0];
	printf("%s=%d", str, result);

	return 0;
}

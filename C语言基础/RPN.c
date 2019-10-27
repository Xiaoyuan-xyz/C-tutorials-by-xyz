#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main_rpn()
{
	char	str[100] = { 0 };
	char*	p = str;
	
	int		num[100] = { 0 };//后缀表达式
	char	operator[100] = { 0 };
	int		index = 0;

	char	stack[100] = { 0 };//符号栈
	int		stacki[100] = { 0 };//数字栈
	int		top = -1;//栈顶序号

	int		temp = 0, temp1 = 0, temp2 = 0;
	int		flag = 0;//当前是否在拼写一个数字

	scanf("%s", str);
	while (1)//中缀表达式转后缀表达式
	{
		if (*p >= '0' && *p <= '9')//如果读到一个数字字符
		{
			flag = 1;//现在在拼写数字
			temp *= 10;
			temp += *p - '0';
		}
		else//遇到了符号或者字符串已经结束了
		{
			if (flag)//如果正在拼写数字，就将数字给到num
			{
				operator[index] = '!';
				num[index++] = temp;
				flag = temp = 0;//现在不拼写数字了
			}
			if (!*p)//如果字符串结束了
			{
				while (top>=0) operator[index++] = stack[top--];//剩余符号出栈
				break;
			}
			else//如果是一个符号
			{
				if (top < 0 || *p == '(') stack[++top] = *p;//栈为空或遇到左括号则入栈
				else if (*p == ')')//遇到右括号，出栈至左括号
				{
					while (top >= 0 && stack[top] != '(')//出栈到左括号
					{
						operator[index++] = stack[top--];
					}
					top--;//左括号出栈
				}
				else if (*p == '*' || *p == '/')//遇到乘除，乘除出栈
				{
					while (top >= 0 && (stack[top] == '*' || stack[top] == '/'))
					{
						operator[index++] = stack[top--];
					}
					stack[++top] = *p;//乘除号进栈
				}
				else //加号和减号
				{
					while (top >= 0&& stack[top] != '(')//遇到加减，四则运算四则运算出栈
					{
						operator[index++] = stack[top--];
					}
					stack[++top] = *p;//加减号进栈
				}
			}
		}
		p++;
	}

	top = -1;//计算后缀表达式
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
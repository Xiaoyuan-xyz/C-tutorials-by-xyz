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
	
	int		temp = 0;//正在拼写的数字
	int		flag = 0;//表示当前是否正在拼写数字

	scanf("%s", str);

	//中缀表达式转后缀表达式
	while (1)
	{
		if (*p >= '0' && *p <= '9')//读到了一个数字
		{
			flag = 1;
			temp *= 10;
			temp += *p - '0';
		}
		else//读到了一个符号，或字符串已经结束了
		{
			if (flag)//如果在拼写一个数字，就先将数字输出
			{
				num[index] = temp;
				operator[index] = '!';
				index++;
				flag = temp = 0;
			}
			if (!*p)//如果字符串已经结束
			{
				//最终，将栈元素全部出栈
				while (top >= 0) operator[index++] = stack[top--];
				break;
			}
			else//读到一个符号
			{
				//如果栈空时，或符号为左括号，入栈
				if (top == -1 || *p == '(')stack[++top] = *p;
				else if (*p == ')')//如果是右括号，出栈到左括号
				{
					while (top >= 0 && stack[top] != '(')
					{
						operator[index++] = stack[top--];
					}
					--top;
				}
				else if (*p == '*' || *p == '/')//如果是乘除，则乘除出栈，新符号入栈
				{
					while (top >= 0 && (stack[top] == '*'||stack[top]=='/'))
					{
						operator[index++] = stack[top--];
					}
					stack[++top] = *p;
				}
				else //如果是加减，则四则运算出栈，新符号入栈
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

	//后缀表达式求值
	top = -1;
	int temp1 = 0;
	int temp2 = 0;
	for (int i = 0; i < index; i++)
	{
		if (operator[i] == '!')//数字入栈stacki
		{
			stacki[++top] = num[i];
		}
		else//符号运算
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
	//最终结果是stacki[0]
	int result = stacki[0];
	printf("%s=%d", str, result);

	return 0;
}

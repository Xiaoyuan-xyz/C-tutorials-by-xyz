#include <stdio.h>

#if 0
long a = 10000, b, c = 2800, d, e, f[2801], g;

int main()
{
	for (; b - c;)f[b++] = a / 5;
	for (; d = 0, g = c * 2; c -= 14, printf("%.4d", e + d / a), e = d % a)
		for (b = c; d += f[b] * a, f[b] = d % --g, d /= g--, --b; d *= b);
	return 0;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{

	int n = 9;
	int d = 500 / n;

	int x = 720.0 / 1920 * 65536;
	int y = 320.0 / 1080 * 65536;

	int dx = 500.0 / n / 1920 * 65536;
	int dy = 500.0 / n / 1080  * 65536;

	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	for (int k = 0; k < 10; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x + i * dx, y + j * dy, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				Sleep(1);
			}
		}
	}
	return 0;
}
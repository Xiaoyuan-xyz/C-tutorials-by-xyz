#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LEN 20

void insertion_sort(int* arr, int len)
{
	for (int i = 1; i < len; i++)
	{
		int temp = arr[i], j;
		for (j = i; j > 0 && temp < arr[j - 1]; j--)
		{
			arr[j] = arr[j - 1];
		}
		arr[j] = temp;
	}
}

void selection_sort(int* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		//Ѱ����Сֵ�ı��min
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}

		//����
		if (min != i)
		{
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

void bubble_sort(int* arr, int len) 
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void print_array(int* arr,int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d,", arr[i]);
	}
	printf("\n");
}

//�������ֻ��ʾ��ԭ���鰴��һ��Ԫ�ط�Ϊ�����ٷֱ�����
void quick_sort_1(int* arr, int len)
{
	int pivot = arr[0];
	int low = 0, high = len - 1;
	while (1)
	{
		while (arr[high] >= pivot)high--;
		if (high <= low)
		{
			arr[low] = pivot;
			print_array(arr, len);
			bubble_sort(arr, low);
			bubble_sort(arr + low + 1, len - low - 1);
			break;
		}
		arr[low] = arr[high];
		print_array(arr, len);

		while (arr[low] <= pivot)low++;
		if (low >= high)
		{
			arr[high] = pivot;
			print_array(arr, len);
			bubble_sort(arr, high);
			bubble_sort(arr + high + 1, len - high - 1);
			break;
		}
		arr[high] = arr[low];
		print_array(arr, len);
	}
}

int main()
{
	int test[] = { 4,1,5,2,3 };
	printf("��������ǰ��");
	print_array(test, 5);
	quick_sort_1(test, 5);
	printf("���������");
	print_array(test, 5);


	srand((unsigned)time(NULL));
	int arr[LEN];
	for (int i = 0; i < LEN; i++)
	{
		arr[i] = rand() % 100;
	}
	printf("��������ǰ��\n");
	print_array(arr, LEN);

	int arr2[LEN];
	memcpy(arr2, arr, LEN * sizeof(int));

	quick_sort_1(arr, LEN);
	printf("���Ǵ������ð�ݣ�");
	print_array(arr, LEN);

	bubble_sort(arr2, LEN);
	printf("��ֻ����ͨ��ð�ݣ�");
	print_array(arr2, LEN);
	return 0;
}
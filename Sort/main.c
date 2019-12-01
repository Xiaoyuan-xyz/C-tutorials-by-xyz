#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>

#define LEN 50000
typedef void (*p_sort_func)(int*, int);

void swap_element(int* n1, int* n2)
{
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

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
		//寻找最小值的编号min
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}

		//交换
		if (min != i)swap_element(arr + i, arr + min);
	}
}

void bubble_sort(int* arr, int len) 
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])swap_element(arr + j, arr + j + 1);
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

//这个函数只表示把原数组按第一个元素分为两组再分别排序
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

//这个函数只表示把原数组按第一个元素用交换的方式分为两组再分别排序
void quick_sort_2(int* arr, int len)
{
	int low = 0, high = len;
	int temp = arr[0];
	while (1)
	{
		while (arr[++low] < temp && low < len - 1);
		while (arr[--high] > temp);
		if (low >= high)break;
		swap_element(arr + low, arr + high);
	}
	swap_element(arr, arr + high);
	insertion_sort(arr, high);
	insertion_sort(arr + high + 1, len - high - 1);
}

void quick_sort(int* arr, int len)
{
	if (len > 1)
	{
		int low = 0, high = len;
		int temp = arr[0];
		while (1)
		{
			while (arr[++low] < temp && low < len - 1);
			while (arr[--high] > temp);
			if (low >= high)break;
			swap_element(arr + low, arr + high);
		}
		swap_element(arr, arr + high);
		quick_sort(arr, high);
		quick_sort(arr + high + 1, len - high - 1);
	}
	
}

void set_three_sample_mid_to_begin(int* arr, int len)
{
	if (arr[len / 2] > arr[len - 1])swap_element(arr + len / 2, arr + len - 1);
	if (arr[0] > arr[len - 1])swap_element(arr, arr + len - 1);
	if (arr[len / 2] > arr[0])swap_element(arr + len / 2, arr);
}

void quick_sort_sample_mid(int* arr, int len)
{
	if (len > 1)
	{
		int low = 0, high = len;

		set_three_sample_mid_to_begin(arr, len);

		int temp = arr[0];
		while (1)
		{
			while (arr[++low] < temp && low < len - 1);
			while (arr[--high] > temp);
			if (low >= high)break;
			swap_element(arr + low, arr + high);
		}
		swap_element(arr, arr + high);
		quick_sort_sample_mid(arr, high);
		quick_sort_sample_mid(arr + high + 1, len - high - 1);
	}

}

void quick_sort_mid_insert(int* arr, int len)
{
	if (len <= 20)
	{
		insertion_sort(arr, len);
		return;
	}
	int low = 0, high = len;
	set_three_sample_mid_to_begin(arr, len);
	int temp = arr[0];
	while (1)
	{
		while (arr[++low] < temp && low < len - 1);
		while (arr[--high] > temp);
		if (low >= high)break;
		swap_element(arr + low, arr + high);
	}
	swap_element(arr, arr + high);
	quick_sort_mid_insert(arr, high);
	quick_sort_mid_insert(arr + high + 1, len - high - 1);
}

void quick_sort_mid_insert_assemble(int* arr, int len)
{
	if (len <= 20)
	{
		insertion_sort(arr, len);
		return;
	}
	int low = 0, high = len;
	int left = 0, right = len;
	set_three_sample_mid_to_begin(arr, len);
	int temp = arr[0];
	while (1)
	{
		while (arr[++low] <= temp && high > low&& low < len)
			if (arr[low] == temp)swap_element(arr + low, arr + (++left));
		while (arr[--high] >= temp && high > low&& high > 0)
			if (arr[high] == temp)swap_element(arr + high, arr + (--right));
		if (low >= high)break;
		swap_element(arr + low, arr + high);
	}
	while (left >= 0)
		swap_element(arr + (high--), arr + (left--));
	while (right <= len - 1)
		swap_element(arr + (low++), arr + (right++));
	quick_sort_mid_insert_assemble(arr, high+1);
	quick_sort_mid_insert_assemble(arr + low, len - low);
}

void sort(p_sort_func func, int* arr_unsorted, int len, char* msg_sort)
{
	int* arr = (int*)malloc(sizeof(int) * len);
	if (arr == NULL) return;
	memcpy(arr, arr_unsorted, len * sizeof(int));
	ULONGLONG before, after;
	before = GetTickCount64();
	func(arr, len);
	after = GetTickCount64();
	printf("%s:%I64d\t", msg_sort, after - before);
	free(arr);
}

void sort_test(int* arr, int len, char* msg_arr)
{
	printf("%s数组[%d]生成完毕:\n", msg_arr, len);

	//sort(bubble_sort, arr, len, "冒泡排序");
	sort(selection_sort, arr, len, "选择排序");
	sort(insertion_sort, arr, len, "插入排序");
	//sort(quick_sort, arr, len, "快速排序");
	sort(quick_sort_sample_mid, arr, len, "快排+取中");
	sort(quick_sort_mid_insert, arr, len, "快排+取中+插入");
	sort(quick_sort_mid_insert_assemble, arr, len, "快排+取中+插入+聚集");
	printf("\n");
}

int main()
{
	srand((unsigned)time(NULL));
	int* arr = (int*)malloc(sizeof(int) * LEN);
	if (arr == NULL)return;
	for (int i = 0; i < LEN; i++)
	{
		arr[i] = rand() % 10000;
	}
	sort_test(arr, LEN, "随机");
	for (int i = 0; i < LEN; i++)
	{
		arr[i] = i;
	}
	sort_test(arr, LEN, "升序");
	for (int i = 0; i < LEN; i++)
	{
		arr[i] = LEN - i;
	}
	sort_test(arr, LEN, "倒序");
	for (int i = 0; i < LEN; i++)
	{
		arr[i] = rand() % 50;
	}
	sort_test(arr, LEN, "重复");
	for (int i = 0; i < LEN; i++)
	{
		arr[i] = rand() % 2;
	}
	sort_test(arr, LEN, " 0-1");
	
	return 0;
}
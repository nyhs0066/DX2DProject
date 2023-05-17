#include "mysort_function.h"

void selection_sort(int* arr, int len)
{
	int idx = 0;
	int temp = 0;

	for (int i = 0; i < len; i++)
	{
		idx = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[idx] > arr[j]) idx = j;
		}

		temp = arr[idx];
		arr[idx] = arr[i];
		arr[i] = temp;
	}
}

void bubble_sort(int* arr, int len)
{
	int temp = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void insertion_sort(int* arr, int len)
{
	int idx, key, temp;

	for (int i = 0; i < len; i++)
	{
		key = arr[i];
		idx = i;

		while (idx > 0 && arr[idx - 1] > key) { idx--; }

		for (int j = i - 1; j >= idx; j--)
		{
			temp = arr[j];
			arr[j] = arr[j + 1];
			arr[j + 1] = temp;
		}

		arr[idx] = key;
	}
}

void shell_sort_sub(int* arr, int len, int gap, int st)
{
	int idx, key, temp;

	for (int i = st; i < len; i += gap)
	{
		key = arr[i];
		idx = i;

		while (idx > st && arr[idx - gap] > key) { idx -= gap; }

		for (int j = i - gap; j >= idx; j -= gap)
		{
			temp = arr[j];
			arr[j] = arr[j + gap];
			arr[j + gap] = temp;
		}

		arr[idx] = key;
	}
}

void shell_sort(int* arr, int len)
{
	int interval = len;

	while (interval > 1)
	{
		interval = interval / 3 + 1;

		for (int k = 0; k < interval; k++)
		{
			shell_sort_sub(arr, len, interval, k);
		}
	}
}

int partition(int* arr, int st, int ed)
{
	int key = arr[ed];
	int pivot = st;
	int idx = ed;
	int temp;

	while (pivot < idx)
	{
		if (key > arr[pivot]) { pivot++; }
		else
		{
			arr[idx--] = arr[pivot];
			arr[pivot] = arr[idx];
		}
	}

	arr[pivot] = key;

	return pivot;
}

void quick_sort_sub(int* arr, int len, int st, int ed)
{
	if (st >= ed) { return; }

	int pivot = partition(arr, st, ed);

	quick_sort_sub(arr, len, st, pivot - 1);
	quick_sort_sub(arr, len, pivot + 1, ed);
}

void quick_sort(int* arr, int len)
{
	int st = 0, ed = len - 1;
	quick_sort_sub(arr, len, st, ed);
}

void merge_sort_sub(int* arr, int st, int ed, int* Lsub, int* Rsub)
{
	if (st == ed) { return; }

	int mid = (st + ed) / 2;
	int lenL = mid - st + 1, lenR = ed - mid;
	int curL = 0, curR = 0;

	merge_sort_sub(arr, st, mid, Lsub, Rsub);
	merge_sort_sub(arr, mid + 1, ed, Lsub, Rsub);

	for (int i = 0; i < lenL; i++) { Lsub[i] = arr[i + st]; }
	for (int i = 0; i < lenR; i++) { Rsub[i] = arr[i + mid + 1]; }
	Lsub[lenL] = Rsub[lenR] = 1 << 30;

	for (int i = st; i <= ed; i++)
	{
		if (Lsub[curL] <= Rsub[curR]) { arr[i] = Lsub[curL++]; }
		else { arr[i] = Rsub[curR++]; }
	}
}

void merge_sort(int* arr, int len)
{
	int* Lsub = new int[len / 2 + 2];
	int* Rsub = new int[len / 2 + 2];

	merge_sort_sub(arr, 0, len - 1, Lsub, Rsub);

	delete[] Lsub, Rsub;
}

void heapify(int* arr, int len, int idx)
{
	if (idx >= len) return;

	int left = idx * 2;
	int right = idx * 2 + 1;
	int max = idx;
	int temp;

	if (right <= len && arr[right] > arr[max]) { max = right; }

	if (arr[left] > arr[max]) { max = left; }

	if (idx != max)
	{
		temp = arr[max];
		arr[max] = arr[idx];
		arr[idx] = temp;

		if (max <= len / 2) { heapify(arr, len, max); }
	}
}

void buildHeap(int* arr, int len)
{
	for (int i = len / 2; i > 0; i--) { heapify(arr, len, i); }
}

void heap_sort(int* arr, int len)
{
	buildHeap(arr, len);

	int temp;

	for (int i = len - 1; i > 1; i--)
	{
		temp = arr[i];
		arr[i] = arr[1];
		arr[1] = temp;

		heapify(arr, i - 1, 1);
	}
}
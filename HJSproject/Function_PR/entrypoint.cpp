#include "myfunc.h"
#include "mysort_function.h"
#include "mydijkstra.h"

#define MYLEN 7
#define VERIFIED

int main()
{
#ifndef VERIFIED

	//output();

	int needSort[7] = { 4, 8, 9, 1, 2, 5, 3 };

	selection_sort(needSort, MYLEN);
	bubble_sort(needSort, MYLEN);
	insertion_sort(needSort, MYLEN);
	shell_sort(needSort, MYLEN);
	quick_sort(needSort, MYLEN);
	merge_sort(needSort, MYLEN);
	heap_sort(needSort, MYLEN);	//4 dismissed;

	for (int i = 0; i < MYLEN; i++)
	{
		cout << needSort[i] << ' ';
	}

#endif //!VERIFIED

	Q1();


}
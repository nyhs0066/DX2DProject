#pragma once

////////////////////////////
//정렬 알고리즘의 간략한 구현
////////////////////////////

//선택 정렬
void selection_sort(int* arr, int len);

//거품 정렬
void bubble_sort(int* arr, int len);

//삽입 정렬
void insertion_sort(int* arr, int len);

//셸 정렬
void shell_sort_sub(int* arr, int len, int gap, int st);
void shell_sort(int* arr, int len);

//퀵 정렬
int partition(int* arr, int st, int ed);
void quick_sort_sub(int* arr, int len, int st, int ed);
void quick_sort(int* arr, int len);

//합병 정렬
void merge_sort_sub(int* arr, int st, int ed, int* Lsub, int* Rsub);
void merge_sort(int* arr, int len);

//힙 정렬
void buildHeap(int* arr, int len);
void heapify(int* arr, int len, int idx);
void heapsort(int* arr, int len);
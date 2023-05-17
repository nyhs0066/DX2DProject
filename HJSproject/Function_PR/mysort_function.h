#pragma once

////////////////////////////
//���� �˰����� ������ ����
////////////////////////////

//���� ����
void selection_sort(int* arr, int len);

//��ǰ ����
void bubble_sort(int* arr, int len);

//���� ����
void insertion_sort(int* arr, int len);

//�� ����
void shell_sort_sub(int* arr, int len, int gap, int st);
void shell_sort(int* arr, int len);

//�� ����
int partition(int* arr, int st, int ed);
void quick_sort_sub(int* arr, int len, int st, int ed);
void quick_sort(int* arr, int len);

//�պ� ����
void merge_sort_sub(int* arr, int st, int ed, int* Lsub, int* Rsub);
void merge_sort(int* arr, int len);

//�� ����
void buildHeap(int* arr, int len);
void heapify(int* arr, int len, int idx);
void heapsort(int* arr, int len);
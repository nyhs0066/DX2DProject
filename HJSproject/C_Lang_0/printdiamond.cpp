#include "practice.h"
using std::cout;
using std::cin;

void print_Diamond()
{
	//��¹��ڴ� 0���� �Ѵ�.

	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	char input;
	int num, wsp, cur, pivot;

	std::cout << "����� ���ڿ� �� ��(Ȧ��)�� �������� �����Ͽ� �Է��Ͻÿ�. \n";
	cin >> input >> num;
	pivot = num / 2;

	//���� ����ȭ
	for (int i = 0; i < num; i++)
	{
		(i > pivot) ? (wsp = i - pivot) : (wsp = pivot - i);

		for (cur = 0; cur < wsp; cur++) { cout << ' '; }
		for (cur = 0; cur < ((pivot - wsp)<<1) + 1; cur++) { cout << input; }
		cout << '\n';
	}

	/*
	//��ܺ�
	for (int i = 0; i < num / 2; i++)
	{
		for (int j = num / 2 - i; j > 0; j--) { cout << ' '; }
		for (int j = 0; j < (i << 1) + 1; j++) { cout << input; }
		cout << '\n';
	}
	//�ߴܺ�
	for (int j = 0; j < num; j++) { cout << input; }
	cout << '\n';

	//�ϴܺ�
	for (int i = num / 2 - 1; i >= 0; i--)
	{
		for (int j = num / 2 - i; j > 0; j--) { cout << ' '; }
		for (int j = 0; j < (i << 1) + 1; j++) { cout << input; }
		cout << '\n';
	}
	*/
}
#include "practice.h"
using std::cout;
using std::cin;

void print_Diamond()
{
	//출력문자는 0으로 한다.

	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	char input;
	int num, wsp, cur, pivot;

	std::cout << "출력할 문자와 줄 수(홀수)를 공백으로 구분하여 입력하시오. \n";
	cin >> input >> num;
	pivot = num / 2;

	//로직 간소화
	for (int i = 0; i < num; i++)
	{
		(i > pivot) ? (wsp = i - pivot) : (wsp = pivot - i);

		for (cur = 0; cur < wsp; cur++) { cout << ' '; }
		for (cur = 0; cur < ((pivot - wsp)<<1) + 1; cur++) { cout << input; }
		cout << '\n';
	}

	/*
	//상단부
	for (int i = 0; i < num / 2; i++)
	{
		for (int j = num / 2 - i; j > 0; j--) { cout << ' '; }
		for (int j = 0; j < (i << 1) + 1; j++) { cout << input; }
		cout << '\n';
	}
	//중단부
	for (int j = 0; j < num; j++) { cout << input; }
	cout << '\n';

	//하단부
	for (int i = num / 2 - 1; i >= 0; i--)
	{
		for (int j = num / 2 - i; j > 0; j--) { cout << ' '; }
		for (int j = 0; j < (i << 1) + 1; j++) { cout << input; }
		cout << '\n';
	}
	*/
}
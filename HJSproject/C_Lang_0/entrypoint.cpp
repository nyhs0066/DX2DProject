#include "practice.h"
#include "salaryman.h"
using std::cout;

int main()
{
	Employee* group[10] =
	{
		new Employee_Hour("권상우", STAFF, HOURLY, 200),
		new Employee_Hour("조인성", STAFF, HOURLY, 220),
		new Employee_Month("감우성", AM, MONTHLY, 3),
		new Employee_Month("강동원", AM, MONTHLY, 5),
		new Employee_Year("황정민", SC, YEARLY, 3),
		new Employee_Month("박중훈", SC, MONTHLY, 15),
		new Employee_Month("최민식", GM, MONTHLY, 20),
		new Employee_Year("정진영", GM, YEARLY, 3),
		new Employee_Hour("안성기", DIR, HOURLY, 50),
		new Employee_Year("송강호", DIR, YEARLY, 4),
	};

	int sum = 0;

	for (int i = 0; i < 10; i++) { sum += group[i]->getSalary(); }
	cout << sum << "만원\n";
	for (int i = 0; i < 10; i++) { delete group[i]; }
}

// 프로그램 디버그 / 계속 진행하기 : <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴
// 중단점(break point) 설정 : <F9>
// 프로시저 단위 실행 : <F10>
// 디버그시 한줄 씩 실행 : <F11>
// 디버그 중지 : shift + <F5>
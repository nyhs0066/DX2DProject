#include <iostream>
using namespace std;

int main()
{
	float ret = 0.0f;
	int cnt = 1;

	for (int i = 1; i <= 10; i++)
	{
		ret = 0.0f;
		
		for (int j = 1; j <= cnt; j++)
		{
			ret += 1.0f / j;
		}

		cnt *= 10;
		cout << ret << '\n';
	}

	
}
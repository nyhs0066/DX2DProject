#include "myrandom.h"

int main()
{
	MyRND test;

	test.setI_DistRange(1, 100);
	test.setLL_DistRange((long long)2 << 33, (long long)2 << 34);
	test.setF_DistRange(0.0f, 1.0f);
	test.setD_DistRange(0.0f, 1.0f);

	std::cout << "[int distribution]\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << test.getI() << '\n';
	}

	std::cout << "[long long distribution]\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << test.getLL() << '\n';
	}

	std::cout << "[float distribution]\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << test.getF() << '\n';
	}

	std::cout << "[double distribution]\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << test.getD() << '\n';
	}
}
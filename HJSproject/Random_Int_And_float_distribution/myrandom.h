#pragma once
#include <iostream>
#include <iomanip>
#include <random>

class MyRND
{
public:
	std::random_device rd;
	std::default_random_engine gen;	//메르센 트위스터 난수 엔진

	std::uniform_int<int>::param_type			iParam;
	std::uniform_int<long long>::param_type		llParam;
	std::uniform_real<float>::param_type		fParam;
	std::uniform_real<double>::param_type		dParam;

	std::uniform_int_distribution<int>			iDist;
	std::uniform_int_distribution<long long>	llDist;
	std::uniform_real_distribution<float>		fDist;
	std::uniform_real_distribution<double>		dDist;

	MyRND();
	~MyRND();

	void setI_DistRange(int min, int max);
	void setLL_DistRange(long long min, long long max);
	void setF_DistRange(float min, float max);
	void setD_DistRange(double min, double max);

	std::pair<int, int> getI_DRange();
	std::pair<long long, long long> getLL_DRange();
	std::pair<float, float> getF_DRange();
	std::pair<double, double> getD_DRange();

	int getI();
	long long getLL();
	float getF();
	double getD();
};
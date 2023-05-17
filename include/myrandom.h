#pragma once
#include "myunih.h"

class MyRND : public Singleton<MyRND>
{
	friend class Singleton<MyRND>;
private:
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

	std::uniform_int_distribution<int>			iTDist;
	std::uniform_int_distribution<long long>	llTDist;
	std::uniform_real_distribution<float>		fTDist;
	std::uniform_real_distribution<double>		dTDist;

	MyRND();
public:
	~MyRND();

	void setIntDistRange(int min, int max);
	void setLongLongDistRange(long long min, long long max);
	void setFloatDistRange(float min, float max);
	void setDoubleDistRange(double min, double max);

	std::pair<int, int> getI_DRange();
	std::pair<long long, long long> getLL_DRange();
	std::pair<float, float> getF_DRange();
	std::pair<double, double> getD_DRange();

	int getI();
	int getI(int min, int max);
	long long getLL();
	long long getLL(long long min, long long max);
	float getF();
	float getF(float min, float max);
	double getD();
	double getD(double min, double max);
};

#define MYRND							MyRND::getInstance()
#define MYRND_IRANGE(imin, imax)		MyRND::getInstance().setIntDistRange(imin, imax)
#define MYRND_LLRANGE(llmin, llmax)		MyRND::getInstance().setLongLongDistRange(llmin, llmax)
#define MYRND_FRANGE(fmin, fmax)		MyRND::getInstance().setFloatDistRange(fmin, fmax)
#define MYRND_DRANGE(dmin, dmax)		MyRND::getInstance().setDoubleDistRange(dmin, dmax)
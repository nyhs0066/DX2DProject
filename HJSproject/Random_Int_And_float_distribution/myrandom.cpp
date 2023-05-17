#include "myrandom.h"

MyRND::MyRND() : gen(rd())
{
	setI_DistRange(0, 1);
	setLL_DistRange(0, 1);
	setF_DistRange(0.0f, 1.0f);
	setD_DistRange(0.0f, 1.0f);
}

MyRND::~MyRND()
{
}

void MyRND::setI_DistRange(int min, int max)
{
	iParam._Init(min, max);
	iDist.param(iParam);
}

void MyRND::setLL_DistRange(long long min, long long max)
{
	llParam._Init(min, max);
	llDist.param(llParam);
}

void MyRND::setF_DistRange(float min, float max)
{
	fParam._Init(min, max);
	fDist.param(fParam);
}

void MyRND::setD_DistRange(double min, double max)
{
	dParam._Init(min, max);
	dDist.param(dParam);
}

std::pair<int, int> MyRND::getI_DRange()
{
	std::uniform_int<int>::param_type temp = iDist.param();
	return std::pair<int, int>(temp._Min, temp._Max);
}

std::pair<long long, long long> MyRND::getLL_DRange()
{
	std::uniform_int<long long>::param_type temp = llDist.param();
	return std::pair<long long, long long>(temp._Min, temp._Max);
}

std::pair<float, float> MyRND::getF_DRange()
{
	std::uniform_real<float>::param_type temp = fDist.param();
	return std::pair<float, float>(temp._Min, temp._Max);
}

std::pair<double, double> MyRND::getD_DRange()
{
	std::uniform_real<double>::param_type temp = dDist.param();
	return std::pair<double, double>(temp._Min, temp._Max);
}

int MyRND::getI()
{
	return iDist(gen);
}

long long MyRND::getLL()
{
	return llDist(gen);
}

float MyRND::getF()
{
	return fDist(gen);
}

double MyRND::getD()
{
	return dDist(gen);
}

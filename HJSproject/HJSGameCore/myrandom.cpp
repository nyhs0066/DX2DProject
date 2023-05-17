#include "myrandom.h"

MyRND::MyRND() : gen(rd())
{
	setIntDistRange(0, 1);
	setLongLongDistRange(0, 1);
	setFloatDistRange(0.0f, 1.0f);
	setDoubleDistRange(0.0f, 1.0f);
}

MyRND::~MyRND()
{
}

void MyRND::setIntDistRange(int min, int max)
{
	iParam._Init(min, max);
	iDist.param(iParam);
}

void MyRND::setLongLongDistRange(long long min, long long max)
{
	llParam._Init(min, max);
	llDist.param(llParam);
}

void MyRND::setFloatDistRange(float min, float max)
{
	fParam._Init(min, max);
	fDist.param(fParam);
}

void MyRND::setDoubleDistRange(double min, double max)
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

int MyRND::getI(int min, int max)
{
	std::uniform_int<int>::param_type temp(min, max);
	iTDist.param(temp);
	return iTDist(gen);
}

long long MyRND::getLL()
{
	return llDist(gen);
}

long long MyRND::getLL(long long min, long long max)
{
	std::uniform_int<long long>::param_type temp(min, max);
	llTDist.param(temp);
	return llTDist(gen);
}

float MyRND::getF()
{
	return fDist(gen);
}

float MyRND::getF(float min, float max)
{
	std::uniform_real<float>::param_type temp(min, max);
	fTDist.param(temp);
	return fTDist(gen);
}

double MyRND::getD()
{
	return dDist(gen);
}

double MyRND::getD(double min, double max)
{
	std::uniform_real<double>::param_type temp(min, max);
	dTDist.param(temp);
	return dTDist(gen);
}

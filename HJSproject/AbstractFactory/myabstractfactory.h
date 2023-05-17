#pragma once
#include <iostream>

using namespace std;

class AbstractFactory
{
public:
	virtual void createObjectA() = 0;
	virtual void createObjectB() = 0;
};

class FactoryA : public AbstractFactory
{
public:
	void createObjectA() override
	{
		cout << 'A' << "Object : Made in Factory : " << 'A' << "\n";
	}
	void createObjectB() override
	{
		cout << 'B' << "Object : Made in Factory : " << 'A' << "\n";
	}
};

class FactoryB : public AbstractFactory
{
public:
	void createObjectA() override
	{
		cout << 'A' << "Object : Made in Factory : " << 'B' << "\n";
	}
	void createObjectB() override
	{
		cout << 'B' << "Object : Made in Factory : " << 'B' << "\n";
	}
};
#include "salaryman.h"

Employee::Employee(const char* name, POSITION position, KIND_OF_SALARY kindOfSalary)
{
	strcpy_s(this->name, 8, name);
	this->position = position;
	this->kindOfSalary = kindOfSalary;
}

Employee_Hour::Employee_Hour(const char* name, POSITION position,
	KIND_OF_SALARY kindOfSalary, int monthlyWorkingTime) : Employee(name, position, kindOfSalary)
{
	this->monthlyWorkingTime = monthlyWorkingTime;
}

int Employee_Hour::getSalary()
{
	return monthlyWorkingTime * pow(2.0f, position);
}

Employee_Month::Employee_Month(const char* name, POSITION position, 
	KIND_OF_SALARY kindOfSalary, int workedYear) : Employee(name, position, kindOfSalary)
{
	this->workedYear = workedYear;
}

int Employee_Month::getSalary()
{
	return 200 + position * 20 + workedYear * 5;
}

Employee_Year::Employee_Year(const char* name, POSITION position, 
	KIND_OF_SALARY kindOfSalary, int abliltyRank) : Employee(name, position, kindOfSalary)
{
	this->abliltyRank = abliltyRank;
}

int Employee_Year::getSalary()
{
	return (2000 + position * 1000 + abliltyRank * 500) / 12;
}

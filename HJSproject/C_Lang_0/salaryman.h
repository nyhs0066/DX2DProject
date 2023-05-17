#pragma once
#include <iostream>
#include <cstring>

enum KIND_OF_SALARY { HOURLY, MONTHLY, YEARLY };
enum POSITION {STAFF, AM, SC, GM, DIR};

class Employee
{
protected:
	char name[8];
	POSITION position;
	KIND_OF_SALARY kindOfSalary;

public:
	Employee(const char* name, POSITION position, KIND_OF_SALARY kindOfSalary);
	virtual ~Employee() {}
	virtual int getSalary() = 0;
};

class Employee_Hour : public Employee
{
private:
	int monthlyWorkingTime;

public:
	Employee_Hour(const char* name, POSITION position, 
		KIND_OF_SALARY kindOfSalary, int monthlyWorkingTime);
	~Employee_Hour() {}
	virtual int getSalary();
};

class Employee_Month : public Employee
{
private:
	int workedYear;

public:
	Employee_Month(const char* name, POSITION position, 
		KIND_OF_SALARY kindOfSalary, int workedYear);
	~Employee_Month() {}
	virtual int getSalary();
};

class Employee_Year : public Employee
{
private:
	int abliltyRank;

public:
	Employee_Year(const char* name, POSITION position,
		KIND_OF_SALARY kindOfSalary, int abliltyRank);
	~Employee_Year() {}
	virtual int getSalary();
};
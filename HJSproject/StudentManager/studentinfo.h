#pragma once

#include <iostream>
#include <iomanip>
#include <random>
#include <assert.h>

namespace nsp_MySTM
{
	using namespace std;
	
	#define MARGIN_OF_ERROR			1.0E-2F
	#define MAX_FIELD_NUM			6
	#define MAX_SCORE_FIELD_NUM		MAX_FIELD_NUM - 2
	#define SUBJECT_NUM_LIMIT		MAX_SCORE_FIELD_NUM - 1

	random_device					RD;
	default_random_engine			gen(RD());
	uniform_int_distribution<>		scoreDist(0, 100);
	uniform_int_distribution<>		charDist('A', 'Z');

	enum E_CATEGORY { C_NAME, C_KOR, C_MAT, C_ENG, C_SUM, C_AVG };

	class StudentInfo
	{
		friend ostream& operator<<(ostream& out, const StudentInfo& opd);
		friend istream& operator>>(istream& in, StudentInfo& opd);

	private:
		//데이터 테이블
		char				name[8];
		int					score[MAX_SCORE_FIELD_NUM];
		float				fAvg;

		//클래스 공통 변수
		static E_CATEGORY	cmpCategoryFlag;
		static const char	fieldNameArray[MAX_FIELD_NUM][6];

	public:
		//자료 설정
		void setValue(E_CATEGORY category);

		//샘플 생성
		void createSample();

		//자료 비교
		bool operator> (const StudentInfo& opd) const;
		bool operator== (const StudentInfo& opd) const;
		bool operator< (const StudentInfo& opd) const;

	public:
		//비교 방법 설정
		static void setCompareType(E_CATEGORY category);

		//인터페이스 출력
		static void printTitle();
		static void printCategory();
	};

	E_CATEGORY StudentInfo::cmpCategoryFlag = E_CATEGORY::C_NAME;

	const char StudentInfo::fieldNameArray[MAX_FIELD_NUM][6] = {
		"이름",
		"국어",
		"수학",
		"영어",
		"총점",
		"평균"
	};

	ostream& operator<<(ostream& out, const StudentInfo& opd)
	{
		size_t gap = sizeof(int);
		out << std::left
			<< std::setw(gap * 2) << opd.name << " | ";

		for (int i = 0; i <= SUBJECT_NUM_LIMIT; i++)
		{
			out << std::setw(gap) << opd.score[i] << " | ";
		}

		out << std::setw(gap * 2) << std::setprecision(2) << std::fixed <<
			opd.fAvg << " | " << '\n';

		return out;
	}

	inline istream& operator>>(istream& in, StudentInfo& opd)
	{
		char temp[8] = { 0 };
		cout << opd.fieldNameArray[0] << " : ";

		in.ignore();
		in.get(opd.name, 8);

		//원치 않은 입력값 무시
		in.ignore(numeric_limits<int>::max(), '\n');

		opd.score[SUBJECT_NUM_LIMIT] = 0;

		for (int i = 0; i < SUBJECT_NUM_LIMIT; i++)
		{
			cout << opd.fieldNameArray[i + 1] << " : "; in >> opd.score[i];

			if (in.fail())
			{
				in.clear(); in.ignore(numeric_limits<int>::max(), '\n');
				cout << "잘못된 값이 입력되었습니다. 0으로 초기화 됩니다.\n";
			}
			opd.score[SUBJECT_NUM_LIMIT] += opd.score[i];
		}

		opd.fAvg = opd.score[SUBJECT_NUM_LIMIT] / (SUBJECT_NUM_LIMIT * 1.0f);

		return in;
	}

	inline void StudentInfo::setCompareType(E_CATEGORY category)
	{
		cmpCategoryFlag = category;
	}

	inline void StudentInfo::printTitle()
	{
		size_t gap = sizeof(int);
		cout << std::left
			<< std::setw(gap * 2) << fieldNameArray[0] << " | ";

		for (int i = 1; i <= MAX_SCORE_FIELD_NUM; i++)
		{
			cout << std::setw(gap) << fieldNameArray[i] << " | ";
		}

		cout << std::setw(gap * 2) << std::setprecision(2) << std::fixed <<
			fieldNameArray[MAX_SCORE_FIELD_NUM + 1] << " | " << '\n';
	}

	inline void StudentInfo::printCategory()
	{
		for (int i = 0; i < MAX_FIELD_NUM; i++)
		{
			cout << i << " - " << fieldNameArray[i] << " | ";
		}
	}

	inline void StudentInfo::setValue(E_CATEGORY category)
	{
		switch (category)
		{
		case E_CATEGORY::C_NAME:
			cin.ignore();
			cout << fieldNameArray[(int)category] << " : "; cin.get(name, 8);
			cin.ignore(numeric_limits<int>::max(), '\n');
			break;

		case E_CATEGORY::C_AVG:
			cout << fieldNameArray[(int)category] << " : "; cin >> fAvg;
			break;

		default:
			cout << fieldNameArray[(int)category] << " : "; cin >> score[(int)category - 1];
			break;
		}
	}

	inline void StudentInfo::createSample()
	{
		int len = 3;

		for (int j = 0; j < len; j++) { name[j] = charDist(gen); }
		name[len] = '\0';

		score[SUBJECT_NUM_LIMIT] = 0;

		for (int i = 0; i < SUBJECT_NUM_LIMIT; i++)
		{
			score[i] = scoreDist(gen);
			score[SUBJECT_NUM_LIMIT] += score[i];
		}

		fAvg = score[SUBJECT_NUM_LIMIT] / (SUBJECT_NUM_LIMIT * 1.0f);
	}

	inline bool StudentInfo::operator>(const StudentInfo& opd) const
	{
		switch (cmpCategoryFlag)
		{
		case E_CATEGORY::C_NAME:
		{
			int cur = 0;
			const char* strL = this->name;
			const char* strR = opd.name;

			while (strL[cur] && strR[cur])
			{
				if (strL[cur] > strR[cur]) { return true; }
				else if (strL[cur] < strR[cur]) { return false; }
				else { cur++; }
			}

			if (strlen(strL) < strlen(strR)) { return true; }
			else { return false; }
		}
		break;
		case E_CATEGORY::C_AVG:
			return (this->fAvg > opd.fAvg);
		default:
			return (this->score[cmpCategoryFlag - 1] > opd.score[cmpCategoryFlag - 1]);
		}
	}

	inline bool StudentInfo::operator==(const StudentInfo& opd) const
	{
		bool ret = false;
		switch (cmpCategoryFlag)
		{
		case E_CATEGORY::C_NAME:
			ret = (strcmp(this->name, opd.name) ? false : true);
			break;
		case E_CATEGORY::C_AVG:
			ret = (fabsf(this->fAvg - opd.fAvg) <= MARGIN_OF_ERROR);
			break;
		default:
			ret = (this->score[cmpCategoryFlag - 1] == opd.score[cmpCategoryFlag - 1]);
			break;
		}

		return ret;
	}

	inline bool StudentInfo::operator<(const StudentInfo& opd) const
	{
		switch (cmpCategoryFlag)
		{
		case E_CATEGORY::C_NAME:
		{
			int cur = 0;
			const char* strL = this->name;
			const char* strR = opd.name;

			while (strL[cur] && strR[cur])
			{
				if (strL[cur] < strR[cur]) { return true; }
				else if (strL[cur] > strR[cur]) { return false; }
				else { cur++; }
			}

			if (strlen(strL) > strlen(strR)) { return true; }
			else { return false; }
		}
		break;
		case E_CATEGORY::C_AVG:
			return (this->fAvg < opd.fAvg);
		default:
			return (this->score[cmpCategoryFlag - 1] < opd.score[cmpCategoryFlag - 1]);
		}
	}
}
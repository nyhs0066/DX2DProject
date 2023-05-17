#pragma once

#include "studentinfo.h"
#include "myflieio.h"
#include "templatelinkedlist.h"

namespace nsp_MySTM
{
	enum MENU { LOAD, SAVE, ADD, DEL, SEARCH, SORT, SAMPLE, RESET, PRTALL, EXIT = 99 };

	class StudentManager
	{
	private:
		DoublelyLinkedList<StudentInfo> database;

#if _HAS_CXX17
		FileIOManager stFileIO;
#endif // _HAS_CXX17

	public:
		StudentManager();
		~StudentManager();

		//기능 함수

		//= 파일 입출력 =
			//지정된 이름의 파일 또는 기본값 설정된 이진형태의 파일을 읽어 온다.
		void loadFile();
		//파일을 지정된 이름 또는 기본값으로 설정된 이름의 이진 파일 형태로 저장한다. 
		void saveFile();

		//= 삽입 / 삭제 / 수정 =
			//전위 또는 후위로 데이터를 추가한다.
		void addData();
		//전위 또는 후위로 데이터를 삭제한다.
		void delData();
		//리스트를 초기화 한다.
		void resetList();

		//= 정렬 =
			//리스트를 정렬한다.
		void sortList();

		//= 검색 =
			//검색을 수행하고 작업을 결정한다.
		void searchItem();
		//카테고리에 따른 검색을 수행한다.
		void categorySearch();

		//기타 기능
			//샘플 데이터를 생성한다.
		void createSampleData();

		//인터페이스 화면 출력

		//데이터를 전부 출력한다.
		void printAll();
		//메뉴를 출력한다.
		void printMenu();
		//매니저의 타이틀을 출력한다.
		void printTitle();

		//매니저 실행 함수
		void run();
	};

	inline StudentManager::StudentManager()
	{
		printTitle();
		printMenu();
	}

	inline StudentManager::~StudentManager() {}

	inline void StudentManager::loadFile()
	{
#if _HAS_CXX17
		void* loadData = nullptr;
		int count = 0;
		size_t dataTypeSize = 0;

		stFileIO.loadFile(&loadData, count, dataTypeSize, L".stdata");

		if (loadData)
		{
			cout << "File load END\n";
			database.clearList();

			for (int i = 0; i < count; i++)
			{
				database.insertElementBack(((StudentInfo*)loadData)[i]);
			}

			delete[] loadData;
			printAll();
		}
#endif //_HAS_CXX17

#if !_HAS_CXX17
		ifstream loadFp;
		string loadFileName;

		cout << "불러올 파일의 이름 :";
		cin >> loadFileName;

		loadFp.open(loadFileName, ios::binary | ios::in);

		if (!loadFp)
		{
			cout << "File open failed : load op dismissed \n";
			return;
		}
		else
		{
			database.clearList();

			int rep;
			loadFp.read((char*)&rep, sizeof(int));

			for (int i = 0; i < rep; i++)
			{
				StudentInfo newData;
				loadFp.read((char*)&newData, sizeof(StudentInfo));
				database.insertElementBack(newData);
			}
		}

		loadFp.close();

		printAll();

		cout << "File load END \n";

#endif // !_HAS_CXX17
	}

	inline void StudentManager::saveFile()
	{
		if (!database.getLength())
		{
			cout << "리스트가 비어있습니다.\n";
			return;
		}

#if _HAS_CXX17
		int count = database.getLength();
		size_t dataTypeSize = sizeof(StudentInfo);
		StudentInfo* saveData = new StudentInfo[count];

		const Node<StudentInfo>* cur = database.findINode(0);

		for (int i = 0; i < count; i++)
		{
			saveData[i] = cur->getData();
			cur = cur->pNext;
		}

		stFileIO.saveFile((void*)saveData, count, dataTypeSize, L".stdata");

		delete[] saveData;
		saveData = nullptr;

		cout << "File save END\n";
#endif // !_HAS_CXX17

#if !_HAS_CXX17
		ofstream saveFp;
		ifstream checkFp;
		string saveFileName;
		bool option;

		cout << "0 : 저장(Database.dat) | 1 : 다른 이름으로 저장 (기본 설정값 : 0)\n";
		cout << "=> ";
		cin >> option;

		if (!option)
		{
			saveFileName = "Database.dat";
		}
		else
		{
			bool saveFlag = false;

			do
			{
				cout << "저장할 파일의 이름 :";
				cin >> saveFileName;

				checkFp.open(saveFileName, ios::binary | ios::in);

				if (!checkFp) { saveFlag = true; }
				else
				{
					checkFp.close();
					option = true;
					cout << "같은 이름의 파일이 이미 존재합니다.\n";
					cout << "0 - 덮어 쓰기 | 1 - 다른 이름으로 저장하기 (기본값 : 1)\n";
					cout << "=> ";
					cin >> option;

					if (!option) { saveFlag = true; }
				}
			} while (!saveFlag);
		}

		saveFp.open(saveFileName, ios::binary | ios::out);

		if (!saveFp)
		{
			cout << "File open failed : save op dismissed \n";
			return;
		}
		else
		{
			int rep = database.getLength();
			saveFp.write((char*)&rep, sizeof(int));

			for (int i = 0; i < rep; i++)
			{
				saveFp.write((char*)&database.findINode(i)->data, sizeof(StudentInfo));
			}
		}

		saveFp.close();

		cout << "File save END \n";
#endif // !_HAS_CXX17

		printAll();
	}

	inline void StudentManager::addData()
	{
		StudentInfo newData;
		cin >> newData;

		int flag;

		cout << "[0 - 전위 추가 | 1 - 후위 추가] : ";
		cin >> flag;
		if (cin.fail()) { throw 1; }


		if (flag) { database.insertElementBack(newData); }
		else { database.insertElement(newData); }

		printAll();
	}

	inline void StudentManager::delData()
	{
		if (database.isEmpty()) { cout << "리스트가 비어있습니다. \n"; return; }
		else
		{
			bool flag;

			cout << "[0 - 전위 삭제 | 1 - 후위 삭제] : ";
			cin >> flag;
			if (cin.fail()) { throw 1; }

			database.deleteElement(flag);

			printAll();
			return;
		}
	}

	inline void StudentManager::sortList()
	{
		bool AnD_flag;
		int category;

		cout << "=정렬 방식= (기본 정렬 방식 : 내림차순 평균)\n";
		cout << "0 - 오름차순 | 1 - 내림차순 : ";
		cin >> AnD_flag;
		if (cin.fail()) { throw 1; }

		StudentInfo::printCategory();
		cin >> category;
		if (cin.fail()) { throw 1; }


		if (category < 0 && category >= MAX_FIELD_NUM) { category = E_CATEGORY::C_AVG; }

		StudentInfo::setCompareType((E_CATEGORY)category);

		database.sortList(AnD_flag);
		printAll();
	}

	inline void StudentManager::searchItem()
	{
		int flag;
		Node<StudentInfo>* find = nullptr;

		cout << "0 - 자료 번호 검색 | 1 - 값 검색  : ";
		cin >> flag;
		if (cin.fail()) { throw 1; }

		if (!flag)
		{
			int idx;

			cout << "=자료 번호 검색=\n";
			cout << "(범위 : 0 ~ " << database.getLength() - 1 << ") : ";
			cin >> idx;
			if (cin.fail()) { throw 1; }

			find = database.findINode(idx);
		}
		else
		{
			categorySearch();

			if (database.getS_Flag())
			{
				int st = database.getS_StIdx();
				int ed = database.getS_EdIdx();
				Node<StudentInfo>* cur;

				for (int i = st; i <= ed; i++)
				{
					cur = database.getINode(i);
					cout << i - st << " | " << cur->data;
				}
				cout << '\n';

				int workIdx;

				while (true)
				{
					cout << "작업할 노드 선택 (범위 : 0 ~ " << ed - st << ") : ";
					cin >> workIdx;
					if (cin.fail()) { throw 1; }

					find = database.getINode(workIdx + database.getS_StIdx());

					if (!find) { cout << "잘못된 번호 입니다. 다시 입력해 주십시오."; }
					else { break; }
				}
			}
			else { find = nullptr; }
		}

		if (find)
		{
			cout << '\n';
			cout << find->data;

			cout << "\n= 수행할 작업 =\n";
			cout << "[ 0 - 새 원소 삽입 | 1 - 삭제 | 2 - 수정 | 이외 번호는 작업 취소 ] : ";
			cin >> flag;
			if (cin.fail()) { throw 1; }

			switch (flag)
			{
			case 0:
			{
				StudentInfo newData;
				cin >> newData;

				int flag;

				cout << "[0 - 전위 추가 | 1 - 후위 추가] : ";
				cin >> flag;
				if (cin.fail()) { throw 1; }

				if (flag) { database.insertElementBack(newData, find); }
				else { database.insertElement(newData, find); }
			}
			break;
			case 1:
				database.deleteElement(find);
				break;
			case 2:
				cin >> find->data;
				break;
			default: break;
			}
			printAll();
		}
		else
		{
			cout << "search & work END \n";
		}
	}

	inline void StudentManager::createSampleData()
	{
		int rep = 5;

		for (int i = 0; i < rep; i++)
		{
			StudentInfo newData;
			newData.createSample();
			database.insertElementBack(newData);
		}

		printAll();
	}

	inline void StudentManager::resetList()
	{
		database.clearList();

		printAll();
	}

	inline void StudentManager::categorySearch()
	{
		int category;
		StudentInfo key;

		cout << "=검색 범주= (기본 범주 : 평균)\n";
		StudentInfo::printCategory();
		cin >> category;
		if (cin.fail()) { throw 1; }

		if (category < 0 && category >= MAX_FIELD_NUM) { category = E_CATEGORY::C_AVG; }

		StudentInfo::setCompareType((E_CATEGORY)category);
		key.setValue((E_CATEGORY)category);

		database.searchNode(key);
	}

	inline void StudentManager::printAll()
	{
		system("cls");
		printTitle();

		const Node<StudentInfo>* cur = database.findINode(0);
		int idx = 0;
		if (cur)
		{
			cout << std::left << std::setw(5) << "번호 |";
			StudentInfo::printTitle();
		}

		while (cur)
		{
			cout << std::left << std::setw(5) << idx++ << "|";
			cout << cur->data;
			cur = cur->pNext;
		}
	}

	inline void StudentManager::printMenu()
	{
		cout << "[0 : 로드  | 1 : 저장  | 2 : 추가  | 3 : 제거 | 4 : 검색&작업] \n";
		cout << "[5 : 정렬  | 6 : 샘플  | 7 : 리셋  | 8 : 재출력 | 99 : 종료  ] \n";
	}

	inline void StudentManager::printTitle()
	{
		cout << "[------------------------------------------------------------]\n";
		cout << "[                      학생 관리 프로그램                    ]\n";
		cout << "[------------------------------------------------------------]\n";
		cout << "\n";
	}

	inline void StudentManager::run()
	{
		//[0 : 로드  | 1 : 저장  | 2 : 추가  | 3 : 제거 | 4 : 검색&작업  ]
		//[5 : 정렬  | 6 : 샘플  | 7 : 리셋  | 8 : 재출력 | 99 : 종료    ]

		int input;

		while (true)
		{
			try
			{
				cin >> input;
				if (cin.fail()) { throw 1; }

				system("cls");

				switch (input)
				{
				case LOAD:		loadFile();				break;
				case SAVE:		saveFile();				break;
				case ADD:		addData();				break;
				case DEL:		delData();				break;
				case SEARCH:	searchItem();			break;
				case SORT:		sortList();				break;
				case SAMPLE:	createSampleData();		break;
				case RESET:		resetList();			break;
				case PRTALL:	printAll();				break;

				case EXIT:								return;

				default:		cout << "기능이 지정되지 않은 숫자입니다. \n";
					break;
				}
			}
			catch (...)
			{
				cin.clear(); cin.ignore(numeric_limits<int>::max(), '\n');
				cout << "잘못된 입력값입니다. 수행하던 작업이 취소 됩니다.\n\n";
			}
			printMenu();
		}
	}

}
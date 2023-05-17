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

		//��� �Լ�

		//= ���� ����� =
			//������ �̸��� ���� �Ǵ� �⺻�� ������ ���������� ������ �о� �´�.
		void loadFile();
		//������ ������ �̸� �Ǵ� �⺻������ ������ �̸��� ���� ���� ���·� �����Ѵ�. 
		void saveFile();

		//= ���� / ���� / ���� =
			//���� �Ǵ� ������ �����͸� �߰��Ѵ�.
		void addData();
		//���� �Ǵ� ������ �����͸� �����Ѵ�.
		void delData();
		//����Ʈ�� �ʱ�ȭ �Ѵ�.
		void resetList();

		//= ���� =
			//����Ʈ�� �����Ѵ�.
		void sortList();

		//= �˻� =
			//�˻��� �����ϰ� �۾��� �����Ѵ�.
		void searchItem();
		//ī�װ��� ���� �˻��� �����Ѵ�.
		void categorySearch();

		//��Ÿ ���
			//���� �����͸� �����Ѵ�.
		void createSampleData();

		//�������̽� ȭ�� ���

		//�����͸� ���� ����Ѵ�.
		void printAll();
		//�޴��� ����Ѵ�.
		void printMenu();
		//�Ŵ����� Ÿ��Ʋ�� ����Ѵ�.
		void printTitle();

		//�Ŵ��� ���� �Լ�
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

		cout << "�ҷ��� ������ �̸� :";
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
			cout << "����Ʈ�� ����ֽ��ϴ�.\n";
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

		cout << "0 : ����(Database.dat) | 1 : �ٸ� �̸����� ���� (�⺻ ������ : 0)\n";
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
				cout << "������ ������ �̸� :";
				cin >> saveFileName;

				checkFp.open(saveFileName, ios::binary | ios::in);

				if (!checkFp) { saveFlag = true; }
				else
				{
					checkFp.close();
					option = true;
					cout << "���� �̸��� ������ �̹� �����մϴ�.\n";
					cout << "0 - ���� ���� | 1 - �ٸ� �̸����� �����ϱ� (�⺻�� : 1)\n";
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

		cout << "[0 - ���� �߰� | 1 - ���� �߰�] : ";
		cin >> flag;
		if (cin.fail()) { throw 1; }


		if (flag) { database.insertElementBack(newData); }
		else { database.insertElement(newData); }

		printAll();
	}

	inline void StudentManager::delData()
	{
		if (database.isEmpty()) { cout << "����Ʈ�� ����ֽ��ϴ�. \n"; return; }
		else
		{
			bool flag;

			cout << "[0 - ���� ���� | 1 - ���� ����] : ";
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

		cout << "=���� ���= (�⺻ ���� ��� : �������� ���)\n";
		cout << "0 - �������� | 1 - �������� : ";
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

		cout << "0 - �ڷ� ��ȣ �˻� | 1 - �� �˻�  : ";
		cin >> flag;
		if (cin.fail()) { throw 1; }

		if (!flag)
		{
			int idx;

			cout << "=�ڷ� ��ȣ �˻�=\n";
			cout << "(���� : 0 ~ " << database.getLength() - 1 << ") : ";
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
					cout << "�۾��� ��� ���� (���� : 0 ~ " << ed - st << ") : ";
					cin >> workIdx;
					if (cin.fail()) { throw 1; }

					find = database.getINode(workIdx + database.getS_StIdx());

					if (!find) { cout << "�߸��� ��ȣ �Դϴ�. �ٽ� �Է��� �ֽʽÿ�."; }
					else { break; }
				}
			}
			else { find = nullptr; }
		}

		if (find)
		{
			cout << '\n';
			cout << find->data;

			cout << "\n= ������ �۾� =\n";
			cout << "[ 0 - �� ���� ���� | 1 - ���� | 2 - ���� | �̿� ��ȣ�� �۾� ��� ] : ";
			cin >> flag;
			if (cin.fail()) { throw 1; }

			switch (flag)
			{
			case 0:
			{
				StudentInfo newData;
				cin >> newData;

				int flag;

				cout << "[0 - ���� �߰� | 1 - ���� �߰�] : ";
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

		cout << "=�˻� ����= (�⺻ ���� : ���)\n";
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
			cout << std::left << std::setw(5) << "��ȣ |";
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
		cout << "[0 : �ε�  | 1 : ����  | 2 : �߰�  | 3 : ���� | 4 : �˻�&�۾�] \n";
		cout << "[5 : ����  | 6 : ����  | 7 : ����  | 8 : ����� | 99 : ����  ] \n";
	}

	inline void StudentManager::printTitle()
	{
		cout << "[------------------------------------------------------------]\n";
		cout << "[                      �л� ���� ���α׷�                    ]\n";
		cout << "[------------------------------------------------------------]\n";
		cout << "\n";
	}

	inline void StudentManager::run()
	{
		//[0 : �ε�  | 1 : ����  | 2 : �߰�  | 3 : ���� | 4 : �˻�&�۾�  ]
		//[5 : ����  | 6 : ����  | 7 : ����  | 8 : ����� | 99 : ����    ]

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

				default:		cout << "����� �������� ���� �����Դϴ�. \n";
					break;
				}
			}
			catch (...)
			{
				cin.clear(); cin.ignore(numeric_limits<int>::max(), '\n');
				cout << "�߸��� �Է°��Դϴ�. �����ϴ� �۾��� ��� �˴ϴ�.\n\n";
			}
			printMenu();
		}
	}

}
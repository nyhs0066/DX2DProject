#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <filesystem>
#include <chrono>

#if _HAS_CXX17

namespace nsp_MySTM
{
	using namespace std::filesystem;
	using namespace std::chrono;

	class FileIOManager
	{
	private:
		directory_iterator			dirIt;

		vector<path>				table;
		vector<path>::iterator		pathIt;

	public:
		FileIOManager();
		~FileIOManager();

		void saveFile(void* source, int count, size_t dataTypeSize, wstring fileExtension);
		void loadFile(void** dest, int& count, size_t& dataTypeSize, wstring fileExtension);

	private:
		void searchCurDir(wstring& fileExtension);
		void printTable();
		void printTitle();
	};

	FileIOManager::FileIOManager()
	{
		pathIt = table.begin();
	}

	FileIOManager::~FileIOManager()
	{

	}

	void FileIOManager::saveFile(void* source, int count,
		size_t dataTypeSize, wstring fileExtension)
	{
		table.clear();
		searchCurDir(fileExtension);

		wstring SaveFileName;
		ofstream saveFp;
		ifstream checkFp;

		bool saveFlag = false;
		bool option;

		do
		{
			system("cls");
			printTable();
			cout << "search END \n\n";

			cout << "저장할 파일의 이름 :";
			wcin >> SaveFileName;
			SaveFileName.append(fileExtension);

			checkFp.open(SaveFileName, ios::binary | ios::in);

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
				else { SaveFileName.clear(); }
			}
		} while (!saveFlag);

		saveFp.open(SaveFileName, ios::binary | ios::out);
		assert(saveFp);

		saveFp.write((char*)&count, sizeof(int));
		saveFp.write((char*)&dataTypeSize, sizeof(size_t));
		saveFp.write((char*)source, dataTypeSize * count);

		saveFp.close();
	}

	void FileIOManager::loadFile(void** dest, int& count, size_t& dataTypeSize, wstring fileExtension)
	{
		table.clear();
		searchCurDir(fileExtension);

		ifstream loadFp;
		wstring loadFileName;

		system("cls");
		printTable();
		cout << "search END \n\n";

		cout << "불러올 파일의 이름 :";
		wcin >> loadFileName;
		loadFileName.append(fileExtension);

		loadFp.open(loadFileName, ios::binary | ios::in);
		if (!loadFp) 
		{ 
			cout << "지정한 이름의 파일이 존재하지 않습니다. \n";
			dest = nullptr;
			return;
		}
		else
		{
			loadFp.read((char*)&count, sizeof(int));
			loadFp.read((char*)&dataTypeSize, sizeof(size_t));

			*dest = new char[dataTypeSize * count];

			loadFp.read((char*)*dest, dataTypeSize * count);

			loadFp.close();
		}
	}

	void FileIOManager::searchCurDir(wstring& fileExtension)
	{
		directory_iterator key(current_path());
		dirIt = key;

		while (dirIt != end(dirIt))
		{
			const directory_entry& curEntry = *dirIt;

			if (curEntry.path().extension() == fileExtension)
			{
				table.push_back(curEntry.path());
			}

			dirIt++;
		}
	}

	void FileIOManager::printTable()
	{
		int idx = 0;

		printTitle();
		for (auto pathIt : table)
		{
			cout << idx++ << " | " << pathIt.filename();
#if _HAS_CXX20
			//GMT+9
			cout << "\t[마지막으로 수정된 시간 : " <<
				clock_cast<file_clock>(last_write_time(pathIt)) + 9h << "]\n";
#endif //_HAS_CXX20
		}
	}

	void FileIOManager::printTitle()
	{
		cout << "= 현재 디렉터리에 존재하는 지정 확장자 파일 = \n\n";
	}

}

#endif //_HAS_CXX17
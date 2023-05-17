#include "myfilereader.h"

bool myfilereader()
{
	//공백과 줄바꿈으로 되어 있는 텍스트 파일의 형식이 유니코드로 
	//작성되어 있다면 이렇게도 읽을 수 있다.
	std::wifstream wiFp;
	std::wstring buf;
	buf.resize(256);

	int num;
	int rect[4];

	wiFp.open(L"../../data/sprite_set/test_sprites/sprite_rect_list.txt", std::ios::in);

	if (!wiFp) { return false; }
	wiFp >> buf >> num;
	wiFp >> buf >> num;

	do
	{
		//buf -> filename save
		for (int i = 0; i < num; i++) 
		{ 
			wiFp >> rect[0] >> rect[1] >> rect[2] >> rect[3]; 
		}
		wiFp >> buf >> num;
	} while (buf != L"END");

	return true;
}

int main()
{
	myfilereader();
}
#include "myfilereader.h"

bool myfilereader()
{
	//����� �ٹٲ����� �Ǿ� �ִ� �ؽ�Ʈ ������ ������ �����ڵ�� 
	//�ۼ��Ǿ� �ִٸ� �̷��Ե� ���� �� �ִ�.
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
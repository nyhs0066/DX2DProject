#include "mygamecore.h"

////////////////////////////////////////////////////////////////////
//	#CreateGameCore_2
// 
//	1. shader / texture �Ŵ��� ����
//		�����̸��� �޾� ���̴��� �ؽ�ó�� �ε��Ѵ�.
//  2. shader�� texture�� ������ ���� ���� ���̴� ���� ����
//	3. timer / input / writer�� �̱��� ���� ���� - ����ȭ
//  
//	

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lCmdLine, int nCmdShow)
{
	MyGameCore test;

	bool createFlag = test.createAndShow(L"Create Texture Object2", WS_OVERLAPPEDWINDOW, 600, 600);
	if (!createFlag) { return false; }

	test.run();

	return 0;
}
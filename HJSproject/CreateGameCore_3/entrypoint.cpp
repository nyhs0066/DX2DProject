#include "mygamecore.h"

////////////////////////////////////////////////////////////////////
//	#CreateGameCore_3
// 
//	1. sampler state Ŭ���� ����
//		���� ���ø� ���¸� �����ϴ� Ŭ����
//  2. ������Ʈ�� ��������Ʈ ������ �÷��̾� ���۰� ���� ������Ʈ ����
//	

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lCmdLine, int nCmdShow)
{
	MyGameCore test;

	bool createFlag = test.createAndShow(L"Create Texture Object3", WS_OVERLAPPEDWINDOW, 600, 600);
	if (!createFlag) { return false; }

	test.run();

	return 0;
}
#include "mygamecore.h"

////////////////////////////////////////////////////////////////////
//	#CreateGameCore_1
// 
//	1. inputŬ���� ���� - �Է��� �ް� Ȯ���ϴ� Ŭ����
//		�ƹ��� ���� window�޽����� ���ư��� �Է¿� ���ؼ��� ó���ϴ� ���� �ٶ��� ����
//		������?
//	2. timerŬ���� ���� - �ð��� ��� Ŭ����. �� Ŭ������ ������ ���� �ð��� ����
//		�׷����� ó���ϰ� �ȴ�.
//	3. 
//	

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lCmdLine, int nCmdShow)
{
	MyGameCore test;

	bool createFlag = test.createAndShow(L"Create Texture Object1", WS_OVERLAPPEDWINDOW, 600, 600);
	if (!createFlag) { return false; }

	test.run();

	return 0;
}
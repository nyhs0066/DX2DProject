#include "mygamecore.h"

////////////////////////////////////////////////////////////////////
//	#CreateGameCore_0 
// 
//	1. ����̽�, ������, â ����, ���� ���� �ھ� ���� �и�
//	2. writerŬ���� ���� - ���ڿ��� ȭ�鿡 �׸��� Ŭ����
//	3. ���� ����ϴ� ����/�Լ� static���� �� ��ũ��ȭ ����
//	4. �̸� ����
//	5. TextLayout�� DWRITE_TEXT_RANGE ������ �ణ ����
//		DWRITE_TEXT_RANGE�� 1�� ���ڸ� �⺻ ������ �Ѵ�.
//		���� ��� ���� ��ġ startPosition�� 10�̸� ó�� ���ڷκ��� 10���� ������ ���ں��� �����϶�� ��
//		length�� �ش� ���̾ƿ��� ���� ���ڷκ��� �� ���� ������ �������� �����Ѵ�.
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
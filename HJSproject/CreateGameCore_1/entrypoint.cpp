#include "mygamecore.h"

////////////////////////////////////////////////////////////////////
//	#CreateGameCore_1
// 
//	1. input클래스 도입 - 입력을 받고 확인하는 클래스
//		아무리 봐도 window메시지로 날아가는 입력에 대해서만 처리하는 것이 바람직 하지
//		않을까?
//	2. timer클래스 도입 - 시간을 재는 클래스. 이 클래스의 프레임 단위 시간을 토대로
//		그래픽을 처리하게 된다.
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
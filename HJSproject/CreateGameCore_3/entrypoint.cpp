#include "mygamecore.h"

////////////////////////////////////////////////////////////////////
//	#CreateGameCore_3
// 
//	1. sampler state 클래스 도입
//		각종 샘플링 상태를 조작하는 클래스
//  2. 오브젝트에 스프라이트 입히고 플레이어 조작과 동적 오브젝트 구현
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
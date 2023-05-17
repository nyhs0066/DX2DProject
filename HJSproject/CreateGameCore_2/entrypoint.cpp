#include "mygamecore.h"

////////////////////////////////////////////////////////////////////
//	#CreateGameCore_2
// 
//	1. shader / texture 매니저 도입
//		파일이름을 받아 쉐이더와 텍스처를 로드한다.
//  2. shader와 texture의 조정을 위한 통합 쉐이더 파일 적용
//	3. timer / input / writer에 싱글톤 패턴 도입 - 전역화
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
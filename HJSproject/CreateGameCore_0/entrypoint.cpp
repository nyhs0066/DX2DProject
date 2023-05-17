#include "mygamecore.h"

////////////////////////////////////////////////////////////////////
//	#CreateGameCore_0 
// 
//	1. 디바이스, 렌더러, 창 관리, 게임 엔진 코어 구현 분리
//	2. writer클래스 도입 - 문자열을 화면에 그리는 클래스
//	3. 자주 사용하는 변수/함수 static지정 및 매크로화 했음
//	4. 이름 정리
//	5. TextLayout의 DWRITE_TEXT_RANGE 사용법을 약간 이해
//		DWRITE_TEXT_RANGE는 1개 글자를 기본 단위로 한다.
//		예를 들면 시작 위치 startPosition이 10이면 처음 글자로부터 10글자 떨어진 글자부터 시작하라는 것
//		length는 해당 레이아웃을 시작 글자로부터 몇 글자 적용할 것인지를 결정한다.
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
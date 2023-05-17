#pragma once

//자주 사용하는 헤더
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <random>
#include <assert.h>
#include <d3d11.h>
#include <dxgi.h>
#include <wrl.h>		//windows Runtime Library : Comptr이 정의되어 있고 릴리즈를 별도로 수행하지 않아도 처리된다.

#include <io.h>			//디렉터리 로드 기능을 위한 헤더
//#include <tchar.h>	//유니코드 - 멀티바이트 호환 헤더
//#include <memory>		//스마트 포인터 정의 헤더

//필수 라이브러리
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

//사용자 작성 매크로
#define MYGAMECORE

//사용자 정의 헤더
#include "myvector.h"

//유니코드-멀티바이트 상호 변환 : 사용에 있어 이슈가 존재하니 사용에 유의
//#include <atlbase.h>
//static std::wstring atl_M2W(const std::string& _src)
//{
//	USES_CONVERSION;
//	return std::wstring(A2W(_src.c_str()));
//};
//
//static std::string atl_W2M(const std::wstring& _src)
//{
//	USES_CONVERSION;
//	return std::string(W2A(_src.c_str()));
//};

//WINAPI
static char* api_W2M(const WCHAR* data)
{
	char retData[4096] = { 0 };

	int iLength = WideCharToMultiByte(CP_ACP, 0,
		data, -1,
		0, 0,					//cbMuitiByte = 0이면 변환에 필요한 크기를 반환한다.
		NULL, NULL);	
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		data, -1,				// 소스(-1은 null포함 문자열을 생성한다는 의미)
		retData, iLength,		// 대상
		NULL, NULL);			// 코드 페이지에 표현되지 않는 문자 추가부
	return retData;
}
static bool api_W2M(const WCHAR* src, char* pDest)
{
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		src, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		src, -1,				//  소스
		pDest, iLength,			// 대상
		NULL, NULL);
	if (iRet == 0) return false;
	return true;
}
static WCHAR* api_M2W(char* data)
{
	WCHAR retData[4096] = { 0 };
	int iLength = MultiByteToWideChar(CP_ACP, 0,
		data, -1,
		0, 0);						//cchWideChar = 0이면 변환에 필요한 크기를 반환한다.
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		data, -1,					//  소스(-1은 null포함 문자열을 생성한다는 의미)
		retData, iLength);			// 대상
	return retData;
}
static bool api_M2W(char* pSrc, WCHAR* pDest)
{
	int iLength = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1,  //  소스
		pDest, iLength); // 대상		
	if (iRet == 0) return false;
	return true;
}

//싱글톤 템플릿 참조
//	-friend지정이 자식 클래스에서 friend지정이 있어야 제대로 된 사용이 가능하다.
template <class T>
class Singleton
{
public:
	static T& getInstance()
	{
		static T single;
		return single;
	}
};
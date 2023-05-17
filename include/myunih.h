#pragma once

//���� ����ϴ� ���
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
#include <wrl.h>		//windows Runtime Library : Comptr�� ���ǵǾ� �ְ� ����� ������ �������� �ʾƵ� ó���ȴ�.

#include <io.h>			//���͸� �ε� ����� ���� ���
//#include <tchar.h>	//�����ڵ� - ��Ƽ����Ʈ ȣȯ ���
//#include <memory>		//����Ʈ ������ ���� ���

//�ʼ� ���̺귯��
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

//����� �ۼ� ��ũ��
#define MYGAMECORE

//����� ���� ���
#include "myvector.h"

//�����ڵ�-��Ƽ����Ʈ ��ȣ ��ȯ : ��뿡 �־� �̽��� �����ϴ� ��뿡 ����
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
		0, 0,					//cbMuitiByte = 0�̸� ��ȯ�� �ʿ��� ũ�⸦ ��ȯ�Ѵ�.
		NULL, NULL);	
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		data, -1,				// �ҽ�(-1�� null���� ���ڿ��� �����Ѵٴ� �ǹ�)
		retData, iLength,		// ���
		NULL, NULL);			// �ڵ� �������� ǥ������ �ʴ� ���� �߰���
	return retData;
}
static bool api_W2M(const WCHAR* src, char* pDest)
{
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		src, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		src, -1,				//  �ҽ�
		pDest, iLength,			// ���
		NULL, NULL);
	if (iRet == 0) return false;
	return true;
}
static WCHAR* api_M2W(char* data)
{
	WCHAR retData[4096] = { 0 };
	int iLength = MultiByteToWideChar(CP_ACP, 0,
		data, -1,
		0, 0);						//cchWideChar = 0�̸� ��ȯ�� �ʿ��� ũ�⸦ ��ȯ�Ѵ�.
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		data, -1,					//  �ҽ�(-1�� null���� ���ڿ��� �����Ѵٴ� �ǹ�)
		retData, iLength);			// ���
	return retData;
}
static bool api_M2W(char* pSrc, WCHAR* pDest)
{
	int iLength = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1,  //  �ҽ�
		pDest, iLength); // ���		
	if (iRet == 0) return false;
	return true;
}

//�̱��� ���ø� ����
//	-friend������ �ڽ� Ŭ�������� friend������ �־�� ����� �� ����� �����ϴ�.
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
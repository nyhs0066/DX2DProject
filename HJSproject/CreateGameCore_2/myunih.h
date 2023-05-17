#pragma once

//main header
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

//D3D Library
//[링커] -> [입력] ->[추가 종속성]항목에서 추가 할 수도 있다.
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "winmm.lib")

//sub header
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <cmath>

#define PI 3.1415926
#define TAU PI*2
#define MARGIN_OF_ERROR 0.001f

#define RAD2DEG(x) ((x) * (180.0f/PI))
#define DEG2RAD(x) ((x) * (PI/180.0f))

template <class T>
class Singleton
{
public:
	static T& getInstance()
	{
		static T sgt;
		return sgt;
	}
};

using namespace std;
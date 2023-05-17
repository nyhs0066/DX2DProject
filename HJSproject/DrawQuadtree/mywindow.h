#pragma once

//main header
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

//D3D DLL동적 로딩도 연계
//[링커] -> [입력] ->[추가 종속성]항목에서 추가 할 수도 있다.
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

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
#include <time.h>

#define PI 3.1415926

using namespace std;
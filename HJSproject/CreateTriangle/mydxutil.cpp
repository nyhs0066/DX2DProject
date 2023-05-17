#include "mydxutil.h"

DxManager::~DxManager()
{
	for (auto it : vAdapterList) { it->Release(); }
	vAdapterList.clear();
}

BOOL DxManager::getAdapterList(vector<IDXGIAdapter*>& vAdapterList)
{
	HRESULT hr;

	IDXGIFactory* pDXGIFactory = nullptr;
	IDXGIAdapter* pTemp = nullptr;
	UINT cnt = 0;

	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);
	if (FAILED(hr)) { return FALSE; }
	
	while (SUCCEEDED(pDXGIFactory->EnumAdapters(cnt, &pTemp)))
	{
		vAdapterList.push_back(pTemp);
		cnt++;
	}

	pDXGIFactory->Release();

	if (vAdapterList.size()) { return TRUE; }
	return FALSE;
}
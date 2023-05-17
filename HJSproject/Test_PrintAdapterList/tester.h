#pragma once
#include "mygamecore.h"
#include <utility>
class TestCase : public MyGameCore
{
private:
	IDXGIFactory* m_pDXGIFactory;
	
	std::vector<std::pair<IDXGIAdapter*, DXGI_ADAPTER_DESC>> m_vAdapterList;
	std::vector<std::vector<std::pair<IDXGIOutput*, DXGI_OUTPUT_DESC>>> m_vOutputList;
	void findAdapterList();
	void findOutputList();

public:
	HRESULT createFactory();
	
	void makeList();

	bool init();
	bool frame();
	bool render();
	bool release();
};
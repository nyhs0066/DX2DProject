#include "tester.h"

HRESULT TestCase::createFactory()
{
	HRESULT hr = S_OK;

	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pDXGIFactory);

	return hr;
}

void TestCase::findAdapterList()
{
	IDXGIAdapter* pDXGIAdapter = nullptr;
	DXGI_ADAPTER_DESC dad;

	UINT idx = 0;

	while (m_pDXGIFactory->EnumAdapters(idx, &pDXGIAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		pDXGIAdapter->GetDesc(&dad);
		m_vAdapterList.push_back(std::make_pair(pDXGIAdapter, dad));

		idx++;
	}
}

void TestCase::findOutputList()
{
	IDXGIOutput* pDXGIOutput;
	DXGI_OUTPUT_DESC dod;

	for (int i = 0; i < m_vAdapterList.size(); i++)
	{
		int idx = 0;
		if (m_vAdapterList[i].first->EnumOutputs(idx, &pDXGIOutput) != DXGI_ERROR_NOT_FOUND)
		{
			m_vOutputList.push_back(std::vector<std::pair<IDXGIOutput*, DXGI_OUTPUT_DESC>>());
			while (m_vAdapterList[i].first->EnumOutputs(idx, &pDXGIOutput) != DXGI_ERROR_NOT_FOUND)
			{

				pDXGIOutput->GetDesc(&dod);
				m_vOutputList[i].push_back(std::make_pair(pDXGIOutput, dod));

				idx++;
			}
		}
	}
}

void TestCase::makeList()
{
	findAdapterList();
	findOutputList();
}

bool TestCase::init()
{
	createFactory();
	makeList();

	return true;
}

bool TestCase::frame()
{
	return true;
}

bool TestCase::render()
{
	return true;
}

bool TestCase::release()
{
	return true;
}

GAME_RUN(My First Library Application, 600, 600)
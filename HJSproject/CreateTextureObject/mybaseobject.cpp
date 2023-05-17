#include "mybaseobject.h"

MyVertexRenderer* MyVertexRenderer::pMVRenderer = nullptr;

MyVertexRenderer::MyVertexRenderer()
{
	pInputLayout = nullptr;
	pVertexShader = nullptr;
	pPixelShader = nullptr;

	pVScode = nullptr;
	pPScode = nullptr;

	init();
}

MyVertexRenderer::~MyVertexRenderer()
{
	release();
}

void MyVertexRenderer::create()
{
	if (!pMVRenderer) { pMVRenderer = new MyVertexRenderer; }
}

MyVertexRenderer* MyVertexRenderer::getMVRenderer()
{
	if (pMVRenderer) { return pMVRenderer; }
	return nullptr;
}

void MyVertexRenderer::setLayoutAndShader()
{
	ID3D11DeviceContext* pDC = MyDxDeviceManager::getInstance().getDContext();

	pDC->IASetInputLayout(pInputLayout);
	pDC->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDC->VSSetShader(pVertexShader, nullptr, 0);
	pDC->PSSetShader(pPixelShader, nullptr, 0);
}

HRESULT MyVertexRenderer::createVShader()
{
	HRESULT hr = S_OK;
	ID3DBlob* pErrCode = nullptr;

	hr = D3DCompileFromFile(L"VertexShader.txt",
		nullptr,
		nullptr,
		"VSmain",
		"vs_5_0",
		0, 0,
		&pVScode,
		&pErrCode);

	if (FAILED(hr))
	{
		OutputDebugStringA((char*)pErrCode->GetBufferPointer());
		pErrCode->Release();
		return hr;
	}

	hr = MyDxDeviceManager::getInstance().getDevice()->CreateVertexShader(pVScode->GetBufferPointer(),
		pVScode->GetBufferSize(),
		nullptr,
		&pVertexShader);

	return hr;
}

HRESULT MyVertexRenderer::createPShader()
{
	HRESULT hr = S_OK;
	ID3DBlob* pErrCode = nullptr;

	hr = D3DCompileFromFile(L"PixelShader.txt",
		nullptr,
		nullptr,
		"PSmain",
		"ps_5_0",
		0, 0,
		&pPScode,
		&pErrCode);

	if (FAILED(hr))
	{
		OutputDebugStringA((char*)pErrCode->GetBufferPointer());
		pErrCode->Release();
		return hr;
	}

	hr = MyDxDeviceManager::getInstance().getDevice()->CreatePixelShader(pPScode->GetBufferPointer(),
		pPScode->GetBufferSize(),
		nullptr,
		&pPixelShader);

	return hr;
}

HRESULT MyVertexRenderer::createILayout()
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,
		D3D11_INPUT_PER_VERTEX_DATA, NULL},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16,
		D3D11_INPUT_PER_VERTEX_DATA, NULL},
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32,
		D3D11_INPUT_PER_VERTEX_DATA, NULL}
	};

	hr = MyDxDeviceManager::getInstance().getDevice()->CreateInputLayout(ied,
		_ARRAYSIZE(ied),
		pVScode->GetBufferPointer(),
		pVScode->GetBufferSize(),
		&pInputLayout);

	return hr;
}

bool MyVertexRenderer::init()
{
	HRESULT hr;

	hr = createVShader();
	if (FAILED(hr)) { return false; }

	hr = createPShader();
	if (FAILED(hr)) { return false; }

	hr = createILayout();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyVertexRenderer::frame()
{
	return false;
}

bool MyVertexRenderer::render()
{
	return false;
}

bool MyVertexRenderer::release()
{
	if (pInputLayout) { pInputLayout->Release(); }
	if (pVertexShader) { pVertexShader->Release(); }
	if (pPixelShader) { pPixelShader->Release(); }
	if (pVScode) { pVScode->Release(); }
	if (pPScode) { pPScode->Release(); }

	return true;
}

MyBaseObject::MyBaseObject()
{
	pVertexBuf = nullptr;
}

MyBaseObject::~MyBaseObject()
{
	release();
}

void MyBaseObject::createRect(RECT rect, int maxX, int maxY)
{
	float LTX = (((float)rect.left / maxX) * 2.0f - 1.0f);
	float LTY = -(((float)rect.top / maxX) * 2.0f - 1.0f);
	float RBX = (((float)rect.right / maxX) * 2.0f - 1.0f);
	float RBY = -(((float)rect.bottom / maxX) * 2.0f - 1.0f);

	vertices.push_back({ {LTX, LTY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} });
	vertices.push_back({ {RBX, LTY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} });
	vertices.push_back({ {LTX, RBY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} });
	vertices.push_back({ {LTX, RBY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} });
	vertices.push_back({ {RBX, LTY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} });
	vertices.push_back({ {RBX, RBY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} });

	/*vertices.push_back({ {LTX, LTY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} });
	vertices.push_back({ {RBX, LTY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} });
	vertices.push_back({ {LTX, RBY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} });
	vertices.push_back({ {LTX, RBY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} });
	vertices.push_back({ {RBX, LTY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} });
	vertices.push_back({ {RBX, RBY, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} });*/
}

HRESULT MyBaseObject::createVBuffer()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth =  sizeof(MyVertex4F) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &vertices[0];

	hr = MyDxDeviceManager::getInstance().getDevice()->CreateBuffer(&bd, &sd, &pVertexBuf);

	return hr;
}

bool MyBaseObject::init()
{
	HRESULT hr = S_OK;
	
	hr = createVBuffer();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyBaseObject::frame()
{
	return true;
}

bool MyBaseObject::render()
{
	MyDxDeviceManager::getInstance().getDContext()->UpdateSubresource(
		pVertexBuf, 0, NULL,
		&vertices.at(0), 0, 0);

	UINT vbStride = sizeof(MyVertex4F);
	UINT offset = 0;

	MyDxDeviceManager::getInstance().getDContext()->IASetVertexBuffers(0, 1, &pVertexBuf, &vbStride, &offset);
	MyVertexRenderer::getMVRenderer()->setLayoutAndShader();

	MyDxDeviceManager::getInstance().getDContext()->Draw(vertices.size(), 0);

	return true;
}

bool MyBaseObject::release()
{
	if (pVertexBuf) { pVertexBuf->Release(); }

	return true;
}
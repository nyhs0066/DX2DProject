#include "mytriangle.h"

MyTriangle::MyTriangle()
{
	pVertexBuf = nullptr;
	pInputLayout = nullptr;
	pVertexShader = nullptr;
	pPixelShader = nullptr;

	pVScode = nullptr;
	pPScode = nullptr;

	vertexNum = 0;
}

MyTriangle::~MyTriangle()
{
	release();
}

HRESULT MyTriangle::createVBuffer()
{
	HRESULT hr = S_OK;

	SimpleVertex triangle[] =
	{
		{0.0f, 0.5f, 1.0f},
		{0.5f, 0.0f, 1.0f},
		{0.5f, -0.5f, 1.0f}
	};

	vertexNum = sizeof(triangle) / sizeof(triangle[0]);
	UINT arrSize = sizeof(SimpleVertex) * vertexNum;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = arrSize;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = triangle;

	hr = pD3Device->CreateBuffer(&bd, &sd, &pVertexBuf);

	return hr;
}

HRESULT MyTriangle::createVShader()
{
	HRESULT hr = S_OK;
	ID3DBlob* pErrCode = nullptr;

	hr = D3DCompileFromFile(L"VertexShader.txt",
							nullptr,
							nullptr,
							"vtshmain",
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

	hr = pD3Device->CreateVertexShader(	pVScode->GetBufferPointer(),
										pVScode->GetBufferSize(),
										nullptr,
										&pVertexShader);

	return hr;
}

HRESULT MyTriangle::createPShader()
{
	HRESULT hr = S_OK;
	ID3DBlob* pErrCode = nullptr;

	hr = D3DCompileFromFile(L"PixelShader.txt",
		nullptr,
		nullptr,
		"pxshmain",
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

	hr = pD3Device->CreatePixelShader(pPScode->GetBufferPointer(),
		pPScode->GetBufferSize(),
		nullptr,
		&pPixelShader);

	return hr;
}

HRESULT MyTriangle::createILayout()
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, 
		D3D11_INPUT_PER_VERTEX_DATA, NULL},
		//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		//D3D11_INPUT_PER_VERTEX_DATA, NULL}
	};

	UINT iedSize = sizeof(ied) / sizeof(ied[0]);

	hr = pD3Device->CreateInputLayout(ied,
		iedSize,
		pVScode->GetBufferPointer(),
		pVScode->GetBufferSize(),
		&pInputLayout);

	return hr;
}

bool MyTriangle::init()
{
	HRESULT hr = S_OK;

	myDxDevice::init();
	
	hr = createVBuffer();
	if (FAILED(hr)) { return false; }

	hr = createVShader();
	if (FAILED(hr)) { return false; }

	hr = createPShader();
	if (FAILED(hr)) { return false; }

	hr = createILayout();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyTriangle::frame()
{
	return true;
}

bool MyTriangle::render()
{
	preRender();

	UINT vbStride = sizeof(SimpleVertex);
	UINT offset = 0;

	pD3DeviceContext->IASetVertexBuffers(0, 1, &pVertexBuf, &vbStride, &offset);
	pD3DeviceContext->IASetInputLayout(pInputLayout);
	pD3DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pD3DeviceContext->VSSetShader(pVertexShader, nullptr, 0);
	pD3DeviceContext->PSSetShader(pPixelShader, nullptr, 0);

	pD3DeviceContext->Draw(vertexNum, 0);

	postRender();

	return true;
}

bool MyTriangle::release()
{
	if (pVertexBuf) { pVertexBuf->Release(); }
	if (pInputLayout) { pInputLayout->Release(); }
	if (pVertexShader) { pVertexShader->Release(); }
	if (pPixelShader) { pPixelShader->Release(); }
	if (pVScode) { pVScode->Release(); }
	if (pPScode) { pPScode->Release(); }

	return true;
}

BOOL MyTriangle::run()
{
	if (!init()) { release(); return FALSE; };

	MSG msg = { 0 };

	while (true)
	{
		if (msg.message == WM_QUIT) { break; }

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!frame() || !render()) { break; }
		}
	}

	release();
	return TRUE;
}

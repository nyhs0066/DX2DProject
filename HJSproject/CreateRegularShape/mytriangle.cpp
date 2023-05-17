#include "mytriangle.h"

MyTriangle::MyTriangle()
{
	pVertexBuf = nullptr;
	pInputLayout = nullptr;
	pVertexShader = nullptr;
	pPixelShader = nullptr;

	pVScode = nullptr;
	pPScode = nullptr;
}

MyTriangle::~MyTriangle()
{
	release();
}

void MyTriangle::createRegularShapeVertices(int numOfAngle)
{
	float TAU = 3.141592 * 2;

	for (int i = 0; i < numOfAngle; i++)
	{
		vertices.push_back(
			{ {cosf((i % numOfAngle) * TAU / numOfAngle), sinf((i % numOfAngle) * TAU / numOfAngle), 1.0f, 1.0f},
				{0.3f, 0.0f, 0.6f, 1.0f}
			}
		);
		vertices.push_back({ {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} });
		vertices.push_back(
			{
				{cosf(((i + 1) % numOfAngle) * TAU / numOfAngle), sinf(((i + 1) % numOfAngle) * TAU / numOfAngle), 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f}
			});
	}
}

HRESULT MyTriangle::createVBuffer()
{
	createRegularShapeVertices(5);

	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth =  sizeof(MyVertex4F) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &vertices[0];

	hr = getDevice()->CreateBuffer(&bd, &sd, &pVertexBuf);

	return hr;
}

HRESULT MyTriangle::createVShader()
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

	hr = getDevice()->CreateVertexShader(	pVScode->GetBufferPointer(),
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

	hr = getDevice()->CreatePixelShader(pPScode->GetBufferPointer(),
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
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, 
		D3D11_INPUT_PER_VERTEX_DATA, NULL},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16,
		D3D11_INPUT_PER_VERTEX_DATA, NULL}
	};

	hr = getDevice()->CreateInputLayout(ied,
		_ARRAYSIZE(ied),
		pVScode->GetBufferPointer(),
		pVScode->GetBufferSize(),
		&pInputLayout);

	return hr;
}

bool MyTriangle::init()
{
	HRESULT hr = S_OK;

	MyDxWindow::init();
	
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

	UINT vbStride = sizeof(MyVertex4F);
	UINT offset = 0;

	getDContext()->IASetVertexBuffers(0, 1, &pVertexBuf, &vbStride, &offset);
	getDContext()->IASetInputLayout(pInputLayout);
	getDContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	getDContext()->VSSetShader(pVertexShader, nullptr, 0);
	getDContext()->PSSetShader(pPixelShader, nullptr, 0);

	getDContext()->Draw(vertices.size(), 0);

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

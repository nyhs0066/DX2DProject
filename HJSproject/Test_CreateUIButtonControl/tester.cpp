#include "tester.h"

bool TestCase::init()
{
	temp = nullptr;
	cnt = 0;
	ZeroMemory(c, sizeof(int) * 100);

	createRBState();
	bStateArr.push_back(temp);
	createGBState();
	bStateArr.push_back(temp);
	createBBState();
	bStateArr.push_back(temp);
	createYBState();
	bStateArr.push_back(temp);
	createCBState();
	bStateArr.push_back(temp);
	createMBState();
	bStateArr.push_back(temp);

	createAlphaBlendState();

	for (int i = 0; i < 100; i++) { c[i] = MYRND.getI(0, bStateArr.size() - 1); }

	LOAD_TEXTURE(L"../../data/shapes/numeric.png");
	LOAD_TEXTURE(L"../../data/sprite_set/test_sprites/sparkle.png");
	LOAD_ST_SPRITE(L"../../data/sprite_set/test_sprites/sprite_rect_list.txt");

	LOAD_MT_SPRITE(L"../../data/ui/test_UI_list.txt");

	pTestUIButton = new MyUIButton;

	pTestUIButton->create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/ui/UI_plus0.png");
	pTestUIButton->setMTsprite(L"test_plus");
	MyVector2F UIPos = { MyWindow::cWidth / 2.0f, MyWindow::cHeight / 2.0f };
	MyRect UIPRect = pTestUIButton->getTexRect();
	UIPRect.pos.x = UIPos.x - UIPRect.fWH.x * 0.5f;
	UIPRect.pos.y = UIPos.y - UIPRect.fWH.y * 0.5f;
	pTestUIButton->setPosRect(UIPRect);

	FLOAT bW = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Width;
	FLOAT bH = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Height;

	space.maxDepth = 5;
	space.create({ 0.0f, 0.0f }, { bW, bH });

	BoundaryRect = space.getBoundary();

	mainCam.setCamRect({ MyWindow::cWidth / 2.0f, bH - MyWindow::cHeight / 2.0f,
		(FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

	//effect preset part
	preset1.createEffectPreset(L"../../data/shader/mydefaultshader.txt",
		L"../../data/sprite_set/test_sprites/sparkle.png", L"sparkle");
	preset1.m_pDrawing->setBoundRect(BoundaryRect);

	////effect create
	//for (int i = 0; i < 100; i++)
	//{
	//	FLOAT fRand = MYRND.getF(0.0f, 250.0f);

	//	MyEffect* newE = new MyEffect;
	//	newE->m_pEPreset = &preset1;
	//	newE->init();
	//	newE->setTimeProperty(30.0f, MYRND.getF(2.0f, 5.0f));
	//	newE->m_SPRect.pos = { MYRND.getF(0.0f, bW), MYRND.getF(0.0f, bH) };
	//	newE->m_SPRect.fWH = { 50.0f + fRand, 50.0f + fRand };

	//	effectList.push_back(newE);
	//}

	//Dummy Set
	MyRect pRect(MyWindow::cWidth / 2.0f, MyWindow::cHeight / 2.0f,
		99.0f, 99.0f);
	MyRect tRect(0.0f, 0.0f, 100.0f, 100.0f);
	dummy.create(L"../../data/shader/myalphatextureshader.txt", L"../../data/shapes/Square.png",
		pRect, tRect, BoundaryRect);
	dummy.init();

	//BG Set
	BGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/texture/010.jpg",
		pRect, tRect, BoundaryRect);
	BGObj.setBGdefault();

	//Cam set
	mainCam.setBoundaryRect(BoundaryRect);
	mainCam.setFollowTarget(&dummy);

	return true;
}

bool TestCase::frame()
{
	dummy.frame();
	mainCam.frame();
	BGObj.frame();
	BGObj.postFrame(mainCam.getCamRect());

	if (pTestUIButton->frame())
	{
		FLOAT fRand = MYRND.getF(0.0f, 250.0f);

		MyEffect* newE = new MyEffect;
		newE->m_pEPreset = &preset1;
		newE->init();
		newE->setTimeProperty(10.0f, MYRND.getF(2.0f, 5.0f));
		newE->m_SPRect.pos = { MYRND.getF(0.0f, BoundaryRect.fWH.x), MYRND.getF(0.0f, BoundaryRect.fWH.y) };
		newE->m_SPRect.fWH = { 50.0f + fRand, 50.0f + fRand };

		effectList.push_back(newE);
	}

	for (it = effectList.begin(); it != effectList.end();)
	{
		if (!(*it)->update())
		{
			cit = it;
			it++;
			delete (*cit);
			effectList.erase(cit);
		}
		else { it++; }
	}

	COLLISION_PLANE cp = MYCP_NONE;
	bool cFlag = false;

	cFlag |= dummy.boundaryCheck();
	if (!cFlag) { dummy.setAerial(); }

	dummy.postFrame(mainCam.getCamRect());

	return true;
}

bool TestCase::render()
{
	BGObj.render();
	dummy.render();

	cnt = 0;
	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		I_DCONTEXT->OMSetBlendState(bStateArr[c[cnt++]], nullptr, -1);
		it->preRender(mainCam.getCamRect());
		it->m_pEPreset->m_pDrawing->render();
	}
	I_DCONTEXT->OMSetBlendState(temp, nullptr, -1);

	pTestUIButton->render();
	
	return true;
}

bool TestCase::release()
{
	dummy.release();
	BGObj.release();

	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		delete it;
		it = nullptr;
	}
	effectList.clear();

	for (vector<ID3D11BlendState*>::iterator::value_type it : bStateArr)
	{
		it->Release();
		it = nullptr;
	}
	bStateArr.clear();

	temp->Release(); temp = nullptr;

	if (pTestUIButton) 
	{
		pTestUIButton->release();
		delete pTestUIButton;
		pTestUIButton = nullptr;
	}

	return true;
}

HRESULT TestCase::createBlendState()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC bd;

	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	
	//렌더 타겟을 하나만 사용하고 있으므로 0번 렌더 타겟에 대한 속성만 지정한다.
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = I_DEVICE->CreateBlendState(&bd, &temp);

	return hr;
}

HRESULT TestCase::createAlphaBlendState()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC bd;

	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	//렌더 타겟을 하나만 사용하고 있으므로 0번 렌더 타겟에 대한 속성만 지정한다.
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = I_DEVICE->CreateBlendState(&bd, &temp);

	return hr;
}

HRESULT TestCase::createRBState()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC bd;

	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	//렌더 타겟을 하나만 사용하고 있으므로 0번 렌더 타겟에 대한 속성만 지정한다.
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED;

	hr = I_DEVICE->CreateBlendState(&bd, &temp);

	return hr;
}

HRESULT TestCase::createGBState()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC bd;

	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	//렌더 타겟을 하나만 사용하고 있으므로 0번 렌더 타겟에 대한 속성만 지정한다.
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_GREEN;

	hr = I_DEVICE->CreateBlendState(&bd, &temp);

	return hr;
}

HRESULT TestCase::createBBState()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC bd;

	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	//렌더 타겟을 하나만 사용하고 있으므로 0번 렌더 타겟에 대한 속성만 지정한다.
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_BLUE;

	hr = I_DEVICE->CreateBlendState(&bd, &temp);

	return hr;
}

HRESULT TestCase::createYBState()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC bd;

	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	//렌더 타겟을 하나만 사용하고 있으므로 0번 렌더 타겟에 대한 속성만 지정한다.
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_GREEN;

	hr = I_DEVICE->CreateBlendState(&bd, &temp);

	return hr;
}

HRESULT TestCase::createCBState()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC bd;

	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	//렌더 타겟을 하나만 사용하고 있으므로 0번 렌더 타겟에 대한 속성만 지정한다.
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_GREEN | D3D11_COLOR_WRITE_ENABLE_BLUE;

	hr = I_DEVICE->CreateBlendState(&bd, &temp);

	return hr;
}

HRESULT TestCase::createMBState()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC bd;

	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	//렌더 타겟을 하나만 사용하고 있으므로 0번 렌더 타겟에 대한 속성만 지정한다.
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_BLUE;

	hr = I_DEVICE->CreateBlendState(&bd, &temp);

	return hr;
}

GAME_RUN(Test_CreateUIButton, 800, 800)
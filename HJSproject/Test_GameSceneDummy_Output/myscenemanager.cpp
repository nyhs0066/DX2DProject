#include "myscenemanager.h"

MyScene::MyScene()
{
	bSceneFlag = 0;
}

MyScene::~MyScene()
{
	release();
}

bool MyScene::init()
{
	return true;
}

bool MyScene::frame()
{
	return true;
}

bool MyScene::render()
{
	return true;
}

bool MyScene::release()
{
	return true;
}

MySceneManager::MySceneManager()
{

}

MySceneManager::~MySceneManager()
{
	release();
}

bool MySceneManager::addScene(wstring wszSceneName, std::unique_ptr<MyScene>& pScene)
{
	map<wstring, std::unique_ptr<MyScene>>::iterator it = m_sceneMap.find(wszSceneName);

	if (it == m_sceneMap.end() && pScene.get())
	{
		m_sceneMap.emplace(wszSceneName, std::move(pScene));
		return true;
	}

	return false;
}

MyScene* MySceneManager::getScene(wstring wszSceneName)
{
	map<wstring, std::unique_ptr<MyScene>>::iterator it = m_sceneMap.find(wszSceneName);

	if (it != m_sceneMap.end())
	{
		return it->second.get();
	}

	return nullptr;
}

bool MySceneManager::init()
{
	return true;
}

bool MySceneManager::frame()
{
	return true;
}

bool MySceneManager::render()
{
	return true;
}

bool MySceneManager::release()
{
	//Iterator Type이 레퍼런스임에 유의
	for (map<wstring, std::unique_ptr<MyScene>>::iterator::reference it : m_sceneMap)
	{
		it.second->release();
	}

	m_sceneMap.clear();

	return true;
}

#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float elapsedTime)
{
	if (m_CanLoadNewScene)
	{
		m_Wait += elapsedTime;
		if (m_Wait >= m_TotalWaitTime)
		{
			m_CanLoadNewScene = false;
			m_Wait = 0.0f;
			LoadScene(m_LevelToLoad);
		}
	}

	m_CurrentScene.lock()->Update(elapsedTime);
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::AddScene(const std::shared_ptr<Scene>& scene)
{
	m_Scenes.emplace_back(scene);
}

void dae::SceneManager::LoadScene(const std::string& name)
{
	if (m_CurrentScene.lock() != nullptr)
		DeleteScene(m_CurrentScene.lock()->GetName());

	for (const auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_CurrentScene = scene;
			scene->LoadSceneElements();
			break;
		}
	}
}

void dae::SceneManager::AddSharedObject(const std::shared_ptr<dae::GameObject>& sharedObject)
{
	m_SharedSceneObjects.emplace_back(sharedObject);
}

void dae::SceneManager::DeleteScene(const std::string& name)
{

	for (const auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			scene->CleanUpScene();
			break;
		}
	}
}

void dae::SceneManager::AddToCurrentScene(const std::shared_ptr<dae::GameObject>& gameObject)
{
	m_CurrentScene.lock()->Add(gameObject);
}

void dae::SceneManager::SetLevelToLoad(const std::string& levelToLoad)
{
	m_LevelToLoad = levelToLoad;
	m_CanLoadNewScene = true;
	m_CurrentScene.lock()->SetIsLoading(true);
}

const std::vector<std::shared_ptr<dae::GameObject>>& dae::SceneManager::GetSharedObjects()
{
	return m_SharedSceneObjects;
}

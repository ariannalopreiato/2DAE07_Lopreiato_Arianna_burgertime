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
	m_CurrentScene.lock()->Render();
}

void dae::SceneManager::RemoveScene(const std::string& name)
{
	for (size_t i = 0; i < m_Scenes.size(); ++i)
		if (m_Scenes[i]->GetName() == name)
			m_Scenes[i] = m_Scenes.back();
	m_Scenes.pop_back();
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

const std::string& dae::SceneManager::GetCurrentSceneName()
{
	return m_CurrentScene.lock()->GetName();
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetCurrentScene()
{
	return m_CurrentScene.lock();
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetSceneByName(const std::string& name)
{
	for (const auto& scene : m_Scenes)
		if (scene->GetName() == name)
			return scene;

	return nullptr;
}

void dae::SceneManager::AddSharedObject(const std::shared_ptr<dae::GameObject>& sharedObject)
{
	m_SharedSceneObjects.emplace_back(sharedObject);
}

void dae::SceneManager::CleanSharedSceneObjects()
{
	m_SharedSceneObjects.clear();
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

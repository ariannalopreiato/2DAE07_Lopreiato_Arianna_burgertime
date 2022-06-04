#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float elapsedTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(elapsedTime);
	}
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

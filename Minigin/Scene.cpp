#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <ranges>
#include <algorithm>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
{}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.emplace_back(object);
}

void dae::Scene::LoadSceneElements()
{
	for (const std::shared_ptr<dae::GameObject>& object : SceneManager::GetInstance().GetSharedObjects())
	{
		Add(object);
	}
}

void dae::Scene::CleanUpScene()
{
	auto sharedObj = SceneManager::GetInstance().GetSharedObjects();
	for (const auto& object : m_Objects)
	{
		if (std::find(sharedObj.begin(), sharedObj.end(), object) == sharedObj.end())
			object->m_MarkForDestruction = true;
	}

	m_Objects.clear();
}

const std::string& dae::Scene::GetName()
{
	return m_Name;
}

void Scene::Update(float elapsedTime)
{
	if (!m_IsLoading)
	{
		for (const std::shared_ptr<GameObject>& object : m_Objects)
		{
			if(object->m_MarkForDestruction == false)
				object->Update(elapsedTime);
		}
	}
	else
	{
		for (const std::shared_ptr<GameObject>& object : SceneManager::GetInstance().GetSharedObjects())
		{
			object->Update(elapsedTime);
		}
	}

	//new feature in C++20 -> like erase(std::remove)
	std::ranges::destroy(std::views::filter(m_Objects, [](const std::shared_ptr<GameObject>& go)
		{
			return go->m_MarkForDestruction;
		}));
}

void Scene::Render() const
{
	for (const std::shared_ptr<GameObject>& object : m_Objects)
	{
		object->Render();
	}
}

void dae::Scene::SetIsLoading(bool isLoading)
{
	m_IsLoading = isLoading;
}

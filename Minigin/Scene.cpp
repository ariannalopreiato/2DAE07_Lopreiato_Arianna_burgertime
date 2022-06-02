#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <ranges>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
{
	//SceneManager::CreateScene(name);
}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.emplace_back(object);
}

void dae::Scene::CleanUpScene()
{
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->m_MarkForDestruction = true;
	}
}

const std::string& dae::Scene::GetName()
{
	return m_Name;
}

void Scene::Update(float elapsedTime)
{
	for(std::shared_ptr<GameObject>& object : m_Objects)
	{
		object->Update(elapsedTime);
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
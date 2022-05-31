#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <ranges>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.emplace_back(object);
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
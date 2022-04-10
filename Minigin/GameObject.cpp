#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include <algorithm>

//------------------------------------- Rule of five ------------------------------------------------
dae::GameObject::~GameObject()
{
	for (size_t i = 0; i < m_Components.size(); ++i)
	{
		m_Components.at(i) = nullptr;
	}
}

dae::GameObject::GameObject(const GameObject& other) //copy
{
	m_Children = other.m_Children;
	m_Components = other.m_Components;
	m_Parent = other.m_Parent;
}

dae::GameObject::GameObject(GameObject&& other) //move
{
	m_Children = std::move(other.m_Children);
	m_Components = std::move(other.m_Components);
	m_Parent = std::move(other.m_Parent);
}

dae::GameObject& dae::GameObject::operator=(const GameObject& other) //copy
{
	m_Children = other.m_Children;
	m_Components = other.m_Components;
	m_Parent = other.m_Parent;
	return *this;
}

dae::GameObject& dae::GameObject::operator=(GameObject&& other) //move
{
	m_Children = std::move(other.m_Children);
	m_Components = std::move(other.m_Components);
	m_Parent = std::move(other.m_Parent);;
	return *this;
}
//--------------------------------------------------------------------------------------------------------

void dae::GameObject::Update(float elapsedTime)
{
	for (size_t i = 0; i < m_Components.size(); ++i)
	{
		m_Components.at(i)->Update(elapsedTime);
	}

	for (size_t j = 0; j < m_Children.size(); ++j)
	{
		m_Children.at(j)->Update(elapsedTime);
	}
}

void dae::GameObject::Render() const
{
	for (size_t i = 0; i < m_Components.size(); ++i)
	{
		m_Components.at(i)->Render();
	}

	for (size_t i = 0; i < m_Children.size(); ++i)
	{
		m_Children.at(i)->Render();
	}
}

//------------------------------------- Components handling ------------------------------------------------
void dae::GameObject::AddComponent(std::shared_ptr<Component> component)
{
	m_Components.push_back(component);
}

int dae::GameObject::GetComponentAmount()
{
	return int(m_Components.size());
}

void dae::GameObject::RemoveComponent(const std::shared_ptr<Component>& component)
{
	//std::remove places elements to be removed at the end
	//erase removes all the elements from the position of the first element equal to container untill the end of it
	 m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
}

void dae::GameObject::RemoveComponentAt(int index)
{
	m_Components.erase(m_Components.begin() + index - 1);
}
//--------------------------------------------------------------------------------------------------------


//------------------------------------- Scenegraph handling ----------------------------------------------
void dae::GameObject::SetParent(const std::shared_ptr<GameObject>& parent)
{
	if (parent)
	{
		if (parent != this->GetParent())
		{
			if (!this->GetParent())
			{
				this->m_Parent = nullptr;
			}
			this->m_Parent = parent;
		}
	}
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_Parent;
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index) const
{
	return m_Children.at(index);
}

void dae::GameObject::AddChild(const std::shared_ptr<GameObject>& child, const std::shared_ptr<GameObject>& parent)
{
	auto oldParent = child->GetParent(); //get the current parent
	if (oldParent != nullptr)
	{
		//if it already has a parent it will be deleted and changed
		auto oldListOfChildren = oldParent->GetChildren();
		for (size_t i = 0; i < oldListOfChildren.size(); ++i)
		{
			//child is removed from the old parent
			if (oldListOfChildren.at(i) == child)
			{
				oldParent->RemoveChildAt(int(i));
				break;
			}
		}
	}
	child->SetParent(parent);
	m_Children.push_back(child); //added to the list
}

const std::vector<std::shared_ptr<dae::GameObject>>& dae::GameObject::GetChildren() const
{
	return m_Children;
}

void dae::GameObject::RemoveChildAt(int index)
{
	m_Children.at(index)->SetParent(nullptr);
	if (index != int(m_Children.size() - 1))
	{
		//move all children
		for (size_t i = index; i < m_Children.size() - 1; ++i)
			m_Children.at(i) = m_Children.at(i + 1);
	}
	m_Children.pop_back(); //delete the empty last spot
	//remove itself from the parent of the child
}

void dae::GameObject::RemoveChild(const std::shared_ptr<GameObject>& child)
{
	m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
}
//--------------------------------------------------------------------------------------------------------

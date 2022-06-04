#pragma once
#include "Component.h"

namespace dae
{
	class Transform;
	class GameObject final
	{
	public:
		void Update(float elapsedTime);
		void Render() const;

		GameObject();
		GameObject(const GameObject& other) noexcept;
		GameObject(GameObject&& other) noexcept;
		GameObject& operator=(const GameObject& other) noexcept;
		GameObject& operator=(GameObject&& other) noexcept;
		~GameObject();

		void AddComponent(std::shared_ptr<Component> component);
		
		template <typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent() const
		{
			for (size_t i = 0; i < m_Components.size(); ++i)
			{
				if (typeid(*m_Components.at(i)) == typeid(ComponentType)) //if it's the same type
					return std::static_pointer_cast<ComponentType>(m_Components.at(i));
			}
			return nullptr;
		}

		template <typename ComponentType>
		std::shared_ptr<ComponentType> GetComponentInheritance() const
		{
			for (size_t i = 0; i < m_Components.size(); ++i)
			{
				//if the current component can convert to the given component type
				if (std::shared_ptr<ComponentType> currentComponent{ std::dynamic_pointer_cast<ComponentType>(m_Components[i]) };
					currentComponent != nullptr)
				{
					return currentComponent;
				}
			}
			return nullptr;
		}

		int GetComponentAmount();
		template <typename ComponentType>
		void RemoveComponentByType()
		{
			if(typeid(ComponentType) != typeid(Transform)) //the transform component CANNOT be removed
				m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(), [](const std::shared_ptr<Component>& component) {return typeid(*(component.get())) == typeid(ComponentType); }), m_Components.end());
		}

		std::shared_ptr<GameObject> GetParent() const;
		std::shared_ptr<GameObject> GetChildAt(int index) const;
		const std::vector<std::shared_ptr<GameObject>>& GetChildren() const;
		void AddChild(const std::shared_ptr<GameObject>& child);
		void RemoveChildAt(int index);
		void RemoveChild(const std::shared_ptr<GameObject>& child);

		void SetPosition(float x, float y);
		bool m_MarkForDestruction{ false };

	private:
		std::vector<std::shared_ptr<GameObject>> m_Children{};
		std::shared_ptr<GameObject> m_Parent{};
		std::vector<std::shared_ptr<Component>> m_Components{};
		std::shared_ptr<Transform> m_Transform{}; //every game object NEEDS to have a transform component
		void SetParent(const std::shared_ptr<GameObject>& parent);
	};
}

#pragma once
#include "Transform.h"
#include "Component.h"

namespace dae
{
	class GameObject final
	{
	public:
		void Update(float elapsedTime);
		void Render() const;

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other);
		GameObject(GameObject&& other);
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other);

		void AddComponent(std::shared_ptr<Component> component);
		
		//todo fix warning (textobject & texturecomponent)
		template <typename Type>
		const std::shared_ptr<Type>& GetComponent() const
		{
			for (size_t i = 0; i < m_Components.size(); ++i)
			{
				if (typeid(*m_Components.at(i)) == typeid(Type)) //if it's the same type
					return std::static_pointer_cast<Type>(m_Components.at(i));
			}
			return nullptr;
		}

		int GetComponentAmount();
		void RemoveComponent(const std::shared_ptr<Component>& component);
		void RemoveComponentAt(int index);
		template <typename Type>
		void RemoveComponentByType(const std::shared_ptr<Type>& component)
		{
			m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
		}

		std::shared_ptr<GameObject> GetParent() const;
		std::shared_ptr<GameObject> GetChildAt(int index) const;
		const std::vector<std::shared_ptr<GameObject>>& GetChildren() const;
		void AddChild(const std::shared_ptr<GameObject>& child, const std::shared_ptr<GameObject>& parent);
		void RemoveChildAt(int index);
		void RemoveChild(const std::shared_ptr<GameObject>& child);

	private:
		std::vector<std::shared_ptr<GameObject>> m_Children;
		std::shared_ptr<GameObject> m_Parent{};
		std::vector<std::shared_ptr<Component>> m_Components;

		void SetParent(const std::shared_ptr<GameObject>& parent);
	};
}

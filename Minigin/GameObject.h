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

		void AddComponent(std::shared_ptr<Component> component);
		
		template <typename Type>
		std::shared_ptr<Type> GetComponent() const
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
			if(typeid(component) != typeid(Transform)) //the transform component CANNOT be removed
				m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
		}

		std::shared_ptr<GameObject> GetParent() const;
		std::shared_ptr<GameObject> GetChildAt(int index) const;
		const std::vector<std::shared_ptr<GameObject>>& GetChildren() const;
		void AddChild(const std::shared_ptr<GameObject>& child, const std::shared_ptr<GameObject>& parent);
		void RemoveChildAt(int index);
		void RemoveChild(const std::shared_ptr<GameObject>& child);

		void SetPosition(const float& x, const float& y);

	private:
		std::vector<std::shared_ptr<GameObject>> m_Children{};
		std::shared_ptr<GameObject> m_Parent{};
		std::vector<std::shared_ptr<Component>> m_Components{};
		std::shared_ptr<Transform> m_Transform{}; //every game object NEEDS to have a transform component
		void SetParent(const std::shared_ptr<GameObject>& parent);
	};
}

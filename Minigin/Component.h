#pragma once

namespace dae
{
	class GameObject;
	class Component
	{
	public:
		//component has access to its game objects
		Component(const std::shared_ptr<GameObject>& gameObject);
		virtual ~Component() = default;

		//empty function definitions
		virtual void Update(float) {}
		virtual void Render() const {}

		std::shared_ptr<GameObject> GetGameObject() const { return m_GameObject.lock(); };

		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<GameObject> &gameObject) = 0;

		Component(const Component& other) = default;
		Component(Component&& other) = default;
		Component& operator=(const Component& other) = default;
		Component& operator=(Component&& other) = default;

		void SetOwner(const std::shared_ptr<GameObject>& gameObject);

	protected:
		//weak pointer to avoid circular dependency between game object and components
		std::weak_ptr<GameObject> m_GameObject;
	};
}

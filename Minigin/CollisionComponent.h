#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class CollisionComponent : public dae::Component
	{
	public:
		CollisionComponent(std::shared_ptr<dae::GameObject> gameObject);
		void Update(float elapsedSec);
		void Render() const;
		bool IsOverlapping(const SDL_Rect& other);
		const SDL_Rect& GetCollisionBox() const;
		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
		bool m_IsBoxVisible{ false };

	private:
		std::weak_ptr<dae::Transform> m_Transform;
		SDL_Rect m_Shape{};
	};
}
#pragma once
#include "Component.h"
#include "structs.h"
#include "Transform.h"

namespace dae
{
	class CollisionComponent : public dae::Component
	{
	public:
		CollisionComponent(std::shared_ptr<dae::GameObject> gameObject);
		void Update(float elapsedSec);
		bool IsOverlapping(const Rectf& other) const;
		const Rectf& GetCollisionBox() const;
		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

	private:
		std::weak_ptr<dae::Transform> m_Transform;
		Rectf m_Shape{};
	};
}
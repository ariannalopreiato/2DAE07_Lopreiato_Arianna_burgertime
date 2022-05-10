#pragma once
#include "Component.h"
#include "structs.h"

namespace dae
{
	class CollisionComponent : public dae::Component
	{
	public:
		CollisionComponent(std::shared_ptr<dae::GameObject> gameObject);
		bool IsOverlapping(const Rectf& other) const;
		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
		Rectf m_Shape{0.0f, 0.0f, 0.0f, 0.0f};
	};
}
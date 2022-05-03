#pragma once
#include "Component.h"
#include "structs.h"

class CollisionComponent : public dae::Component
{
public:
	CollisionComponent(std::shared_ptr<dae::GameObject> gameObject, Rectf shape);
	void Update(float elapsedSec);
	bool IsOverlapping(const Rectf& other) const;
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
	Rectf m_Shape{};
};


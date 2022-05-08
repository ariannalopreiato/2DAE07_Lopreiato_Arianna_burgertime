#pragma once
#include "Component.h"
#include "Vector2f.h"

class PlayerMovementComponent : public dae::Component
{
public:
	PlayerMovementComponent(const std::shared_ptr<dae::GameObject>& gameObject, float speed);
	void Update(float elapsedSec);
	const Rectf& Move(Rectf& shape, const Vector2f& direction);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	float m_Speed{ 0.0f };
	float m_ElapsedSec{ 0.0f };
};


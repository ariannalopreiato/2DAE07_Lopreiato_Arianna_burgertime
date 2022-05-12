#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Vector2f.h"
#include "Transform.h"
class PlayerMovementComponent : public dae::Component
{
public:
	PlayerMovementComponent(const std::shared_ptr<dae::GameObject>& gameObject, float speed);
	void Update(float elapsedSec);
	void SetVelocity(const Vector2f& velocity);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	float m_Speed{ 0.0f };
	std::weak_ptr<dae::Transform> m_Transform;
	Vector2f m_Velocity{ 0.0f, 0.0f };
};


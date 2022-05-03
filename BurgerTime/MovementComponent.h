#pragma once
#include "Component.h"
#include "structs.h"
#include "Vector2f.h"

class MovementComponent : public dae::Component
{
public:
	MovementComponent(const std::shared_ptr<dae::GameObject>& gameObject, const float& speed);
	virtual void Update(float elapsedSec);
	void OnMovement();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	Vector2f m_Velocity{ 0.0f, 0.0f };
	float m_Speed{ 0.0f };
	bool m_IsMoving{ false };
};


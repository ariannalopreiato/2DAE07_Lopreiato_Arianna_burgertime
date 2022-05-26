#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Transform.h"
#include "LevelCreator.h"

class PlayerMovementComponent : public dae::Component
{
public:
	PlayerMovementComponent(const std::shared_ptr<dae::GameObject>& gameObject, float speed);
	void Update(float elapsedSec);
	void SetVelocity(glm::vec2 velocity);
	void MoveBack();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	const int m_MoveBack{ 2 };
	float m_Speed{ 0.0f };
	std::weak_ptr<dae::Transform> m_Transform;
	glm::vec2 m_Velocity{ 0.0f, 0.0f };
};


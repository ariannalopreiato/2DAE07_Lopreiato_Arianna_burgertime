#include "PlayerMovementComponent.h"

PlayerMovementComponent::PlayerMovementComponent(const std::shared_ptr<dae::GameObject>& gameObject, float speed)
	:Component(gameObject)
	, m_Speed(speed)
{}

void PlayerMovementComponent::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;
}

const Rectf& PlayerMovementComponent::Move(Rectf& shape, const Vector2f& direction)
{
	shape.left += m_ElapsedSec * (direction.x * m_Speed);
	shape.bottom += m_ElapsedSec * (direction.y * m_Speed);
	return shape;
}

std::shared_ptr<dae::Component> PlayerMovementComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PlayerMovementComponent>(gameObject, m_Speed);
}

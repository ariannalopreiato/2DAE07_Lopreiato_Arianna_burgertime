#include "PlayerMovementComponent.h"
#include "GameObject.h"

PlayerMovementComponent::PlayerMovementComponent(const std::shared_ptr<dae::GameObject>& gameObject, float speed)
	:Component(gameObject)
	, m_Speed(speed)
{
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
}

void PlayerMovementComponent::Update(float elapsedSec)
{
	auto currentPos = m_Transform.lock()->GetPosition(); //get current position
	glm::vec2 startPos{ currentPos.x, currentPos.y };
	startPos.x += elapsedSec * (m_Velocity.x * m_Speed);
	startPos.y += elapsedSec * (m_Velocity.y * m_Speed);
	m_Transform.lock()->SetPosition(startPos.x, startPos.y, 0.0f); //pass new position
}

void PlayerMovementComponent::SetVelocity(glm::vec2 velocity)
{
	m_Velocity = velocity;
}


std::shared_ptr<dae::Component> PlayerMovementComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PlayerMovementComponent>(gameObject, m_Speed);
}

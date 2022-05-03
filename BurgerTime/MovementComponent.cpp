#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "InputComponent.h"

MovementComponent::MovementComponent(const std::shared_ptr<dae::GameObject>& gameObject, const float& speed)
	:Component(gameObject)
	, m_Speed(speed)
{}

void MovementComponent::Update(float elapsedSec)
{
	if (m_IsMoving) //if there is input, move character
	{
		auto collision = m_GameObject.lock()->GetComponent<CollisionComponent>();
		Rectf shape = collision->m_Shape;
		shape.bottom += m_Velocity.y * elapsedSec;
		shape.left += m_Velocity.x * elapsedSec;
		collision->m_Shape = shape;
		m_IsMoving = false;
	}
}

void MovementComponent::OnMovement()
{
	m_IsMoving = true;
}

std::shared_ptr<dae::Component> MovementComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<MovementComponent>(gameObject, m_Speed);
}
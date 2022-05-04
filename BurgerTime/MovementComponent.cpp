#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "InputComponent.h"

MovementComponent::MovementComponent(const std::shared_ptr<dae::GameObject>& gameObject, bool isControlled)
	:Component(gameObject)
	, m_IsControlled(isControlled)
{}

std::shared_ptr<dae::Component> MovementComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<MovementComponent>(gameObject, m_IsControlled);
}

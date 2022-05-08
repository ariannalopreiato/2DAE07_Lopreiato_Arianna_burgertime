#include "PlayerAttackComponent.h"

PlayerAttackComponent::PlayerAttackComponent(const std::shared_ptr<dae::GameObject>& gameObject, int pepperShots)
	:Component(gameObject)
	, m_PepperShots(pepperShots)
	, m_CurrentShots(pepperShots)
{}

void PlayerAttackComponent::Attack()
{
	if (m_CurrentShots > 0)
		--m_CurrentShots;
}

int PlayerAttackComponent::GetPepperShots() const
{
	return m_CurrentShots;
}

std::shared_ptr<dae::Component> PlayerAttackComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PlayerAttackComponent>(gameObject, m_PepperShots);
}

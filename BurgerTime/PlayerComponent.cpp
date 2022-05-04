#include "PlayerComponent.h"
#include <iostream>

PlayerComponent::PlayerComponent(const std::shared_ptr<dae::GameObject>& gameObject, int pepperShots)
	:Component(gameObject)
	, m_PepperShots(pepperShots)
	, m_CurrentShots(pepperShots)
{}

void PlayerComponent::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;
}

void PlayerComponent::Move()
{
	
}

void PlayerComponent::Attack()
{
	if (m_PepperShots > 0)
		--m_PepperShots;
}

std::shared_ptr<dae::Component> PlayerComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PlayerComponent>(gameObject, m_PepperShots);
}

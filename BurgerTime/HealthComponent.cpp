#include "HealthComponent.h"

HealthComponent::HealthComponent(std::shared_ptr<dae::GameObject> gameObject, int lives)
	:Component(gameObject)
	,m_StartingLives(lives)
	, m_CurrentLives(lives)
{}

void HealthComponent::Update(float)
{
	if (m_IsDead) 
	{
		m_CurrentLives = m_StartingLives;
		m_IsDead = false;
	};
}

int HealthComponent::GetCurrentLives() const
{
	return m_CurrentLives;
}

void HealthComponent::RemoveLife()
{
	if (m_CurrentLives > 1)
		--m_CurrentLives;
	else
		m_IsDead = true;
}

std::shared_ptr<dae::Component> HealthComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<HealthComponent>(gameObject, m_StartingLives);
}

bool HealthComponent::IsDead() const
{
	return m_IsDead;
}

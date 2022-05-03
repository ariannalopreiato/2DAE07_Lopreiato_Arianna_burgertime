#include "AttackComponent.h"
#include "InputComponent.h"

AttackComponent::AttackComponent(std::shared_ptr<dae::GameObject> gameObject, int pepperShots)
	:Component(gameObject)
	, m_PepperShots(pepperShots)
	, m_CurrentShots(pepperShots)
{}

void AttackComponent::Update()
{
	auto input = m_GameObject.lock()->GetComponent<InputComponent>();
	if (input->IsAttacking() && m_CurrentShots > 0)
	{
		--m_CurrentShots;
	}
}

std::shared_ptr<dae::Component> AttackComponent::Clone(const std::shared_ptr<dae::GameObject>&gameObject)
{
	return std::make_shared<AttackComponent>(gameObject, m_PepperShots);
}

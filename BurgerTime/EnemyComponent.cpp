#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(const std::shared_ptr<dae::GameObject>& gameObject, EnemyType enemyType)
	:Component(gameObject)
	, m_EnemyType(enemyType)
{}

void EnemyComponent::Update(float)
{
}

void EnemyComponent::Render() const
{
}

std::shared_ptr<dae::Component> EnemyComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<EnemyComponent>(gameObject, m_EnemyType);
}

#include "EnemyManager.h"
#include "GameObject.h"

EnemyManager::EnemyManager(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
{}

void EnemyManager::Update(float)
{

}

void EnemyManager::Render() const
{
}

const std::vector<std::weak_ptr<Enemy>>& EnemyManager::GetEnemies() const
{
	return m_Enemies;
}

std::shared_ptr<dae::Component> EnemyManager::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<EnemyManager>(gameObject);
}

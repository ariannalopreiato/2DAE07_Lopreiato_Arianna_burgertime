#include "EnemyManager.h"
#include "GameObject.h"

EnemyManager::EnemyManager()
{}

void EnemyManager::Update(float)
{

}
  
std::shared_ptr<dae::GameObject> EnemyManager::SpawnMrEgg(float posX, float posY)
{
	auto enemy = SpawnEnemy(posX, posY);
	auto egg = std::make_shared<MrEggComponent>(enemy);
	enemy->AddComponent(egg);
	return enemy;
}

std::shared_ptr<dae::GameObject> EnemyManager::SpawnMrHotDog(float posX, float posY)
{
	auto enemy = SpawnEnemy(posX, posY);
	auto hotDog = std::make_shared<MrHotDogComponent>(enemy);
	enemy->AddComponent(hotDog);
	return enemy;
}

std::shared_ptr<dae::GameObject> EnemyManager::SpawnMrPickle(float posX, float posY)
{
	auto enemy = SpawnEnemy(posX, posY);
	auto pickle = std::make_shared<MrPickleComponent>(enemy);
	enemy->AddComponent(pickle);
	return enemy;
}

std::shared_ptr<dae::GameObject> EnemyManager::SpawnEnemy(float posX, float posY)
{
	auto enemyObj = std::make_shared<dae::GameObject>();
	enemyObj->GetComponent<dae::Transform>()->SetPosition(posX, posY, 0.0f);

	auto collisionComponent = std::make_shared<dae::CollisionComponent>(enemyObj);
	auto healthComponent = std::make_shared<HealthComponent>(enemyObj, 1);

	enemyObj->AddComponent(collisionComponent);
	enemyObj->AddComponent(healthComponent);
	m_Enemies.emplace_back(enemyObj);
	return enemyObj;
}

const std::vector<std::weak_ptr<dae::GameObject>>& EnemyManager::GetEnemies()
{
	return m_Enemies;
}

void EnemyManager::SetPlayerPos(const SDL_Rect& playerPos)
{
	for (size_t i = 0; i < m_Enemies.size(); ++i)
	{
		auto enemy = m_Enemies.at(i).lock()->GetComponent<EnemyComponent>();
		if(enemy != nullptr)
			enemy->SetPlayerPos(playerPos);
	}
}

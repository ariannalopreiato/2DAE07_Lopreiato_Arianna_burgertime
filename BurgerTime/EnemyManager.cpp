#include "EnemyManager.h"
#include "GameObject.h"
#include "LevelCreator.h"

EnemyManager::EnemyManager()
{
	auto ingredients = LevelCreator::GetIngredients();
	for (size_t i = 0; i < ingredients.size(); ++i)
		m_Ingredients.emplace_back(ingredients[i]->GetGameObject());
}

void EnemyManager::Update(float)
{
	if (m_Ingredients.empty())
	{
		auto ingredients = LevelCreator::GetIngredients();
		for (size_t i = 0; i < ingredients.size(); ++i)
			m_Ingredients.emplace_back(ingredients[i]->GetGameObject());
	}
}

void EnemyManager::SetScoreComponent(const std::shared_ptr<dae::GameObject>& scoreComponent)
{
	m_Score.lock() = scoreComponent;
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

	auto behaviourComponent = std::make_shared<CharacterBehaviour>(enemyObj);

	enemyObj->AddComponent(collisionComponent);
	enemyObj->AddComponent(behaviourComponent);
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
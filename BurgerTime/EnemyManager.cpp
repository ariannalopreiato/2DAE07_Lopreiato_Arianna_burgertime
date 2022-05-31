#include "EnemyManager.h"
#include "GameObject.h"

EnemyManager::EnemyManager()
{
	m_Ingredients = LevelCreator::GetIngredients();
}

void EnemyManager::Update(float)
{
	if(m_Ingredients.empty())
		m_Ingredients = LevelCreator::GetIngredients();
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

//void EnemyManager::CheckInOnIngredient()
//{
//	for (size_t i = 0; i < m_Ingredients.size(); ++i)
//	{
//		auto enemyBox = m_Enemies[i].lock()->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
//		auto ingredientBox = m_Ingredients[i]->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
//	}
//}
//
//void EnemyManager::CheckIsBeingHitByIngredient()
//{
//	for (size_t i = 0; i < m_Ingredients.size(); ++i)
//	{
//		auto enemyColl = m_Enemies[i].lock()->GetComponent<dae::CollisionComponent>();
//		auto enemyBox = enemyColl->GetCollisionBox();
//		auto ingredientBox = m_Ingredients[i]->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
//		bool isFalling = m_Ingredients[i]->GetComponent<Ingredient>()->IsIngredientFalling();
//
//		if (enemyColl->IsOverlapping(ingredientBox) && isFalling) 
//		{
//			if (enemyBox.y > ingredientBox.y) //the ingredient falls on the enemy
//				m_Enemies[i].lock()->GetComponent<EnemyComponent>()->Die();
//			else if (enemyBox.y + enemyBox.h < ingredientBox.y + ingredientBox.h) //the enemy is on the falling ingredient
//				m_Enemies[i].lock()->GetComponent<EnemyComponent>()->StayOnFallingIngredient();
//		}
//	}
//}

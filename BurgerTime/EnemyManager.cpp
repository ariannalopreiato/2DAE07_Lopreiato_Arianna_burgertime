#include "EnemyManager.h"
#include "GameObject.h"

EnemyManager::EnemyManager()
{}

void EnemyManager::Update(float)
{

}

std::shared_ptr<dae::GameObject> EnemyManager::SpawnMrEgg(float posX, float posY)
{
	int points{ 300 };
	std::shared_ptr<dae::Texture2D> picture{};
	picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/MrEgg.png");
	return SpawnEnemy(posX, posY, points, picture);
}

std::shared_ptr<dae::GameObject> EnemyManager::SpawnMrHotDog(float posX, float posY)
{
	int points{ 100 };
	std::shared_ptr<dae::Texture2D> picture{};
	picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/MrHotDog.png");
	return SpawnEnemy(posX, posY, points, picture);
}

std::shared_ptr<dae::GameObject> EnemyManager::SpawnMrPickle(float posX, float posY)
{
	int points{ 200 };
	std::shared_ptr<dae::Texture2D> picture{};
	picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/MrPickle.png");
	return SpawnEnemy(posX, posY, points, picture);
}

std::shared_ptr<dae::GameObject> EnemyManager::SpawnEnemy(float posX, float posY, int points, const std::shared_ptr<dae::Texture2D>& texture)
{
	auto enemyObj = std::make_shared<dae::GameObject>();
	enemyObj->GetComponent<dae::Transform>()->SetPosition(posX, posY, 0.0f);

	auto enemyComponent = std::make_shared<EnemyComponent>(enemyObj);
	auto textureComponent = std::make_shared<dae::TextureComponent>(enemyObj, texture);
	auto pointComponent = std::make_shared<PointComponent>(enemyObj, points);
	auto collisionComponent = std::make_shared<dae::CollisionComponent>(enemyObj);
	auto healthComponent = std::make_shared<HealthComponent>(enemyObj, 1);
	auto animationComponent = std::make_shared<dae::AnimationComponent>(enemyObj, 2, 6, 8, 1);

	enemyObj->AddComponent(textureComponent);
	enemyObj->AddComponent(pointComponent);
	enemyObj->AddComponent(collisionComponent);
	enemyObj->AddComponent(healthComponent);
	enemyObj->AddComponent(animationComponent);
	enemyObj->AddComponent(enemyComponent);
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
		m_Enemies.at(i).lock()->GetComponent<EnemyComponent>()->SetPlayerPos(playerPos);
}

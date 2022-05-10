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

std::shared_ptr<dae::GameObject> EnemyManager::SpawnEnemy(EnemyType enemyType)
{
	int points{ 0 };    
	std::shared_ptr<dae::Texture2D> picture{}; 
	switch (enemyType)
	{
	case EnemyType::mrEgg:
		points = 300;
		picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/MrEgg.png");
		break;

	case EnemyType::mrHotDog:
		points = 100;
		picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/MrHotDog.png");
		break;

	case EnemyType::mrPickle:
		points = 200;
		picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/MrPickle.png");
		break;
	}

	auto enemyObj = std::shared_ptr<dae::GameObject>();
	auto enemyComponent = std::make_shared<EnemyComponent>(enemyObj, enemyType); //create requested enemy
	auto pointComponent = std::make_shared<PointComponent>(enemyObj, points);
	auto textureComponent = std::make_shared<dae::TextureComponent>(enemyObj, picture);
	auto collisionComponent = std::make_shared<dae::CollisionComponent>(enemyObj);
	auto healthComponent = std::make_shared<HealthComponent>(enemyObj, 1);
	auto animationComponent = std::make_shared<dae::AnimationComponent>(enemyObj, 8, 4, 8, 1);
	enemyObj->AddComponent(enemyComponent);
	enemyObj->AddComponent(pointComponent);
	enemyObj->AddComponent(textureComponent);
	enemyObj->AddComponent(collisionComponent);
	enemyObj->AddComponent(healthComponent);
	enemyObj->AddComponent(animationComponent);
	//m_GameObject.lock()->AddChild(enemyObj, std::make_shared<dae::GameObject>(this));    ???
	return enemyObj;
}

std::shared_ptr<dae::Component> EnemyManager::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<EnemyManager>(gameObject);
}

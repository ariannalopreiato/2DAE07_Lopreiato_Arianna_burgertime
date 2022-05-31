#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "PointComponent.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "HealthComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "MrEggComponent.h"
#include "MrHotDogComponent.h"
#include "MrPickleComponent.h"
#include "LevelCreator.h"

class EnemyManager
{
public:
	static void Update(float elapsedSec);
	static void SetScoreComponent(const std::shared_ptr<dae::GameObject>& scoreComponent);
	static std::shared_ptr<dae::GameObject> SpawnMrEgg(float posX, float posY);
	static std::shared_ptr<dae::GameObject> SpawnMrHotDog(float posX, float posY);
	static std::shared_ptr<dae::GameObject> SpawnMrPickle(float posX, float posY);
	static const std::vector<std::weak_ptr<dae::GameObject>>& GetEnemies();
	static void SetPlayerPos(const SDL_Rect& playerPos);
	//static void CheckInOnIngredient();
	//static void CheckIsBeingHitByIngredient();
	//static void RemoveEnemy(int index);

private:
	EnemyManager();
	static std::shared_ptr<dae::GameObject> SpawnEnemy(float posX, float posY);
	inline static std::vector<std::weak_ptr<dae::GameObject>> m_Enemies;
	inline static std::vector<std::shared_ptr<dae::GameObject>> m_Ingredients;
	inline static std::weak_ptr<dae::GameObject> m_Score;
};
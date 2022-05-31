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

class EnemyManager
{
public:
	static void Update(float elapsedSec);
	static std::shared_ptr<dae::GameObject> SpawnMrEgg(float posX, float posY);
	static std::shared_ptr<dae::GameObject> SpawnMrHotDog(float posX, float posY);
	static std::shared_ptr<dae::GameObject> SpawnMrPickle(float posX, float posY);
	static const std::vector<std::weak_ptr<dae::GameObject>>& GetEnemies();
	static void SetPlayerPos(const SDL_Rect& playerPos);
	//static void RemoveEnemy(int index);

private:
	EnemyManager();
	static std::shared_ptr<dae::GameObject> SpawnEnemy(float posX, float posY);
	inline static std::vector<std::weak_ptr<dae::GameObject>> m_Enemies;
};
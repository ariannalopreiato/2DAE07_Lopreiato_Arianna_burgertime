#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "CollisionComponent.h"
#include "MrEggComponent.h"
#include "MrHotDogComponent.h"
#include "MrPickleComponent.h"
#include "CharacterBehaviour.h"

class EnemyManager
{
public:
	static void Update(float elapsedSec);
	static void SetScoreComponent(const std::shared_ptr<dae::GameObject>& scoreComponent);
	static void SpawnAllLevelEnemies(const std::string& path);
	static const std::vector<std::shared_ptr<dae::GameObject>>& GetEnemies();
	static void SetPlayerPos(const SDL_Rect& playerPos);

private:
	EnemyManager();
	static void SpawnElementsOfRow(const std::string& start, const std::string& currentLine);
	static const glm::vec2 GetPosition(const std::string& string);
	static void SpawnMrEgg(float posX, float posY);
	static void SpawnMrHotDog(float posX, float posY);
	static void SpawnMrPickle(float posX, float posY);
	static std::shared_ptr<dae::GameObject> SpawnEnemy(float posX, float posY);
	inline static std::vector<std::shared_ptr<dae::GameObject>> m_Enemies;
	inline static std::vector<std::shared_ptr<dae::GameObject>> m_Ingredients;
	inline static std::weak_ptr<dae::GameObject> m_Score;
};
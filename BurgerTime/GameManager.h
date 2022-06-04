#pragma once
#include "MiniginPCH.h"
#include "LevelCreator.h"
#include "PlayerComponent.h"
#include "PlayerAttackComponent.h"
#include "PlayerMovementComponent.h"
#include "CharacterBehaviour.h"
#include "ControllerButton.h"
#include "CollisionComponent.h"
#include "AttackCommand.h"
#include "PointComponent.h"

enum class GameMode
{
	single, multi, versus
};

class GameManager
{
public:
	static void AddIngredient();
	static void SetGameMode(GameMode gameMode);
	static void LoadUI(const std::shared_ptr<dae::Font>& font);
	static void LoadLevel(const std::string& levelPath, const std::shared_ptr<PointComponent> score);
	static void LoadEnemies(const std::string& enemiesPath);
	static void LoadPlayers(const glm::vec3& pos1, const glm::vec3& pos2 = { 0.0f, 0.0f, 0.0f });
	//static void Update(float elapsedSec);
	//void LevelComplete();

private:
	GameManager() {};
	static void NextScene();
	static std::shared_ptr<dae::GameObject> InitializePlayer(int playerIdx, const glm::vec3& startPos, const std::string& texture, bool isEnemy, std::shared_ptr<HealthComponent> multiPlayer = nullptr);

	inline static GameMode m_GameMode;
	inline static bool m_StartWaiting{ false };
	inline static int m_AmountOfIngredients{ 0 };
	inline static int m_NrScenes{ 1 };
	inline static int m_CurrentAmountIngredientsOnPlate{ 0 };
	inline static float m_CurrentTime{ 0.0f };
	inline static float m_TotaWaitTime{ 2.f };
};

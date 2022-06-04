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

enum class InputMethod
{
	keyboard, controller
};

class GameManager
{
public:
	static void InputSetup(InputMethod inputOne = InputMethod::keyboard, InputMethod inputTwo = InputMethod::keyboard);
	static void AddIngredient();
	static void SetGameMode(GameMode gameMode);
	static void LoadUI(const std::shared_ptr<dae::Font>& font);
	static void LoadLevel(const std::string& levelPath, const std::shared_ptr<PointComponent> score);
	static void LoadPlayersAndEnemies(const glm::vec3& pos1, const std::string& enemiesPath, const glm::vec3& pos2 = { 0.0f, 0.0f, 0.0f });

private:
	GameManager() {};
	static void SetUpInputKeyboard(const std::shared_ptr<PlayerComponent>& player, int playerIdx);
	static void SetUpInputController(const std::shared_ptr<PlayerComponent>& player);
	static void NextScene();
	static void LoadEnemies(const std::string& enemiesPath);
	static std::shared_ptr<dae::GameObject> InitializePlayer(int playerIdx, const glm::vec3& startPos, const std::string& texture, bool isEnemy, std::shared_ptr<HealthComponent> multiPlayer = nullptr, std::shared_ptr<dae::GameObject> otherPlayer = nullptr);

	inline static GameMode m_GameMode;
	inline static bool m_StartWaiting{ false };
	inline static int m_AmountOfIngredients{ 0 };
	inline static int m_NrScenes{ 1 };
	inline static int m_CurrentAmountIngredientsOnPlate{ 0 };
	inline static float m_CurrentTime{ 0.0f };
	inline static float m_TotaWaitTime{ 2.f };
	inline static InputMethod m_InputOne{};
	inline static InputMethod m_InputTwo{};
};

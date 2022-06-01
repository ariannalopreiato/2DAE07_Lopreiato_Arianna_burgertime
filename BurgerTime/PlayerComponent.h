#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Command.h"
#include "ControllerButton.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "MoveCommand.h"
#include "HealthComponent.h"
#include "LevelCreator.h"
#include "LevelObjectType.h"
#include "EnemyManager.h"

enum class PlayerState
{
	idle, walking, attacking, climbing
};

struct Line
{
	int x1, y1, x2, y2;
};

class PlayerComponent : public dae::Component
{
public:
	PlayerComponent(const std::shared_ptr<dae::GameObject>& gameObject, int playerIdx);
	void Update(float elapsedSec);
	void Render() const;
	void AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button, bool executeOnPress, int playerIdx);
	void AddCommand(std::unique_ptr<dae::Command> command, SDL_Scancode key, bool executeOnPress, int playerIdx);
	void CheckStates();
	void Move(PlayerDirection direction);
	void CheckIsNextToStairs();
	void IsWalkingOnIngredient();
	void Attack();
	bool CanGoLeft();
	bool CanGoRight();
	void SnapBack();
	void SnapDown();
	void SnapToStair(const SDL_Rect& stairBox);
	glm::vec2 GetVelocity() const;
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	void CheckIsHitByEnemy();

	//Player info
	int m_PlayerIdx{ 0 };
	const float m_PlayerWidth{ 30.f };
	const float m_PlayerHeight{ 30.f };
	glm::vec2 m_Velocity{};
	glm::vec3 m_StartPos{};

	//Handle animation
	bool m_IsNextToStairs{ false };
	const int m_StartingColHorizontal{ 3 };
	const int m_StartingColUp{ 6 };
	const int m_StartingColDown{ 0 };
	int m_CurrentCol{ 0 };

	//Players state
	PlayerState m_PlayerState{ PlayerState::idle };
	PlayerDirection m_PlayerDirection{ PlayerDirection::down };

	//Components
	std::weak_ptr<dae::CollisionComponent> m_Collision;
	std::weak_ptr<PlayerMovementComponent> m_Movement;
	std::weak_ptr<PlayerAttackComponent> m_Attack;
	std::weak_ptr<dae::TextureComponent> m_Texture;
	std::weak_ptr<dae::AnimationComponent> m_Animation;
	std::weak_ptr<HealthComponent> m_Health;
	std::weak_ptr<dae::Transform> m_Transform;

	SDL_Rect test{};
	Line m_LineLeft{};
	Line m_LineRight{};
	SDL_Rect m_PlatformColliding{};
	int m_LineLength{ 5 };
};


#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Vector2f.h"
#include "Command.h"
#include "ControllerButton.h"
#include "KeyboardButton.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "MoveCommand.h"
#include "PointComponent.h"
#include "HealthComponent.h"

enum class PlayerState
{
	idle, walking, attacking, climbing
};

class PlayerComponent : public dae::Component
{
public:
	PlayerComponent(const std::shared_ptr<dae::GameObject>& gameObject, int playerIdx);
	void Update(float elapsedSec);
	void AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button, bool executeOnPress, int playerIdx);
	void AddCommand(std::unique_ptr<dae::Command> command, dae::KeyboardButton key, bool executeOnPress, int playerIdx);
	void Move(PlayerDirection direction);
	void SetIsNextToStair(bool isNextToStair);
	void Attack();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	//Player info
	int m_PlayerIdx{ 0 };
	const float m_PlayerSize{ 30.f };
	Vector2f m_Velocity{};

	//Handle animation
	bool m_IsImageFlipped{ false };
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
	std::weak_ptr<PointComponent> m_Points;
	std::weak_ptr<HealthComponent> m_Health;
	std::weak_ptr<dae::Transform> m_Transform;
};


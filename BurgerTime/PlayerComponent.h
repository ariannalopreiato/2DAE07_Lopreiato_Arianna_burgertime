#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Vector2f.h"
#include "Command.h"
#include "ControllerButton.h"
#include "KeyboardButton.h"
#include "PlayerState.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "MoveCommand.h"

class PlayerComponent : public dae::Component
{
public:
	PlayerComponent(const std::shared_ptr<dae::GameObject>& gameObject, int playerIdx);
	void Update(float elapsedSec);
	void AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button, bool executeOnPress, int playerIdx);
	void AddCommand(std::unique_ptr<dae::Command> command, dae::KeyboardButton key, bool executeOnPress, int playerIdx);
	void Move(PlayerDirection direction);
	void Attack();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	int m_PlayerIdx{ 0 };
	Vector2f m_Velocity{};
	bool m_IsImageFlipped{ false };
	PlayerState m_PlayerState{ PlayerState::idle };
	std::weak_ptr<dae::CollisionComponent> m_Collision;
	std::weak_ptr<PlayerMovementComponent> m_Movement;
	std::weak_ptr<PlayerAttackComponent> m_Attack;
	std::weak_ptr<dae::TextureComponent> m_Texture;
	std::weak_ptr<dae::AnimationComponent> m_Animation;
};


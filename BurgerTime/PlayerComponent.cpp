#include "PlayerComponent.h"
#include <iostream>
#include "GameObject.h"
#include "InputManager.h"

PlayerComponent::PlayerComponent(const std::shared_ptr<dae::GameObject>& gameObject, int playerIdx)
	:Component(gameObject)
	, m_PlayerIdx(playerIdx)
{}

void PlayerComponent::Update(float)
{
	if (m_Texture.lock() == nullptr)
		m_Texture = m_GameObject.lock()->GetComponent<dae::TextureComponent>();
	if (m_Animation.lock() == nullptr)
	{
		m_Animation = m_GameObject.lock()->GetComponent<dae::AnimationComponent>();
		m_Texture.lock()->SetDestinationSize(30.f, 30.f);
	}

	Rectf source = m_Animation.lock()->GetSource();
	m_Texture.lock()->SetSource(source);
}

void PlayerComponent::AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button, bool executeOnPress, int playerIdx)
{
	auto& inputManager = dae::InputManager::GetInstance();
	inputManager.AddCommandController(std::move(command), button, executeOnPress, playerIdx);
}

void PlayerComponent::AddCommand(std::unique_ptr<dae::Command> command, dae::KeyboardButton key, bool executeOnPress, int playerIdx)
{
	auto& inputManager = dae::InputManager::GetInstance();
	inputManager.AddCommandKeyboard(std::move(command), key, executeOnPress, playerIdx);
}

void PlayerComponent::Move(PlayerDirection direction)
{
	m_PlayerState = PlayerState::walking;

	if (m_Collision.lock() == nullptr)
		m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();
	if (m_Movement.lock() == nullptr)
		m_Movement = m_GameObject.lock()->GetComponent<PlayerMovementComponent>();

	if (m_IsImageFlipped)
	{
		m_Texture.lock()->SetFlip(SDL_FLIP_NONE);
		m_IsImageFlipped = false;
	}

	switch (direction)
	{
	//case PlayerDirection::down:
	//	m_Velocity.x = 0.0f;
	//	m_Velocity.y = 1.0f;
	//	break;
	//case PlayerDirection::up:
	//	m_Velocity.x = 0.0f;
	//	m_Velocity.y = -1.0f;
	//	break;
	case PlayerDirection::left:
		m_Velocity.x = -1.0f;
		m_Velocity.y = 0.0f;
		m_Animation.lock()->SetNewStartingCol(3);
		break;
	case PlayerDirection::right:
		m_Velocity.x = 1.0f;
		m_Velocity.y = 0.0f;
		m_Animation.lock()->SetNewStartingCol(3);
		m_Texture.lock()->SetFlip(SDL_FLIP_HORIZONTAL);
		m_IsImageFlipped = true;
		break;
	default:
		break;
	}

	Rectf shape = m_Collision.lock()->m_Shape;
	shape = m_Movement.lock()->Move(shape, m_Velocity);
	m_Collision.lock()->m_Shape = shape;
	m_Texture.lock()->SetPosition(shape.left, shape.bottom);

}

void PlayerComponent::Attack()
{
	m_PlayerState = PlayerState::attacking;

	if (m_Attack.lock() == nullptr)
		m_Attack = m_GameObject.lock()->GetComponent<PlayerAttackComponent>();

	//if it's attacking, it stops moving
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;
	m_Attack.lock()->Attack();
}

std::shared_ptr<dae::Component> PlayerComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PlayerComponent>(gameObject, m_PlayerIdx);
}
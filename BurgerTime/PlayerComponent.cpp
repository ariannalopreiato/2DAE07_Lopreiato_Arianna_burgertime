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

	if (m_Movement.lock() == nullptr)
		m_Movement = m_GameObject.lock()->GetComponent<PlayerMovementComponent>();

	if (m_Health.lock() == nullptr)
		m_Health = m_GameObject.lock()->GetComponent<HealthComponent>();

	if (m_Collision.lock() == nullptr)
	{
		m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();
		m_Collision.lock()->m_Shape.height = m_PlayerSize;
		m_Collision.lock()->m_Shape.width = m_PlayerSize;
	}
	if (m_Animation.lock() == nullptr)
	{
		m_Animation = m_GameObject.lock()->GetComponent<dae::AnimationComponent>();
		m_Texture.lock()->SetDestinationSize(m_PlayerSize, m_PlayerSize);
	}

	Rectf source = m_Animation.lock()->GetSource();
	m_Texture.lock()->SetSource(source);

	switch (m_PlayerState)
	{
	case PlayerState::attacking:
		m_Animation.lock()->m_CanAnimate = true;
		//if it's attacking, it stops moving
		m_Velocity.x = 0.0f;
		m_Velocity.y = 0.0f;
		break;
		
	case PlayerState::climbing:
		m_Animation.lock()->m_CanAnimate = true;
		switch (m_PlayerDirection)
		{
		case PlayerDirection::down:
			m_Velocity.x = 0.0f;
			m_Velocity.y = 1.0f;
			m_Animation.lock()->SetNewStartingCol(m_StartingColDown);
			m_CurrentCol = m_StartingColDown;
			break;
		case PlayerDirection::up:
			m_Velocity.x = 0.0f;
			m_Velocity.y = -1.0f;
			m_Animation.lock()->SetNewStartingCol(m_StartingColUp);
			m_CurrentCol = m_StartingColUp;
			m_IsImageFlipped = true;
			break;
		}
		break;

	case PlayerState::idle:
		m_Animation.lock()->m_CanAnimate = false;
		if(m_IsImageFlipped)
			m_Animation.lock()->SetNewStartingCol(m_CurrentCol - 1);
		else
			m_Animation.lock()->SetNewStartingCol(m_CurrentCol + 1);
		//if it's idle, it stops moving
		m_Velocity.x = 0.0f;
		m_Velocity.y = 0.0f;
		break;

	case PlayerState::walking:
		m_Animation.lock()->m_CanAnimate = true;
		m_Animation.lock()->SetNewStartingCol(m_StartingColHorizontal);
		m_CurrentCol = m_StartingColHorizontal;

		if (m_IsImageFlipped)
		{
			//flip the image to the original position
			m_Texture.lock()->SetFlip(SDL_FLIP_NONE);
			m_IsImageFlipped = false;
		}

		switch (m_PlayerDirection)
		{
		case PlayerDirection::left:
			m_Velocity.x = -1.0f;
			m_Velocity.y = 0.0f;
			break;
		case PlayerDirection::right:
			m_Velocity.x = 1.0f;
			m_Velocity.y = 0.0f;
			m_Texture.lock()->SetFlip(SDL_FLIP_HORIZONTAL); //flip the image
			m_IsImageFlipped = true;
			break;
		}
		break;
	}

	Rectf shape = m_Collision.lock()->m_Shape; //get current collision box
	shape = m_Movement.lock()->Move(shape, m_Velocity); //move the player
	m_Collision.lock()->m_Shape = shape; //set the new position of the collision box
	m_Texture.lock()->SetPosition(shape.left, shape.bottom); //pass the new position to the texture to move it
	m_PlayerState = PlayerState::idle;
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
	if(direction != PlayerDirection::up && direction != PlayerDirection::down)
		m_PlayerState = PlayerState::walking; 
	else
	{
		if (m_IsNextToStairs)
			m_PlayerState = PlayerState::climbing; //if it's next to a stair and it goes up/down it's climbing
		else
			m_PlayerState = PlayerState::idle; // if it's not next to a stair and it goes up/down it's idle
	}

	m_PlayerDirection = direction;
}

void PlayerComponent::SetIsNextToStair(bool isNextToStair)
{
	m_IsNextToStairs = isNextToStair;
}

void PlayerComponent::Attack()
{
	if (m_Attack.lock() == nullptr)
		m_Attack = m_GameObject.lock()->GetComponent<PlayerAttackComponent>();

	m_PlayerState = PlayerState::attacking;

	m_Attack.lock()->Attack();

	m_PlayerState = PlayerState::idle;
}

std::shared_ptr<dae::Component> PlayerComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PlayerComponent>(gameObject, m_PlayerIdx);
}
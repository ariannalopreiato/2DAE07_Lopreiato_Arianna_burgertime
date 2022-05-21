#include "PlayerComponent.h"
#include <iostream>
#include "GameObject.h"
#include "InputManager.h"
#include "Renderer.h"

PlayerComponent::PlayerComponent(const std::shared_ptr<dae::GameObject>& gameObject, int playerIdx)
	:Component(gameObject)
	, m_PlayerIdx(playerIdx)
{
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
	m_Transform.lock()->SetSize(m_PlayerSize, m_PlayerSize, 0.0f);
	m_Transform.lock()->SetPosition(50.0f, 350.f, 0.0f);
}

void PlayerComponent::Update(float)
{
	if (m_Texture.lock() == nullptr)
		m_Texture = m_GameObject.lock()->GetComponent<dae::TextureComponent>();

	if (m_Movement.lock() == nullptr)
		m_Movement = m_GameObject.lock()->GetComponent<PlayerMovementComponent>();

	if (m_Health.lock() == nullptr)
		m_Health = m_GameObject.lock()->GetComponent<HealthComponent>();

	if (m_Collision.lock() == nullptr)
		m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();

	if (m_Animation.lock() == nullptr)
		m_Animation = m_GameObject.lock()->GetComponent<dae::AnimationComponent>();
	
	//m_Collision.lock()->m_IsBoxVisible = true;

	SDL_Rect source = m_Animation.lock()->GetSource();
	m_Texture.lock()->SetSource(source);
	CheckIsNextToStairs();
	IsWalkingOnIngredient();

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

	m_Movement.lock()->SetVelocity(m_Velocity);
	m_PlayerState = PlayerState::idle;
}

void PlayerComponent::Render() const
{
	auto renderer = dae::Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, Uint8{ 255 }, Uint8{ 0 }, Uint8{ 0 }, Uint8{ 255 });
	SDL_RenderDrawRect(renderer, &test);
}

void PlayerComponent::AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button, bool executeOnPress, int playerIdx)
{
	auto& inputManager = dae::InputManager::GetInstance();
	inputManager.AddCommandController(std::move(command), button, executeOnPress, playerIdx);
}

void PlayerComponent::AddCommand(std::unique_ptr<dae::Command> command,SDL_Scancode key, bool executeOnPress, int playerIdx)
{
	auto& inputManager = dae::InputManager::GetInstance();
	inputManager.AddCommandKeyboard(std::move(command), key, executeOnPress, playerIdx);
}

void PlayerComponent::Move(PlayerDirection direction)
{
	if(direction != PlayerDirection::up && direction != PlayerDirection::down && m_PlayerState != PlayerState::climbing && IsOnPlatform())
		m_PlayerState = PlayerState::walking; 
	else
	{
		if (m_IsNextToStairs )//&& !IsOnPlatform())
			m_PlayerState = PlayerState::climbing; //if it's next to a stair and it goes up/down it's climbing
		else
			m_PlayerState = PlayerState::idle; // if it's not next to a stair and it goes up/down it's idle
	}

	m_PlayerDirection = direction;
}

void PlayerComponent::CheckIsNextToStairs()
{
	auto stairs = LevelCreator::GetStairs();
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	SDL_Rect playerCenter{};
	playerCenter.w = playerBox.w / 3;
	playerCenter.h = playerBox.h;
	playerCenter.y = playerBox.y;
	playerCenter.x = playerBox.x + playerCenter.w;
	test = playerCenter;

	for (size_t i = 0; i < stairs.size(); ++i)
	{
		auto stairCollision = stairs.at(i)->GetComponent<dae::CollisionComponent>();
		auto stairBox = stairCollision->GetCollisionBox();
		if (stairCollision->IsOverlapping(playerCenter))
		{
			m_IsNextToStairs = true;
			break;
		}
		else
			m_IsNextToStairs = false;
	}
}

bool PlayerComponent::IsOnPlatform()
{
	if (m_PlayerState != PlayerState::climbing)
	{
		auto objects = LevelCreator::GetObjects();
		auto playerBox = m_Collision.lock()->GetCollisionBox();
		for (int i = 0; i < objects.size(); ++i)
		{
			auto box = objects.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
			if (playerBox.y + playerBox.h == box.y)   
				return true;
		}
	}
	return false;
}

void PlayerComponent::IsWalkingOnIngredient()
{
	auto ingredients = LevelCreator::GetIngredients();
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	for (int i = 0; i < ingredients.size(); ++i)
	{
		auto pieces = ingredients.at(i)->GetComponent<Ingredient>()->GetPieces();
		for (size_t currentPiece = 0; currentPiece < pieces.size(); ++currentPiece)
		{
			auto box = pieces.at(currentPiece).shapeSize;
			if (box.y == playerBox.y + playerBox.h && playerBox.x + playerBox.w / 2 > box.x && playerBox.x + playerBox.w / 2 < box.x + box.w)
				ingredients.at(i)->GetComponent<Ingredient>()->SetHasWalkedOnPiece(currentPiece);
		}
	}
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
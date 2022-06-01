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
	m_Transform.lock()->SetSize(m_PlayerWidth, m_PlayerHeight, 0.0f);
	m_Transform.lock()->SetPosition(50.0f, 350.f, 0.0f);
	m_StartPos = m_Transform.lock()->GetPosition();
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

	auto playerCollBox{ m_Collision.lock()->GetCollisionBox() };
	m_LineLeft = Line{ playerCollBox.x, 
		playerCollBox.y + playerCollBox.h, 
		playerCollBox.x, 
		playerCollBox.y + playerCollBox.h + m_LineLength };
	m_LineRight = Line{ playerCollBox.x + playerCollBox.w, 
		playerCollBox.y + playerCollBox.h, 
		playerCollBox.x + playerCollBox.w, 
		playerCollBox.y + playerCollBox.h + m_LineLength };

	SDL_Rect source = m_Animation.lock()->GetSource();
	m_Texture.lock()->SetSource(source);

	CheckIsNextToStairs();

	IsWalkingOnIngredient();

	CheckIsHitByEnemy();

	CheckStates();
	
	EnemyManager::SetPlayerPos(m_Collision.lock()->GetCollisionBox());
}

void PlayerComponent::Render() const
{
	auto renderer = dae::Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, Uint8{ 255 }, Uint8{ 0 }, Uint8{ 0 }, Uint8{ 255 });
	SDL_RenderDrawRect(renderer, &test);
}

void PlayerComponent::AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button, bool executeOnPress)
{
	auto& inputManager = dae::InputManager::GetInstance();
	inputManager.AddCommandController(std::move(command), button, executeOnPress, m_PlayerIdx);
}

void PlayerComponent::AddCommand(std::unique_ptr<dae::Command> command,SDL_Scancode key, bool executeOnPress)
{
	auto& inputManager = dae::InputManager::GetInstance();
	inputManager.AddCommandKeyboard(std::move(command), key, executeOnPress, m_PlayerIdx);
}

void PlayerComponent::CheckStates()
{
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
			if (CanGoDown())
			{
				m_Velocity.x = 0.0f;
				m_Velocity.y = 1.0f;
				m_Animation.lock()->SetNewStartingCol(m_StartingColDown);
				m_CurrentCol = m_StartingColDown;
			}
			else
			{
				if (CanGoLeft() || CanGoRight())
					SnapDown();
			}
			break;
		case PlayerDirection::up:
			if (CanGoUp())
			{
				m_Velocity.x = 0.0f;
				m_Velocity.y = -1.0f;
				m_Animation.lock()->SetNewStartingCol(m_StartingColUp);
				m_CurrentCol = m_StartingColUp;
			}
			else
			{
				if (CanGoLeft() || CanGoRight())
					SnapDown();
			}
			m_Texture.lock()->m_IsImageFlipped = true;
			break;
		}
		break;

	case PlayerState::idle:
		m_Animation.lock()->m_CanAnimate = false;
		if (m_Texture.lock()->m_IsImageFlipped)
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

		if (m_Texture.lock()->m_IsImageFlipped)
		{
			//flip the image to the original position
			m_Texture.lock()->SetFlip(SDL_FLIP_NONE);
			m_Texture.lock()->m_IsImageFlipped = false;
		}

		switch (m_PlayerDirection)
		{
		case PlayerDirection::left:
			if (CanGoLeft())
			{
				m_Velocity.x = -1.0f;
				m_Velocity.y = 0.0f;
				//SnapDown();
			}
			else
				SnapBack();
			break;
		case PlayerDirection::right:
			if (CanGoRight())
			{
				m_Velocity.x = 1.0f;
				m_Velocity.y = 0.0f;
				//SnapDown();
			}
			else
				SnapBack();
			m_Texture.lock()->SetFlip(SDL_FLIP_HORIZONTAL); //flip the image
			m_Texture.lock()->m_IsImageFlipped = true;
			break;
		}
		break;
	}

	m_Movement.lock()->SetVelocity(m_Velocity);
	m_PlayerState = PlayerState::idle;
}

void PlayerComponent::Move(PlayerDirection direction)
{
	if (direction != PlayerDirection::up && direction != PlayerDirection::down && m_PlayerState != PlayerState::climbing
		&&(CanGoLeft() || CanGoRight()))
		m_PlayerState = PlayerState::walking;
	else
	{
		if (m_IsNextToStairs && (CanGoDown() || CanGoUp()))
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

void PlayerComponent::IsWalkingOnIngredient()
{
	auto ingredients = LevelCreator::GetIngredients();
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	for (size_t i = 0; i < ingredients.size(); ++i)
	{
		auto pieces = ingredients.at(i)->GetComponent<Ingredient>()->GetPieces();
		for (size_t currentPiece = 0; currentPiece < pieces.size(); ++currentPiece)
		{
			auto box = pieces.at(currentPiece).shapeSize;
			if (SDL_IntersectRectAndLine(&box, &m_LineLeft.x1, &m_LineLeft.y1, &m_LineLeft.x2, &m_LineLeft.y2)
				|| SDL_IntersectRectAndLine(&box, &m_LineRight.x1, &m_LineRight.y1, &m_LineRight.x2, &m_LineRight.y2))
				ingredients[i]->GetComponent<Ingredient>()->SetHasWalkedOnPiece(currentPiece);
		}
	}
}

void PlayerComponent::CheckIsHitByEnemy()
{
	auto enemies = EnemyManager::GetEnemies();
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		auto enemyColl = enemies[i].lock()->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
		if (m_Collision.lock()->IsOverlapping(enemyColl))
		{
			m_GameObject.lock()->GetComponent<HealthComponent>()->RemoveLife();
			m_Transform.lock()->SetPosition(m_StartPos);
			enemies[i].lock()->GetComponentInheritance<EnemyComponent>()->Die();
		}
	}
}

void PlayerComponent::Attack()
{
	if (m_Attack.lock() == nullptr)
		m_Attack = m_GameObject.lock()->GetComponent<PlayerAttackComponent>();

	m_PlayerState = PlayerState::attacking;
	m_Attack.lock()->Attack();
}

bool PlayerComponent::CanGoLeft()
{
	auto objects = LevelCreator::GetPlatforms();
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	for (size_t i = 0; i < objects.size(); ++i)
	{
		auto box = objects.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
		box.h = 1;
		if (SDL_IntersectRectAndLine(&box, &m_LineLeft.x1, &m_LineLeft.y1, &m_LineLeft.x2, &m_LineLeft.y2))
		{
			m_PlatformColliding = box;
			return true;
		}
	}
	return false;
}

bool PlayerComponent::CanGoRight()
{
	auto objects = LevelCreator::GetPlatforms();
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	for (size_t i = 0; i < objects.size(); ++i)
	{
		auto box = objects.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
		box.h = 1;
		if (SDL_IntersectRectAndLine(&box, &m_LineRight.x1, &m_LineRight.y1, &m_LineRight.x2, &m_LineRight.y2))
		{
			m_PlatformColliding = box;
			return true;
		}
	}
	return false;
}

bool PlayerComponent::CanGoUp()
{
	auto stairs = LevelCreator::GetStairs();
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	playerBox.h = 1;

	for (size_t i = 0; i < stairs.size(); ++i)
	{
		auto stairBox = stairs.at(i)->GetComponent<dae::CollisionComponent>();
		if (stairBox->IsOverlapping(playerBox))
			return true;
	}
	return false;
}

bool PlayerComponent::CanGoDown()
{
	auto stairs = LevelCreator::GetStairs();
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	playerBox.y = playerBox.y + playerBox.h;
	playerBox.h = 2;
	for (size_t i = 0; i < stairs.size(); ++i)
	{
		auto stairBox = stairs.at(i)->GetComponent<dae::CollisionComponent>();
		if (stairBox->IsOverlapping(playerBox))
			return true;
	}
	return false;
}

void PlayerComponent::SnapBack()
{
	int pushBack{ 1 };
	auto currentPos = m_Transform.lock()->GetPosition();
	if (!CanGoLeft())
		m_Transform.lock()->SetPosition(float(currentPos.x + pushBack), float(currentPos.y), 0.0f);
	else if (!CanGoRight())
		m_Transform.lock()->SetPosition(float(currentPos.x - pushBack), float(currentPos.y), 0.0f);
}

void PlayerComponent::SnapDown()
{
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	m_Transform.lock()->SetPosition(float(playerBox.x), float(m_PlatformColliding.y - playerBox.h), 0.0f);
}

void PlayerComponent::SnapToStair(const SDL_Rect& stairBox)
{
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	m_Transform.lock()->SetPosition(float(stairBox.x), float(playerBox.y), 0.0f);
}

glm::vec2 PlayerComponent::GetVelocity() const
{
	return m_Velocity;
}

std::shared_ptr<dae::Component> PlayerComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PlayerComponent>(gameObject, m_PlayerIdx);
}
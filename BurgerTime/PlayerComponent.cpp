#include "PlayerComponent.h"
#include <iostream>
#include "GameObject.h"
#include "InputManager.h"
#include "Renderer.h"

PlayerComponent::PlayerComponent(const std::shared_ptr<dae::GameObject>& gameObject, glm::vec3 position, int playerIdx, bool isEnemy)
	:Component(gameObject)
	, m_PlayerIdx(playerIdx)
	, m_IsEnemy(isEnemy)
	, m_StartPos(position)
{
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
	m_Transform.lock()->SetSize(m_PlayerWidth, m_PlayerHeight, 0.0f);
	m_Transform.lock()->SetPosition(position);
	m_StartPos = m_Transform.lock()->GetPosition();
	m_Behaviour = m_GameObject.lock()->GetComponent<CharacterBehaviour>();
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

	if(m_Behaviour.lock() == nullptr)
		m_Behaviour = m_GameObject.lock()->GetComponent<CharacterBehaviour>();

	auto playerCollBox{ m_Collision.lock()->GetCollisionBox() };

	SDL_Rect source = m_Animation.lock()->GetSource();
	m_Texture.lock()->SetSource(source);

	IsWalkingOnIngredient();

	if(!m_IsEnemy)
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
	inputManager.AddCommandKeyboard(std::move(command), key, executeOnPress);
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
			if (m_Behaviour.lock()->CanGoDown())
			{
				m_Velocity.x = 0.0f;
				m_Velocity.y = 1.0f;
				m_Animation.lock()->SetNewStartingCol(m_StartingColDown);
				m_CurrentCol = m_StartingColDown;
			}
			else
			{
				if (m_Behaviour.lock()->CanGoLeft() || m_Behaviour.lock()->CanGoRight())
					m_Behaviour.lock()->SnapDown();
			}
			break;
		case PlayerDirection::up:
			if (m_Behaviour.lock()->CanGoUp())
			{
				m_Velocity.x = 0.0f;
				m_Velocity.y = -1.0f;
				m_Animation.lock()->SetNewStartingCol(m_StartingColUp);
				m_CurrentCol = m_StartingColUp;
			}
			else
			{
				if (m_Behaviour.lock()->CanGoLeft() || m_Behaviour.lock()->CanGoRight())
					m_Behaviour.lock()->SnapDown();
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
			if (m_Behaviour.lock()->CanGoLeft())
			{
				m_Velocity.x = -1.0f;
				m_Velocity.y = 0.0f;
			}
			else
				m_Behaviour.lock()->SnapBack();
			break;
		case PlayerDirection::right:
			if (m_Behaviour.lock()->CanGoRight())
			{
				m_Velocity.x = 1.0f;
				m_Velocity.y = 0.0f;
			}
			else
				m_Behaviour.lock()->SnapBack();
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
		&&(m_Behaviour.lock()->CanGoLeft() || m_Behaviour.lock()->CanGoRight()))
		m_PlayerState = PlayerState::walking;
	else
	{
		if ((m_Behaviour.lock()->CanGoDown() || m_Behaviour.lock()->CanGoUp()))
			m_PlayerState = PlayerState::climbing; //if it's next to a stair and it goes up/down it's climbing
		else
			m_PlayerState = PlayerState::idle; // if it's not next to a stair and it goes up/down it's idle
	}
	m_PlayerDirection = direction;
}

void PlayerComponent::IsWalkingOnIngredient()
{
	auto characterBehaviour = m_GameObject.lock()->GetComponent<CharacterBehaviour>();
	Line lineLeft = characterBehaviour->GetLineLeft();
	Line lineRight = characterBehaviour->GetLineRight();
	auto ingredients = LevelCreator::GetIngredients();
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	for (size_t i = 0; i < ingredients.size(); ++i)
	{
		auto pieces = ingredients.at(i)->GetGameObject()->GetComponent<Ingredient>()->GetPieces();
		for (size_t currentPiece = 0; currentPiece < pieces.size(); ++currentPiece)
		{
			auto box = pieces.at(currentPiece).shapeSize;
			if (SDL_IntersectRectAndLine(&box, &lineLeft.x1, &lineLeft.y1, &lineLeft.x2, &lineLeft.y2)
				|| SDL_IntersectRectAndLine(&box, &lineRight.x1, &lineRight.y1, &lineRight.x2, &lineRight.y2))
				ingredients[i]->GetGameObject()->GetComponent<Ingredient>()->SetHasWalkedOnPiece(currentPiece);
		}
	}
}

void PlayerComponent::CheckIsHitByEnemy()
{
	auto enemies = EnemyManager::GetEnemies();
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		auto enemyColl = enemies[i]->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
		if (m_Collision.lock()->IsOverlapping(enemyColl) && !enemies[i]->GetComponentInheritance<EnemyComponent>()->GetIsDead())
		{
			m_GameObject.lock()->GetComponent<HealthComponent>()->RemoveLife();
			m_Transform.lock()->SetPosition(m_StartPos);
			enemies[i]->GetComponentInheritance<EnemyComponent>()->Die();
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
	return std::make_shared<PlayerComponent>(gameObject, m_StartPos,m_PlayerIdx);
}
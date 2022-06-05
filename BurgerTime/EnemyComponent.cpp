#include "EnemyComponent.h"
#include "GameObject.h"
#include "LevelCreator.h"

EnemyComponent::EnemyComponent(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
{
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
	m_StartPos = m_Transform.lock()->GetPosition();
	m_Transform.lock()->SetSize(m_EnemyWidth, m_EnemyHeight, 0.0f);
	m_Behaviour = m_GameObject.lock()->GetComponent<CharacterBehaviour>();
}

void EnemyComponent::Update(float elapsedSec)
{
	if (m_Animation.lock() == nullptr)
		m_Animation = m_GameObject.lock()->GetComponent<dae::AnimationComponent>();
	if (m_Texture.lock() == nullptr)
		m_Texture = m_GameObject.lock()->GetComponent<dae::TextureComponent>();
	if (m_Collision.lock() == nullptr)
		m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();
	if (m_Behaviour.lock() == nullptr)
		m_Behaviour = m_GameObject.lock()->GetComponent<CharacterBehaviour>();

	if (!m_IsFalling && !m_IsDead)
	{
		m_Animation.lock()->m_CanAnimate = true;
		m_Texture.lock()->m_IsImageShowing = true;

		SDL_Rect source = m_Animation.lock()->GetSource();
		m_Texture.lock()->SetSource(source);

		Move(elapsedSec);
	}
	else if (m_IsDead)
	{
		m_Animation.lock()->m_CanAnimate = false;
		m_Texture.lock()->m_IsImageShowing = false;
		if (m_CurrentRespawnTime >= m_RespawnTime)
		{
			m_IsDead = false;
			m_CurrentRespawnTime = 0.0f;
		}
		else
			m_CurrentRespawnTime += elapsedSec;
	}

	if (m_UseTimer)
	{
		m_CurrentTime += elapsedSec;
		if (m_CurrentTime >= m_MaxWaitTime)
		{
			m_CurrentTime = true;
			m_UseTimer = false;
		}
	}
	else
		CheckIntersection();
		
		
	CheckIsBeingHitByIngredient();
}

void EnemyComponent::Move(float elapsedSec)
{
	if (m_Texture.lock()->m_IsImageFlipped)
	{
		m_Texture.lock()->SetFlip(SDL_FLIP_NONE);
		m_Texture.lock()->m_IsImageFlipped = false;
	}
	if (m_Velocity.x > 0.0f)
	{
		m_Animation.lock()->SetNewStartingCol(m_StartingColHorizontal);
		m_Texture.lock()->SetFlip(SDL_FLIP_HORIZONTAL);
		m_Texture.lock()->m_IsImageFlipped = true;
	}
	else if (m_Velocity.x < 0.0f)
		m_Animation.lock()->SetNewStartingCol(m_StartingColHorizontal);


	auto currentPos = m_Transform.lock()->GetPosition(); //get current position
	glm::vec2 newPos{ currentPos.x, currentPos.y };
	newPos.x += elapsedSec * (m_Velocity.x * m_Speed);
	newPos.y += elapsedSec * (m_Velocity.y * m_Speed);
	m_Transform.lock()->SetPosition(newPos.x, newPos.y, 0.0f); //pass new position

	ImplementedMovement();
}

void EnemyComponent::MoveHorizontal()
{
	auto enemyBox = m_Collision.lock()->GetCollisionBox();

	if (!m_Behaviour.lock()->CanGoRight() && m_Behaviour.lock()->CanGoLeft())
	{
		m_Velocity.x = -1.0f;
		m_Velocity.y = 0.0f;
	}
	else if (m_Behaviour.lock()->CanGoRight() && !m_Behaviour.lock()->CanGoLeft())
	{
		m_Velocity.x = 1.0f;
		m_Velocity.y = 0.0f;
	}
	else if (m_Behaviour.lock()->CanGoRight() && m_Behaviour.lock()->CanGoLeft())
	{
		if (!m_IsMoving)
		{
			m_Velocity.y = 0.0f;
			if (m_PlayerPos.x > enemyBox.x)
				m_Velocity.x = 1.0f;
			else if (m_PlayerPos.x < enemyBox.x)
				m_Velocity.x = -1.0f;
			else if (m_PlayerPos.x == enemyBox.x)
			{
				int randNum = rand() % 2;
				if (randNum == 0)
					m_Velocity.x = 1.0f;

				else
					m_Velocity.x = -1.0f;
			}
		}
	}
	m_Behaviour.lock()->SnapDown();
	m_IsMoving = true;
	m_Animation.lock()->SetNewStartingCol(m_StartingColHorizontal);
	m_UseTimer = true;
	m_CanClimb = true;
}

void EnemyComponent::CheckIntersection()
{
	auto enemyBox = m_Collision.lock()->GetCollisionBox();

	if (m_Behaviour.lock()->CanGoLeft() || m_Behaviour.lock()->CanGoRight())
	{
		if ((m_Behaviour.lock()->CanGoDown() || m_Behaviour.lock()->CanGoUp()) && m_CanClimb)
		{
			if (m_Behaviour.lock()->CanGoDown() && !m_Behaviour.lock()->CanGoUp())
			{
				m_Velocity.x = 0.0f;
				m_Velocity.y = 1.0f;
			}
			if (!m_Behaviour.lock()->CanGoDown() && m_Behaviour.lock()->CanGoUp())
			{
				m_Velocity.x = 0.0f;
				m_Velocity.y = -1.0f;
			}
			if (m_Behaviour.lock()->CanGoDown() && m_Behaviour.lock()->CanGoUp())
			{
				m_Velocity.x = 0.0f;
				if (m_PlayerPos.y > enemyBox.y)
					m_Velocity.y = 1.0f;
				else if (m_PlayerPos.y < enemyBox.y)
					m_Velocity.y = -1.0f;
				else if (m_PlayerPos.y == enemyBox.y)
				{
					int randNum = rand() % 2;
					if (randNum == 0)
						m_Velocity.y = 1.0f;
					else
						m_Velocity.y = -1.0f;
				}
			}
			if (m_Velocity.y > 0.0f)
				m_Animation.lock()->SetNewStartingCol(m_StartingColDown);
			else
				m_Animation.lock()->SetNewStartingCol(m_StartingColUp);

			m_UseTimer = true;
			m_CanClimb = false;
			m_IsMoving = false;
		}
		else
		{
			MoveHorizontal();
			m_Behaviour.lock()->SnapBack();
		}
	}
}

bool EnemyComponent::GetIsStunned()
{
	return m_IsStunned;
}

bool EnemyComponent::GetIsDead()
{
	return m_IsDead;
}

void EnemyComponent::Die()
{
	notify(std::to_string(m_Points));
	m_IsDead = true;
	m_Transform.lock()->SetPosition(m_StartPos);
	m_UseTimer = true;
	m_CanClimb = true;
}

void EnemyComponent::SetPlayerPos(const SDL_Rect& playerPos)
{
	m_PlayerPos = playerPos;
}

void EnemyComponent::CheckIsBeingHitByIngredient()
{
	auto ingredients = LevelCreator::GetIngredients();
	for (size_t i = 0; i < ingredients.size(); ++i)
	{
		auto enemyBox = m_Collision.lock()->GetCollisionBox();
		auto ingredientBox = ingredients[i]->GetCollisionBox();
		bool isFalling = ingredients[i]->GetGameObject()->GetComponent<Ingredient>()->IsIngredientFalling();

		if (m_Collision.lock()->IsOverlapping(ingredientBox) && isFalling)
		{
			if (enemyBox.y > ingredientBox.y ) //the ingredient falls on the enemy
				Die();
			else if (enemyBox.y + enemyBox.h < ingredientBox.y + ingredientBox.h) //the enemy is on the falling ingredient
			{
				if (!m_IsFalling && !m_IsDead)
				{
					ingredients[i]->GetGameObject()->GetComponent<Ingredient>()->AddEnemyOnIngredient(m_GameObject.lock());
					m_IsFalling = true;
				}
			}
		}
	}
}
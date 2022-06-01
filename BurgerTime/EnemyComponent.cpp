#include "EnemyComponent.h"
#include "GameObject.h"

EnemyComponent::EnemyComponent(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
{
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
	m_StartPos = m_Transform.lock()->GetPosition();
	m_Transform.lock()->SetSize(m_EnemyWidth, m_EnemyHeight, 0.0f);
	m_Velocity.x = -1.0f;
	m_Velocity.y = 0.0f;

}

void EnemyComponent::Update(float elapsedSec)
{
	if (!m_IsFalling && !m_IsDead)
	{
		//when reaching intersection it checks which direction takes them closer to the player
		if (m_Animation.lock() == nullptr)
			m_Animation = m_GameObject.lock()->GetComponent<dae::AnimationComponent>();
		if (m_Texture.lock() == nullptr)
			m_Texture = m_GameObject.lock()->GetComponent<dae::TextureComponent>();
		if (m_Collision.lock() == nullptr)
			m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();

		if (m_Animation.lock() != nullptr && m_Texture.lock() != nullptr)
		{
			m_Collision.lock()->m_IsBoxVisible = true;
			m_Animation.lock()->m_CanAnimate = true;
			m_Texture.lock()->m_IsImageShowing = true;

			SDL_Rect source = m_Animation.lock()->GetSource();
			m_Texture.lock()->SetSource(source);

			Move(elapsedSec);
		}
	}
	else if (m_IsDead)
	{
		m_Animation.lock()->m_CanAnimate = false;
		m_Texture.lock()->m_IsImageShowing = false;
		if (m_CurrentTime >= m_MaxWaitTime)
		{
			m_IsDead = false;
			m_CurrentTime = 0.0f;
		}
		else
			m_CurrentTime += elapsedSec;
	}


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
	else if (m_Velocity.y > 0.0f)
		m_Animation.lock()->SetNewStartingCol(m_StartingColDown);
	else if (m_Velocity.y < 0.0f)
		m_Animation.lock()->SetNewStartingCol(m_StartingColUp);

	auto currentPos = m_Transform.lock()->GetPosition(); //get current position
	glm::vec2 newPos{ currentPos.x, currentPos.y };
	newPos.x += elapsedSec * (m_Velocity.x * m_Speed);
	newPos.y += elapsedSec * (m_Velocity.y * m_Speed);
	m_Transform.lock()->SetPosition(newPos.x, newPos.y, 0.0f); //pass new position

	CheckIntersection();

	ImplementedMovement();
}

bool EnemyComponent::IsNextToStairs()
{
	auto stairs = LevelCreator::GetStairs();
	auto enemyBox = m_Collision.lock()->GetCollisionBox();
	SDL_Rect enemyCenter{};
	enemyCenter.w = enemyBox.w / 3;
	enemyCenter.h = enemyBox.h;
	enemyCenter.y = enemyBox.y;
	enemyCenter.x = enemyBox.x + enemyCenter.w + enemyCenter.w / 2;

	for (size_t i = 0; i < stairs.size(); ++i)
	{
		auto stairCollision = stairs.at(i)->GetComponent<dae::CollisionComponent>();
		auto stairBox = stairCollision->GetCollisionBox();
		if (stairCollision->IsOverlapping(enemyCenter))
			//return true; 
			return false;
	}
	return false;
}

bool EnemyComponent::IsOnPlatform()
{
	auto platforms = LevelCreator::GetPlatforms();
	auto enemyBox = m_Collision.lock()->GetCollisionBox();
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		auto box = platforms.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
		int margin{ 2 };
		if ((enemyBox.y + enemyBox.h <= box.y - margin || enemyBox.y + enemyBox.h == box.y) && enemyBox.x >= box.x && enemyBox.x + enemyBox.w <= box.x + box. w)
		{
			m_CurrentPlatformShape = box;
			return true;
		}
	}
	return false;
}

bool EnemyComponent::CanGoUp()
{
	auto enemyBox = m_Collision.lock()->GetCollisionBox();
	if (m_CanClimb)
	{
		auto stairs = LevelCreator::GetStairs();
		for (size_t i = 0; i < stairs.size(); ++i)
		{
			auto stairBox = stairs.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
			if (stairBox.y < enemyBox.y + (enemyBox.h / 2))
			{
				return true;
			}
		}
	}
	return false;
}

bool EnemyComponent::CanGoDown()
{
	auto enemyBox = m_Collision.lock()->GetCollisionBox();
	if (m_CanClimb)
	{
		auto stairs = LevelCreator::GetStairs();
		for (size_t i = 0; i < stairs.size(); ++i)
		{
			auto stairBox = stairs.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
			if (stairBox.y > enemyBox.y + (enemyBox.h / 2))
			{
				return true;
			}
		}
	}
	return false;
}

void EnemyComponent::CheckIntersection()
{
	auto enemyBox = m_Collision.lock()->GetCollisionBox();
	if (IsNextToStairs() && IsOnPlatform())
	{
		if (CanGoDown() && !CanGoUp())
		{
			m_Velocity.x = 0.0f;
			m_Velocity.y = 1.0f;
			m_CanClimb = false;
		}
		else if (!CanGoDown() && CanGoUp())
		{
			m_Velocity.x = 0.0f;
			m_Velocity.y = -1.0f;
			m_CanClimb = false;
		}
		else if(CanGoUp() && CanGoDown())
		{
			m_Velocity.x = 0.0f;
			if (m_PlayerPos.y > enemyBox.y)
				m_Velocity.y = 1.0f;
			else if (m_PlayerPos.y < enemyBox.y)
				m_Velocity.y = -1.0f;
			else
			{
				int randNum = rand() % 2;
				if (randNum == 0)
					m_Velocity.y = 1.0f;
				else
					m_Velocity.y = -1.0f;
			}
		}
	}
	else if (IsOnPlatform() && !CanGoDown() && !CanGoUp())
	{
		enemyBox.y = m_CurrentPlatformShape.y + enemyBox.h;
		m_Transform.lock()->SetPosition(float(enemyBox.x), float(enemyBox.y), 0.0f);

		if (m_PlayerPos.x > enemyBox.x)
		{
			m_Velocity.x = 1.0f;
			m_Velocity.y = 0.0f;
		}
		else
		{
			m_Velocity.x = -1.0f;
			m_Velocity.y = 0.0f;
		}
		m_CanClimb = true;
	}
}

void EnemyComponent::Die()
{
	notify(std::to_string(m_Points));
	m_IsDead = true;
	m_Transform.lock()->SetPosition(m_StartPos);
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
		auto ingredientBox = ingredients[i]->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
		bool isFalling = ingredients[i]->GetComponent<Ingredient>()->IsIngredientFalling();

		if (m_Collision.lock()->IsOverlapping(ingredientBox) && isFalling)
		{
			if (enemyBox.y > ingredientBox.y ) //the ingredient falls on the enemy
				Die();
			else if (enemyBox.y + enemyBox.h < ingredientBox.y + ingredientBox.h) //the enemy is on the falling ingredient
			{
				if (!m_IsFalling && !m_IsDead)
				{
					ingredients[i]->GetComponent<Ingredient>()->AddEnemyOnIngredient(m_GameObject.lock());
					m_IsFalling = true;
				}
			}
		}
	}
}
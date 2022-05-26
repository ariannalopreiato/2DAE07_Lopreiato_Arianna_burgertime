#include "EnemyComponent.h"
#include "GameObject.h"

EnemyComponent::EnemyComponent(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
{
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
	m_Transform.lock()->SetSize(m_EnemyWidth, m_EnemyHeight, 0.0f);
	m_Velocity.x = -1.0f;
	m_Velocity.y = 0.0f;
}

void EnemyComponent::Update(float elapsedSec)
{
	//when reaching intersection it checks which direction takes them closer to the player
	if (m_Animation.lock() == nullptr)
		m_Animation = m_GameObject.lock()->GetComponent<dae::AnimationComponent>();
	if (m_Texture.lock() == nullptr)
		m_Texture = m_GameObject.lock()->GetComponent<dae::TextureComponent>();
	if (m_Collision.lock() == nullptr)
		m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();

	m_Collision.lock()->m_IsBoxVisible = true;
	m_Animation.lock()->m_CanAnimate = true;

	SDL_Rect source = m_Animation.lock()->GetSource();
	m_Texture.lock()->SetSource(source);

	CheckIntersection();

	Move(elapsedSec);
}

void EnemyComponent::Render() const
{
}

void EnemyComponent::SetPlayerPos(const SDL_Rect& playerPos)
{
	m_PlayerPos = playerPos;
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
	else if(m_Velocity.y < 0.0f)
		m_Animation.lock()->SetNewStartingCol(m_StartingColUp);

	auto currentPos = m_Transform.lock()->GetPosition(); //get current position
	glm::vec2 newPos{ currentPos.x, currentPos.y };
	newPos.x += elapsedSec * (m_Velocity.x * m_Speed);
	newPos.y += elapsedSec * (m_Velocity.y * m_Speed);
	m_Transform.lock()->SetPosition(newPos.x, newPos.y, 0.0f); //pass new position
}

bool EnemyComponent::CheckIsNextToStairs()
{
	auto stairs = LevelCreator::GetStairs();
	auto enemyBox = m_Collision.lock()->GetCollisionBox();
	SDL_Rect enemyCenter{};
	enemyCenter.w = enemyBox.w / 3;
	enemyCenter.h = enemyBox.h;
	enemyCenter.y = enemyBox.y;
	enemyCenter.x = enemyBox.x + enemyCenter.w;

	for (size_t i = 0; i < stairs.size(); ++i)
	{
		auto stairCollision = stairs.at(i)->GetComponent<dae::CollisionComponent>();
		auto stairBox = stairCollision->GetCollisionBox();
		if (stairCollision->IsOverlapping(enemyCenter))
			return true;
	}
	return false;
}

void EnemyComponent::CheckIntersection()
{
	if (CheckIsNextToStairs() && IsOnPlatform())
	{
		auto enemyBox = m_Collision.lock()->GetCollisionBox();
		if (!m_HasWalkedStair)
		{
			glm::vec2 startingVelocity = m_Velocity;
			auto stairs = LevelCreator::GetStairs();
			for (size_t i = 0; i < stairs.size(); ++i)
			{
				auto stairBox = stairs.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
				if (stairBox.y > enemyBox.y + (enemyBox.h / 2))
				{
					//can go down
					if (m_PlayerPos.y > enemyBox.y)
					{
						m_Velocity.x = 0.0f;
						m_Velocity.y = 1.0f;
					}
					else if (enemyBox.y == m_PlayerPos.y)
						m_Velocity = startingVelocity;
				}
				else
				{
					//can go up
					if (m_PlayerPos.y < enemyBox.y)
					{
						m_Velocity.x = 0.0f;
						m_Velocity.y = -1.0f;
					}
				}
				m_HasWalkedStair = true;
			}
		}
		else
		{
			m_HasWalkedStair = false;
			if (m_PlayerPos.x < enemyBox.x)
			{
				m_Velocity.x = -1.0f;
				m_Velocity.y = 0.0f;
			}
			else
			{
				m_Velocity.x = 1.0f;
				m_Velocity.y = 0.0f;
			}
		}
	}
}

bool EnemyComponent::IsOnPlatform()
{

	auto platforms = LevelCreator::GetPlatforms();
	auto enemyBox = m_Collision.lock()->GetCollisionBox();
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		auto box = platforms.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
		if (enemyBox.y + enemyBox.h == box.y)
			return true;
	}
	return false;
}

std::shared_ptr<dae::Component> EnemyComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<EnemyComponent>(gameObject);
}
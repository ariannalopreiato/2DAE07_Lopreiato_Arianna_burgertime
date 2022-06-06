#include "Pepper.h"
#include "GameObject.h"
#include "Renderer.h"
#include "PlayerComponent.h"
#include "EnemyManager.h"

Pepper::Pepper(const std::shared_ptr<dae::GameObject>& gameObject, const std::shared_ptr<dae::GameObject>& player)
	:Component(gameObject)
	, m_Player(player)
{
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
	m_Transform.lock()->SetSize(m_SpriteSize, m_SpriteSize, 0.0f);
	SetPosition();
}

void Pepper::SetPosition()
{
	m_PlayerPos = m_Player.lock()->GetComponent<dae::Transform>()->GetPosition();

	auto velocity = m_Player.lock()->GetComponent<PlayerComponent>()->GetVelocity();
	if (velocity.y == 0.0f)
	{
		if (velocity.x > 0.0f)
			m_Transform.lock()->SetPosition(m_PlayerPos.x + m_SpriteSize, m_PlayerPos.y, 0.0f);
		else
			m_Transform.lock()->SetPosition(m_PlayerPos.x - m_SpriteSize, m_PlayerPos.y, 0.0f);
	}
	else
	{
		if (velocity.y > 0.0f)
			m_Transform.lock()->SetPosition(m_PlayerPos.x, m_PlayerPos.y + m_SpriteSize, 0.0f);
		else
			m_Transform.lock()->SetPosition(m_PlayerPos.x, m_PlayerPos.y - m_SpriteSize, 0.0f);
	}
}

void Pepper::Update(float)
{
	if (m_Animation.lock() == nullptr)
		m_Animation = m_GameObject.lock()->GetComponent<dae::AnimationComponent>();
	
	if (m_Collision.lock() == nullptr)
		m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();

	m_Animation.lock()->m_CanAnimate = true;

	CheckIsHitByEnemies();
}

void Pepper::CheckIsHitByEnemies()
{
	auto enemies = EnemyManager::GetEnemies();
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		auto enemyBox = enemies[i]->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
		if (m_Collision.lock()->IsOverlapping(enemyBox))
			enemies[i]->GetComponentInheritance<EnemyComponent>()->m_IsStunned = true;
	}
}

std::shared_ptr<dae::Component> Pepper::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<Pepper>(gameObject, m_Player.lock());
}

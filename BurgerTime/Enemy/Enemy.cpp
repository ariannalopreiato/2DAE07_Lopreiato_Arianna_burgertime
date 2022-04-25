#include "Enemy.h"
#include "Texture2D.h"

Enemy::Enemy(EnemyType type, float x, float y, float width, float height)
	:Enemy(type, Rectf{x, y, width, height})
{}

Enemy::Enemy(EnemyType type, Point2f position, float width, float height)
	:Enemy(type, Rectf{position.x, position.y, width, height})
{}

Enemy::Enemy(EnemyType type, Rectf enemy)
	: m_Type(type)
	, m_EnemyHitBox(enemy)
{}

bool Enemy::DoHitTest(const Rectf& player) const
{
	return dae::utils::IsOverlapping(player, m_EnemyHitBox);
}

bool Enemy::IsDead() const
{
	return false;
}

const Texture2D& Enemy::GetTexture()
{
	return *m_EnemyTexture;
}

const int& Enemy::GetPoints()
{
	return m_Points;
}

const Rectf& Enemy::GetEnemyHitBox()
{
	return m_EnemyHitBox;
}

bool Enemy::IsEnemyStunned()
{
	return m_IsStunned;
}

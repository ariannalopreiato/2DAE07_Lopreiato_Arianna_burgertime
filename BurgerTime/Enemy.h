#pragma once
#include "structs.h"
#include "Vector2f.h"
#include "utils.h"

enum class EnemyType
{
	MrHotDog, MrPickle, MrEgg
};

class Texture2D;
class Enemy
{
public:
	Enemy(EnemyType type, float x, float y, float width, float height);
	Enemy(EnemyType type, Point2f position, float width, float height);
	Enemy(EnemyType type, Rectf enemy);
	virtual void Update(float elapsedSec) = 0;
	virtual void Render() const = 0;
	bool DoHitTest(const Rectf& player) const;
	bool IsDead() const;
	//const Texture2D& GetTexture();
	const int& GetPoints();
	const Rectf& GetEnemyHitBox();
	bool IsEnemyStunned();

protected:
	int m_Points;
	Rectf m_EnemyHitBox;
	EnemyType m_Type;
	Vector2f m_Velocity{ 0.0f, 0.0f };
	///Texture2D* m_EnemyTexture;
	bool m_IsStunned{ false };
};


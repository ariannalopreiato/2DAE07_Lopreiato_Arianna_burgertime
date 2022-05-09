#pragma once
#include "structs.h"
#include "Vector2f.h"
#include "utils.h"


class Texture2D;
class Enemy
{
public:
	Enemy();
	virtual void Update(float elapsedSec) = 0;
	virtual void Render() const = 0;
	bool IsEnemyStunned();

protected:
	bool m_IsStunned{ false };
	Vector2f m_Velocity{ 0.0f, 0.0f };

};


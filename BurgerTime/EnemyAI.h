#pragma once
#include "MiniginPCH.h"

class EnemyAI
{
public:
	//virtual bool CheckIsNextToStairs() = 0;
	//virtual void CheckIntersection() = 0;
	//virtual void Move(float elapsedSec) = 0;
	bool m_IsStunned{ false };

protected:
	float m_Speed{ 18.f };
	glm::vec2 m_Velocity{ 0.0f, 0.0f };
	bool m_CanClimb{ true };
	const float m_EnemyWidth{ 25.f };
	const float m_EnemyHeight{ 30.f };
	//std::weak_ptr<dae::Transform> m_Transform;
	//std::weak_ptr<dae::TextureComponent> m_Texture;
	//std::weak_ptr<dae::AnimationComponent> m_Animation;
	//std::weak_ptr<dae::CollisionComponent> m_Collision;
	//SDL_Rect m_PlayerPos{};
};


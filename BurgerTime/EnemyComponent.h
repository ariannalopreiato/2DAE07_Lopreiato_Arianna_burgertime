#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Transform.h"
#include "AnimationComponent.h"
#include "TextureComponent.h"
#include "LevelCreator.h"

class EnemyComponent : public dae::Component
{
public:
	EnemyComponent(const std::shared_ptr<dae::GameObject>& gameObject);
	virtual void Update(float elapsedSec);
	virtual void ImplementedMovement() = 0;

	void SetPlayerPos(const SDL_Rect& playerPos);
	bool m_IsStunned{ false };

protected:
	virtual void Move(float elapsedSec);
	bool IsNextToStairs();
	bool IsOnPlatform();
	bool CanGoUp();
	bool CanGoDown();
	void CheckIntersection();

	bool m_CanClimb{ true };
	float m_MaxWaitTime{ 3.f };
	float m_CurrentTime{0.0f};
	const float m_Speed{ 18.f };
	SDL_Rect m_CurrentPlatformShape{};

	const float m_EnemyWidth{ 25.f };
	const float m_EnemyHeight{ 30.f };
	glm::vec2 m_Velocity{ 0.0f, 0.0f };

	const int m_StartingColHorizontal{ 2 };
	const int m_StartingColUp{ 4 };
	const int m_StartingColDown{ 0 };

	std::weak_ptr<dae::Transform> m_Transform;
	std::weak_ptr<dae::TextureComponent> m_Texture;
	std::weak_ptr<dae::AnimationComponent> m_Animation;
	std::weak_ptr<dae::CollisionComponent> m_Collision;
	SDL_Rect m_PlayerPos{};
};
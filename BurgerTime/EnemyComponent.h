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
	virtual void Render() const;
	void SetPlayerPos(const SDL_Rect& playerPos);
	bool m_IsStunned{ false };
	bool CheckIsNextToStairs();
	void CheckIntersection();
	bool IsOnPlatform();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	void Move(float elapsedSec);

	bool m_HasWalkedStair{ false };
	const float m_Speed{ 18.f };
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
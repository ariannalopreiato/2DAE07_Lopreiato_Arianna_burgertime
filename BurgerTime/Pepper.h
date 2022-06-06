#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "TextureComponent.h"

class Pepper : public dae::Component
{
public:
	Pepper(const std::shared_ptr<dae::GameObject>& gameObject, const std::shared_ptr<dae::GameObject>& player);
	void SetPosition();
	void Update(float elapsedSec);
	void CheckIsHitByEnemies();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	std::weak_ptr<dae::CollisionComponent> m_Collision;
	std::weak_ptr<dae::AnimationComponent> m_Animation;
	std::weak_ptr<dae::Transform> m_Transform;
	std::weak_ptr<dae::GameObject> m_Player;
	float m_SpriteSize{ 30.f };
	glm::vec3 m_PlayerPos{};
};


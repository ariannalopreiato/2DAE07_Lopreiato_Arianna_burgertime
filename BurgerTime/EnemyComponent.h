#pragma once
#include "MiniginPCH.h"
#include "Component.h"

enum class EnemyType
{
	mrEgg, mrHotDog, mrPickle
};

class EnemyComponent : public dae::Component
{
public:
	EnemyComponent(const std::shared_ptr<dae::GameObject>& gameObject, EnemyType enemyType);
	virtual void Update(float elapsedSec);
	virtual void Render() const;
	bool m_IsStunned{ false };
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	glm::vec2 m_Velocity;
	EnemyType m_EnemyType{ EnemyType::mrHotDog };
};


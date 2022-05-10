#pragma once
#include "structs.h"
#include "Vector2f.h"
#include "utils.h"
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

protected:
	Vector2f m_Velocity{ 0.0f, 0.0f };
	EnemyType m_EnemyType{ EnemyType::mrHotDog };
};


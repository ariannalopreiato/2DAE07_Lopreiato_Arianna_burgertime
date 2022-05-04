#pragma once
#include "Component.h"

class PlayerComponent : public dae::Component
{
public:
	PlayerComponent(const std::shared_ptr<dae::GameObject>& gameObject, int pepperShots);
	void Update(float elapsedSec);
	void Move();
	void Attack();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	int m_PepperShots{ 0 };
	int m_CurrentShots{ 0 };
	//Vector2f m_Velocity{ 0.0f, 0.0f };
	float m_Speed{ 0.0f };
	float m_ElapsedSec{ 0.0f };
};


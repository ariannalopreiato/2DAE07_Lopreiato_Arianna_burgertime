#pragma once
#include "Component.h"

class HealthComponent : public dae::Component
{
public:
	HealthComponent(std::shared_ptr<dae::GameObject> gameObject, int lives);
	void Update(float elapsedTime);
	bool IsDead() const;
	int GetCurrentLives() const;
	void RemoveLife();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	int m_StartingLives{};
	int m_CurrentLives{};
	bool m_IsDead{ false };
};


#pragma once
#include "Component.h"

class PlayerAttackComponent : public dae::Component
{
public:
	PlayerAttackComponent(const std::shared_ptr<dae::GameObject>& gameObject, int pepperShots);
	void Attack();
	int GetPepperShots() const;
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	int m_PepperShots{ 0 };
	int m_CurrentShots{ 0 };
};


#pragma once
#include "Component.h"

class AttackComponent : public dae::Component
{
public:
	AttackComponent(std::shared_ptr<dae::GameObject> gameObject, int pepperShots);
	void Update();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	int m_PepperShots{};
	int m_CurrentShots{};
};


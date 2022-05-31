#pragma once
#include "EnemyComponent.h"

class MrEggComponent : public EnemyComponent
{
public:
	MrEggComponent(const std::shared_ptr<dae::GameObject>& gameObject);
	virtual void ImplementedMovement() override {};
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
private:
};


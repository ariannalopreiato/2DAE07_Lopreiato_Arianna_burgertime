#pragma once
#include "EnemyComponent.h"

class MrPickleComponent : public EnemyComponent
{
public:
	MrPickleComponent(const std::shared_ptr<dae::GameObject>& gameObject);
	virtual void ImplementedMovement() override {};
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
private:
};


#pragma once
#include "EnemyComponent.h"

class MrHotDogComponent : public EnemyComponent
{
public:
	MrHotDogComponent(const std::shared_ptr<dae::GameObject>& gameObject);
	virtual void ImplementedMovement() override {};
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
};


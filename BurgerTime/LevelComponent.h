#pragma once
#include "Component.h"

class LevelComponent : public dae::Component
{
public:
	LevelComponent(const std::shared_ptr<dae::GameObject>& gameObject);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
};


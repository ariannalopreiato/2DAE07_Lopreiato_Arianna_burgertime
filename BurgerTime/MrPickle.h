#pragma once
#include "Enemy.h"
#include "Component.h"

class MrPickle : public Enemy, dae::Component
{
public:
	MrPickle(const std::shared_ptr<dae::GameObject>& gameObject);
};


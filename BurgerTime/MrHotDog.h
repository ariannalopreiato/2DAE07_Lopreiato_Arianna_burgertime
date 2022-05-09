#pragma once
#include "Enemy.h"
#include "Component.h"

class MrHotDog : public Enemy, dae::Component
{
	MrHotDog(const std::shared_ptr<dae::GameObject>& gameObject);
};


#include "MrHotDog.h"

MrHotDog::MrHotDog(const std::shared_ptr<dae::GameObject>& gameObject)
	:Enemy(gameObject)
	, Component(gameObject)
{}
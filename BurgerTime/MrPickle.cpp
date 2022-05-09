#include "MrPickle.h"

MrPickle::MrPickle(const std::shared_ptr<dae::GameObject>& gameObject)
	:Enemy(gameObject)
	, Component(gameObject)
{}

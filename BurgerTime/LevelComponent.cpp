#include "LevelComponent.h"

LevelComponent::LevelComponent(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
{}

std::shared_ptr<dae::Component> LevelComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<LevelComponent>(gameObject);
}

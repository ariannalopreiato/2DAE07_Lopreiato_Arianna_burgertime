#include "MrHotDogComponent.h"

MrHotDogComponent::MrHotDogComponent(const std::shared_ptr<dae::GameObject>& gameObject)
	:EnemyComponent(gameObject)
{
	auto picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/MrHotDog.png");
	auto texture = std::make_shared<dae::TextureComponent>(m_GameObject.lock(), picture);
	m_GameObject.lock()->AddComponent(texture);
	auto animationComponent = std::make_shared<dae::AnimationComponent>(m_GameObject.lock(), 2, 6, 8, 1);
	m_GameObject.lock()->AddComponent(animationComponent);
	m_Texture = texture;
	m_Points = 100;
}

std::shared_ptr<dae::Component> MrHotDogComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<MrHotDogComponent>(gameObject);
}

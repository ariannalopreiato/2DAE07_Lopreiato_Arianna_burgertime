#include "MrEggComponent.h"
#include "LevelCreator.h"

MrEggComponent::MrEggComponent(const std::shared_ptr<dae::GameObject>& gameObject)
	:EnemyComponent(gameObject)
{
	auto picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/MrEgg.png");
	auto texture = std::make_shared<dae::TextureComponent>(m_GameObject.lock(), picture);
	m_GameObject.lock()->AddComponent(texture);
	auto animationComponent = std::make_shared<dae::AnimationComponent>(m_GameObject.lock(), 2, 6, 8, 1);
	m_GameObject.lock()->AddComponent(animationComponent);
	m_Texture = texture;
	m_Points = 300;
}

std::shared_ptr<dae::Component> MrEggComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<MrEggComponent>(gameObject);
}

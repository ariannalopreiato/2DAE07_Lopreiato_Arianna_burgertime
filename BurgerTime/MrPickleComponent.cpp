#include "MrPickleComponent.h"
#include "GameObject.h"

MrPickleComponent::MrPickleComponent(const std::shared_ptr<dae::GameObject>& gameObject)
	:EnemyComponent(gameObject)
{
	auto picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/MrPickle.png");
	auto texture = std::make_shared<dae::TextureComponent>(m_GameObject.lock(), picture);
	m_GameObject.lock()->AddComponent(texture);
	auto animationComponent = std::make_shared<dae::AnimationComponent>(m_GameObject.lock(), 2, 6, 8, 1);
	m_GameObject.lock()->AddComponent(animationComponent);
	m_Texture = texture;
	m_Points = 200;
}

void MrPickleComponent::ImplementedMovement()
{
	if((m_Behaviour.lock()->CanGoLeft() || m_Behaviour.lock()->CanGoRight())
		&&(!m_Behaviour.lock()->CanGoDown() && !m_Behaviour.lock()->CanGoUp()))
		m_IsMoving = true;
}

std::shared_ptr<dae::Component> MrPickleComponent::Clone(const std::shared_ptr<dae::GameObject>&gameObject)
{
	return std::make_shared<MrPickleComponent>(gameObject);
}

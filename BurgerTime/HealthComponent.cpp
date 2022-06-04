#include "HealthComponent.h"
#include "GameObject.h"

HealthComponent::HealthComponent(std::shared_ptr<dae::GameObject> gameObject, int lives)
	:Component(gameObject)
	,m_StartingLives(lives)
	, m_CurrentLives(lives)
{
	//for (size_t i = 0; i < size_t(m_StartingLives); ++i)
		//SpawnLife();
	m_TopMostPos = m_GameObject.lock()->GetComponent<dae::Transform>()->GetPosition();
}

void HealthComponent::Update(float)
{
	if (m_IsDead) 
	{
		m_CurrentLives = m_StartingLives;
		m_IsDead = false;
	};
}

int HealthComponent::GetCurrentLives() const
{
	return m_CurrentLives;
}

void HealthComponent::SpawnLife()
{
	auto picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/LifeIcon.png");
	auto texture = std::make_shared<dae::TextureComponent>(m_GameObject.lock(), picture);

	//auto transform = gameObject->GetComponent<dae::Transform>();
	//transform->SetPosition(m_TopMostPos);
	//transform->SetSize(m_Size, m_Size, 0.0f);
}

void HealthComponent::RemoveLife()
{
	//if (m_CurrentLives > 1)
	//{
	//	--m_CurrentLives;
	//	m_TopMostPos.y -= m_Distance + m_Size;
	//	//m_LivesDisplay[m_LivesDisplay.size() - 1]->m_MarkForDestruction = true;
	//	//m_GameObject.lock()->RemoveChild(m_LivesDisplay[m_LivesDisplay.size() - 1]);
	//	//m_LivesDisplay.pop_back();
	//}
	//else
	//{
	//	m_IsDead = true;
	//	std::cout << "dead" << std::endl;
	//}
}

std::shared_ptr<dae::Component> HealthComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<HealthComponent>(gameObject, m_StartingLives);
}

bool HealthComponent::IsDead() const
{
	return m_IsDead;
}
